#include "schema.h"
#include "../utils/fnv.h"
#include "../../sdk/interfaces/schemasystem.h"
#include <iostream>


std::optional<int32_t> CSchemaManager::GetSchemaOffset(const char* moduleName, const char* bindingName, const char* fieldName) {
    CSchemaSystemTypeScope* typeScope = CSchemaSystem::Get()->FindTypeScopeForModule(moduleName);
    if (!typeScope) {
        std::cout << "[schemamgr] No type scope found for '" << moduleName << "'." << std::endl;
        return {};
    }

    CSchemaClassInfo* classInfo = typeScope->FindDeclaredClass(bindingName);
    if (!classInfo) {
        std::cout << "[schemamgr] No binding named '" << bindingName << "' has been found in module '" << moduleName << "'." << std::endl;
        return {};
    }

    uint32_t fieldHash = fnv::Hash(fieldName);
    for (int i = 0; classInfo->m_Fields && i < classInfo->m_nFieldsCount; ++i) {
        auto& field = classInfo->m_Fields[i];
        if (fnv::Hash(field.m_Name) == fieldHash) {
            std::cout << "[schemamgr] '" << bindingName << "::" << fieldName << "' offset is 0x" << std::hex << field.m_nSingleInheritanceOffset << "." << std::endl;
            return field.m_nSingleInheritanceOffset;
        }
    }
    return {};
}