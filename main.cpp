#include <cstdio>
#include <cstdlib>
#include "configuration.h"
#include "skype.h"
#include "svn.h"
#include <unistd.h>

int main ( int argc, const char* argv[] )
{
    Configuration config ( "svnbot.conf" );
    if ( config.isOk () )
    {
        struct SVNData
        {
            SVN svn;
            int lastRev;
        };

        SkypeConnector connector ( config.getSkypeName().c_str() );

        // Load the repositories from the config and get the initial revision
        puts ( "Fetching initial revisions...");
        std::map<std::string, SVNData> repos;
        for ( auto& repo : config.getRepos() )
        {
            printf ( "\t[%s] ", repo.first.c_str() );
            fflush ( stdout );

            SVN svn ( repo.second );
            int lastRev = svn.getRevision ();
            printf ( "%d\n", lastRev );

            repos[repo.first] = {svn, lastRev};
        }

        // Poll
        while ( true )
        {
            puts ( "Polling...");
            for ( auto& repo : repos )
            {
                printf ( "\t[%s] %d -> ", repo.first.c_str(), repo.second.lastRev );
                fflush ( stdout );

                auto& data = repo.second;
                int rev = data.svn.getRevision ();
                printf ( "%d\n", rev );

                while ( rev > data.lastRev )
                {
                    data.lastRev++;
                    std::string log;
                    data.svn.getLog ( data.lastRev, &log );
                    if ( log.length() > 0 )
                        connector.send ( "CHATMESSAGE %s [%s]\n%s", config.getSkypeChannel().c_str(), repo.first.c_str(), log.c_str() );
                }
            }

            sleep ( config.getPollInterval() );
        }
    }
    return EXIT_SUCCESS;
}

