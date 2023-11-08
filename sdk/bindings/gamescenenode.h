#pragma once

#include "../../src/math/types/transform.h"
#include "../../src/schema/schema.h"
#include "skeletoninstance.h"


class CGameSceneNode {
   public:
    CSkeletonInstance* GetSkeletonInstance(); // Virtual Index 8
    SCHEMA(CTransform, m_nodeToWorld, "CGameSceneNode", "m_nodeToWorld");
};