#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

void module2_function() {
    auto readFile = []() {
        std::ifstream file("data.txt");
        if (!file) {
            std::cerr << "Module2 (std::thread): Не вдалося відкрити файл data.txt" << std::endl;
            return;
        }
        std::string line;
        std::cout << "Module2 (std::thread): Асинхронне читання файлу:" << std::endl;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };

    std::thread ioThread(readFile);
    ioThread.join();
}
