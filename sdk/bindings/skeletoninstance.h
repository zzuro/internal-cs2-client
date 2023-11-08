#pragma once
#include "../../src/schema/schema.h"
#include "modelstate.h"
#include "gamescenenode.h"

class CSkeletonInstance : public CGameSceneNode
{   
public:
    SCHEMA(CModelState, m_modelState, "CGameSceneNode", "m_modelState ");
};