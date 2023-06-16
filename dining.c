#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5 // Number of philosophers

sem_t chopstick[N];

void *philosopher(void *arg) {
 int i = *(int *)arg;
 int left = i;
 int right = (i + 1) % N;

 while (1) {
   // Philosopher thinks for a random amount of time
   printf("Philosopher %d is thinking\n", i);
   sleep(rand() % 10);

   // Philosopher is hungry and tries to pick up chopsticks
   printf("Philosopher %d is hungry\n", i);

   // Wait for the left chopstick
   sem_wait(&chopstick[left]);
   printf("Philosopher %d picked up chopstick %d\n", i, left);

   // Wait for the right chopstick
   sem_wait(&chopstick[right]);
   printf("Philosopher %d picked up chopstick %d\n", i, right);

   // Philosopher eats for a random amount of time
   printf("Philosopher %d is eating\n", i);
   sleep(rand() % 10);

   // Philosopher puts down chopsticks
   sem_post(&chopstick[left]);
   printf("Philosopher %d put down chopstick %d\n", i, left);

   sem_post(&chopstick[right]);
   printf("Philosopher %d put down chopstick %d\n", i, right);
 }
}

int main() {
 pthread_t tid[N];
 int i;

 // Initialize semaphores
 for (i = 0; i < N; i++) {
   sem_init(&chopstick[i], 0, 1);
 }

 // Create philosopher threads
 for (i = 0; i < N; i++) {
   int *arg = malloc(sizeof(*arg));
   *arg = i;
   pthread_create(&tid[i], NULL, philosopher, arg);
 }

 // Wait for philosopher threads to finish
 for (i = 0; i < N; i++) {
   pthread_join(tid[i], NULL);
 }

 // Destroy semaphores
 for (i = 0; i < N; i++) {
   sem_destroy(&chopstick[i]);
 }

 return 0;
}



