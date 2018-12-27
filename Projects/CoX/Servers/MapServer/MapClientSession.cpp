/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

/*!
 * @addtogroup MapServer Projects/CoX/Servers/MapServer
 * @{
 */

#include "MapClientSession.h"
#include "Logging.h"

void MapClientSession::addCommandToSendNextUpdate(std::unique_ptr<SEGSEvents::GameCommandEvent> &&v) {
    m_contents.emplace_back(std::move(v));
}

void MapClientSession::AddShortcut(int index, NetCommand *command)
{
    if (m_shortcuts.find(index) != m_shortcuts.end())
    {
        qDebug() << "Replacing command" << index << m_shortcuts[index]->m_name <<
                    "->" << command->m_name;
    }
    m_shortcuts[index] = command;
}
//! @}

