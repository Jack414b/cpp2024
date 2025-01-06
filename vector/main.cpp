//include the headers that you need here.
#include <iostream>
#include <assert.h>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename T>
class CArrayIterator;

template <typename T>
class CArrayConstIterator;

template <typename T>
class CArray
{
public:
    typedef T Element;
    typedef CArrayIterator<T> Iterator;
    typedef CArrayConstIterator<T> ConstIterator;

public:
    CArray() : _buff(nullptr), _size(0), _cap(0){}
    CArray(const CArray &rhs) : _size(rhs._size), _cap(rhs._cap){
        _buff = new Element[_size]();
        std::copy(rhs._buff, rhs._buff + _size, _buff);
    }
    ~CArray() {
        delete[] _buff;
        _buff = nullptr;
    }

public:
    int capacity() const
    {
        return _cap;
    }
    int size() const
    {
        return _size;
    }

    void recap(int cap){
        if(cap <= 0 || cap == _cap){
            return;
        }
        int new_size = (_size > cap) ? cap : _size;
        Element* newx = new Element[cap];

        if(newx) {
            std::copy(_buff, _buff + new_size, newx);
            delete[] _buff;
            _buff = newx;
            _cap = cap;
            _size = new_size;
        }
    }

    Element &at(int index)
    {
        return _buff[index];
    }
    Element at(int index) const
    {
        return _buff[index];
    }

    Iterator begin(){
        return Iterator(_buff);
    }

    Iterator end(){
        return Iterator(_buff + _size);
    }

    ConstIterator begin() const{
        return ConstIterator(_buff);
    }

    ConstIterator end() const{
        return ConstIterator(_buff + _size);
    }

    void append(Element element){
        _check_capacity(_size + 1);
        _buff[_size++] = element;   
    }
    void insert(int index, Element element){
        if(index < 0 || index > _size){
            return;
        }
        _check_capacity(_size + 1);
        for(int i = _size; i > index; --i){
            _buff[i] = _buff[i - 1];
        }
        _buff[index] = element;
        ++_size;
    }

    void copy(const CArray &rhs){
        if(this == &rhs){
            return;
        }
        if(_cap < rhs._size){
            recap(rhs._size);
        }
        _size = rhs._size;
        std::copy(rhs._buff, rhs._buff + _size, _buff);
    }
    bool compare(const CArray &rhs) const{
        if(_size != rhs._size){
            return false;
        }
        for(int i = 0; i < _size; ++i){
            if(_buff[i] != rhs._buff[i]){
                return false;
            }
        }
        return true;
    }

private:
    void _check_capacity(int minimal){
        if(minimal > _cap){
            int new_cap = _cap * 2;
            if(new_cap < minimal){
                new_cap = minimal;
            }
            recap(new_cap);
        }
    }
    Element *_buff;
    int _size;
    int _cap;
};

template <typename T>
class CArrayIterator : public iterator<std::random_access_iterator_tag, T>
{

public:
    CArrayIterator() {}
    CArrayIterator(T *current){
        _current = current;
    }
    CArrayIterator(const CArrayIterator &rhs){
        _current = rhs._current;
    }
    ~CArrayIterator() {}

public:
    //实现所需要的操作符重载函数
    CArrayIterator &operator++(){
        ++_current;
        return *this;
    }

    CArrayIterator operator++(int){
        CArrayIterator tmp(*this);
        ++_current;
        return tmp;
    }

    T& operator*(){
        return *_current;
    }

    T* operator->(){
        return _current;
    }

    bool operator==(const CArrayIterator &rhs){
        return _current == rhs._current;
    }

    bool operator!=(const CArrayIterator &rhs){
        return _current != rhs._current;
    }

protected:
    T *_current;
    friend class CArray<T>;
};

template <class T>
class CArrayConstIterator : public iterator<input_iterator_tag, T>
{
public:
    CArrayConstIterator() {}
    CArrayConstIterator(T *current){
        _current = current;
    }
    CArrayConstIterator(const CArrayConstIterator &rhs){
        _current = rhs._current;
    };
    ~CArrayConstIterator() {}

public:
    //实现所需要的操作符重载函数
    CArrayConstIterator &operator++(){
        ++_current;
        return *this;
    }

    CArrayConstIterator operator++(int){
        CArrayConstIterator tmp(*this);
        ++_current;
        return tmp;
    }

    const T& operator*(){
        return *_current;
    }

    const T* operator->(){
        return _current;
    }

    bool operator==(const CArrayConstIterator &rhs){
        return _current == rhs._current;
    }

    bool operator!=(const CArrayConstIterator &rhs){
        return _current != rhs._current;
    }

protected:
    T *_current;
    friend class CArray<T>;
};
/*******************************************************
* 本地端调试代码样例
********************************************************/

#if 1
template <typename T>
class Obj
{
public:
    Obj(){};
    Obj(int val) : data(val){};
    ~Obj(){};

public:
    T data;

private:
    template <typename Tp>
    friend std::ostream &operator<<(std::ostream &os, const Obj<Tp> &obj);
};

template <typename Tp>
std::ostream &operator<<(std::ostream &os, const Obj<Tp> &obj)
{
    os << obj.data;
    return os;
}

int main(int argc, char const *argv[])
{
    CArray<int> array;
    // 不再需要initial，但应该有正确的初始化
    // array_initial(array);
    array.recap(10);
    assert(array.capacity() == 10);
    //////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < 20; ++i)
    {
        array.append(i);
    }
    assert(array.size() == 20);
    for (int i = 0; i < array.size(); ++i)
    {
        assert(array.at(i) == i);
    }
    //////////////////////////////////////////////////////////////////////////
    CArray<int> array2, array3;
    // array_initial(array2);
    // array_initial(array3);
    array2.copy(array);
    assert(array.compare(array2) == true);
    array3.copy(array);
    assert(array.compare(array3) == true);
    //////////////////////////////////////////////////////////////////////////
    array2.insert(2, 3);
    assert(array.compare(array2) == false);
    //////////////////////////////////////////////////////////////////////////
    array3.at(2) = 5;
    assert(array.compare(array3) == false);
    //////////////////////////////////////////////////////////////////////////
	for (CArray<int>::Iterator it = array.begin(); it != array.end(); ++it)
    {
        std::cout << *it << " ";
        (*it) = (*it) + 10;
    }
    std::cout << std::endl;
    for (CArray<int>::Iterator it = array.begin(); it != array.end();)
    {
        std::cout << *(it++) << " ";
    }
    std::cout << std::endl;
    const CArray<int> tmp(array);

    for (CArray<int>::ConstIterator it = tmp.begin(); it != tmp.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    CArray<Obj<int>> obj_arr;
    for (CArray<int>::ConstIterator it = tmp.begin(); it != tmp.end();)
    {
        obj_arr.append(Obj<int>(*it));
        std::cout << *(it++) << " ";
    }
    std::cout << std::endl;
    for (CArray<Obj<int>>::Iterator it = obj_arr.begin(); it != obj_arr.end(); ++it)
    {
        std::cout << (*it) << " ";
    }
    std::cout << std::endl;
    for (CArray<Obj<int>>::Iterator it = obj_arr.begin(); it != obj_arr.end(); ++it)
    {
        std::cout << it->data << " ";
    }
    std::cout << std::endl;
    return 0;
}
#endif