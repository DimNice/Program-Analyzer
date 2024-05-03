#include <iostream>
class A {
        public:
            void bar() {
                std::cout << "Test!\n";
            }
};

int main() {  //with
    A* a = 0;
    a->bar();
    return 0;
}