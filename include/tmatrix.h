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
    if (sz > MAX_VECTOR_SIZE)
        throw ("cant_create_too_large_vector");
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
        pMem = v.pMem;
        sz = v.sz;
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v) 
    {
        if (sz != v.sz) 
        {
            T* p = new T[v.sz]();
            delete[] pMem;
            sz = v.sz;
            pMem = p;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

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
        if (ind >= sz) throw("Error wrong size");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz) throw("Error wrong size");
        return pMem[ind];
    }
        
    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz == v.sz) 
        {
            for (int i = 0; i < sz; i++) 
            {
                if (pMem[i] != v.pMem[i]) 
                {
                    return false;
                }
            }
            return true;
        }
        else 
        {
            return false;
        }
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz == v.sz) 
        {
            for (int i = 0; i < sz; i++) 
            {
                if (pMem[i] != v.pMem[i]) 
                {
                    return true;
                }
            }
            return false;
        }
        else 
        {
            return true;
        }
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] + val;
        }
        return res;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] - val;
        }
        return res;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw ("vectors with different sizes");
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw ("vectors with different sizes");
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
            throw ("vectors with different sizes");
        T res = 0;
        for (int i = 0; i < sz; i++) 
        {
            res += pMem[i] * v.pMem[i];
        }
        return res;
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
        if (s > MAX_MATRIX_SIZE)
            throw ("cant_create_too_large_matrix");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    size_t size() const noexcept { return sz; }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    T& at(size_t i, size_t j)
    {
        if (i >= sz || j >= sz)
            throw ("set_element_with_too_large_index");
        return pMem[i][j];
    }

    const T& at(size_t i, size_t j) const
    {
        if (i >= sz || j >= sz)
            throw ("set_element_with_too_large_index");
        return pMem[i][j];
    }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz == m.sz) {
            for (size_t i = 0; i < sz; i++) 
            {
                if (pMem[i] != m.pMem[i]) 
                {
                    return false;
                }
            }
            return true;
        }
        else 
        {
            return false;
        }
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz)
            throw ("matrix ans vector with different sizes");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++) 
        {
            res.pMem[i] = 0;
            for (size_t j = 0; j < sz; j++) 
            {
                res.pMem[i] += pMem[j][i] * v.pMem[j];
            }
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw ("matrix with different sizes");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] + m.pMem[i];
        }
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw ("matrix with different sizes");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) 
        {
            res.pMem[i] = pMem[i] - m.pMem[i];
        }
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw ("matrix with different sizes");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) 
        {
            for (size_t j = 0; j < sz; j++) 
            {
                res.pMem[i][j] = 0;
            }
        }
        for (size_t i = 0; i < sz; i++) 
        {
            for (size_t j = 0; j < sz; j++) 
            {
                for (size_t k = 0; k < sz; k++)
                {
                    res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
                }             
            }
        }
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) 
        {
            for (size_t j = 0; j < v.sz; j++) 
            {
                istr >> v.pMem[i][j]; 
            }                
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) 
        {
            for (size_t j = 0; j < v.sz; j++) 
            {
                ostr << v.pMem[i][j] << ' ';
            }
        }
        return ostr;
    }
};

#endif
