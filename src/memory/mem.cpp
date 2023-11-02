#include "mem.h"
#include "../utils/fnv.h"
#include "../sigscan/sigscan.h"


std::unordered_map<uint32_t, ModulePtr_t> mem::m_CachedModules;
std::vector<CSigScan*> mem::m_ScheduledScans; 


void mem::Initialize()
{
    for(CSigScan* scan : m_ScheduledScans)
    {
        scan->FindSignature();
        scan->FreeData();   
    }

    std::vector<CSigScan*>().swap(m_ScheduledScans);
}

void mem::ScheduleScan(CSigScan* sigScan)
{
   m_ScheduledScans.emplace_back(sigScan);
}

ModulePtr_t&  mem::GetModule(const char* libName) {
    auto hash = fnv::Hash(libName);

    auto it = m_CachedModules.find(hash);
    if (it != m_CachedModules.end()) {
        return it->second;
    }

    auto module = std::make_unique<CModule>(libName);
    if (module->Retrieve()) {
        return m_CachedModules.emplace(hash, std::move(module)).first->second;
    }
    
    static ModulePtr_t null{};
    return null;
}