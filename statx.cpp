#include <iostream>

extern "C"{
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
}

int main(int argc, char *argv[]){
    
    if(argc!=2){
        std::cerr << "only one argument allowed\n";
        return 1;
    }

    struct statx stx = {};

    // erster statx-Aufruf
    int test = statx(AT_FDCWD, argv[1], AT_SYMLINK_NOFOLLOW, STATX_UID | STATX_GID, &stx);
    if (test == -1){
        std::cerr << "failed - errno\n";
        return 1;
    }
    std::cout << "UID: " << stx.stx_uid  << ", GID: " << stx.stx_gid << std::endl;

    // zweiter statx-Aufruf
    test = statx(AT_FDCWD, argv[1], AT_SYMLINK_NOFOLLOW, STATX_SIZE, &stx);
    if (test == -1){
        std::cerr << "failed - errno\n";
        return 1;
    }
    std::cout << "Size: " << stx.stx_size << std::endl;

 // dritter statx-Aufruf
    test = statx(AT_FDCWD, argv[1], AT_SYMLINK_NOFOLLOW, STATX_MODE, &stx);
    if (test == -1){
        std::cerr << "failed - errno\n";
        return 1;
    }
    std::cout << ((stx.stx_mode & S_IRUSR) ? "r" : "-");
    std::cout << ((stx.stx_mode & S_IWUSR) ? "w" : "-");
    std::cout << ((stx.stx_mode & S_IXUSR) ? "x" : "-");
    std::cout << ((stx.stx_mode & S_IRGRP) ? "r" : "-");
    std::cout << ((stx.stx_mode & S_IWGRP) ? "w" : "-");
    std::cout << ((stx.stx_mode & S_IXGRP) ? "x" : "-");
    std::cout << ((stx.stx_mode & S_IROTH) ? "r" : "-");
    std::cout << ((stx.stx_mode & S_IWOTH) ? "w" : "-");
    std::cout << ((stx.stx_mode & S_IXOTH) ? "x" : "-");
    std::cout << "\n";

    return 0;
}
