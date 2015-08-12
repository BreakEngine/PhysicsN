#ifndef IEMATH_H
#define IEMATH_H

#include <cmath> // abs, sqrt
#include <cassert> // assert
#include <algorithm> // max, min
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

typedef float real;
typedef double real64;
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef glm::vec2 Vec2;

#ifdef WIN32 // these types are not standard, only exist in windows
typedef __int64 int64;
typedef unsigned __int64 uint64;
#endif
typedef float f32;
typedef double f64;

const real PI = 3.141592741f;
const real EPSILON = 0.0001f;




inline real LenSqr( glm::vec2 _vec ) 
{
	return _vec.x * _vec.x + _vec.y * _vec.y;
}



inline real Len( glm::vec2 _vec ) 
{
	return std::sqrt( _vec.x * _vec.x + _vec.y * _vec.y );
}


inline glm::vec2 Normalize( glm::vec2 _vec )
{
	real len = Len( _vec );

	if(len > EPSILON)
	{
		real invLen = 1.0f / len;
		_vec.x *= invLen;
		_vec.y *= invLen;
	}

	return _vec;
}




struct Mat2
{
	union
	{
		struct
		{
			real m00, m01;
			real m10, m11;
		};

		real m[2][2];
		real v[4];
	};

	Mat2( ) {}
	Mat2( real radians )
	{
		real c = std::cos( radians );
		real s = std::sin( radians );

		m00 = c; m01 = -s;
		m10 = s; m11 =  c;
	}

	Mat2( real a, real b, real c, real d )
		: m00( a ), m01( b )
		, m10( c ), m11( d )
	{
	}

	void Set( real radians )
	{
		real c = std::cos( radians );
		real s = std::sin( radians );

		m00 = c; m01 = -s;
		m10 = s; m11 =  c;
	}

	Mat2 Abs( void ) const
	{
		return Mat2( std::abs( m00 ), std::abs( m01 ), std::abs( m10 ), std::abs( m11 ) );
	}

	Vec2 AxisX( void ) const
	{
		return Vec2( m00, m10 );
	}

	Vec2 AxisY( void ) const
	{
		return Vec2( m01, m11 );
	}

	Mat2 Transpose( void ) const
	{
		return Mat2( m00, m10, m01, m11 );
	}

	const Vec2 operator*( const Vec2& rhs ) const
	{
		return Vec2( m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y );
	}

	const Mat2 operator*( const Mat2& rhs ) const
	{
		// [00 01]  [00 01]
		// [10 11]  [10 11]

		return Mat2(
			m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
			m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
			m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
			m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
		);
	}
};



inline Vec2 Min( const Vec2& a, const Vec2& b )
{
	return Vec2( std::min( a.x, b.x ), std::min( a.y, b.y ) );
}

inline Vec2 Max( const Vec2& a, const Vec2& b )
{
	return Vec2( std::max( a.x, b.x ), std::max( a.y, b.y ) );
}

inline real Dot( const Vec2& a, const Vec2& b )
{
	return a.x * b.x + a.y * b.y;
}

inline real DistSqr( const Vec2& a, const Vec2& b )
{
	Vec2 c = a - b;
	return Dot( c, c );
}

inline Vec2 Cross( const Vec2& v, real a )
{
	return Vec2( a * v.y, -a * v.x );
}

inline Vec2 Cross( real a, const Vec2& v )
{
	return Vec2( -a * v.y, a * v.x );
}

inline real Cross( const Vec2& a, const Vec2& b )
{
	return a.x * b.y - a.y * b.x;
}



// Comparison with tolerance of EPSILON
inline bool Equal( real a, real b )
{
	// <= instead of < for NaN comparison safety
	return std::abs( a - b ) <= EPSILON;
}



inline real Sqr( real a )
{
	return a * a;
}



inline real Clamp( real min, real max, real a )
{
	if (a < min) return min;
	if (a > max) return max;
	return a;
}



inline int32 Round( real a )
{
	return (int32)(a + 0.5f);
}


/*
needed to use,,
*/
inline real Random( real l, real h )
{
	real a = (real)rand( );
	a /= RAND_MAX;
	a = (h - l) * a + l;
	return a;
}

inline bool BiasGreaterThan( real a, real b )
{
	const real k_biasRelative = 0.95f;
	const real k_biasAbsolute = 0.01f;
	return a >= b * k_biasRelative + a * k_biasAbsolute;
}



/*
constat to use..
*/
const f32 gravityScale = 5.0f;
const Vec2 gravity( 0, 10.0f * gravityScale );
const float dt = 1.0f / 60.0f;

#endif // IEMATH_H
