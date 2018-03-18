/*
 * Super Entity Game Server Project
 * http://segs.sf.net/
 * Copyright (c) 2006 - 2016 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 */
#define _USE_MATH_DEFINES
#include "Entity.h"
#include "Servers/MapServer/DataHelpers.h"

#include <QtCore/QDebug>
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>
//#define LOG_
//TODO: this file needs to know the MapInstance's WorldSimulation rate - Maybe extract it as a configuration object ?

#define WORLD_UPDATE_TICKS_PER_SECOND 30

void Entity::sendAllyID(BitStream &bs)
{
    bs.StorePackedBits(2,0);
    bs.StorePackedBits(4,0); // NPC->0

}
void Entity::sendPvP(BitStream &bs)
{
    bs.StoreBits(1,0);
    bs.StoreBits(1,0);
    bs.StorePackedBits(5,0);
    bs.StoreBits(1,0);
}

void Entity::fillFromCharacter(Character *f)
{
    m_char = *f;
    m_hasname = true;
    m_db_id = m_char.m_db_id;
    m_entity_data.m_origin_idx = getEntityOriginIndex(true, getOrigin(*f));
    m_entity_data.m_class_idx = getEntityClassIndex(true, getClass(*f));
}
/**
 *  This will mark the Entity as being in logging out state
 *  \arg time_till_logout is time in seconds untill logout is done
 */
void Entity::beginLogout(uint16_t time_till_logout)
{
    m_is_logging_out = true;
    m_time_till_logout = time_till_logout*1000;
}

void fillEntityFromNewCharData(Entity &e, BitStream &src,ColorAndPartPacker *packer )
{
    QString description;
    QString battlecry;
    e.m_type = src.GetPackedBits(1); //2. Possibly EntType (ENT_PLAYER)
    e.m_char.GetCharBuildInfo(src);
    e.m_char.recv_initial_costume(src,packer);
    e.m_char.m_char_data.m_has_the_prefix = src.GetBits(1); // The -> 1
    if(e.m_char.m_char_data.m_has_the_prefix)
        e.m_char.m_char_data.m_has_titles = true;
    src.GetString(battlecry);
    src.GetString(description);
    setBattleCry(e.m_char,battlecry);
    setDescription(e.m_char,description);
    e.m_entity_data.m_origin_idx = getEntityOriginIndex(true, getOrigin(e.m_char));
    e.m_entity_data.m_class_idx = getEntityClassIndex(true, getClass(e.m_char));
    setDbId(e,e.m_char.m_db_id);

    // New Character Spawn Location
    //e.m_entity_data.pos                 = glm::vec3(-60.5f,180.0f,0.0f); // Tutorial Starting Location
    e.m_entity_data.pos                   = glm::vec3(128.0f,16.0f,-198.0f); // Atlas Park Starting Location
    e.m_direction                         = glm::quat(1.0f,0.0f,0.0f,0.0f);
}
void Entity::InsertUpdate( PosUpdate pup )
{
    m_update_idx++;
    m_update_idx %=64;
    m_pos_updates[m_update_idx]=pup;
}

void Entity::dump()
{
    QString msg = "EntityDebug\n  "
            + name()
            + "\n  db_id: " + QString::number(m_db_id)
            + "\n  entity idx: " + QString::number(m_idx)
            + "\n  access level: " + QString::number(m_entity_data.m_access_level)
            + "\n  m_type: " + QString::number(m_type)
            + "\n  class idx: " + QString::number(m_entity_data.m_class_idx)
            + "\n  origin idx: " + QString::number(m_entity_data.m_origin_idx)
            + "\n  pos: " + QString::number(m_entity_data.pos.x) + ", "
                          + QString::number(m_entity_data.pos.y) + ", "
                          + QString::number(m_entity_data.pos.z)
            + "\n  orient: " + QString::number(m_entity_data.m_orientation_pyr.p) + ", "
                             + QString::number(m_entity_data.m_orientation_pyr.y) + ", "
                             + QString::number(m_entity_data.m_orientation_pyr.r)
            + "\n  target: " + QString::number(m_target_idx)
            + "\n  assist target: " + QString::number(m_assist_target_idx)
            + "\n  m_SG_id: " + QString::number(m_supergroup.m_SG_id)
            + "\n  m_team_id: " + QString::number(m_team.m_team_id);

    qDebug().noquote() << msg;
    if(m_type == Entity::ENT_PLAYER)
        m_char.dump();
}

void Entity::addPosUpdate(const PosUpdate & p) {
    m_update_idx = (m_update_idx+1) % 64;
    m_pos_updates[m_update_idx] = p;
}

void Entity::addInterp(const PosUpdate & p) {
    interpResults.emplace_back(p);
}

Entity::Entity()
{
    m_entity_data.m_access_level = 9; // enables access to all deve
}

void abortLogout(Entity *e)
{
    e->m_is_logging_out = false; // send logout time of 0
    e->m_time_till_logout = 0;
}

void initializeNewPlayerEntity(Entity &e)
{
    e.m_costume_type                    = 1;
    e.m_destroyed                       = false;
    e.m_type                            = Entity::ENT_PLAYER; // 2
    e.m_create_player                   = true;
    e.m_player_villain                  = false;
    e.m_entity_data.m_origin_idx        = {0};
    e.m_entity_data.m_class_idx         = {0};
    e.m_selector1                       = false;
    e.m_hasname                         = true;
    e.m_supergroup.m_SG_info            = false;
    e.m_team.m_has_team                 = false;
    e.m_pchar_things                    = true;
    e.m_entity_data.m_access_level      = 9;

    e.m_char.reset();
    e.might_have_rare = e.m_rare_bits   = true;
}
