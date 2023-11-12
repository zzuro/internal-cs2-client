#pragma once

#include "../../src/math/types/transform.h"
#include "../../src/schema/schema.h"
#include "modelstate.h"

class CGameSceneNode {
   public:
    SCHEMA(CTransform, m_nodeToWorld, "CGameSceneNode", "m_nodeToWorld");
    SCHEMA(CModelState, m_modelState, "CSkeletonInstance", "m_modelState");
};