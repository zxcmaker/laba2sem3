#pragma once
#include "Vector.h"
#include <iostream>


const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicMatrix : public TDynamicVector < TDynamicVector < T>>
{
    using TDynamicVector <TDynamicVector <T>>::pMem;
    using TDynamicVector <TDynamicVector <T>>::sz;
public:
    using TDynamicVector <TDynamicVector <T>>::operator[];
    TDynamicMatrix(size_t size = 1);
    virtual ~TDynamicMatrix() {};

    bool operator==(const TDynamicMatrix& m);

    TDynamicMatrix<T> operator*(const T val);
    TDynamicMatrix<T> operator*=(const T val);
    TDynamicVector<T> operator*(const TDynamicVector<T>& v);
    TDynamicMatrix operator+(const TDynamicMatrix& m);
    TDynamicMatrix operator-(const TDynamicMatrix& m);
    TDynamicMatrix operator*(const TDynamicMatrix& m);

    template<typename T>
    friend std::istream& operator>>(std::istream& istr, TDynamicMatrix<T>& v);

    template<typename T>
    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix<T>& v);
};

template<typename T>
inline TDynamicMatrix<T>::TDynamicMatrix(size_t size) : TDynamicVector<TDynamicVector<T>>(size)
{
    if (size > MAX_MATRIX_SIZE)
        throw "size > MAX_MATRIX_SIZE";
    for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
}

template<typename T>
inline bool TDynamicMatrix<T>::operator==(const TDynamicMatrix& m)
{
    return TDynamicVector<TDynamicVector<T>>::operator == (m);
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const T val)
{
    TDynamicMatrix<T> res(*this);
    for (int i = 0; i < sz; i++)
        res.pMem[i] = res.pMem[i] * val;
    return res;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*=(const T val)
{
    for (int i = 0; i < sz; i++)
        pMem[i] *= val;
    return*this;
}

template<typename T>
inline TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& v)
{
    if (sz != v.size())
        throw "operator* : sz != v.sz";
    TDynamicVector<T> res(sz);
    for (int i = 0; i < sz; i++)
    {
        res.pMemm()[i] = 0;
        for (int j = 0; j < sz; j++)
            res.pMemm()[i] += pMem[i][j] * v.pMemm()[j];
    }
    return res;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m)
{
    if (sz != m.sz)
        throw "operator+ : sz != m.sz";
    TDynamicMatrix<T> res(sz);
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            res.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
    return res;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m)
{
    if (sz != m.sz)
        throw "operator+ : sz != m.sz";
    TDynamicMatrix<T> res(sz);
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            res.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
    return res;
}

template<typename T>
inline TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m)
{
    TDynamicMatrix res(*this);
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < sz; k++)
                res.pMem[i][j] += m.pMem[k][j] * pMem[i][k];
        }
    }
    return res;
}

template<typename T>
inline std::istream& operator>>(std::istream& istr, TDynamicMatrix<T>& v)
{
    for (int i = 0; i < v.size(); i++)
        for (int j = 0; j < v.size(); j++)
            istr >> v.pMem[i][j];
    return istr;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix<T>& v)
{
    for (int i = 0; i < v.sz; i++)
        ostr << v.pMem[i] << std::endl;
    ostr << std::endl;
    return ostr;
}