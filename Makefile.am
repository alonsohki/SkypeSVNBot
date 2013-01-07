bin_PROGRAMS=svnbot

svnbot_SOURCES=iniparser.cpp main.cpp skype.cpp
svnbot_CXXFLAGS=`pkg-config --cflags glib-2.0` `pkg-config --cflags dbus-glib-1` -std=gnu++0x
svnbot_LDFLAGS=`pkg-config --libs glib-2.0` `pkg-config --libs dbus-glib-1`
