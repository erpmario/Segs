/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include "CRUDP_Protocol/CRUD_Events.h"

namespace SEGSEvents
{
using GameLinkEvent = CRUDLink_Event;
}
class CharacterClient;
class BitStream;

// TODO: Is GameEventFactory a misleading name, since this class is not a factory for 'all' game events ?
class GameEventFactory final : public CRUD_EventFactory
{
public:
    typedef CharacterClient tClientData ; //!< typedef used by CRUDLink to store per-connection data
    SEGSEvents::GameLinkEvent *EventFromStream(BitStream &bs) override;
};
