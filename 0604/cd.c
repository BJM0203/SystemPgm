#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s 디렉터리\n", argv[0]);
        return 1;
    }

    if (chdir(argv[1]) != 0) {
        perror("디렉터리 변경 오류");
        return 1;
    }
    printf("%s로 이동했습니다.\n", argv[1]);
    return 0;
}

