#pragma once

#include "baseentity.h"

class C_CSPlayerPawnBase : public C_BaseEntity {
   public:
    bool IsPlayerPawn();
    bool IsObserverPawn();
};