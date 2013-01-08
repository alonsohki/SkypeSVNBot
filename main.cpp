#include <cstdio>
#include <cstdlib>
#include "configuration.h"
#include "skype.h"
#include "svn.h"

int main ( int argc, const char* argv[] )
{
    Configuration config ( "svnbot.conf" );
    if ( config.isOk () )
    {
        SkypeConnector connector ( config.getSkypeName().c_str() );
    }
    return EXIT_SUCCESS;
}

