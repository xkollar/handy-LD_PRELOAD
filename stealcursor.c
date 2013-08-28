#include <SDL/SDL.h>
#include <dlfcn.h>

__attribute__((visibility("default")))
SDL_GrabMode SDL_WM_GrabInput(SDL_GrabMode mode __attribute__((unused)))
{
        static SDL_GrabMode (*lib_SDL_WM_GrabInput) (SDL_GrabMode mode) = NULL;
        if (!lib_SDL_WM_GrabInput) {
                lib_SDL_WM_GrabInput = dlsym(RTLD_NEXT, "SDL_WM_GrabInput");
        }
        return lib_SDL_WM_GrabInput(SDL_GRAB_QUERY);
}

__attribute__((visibility("default")))
int SDL_ShowCursor(int i __attribute__((unused)))
{
     return 1;
}
