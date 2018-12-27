/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include "Common/CRUDP_Protocol/CRUD_Events.h"

namespace SEGSEvents
{
using MapLinkEvent = CRUDLink_Event;
}

/////////////////////////////////////////////////////////////////////
class MapEventFactory : public CRUD_EventFactory
{
public:
    SEGSEvents::MapLinkEvent *EventFromStream(BitStream &bs) override;
    static SEGSEvents::MapLinkEvent *CommandEventFromStream(BitStream &bs);
};



