#include <stdio.h>

void module1_function();
void module2_function();

int main() {
    printf("Запуск C-програми з OpenMP та асинхронним I/O...\n");

    module1_function();
    module2_function();

    printf("C-програма завершена.\n");
    return 0;
}
