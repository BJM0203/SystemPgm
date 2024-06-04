#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s 디렉터리이름\n", argv[0]);
        return 1;
    }

    if (mkdir(argv[1], 0777) != 0) {
        perror("디렉터리 생성 오류");
        return 1;
    }

    printf("%s 디렉터리를 생성했습니다.\n", argv[1]);
    return 0;
}

