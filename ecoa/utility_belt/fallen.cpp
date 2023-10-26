#include "gui.hpp"
#include <fstream>

std::string rand_str(std::string flag) {
  std::ifstream file(
      "/home/user42/Documents/dojo_gdb/ecoa/utility_belt/fazeclan");
  if (!file.is_open())
    return (flag);
  getline(file, flag);
  file.close();
  return (flag);
}
