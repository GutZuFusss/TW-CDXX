#pragma once

#include <math.h>

constexpr auto PI = 3.14159265358979323846;

//the vector stuff is taken from https://github.com/teeworlds/teeworlds/blob/master/src/base/vmath.h (credits to them)
template<typename T>
class vector2_base
{
public:
	union { T x, u; };
	union { T y, v; };

	vector2_base() {}
	vector2_base(T nx, T ny)
	{
		x = nx;
		y = ny;
	}

	vector2_base operator -() const { return vector2_base(-x, -y); }
	vector2_base operator -(const vector2_base& v) const { return vector2_base(x - v.x, y - v.y); }
	vector2_base operator +(const vector2_base& v) const { return vector2_base(x + v.x, y + v.y); }
	vector2_base operator *(const T v) const { return vector2_base(x * v, y * v); }
	vector2_base operator *(const vector2_base& v) const { return vector2_base(x * v.x, y * v.y); }
	vector2_base operator /(const T v) const { return vector2_base(x / v, y / v); }
	vector2_base operator /(const vector2_base& v) const { return vector2_base(x / v.x, y / v.y); }

	const vector2_base& operator +=(const vector2_base& v) { x += v.x; y += v.y; return *this; }
	const vector2_base& operator -=(const vector2_base& v) { x -= v.x; y -= v.y; return *this; }
	const vector2_base& operator *=(const T v) { x *= v; y *= v; return *this; }
	const vector2_base& operator *=(const vector2_base& v) { x *= v.x; y *= v.y; return *this; }
	const vector2_base& operator /=(const T v) { x /= v; y /= v; return *this; }
	const vector2_base& operator /=(const vector2_base& v) { x /= v.x; y /= v.y; return *this; }

	bool operator ==(const vector2_base& v) const { return x == v.x && y == v.y; } //TODO: do this with an eps instead
	bool operator !=(const vector2_base& v) const { return x != v.x || y != v.y; }

	operator const T* () { return &x; }
};

template<typename T>
inline vector2_base<T> rotate(const vector2_base<T>& a, float angle)
{
	angle = angle * PI / 180.0f;
	float s = sinf(angle);
	float c = cosf(angle);
	return vector2_base<T>((T)(c * a.x - s * a.y), (T)(s * a.x + c * a.y));
}

template<typename T>
inline T distance(const vector2_base<T>& a, const vector2_base<T>& b)
{
	return length(a - b);
}

template<typename T>
inline T dot(const vector2_base<T>& a, const vector2_base<T>& b)
{
	return a.x * b.x + a.y * b.y;
}

template<typename T>
inline vector2_base<T> closest_point_on_line(vector2_base<T> line_point0, vector2_base<T> line_point1, vector2_base<T> target_point)
{
	vector2_base<T> c = target_point - line_point0;
	vector2_base<T> v = (line_point1 - line_point0);
	v = normalize(v);
	T d = length(line_point0 - line_point1);
	T t = dot(v, c) / d;
	return mix(line_point0, line_point1, clamp(t, (T)0, (T)1));
	/*
	if (t < 0) t = 0;
	if (t > 1.0f) return 1.0f;
	return t;*/
}

//
inline float length(const vector2_base<float>& a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

inline float angle(const vector2_base<float>& a)
{
	return atan2f(a.y, a.x);
}

inline vector2_base<float> normalize(const vector2_base<float>& v)
{
	float l = (float)(1.0f / sqrtf(v.x * v.x + v.y * v.y));
	return vector2_base<float>(v.x * l, v.y * l);
}

inline vector2_base<float> direction(float angle)
{
	return vector2_base<float>(cosf(angle), sinf(angle));
}

typedef vector2_base<float> vec2;
typedef vector2_base<bool> bvec2;
typedef vector2_base<int> ivec2;
