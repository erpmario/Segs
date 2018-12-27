/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once

#include "trick_definitions.h"
class BinStore;
class QString;

constexpr const static uint32_t tricks_i0_requiredCrc = 0xB46B669E;
constexpr const static uint32_t tricks_i2_requiredCrc = 0xB06B1696;
bool loadFrom(BinStore *s,SceneModifiers &target);
bool LoadModifiersData(const QString &fname, SceneModifiers &m);
void saveTo(const SceneModifiers &target,const QString &baseName,bool text_format=false);
