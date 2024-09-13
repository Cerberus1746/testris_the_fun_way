import <vector>;

import clockwork_reverie_object;

export namespace ClockworkReverie {
class GameObject : EngineObject {
public:
  GameObject *parent;
  vector<GameObject> children;

  GameObject get_child(size_t index) { return children[index]; }
};
} // namespace ClockworkReverie
