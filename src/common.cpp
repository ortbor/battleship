#include "../lib/common.hpp"

std::filesystem::path Path() {
  std::string path_str(PATH_MAX + 1, 0);
#if defined(__unix)
  readlink("/proc/self/exe", path_str.data(), PATH_MAX);
#elif defined(_WIN32)
  GetModuleFileName(NULL, path_str.data(), PATH_MAX);
#else
  throw std::runtime_error("Unsupported OS");
#endif
  return std::filesystem::path(path_str).parent_path();
}