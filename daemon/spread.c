/*
 * The Spread Toolkit.
 *
 * The contents of this file are subject to the Spread Open-Source
 * License, Version 1.0 (the ``License''); you may not use
 * this file except in compliance with the License.  You may obtain a
 * copy of the License at:
 *
 * http://www.spread.org/license/
 *
 * or in the file ``license.txt'' found in this distribution.
 *
 * Software distributed under the License is distributed on an AS IS basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Creators of Spread are:
 *  Yair Amir, Michal Miskin-Amir, Jonathan Stanton, John Schultz.
 *
 *  Copyright (C) 1993-2016 Spread Concepts LLC <info@spreadconcepts.com>
 *
 *  All Rights Reserved.
 *
 * Major Contributor(s):
 * ---------------
 *    Amy Babay            babay@cs.jhu.edu - accelerated ring protocol.
 *    Ryan Caudy           rcaudy@gmail.com - contributions to process groups.
 *    Claudiu Danilov      claudiu@acm.org - scalable wide area support.
 *    Cristina Nita-Rotaru crisn@cs.purdue.edu - group communication security.
 *    Theo Schlossnagle    jesus@omniti.com - Perl, autoconf, old skiplist.
 *    Dan Schoenblum       dansch@cnds.jhu.edu - Java interface.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "arch.h"
#include "spread_params.h"
#include "session.h"
#include "configuration.h"
#include "spu_events.h"
#include "status.h"
#include "log.h"
#include "sess_body.h"
#include "spu_alarm.h"
#include "stdutil/stdutil.h"

// Glib
#include <glib.h>


#ifndef ARCH_PC_WIN95
#  include <grp.h>
#  include <pwd.h>
#  include <unistd.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

#ifdef	ARCH_PC_WIN95
#  include	<winsock2.h>
WSADATA		WSAData;
#endif	/* ARCH_PC_WIN95 */

static	char		*My_name;
static	char		My_name_buf[80];
static	char		Config_file[512];
static	int		Log;

static  const char            Spread_build_date[] = SPREAD_BUILD_DATE;

static	void	Invalid_privilege_decrease(char *user, char *group);

/* auth-null.c: */
void null_init(void);
/* auth-ip.c: */
void ip_init(void);
/* acp-permit.c: */
void permit_init(void);

static void Bye( void )
{
        Alarmp( SPLOG_PRINT, PRINT, "Spread daemon exiting normally!\n" );
}

static void E_exit_events_wrapper( int signum )
{
        E_exit_events_async_safe();
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
void log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer data)
{

   printf("%s", message);

}


//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
static void credits_print( void)
{

   Alarmp( SPLOG_PRINT, SYSTEM, "/===========================================================================\\\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| The Spread Toolkit                                                        |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| Copyright (c) 1993-2016 Spread Concepts LLC                               |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| All rights reserved.                                                      |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| The Spread toolkit is licensed under the Spread Open-Source License.      |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| You may only use this software in compliance with the License.            |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| A copy of the license can be found at http://www.spread.org/license       |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| This product uses software developed by Spread Concepts LLC for use       |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| in the Spread toolkit. For more information about Spread,                 |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| see http://www.spread.org                                                 |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| This software is distributed on an \"AS IS\" basis, WITHOUT WARRANTY OF     |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| ANY KIND, either express or implied.                                      |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| Creators:                                                                 |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Yair Amir             yairamir@cs.jhu.edu                              |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Michal Miskin-Amir    michal@spreadconcepts.com                        |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Jonathan Stanton      jonathan@spreadconcepts.com                      |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    John Schultz          jschultz@spreadconcepts.com                      |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| Major Contributors:                                                       |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Amy Babay            babay@cs.jhu.edu - accelerated ring protocol.     |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Ryan Caudy           rcaudy@gmail.com - contribution to process groups.|\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Claudiu Danilov      claudiu@acm.org - scalable, wide-area support.    |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Cristina Nita-Rotaru crisn@cs.purdue.edu - GC security.                |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Theo Schlossnagle    jesus@omniti.com - Perl, autoconf, old skiplist.  |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Dan Schoenblum       dansch@cnds.jhu.edu - Java interface.             |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| Special thanks to the following for discussions and ideas:                |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    Ken Birman, Danny Dolev, Jacob Green, Mike Goodrich, Ben Laurie,       |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|    David Shaw, Gene Tsudik, Robbert VanRenesse.                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| Partial funding provided by the Defense Advanced Research Project Agency  |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| (DARPA) and the National Security Agency (NSA) 2000-2004. The Spread      |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| toolkit is not necessarily endorsed by DARPA or the NSA.                  |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| For a full list of contributors, see Readme.txt in the distribution.      |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| WWW:     www.spread.org     www.spreadconcepts.com                        |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| Contact: info@spreadconcepts.com                                          |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "|                                                                           |\n");
   Alarmp( SPLOG_PRINT, SYSTEM, "| Version %d.%02d.%02d Built %-17s                                   |\n",
	   (int)SP_MAJOR_VERSION, (int)SP_MINOR_VERSION, (int)SP_PATCH_VERSION, Spread_build_date );
   Alarmp( SPLOG_PRINT, SYSTEM, "\\===========================================================================/\n");
   
}


#define DEFAULT_LOG_FILE "spread.log"
#define DEFAULT_LOG_DIR "/usr/local/rx/log/"

#define DEFAULT_DEAMON_NAME "4803@127.0.0.1"
#define DEFAULT_CONFIG_FILE "/usr/local/rx/etc/spread_config.json"
#define DEFAULT_LOG_LEVEL "WARNING"

static gchar *log_file   = DEFAULT_LOG_FILE;
static gchar* log_dir = DEFAULT_LOG_DIR;
static gchar* log_level = DEFAULT_LOG_LEVEL;

static gchar *daemon_name   = DEFAULT_DEAMON_NAME;
static gchar *config_file   = DEFAULT_CONFIG_FILE;

static gboolean about = FALSE;
static gboolean version = FALSE;

//----------------------------------------------------------------------
// General options
//----------------------------------------------------------------------
static GOptionEntry general_options[] =
{
   { "version", 'v', 0,  G_OPTION_ARG_NONE, &version, "Version", NULL},
   { "about", 'a', 0, G_OPTION_ARG_NONE, &about, "Print credit page.", NULL}, 
   {NULL}
};


//----------------------------------------------------------------------
// Config options
//----------------------------------------------------------------------
static GOptionEntry config_options[] =
{
   { "name", 'n', 0, G_OPTION_ARG_STRING, &daemon_name, "Override local daemon name", NULL},
   { "config-file", 'c', 0, G_OPTION_ARG_STRING, &config_file, "Configuration file.", NULL},
   {NULL}
};

//----------------------------------------------------------------------
// Log options
//----------------------------------------------------------------------
static GOptionEntry log_options[] =
{
   { "log-dir", 'd', 0, G_OPTION_ARG_STRING, &log_dir, "Log directory", NULL},
   { "log-file", 'l', 0, G_OPTION_ARG_STRING, &log_file, "Log file.", NULL},
   { "log-level", 0, 0, G_OPTION_ARG_STRING, &log_level, "Log level", "LEVEL" },
   {NULL}
};



//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
int main(int argc, char *argv[])
{


   GError* error = NULL;
   GOptionContext* context = NULL;

   struct group  *grp;
   struct passwd *pwd;

   // Install log handler
   g_log_set_handler(NULL, G_LOG_LEVEL_WARNING|G_LOG_LEVEL_MESSAGE|G_LOG_FLAG_FATAL, log_handler, NULL);

   // Parse arguments
   context = g_option_context_new("- NGspread");

   GOptionGroup *group;

   group = g_option_group_new("general",
			      "General Options",
			      "General Options",
			      NULL,
			      NULL);

   g_option_group_add_entries(group, general_options);
   g_option_context_set_main_group(context, group);

   
   group = g_option_group_new("config",
			      "Configuration",
			      "Configuration",
			      NULL,
			      NULL);
   
   g_option_group_add_entries(group, config_options);
   g_option_context_add_group(context, group);
   
   group = g_option_group_new("logging",
			      "Logging",
			      "Logging",
			      NULL,
			      NULL);
   g_option_group_add_entries(group, log_options);
   g_option_context_add_group(context, group);


   
   // g_option_context_add_main_entries(context, entries, NULL);

   if(!g_option_context_parse(context, &argc, &argv, &error))
   {
      g_message("%s: option parsing failed: %s", __PRETTY_FUNCTION__, error->message);
      return -1;
   }


   atexit( Bye );
   
   signal( SIGINT,  E_exit_events_wrapper );
   signal( SIGTERM, E_exit_events_wrapper );

   Alarm_set_types( CONF_SYS );
   Alarm_set_priority( SPLOG_INFO );

   if(version)
   {
      version_print();
      exit(0);
   }
   
   if (about)
   {
      credits_print();
      exit(0);
   }
   

        /* initialize each valid authentication protocol */
        null_init();
        ip_init();
#ifdef  ENABLE_PASSWORD
        pword_init();
#endif
        permit_init();

        /* Initialize Access Control & Authentication */
        Acm_init();

	Conf_init( Config_file, My_name );

	E_init();

	{
	  sp_time t = E_get_time();

	  set_rand( (int) stdhcode_oaat( &t, sizeof( t ) ) ^ (int) stdhcode_oaat( &My.id, sizeof( My.id ) ) );
	}

#ifndef	ARCH_PC_WIN95
        /* Verify that unix socket dir is safe if runing as root user */
        if (geteuid() == (uid_t) 0) {
            struct stat usock_stat;
            Alarmp( SPLOG_INFO, SECURITY, "Spread is running as root so check file locations\n");
            if (stat( SP_UNIX_SOCKET, &usock_stat)) {
                Alarmp( SPLOG_FATAL, SECURITY, "Spread unable to stat the unix domain socket dir (%s). Please verify the selected directory and restart the daemon\n", SP_UNIX_SOCKET );
                exit( 0 );
            }

            if ( (usock_stat.st_mode & S_IWOTH) || !(usock_stat.st_uid == (uid_t) 0) )
                Alarmp( SPLOG_WARNING, PRINT, "Spread: SECURITY RISK! running as root, but unix domain socket is not in a root-only writable directory. May risk denial of service or malicious deletion of unexpected file in directory: %s\n", SP_UNIX_SOCKET );
	}
#endif

	Sess_init();

	Stat_init();

#ifndef	ARCH_PC_WIN95

	/* Yupp, we're paranoid */

	if (geteuid() != (uid_t) 0) {
            Alarmp( SPLOG_WARNING, SECURITY, "Spread: not running as root, won't chroot\n" );
	}
	else if ( (grp = getgrnam(Conf_get_group())) == NULL
                  || (pwd = getpwnam(Conf_get_user())) == NULL ) {
            Invalid_privilege_decrease(Conf_get_user(), Conf_get_group());
	}
	else if (chdir(Conf_get_runtime_dir()) < 0
                  || chroot(Conf_get_runtime_dir()) < 0 ) {
            Alarmp( SPLOG_FATAL, SECURITY, "Spread: FAILED chroot to '%s'\n",
                   Conf_get_runtime_dir() );
	}
	else if ( setgroups(1, &grp->gr_gid) < 0
                  || setgid(grp->gr_gid) < 0
                  || setuid(pwd->pw_uid) < 0) {
            Invalid_privilege_decrease(Conf_get_user(), Conf_get_group());
	} else {
            Alarmp( SPLOG_INFO, SECURITY, "Spread: setugid and chroot successeful\n" );
	}

#endif	/* ARCH_PC_WIN95 */

	if( Log ) Log_init();

	E_handle_events();

        Sess_fini();

	return 0;
}
//----------------------------------------------------------------------
//  end main
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
static	void	Invalid_privilege_decrease(char *user, char *group)
{
    Alarmp( SPLOG_FATAL, SECURITY, "Spread: FAILED privilege drop to user/group "
           "'%s/%s' (defined in spread.conf or spread_params.h)\n",
           user, group );
}


//----------------------------------------------------------------------
// EOF
//----------------------------------------------------------------------
