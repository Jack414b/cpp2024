#include <iostream>
#include <cassert>
//include the headers that you need here.

typedef struct
{
    int *elements;
    int size;
    int capacity;
} CArray;

void array_initial(CArray &array)
{
    array.size = 0;
    array.capacity = 0;
    array.elements = nullptr;
/*    array.elements = (int*)malloc(sizeof(int) * array.capacity);
    if(array.elements == nullptr){
        std::cerr << "Memory allocation failed" << std::endl;
    }
*/
}

inline int array_capacity(CArray &array)
{
    return array.capacity;
}

inline int array_size(CArray &array)
{
    return array.size;
}

void array_recap(CArray &array, int capacity)
{
    if(capacity < array.size){
        std::cerr << "Warning: capacity is too small!" << std::endl;
        return;
    }
    array.capacity = capacity;
    array.elements = (int*)realloc(array.elements, sizeof(int) * capacity);
    if(array.elements == nullptr){
        std::cerr << "Memory allocation failed" << std::endl;
        return;
    }
}

inline int &array_at(CArray &array, int index)
{
//    assert(index <= array.size && index >= 0);
    return array.elements[index];
}

void array_append(CArray &array, int element)
{
    if(array.size >= array.capacity){
        array_recap(array, array.capacity * 2);
    }
    array.elements[array.size++] = element;
}
void array_insert(CArray &array, int index, int element)
{
//   assert(index <= array.size && index >= 0);
    if(array.size >= array.capacity){
        array_recap(array, array.capacity * 2);
    }
    for(int i = array.size; i > index; --i){
        array.elements[i] = array.elements[i - 1];
    }
    array.elements[index] = element;
    array.size += 1;
}

void array_copy(CArray &src, CArray &dst)
{
    array_recap(dst, src.capacity);
    dst.capacity = src.capacity;
    dst.size = src.size;
    for(int i = 0; i < src.size; ++i){
        dst.elements[i] = src.elements[i];
    }

}

bool array_compare(CArray &array1, CArray &array2)
{
    if(array1.size != array2.size){
        return false;
    }
    for(int i = 0; i < array1.size; ++i){
        if(array1.elements[i] != array2.elements[i]){
            return false;
        }
    }
    return true;
}

void array_destroy(CArray &array)
{
    free(array.elements);
    array.elements = nullptr;
    array.size = 0;
    array.capacity = 0;
}

/*************************************************************************
*下面是一个给你们方便在本地端测试的main函数
*实际上，我们OJ的测试面函数并不是这样的
*所以如果你在你的本地端用这个main函数测试通过了，并不代表在OJ上能够通过
***********************************************************************/


int main(int argc, char *argv[])
{
    CArray array;
    array_initial(array);
    array_recap(array, 10);
    assert(array_capacity(array) == 10);
    //////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < 20; ++i)
    {
        array_append(array, i);
    }
    assert(array_size(array) == 20);
    for (int i = 0; i < array_size(array); ++i)
    {
        assert(array_at(array, i) == i);
    }
    //////////////////////////////////////////////////////////////////////////
    CArray array2, array3;
    array_initial(array2);
    array_initial(array3);
    array_copy(array, array2);
    assert(array_compare(array, array2) == true);
    array_copy(array, array3);
    assert(array_compare(array, array3) == true);
    //////////////////////////////////////////////////////////////////////////
    array_insert(array2, 2, 3);
    assert(array_compare(array, array2) == false);
    //////////////////////////////////////////////////////////////////////////
    array_at(array3, 2) = 5;
    assert(array_compare(array, array3) == false);
    //////////////////////////////////////////////////////////////////////////
    array_destroy(array);
    array_destroy(array2);
    array_destroy(array3);
    return 0;
}
