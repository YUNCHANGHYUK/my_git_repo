#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


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
        
    }

    return 0;
    
}

