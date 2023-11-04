#include "playerpawn.h"
#include "../interfaces/schemasystem.h"


bool C_CSPlayerPawnBase::IsPlayerPawn() {
    static CSchemaClassInfo* playerPawnClass =
        CSchemaSystem::Get()->FindTypeScopeForModule(CConstants::CLIENT_LIB)->FindDeclaredClass("C_CSPlayerPawn");
    return Schema_DynamicBinding() == playerPawnClass;
}

bool C_CSPlayerPawnBase::IsObserverPawn() {
    static CSchemaClassInfo* observerPawnClass =
        CSchemaSystem::Get()->FindTypeScopeForModule(CConstants::CLIENT_LIB)->FindDeclaredClass("C_CSObserverPawn");
    return Schema_DynamicBinding() == observerPawnClass;
}