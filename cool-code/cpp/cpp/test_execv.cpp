#include <unistd.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
    printf("argv[0]::%s\n",argv[0]);
    printf("argv[1]::%s\n",argv[1]);
    printf("argv[2]::%s\n",argv[2]);
    execv("/bin/ls ",argv);
    return 0;
}
