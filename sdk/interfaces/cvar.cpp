#include "cvar.h"

#include "../../src/memory/mem.h"
#include "../../src/utils/constants.h"
#include "../../src/utils/fnv.h"
#include "../../src/virtual/virtual.h"


CCVar* CCVar::Get() {
    static const auto inst = mem::GetInterface(CConstants::TIER_LIB, "VEngineCvar007");
    return inst.Get<CCVar*>();
}

CCVar::CVarIterator_t CCVar::GetFirstCvarIterator() {
    CVarIterator_t iterator = -1;
    vt::CallMethod<void>(this, 12, &iterator);
    return iterator;
}

CCVar::CVarIterator_t CCVar::GetNextCvarIterator(CVarIterator_t prev) {
    CVarIterator_t iterator = prev;
     vt::CallMethod<void>(this, 13, &iterator, prev);
    return iterator;
}

ConVar* CCVar::GetCvarByIndex(CVarIterator_t index) { return vt::CallMethod<ConVar*>(this, 37, index); }

ConVar* CCVar::GetCvarByName(const char* name) {
    const uint32_t hash = fnv::Hash(name);

    CVarIterator_t it = GetFirstCvarIterator();
    do {
        ConVar* cvar = GetCvarByIndex(it);

        if (cvar && fnv::Hash(cvar->m_Name) == hash) {
            return cvar;
        }

        it = GetNextCvarIterator(it);
    } while (it != static_cast<CVarIterator_t>(-1));

    return nullptr;
}