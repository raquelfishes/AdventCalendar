#pragma once

//#include "std_includes.h"

template<typename T>
class Vector2
{

public:
  Vector2() : x( 0 ), y( 0 ) {};
  Vector2(const T& v) : x(v),y(v){}
  Vector2(const T& x, const T& y) : x(x), y(y){}

  void operator = (const Vector2& v) { x = v.x; y = v.y; }
  bool operator == (const Vector2& v) const { return x == v.x && y == v.y; }
  bool operator != (const Vector2& v) const { return x != v.x || y != v.y; }
  bool operator < (const Vector2& v) const { return x < v.x || (x==v.x && y <v.y);  }
  
  Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
  Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
  void operator += (const Vector2& v) { x += v.x; y += v.y; }
  void operator -= (const Vector2& v) { x -= v.x; y -= v.y; }
  Vector2 operator * (const T& v) const { return Vector2(x * v, y * v); }
  Vector2 operator / (const T& v) const { const T inv = 1 / v;  return Vector2(x * inv, y * inv); }

public:

  T x;
  T y;
};



typedef Vector2<int> Vector2I;
//typedef Vector2<long long> Vector2LL;
//typedef Vector2<float> Vector2F;
//typedef Vector2<double> Vector2D;