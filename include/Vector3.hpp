#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <iostream>
#include <cmath>
namespace sima

{
template <class T>
class Vector3
{

public:
  inline Vector3() { tElem_[0] = tElem_[1] = tElem_[2] = 0; }
  Vector3(T x, T y, T z) { tElem_[0] = x; tElem_[1] = y; tElem_[2]= z; }
  Vector3(T *p) { tElem_[0] = p[0]; tElem_[1] = p[1]; tElem_[2]= p[2]; }

  void setXYZ(T newX, T newY, T newZ) { tElem_[0] = newX; tElem_[1] = newY; tElem_[2] = newZ; }

  void setXYZ(T *p) { tElem_[0] = p[0]; tElem_[1] = p[1]; tElem_[2] = p[2]; }

  operator const T*() const { return &tElem_[0]; }
  operator T*() { return &tElem_[0]; }
  T& operator[](int i) { return tElem_[i]; }
  const T& operator[](int i) const { return tElem_[i]; }
  inline bool operator==(const Vector3<T>& v);
  inline bool operator!=(const Vector3<T>& v);
  inline Vector3<T> operator-(const Vector3<T>& v) const;
  inline Vector3<T> operator-() const;
  inline Vector3<T> operator+(const Vector3<T>& v) const;

  inline Vector3<T>& operator+=(const Vector3<T>&v);
  inline Vector3<T>& operator/=(const Vector3<T>&v);
  inline Vector3<T>& operator*=(const Vector3<T>&v);
  inline Vector3<T> operator/(T a) const;
  inline Vector3<T>& operator/=(T a);
  inline Vector3<T> operator*(T a);
  inline Vector3<T>& operator*=(T a);
  inline Vector3<T>& operator+=(T a);

  inline Vector3<T> cross(const Vector3<T>& v) const;
  inline T sqrMag() const;
  inline T magnitude() const;
  inline T dot(const Vector3<T>& v) const;
  inline T lInfNorm(const Vector3<T> &v) const;
  inline Vector3<T>& normalize();
  inline Vector3<T> getNormalized();

  void write(std::ostream& os) const;

private:
  T tElem_[3];
};

template <class T>
inline
bool Vector3<T>::operator==(const Vector3<T>& v)
{
    bool c=true;
    c = c && tElem_[0] == v[0];
    c = c && tElem_[1] == v[1];
    c = c && tElem_[2] == v[2];
    return c;
}

template <class T>
inline
bool Vector3<T>::operator!=(const Vector3<T>& v)
{
    bool c=true;
    c = c && tElem_[0] != v[0];
    c = c && tElem_[1] != v[1];
    c = c && tElem_[2] != v[2];
    return c;
}

template <class T>
inline
Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const
{
    Vector3<T> c;
    c[0] = tElem_[0] - v[0];
    c[1] = tElem_[1] - v[1];
    c[2] = tElem_[2] - v[2];
    return c;
}

template<class T>
inline
Vector3<T> Vector3<T>::operator-() const
// Returns the negative of *this.  Creates a temporary for the return value.
{
    Vector3<T> result;
    result.tElem_[0] = -tElem_[0];
    result.tElem_[1] = -tElem_[1];
    result.tElem_[2] = -tElem_[2];
    return result;
}

template <class T>
inline
Vector3<T> Vector3<T>::operator+(const Vector3<T>& v) const
{
    Vector3<T> c;
    c[0] = tElem_[0] + v[0];
    c[1] = tElem_[1] + v[1];
    c[2] = tElem_[2] + v[2];
    return c;
}

template <class T>
inline
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& v)
{
    tElem_[0] += v[0];
    tElem_[1] += v[1];
    tElem_[2] += v[2];
    return *this;
}

template <class T>
inline
Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& v)
{
    tElem_[0] /= v[0];
    tElem_[1] /= v[1];
    tElem_[2] /= v[2];
    return *this;
}

template <class T>
inline
Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& v)
{
    tElem_[0] *= v[0];
    tElem_[1] *= v[1];
    tElem_[2] *= v[2];
    return *this;
}

template <class T>
inline
Vector3<T> Vector3<T>::operator/(T a) const
{
  Vector3<T> t(*this);
  t/=a;
  return t;
}

template <class T>
inline
Vector3<T>& Vector3<T>::operator/=(T a)
{
    tElem_[0] /= a;
    tElem_[1] /= a;
    tElem_[2] /= a;
    return *this;
}

template <class T>
inline
Vector3<T> Vector3<T>::operator*(T a)
{
  Vector3<T> res;
  res.tElem_[0] = tElem_[0]*a;
  res.tElem_[1] = tElem_[1]*a;
  res.tElem_[2] = tElem_[2]*a;
  return res;
}

template <class T>
inline
Vector3<T>& Vector3<T>::operator*=(T a)
{
    tElem_[0] *= a;
    tElem_[1] *= a;
    tElem_[2] *= a;
    return *this;
}

template <class T>
inline
Vector3<T>& Vector3<T>::operator+=(T a)
{
    tElem_[0] += a;
    tElem_[1] += a;
    tElem_[2] += a;
    return *this;
}

template <class T>
inline
Vector3<T> Vector3<T>::cross(const Vector3<T>& v) const
{
    Vector3<T> result;
    result.tElem_[0] = tElem_[1] * v.tElem_[2] - tElem_[2] * v.tElem_[1];
    result.tElem_[1] = tElem_[2] * v.tElem_[0] - tElem_[0] * v.tElem_[2];
    result.tElem_[2] = tElem_[0] * v.tElem_[1] - tElem_[1] * v.tElem_[0];
    return result;
}

template <class T>
inline
T Vector3<T>::dot(const Vector3<T>& v) const
{
    T result;
    result = tElem_[0] * v.tElem_[0];
    result += tElem_[1] * v.tElem_[1];
    result += tElem_[2] * v.tElem_[2];
    return result;

}

template <class T>
inline
T Vector3<T>::sqrMag() const
{
    return tElem_[0]*tElem_[0] + tElem_[1]*tElem_[1] + tElem_[2]*tElem_[2];
}

template <class T>
inline
T Vector3<T>::magnitude() const
{
  return (T)std::sqrt(sqrMag());
}

template <class T>
inline
T Vector3<T>::lInfNorm(const Vector3<T> &v) const
{
    T	dx = (T)fabs(tElem_[0] - v.tElem_[0]);
    T dy = (T)fabs(tElem_[1] - v.tElem_[1]);
    T dz = (T)fabs(tElem_[2] - v.tElem_[2]);
    T d = dx;
    if (dy > d) d = dy;
    if (dz > d) d = dz;
    return d;
}


template <class T>
inline
Vector3<T>& Vector3<T>::normalize()
{
    T f = magnitude();
    if(f < 0.0000001)
    {
        // Punt.
        tElem_[0] = 1;
        tElem_[1] = 0;
        tElem_[2] = 0;
    }
    else
    {
        this->operator/=(f);
    }
    return *this;
}


template <class T>
inline
Vector3<T> Vector3<T>::getNormalized()
{
    T f = magnitude();
    Vector3<T> ret = *this;
    if(f < 0.0000001)
    {
        // Punt.
        ret.tElem_[0] = 1;
        ret.tElem_[1] = 0;
        ret.tElem_[2] = 0;
    }
    else
    {
        ret /= f;
    }
    return ret;
}

template <class T>
void Vector3<T>::write(std::ostream& os) const
{
   os << tElem_[0] << " ";
   os << tElem_[1] << " ";
   os << tElem_[2];
}

/// Stream insertion for vec3.
template <class T>
inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
{ v.write(os); return os; }

typedef Vector3<float> Vector3f;
typedef Vector3<unsigned int> Vector3ui;

} // end namespace sima

#endif // _VECTOR3_H_
