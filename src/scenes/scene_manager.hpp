#pragma once

#include "scene.hpp"

namespace FunEngine {
class SceneManager : EngineObject {
public:
  Scene active_scene;

  SceneManager();
};
} // namespace FunEngine
