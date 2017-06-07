/*
    条件变量:
        是利用线程间共享的全局变量进行同步的一种机制，主要包括两个动作 ：
        一个线程等待"条件变量的条件成立"而挂起；另一个线程使"条件成立"（
        给出条件 成立信号）。为了防止竞争，条件变量的使用总是和一个互斥锁
        结合在一起。
    http://www.cnblogs.com/cxjchen/archive/2013/05/16/3081596.html
    程序创建了2个新线程使他们同步运行，实现进程t_b打印9以内3的倍数，t_a打印
    其他的数，程序开始线程t_b不满足条件等待，线程t_a运行使a循环加1并打印。直
    到i为3的倍数时，线程t_a发送信号通知进程t_b，这时t_b满足条件，打印i值
 */
#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;/*初始化互斥锁*/
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;//init cond

void *thread1(void*);
void *thread2(void*);

int i = 1; //global

int main(void){
    pthread_t t_a;
    pthread_t t_b;//two thread

    pthread_create(&t_a,NULL,thread2,(void*)NULL);
    pthread_create(&t_b,NULL,thread1,(void*)NULL);//Create thread

    pthread_join(t_b,NULL);//wait a_b thread end
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    exit(0);

}

void *thread1(void *junk){
    for(i = 1;i<= 9; i++){
        pthread_mutex_lock(&mutex); //互斥锁
        printf("call thread1 \n");
        if(i%3 == 0)
            pthread_cond_signal(&cond); //send sianal to t_b
        else
            printf("thread1: %d\n",i);
        pthread_mutex_unlock(&mutex);
        sleep(1);

    }

}

void *thread2(void*junk){
    while(i < 9)
    {
        pthread_mutex_lock(&mutex);
        printf("call thread2 \n");
        if(i%3 != 0)
            pthread_cond_wait(&cond,&mutex); //wait(原子操作，第一步解锁，第二步阻塞)
        printf("thread2: %d\n",i);
        pthread_mutex_unlock(&mutex);
        sleep(1);

    }

}
