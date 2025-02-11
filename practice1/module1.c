#include <stdio.h>
#include <omp.h>

void module1_function() {
    int i;
    #pragma omp parallel for
    for (i = 0; i < 4; i++) {
        int thread_id = omp_get_thread_num();
        printf("Module1 (OpenMP): Привіт від потоку %d, ітерація %d\n", thread_id, i);
    }
}
