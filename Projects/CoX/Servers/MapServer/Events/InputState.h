/*
 * Super Entity Game Server Project
 * http://segs.sf.net/
 * Copyright (c) 2006 - 2016 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 */
#pragma once
#include "MapEvents.h"
#include "Entity.h"

class InputState : public MapLinkEvent
{
public:
    InputStateStorage   m_data;
    bool                m_has_target;
    uint32_t            m_target_idx;
    uint32_t            m_assist_target_idx;

public:
    InputState() : MapLinkEvent(MapEventTypes::evInputState),m_user_commands(0)
    {}
    void serializeto(BitStream &) const;
    void partial_2(BitStream &bs);
    void extended_input(BitStream &bs);
    void serializefrom(BitStream &bs);
    void recv_client_opts(BitStream &bs);
    glm::vec3 &pyr() {return m_data.camera_pyr;}
    BitStream m_user_commands;
};
