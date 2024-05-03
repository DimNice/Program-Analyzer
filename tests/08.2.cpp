// !test null_pointer_derefence

#include <iostream>  // without
class Test
{
    public:
        int a;
        int b;
        void printData(){
            cout << a << ", " << b << endl;
        }
        int setA(){
            return a;
        }
};

int main()
{
        Test * tst = new Test();
        if (tst != nullptr) {
            tst->printData();
            delete tst;
        }
        cout << "Hello, world!" << endl;
        return 0;
}