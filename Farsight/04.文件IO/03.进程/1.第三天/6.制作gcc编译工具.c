/*************************************************************************
	> File Name:    6.制作gcc编译工具.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月03日 星期三 14时36分35秒
*************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char name[255]="./";
    /*判断参数*/
    if(argc !=2)
    {
        printf("error\n");
        return -1;
    }
    char charname[255];
    strcpy(charname, argv[1]);
    charname[strlen(charname) - 2] = 0;
    remove(charname);
    
    pid_t pid = fork();
    /*子进程*/
    if(!pid)
    {
        execlp("gcc", "gcc", argv[1], "-o", charname, NULL);
        perror("son");
    }
    /*父进程*/
    else if(pid)
    {
        wait(NULL);
        if(access(charname, F_OK) ==0)
        {
            strcat(name, charname);
            printf("%s\n",name);
            execlp(name, name, NULL);
        }
        else
            printf("gcc is error!\n");
    }
    else
        perror("fork");
    return 0;
}
