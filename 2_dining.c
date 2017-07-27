#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t philosopher[5];
pthread_mutex_t Stick[5];

void *func(int n)
   {
   printf ("Philosopher %d is thinking\n",n);

   pthread_mutex_lock(&Stick[n]);
   pthread_mutex_lock(&Stick[(n+1)%5]);
   printf ("Philosopher %d is eating\n",n);
   sleep(3);
   pthread_mutex_unlock(&Stick[n]);
   pthread_mutex_unlock(&Stick[(n+1)%5]);

   printf ("Philosopher %d finished eating\n",n);

   return(NULL);
   }

int main()
   {
   int i;
   for(i=0;i<5;i++)
      pthread_mutex_init(&Stick[i],NULL);

   for(i=0;i<5;i++)
      pthread_create(&philosopher[i],NULL,(void *)func,(void *)i);

   for(i=0;i<5;i++)
      pthread_join(philosopher[i],NULL);

   for(i=0;i<5;i++)
      pthread_mutex_destroy(&Stick[i]);

   return 0;
   }