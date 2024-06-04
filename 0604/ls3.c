#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// 파일 정보 출력 함수
void print_file_info(const char *filename) {
    struct stat file_stat;

    // 파일 정보 가져오기
    if (stat(filename, &file_stat) == -1) {
        perror("Error getting file info");
        return;
    }

    // 파일 유형 및 권한 출력
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    // 파일 크기 출력
    printf(" %ld", file_stat.st_size);

    // 파일 이름 출력
    printf(" %s\n", filename);
}

// 파일 크기 비교 함수 - qsort에 사용
int compare_file_size(const void *a, const void *b) {
    struct stat file_stat_a, file_stat_b;
    stat(*(const char **)a, &file_stat_a);
    stat(*(const char **)b, &file_stat_b);
    return (file_stat_b.st_size - file_stat_a.st_size);
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    char *files[1000];
    int count = 0;

    // 디렉터리 열기
    if ((dir = opendir(".")) == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // 디렉터리의 파일들 읽기
    while ((entry = readdir(dir)) != NULL) {
        // -a 옵션: 모든 파일 표시
        if (argc > 1 && strcmp(argv[1], "-a") == 0) {
            files[count++] = entry->d_name;
        }
        // 옵션이 없는 경우 기본적으로 숨겨진 파일은 표시하지 않음
        else if (entry->d_name[0] != '.') {
            files[count++] = entry->d_name;
        }
    }

    // -l 옵션: 파일 정보 출력
    if (argc > 1 && strcmp(argv[1], "-l") == 0) {
        for (int i = 0; i < count; ++i) {
            print_file_info(files[i]);
        }
    }
    // -h 옵션: 파일 크기를 인간이 읽기 쉬운 형식으로 표시
    else if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        for (int i = 0; i < count; ++i) {
            struct stat file_stat;
            stat(files[i], &file_stat);
            printf("%s %ld %s\n", (S_ISDIR(file_stat.st_mode)) ? "d" : "-", file_stat.st_size, files[i]);
        }
    }
    // -r 옵션: 파일 이름을 반대로 정렬하여 출력
    else if (argc > 1 && strcmp(argv[1], "-r") == 0) {
        for (int i = count - 1; i >= 0; --i) {
            printf("%s\n", files[i]);
        }
    }
    // 그 외의 경우: 단순 파일 이름 출력
    else {
        for (int i = 0; i < count; ++i) {
            printf("%s\n", files[i]);
        }
    }

    // 디렉터리 닫기
    closedir(dir);

    return 0;
}
