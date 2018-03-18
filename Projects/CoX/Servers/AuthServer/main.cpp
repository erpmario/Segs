/*
 * Super Entity Game Server Project
 * http://segs.sf.net/
 * Copyright (c) 2006 - 2016 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *

 */
//#define ACE_NTRACE 0
#include "Servers/ServerManager.h"
#include "Servers/server_support.h"
#include "Settings.h"
#include "version.h"
//////////////////////////////////////////////////////////////////////////

#include "Servers/AdminServer/AdminServer.h"
#include "AuthServer.h"
#include "Servers/MapServer/MapServer.h"
#include "Servers/GameServer/GameServer.h"
//////////////////////////////////////////////////////////////////////////

#include <ace/ACE.h>
#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include <ace/Log_Record.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Acceptor.h>

#include <ace/Reactor.h>
#include <ace/TP_Reactor.h>
#include <ace/INET_Addr.h>
#include <ace/OS_main.h> //Included to enable file logging
#include <ace/streams.h> //Included to enable file logging

#include <QtCore/QCoreApplication>
#include <QtCore/QLoggingCategory>
#include <QtCore/QSettings>
#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <memory>
namespace
{
static bool s_event_loop_is_done=false; //!< this is set to true when ace reactor is finished.
ACE_THR_FUNC_RETURN event_loop (void *arg)
{
    ACE_Reactor *reactor = static_cast<ACE_Reactor *>(arg);
    reactor->owner (ACE_OS::thr_self ());
    reactor->run_reactor_event_loop ();
    ServerManager::instance()->StopLocalServers();
    ServerManager::instance()->GetAdminServer()->ShutDown("No reason");
    s_event_loop_is_done = true;
    return (ACE_THR_FUNC_RETURN)nullptr;
}
bool CreateServers()
{
    auto server_manger = ServerManager::instance();
    GameServer *game_instance   = new GameServer;
    MapServer * map_instance    = new MapServer;
    server_manger->SetAdminServer(AdminServer::instance());
    server_manger->SetAuthServer(new AuthServer);
    server_manger->AddGameServer(game_instance);
    server_manger->AddMapServer(map_instance);
    return true;
}

QFile segs_log_target;
void segsLogMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    static QTextStream stdOut(stdout);
    static QTextStream fileLog(&segs_log_target);
    QString message;
    switch (type)
    {
        case QtDebugMsg:
            message = "Debug   : ";
            break;
        case QtInfoMsg:
            message = "";  // no prefix for informational messages
            break;
        case QtWarningMsg:
            message = "Warning : ";
            break;
        case QtCriticalMsg:
            message = "Critical: ";
            break;
        case QtFatalMsg:
            stdOut << "Fatal error" << localMsg.constData();
            abort();
    }
    stdOut << message << localMsg.constData() << "\n";
    stdOut.flush();
    if(type!=QtInfoMsg)
    {
        fileLog << message << localMsg.constData() << "\n";
        fileLog.flush();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // End of anonymous namespace
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ACE_INT32 ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
    segs_log_target.setFileName("output.log");
    if(!segs_log_target.open(QFile::WriteOnly|QFile::Append))
    {
        qCritical() << "Failed to open log file in write mode, will procede with console only logging";
    }
    QLoggingCategory::setFilterRules("*.debug=true\nqt.*.debug=false");
    qInstallMessageHandler(segsLogMessageOutput);
    QCoreApplication q_app(argc,argv);
    QCoreApplication::setOrganizationDomain("segs.nemerle.eu");
    QCoreApplication::setOrganizationName("SEGS Project");
    QCoreApplication::setApplicationName("segs_server");
    QCoreApplication::setApplicationVersion(VersionInfo::getAuthVersion());

    QCommandLineParser parser;
    parser.setApplicationDescription("SEGS - CoX server");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
                          {{"f","config"},
                           "Use the provided settings file, default value is <settings.cfg>",
                           "filename","settings.cfg"}
                      });
    parser.process(q_app);
    if(parser.isSet("help")||parser.isSet("version"))
        return 0;

    Settings::setSettingsPath(parser.value("config")); // set settings.cfg from args

    ACE_Sig_Set interesting_signals;
    interesting_signals.sig_add(SIGINT);
    interesting_signals.sig_add(SIGHUP);

    const size_t N_THREADS = 1;
    ACE_TP_Reactor threaded_reactor;
    ACE_Reactor new_reactor(&threaded_reactor); //create concrete reactor
    std::unique_ptr<ACE_Reactor> old_instance(ACE_Reactor::instance(&new_reactor)); // this will delete old instance when app finishes

    ServerStopper st; // it'll register itself with current reactor, and shut it down on sigint
    new_reactor.register_handler(interesting_signals,&st);

    // Print out startup copyright messages

    qInfo().noquote() << VersionInfo::getCopyright();
    qInfo().noquote() << VersionInfo::getAuthVersion();

    qInfo().noquote() << "main";

    ACE_Thread_Manager::instance()->spawn_n(N_THREADS, event_loop, ACE_Reactor::instance());
    bool no_err = CreateServers();
    if(no_err)
        no_err = ServerManager::instance()->LoadConfiguration();
    if(no_err)
        no_err = ServerManager::instance()->StartLocalServers();
    if(no_err)
        no_err = ServerManager::instance()->CreateServerConnections();
    if(!no_err)
    {
        ACE_Reactor::instance()->end_event_loop();
        ACE_Thread_Manager::instance()->wait();
        ACE_Reactor::close_singleton();
        return -1;
    }
    // process all queued qt messages here.
    while( !s_event_loop_is_done )
        QCoreApplication::processEvents();

    ACE_Thread_Manager::instance()->wait();
    ACE_Reactor::close_singleton();
    return 0;
}
