#include <iostream>
using namespace std;

int foo(const char* cptr, unsigned int len) {
    for (int i = 0; i < len; i++) {
        const char a = *cptr;
        cout << a;
        cptr++;
    }
    return 0;
}

#define size 10

int yum(const char thing[size]) {
    for (int i = 0; i < size; i++) {
        // If we have a null character (see ascii table)
        if (thing[i] == 0) {
            break;
        }
        cout << thing[i];
    }
    return 0;
}

int main(void) {
    foo("hello", 5);

    yum(", world!");

    cout << endl;
}
