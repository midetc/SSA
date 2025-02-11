#include <iostream>
#include <thread>

void module1_function();
void module2_function();

int main() {
    std::cout << "Запуск C++ програми з std::thread...\n";

    std::thread t1(module1_function);
    std::thread t2(module2_function);

    t1.join();
    t2.join();

    std::cout << "C++ програма завершена.\n";
    return 0;
}
