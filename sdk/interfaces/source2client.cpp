#include "source2client.h"

#include "../../src/memory/mem.h"
#include "../../src/utils/constants.h"

CSource2Client* CSource2Client::Get() {
    static const auto inst = mem::GetInterface(CConstants::CLIENT_LIB, "Source2Client002");
    return inst.Get<CSource2Client*>();
}