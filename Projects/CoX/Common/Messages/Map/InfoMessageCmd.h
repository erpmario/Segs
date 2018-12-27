/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include "GameCommand.h"
#include "MapEventTypes.h"

struct MapClientSession;
class QString;

enum class MessageChannel : int;
namespace SEGSEvents
{

// [[ev_def:type]]
class InfoMessageCmd : public GameCommandEvent
{
public:
    // [[ev_def:field]]
    QString         m_msg;
    // [[ev_def:field]]
    MessageChannel  m_channel_type;
    int             m_target_player_id;
explicit            InfoMessageCmd() : GameCommandEvent(MapEventTypes::evInfoMessageCmd) {}
                    InfoMessageCmd(MessageChannel t, const QString &msg) : GameCommandEvent(MapEventTypes::evInfoMessageCmd),
                        m_msg(msg),m_channel_type(t)
                    {
                    }
    void            serializeto(BitStream &bs) const override;
    EVENT_IMPL(InfoMessageCmd)
};

} // end of SEGSEvents namespace
