#include <iostream>
using namespace std;

#include <stdint.h>

int main(void) {
    cout << "int    = " << sizeof(int) << " bytes" << endl;
    cout << "long   = " << sizeof(long) << " bytes" << endl;
    cout << "char   = " << sizeof(char) << " bytes" << endl;
    cout << "float  = " << sizeof(float) << " bytes" << endl;
    cout << "double = " << sizeof(double) << " bytes" << endl;
    
    cout << endl;
    
    cout << "uint8_t = " << sizeof(uint8_t) << " bytes" << endl;
    cout << "uint16_t = " << sizeof(uint16_t) << " bytes" << endl;
    cout << "uint32_t = " << sizeof(uint32_t) << " bytes" << endl;
    cout << "uint64_t = " << sizeof(uint64_t) << " bytes" << endl;

    unsigned char a; // this does actually work haha
    
    return 0;
}
