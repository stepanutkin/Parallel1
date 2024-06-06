#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

void clientThread(std::atomic<int>& clientsCounter, int maxClients) {
    while (clientsCounter < maxClients) {
        clientsCounter++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void operatorThread(std::atomic<int>& clientsCounter) {
    while (clientsCounter > 0) {
        clientsCounter--;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    int maxClients = 10;  // Максимальное количество клиентов
    std::atomic<int> clientsCounter(0);

    std::thread clientThreadObj(clientThread, std::ref(clientsCounter), maxClients);
    std::thread operatorThreadObj(operatorThread, std::ref(clientsCounter));

    clientThreadObj.join();
    operatorThreadObj.join();

    std::cout << "All clients are served" << std::endl;

    return 0;
}