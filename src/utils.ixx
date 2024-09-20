module;

#include <string>
#include <vector>

export module clockwork_reverie.utils;

export namespace ClockworkReverie::Utils {
/**
 * @brief Split a string on delimiters
 *        This function is not exposed to Python, use `str.split()` instead
 *
 * @param input_str
 * @param delimiter
 * @return std::vector<std::string>>
 */
auto explode(const std::string &input_str, const char &delimiter) {
  std::string next;
  std::vector<std::string> result;

  for (auto curr_char : input_str) {
    if (curr_char == delimiter) {
      if (!next.empty()) {
        result.push_back(next);
        next.clear();
      }
    } else {
      next += curr_char;
    }
  }

  if (!next.empty())
    result.push_back(next);

  return result;
}

struct Version final {
  int major;
  int minor;
  int patch;

  auto operator<=>(const Version &) const = default;

  Version(const int major, const int minor, const int patch)
      : major(major), minor(minor), patch(patch) {}

  Version(const std::string &version_string) {
    auto splitted = explode(version_string, '.');

    major = std::stoi(splitted[0]);
    minor = std::stoi(splitted[1]);
    patch = std::stoi(splitted[2]);
  }
};
} // namespace ClockworkReverie::Utils
