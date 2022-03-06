#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/*
 int pthread_create(pthread_t *thread,const pthread_attr *attr,void *(start_routime)(void *),void *arg);
 pthread_t * thread              thread id
 const pthread_attr_t *attr      thread attr
 void *(start_routime)(void *)   thread function
 void *arg                       para
 */

class Thread{
public:
    Thread();
    ~Thread();
    int Start();
    static void* ThreadFunc(void *);
    int Run();
private:
    pthread_t mTid;
};
Thread::Thread() : mTid{0}{}
Thread::~Thread() {}
int Thread::Start(){
    return pthread_create(&mTid,NULL,&Thread::ThreadFunc,(void*)this) == 0;
}
void *Thread::ThreadFunc(void *arg){
    Thread * self = (Thread*)arg;
    self->Run();
    return NULL;
}
int Thread::Run(){
    while(1){
        printf("%d\n",mTid);
        sleep(1);
    }
    return 1;
}

int main(){
    Thread t1;
    t1.Start();
    Thread t2;
    t1.Start();
    while(1){
        sleep(1);
    }
}
