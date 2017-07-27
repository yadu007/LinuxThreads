
/*
IMPLEMENTATION OF SEMAPHORES USING CONDITION VARIABLES AND MUTEXES
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
 int val;
 pthread_mutex_t mutex;
 pthread_cond_t cond;
}semaphore;

void sem_init(semaphore *Initial, int value) //here we put the initial value to the semaphore                                                    
{                                                                   
Initial->val = value;                                
}        

void sem_post(semaphore *sem)  //function similar to sem_post                                  
{                                                                      
  pthread_mutex_lock(&(sem->mutex)); 
  s->val++;                        //increasing the value of semaphore                
  pthread_cond_signal(&(sem->cond)); //signaling to wake up waiting threads
  pthread_mutex_lock(&(sem->mutex)); 
}    

void sem_wait(semaphore *s)  //function similar to sem_wait                                            
{   
                                                                                 
  pthread_mutex_lock(&(s->mutex));                
  while(s->val <= 0)
    {                                         
       pthread_cond_wait(&(s->cond),&(s->mutex)); //continue if a signal received from the other thread
       s->val--;                              //decreasing the value of semaphore
    }
  pthread_mutex_unlock(&(s->mutex));             
}        