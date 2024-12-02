#include <iostream>
#include <vector>
#include <assert.h>

class Vector
{
public:
    typedef std::vector<double> Data;
    static Vector INVALID_VECTOR;

public:


    Vector() {}
    Vector(int length, const double data[]){
    _data.resize(length);
    for (int idx = 0; idx < length; ++idx)
    {
        _data[idx] = data[idx];
    }
    }
    Vector(int length, const double data){
        _data.resize(length);
        for (int idx = 0; idx < length; ++idx){
        _data[idx] = data;
        }
    };

    ~Vector()
    {
        _data.clear();
    }

    void resize(int length)
    {
        _data.resize(length);
    }

    int size() const { return _data.size(); }

    double &operator[](int idx) { return _data[idx]; }
    double operator[](int idx) const { return _data[idx]; }

    const Vector &operator=(const Vector &rhs){
        _data = rhs._data;

        return *this;
    }

    const Vector &operator=(double rhs){
        for (int idx = 0; idx < size(); ++idx){
            _data[idx] = rhs;
        }

        return *this;
    }

    Vector operator-() const{
        Vector result(*this);
        for (Data::size_type idx = 0; idx < _data.size(); ++idx){
            result[idx] = -_data[idx];
        }

        return result;
    }

    Vector operator+(const Vector &rhs) const{
        if (size() != rhs.size()){
            return INVALID_VECTOR;
        }

        Vector result(*this);
        for (Data::size_type idx = 0; idx < _data.size(); ++idx){
            result[idx] = _data[idx] + rhs[idx];
        }

        return result;
    }

    Vector operator+(double rhs) const
    {
        return *this + Vector(size(), rhs);
    }

    Vector operator-(const Vector &rhs) const
    {
        return *this + (-rhs);
    }
    Vector operator-(double rhs) const
    {
        return *this - Vector(size(), rhs);
    }

    Vector operator*(double rhs) const{
        Vector temp = *this;

        for (int idx = 0; idx < size(); ++idx){
            temp[idx] *= rhs;
        }

        return temp;
    }

    bool operator==(const Vector &rhs) const{
        if (rhs.size() != size()){
            return false;
        }

        for (int idx = 0; idx < size(); ++idx){
            if (rhs[idx] != _data[idx]){
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector &rhs) const
    {
        return !(rhs == *this);
    }

private:
    Data _data;

    friend std::ostream &operator<<(std::ostream &os, const Vector &vector);
};

std::ostream &operator<<(std::ostream &os, const Vector &vector);

Vector Vector::INVALID_VECTOR;

std::ostream &operator<<(std::ostream &os, const Vector &vector)
{
    std::cout << "vector (1 X " << vector.size() << "): " << std::endl;
    for (int idx = 0; idx < vector.size(); ++idx)
    {
        os << vector[idx] << " ";
    }

    return os;
}

class Matrix
{
public:
    /// 定义类型便于其他代码使用
    typedef std::vector<Vector> Data;

    /// 定义非法矩阵，这里用0 * 0矩阵表示，也可在Matrix中添加一个特殊标志位
    static Matrix INVALID_MATRIX;

public:
    // Matrix类构造函数.
    /// 默认构造函数要加，否则vector无法resize
    Matrix() {}

    Matrix(const Vector &rhs);

    Matrix(int row, int col);

    Matrix(int row, int col, const double data[]);

    Matrix(int row, int col, const double data);

    Matrix(const Matrix &rhs) : _data(rhs._data) {}

    // Matrix类析构函数
    ~Matrix()
    {
        /// 养成习惯，析构时清空
        _data.clear();
    }

    // Matrix类接口.
public:
    // Matrix类赋值函数
    const Matrix &operator=(const Matrix &rhs);
    const Matrix &operator=(const Vector &rhs);

    int rows() const
    {
        return _data.size();
    }

    int cols() const
    {
        if (_data.empty())
        {
            return 0;
        }

        return _data[0].size();
    }

    Matrix trans() const;

    Vector &operator[](int row)
    {
        return _data[row];
    }

    const Vector &operator[](int row) const
    {
        return _data[row];
    }

    
    Matrix operator-() const;

    Matrix operator*(const Matrix &rhs) const;
    Matrix operator*(double rhs) const;

    Matrix operator+(const Matrix &rhs) const;
    Matrix operator+(double rhs) const
    {
        return *this + Matrix(rows(), cols(), rhs);
    }

    Matrix operator-(const Matrix &rhs) const
    {
        return *this + (-rhs);
    }

    Matrix operator-(double rhs) const
    {
        return *this - Matrix(rows(), cols(), rhs);
    }


    bool operator==(const Matrix &rhs) const{
        if (rows() != rhs.rows() || cols() != rhs.cols()){
            return false;
        }
        for (int row = 0; row < rows(); ++row){
            for (int col = 0; col < rhs.cols(); ++col){
                if (_data[row][col] != rhs._data[row][col]){
                return false;
                }
            }
        }

        return true;
    }

    bool operator==(const Vector &rhs) const{
    if (_data.size() != 1)
    {
        return false;
    }

    return operator[](0) == rhs;
    }

    bool operator!=(const Matrix &rhs) const
    {
        return !(*this == rhs);
    }

    bool operator!=(const Vector &rhs) const
    {
        return !(*this == rhs);
    }

    // Matrix类私有实现方法
private:
    // Matrix类私有属性
private:
    /// 所有成员函数应设为私有
    Data _data;

    /// operator<<需加友元声明，否则无法打印
    friend std::ostream &operator<<(std::ostream &out, const Matrix &rhs);
}; // class Matrix类定义结束.

/// 定义Matrix流输出操作
std::ostream &operator<<(std::ostream &out, const Matrix &rhs);

Matrix Matrix::INVALID_MATRIX;

Matrix::Matrix(const Vector &rhs)
{
    *this = rhs;
}

Matrix::Matrix(int rows, int cols)
{
    _data.resize(rows);
    for (int r = 0; r < rows; ++r)
    {
        _data[r].resize(cols);
    }
}

Matrix::Matrix(int rows, int cols, const double data[])
{
    _data.resize(rows);
    for (int r = 0; r < rows; ++r)
    {
        _data[r].resize(cols);

        for (int c = 0; c < cols; ++c)
            _data[r][c] = data[r * cols + c];
    }
}

Matrix::Matrix(int rows, int cols, const double data)
{
    _data.resize(rows);

    for (int r = 0; r < rows; ++r)
    {
        _data[r].resize(cols);

        for (int c = 0; c < cols; ++c)
            _data[r][c] = data;
    }
}

Matrix Matrix::trans() const
{
    Matrix temp(cols(), rows());

    for (int r = 0; r < rows(); ++r)
    {
        for (int c = 0; c < cols(); ++c)
        {
            temp[c][r] = _data[r][c];
        }
    }

    return temp;
}

// Matrix类赋值函数
const Matrix &Matrix::operator=(const Matrix &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    _data = rhs._data;
    return *this;
}

const Matrix &Matrix::operator=(const Vector &rhs)
{
    _data.resize(1);
    _data[0] = rhs;

    return *this;
}

Matrix Matrix::operator-() const
{
    Matrix temp(rows(), cols());
    for (int row = 0; row < rows(); ++row)
    {
        for (int col = 0; col < cols(); ++col)
        {
            temp[row][col] = -_data[row][col];
        }
    }

    return temp;
}

Matrix Matrix::operator*(const Matrix &rhs) const
{
    if (cols() != rhs.rows())
    {
        return Matrix::INVALID_MATRIX;
    }

    Matrix temp(rows(), rhs.cols());
    for (int row = 0; row < rows(); ++row)
    {
        for (int col = 0; col < rhs.cols(); ++col)
        {
            double result = 0;
            for (int mul = 0; mul < cols(); ++mul)
            {
                result += _data[row][mul] * rhs._data[mul][col];
            }
            temp._data[row][col] = result;
        }
    }

    return temp;
}

Matrix Matrix::operator*(double rhs) const
{
    Matrix temp = *this;

    for (int r = 0; r < rows(); ++r)
    {
        for (int c = 0; c < cols(); ++c)
        {
            temp[r][c] *= rhs;
        }
    }

    return temp;
}

Matrix Matrix::operator+(const Matrix &rhs) const
{
    if (rows() != rhs.rows() || cols() != cols())
    {
        return Matrix::INVALID_MATRIX;
    }

    Matrix temp(rows(), cols());
    for (int row = 0; row < rows(); ++row)
    {
        for (int col = 0; col < rhs.cols(); ++col)
        {
            temp[row][col] = _data[row][col] + rhs[row][col];
        }
    }

    return temp;
}


/// 定义Matrix流输出操作
std::ostream &operator<<(std::ostream &out, const Matrix &rhs)
{
    out << "---------------------------------------------------" << std::endl;
    out << "(" << rhs.rows() << "x" << rhs.cols() << ") Matrix: " << std::endl;
    for (int row = 0; row < rhs.rows(); ++row)
    {
        for (int col = 0; col < rhs.cols(); ++col)
        {
            out << rhs._data[row][col] << "\t";
        }
        out << std::endl;
    }
    out << "===================================================" << std::endl;

    return out;
}



// 提供的测试代码
// 该测试用例中涉及的Vector及Matrix自行设计，逐渐熟悉并掌握类接口设计能力
// 建议可以先注释掉全部或大部分测试代码，从而以免在一开始因代码仅完成很少部分，产生太多编译错误
// 仅通过测试代码分析类的职责，开发完成后，放开测试代码
// 测试不通过，在考虑职责分析是否有误解
// 建议思考的方式为“我应该为Vector和Matrix提供什么接口，这些接口应当完成什么功能以满足他们的职责”为出发点，实现后通过测试用例验证
// 而非“我应该为Vector和Matrix提供什么接口，以能通过测试代码”为出发点，通不过一句，改一个函数，通过一句，就转移到下一个函数的方式
// 前者以对象为中心，考虑职责，在思考过程和实现过程中，类独立设计并实现，最终通过交互完成功能，类设计和实现的过程和测试代码的顺序无关，
// 仅与自身从测试代码中分析并融合出的职责需求有关
// 后者以过程为中心，考虑功能，思考过程和实现的过程中，类在不断的“测试过程”中运行，以测试代码运行的顺序增加功能

int main(int argc, char *argv[])
{
    // 通过传递元素素组初始化向量，最终将得到3个元素
    double data1[] = {3.4, 4.4, 6.0};
    Vector v(sizeof(data1) / sizeof(double), data1);

    // 确保完备的初始化向量
    assert(v.size() == sizeof(data1) / sizeof(double));
    for (int idx = 0; idx < sizeof(data1) / sizeof(double); ++idx)
    {
        assert(v[idx] == data1[idx]);
    }

    // v的值应等于自身，且不会不等于自身
    assert(v == v);
    assert(!(v != v));

    // v + v按元素分别求和的结果，相当于每个元素直接与2相乘
    assert(v + v == v * 2);

    // v - v按元素分别求和的结果，相当于v加上v的相反数
    assert(v - v == v + (-v));

    // v = 3的结果使向量的每个元素都变为3，因此等于直接初始化一个只有三个元素，且初始值为3的向量
    assert((v = 3) == Vector(sizeof(data1) / sizeof(double), 3));

    // v + 3的结果使向量的每个元素都加上3，因此等于直接初始化一个只有三个元素，且初始值为6的向量
    // 而 v - 3则直接初始化一个只有三个元素，且初始值为0的向量
    assert(v + 3 == Vector(sizeof(data1) / sizeof(double), 6));
    assert(v - 3 == Vector(sizeof(data1) / sizeof(double), 0.0));

    // 另行定义一个有十个元素，且每个元素值为5的向量
    Vector v2(10, 5);

    // 确保其正确初始化
    assert(v2.size() == 10);
    for (int idx = 0; idx < v2.size(); ++idx)
    {
        assert(v2[idx] == 5);
    }

    // 两个元素个数不相等的向量相加，其结果为【无效向量】
    assert(v + v2 == Vector::INVALID_VECTOR);

    //////////////////////////////////////////////////
    // 通过传递元素素组初始化矩阵，3( 行) X 2(列) 矩阵为：
    // 1 1
    // 1 1
    // 1 1
    double data2[] = {1, 1, 1, 1, 1, 1};
    Matrix m1(3, 2, data2);

    // m4等于m1乘以标量2，因此按元素分别求乘积，得到3( 行) X 2(列) 矩阵，为：
    // 2 2
    // 2 2
    // 2 2
    Matrix m4 = m1 * 2;

    // 确保m1初始化正确，且与标量乘积正确
    assert(m4.rows() == 3);
    assert(m4.cols() == 2);
    for (int r = 0; r < 2; ++r)
    {
        for (int c = 0; c < 2; ++c)
        {
            assert(m4[r][c] == 2);
        }
    }

    // 以同样的数组初始化矩阵，但如果行数、列数不同，获得的矩阵也不同
    Matrix m2(6, 1, data2);
    Matrix m3(3, 2, data2);

    // 因此m1与m2同样有6个1，但行列不同，因此不相等
    assert(m1 != m2);
    // 只有m3这样的行列相同，元素相同，才应相等
    assert(m1 == m3);

    // 同样的结果可以通过直接初始化每个元素为一个相同的数值得到
    assert(m1 == Matrix(3, 2, 1));

    // m1相加之后，应得到一个3行2列，元素全为2的矩阵
    assert(m1 + m1 == Matrix(3, 2, 2));
    // 但如果矩阵行列不同，无法直接相加，只能得到非法矩阵
    assert(m1 + m2 == Matrix::INVALID_MATRIX);

    // 同样，减法按元素相减，相当于加上相反数
    assert(m1 - m1 == m1 + (-m1));
    // 相反数的结果应正确
    assert(-m1 == Matrix(3, 2, -1));

    // 在乘法中，如果矩阵行列不满足条件，只能得到非法矩阵
    assert(m1 * m1 == Matrix::INVALID_MATRIX);
    // 满足乘法条件，m1与其转置矩阵的乘积((3 X 2) X (2 X 3))为3行3列元素为2矩阵
    assert(m1 * m1.trans() == Matrix(3, 3, 2));
    // 满足乘法条件，m1转置矩阵与m1的乘积((2 X 3) X (3 X 2))为2行2列元素为3矩阵
    assert(m1.trans() * m1 == Matrix(2, 2, 3));

    // 向量可转化为矩阵与矩阵相乘，同样要满足矩阵乘法条件，由于v相当于1X3矩阵，元素为3，因此结果为1X2矩阵，元素为9
    assert(Matrix(v) * m1 == Matrix(1, 2, 9));
    // 改变顺序后也可通过转置获得另一个乘积，因此结果为2X1矩阵，元素为9，即相当于上面一个结果的转置
    assert(m1.trans() * Matrix(v).trans() == Matrix(2, 1, 9));
    return 0;
}

