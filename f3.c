#include<pthread.h>
#include<semaphore.h>
#define BUFSIZE 100
#define TRUE 1
#define FALSE 0
#define up(sem) sem_post(&sem)
#define down(sem) sem_wait(&sem)
int buffer[BUFSIZE];
sem_t full_slots, empty_slots;
int head = 0, tail = 0;
void*
producer(void *arg)
{
int dat = 0;
while(TRUE) {
down(empty_slots);

buffer[tail] = dat++;
tail = (tail+1)%BUFSIZE;
up(full_slots);
}
}
void*
consumer(void* arg)
{
while(TRUE) {
down(full_slots);
printf("data = %d\n", buffer[head]);
head = (head+1)%BUFSIZE;
up(empty_slots);
}
}
int
main()
{
pthread_t t1, t2;
sem_init(&empty_slots, 0, BUFSIZE);
sem_init(&full_slots, 0, 0);
pthread_create(&t1, 0, producer, 0);
pthread_create(&t1, 0,consumer, 0);
while(1);
}
