#pragma once

#include "base.h"
#include <memory>
#include <unordered_map>
#include <mutex>

class CEntityInstance;
class CCachedPlayer;

namespace CMatchCache {
   
    using CachedEntityPtr = std::unique_ptr<CCachedBaseEntity>;

    std::unordered_map<int, CMatchCache::CachedEntityPtr>& GetCachedEntities();
    std::mutex& GetLock();

    void Initialize();

    void AddEntity(CEntityInstance* inst, CBaseHandle handle);
    void RemoveEntity(CEntityInstance* inst, CBaseHandle handle);

    CachedEntityPtr& GetEntityByIndex(int i);
    CCachedPlayer* GetLocalPlayer();

    CachedEntityPtr CreateCachedEntityPointer(C_BaseEntity* ent);

    extern std::mutex m_EntitiesLock;
    extern std::unordered_map<int, CachedEntityPtr> m_CachedEntities;
};