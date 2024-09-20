module;

#define SDL_GPU_SHADERCROSS_IMPLEMENTATION
#include <SDL_gpu_shadercross.h>

#include <SDL3/SDL.h>

#include <memory>
#include <string>
#include <variant>

export module clockwork_reverie;

import clockwork_reverie.utils;
import clockwork_reverie.graphics.window;
import clockwork_reverie.math.geometry.basic_shapes;

namespace geometry = ClockworkReverie::Math::Geometry;

export namespace ClockworkReverie {
struct Main final {
private:
  Utils::Version *version;
  const char *name;
  SDL_Event event;
  SDL_GPUDevice *device;
  bool is_running;

  Graphics::Window *main_window;

  // SDL_Event event;
  // bool is_running;

public:
  Main(const char *name, Utils::Version *version)
      : version(version), name(name) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
      throw;
    }

    device = SDL_CreateGPUDevice(SDL_ShaderCross_GetSPIRVShaderFormats(),
                                 SDL_TRUE, nullptr);
    if (device == nullptr) {
      SDL_Log("GPUCreateDevice failed");
      throw;
    }

    geometry::Size2d<unsigned short int> size(800, 600);

    Graphics::Window window(name, &size, device, SDL_WINDOW_VULKAN);
    this->main_window = &window;

    is_running = true;
    while (is_running) {
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
          is_running = false;
          SDL_Log("Quit signal detected.");
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
        }

        if (!is_running)
          break;
      }
    }
    /*
    auto vertex_shader = LoadShader(device, "RawTriangle.vert", 0, 0, 0, 0);
    if (!vertex_shader) {
      SDL_Log("Failed to create vertex shader!");
      return;
    }


    */
  }

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
        SDL_ShaderCross_CompileFromSPIRV(device, &shaderInfo, SDL_FALSE));

    if (shader == NULL) {
      SDL_Log("Failed to create shader!");
      SDL_free(code);
      return NULL;
    }

    SDL_free(code);
    return shader;
  }
};
} // namespace ClockworkReverie
