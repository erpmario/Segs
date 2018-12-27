/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 */

#pragma once
#include "CohTextureConverter.h"
#include "Common/Runtime/Model.h"
#include <glm/vec3.hpp>
#include <QStringList>
#include <memory>
#include <vector>
#include <stdint.h>
namespace Urho3D
{
    class StaticModel;
}
namespace SEGS 
{
    struct VBOPointers;
}
using CoHModel = SEGS::Model;

float *combineBuffers(SEGS::VBOPointers &meshdata, SEGS::Model *mdl);
