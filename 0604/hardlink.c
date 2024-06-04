#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // 인수의 유효성 확인
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    // 하드 링크 생성
    if (link(argv[1], argv[2]) == -1) {
        perror("Error creating hard link");
        return 1;
    }

    printf("Hard link created: %s -> %s\n", argv[2], argv[1]);

    return 0;
}
