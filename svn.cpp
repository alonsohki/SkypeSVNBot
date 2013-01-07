#include <cstdarg>
#include "svn.h"
#include "passthru.h"

namespace
{
    std::string formatString ( const char* format, ... )
    {
        char buffer [ 1024 ];
        va_list vl;
        va_start ( vl, format );
        vsnprintf ( buffer, sizeof(buffer), format, vl );
        va_end ( vl );
        return std::string(buffer);
    }
}

SVN::SVN ( const std::string& repoURL )
: mRepoURL ( repoURL )
{
}

SVN::~SVN ()
{
}


int SVN::getRevision () const
{
    std::string out;
    passthru ( formatString("svn info --non-interactive %s | grep \"^Rev[^ ]*:\" | cut -d' ' -f2", mRepoURL.c_str()), &out );
    return atoi(out.c_str());
}

void SVN::getLog ( int revision, std::string* out ) const
{
    passthru ( formatString("svn log --non-interactive -v -r %d %s", revision, mRepoURL.c_str()), out );
}
