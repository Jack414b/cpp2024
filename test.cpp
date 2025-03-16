#include <iostream>

template <typename T>
class SmartPointer {
private:
    T* ptr;
    unsigned* ref_count;

public:
    // 构造函数
    explicit SmartPointer(T* p = nullptr) : ptr(p), ref_count(new unsigned(1)) {
        std::cout << "SmartPointer created. Ref count: " << *ref_count << std::endl;
    }

    // 拷贝构造函数
    SmartPointer(const SmartPointer<T>& sp) : ptr(sp.ptr), ref_count(sp.ref_count) {
        ++(*ref_count);
        std::cout << "SmartPointer copied. Ref count: " << *ref_count << std::endl;
    }

    // 赋值运算符重载
    SmartPointer<T>& operator=(const SmartPointer<T>& sp) {
        if (this != &sp) {
            // 先减少当前对象的引用计数
            if (--(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
                std::cout << "SmartPointer destroyed." << std::endl;
            }

            // 复制新的对象
            ptr = sp.ptr;
            ref_count = sp.ref_count;
            ++(*ref_count);
            std::cout << "SmartPointer assigned. Ref count: " << *ref_count << std::endl;
        }
        return *this;
    }

    // 析构函数
    ~SmartPointer() {
        if (--(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
            std::cout << "SmartPointer destroyed." << std::endl;
        }
    }

    // 重载 * 操作符
    T& operator*() {
        return *ptr;
    }

    // 重载 -> 操作符
    T* operator->() {
        return ptr;
    }

    // 重载 ++ 操作符（前置）
    SmartPointer<T>& operator++() {
        ++(*ptr);
        return *this;
    }

    // 重载 ++ 操作符（后置）
    SmartPointer<T> operator++(int) {
        SmartPointer<T> temp = *this;
        ++(*ptr);
        return temp;
    }
};

// 测试代码
int main() {
    SmartPointer<int> sp1(new int(10));
    SmartPointer<int> sp2 = sp1;

    std::cout << "Value: " << *sp1 << std::endl;
    ++sp1;
    std::cout << "Value after increment: " << *sp1 << std::endl;

    return 0;
}


