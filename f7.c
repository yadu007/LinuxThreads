#include<pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
int nreaders = 0, writing = 0;
void
acquire_read_lock()
{
    pthread_mutex_lock(&mutex);
    while(writing)
    pthread_cond_wait(&cond, &mutex);
    ++nreaders;
    pthread_mutex_unlock(&mutex);
}

void
release_read_lock()
{
    pthread_mutex_lock(&mutex);
    --nreaders;
    if(nreaders == 0) pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}

void
acquire_write_lock()
{
    pthread_mutex_lock(&mutex);
    while(writing || (nreaders > 0))
    pthread_cond_wait(&cond, &mutex);
    writing = 1;
    pthread_mutex_unlock(&mutex);
}

void
release_write_lock()
{
    pthread_mutex_lock(&mutex);
    writing = 0;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}

void*
reader(void *s)
{
    int i;
    while(1) {
    acquire_read_lock();
    for(i = 0; i < 5; i++) {
    printf("reader id: %d, ount: %d\n", (int)s, i);
    sleep(1);
    }
    release_read_lock();
    sched_yield();
    }
}

void*
writer(void *s)
{
    int i;
    while(1) {
    acquire_write_lock();
    for(i = 0; i < 5; i++) {
    printf("writer id: %d, ount: %d\n", (int)s, i);
    sleep(1);
    }
    release_write_lock();
    sched_yield();
    }
}

main()
{
    pthread_t t[6];
    pthread_attr_t attr;
    int i = 0;
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);
    for(i = 0; i < 3; i++)
    pthread_create(&t[i], 0, reader, (void*)i);
    for(; i < 6; i++)
    pthread_create(&t[i], 0, writer, (void*)i);
    while(1);
}
