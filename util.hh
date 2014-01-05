/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef UTIL_HH
#define UTIL_HH

#include <string>
#include <cstring>

#include "address.hh"
#include "poller.hh"
#include "signalfd.hh"
#include "child_process.hh"

std::string shell_path( void );
void drop_privileges( void );
void check_requirements( const int argc, const char * const argv[] );
bool check_folder_existence( const std::string & directory );
std::string check_storage_folder( const char * const folder_path );
Address first_nameserver( void );
void prepend_shell_prefix( const std::string & str );
template <typename T> void zero( T & x ) { memset( &x, 0, sizeof( x ) ); }

PollerShortNames::Result handle_signal( const signalfd_siginfo & sig,
                                        ChildProcess & child_process );

#endif /* UTIL_HH */
