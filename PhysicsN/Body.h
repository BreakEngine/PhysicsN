#pragma once
class Shape;


class Body
{
public:

	Body( Shape *shape_, uint32 x, uint32 y );

	void ApplyForce( const Vec2& f );

	void SetStatic( void );

	void SetOrient( real Degree );

	void RSetOrient( real Radians );

	//used by the engine ....
	void ApplyImpulse( const Vec2& impulse, const Vec2& contactVector );

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
	Shape *shape;

	// Store a color in RGB format
	real r, g, b;
};