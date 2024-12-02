#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int function(int a, int b){
    return a + b;
}

class Adaptor {
    typedef int (* FuncPtr)(int a, int b);
    FuncPtr _ptr;
    int _param;
public:
    Adaptor(FuncPtr p, int pa) : _ptr(p), _param(pa) {};

    int operator ()(int b) {
        return _ptr(_param,b);
    }
};

int main(){
    Adaptor adaptor(function, 3);
    cout << adaptor(4) << endl;
    cout << function(3, 4) << endl;
    return 0;
}


