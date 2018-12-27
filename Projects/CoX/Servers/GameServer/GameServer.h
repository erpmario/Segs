/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once

#include "GameLink.h"

#include <memory>

class CharacterDatabase;
class GameServerData;

class GameServer final : public EventProcessor
{
        class PrivateData;
public:
                                IMPL_ID(GameServer)
                                ~GameServer() override;
                                GameServer(int id);
        bool                    ReadConfigAndRestart();
        const ACE_INET_Addr &   getAddress();

        QString                 getName();
        uint8_t                 getId();
        uint16_t                getCurrentPlayers();
        uint16_t                getMaxPlayers();
        int                     getMaxCharacterSlots() const;
protected:
        int                     handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask) override;
        void                    dispatch(SEGSEvents::Event *ev) override;
        void                    serialize_from(std::istream &is) override;
        void                    serialize_to(std::ostream &os) override;
        std::unique_ptr<PrivateData> d;
};
