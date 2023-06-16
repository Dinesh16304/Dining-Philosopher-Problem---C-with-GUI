#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <gtk/gtk.h>
#include<stdlib.h>
#include <unistd.h>


int N = 10; // Number of philosophers

sem_t chopstick[10];
int count = 0;

void *philosopher(void *arg) {
int i = *(int *)arg;
int left = i;
int right = (i + 1) % N;

while (count++ < 50) {
  // Philosopher thinks for a random amount of time
  printf("Philosopher %d is thinking\n", i);
  sleep(2);
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
  sleep(2);
  // Philosopher puts down chopsticks
  sem_post(&chopstick[left]);
  printf("Philosopher %d put down chopstick %d\n", i, left);
  sem_post(&chopstick[right]);
  printf("Philosopher %d put down chopstick %d\n", i, right);
}
}












static void on_button_clicked(GtkWidget *widget, gpointer data) {
   // Get the number of trains from the user
   N = atoi(gtk_entry_get_text(GTK_ENTRY(data))); pthread_t tid[N];
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




}




















int main(int argc, char* argv[]) {
   GtkWidget *window;
   GtkWidget *grid;
   GtkWidget *label;
   GtkWidget *entry;
   GtkWidget *button;




   gtk_init(&argc, &argv);




   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "Dining philosopher problem");
   gtk_container_set_border_width(GTK_CONTAINER(window), 10);
   gtk_widget_set_size_request(window, 300, 100);




   grid = gtk_grid_new();
   gtk_container_add(GTK_CONTAINER(window), grid);




   label = gtk_label_new("Enter number of philosophers:");
   gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);




   entry = gtk_entry_new();
   gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);




   button = gtk_button_new_with_label("Start");
   g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);
   gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);




   g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);




   gtk_widget_show_all(window);




   gtk_main();




   return 0;
}







gcc dining.c -o dinning `pkg-config --cflags --libs gtk+-3.0`

