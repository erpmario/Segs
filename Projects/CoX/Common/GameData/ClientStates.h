/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once

enum class ClientStates : uint8_t
{
    SIMPLE = 0,
    CREATE_TEAM_CONTAINER = 1,
    CREATE_TEAM_CONTAINER_WAIT_MAPSVRR_RESPONSE = 2,
    DEAD = 3,
    RESURRECT = 4,
    AWAITING_GURNEY_XFER = 5,
    MAX_CLIENT_STATE
};
