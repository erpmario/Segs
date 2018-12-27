/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <memory>
#include <vector>

class QString;

namespace SEGS
{
struct SceneGraph;
struct SceneNode;
} // namespace SEGS

///
/// \brief The MapSceneGraph class and functions operating on it are central point of access to the world's geometry
///
class MapSceneGraph
{
    std::unique_ptr<SEGS::SceneGraph> m_scene_graph;
    //! Contains all nodes from the scene graph that have any properties set, for faster lookups.
    //! @todo consider creating a property-name => [SceneNode,SceneNode] mapping instead ?
    std::vector<SEGS::SceneNode *> m_nodes_with_properties;
    glm::vec3 m_spawn_point;
public:
    MapSceneGraph();
    ~MapSceneGraph();
    bool loadFromFile(const QString &mapname);
    void set_default_spawn_point(glm::vec3 loc) { m_spawn_point = loc; }
    glm::vec3 spawn_location() const { return m_spawn_point; }
    std::vector<glm::mat4> spawn_points(const QString &kind) const;
    void spawn_npcs(class MapInstance *instance);
    void build_combat_navigation_graph();
    void build_pedestrian_navigation_graph();
};
