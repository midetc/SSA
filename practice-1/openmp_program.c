#include <stdio.h>
#include <omp.h>

// Функції, аналогічні модулям
void module1_function() {
    printf("Модуль 1: Привіт з модуля 1!\n");
}

void module2_function() {
    printf("Модуль 2: Привіт з модуля 2!\n");
}

int main() {
    // Задаємо кількість потоків (опційно)
    omp_set_num_threads(4);

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("OpenMP-потік %d запущено.\n", id);
        if (id % 2 == 0)
            module1_function();
        else
            module2_function();
    }

    printf("Усі OpenMP-потоки завершено.\n");
    return 0;
}
