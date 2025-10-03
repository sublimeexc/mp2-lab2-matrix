// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
        {
            return *this;
        }
        if (sz != v.sz)
        {
            T* p = new T[v.sz];
            sz = v.sz;
            delete[] pMem;
            pMem = p;
        }
        TDynamicVector tmp(sz);
        swap(*this, tmp);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept
    {
        return sz;
    }

    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return 0;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != v.pMem[i]) return 0;
        }
        return 1;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return 1;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != v.pMem[i]) return 1;
        }
        return 0;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + val;
        }
        return tmp
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] - val;
        }
        return tmp
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + v.pMem[i];
        }
        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] - v.pMem[i];
        }
        return tmp;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        T tmp = 0;
        for (size_t i = 0; i < sz; i++)
        {
            tmp += pMem[i] * v.pMem[i];
        }
        return tmp;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) 
        {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
    }
};

#endif
