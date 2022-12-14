#pragma once

// 数学库
#include <vector>
#include <assert.h>
#include <initializer_list>
#include <iostream>
#include <ostream>

#define LIN_PI 3.1415926

template<typename T, size_t L>
struct Vector
{
public:
    Vector(std::initializer_list<T> val)
    {
        for (int i = 0;i < L; ++i)
            val[i] = *(val.begin()+i);
    }
    Vector(const Vector<T, L>& rhs)
    {
        for (int i = 0;i < L; ++i)
            val[i] = rhs.val[i];
    }
    Vector()
    {
        for (int i = 0;i < L; ++i)
            val[i] = T();
    }
    T&       operator [](const size_t i) 
    {
        assert(i < L && i >= 0);
        return val[i];
    }
    const T& operator [](const size_t i) const 
    {
        assert(i < L && i >= 0);
        return val[i];
    }

    Vector<T, L>& operator /=(const T& div)
    {
        for (int i = 0; i < L; ++i)
        {
            val[i] /= div;
        }
    }

private:
    T val[L];
};

template<typename T>
struct Vector<T, 2>
{
    Vector(std::initializer_list<T> l)
    {
        assert(l.size() == 2);
        for (int i = 0; i < 2; ++i)
        {
            val[i] = *(l.begin() + i);
        }
    }
    Vector(T x, T y)
        : x(x), y(y)
    {}
    Vector()
        : x(), y()
    {}
    union 
    {
        struct { T x, y;   };
        struct { T u, v;   };
        struct { T val[2]; };
    };
    T& operator[] (int i)
    {
        assert(i >= 0 && i < 2);
        return val[i];
    }
    const T& operator [](const size_t i) const 
    {
        assert(i < 2 && i >= 0);
        return val[i];
    }
};

template<typename T>
struct Vector<T, 3>
{
    Vector(std::initializer_list<T> l)
    {
        assert(l.size() == 3);
        for (int i = 0; i < 3; ++i)
        {
            val[i] = *(l.begin() + i);
        }
    }
    Vector(T x, T y, T z)
        : x(x), y(y), z(z)
    {}
    Vector()
        : x(), y(), z()
    {}
    union
    {
        struct { T x, y, z;   };
        struct { T val[3];    };
    };
    T& operator[] (int i)
    {
        assert(i >= 0 && i < 3);
        return val[i];
    }
    const T& operator [](const size_t i) const 
    {
        assert(i < 3 && i >= 0);
        return val[i];
    }

    Vector<T, 3> operator ^ (const Vector<T, 3>& rhs) const
    {
        return Vector<T, 3>(y * rhs.z - rhs.y * z, - (x * rhs.z - rhs.x * z), x * rhs.y - rhs.x * y);
    }

    Vector<T, 3> operator - () const
    {
        return Vector<T, 3>(-x, -y, -z);
    }
};

template<typename T>
struct Vector<T, 4>
{
    Vector(std::initializer_list<T> initialize)
    {
        for (int i = 0;i < 4; ++i)
            val[i] = *(initialize.begin() + i);
    }
    Vector(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
    {}
    Vector()
        : x(), y(), z(), w()
    {}
    union 
    {
        struct { T x, y, z, w; };
        struct { T val[4];     };
    };
    T& operator[] (int i)
    {
        assert(i >= 0 && i < 4);
        return val[i];
    }
    const T& operator [](const size_t i) const 
    {
        assert(i < 4 && i >= 0);
        return val[i];
    }

    friend std::ostream& operator<<(std::ostream& output, const Vector<T, 4>& vec)
    {
        output << vec.x << ' ' << vec.y << ' ' << vec.z << ' ' << vec.w;
        return output;
    }
};


template<typename T, size_t row, size_t col>
class Matrix
{
private:
    Vector<T, col> val[row]; // 每行存的是列向量
public:
    static Matrix<T, row, col> Idtentity()
    {
        Matrix<T, row, col> res;
        for (int i = 0;i < row; ++i) res[i][i] = 1;
        return res;
    }
    Matrix(std::initializer_list<Vector<T, col>> initialize)
    {
        for (int i = 0; i < row; ++i)
        {
            val[i] = *(initialize.begin() + i);
        }
    }
    Matrix(const Matrix<T, row, col>& rhs)
    {
        for (int i = 0;i < row; ++i)
            val[i] = rhs.val[i];
    }
    Matrix()
    {
        for (int i = 0;i < row; ++i)
            val[i] = Vector<T, col>();
    }
    Vector<T, col>&       operator[] (int i)
    {
        assert(i >= 0 && i < row);
        return val[i];
    }
    const Vector<T, col>& operator[] (int i) const
    {
        assert(i >= 0 && i < row);
        return val[i];
    }

    friend std::ostream& operator<<(std::ostream& output, const Matrix<T, row, col>& m)
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                output << m.val[i][j] << ' ';
            }
            output << '\n';
        }
        return output;
    }
};

template<typename T, size_t R1, size_t C1, size_t C2>
Matrix<T, R1, C2> operator*(const Matrix<T, R1, C1>& lhs, const Matrix<T, C1, C2>& rhs)
{
    Matrix<T, R1, C2> res;
    for (int i = 0;i < R1; ++i)
    {
        for (int j = 0;j < C2; ++j)
        {
            res[i][j] = 0;
            for (int k = 0;k < C1; ++k)
            {
                res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return res;
}



typedef Vector<float, 2> vec2f;
typedef Vector<int, 2>   vec2i;
typedef Vector<float, 3> vec3f;
typedef Vector<int, 3>   vec3i;
typedef Vector<float, 4> vec4f;

typedef Matrix<float, 4, 4> m4f;

template<typename T, size_t L>
Vector<T, L> operator + (const Vector<T, L>& lhs, const Vector<T, L>& rhs)
{
    Vector<T, L> res;
    for (int i = 0; i < L; ++i)
        res[i] = lhs[i] + rhs[i];
    return res;
}

template<typename T, size_t L>
Vector<T, L> operator - (const Vector<T, L>& lhs, const Vector<T, L>& rhs)
{
    Vector<T, L> res;
    for (int i = 0; i < L; ++i)
        res[i] = lhs[i] - rhs[i];
    return res;
}

template<typename T, size_t L>
Vector<T, L> operator * (const Matrix<T, L, L>& m, const Vector<T, L>& rhs)
{
    Vector<T, L> res;
    for (int i = 0; i < L; ++i)
        res[i] = m[i] * rhs;
    return res;
}

template<typename T, size_t L>
void printVec(const Vector<T, L>& v)
{
    for (int i = 0; i < L; ++i)
        std::cout << v[i] << ' ';
    std::cout << std::endl;
}

template<typename T, size_t L>
float operator * (const Vector<T, L>& lhs, const Vector<T, L>& rhs)
{
    float res = 0;
    for (int i = 0; i < L; ++i)
        res += lhs[i] * rhs[i];
    return res;
}

template<typename T, size_t L>
Vector<T, L> operator * (const Vector<T, L>& lhs, const T& div)
{
    Vector<T, L> res(lhs);
    for (int i = 0; i < L; ++i)
    {
        res[i] *= div;
    }
    return res;
}

template<typename T, size_t L>
Vector<T, L> operator / (const Vector<T, L>& lhs, const T& div)
{
    Vector<T, L> res(lhs);
    for (int i = 0; i < L; ++i)
    {
        res[i] /= div;
    }
    return res;
}

vec3f barycentric2D(vec2f a, vec2f b, vec2f c, vec2f p)
{
    // 这里是没有矫正过的插值，没有使用z轴去计算
    vec3f res;
    res.x = ((p.x - c.x) * (c.y - b.y) - (p.y - c.y) * (c.x - b.x)) /
        ((a.x - c.x) * (c.y - b.y) - (a.y - c.y) * (c.x - b.x));
    res.y = ((p.y - c.y) * (a.x - c.x) - (p.x - c.x) * (a.y - c.y)) /
        ((b.y - c.y) * (a.x - c.x) - (b.x - c.x) * (a.y - c.y));
    res.z = 1 - res.x - res.y;
    return res;
}


vec3f barycentric2D(vec3f a, vec3f b, vec3f c, vec3f p)
{
    // 这里是没有矫正过的插值，没有使用z轴去计算
    vec3f res;
    res.x = ((p.x - c.x) * (c.y - b.y) - (p.y - c.y) * (c.x - b.x)) /
        ((a.x - c.x) * (c.y - b.y) - (a.y - c.y) * (c.x - b.x));
    res.y = ((p.y - c.y) * (a.x - c.x) - (p.x - c.x) * (a.y - c.y)) /
        ((b.y - c.y) * (a.x - c.x) - (b.x - c.x) * (a.y - c.y));
    res.z = 1 - res.x - res.y;
    return res;
}
vec3f vec423(const vec4f& v)
{
    return vec3f(v.x / v.w, v.y / v.w, v.z / v.w);
}

vec4f vec324(const vec3f& v, float w)
{
    return vec4f(v.x, v.y, v.z, w);
}
