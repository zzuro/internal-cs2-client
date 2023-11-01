#include "module.h"
#include "../pointer/pointer.h"

CModule::CModule(const char* name) {
    m_Name = name;
    m_Handle = nullptr;
    m_Begin = m_Size = 0;
}

CModule::~CModule() {
    if (!m_Handle) {
        return;
    }
}

bool CModule::Retrieve() {
    if (m_Handle) {
        return true;
    }

    InitializeHandle();
    InitializeBounds();

    return m_Handle != nullptr;
}

uintptr_t CModule::GetInterface(const char* version) {
    uintptr_t rv = 0;
    if (m_Handle) {
        CPointer pCreateInterface = GetProcAddress("CreateInterface");
        if (!pCreateInterface.IsValid()) {
            return rv;
        }

        // Used internally to register classes.
        struct InterfaceReg {
            std::add_pointer_t<uintptr_t()> m_CreateFn;
            const char* m_pName;
            InterfaceReg* m_pNext;  // For the global list.
        };

        InterfaceReg* s_pInterfaceRegs =

        pCreateInterface.Absolute(3, 0).Dereference(1).Get<InterfaceReg*>();

        uint32_t versionHash = fnv1a::Hash(version);
        for (; s_pInterfaceRegs; s_pInterfaceRegs = s_pInterfaceRegs->m_pNext) {
            if (fnv1a::Hash(s_pInterfaceRegs->m_pName) == versionHash) {
                rv = s_pInterfaceRegs->m_CreateFn();
                break;
            }
        }
    }

    return rv;
}

uintptr_t CModule::GetProcAddress(const char* procName) {
    uintptr_t rv = 0;
    if (m_Handle) {
#ifdef _WIN32
        rv = reinterpret_cast<uintptr_t>(::GetProcAddress(static_cast<HMODULE>(m_Handle), procName));
#else
        rv = reinterpret_cast<uintptr_t>(dlsym(m_Handle, procName));
#endif
    }

    return rv;
}

uintptr_t CModule::FindPattern(const std::span<const int>& pattern) const {
    uintptr_t rv = 0;
    if (m_Handle) {
        uint8_t* bytes = reinterpret_cast<uint8_t*>(m_Begin);

        // Faster than pattern[] in debug builds because of _STL_VERIFY.
        const int* patternData = pattern.data();
        const size_t patternSize = pattern.size();

        for (size_t i = 0; i < m_Size - patternSize; ++i) {
            bool found = true;
            for (size_t j = 0; j < patternSize; ++j) {
                if (bytes[i + j] != patternData[j] && patternData[j] != -1) {
                    found = false;
                    break;
                }
            }

            if (found) {
                rv = reinterpret_cast<uintptr_t>(&bytes[i]);
                break;
            }
        }
    }

    return rv;
}

void CModule::InitializeHandle() {
#ifdef _WIN32
    m_Handle = GetModuleHandle(GetName());
#else
    m_Handle = dlopen(GetName(), RTLD_LAZY | RTLD_NOLOAD);
#endif
}

void CModule::InitializeBounds() {
    if (!m_Handle) {
        return;
    }

    MODULEINFO mi;
    BOOL status = GetModuleInformation(GetCurrentProcess(), static_cast<HMODULE>(m_Handle), &mi, sizeof(mi));
    if (status == 0) {
        return;
    }

    SetBounds(reinterpret_cast<uintptr_t>(m_Handle), mi.SizeOfImage);
}

void CModule::SetBounds(uintptr_t begin, uintptr_t size) {
    m_Begin = begin;
    m_Size = size;
}