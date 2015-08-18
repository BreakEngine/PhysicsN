#pragma once
#include "Collider.h"
#include "IShape.h"

class Body2D
{
public:
	Body2D(void);
	Body2D(Collider::Type type ,vec2 _position , Vec2 Width_hight);  //for rectangles
	Body2D(Collider::Type type ,vec2 _position , real _radius);       //for circles
	~Body2D(void);


	void ApplyForce( const Vec2& f );

	void SetStatic( void );

	void SetOrient( real Degree );

	void ApplyImpulse( const Vec2& impulse, const Vec2& contactVector );

	Collider::Type GetCollider();


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

	Collider::Type _typ;


	// For circle shape
	real radius;
	real density;

	// For Polygon shape
	Mat2 u; // Orientation matrix from model to world
	real width;
	real hight;


	// Shape interface
	Shape *RigidBody;
};

