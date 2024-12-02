#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Value
{
public:
    Value(int value) : _value(value) { }
    ~Value() { cout << "Value::~Value() " << _value << endl; }

    int get_value() const { return _value; }

private:
    int _value; 
};

class SPointer
{
public:
    typedef Value* Pointer;
    typedef Value& Reference;

    SPointer(Pointer value) : _value(value), _counter(new int(1)) { }
    SPointer(const SPointer& rhs) : _value(rhs._value), _counter(rhs._counter) {
        _toref(); 
    }
    SPointer& operator=(const SPointer& rhs) {
        if (&rhs == this) { return *this; }
        _unref();
     
        _value = rhs._value;
        _counter = rhs._counter;
        _toref();
    }
    ~SPointer() { _unref(); }

    Reference operator*() { return *_value; }
    Pointer operator->() { return _value; }
private:
    void _toref() { ++(*_counter); }
    void _unref() { 
        if (--(*_counter) == 0) {
            delete _value;
            delete _counter; 
            _value = nullptr;
            _counter = nullptr;
        }
    }

private:
    Pointer _value; 
    int* _counter; 
};

int main()
{
    {
        SPointer pointer1(new Value(3));
        SPointer pointer2 = pointer1;
        pointer2 = pointer1;
        pointer1 = pointer1;

        SPointer pointer3(new Value(4));
        cout << pointer3->get_value() << endl;
        cout << pointer2->get_value() << endl;
        pointer1 = pointer3;
        pointer2 = pointer3; 
        cout << "time to delete \"new Value(3)\" because all spointer point to \"new Value(4)\" in pointer3" << endl; 
    }
    system("PAUSE"); 
    return 0; 
}
