#pragma once

#include <cassert>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void __passthru ( const char* cmd, std::string* output )
{
    int pipefd[2];
    assert ( pipe ( pipefd ) == 0 );

    pid_t child = fork ();
    bool weAreInChild = child == 0;

    if ( weAreInChild )
    {
        close ( pipefd[0] );

        int fd = fileno(stdout);
        close ( fd );
        assert ( fd == dup ( pipefd[1] ) );

        int ret = system ( cmd );
        close ( pipefd[1] );
        exit ( ret );
    }

    close ( pipefd[1] );

    char buffer [ 128 ];
    int n;
    while ( ( n = read ( pipefd[0], &buffer[0], sizeof(buffer) - 1) ) > 0 )
    {
        buffer[n] = '\0';
        output->append ( buffer );
    }

    close ( pipefd[0] );
    waitpid ( child, 0, 0 );
}

static void passthru ( const std::string& str, std::string* output )
{
    return __passthru ( str.c_str(), output );
}

static void passthru ( const char* cmd, std::string* output )
{
    return __passthru ( cmd, output );
}

