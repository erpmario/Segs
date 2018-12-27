/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include "MapEventTypes.h"
#include "Common/GameData/gui_definitions.h"

namespace SEGSEvents
{
// [[ev_def:type]]
class WindowState final : public MapLinkEvent
{
public:
    // [[ev_def:field]]
    GUIWindow wnd;
    WindowState():MapLinkEvent(MapEventTypes::evWindowState) {}
    void serializeto(BitStream &bs) const override;
    void serializefrom(BitStream &bs) override;
    EVENT_IMPL(WindowState)
};
} // end of SEGSEvents namespace

