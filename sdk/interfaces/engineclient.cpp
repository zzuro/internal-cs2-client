#include "engineclient.h"
#include "../../src/memory/mem.h"
#include "../../src/utils/constants.h"
#include "../../src/virtual/virtual.h"

CEngineClient* CEngineClient::Get() {
    static const auto inst = mem::GetInterface(CConstants::ENGINE_LIB, "Source2EngineToClient001");
    return inst.Get<CEngineClient*>();
}

bool CEngineClient::IsInGame() { return vt::CallMethod<bool>(this, 32); }

int CEngineClient::GetLocalPlayer() {
    int index = -1;
    vt::CallMethod<void>(this, 44, &index, 0);
    return index + 1;
}

int CEngineClient::GetEngineBuildNumber() { return vt::CallMethod<int>(this, 77); }