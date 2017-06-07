/*************************************************************************
	> FilmZed Time: 2016年08月05日 星期五 21时38分13秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    unsigned int time;
    alarm(2);
    pause();
    printf("time = %d\n", time);

    return 0;
}
