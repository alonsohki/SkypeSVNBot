#pragma once

#include <glib.h>
#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <string>

class SkypeConnector
{
public:
            SkypeConnector      ( const char* instanceName );
            ~SkypeConnector     ();

    void    send                ( const char* format, ... );

private:
    DBusObjectPathVTable    mVtable;
    DBusConnection*         mConnection;
    DBusError               mError;
};

