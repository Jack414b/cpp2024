#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const int SIZE = 100;

class Stack{
    int top;
    int buffer[SIZE];
    //int x = 0;
public:
    Stack() : top(-1){}

    bool push(int i){
        if(top >= SIZE - 1){
            cout << "overFlow!" << endl;
            return false;
        }
        buffer[++top] = i;
        return true;
    }

    bool pop(int &i){
        if(top < 0){
            cout << "underflow!" << endl;
            return false;
        }
        i = buffer[top--];
        return true;
    }

    ~Stack(){}
};

int main(){
    Stack obj;

    for(int i = 0; i < 5; i++){
        obj.push(i);
    }

    int value;
    while(obj.pop(value)){
        cout << "Popped value:" << value << endl;
    }
    return 0;
}


