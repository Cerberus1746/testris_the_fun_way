import <vector>;

import engine_object;

export namespace FunEngine {
class GameObject : EngineObject {
public:
  GameObject *parent;
  vector<GameObject> children;

  GameObject get_child(size_t index){ return children[index]; }
};
} // namespace FunEngine
