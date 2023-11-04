#include "schemasystem.h"

#include "../../src/memory/mem.h"
#include "../../src/utils/constants.h"
#include "../../src/virtual/virtual.h"

CSchemaSystem* CSchemaSystem::Get() {
    static const auto inst = mem::GetInterface(CConstants::SCHEMASYSTEM_LIB, "SchemaSystem_001");
    return inst.Get<CSchemaSystem*>();
}

CSchemaSystemTypeScope* CSchemaSystem::FindTypeScopeForModule(const char* name) {
    return vt::CallMethod<CSchemaSystemTypeScope*>(this, 13, name, nullptr);
}

CSchemaClassInfo* CSchemaSystemTypeScope::FindDeclaredClass(const char* name) {
    CSchemaClassInfo* binding = nullptr;
    vt::CallMethod<void>(this, 2, &binding, name);
    return binding;
}

bool CSchemaClassInfo::InheritsFrom(CSchemaClassInfo* other) {
    if (!other || !m_BaseClasses) return false;

    if (this == other) return true;

    for (int i = 0; i < m_nBaseClassesCount; ++i) {
        auto& baseClass = m_BaseClasses[i];
        if (baseClass.m_pClass->InheritsFrom(other)) {
            return true;
        }
    }

    return false;
}