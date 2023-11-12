#pragma once
#include <cstdint>

class c_cmd_qangle
{
public:
    char pad_0[24];   // 0x0000
    float x;          // 0x0018
    float y;          // 0x001C
    float z;          // 0x0020
    char pad_1[1052]; // 0x0024
};                    // Size: 0x0440

class c_user_cmd_base
{
public:
    char pad_0[64];             // 0x0000
    c_cmd_qangle *m_viewangles; // 0x0040
    char pad_1[1016];           // 0x0048
};                              // Size: 0x0440

class CUserCmd
{
public:
    char pad_0[48];          // 0x0000
    c_user_cmd_base *m_base; // 0x0030
    char pad_1[24];          // 0x0038
    uint32_t m_buttons;      // 0x0050
    char pad_2[1004];        // 0x0054
};                           // Size: 0x0440

class CInputSystem
{
public:
    static CInputSystem *Get();

    bool IsRelativeMouseMode();
    void *GetSDLWindow();
    CInputSystem* get_user_cmd(void* a1, std::uint32_t a2)
    {
        // 48 63 DA 4C 8B E1 4C 69 EB
        std::int64_t v5 = 0x460 * a2;
        std::int64_t v6 = *reinterpret_cast<std::int64_t*>(reinterpret_cast<std::uintptr_t>(a1) + v5 + 0x41E0);
        std::int64_t v7 = 0x70 * (0x9A * a2 + v6 % 0x96) + reinterpret_cast<std::uintptr_t>(a1);
        std::uint64_t split_screen = v7 + 0x10;

        return reinterpret_cast<CInputSystem*>(split_screen);
    }

};
