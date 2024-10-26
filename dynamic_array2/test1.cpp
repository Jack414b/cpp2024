//include the headers that you need here.
#include <memory.h>
#include <iostream>
#include <assert.h>
#include <cstring>

class CArray
{
public:
    typedef int Element;

public:
    CArray()
    {
        _size = 0;
        _cap = 0;
        _x = NULL;
    }
    ~CArray()
    {
        delete[] _x;
        _x = NULL;            
        _size = 0;
        _cap = 0;
    }

    int capacity() const
    {
        return _cap;
    }
    int size() const
    {
        return _size;
    }

    void recap(int capacity)
    {       
        int i;
        int new_cap, size;
        new_cap = capacity;
        
        size = _size;
    
        if(_cap == capacity){
            return;
        }
        
        int* newx = new int[new_cap]; 
        if (newx != NULL){
                if (size > new_cap)
                {
                    size = new_cap;
                }
                for (i = 0; i < size; ++i)
                {
                    newx[i] = _x[i];
                }
                delete[] _x;
                _cap = new_cap;
                _x = newx;
                _size = size;
        }
        

    }

    Element& at(int index)
    {
        return _x[index];
    }
    Element at(int index) const
    {
        return _x[index];
    }

    void append(Element element)
    {
        int size = _size;
        int cap = _cap;
        if (_size >= _cap)
        {
            recap(cap + 1);
        }
        _x[_size] = element;
        _size++;
    }
    void insert(int index, Element element)
    {
        int i, size;
        size = _size;
        if (index >= 0)
        {
            if (_size >= _cap)
            {
                recap(_cap + 1);
            }

            if (index < size)
            {
                for (i = size; i > index; --i)
                {
                    _x[i] = _x[i - 1];
                }
                _x[index] = element;
            }
            else
            {
                _x[index] = element;
            }
            _size++;
        }
    }

    void copy(const CArray& rhs)
    {
        int size, i;
        size = rhs._size;

        if (this->_cap != rhs._cap)
        {
            recap(rhs._cap);
        }
        this->_size = rhs._size;
        this->_cap = rhs._cap;
        for (i = 0; i < size; ++i)
        {
            this->_x[i] = rhs._x[i];
        }

    }
    bool compare(const CArray& rhs) const
    {
        int i;
       
        if (this->_size != rhs._size)
        {
            return false;
        }
        else
        {
            for (i = 0; i < rhs._size; ++i)
            {
                if (this->_x[i] != rhs._x[i])
                {
                    return false;
                }
            }
        }
        return true;
        
    }

private:
    int* _x;
    int _cap;
    int _size;
    /*data*/
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


