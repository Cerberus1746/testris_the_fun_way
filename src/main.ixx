module;

#include <SDL3/SDL.h>
#include <string>

export module engine;

export namespace ClockworkReverie {
struct Version final {
  int major;
  int minor;
  int patch;
};

struct Main final {
private:
  bool is_running;

  SDL_Window *window;
  SDL_Event event;

public:
  std::string name;
  Version version;

  Main(std::string name, Version version) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
      return;
    }

    window = SDL_CreateWindow("An SDL3 window", 640, 480, SDL_WINDOW_VULKAN);

    if (!window) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                   SDL_GetError());
      return;
    }

    is_running = true;
    while (!is_running) {
      while (SDL_PollEvent(&event)) {
      }
    }
  }
};
} // namespace ClockworkReverie
