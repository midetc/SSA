#include <stdio.h>
#include <pthread.h>

// Оголошення функцій з модулів
extern void module1_function();
extern void module2_function();

#define NUM_THREADS 4

void* thread_func(void* arg) {
    int id = *(int*)arg;
    printf("Потік %d запущено.\n", id);
    // В залежності від номера потоку викликаємо функцію з module1 або module2
    if (id % 2 == 0)
        module1_function();
    else
        module2_function();
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Усі потоки (pthread) завершено.\n");
    return 0;
}
