#pragma once
#include "rigidBody.h"

#define MaxPolyVertexCount 64

class Body
{
public:

	Body(RigidBody *_rigBody, uint32 x, uint32 y );

	~Body()
	{
		delete rigBody;
	}

	void ApplyForce( const Vec2& f );

	void SetStatic( void );

	void SetOrient( real Degree );

	//used by the engine ....
	void ApplyImpulse( const Vec2& impulse, const Vec2& contactVector );

	void SetColliderType(RigidBody::Type type);

	RigidBody::Type GetColliderType();

	Vec2 position;
	Vec2 velocity;

	real angularVelocity;
	real torque;
	real orient; // degree

	Vec2 force;

	// Set by shape
	real I;  // moment of inertia
	real iI; // inverse inertia 
	real m;  // mass
	real im; // inverse masee

	real staticFriction;
	real dynamicFriction;
	real restitution;

	// Shape interface
	RigidBody *rigBody;

	RigidBody::Type _type;

	// For circle shape
	real radius;
	real density;

	// For Polygon shape
	Mat2 u; // Orientation matrix from model to world
	real width;
	real hight;



	uint32 m_vertexCount;
	Vec2 m_vertices[MaxPolyVertexCount];
	Vec2 m_normals[MaxPolyVertexCount];


	// Store a color in RGB format
	real r, g, b;
};