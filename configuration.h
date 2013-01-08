#pragma once

#include <map>
#include <string>

class Configuration
{
public:
    typedef std::map<std::string, std::string> RepoMap;

public:
        Configuration   ( const char* path );
        ~Configuration  ();

    const std::string&  getSkypeChannel     () const { return mSkypeChannel; }
    const std::string&  getSkypeName        () const { return mSkypeName; }
    const RepoMap&      getRepos            () const { return mRepos; }

    bool                isOk                () const { return mOk; }

private:
    std::string     mSkypeChannel;
    std::string     mSkypeName;
    RepoMap         mRepos;
    bool            mOk;
};

