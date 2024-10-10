module;
#ifdef WITH_SDL
#define SDL_GPU_SHADERCROSS_IMPLEMENTATION
#include <SDL_gpu_shadercross.h>

#include <SDL3/SDL.h>
#endif
export module clockwork_reverie;

import clockwork_reverie.utils;

#ifdef WITH_SDL
import clockwork_reverie.graphics.window;
#endif

import clockwork_reverie.math.geometry.basic_shapes;

namespace geometry = ClockworkReverie::Math::Geometry;

export namespace ClockworkReverie {
struct Main final {
private:
  Utils::Version *version;
  const char *name;
  bool is_running;
#ifdef WITH_SDL
  SDL_Event event;
  SDL_GPUDevice *device;

  Graphics::Window *main_window;
#endif

  // SDL_Event event;
  // bool is_running;

public:
  Main(const char *name, Utils::Version *version)
      : version(version), name(name) {
#ifdef WITH_SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
      throw;
    }

    device = SDL_CreateGPUDevice(SDL_ShaderCross_GetSPIRVShaderFormats(), true,
                                 nullptr);
    if (device == nullptr) {
      SDL_Log("GPUCreateDevice failed");
      throw;
    }

    geometry::Size2d<unsigned short int> size(800, 600);

    Graphics::Window window(name, &size, device, SDL_WINDOW_VULKAN);
    this->main_window = &window;
#endif

    is_running = true;
    while (is_running) {

#ifdef WITH_SDL
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
          is_running = false;
          SDL_Log("Quit signal detected.");
          break;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
        }
      }
#endif
      if (!is_running)
        break;
    }
    /*
    auto vertex_shader = LoadShader(device, "RawTriangle.vert", 0, 0, 0, 0);
    if (!vertex_shader) {
      SDL_Log("Failed to create vertex shader!");
      return;
    }


    */
  }

#ifdef WITH_SDL
  SDL_GPUShader *LoadShader(SDL_GPUDevice *device, const char *full_path,
                            Uint32 samplerCount, Uint32 uniformBufferCount,
                            Uint32 storageBufferCount,
                            Uint32 storageTextureCount) {
    // Auto-detect the shader stage from the file name for convenience
    SDL_GPUShaderStage stage;
    if (SDL_strstr(full_path, ".vert")) {
      stage = SDL_GPU_SHADERSTAGE_VERTEX;
    } else if (SDL_strstr(full_path, ".frag")) {
      stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    } else {
      SDL_Log("Invalid shader stage!");
      return NULL;
    }

    size_t codeSize;
    void *code = SDL_LoadFile(full_path, &codeSize);
    if (code == NULL) {
      SDL_Log("Failed to load shader from disk! %s", full_path);
      return NULL;
    }

    SDL_GPUShaderCreateInfo shaderInfo = {
        .code_size = codeSize,
        .code = static_cast<const Uint8 *>(code),
        .entrypoint = "main",
        .format = SDL_GPU_SHADERFORMAT_SPIRV,
        .stage = stage,
        .num_samplers = samplerCount,
        .num_storage_textures = storageTextureCount,
        .num_storage_buffers = storageBufferCount,
        .num_uniform_buffers = uniformBufferCount,
    };

    auto shader = static_cast<SDL_GPUShader *>(
        SDL_ShaderCross_CompileGraphicsShaderFromSPIRV(device, &shaderInfo));

    if (shader == nullptr) {
      SDL_Log("Failed to create shader!");
      SDL_free(code);
      return nullptr;
    }

    SDL_free(code);
    return shader;
  }
#endif
};
} // namespace ClockworkReverie
