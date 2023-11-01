#pragma once



namespace mem
{
    auto GetModule(const char* moduleName);
    auto GetInterface(const char* moduleName, const char* interfaceName);
    auto GetProcAddress(const char* moduleName, const char* procName);

    
}