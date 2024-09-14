module;

#include <string>
#include <vector>

#include <SDL3/SDL.h>

export module clockwork_reverie.graphics.window;

import clockwork_reverie.math.utils;
import clockwork_reverie.math.geometry.basic_shapes;

namespace geometry = ClockworkReverie::Math::Geometry;

export namespace ClockworkReverie::Graphics {

class Window {
  static SDL_Window *main_window;

  std::vector<SDL_Window *> child_windows;

  SDL_GPUDevice *device;
  geometry::Size2d<unsigned short int> size;

public:
  ~Window() {
    SDL_DestroyWindow(main_window);

    for (auto curr_window : child_windows)
      SDL_DestroyWindow(curr_window);
  }

  Window(const std::string &title, geometry::Size2d<unsigned short int> &size,
         SDL_GPUDevice *device, SDL_WindowFlags flags) {
    this->device = device;
    this->size = size;

    auto c_title = title.c_str();

    main_window = SDL_CreateWindow(c_title, size.x_axis, size.y_axis, flags);

    if (!main_window) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                   SDL_GetError());
      return;
    }

    if (!SDL_ClaimWindowForGPUDevice(device, main_window)) {
      SDL_Log("GPUClaimWindow failed");
      return;
    }
  }

  auto get_main_window() { return main_window; }
};

SDL_Window *Window::main_window = nullptr;
} // namespace ClockworkReverie::Graphics
