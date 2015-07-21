#pragma once
#include "Body.h"

#define MaxPolyVertexCount 64

class Shape
{
public:
	enum Type
	{
		eCircle,
		ePoly,
		eCount
	};

	Shape( ) {}
	virtual Shape *Clone( void ) const = 0;
	virtual void Initialize( void ) = 0;
	virtual void ComputeMass( real density ) = 0;
	virtual void SetOrient( real Radiance ) = 0;

	virtual void DSet_Orient( real Degree ) =0;

	virtual void Draw( void ) const = 0;
	virtual Type GetType( void ) const = 0;

	Body *body;

	// For circle shape
	real radius;

	// For Polygon shape
	Mat2 u; // Orientation matrix from model to world
};













