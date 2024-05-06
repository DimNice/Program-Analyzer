// !test race_condition
#include <iostream>
#include <thread>
using namespace std;

int counter = 0;

void* incrementCounter(void*) {
    counter++;
    return NULL;
}

int main() {

    pthread_create(&t1, NULL, incrementCounter, NULL); // Первый поток увеличивает счетчик
    pthread_create(&t2, NULL, incrementCounter, NULL); // Второй поток также увеличивает счетчик

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    std::cout << "Значение счетчика: " << counter << std::endl; // Выводим значение счетчика

    pthread_cancel(t1);
    pthread_cancel(t2);

    return 0;
}