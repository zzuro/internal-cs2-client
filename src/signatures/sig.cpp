#include "sig.h"
#include "../sigscan/sigscan.h"
#include "../utils/constants.h"
#include "../utils/stb.hh"

#define SDK_SIG(sig) stb::simple_conversion::build<stb::fixed_string{sig}>::value

namespace signatures {
    CSigScan GetBaseEntity("CGameEntitySystem::GetBaseEntity", CConstants::CLIENT_LIB,
                            {
                                {SDK_SIG("8B D3 E8 ? ? ? ? 48 8B F8 48 85 C0 74 76"), [](CPointer& ptr) { ptr.Absolute(3, 0); }},
                                {SDK_SIG("81 FA ? ? ? ? 77 36")}
                            });

    CSigScan GetHighestEntityIndex("CGameEntitySystem::GetHighestEntityIndex", CConstants::CLIENT_LIB,
                                    {
                                        {SDK_SIG("33 DB E8 ? ? ? ? 8B 08"), [](CPointer& ptr) { ptr.Absolute(3, 0); }},
                                        {SDK_SIG("E8 ? ? ? ? 33 DB 39 5C 24 40"), [](CPointer& ptr) { ptr.Absolute(1, 0); }},
                                    });

    CSigScan GetCSGOInput("CCSGOInput", CConstants::CLIENT_LIB,
                            {   
                                {SDK_SIG("BA ? ? ? ? 48 03 1D ? ? ? ?"), [](CPointer& ptr) { ptr.Absolute(8, 0).Dereference(1); }},
                            });

    CSigScan GetMatricesForView("CRenderGameSystem::GetMatricesForView", CConstants::CLIENT_LIB,
                                {
                                    {SDK_SIG("40 53 48 81 EC ? ? ? ? 49 8B C1")},
                                    {SDK_SIG("48 89 44 24 ? E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? B0 01"), [](CPointer& ptr) { ptr.Absolute(6, 0); }},
                                });

    CSigScan GetHitboxSet("C_BaseEntity::GetHitboxSet", CConstants::CLIENT_LIB,
                        {
                            {SDK_SIG("E8 ? ? ? ? 48 85 C0 0F 85 ? ? ? ? 44 8D 48 07"), [](CPointer& ptr) { ptr.Absolute(1, 0); }},
                            {SDK_SIG("41 8B D6 E8 ? ? ? ? 4C 8B F8"), [](CPointer& ptr) { ptr.Absolute(4, 0); }},
                        });

    CSigScan HitboxToWorldTransforms("C_BaseEntity::HitboxToWorldTransforms", CConstants::CLIENT_LIB,
                                    {
                                        {SDK_SIG("E8 ? ? ? ? 45 33 F6 4C 63 E0"), [](CPointer& ptr) { ptr.Absolute(1, 0); }},
                                    });


    CSigScan ForceJump("dwForceJump", CConstants::CLIENT_LIB,
                            {   
                                {SDK_SIG("48 8B 05 ? ? ? ? 48 8D 1D ? ? ? ? 48 89 45"), [](CPointer& ptr) { ptr.Offset(48); }},
                            });
}  