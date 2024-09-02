import game_object;
import matrix4x4;

export namespace FunEngine {
class GameObject3d : public GameObject {
public:
  Math::Matrix4x4<double> global_position;

  void set_global_position(double x_axis, double y_axis, double z_axis) {
    global_position.set_position(x_axis, y_axis, z_axis);
  }
};
} // namespace FunEngine
