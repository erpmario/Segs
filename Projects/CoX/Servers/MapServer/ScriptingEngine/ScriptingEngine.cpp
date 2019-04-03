/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2019 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#include "ScriptingEngine.h"

int luaopen_package(lua_State *)
{
    assert(false && "functionality removed");
    return 0;
}

int luaopen_io(lua_State *)
{
    assert(false && "functionality removed");
    return 0;
}

int luaopen_os(lua_State *)
{
    assert(false && "functionality removed");
    return 0;
}

/*!
 * @brief Default constructor. Creates a new ScriptingEnginePrivate instance and assigns it to the corresponding member
 *        variable.
 */
ScriptingEngine::ScriptingEngine()
{
     m_private.reset(new ScriptingEnginePrivate);
}

ScriptingEngine::~ScriptingEngine() = default;

/*!
 * @brief Calls each of the three register functions in turn: register_GenericTypes, register_SpawnerTypes, and
 *        register_CharacterTypes.
 */
void ScriptingEngine::registerTypes()
{
    register_GenericTypes();
    register_SpawnerTypes();
    register_CharacterTypes();
}

//! @}
