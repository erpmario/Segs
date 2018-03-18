/*
 * Super Entity Game Server Project
 * http://segs.sf.net/
 * Copyright (c) 2006 - 2016 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 */

#pragma once
// segs includes

#include "Common/Servers/Client.h"
#include "Common/Servers/Server.h"
#include "Common/Servers/ServerHandle.h"
#include "Common/Servers/AuthServerInterface.h"

// QT includes
#include <QtCore/QHash>
#include <QtCore/QString>

// ACE includes
#include <ace/ACE.h>
#include <ace/INET_Addr.h>
#include <ace/Singleton.h>
#include <ace/Synch.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

#include <unordered_map>

class AuthLink;
typedef ACE_Acceptor<AuthLink, ACE_SOCK_ACCEPTOR> ClientAcceptor;
class IClient;
typedef QHash<QString,AuthClient *> hmClients;
class AuthClient;
class AuthServer final : public IAuthServer
{
//boost::object_pool<AuthClient>          m_client_pool;  //!< pool used to efficiently construct new client objects.
    typedef hmClients::iterator         ihmClients; //!< helper typedef for iterators to m_clients store
    typedef hmClients::const_iterator   cihmClients; //!< helper typedef for const iterators to m_clients store
public:
                                    AuthServer();
                                    ~AuthServer() override;

        bool                        ReadConfig() override;
        bool                        Run(void) override;
        bool                        ShutDown(const QString &reason="No particular reason") override;

        ServerHandle<IAdminServer>  AuthenticateMapServer(const ServerHandle<IMapServer> &map,int version,const std::string &passw) override;
        AuthClient *                GetClientByLogin(const char *) override;
protected:
        ClientAcceptor *            m_acceptor;     //!< ace acceptor wrapping AuthClientService
        ACE_INET_Addr               m_location;     //!< address this server will bind at.
        bool                        m_running;      //!< true if this server is running
        hmClients                   m_clients;      //!< mapping from string:login to client's object
};
