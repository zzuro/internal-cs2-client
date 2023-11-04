#pragma once

#include "../../src/math/types/transform.h"
#include "../../src/schema/schema.h"

class CGameSceneNode {
   public:
    SCHEMA(CTransform, m_nodeToWorld, "CGameSceneNode", "m_nodeToWorld");
};