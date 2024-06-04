#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void mkdir_p(const char* path) {
    char* token, * path_copy;
    char* sep = "/";
    char dir_path[256] = "";

    path_copy = strdup(path);

    token = strtok(path_copy, sep);
    while (token != NULL) {
        strcat(dir_path, token);
        strcat(dir_path, sep);
        mkdir(dir_path, 0777);
        token = strtok(NULL, sep);
    }

    free(path_copy);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s 디렉터리경로\n", argv[0]);
        return 1;
    }

    mkdir_p(argv[1]);
    printf("%s 디렉터리를 생성했습니다.\n", argv[1]);

    return 0;
}

