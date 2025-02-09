#include <iostream>
#include <thread>
#include <vector>

void module1_function() {
    std::cout << "Модуль 1: Привіт з модуля 1!" << std::endl;
}

void module2_function() {
    std::cout << "Модуль 2: Привіт з модуля 2!" << std::endl;
}

void threadFunction(int id) {
    std::cout << "Потік " << id << " запущено." << std::endl;
    if (id % 2 == 0)
        module1_function();
    else
        module2_function();
}

int main() {
    const int NUM_THREADS = 4;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(threadFunction, i);
    }
    for (auto &t : threads) {
        t.join();
    }

    std::cout << "Усі std::thread завершено." << std::endl;
    return 0;
}
