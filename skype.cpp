#include <cstdio>
#include <cstdarg>
#include "skype.h"

SkypeConnector::SkypeConnector ( const char* instanceName )
{
    dbus_error_init( &mError ); 
    mConnection = dbus_bus_get( DBUS_BUS_SESSION, &mError );
    if ( mConnection == nullptr )
    {
        fprintf( stderr, "Failed to open connection to bus: %s\n", mError.message );
    }
    else
    {
        dbus_connection_register_object_path( mConnection, "/com/Skype/Client", &mVtable, 0 );

        send ( "NAME %s", instanceName );
        send ( "PROTOCOL 7" );
    }
}

SkypeConnector::~SkypeConnector ()
{
    dbus_error_free ( &mError );
}

void SkypeConnector::send ( const char* format, ... )
{
    DBusMessageIter iter;
    va_list vl;
    char buffer [ 8192 * 4 ];
    const char* str = &buffer[0];

    va_start ( vl, format );
    vsnprintf ( buffer, sizeof(buffer), format, vl );
    va_end ( vl );

//    printf ( ">> Skype: %s\n", buffer );

    DBusMessage *message = dbus_message_new_method_call(
        "com.Skype.API",
        "/com/Skype",
        "com.Skype.API",
        "Invoke"
    ); 
 
    if ( !dbus_message_append_args( message, DBUS_TYPE_STRING, &str, DBUS_TYPE_INVALID ) )
        fprintf( stderr, "Error: reply is not except format\n" );
    else 
        dbus_connection_send ( mConnection, message, nullptr );
}

