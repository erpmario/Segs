/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

/*!
 * @addtogroup AuthDatabase Projects/CoX/Servers/AuthDatabase
 * @{
 */

#include "AuthDBSync.h"

#include "AuthDBSyncHandler.h"

#include <QDebug>
static AuthDBSyncHandler *s_db_sync_handler=nullptr;
void startAuthDBSync()
{
    if(s_db_sync_handler!=nullptr)
    {
        qCritical() << "Cannot start db sync service, it's already running";
        return;
    }
    s_db_sync_handler = new AuthDBSyncHandler;
    s_db_sync_handler->activate();
}

//! @}
