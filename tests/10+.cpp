// !test race_condition
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void* incrementCounter(void*) {
    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, incrementCounter, NULL); // Первый поток увеличивает счетчик
    pthread_create(&t2, NULL, incrementCounter, NULL); // Второй поток также увеличивает счетчик

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    std::cout << "Значение счетчика: " << counter << std::endl; // Выводим значение счетчика

    pthread_cancel(t1);
    pthread_cancel(t2);

    return 0;
}