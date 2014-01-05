/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <string>
#include <iostream>

#include "web_server.hh"
#include "apache_configuration.hh"
#include "system_runner.hh"
#include "config.h"
#include "util.hh"

using namespace std;

WebServer::WebServer( const Address & addr, const string & record_folder, const string & user )
    : pid_file_name(),
      config_file( apache_main_config + record_folder + "\n" ),
      error_log( "", "error" ),
      access_log( "", "access" )
{
    /* make pid file using random number */
    pid_file_name = "/tmp/lock" + to_string( random() );

    /* if port 443, add ssl components */
    if ( addr.port() == 443 ) { /* ssl */
        config_file.append( apache_ssl_config );
    }

    /* add pid file, log files, user/group name, and listen line to config file and run apache */
    config_file.append( "PidFile " + pid_file_name + "\n" );

    config_file.append( "ErrorLog " + error_log.name() + "\n" );

    config_file.append( "CustomLog " + access_log.name() + " common" + "\n" );

    config_file.append( "User " + user + "\n" );

    config_file.append( "Group " + user + "\n" );

    config_file.append( "Listen " + addr.ip() + ":" + to_string( addr.port() ) );

    run( { APACHE2, "-f", config_file.name(), "-k", "start" } );
}

WebServer::~WebServer()
{
    run( { APACHE2, "-f", config_file.name(), "-k", "stop" } );

    /* delete pid file */
    SystemCall( "remove", remove( pid_file_name.c_str() ) );
}
