#include<iostream>
#include<assert.h>
#include<cstring>
//include the headers that you need here.
#include <memory.h>

class CArray
{
public:
    typedef int Element;

public:
    CArray();
    ~CArray();

    int capacity() const;
    int size() const;

    void recap(int capacity);

    Element &at(int index);
    Element at(int index) const;

    void append(Element element);
    void insert(int index, Element element);

    void copy(const CArray &rhs);
    bool compare(const CArray &rhs) const;

private:
    /*data*/
    Element* data;
    int _size;
    int _cap;
};

    CArray::CArray() : data(NULL), _size(0), _cap(0) {};

    CArray::~CArray(){
        delete[] data;
        data = NULL;
        _size = 0;
        _cap = 0;
    };

    int CArray::capacity() const {
        return _cap;
    };
    
    int CArray::size() const{
        return _size;
    };

    void CArray::recap(int capacity){
        if(_cap == capacity){
            return;
        }
        
        Element* newdata = new Element[capacity];
        _size = _cap < _size ? _cap : _size;
        memcpy(newdata, data, _size * sizeof(Element));
        delete[] data;
        _cap = capacity;
        data = newdata;
        
    };

    CArray::Element& CArray::at(int index){
        return data[index];
    };
    CArray::Element CArray::at(int index) const{
        return data[index];
    };

    void CArray::append(Element element){
        if(_size >= _cap){
            recap(_size + 1);
        }
        data[_size++] = element;
    };

    void CArray::insert(int index, Element element){
        if(_size >= _cap){
            recap(_cap == 0 ? 1 : 2 * _cap );
        }
        for(int i = _size; i > index; --i){
            data[i] = data[i - 1];
        }
        data[index] = element;
        _size++;
    };

    void CArray::copy(const CArray &rhs){
        recap(rhs._cap);
        _size = rhs._size;
        memcpy(data, rhs.data, _size * sizeof(Element));
    };

    bool CArray::compare(const CArray &rhs) const {
        if(_size != rhs._size) return false;
        return memcmp(data, rhs.data, _size * sizeof(Element)) == 0;
    };

int main(int argc, char *argv[])
{
    CArray array;
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
    CArray array2, array3;
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
    // 不再需要destroy，但应该有正确的内存释放
    // array_destroy(array);
    // array_destroy(array2);
    // array_destroy(array3);
	return 0;
}
