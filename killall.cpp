#include <cstring>
#include <iostream>
#include <cstdlib>
#include <csignal>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>
extern "C"{
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <name>\n";
    return 1;
  }

  const char* name = argv[1];
  DIR* proc_dir = opendir("/proc");
  if (proc_dir == nullptr) {
    std::cerr << "Error opening /proc\n";
    return 1;
  }

  struct dirent* entry;
  while ((entry = readdir(proc_dir)) != nullptr) {

    char* endptr;
    long pid = strtol(entry->d_name, &endptr, 10);
    if (*endptr != '\0') {
      continue;
    }



    char status_path[256];
    snprintf(status_path, sizeof(status_path), "/proc/%ld/status", pid);
    std::ifstream status_file(status_path);
    std::string line;


    while (std::getline(status_file, line)) {
      if (line.compare(0, strlen("Name:"), "Name:") == 0) {
        std::string name_str = line.substr(strlen("Name:") + 1);
        if (name_str.find(name) != std::string::npos) {
          if (kill(pid, SIGKILL) == -1) {
            std::cerr << "Error killing process " << pid << "\n";
          } else {
            std::cout << "Killed process " << pid << "\n";
          }
        }
        break;
      }
    }
  }

  closedir(proc_dir);
  return 0;
}
