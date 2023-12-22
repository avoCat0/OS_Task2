#include <iostream>

extern "C" {
#include <sys/utsname.h>
}

int main() {
    struct utsname info;
    uname(&info);

    std::cout << "Hostname: " << info.nodename << std::endl;
    std::cout << "OS: " << info.sysname << std::endl;
    std::cout << "Version: " << info.version << std::endl;
    std::cout << "Release: " << info.release << std::endl;

    return 0;
}