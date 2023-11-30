#pragma once
#include <cstdint>
#include "../bindings/user_cmd.h"

class CInputSystem
{
public:
    static CInputSystem *Get();

    bool IsRelativeMouseMode();
    void *GetSDLWindow();

    CUserCmd* GetUserCmd() { return &pCommandsArray[iSequenceNumber % 150]; }

    char pad_0x0000[0x250];        
    CUserCmd pCommandsArray[150];  
    char pad002[0x1];
	bool bInThirdperson;
	char pad003[0x22];
	int32_t iSequenceNumber;
    
};
