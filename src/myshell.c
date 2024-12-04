#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "ls_command.h"
#include "cat_command.h"

#define MAX_LINE 80
#define MAX_ARGS 10

int main()
{

    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while (1)
    {   
        //print the prompt
        printf("myshell> ");
        

        //read the input from the user
        fgets(input, MAX_LINE, stdin);
        //printf("input: %s\n", input);


        //tokenize input
        token = strtok(input, " \n\t");
        int i = 0;
        while (token != NULL)
        {
            argv[i++] = token;
            token = strtok(NULL, " \n\t");
        }
        argv[i] = NULL;

        if(argv[0] == NULL) //empty command 
        {
            continue;
        }

        //exit command
        if(strcmp(argv[0],"exit") == 0)
        {
            printf("goodbye\n");
            exit(0);
        } 
        
        //cd command
        else if (strcmp(argv[0], "cd") == 0)
        {
            chdir(argv[1]);

        } 
        
        //pwd command
        else if (strcmp(argv[0], "pwd") == 0)
        {
            getcwd(input, MAX_LINE);
            printf("%s\n", input);
        }

        else if (strcmp(argv[0], "ls") == 0)
        {
            my_ls();
        }
        
        else if (strcmp(argv[0], "cat") == 0)
        {
            my_cat(argv[1]);
        }

        else {
            if (access(argv[0], X_OK) == 0) {
                pid_t pid = fork(); // 자식 프로세스 생성
                if (pid == 0) { // 자식 프로세스
                    execv(argv[0], argv); // 명령 실행
                    perror("execv"); // 실패 시 오류 메시지 출력
                    exit(EXIT_FAILURE); // 실행 실패 시 종료
                } else if (pid > 0) { // 부모 프로세스
                    int status;
                    waitpid(pid, &status, 0); // 자식 프로세스 종료 대기
                } else {
                    perror("fork"); // fork 실패 처리
                }
            } 
            else 
            {
                printf("not executable: %s\n", argv[0]);
            }

        }

    }

    return 0;
    
}

