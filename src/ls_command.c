
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "ls_command.h"


void my_ls(void)
{
    DIR *dir;
    struct dirent *entry;


    dir = opendir("."); //현재 디렉토리를 열어라

    if (!dir)
    {
        perror("opendir");
        return;
    }
    else {
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_DIR)
            {
                printf("%s/\n", entry->d_name);
            }
            else
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}