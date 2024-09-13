module;

#include <string>
#include <vector>

export module clockwork_reverie.utils;

export namespace ClockworkReverie::Utils {
/**
 * @brief This function is not exposed to Python, use `str.split()` instead
 *
 * @param input_str
 * @param delimiter
 * @return std::vector<std::string>>
 */
auto explode(const std::string &input_str, const char &delimiter) {
  std::string next;
  std::vector<std::string> result;

  for (auto iter = input_str.begin(); iter != input_str.end(); iter++) {
    if (*iter == delimiter) {
      if (!next.empty()) {
        result.push_back(next);
        next.clear();
      }
    } else
      next += *iter;
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

  static Version from_string(const std::string str) {
    auto splitted = explode(str, '.');

    return Version(std::stoi(splitted[0]), std::stoi(splitted[1]),
                   std::stoi(splitted[2]));
  }
};
} // namespace ClockworkReverie::Utils
