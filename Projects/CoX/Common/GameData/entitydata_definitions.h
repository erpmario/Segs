/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once

#include <QtCore/QString>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

struct EntityData
{
<<<<<<< HEAD
static const constexpr  uint32_t    class_version       = 3;
=======
static const constexpr  uint32_t    class_version       = 5;    // v5: removes m_current_map
>>>>>>> upstream/master
                        uint32_t    m_access_level      = 0;
                        uint8_t     m_origin_idx        = {0};
                        uint8_t     m_class_idx         = {0};
                        glm::vec3   m_pos;
                        glm::vec3   m_orientation_pyr;          // Stored in Radians
<<<<<<< HEAD
                        uint32_t    m_map_idx           = 1;    // only 1 map instance
=======
                        uint32_t    m_map_idx           = 0;	// map_idx == 0 will load up Outbreak. So newly-created characters will go there
>>>>>>> upstream/master
};
