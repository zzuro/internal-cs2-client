#include "virtual.h"
#include <iostream>

CPointer vt::GetMethod(CPointer base, uint32_t index) {
    if (!base.IsValid()) {
        return 0;
    }

    CPointer VTable = base.GetField<uintptr_t>(0);
    if (!VTable.IsValid()) {
        return 0;
    }

    return VTable.GetField<uintptr_t>(index * sizeof(uintptr_t));
}
