#include <cstdio>
#include "configuration.h"
#include "iniparser.h"

Configuration::Configuration ( const char* file )
: mOk ( false )
{
    Rsl::File::Ini::IniParser parser ( file );
    const char* val = parser.GetValue ( "svn", "poll_interval" );
    if ( val )
        mPollInterval = atoi(val);
    else
    {
        fprintf ( stderr, "Configuration error: No SVN poll interval found\n" );
        return;
    }

    val = parser.GetValue ( "skype", "instance_name" );
    if ( val )
        mSkypeName = val;
    else
    {
        fprintf ( stderr, "Configuration error: No Skype instance name given\n" );
        return;
    }

    val = parser.GetValue ( "skype", "channel" );
    if ( val )
        mSkypeChannel = val;
    else
    {
        fprintf ( stderr, "Configuration error: No Skype channel given\n" );
        return;
    }

    for ( int i = 1; true; ++i )
    {
        char repoName [ 32 ];
        snprintf ( repoName, sizeof(repoName), "repo%d", i );
        val = parser.GetValue ( repoName, "name" );
        if ( val == nullptr )
            break;
        const char* url = parser.GetValue ( repoName, "url" );
        if ( url == nullptr )
        {
            fprintf ( stderr, "Configuration warning: No URL configured for repo '%s'\n", val );
        }
        else
            mRepos[val] = url;
    }

    if ( mRepos.size() == 0 )
    {
        fprintf ( stderr, "Configuration error: No repositories could be found!\n" );
        return;
    }

    mOk = true;
}

Configuration::~Configuration ()
{
}

