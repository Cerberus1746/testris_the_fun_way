module;

#define SDL_GPU_SHADERCROSS_IMPLEMENTATION
#include <SDL3/SDL.h>
#include <SDL_gpu_shadercross.h>

#include <string>
#include <variant>

export module clockwork_reverie;

import clockwork_reverie.utils;

export namespace ClockworkReverie {

struct Main final {
private:
  bool is_running;

  SDL_Window *window;
  SDL_GPUDevice *device;
  SDL_Event event;

public:
  std::string name;
  Utils::Version version;

  SDL_GPUShader *LoadShader(SDL_GPUDevice *device, const char *shaderFilename,
                            Uint32 samplerCount, Uint32 uniformBufferCount,
                            Uint32 storageBufferCount,
                            Uint32 storageTextureCount) {
    // Auto-detect the shader stage from the file name for convenience
    SDL_GPUShaderStage stage;
    if (SDL_strstr(shaderFilename, ".vert"))
      stage = SDL_GPU_SHADERSTAGE_VERTEX;
    else if (SDL_strstr(shaderFilename, ".frag"))
      stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    else {
      SDL_Log("Invalid shader stage!");
      return NULL;
    }

    char fullPath[256];
    SDL_snprintf(fullPath, sizeof(fullPath),
                 "%sContent/Shaders/Compiled/%s.spv", SDL_GetBasePath(),
                 shaderFilename);

    size_t codeSize;
    auto code = SDL_LoadFile(fullPath, &codeSize);
    if (!code) {
      SDL_Log("Failed to load shader from disk! %s", fullPath);
      return NULL;
    }

    SDL_GPUShader *shader;
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
    if (SDL_GetGPUDriver(device) == SDL_GPU_DRIVER_VULKAN) {
      shader = SDL_CreateGPUShader(device, &shaderInfo);
    } else {
      shader = static_cast<SDL_GPUShader *>(
          SDL_ShaderCross_CompileFromSPIRV(device, &shaderInfo, SDL_FALSE));
    }
    if (shader == NULL) {
      SDL_Log("Failed to create shader!");
      SDL_free(code);
      return NULL;
    }

    SDL_free(code);
    return shader;
  }

  Main(std::string name,
       std::variant<const Utils::Version, const std::string> version) {
    if (std::holds_alternative<const std::string>(version))
      this->version =
          Utils::Version::from_string(std::get<const std::string>(version));
    else
      this->version = std::get<const Utils::Version>(version);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
      SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
      return;
    }

    device = SDL_CreateGPUDevice(SDL_ShaderCross_GetShaderFormats(), SDL_TRUE,
                                 NULL);
    if (!device) {
      SDL_Log("GPUCreateDevice failed");
      return;
    }

    window = SDL_CreateWindow("An SDL3 window", 640, 480, SDL_WINDOW_VULKAN);
    if (!window) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                   SDL_GetError());
      return;
    }

    if (!SDL_ClaimWindowForGPUDevice(device, window)) {
      SDL_Log("GPUClaimWindow failed");
      return;
    }

    auto vertex_shader = LoadShader(device, "RawTriangle.vert", 0, 0, 0, 0);
    if (!vertex_shader) {
      SDL_Log("Failed to create vertex shader!");
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
