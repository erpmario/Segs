/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include "GameCommand.h"
#include "MapEventTypes.h"

namespace SEGSEvents
{

// [[ev_def:type]]
class ChatDividerMoved : public MapLinkEvent
{
public:
    // [[ev_def:field]]
    float m_position;

    ChatDividerMoved() : MapLinkEvent(MapEventTypes::evChatDividerMoved) {}

    // SerializableEvent interface
    void serializefrom(BitStream &src) override;
    void serializeto(BitStream &) const override;
    EVENT_IMPL(ChatDividerMoved)
};

} // end of SEGSEvents namespace

