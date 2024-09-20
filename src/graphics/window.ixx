module;

#include <memory>
#include <vector>

#include <SDL3/SDL.h>

export module clockwork_reverie.graphics.window;

import clockwork_reverie.math.utils;
import clockwork_reverie.math.geometry.basic_shapes;

namespace geometry = ClockworkReverie::Math::Geometry;
export namespace ClockworkReverie::Graphics {
class SDLWindow {
  SDL_Window *window;

public:
  SDLWindow(const char *title, int width, int height, SDL_WindowFlags flags)
      : window(SDL_CreateWindow(title, width, height, flags)) {
    if (window == nullptr) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                   SDL_GetError());
      throw;
    }
    SDL_Log("SDLWindow created");
  }

  ~SDLWindow() {
    SDL_DestroyWindow(window);
    SDL_Log("SDLWindow Destroyed");
  }

  auto get() { return window; }
};

struct Window {
  SDLWindow window;
  Window *parent;
  std::vector<Window> children;

  const char *title;
  SDL_GPUDevice *device;

  ~Window() {
    children.clear();
    release_from_device();
    SDL_Log("Window Destroyed");
  }

  Window(const char *title, geometry::Size2d<unsigned short int> *size,
         SDL_GPUDevice *device, SDL_WindowFlags flags)
      : window(title, size->get_width(), size->get_height(), flags),
        title(title), device(device) {

    if (!SDL_ClaimWindowForGPUDevice(device, window.get())) {
      SDL_Log("GPUClaimWindow failed");
      throw;
    }
  }

  void release_from_device() {
    SDL_ReleaseWindowFromGPUDevice(device, window.get());
  }
};
} // namespace ClockworkReverie::Graphics
