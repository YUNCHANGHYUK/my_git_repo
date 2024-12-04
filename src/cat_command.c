#include <unistd.h>  
#include <fcntl.h>    
#include <stdio.h>  
#include <stdlib.h>   
#include "cat_command.h"

#define BUFFER_SIZE 1024  

void my_cat(const char *filename) {
    if (filename == NULL) {
        write(STDOUT_FILENO, "사용법: cat <파일명>\n", 17);
        return;
    }

    // 파일을 읽기 전용으로 엽니다.
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("cat");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // 파일에서 데이터를 읽어와 표준 출력으로 씁니다.
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
        if (bytes_written < 0) {
            perror("write");
            close(fd);
            return;
        }
    }

    // 읽기 중 오류가 발생했는지 확인합니다.
    if (bytes_read < 0) {
        perror("read");
    }

    // 파일 디스크립터를 닫습니다.
    close(fd);
}
