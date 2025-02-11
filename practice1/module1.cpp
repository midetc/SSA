#include <iostream>
#include <thread>
#include <vector>

void module1_function() {
    auto worker = [](int id) {
        std::cout << "Module1 (std::thread): Привіт від потоку " << id << std::endl;
    };

    const int numThreads = 4;
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, i);
    }
    for (auto& t : threads) {
        t.join();
    }
}
