#pragma once
#include <iostream>
const int MAX_VECTOR_SIZE = 10000000;

template<typename T>
class TVectorIterator;

template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1);
	TDynamicVector(T* arr, size_t s);
	TDynamicVector(const TDynamicVector& v);
	TDynamicVector(TDynamicVector&& v) noexcept;
	~TDynamicVector();
	TDynamicVector& operator=(const TDynamicVector& v);
	TDynamicVector& operator=(TDynamicVector&& v) noexcept;

	size_t size() const noexcept;
	T* pMmem() const noexcept;

	T& operator[](size_t ind);
	const T& operator[](size_t ind) const;
	T& at(size_t ind);
	const T& at(size_t ind) const;

	bool operator==(const TDynamicVector& v) noexcept;
	bool operator!=(const TDynamicVector& v) noexcept;

	TDynamicVector operator+(T val);
	TDynamicVector operator-(double val);
	TDynamicVector operator*(double val);

	TDynamicVector operator+(const TDynamicVector& v);
	TDynamicVector operator-(const TDynamicVector& v);
	T operator*(const TDynamicVector& v);

	template<typename T>
	friend std::istream& operator>>(std::istream& istr, TDynamicVector<T>& v);

	template<typename T>
	friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector<T>& v);

	TVectorIterator<T> begin();
	TVectorIterator<T> end();
};

template<typename T>
std::ostream& operator<<(std::ostream& ostr, const TDynamicVector<T>& v)
{
	for (size_t i = 0; i < v.sz; i++)
		ostr << v.pMem[i] << ' ';
	return ostr;
}

template<typename T>
std::istream& operator>>(std::istream& istr, TDynamicVector<T>& v)
{
	for (size_t i = 0; i < v.sz; i++)
		istr >> v.pMem[i];
	return istr;
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(size_t size)
{
	if (size <= 0)
		throw "TDynamicVector size <= 0";
	if (size > MAX_VECTOR_SIZE)
		throw "size > MAX_VECTOR_SIZE";
	sz = size;
	pMem = new T[size];

}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(T* arr, size_t s)
{
	if (s <= 0)
		throw "TDynamicVector s <= 0";
	if (arr == nullptr)
		throw "TDynamicVector arr == nullptr";
	sz = s;
	pMem = new T[sz];
	for (int i = 0; i < sz; i++)
		pMem[i] = arr[i];
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(const TDynamicVector& v)
{
	if (v.pMem == nullptr)
	{
		sz = 0;
		pMem = nullptr;
	}
	else
	{
		sz = v.sz;
		pMem = new T[sz];
		for (int i = 0; i < sz; i++)
			pMem[i] = v.pMem[i];
	}
}

template<typename T>
inline TDynamicVector<T>::TDynamicVector(TDynamicVector&& v) noexcept
{
	sz = v.sz;
	pMem = v.pMem;
	v.sz = 0;
	v.pMem = nullptr;
}

template<typename T>
inline TDynamicVector<T>::~TDynamicVector()
{
	if (pMem != nullptr)
	{
		delete[] pMem;
		sz = 0;
	}
}

template<typename T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& v)
{
	if (this != &v)
	{
		if (pMem == nullptr)
			delete[] pMem;
		if (v.pMem == nullptr)
		{
			sz = 0;
			pMem = nullptr;
		}
		else
		{
			sz = v.sz;
			pMem = new T[sz];
			for (int i = 0; i < sz; i++)
				pMem[i] = v.pMem[i];
		}
	}
	return*this;
}

template<typename T>
inline TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector<T>&& v) noexcept
{
	if (this != &v)
	{
		if (pMem != nullptr)
			delete[] pMem;
		sz = v.sz;
		pMem = v.pMem;
		v.sz = 0;
		v.pMem = nullptr;
	}
	return*this;
}

template<typename T>
inline size_t TDynamicVector<T>::size() const noexcept
{
	return sz;
}

template<typename T>
inline T* TDynamicVector<T>::pMmem() const noexcept
{
	return pMem;
}

template<typename T>
inline T& TDynamicVector<T>::operator[](size_t ind)
{
	return pMem[ind];
}

template<typename T>
inline const T& TDynamicVector<T>::operator[](size_t ind) const
{
	return pMem[ind];
}

template<typename T>
inline T& TDynamicVector<T>::at(size_t ind)
{
	if (pMem == nullptr)
		throw "operator[] pMem != nullptr";
	if (ind >= sz || ind < 0)
		throw "operator[] ind >= sz || ind < 0";
	return pMem[ind];
}

template<typename T>
inline const T& TDynamicVector<T>::at(size_t ind) const
{
	if (pMem == nullptr)
		throw "operator[] pMem != nullptr";
	if (ind >= sz || ind < 0)
		throw "operator[] ind >= sz || ind < 0";
	return pMem[ind];
}
template<typename T>
inline bool TDynamicVector<T>::operator==(const TDynamicVector& v) noexcept
{
	if (sz != v.sz)
		return false;
	for (int i = 0; i < sz; i++)
	{
		if (pMem[i] != v.pMem[i])
			return false;
	}
	return true;
}

template<typename T>
inline bool TDynamicVector<T>::operator!=(const TDynamicVector& v) noexcept
{
	return !(this->operator==(v));
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(T val)
{
	if (pMem == nullptr) throw "operator +: pMem == nillptr";
	TDynamicVector<T> res(*this);
	for (int i = 0; i < sz; i++)
	{
		res.pMem[i] += val;
	}
	return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(double val)
{
	if (pMem == nullptr) throw "operator -: pMem == nillptr";
	TDynamicVector<T> res(*this);
	for (int i = 0; i < sz; i++)
	{
		res.pMem[i] -= val;
	}
	return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator*(double val)
{
	if (pMem == nullptr) throw "operator *: pMem == nillptr";
	TDynamicVector<T> res(*this);
	for (int i = 0; i < sz; i++)
	{
		res.pMem[i] *= val;
	}
	return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector& v)
{
	if (pMem == nullptr)"operator +: pMem == nillptr";
	if (sz != v.sz)
		throw "operator+: sz != v.sz";
	TDynamicVector res(*this);
	for (int i = 0; i < sz; i++)
		res.pMem[i] += v.pMem[i];
	return res;
}

template<typename T>
inline TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector& v)
{
	if (pMem == nullptr)"operator -: pMem == nillptr";
	if (sz != v.sz)
		throw "operator-: sz != v.sz";
	TDynamicVector res(*this);
	for (int i = 0; i < sz; i++)
		res.pMem[i] -= v.pMem[i];
	return res;
}

template<typename T>
inline T TDynamicVector<T>::operator*(const TDynamicVector& v)
{
	if (pMem == nullptr)"operator *: pMem == nillptr";
	if (sz != v.sz)
		throw "operator*: sz != v.sz";
	T res = 0;
	for (int i = 0; i < sz; i++)
		res += pMem[i] * v.pMem[i];
	return res;
}

template<typename T>
inline TVectorIterator<T> TDynamicVector<T>::begin()
{
	return TVectorIterator<T>(*this);
}

template<typename T>
inline TVectorIterator<T> TDynamicVector<T>::end()
{
	return TVectorIterator<T>(*this, this->size());
}

template<typename T>
class TVectorIterator
{
public:
	TVectorIterator(TDynamicVector<T>& v);
	TVectorIterator(TDynamicVector<T>& v, int ind);
	TVectorIterator(TVectorIterator<T>& iv);

	bool operator==(const TVectorIterator<T>& v);
	bool operator!=(const TVectorIterator<T>& v);

	TVectorIterator operator++();
	TVectorIterator operator--();
	T& operator*();
private:
	TDynamicVector<T>& vector;
	int index;
};

template<typename T>
inline TVectorIterator<T>::TVectorIterator(TDynamicVector<T>& v) :vector(v)
{
	index = 0;
}

template<typename T>
inline TVectorIterator<T>::TVectorIterator(TDynamicVector<T>& v, int ind) : vector(v)
{
	index = ind;
}

template<typename T>
inline TVectorIterator<T>::TVectorIterator(TVectorIterator<T>& iv) : vector(iv.vector)
{
	index = iv.index;
}

template<typename T>
inline bool TVectorIterator<T>::operator==(const TVectorIterator<T>& v)
{
	if (&(vector) == &(v.vector) && index == v.index)
		return true;
	else
		return false;
}

template<typename T>
inline bool TVectorIterator<T>::operator!=(const TVectorIterator<T>& v)
{
	if (&(vector) == &(v.vector) && index == v.index)
		return false;
	else
		return true;
}

template<typename T>
inline TVectorIterator<T> TVectorIterator<T>::operator++()
{
	this->index++;
	if (this->index > this->vector.size())
		this->index = this->vector.size();
	return*this;
}

template<typename T>
inline TVectorIterator<T> TVectorIterator<T>::operator--()
{
	this->index--;
	if (this->index > 0)
		this->index = 0;
	return*this;
}

template<typename T>
inline T& TVectorIterator<T>::operator*()
{
	return vector.at(index);
}