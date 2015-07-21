#pragma once

#include "Precompiled.h"


class PolygonShape : public Shape
{
public:
	PolygonShape();

	void Initialize( void );

	Shape *Clone( void ) const;

	void ComputeMass( real density );

	void SetOrient( real Radiance );

	void DSet_Orient( real Degree );


	void Draw( void ) const;

	Type GetType( void ) const;


	// Half width and half height
	void SetBox( real hw, real hh );

	void Set( Vec2 *vertices, uint32 count );

	// The extreme point along a direction within a polygon
	Vec2 GetSupport( const Vec2& dir );

	uint32 m_vertexCount;
	Vec2 m_vertices[MaxPolyVertexCount];
	Vec2 m_normals[MaxPolyVertexCount];
};


