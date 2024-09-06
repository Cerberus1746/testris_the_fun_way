module;

#include <vector>

export module engine.graphical_device;

namespace ClockworkReverie::Graphics {

class GraphicDevice {
  static std::vector<GraphicDeviceBase> graphic_devices;

public:
  static void register() {}

};

struct GraphicDeviceBase {
  GraphicDeviceBase(std::string name) {
    GraphicDevice.register(name, this)
  }
};

} // namespace ClockworkReverie::Graphics
