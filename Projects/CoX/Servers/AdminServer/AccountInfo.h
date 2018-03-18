/*
 * Super Entity Game Server Project
 * http://segs.sf.net/
 * Copyright (c) 2006 - 2016 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 */

#pragma once

// ACE Logging
#include <QtCore/QString>
#include <string>
#include <vector>

class IClient;
class CharacterClient;
class CharacterCostume;
class Character;
class Entity;

class AdminDatabase;
class CharacterDatabase;

class AccountInfo
{
    friend class CharacterDatabase;
    friend class AdminDatabase;

    QString                     m_login;
    uint8_t                     m_access_level;
    uint64_t                    m_acc_server_acc_id;

    uint64_t                    m_game_server_acc_id;
    std::vector<Character *>    m_characters;
    uint8_t                     m_max_slots;

    void                        max_slots(uint8_t maxs) {m_max_slots=maxs;}
    void                        game_server_id(uint64_t id){m_game_server_acc_id=id;}
    bool                        fill_characters_db();
    int8_t                      char_slot_index(Character *c);
public:
                                AccountInfo();

    uint8_t                     access_level() const { return m_access_level; }
    void                        access_level(uint8_t val) { m_access_level = val; }
    const QString &             login() const {return m_login;}
    void                        login(const QString & v){m_login=v;}

    uint64_t                    account_server_id() const {return m_acc_server_acc_id;}
    void                        account_server_id(const uint64_t &v) {m_acc_server_acc_id=v;}
    uint64_t                    game_server_id() const {return m_game_server_acc_id;}
    uint8_t                     max_slots() {return m_max_slots;}
    Character *                 get_character(size_t idx);
    Character *                 create_new_character(); // returns 0 if no free slots are left
    bool                        store_new_character(Entity *e, Character *c);
    bool                        remove_character(Character *character);
    bool                        fill_game_db(uint64_t game_server_idx);
    void                        reset();
};
