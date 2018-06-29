#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
const int MAX_M = 10;

struct Matrix{

   int _n, _m;
   int _a[MAX_M][MAX_M];

   Matrix(int __n = 0, int __m = 0) { _n = __n; _m = __m; memset(_a, 0, sizeof(_a));}

   int* operator[] (int i)   { return _a[i]; }
   const int* operator[] (int i) const { return _a[i]; }

   Matrix& operator= (Matrix rhs)
   {
       (*this)._n = rhs._n; (*this)._m = rhs._m;
       for(int i = 1; i <= rhs._n; i++)
         for(int j = 1; j <= rhs._m; j++)
            (*this)[i][j] = rhs[i][j];

       return *this;
   }

   Matrix& operator*= (const Matrix& rhs)
   {
       assert((*this)._m == rhs._n);

       Matrix _tmp((*this)._n, rhs._m);
       for(int i = 1; i <= (*this)._n; i++)
           for(int j = 1; j <= rhs._m; j++)
               for(int k = 1; k <= (*this)._m; k++)
                    _tmp[i][j] += (*this)[i][k] * rhs[k][j];

       (*this) = _tmp;
       return *this;
   }
};

inline Matrix operator* (Matrix lhs, const Matrix& rhs)
{
       lhs *= rhs;
       return lhs;
}

ostream& operator<< (ostream& os, const Matrix& obj)
{
    for(int i = 1; i <= obj._n; i++)
    {
        for(int j = 1; j <= obj._m; j++)
            os << obj[i][j] << " ";
        os << endl;
    }

    return os;
}

istream& operator>> (istream& is, Matrix& obj)
{
    if(!obj._n && !obj._m) is >> obj._n >> obj._m;
    for(int i = 1; i <= obj._n; i++)
        for(int j = 1; j <= obj._m; j++)
           is >> obj[i][j];

    return is;
}

template <class T>
T fast_pow(const T& _base, int _e)
{
    if(_e == 1)
        return _base;

    T _res = fast_pow(_base, _e / 2);
    _res *= _res;

    if(_e % 2)
        _res *= _base;

    return _res;
}


