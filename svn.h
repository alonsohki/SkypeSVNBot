#pragma once

#include <string>

class SVN
{
public:
            SVN             () {}
            SVN             ( const std::string& repoURL );
            ~SVN            ();

    int     getRevision     () const;
    void    getLog          ( int revision, std::string* out ) const;

private:
    std::string     mRepoURL;
};

