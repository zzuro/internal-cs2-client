#include "sdl.h"
#include "../../src/memory/mem.h"
#include "../../src/utils/constants.h"


namespace sdl {
    int SetRelativeMouseMode(int enabled) {
        static const auto fn = mem::GetProcAddress(CConstants::SDL_LIB, "SDL_SetRelativeMouseMode");
        return fn.Call<decltype(&SetRelativeMouseMode)>(enabled);
    }

    int SetWindowGrab(void* window, int grabbed) {
        static const auto fn = mem::GetProcAddress(CConstants::SDL_LIB, "SDL_SetWindowGrab");
        return fn.Call<decltype(&SetWindowGrab)>(window, grabbed);
    }

    void WarpMouseInWindow(void* window, float x, float y) {
        static const auto fn = mem::GetProcAddress(CConstants::SDL_LIB, "SDL_WarpMouseInWindow");
        return fn.Call<decltype(&WarpMouseInWindow)>(window, x, y);
    }
}  // namespace sdl