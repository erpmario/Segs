/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include <stdint.h>

enum eAuthPacketType : uint8_t ;
namespace SEGSEvents {
class AuthLinkEvent;
}

class AuthEventFactory
{
public:
using   EventType = SEGSEvents::AuthLinkEvent;
    
static  EventType * EventForType(eAuthPacketType type);
static  void        Destroy(EventType *what);
};
