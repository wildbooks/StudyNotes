/*************************************************************************
	> File Name:    1.lock_set.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月09日 星期二 22时11分34秒
*************************************************************************/
/*
        读锁
            共享锁，同时进行
        写锁
            互斥锁，上锁后其他进程会发生阻塞

*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int lock_set(int fd, int type);

int main(int argc, char* argv[])
{
    int fd;
    /**/
    if((fd = open("hello", O_RDWR)) <0)
    {
        perror("open");
        return -1;
    }

    lock_set(fd, F_WRLCK);
    getchar();

    lock_set(fd, F_UNLCK);
    getchar();
    close(fd);

    return 0;
}


int lock_set(int fd, int type)
{
    struct flock old_lock, lock;

    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_type = type;
    lock.l_pid = -1;

    /*判断文件是否可以上锁*/
    fcntl(fd, F_GETLK, &lock);

    if(lock.l_type != F_UNLCK)
    {
        /*判断文件不能上锁的原因*/
        if(lock.l_type == F_RDLCK) //该文件已有读取锁
        {
            printf("Read lock already set by %d\n", lock.l_pid);
        }

        else if(lock.l_type == F_WRLCK) //该文件已有写入锁
        {
            printf("Write lock already set by %d\n", lock.l_pid);
        }
    }

    /*l_type 可能已被F_GETLK修改过*/
    lock.l_type = type;

    /*跟据不同的type值进行阻塞式上锁或解锁*/
    if((fcntl(fd, F_SETLKW, &lock)) <0)
    {
        printf("Lock failed:type = %d\n", lock.l_type);
        return -1;
    }

    switch(lock.l_type)
    {
        case F_RDLCK:
        {
            printf("Read lock set by %d\n", getpid());
        }
        break;

        case F_WRLCK:
        {
            printf("Write lock set by %d\n", getpid());
        }
        break;

        case F_UNLCK:
        {
            printf("Release lock by %d\n", getpid());
            return 1;
        }
        break;
    }

    return 0;

}




