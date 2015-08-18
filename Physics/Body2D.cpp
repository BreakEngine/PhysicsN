#include "EngineFiles.h"



Body2D::Body2D(void)
{
}

Body2D::Body2D(Collider::Type type ,vec2 _position , Vec2 Width_hight)
{

	_typ = type;
	width = Width_hight.x;
	hight = Width_hight.y;
	position = _position;




	velocity = Vec2( 0, 0 );
	angularVelocity = 0;
	torque = 0;
	force = Vec2( 0, 0 );
	SetOrient(0);

	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.5f;

	m = 5;
	im = 0.5;
	I = 0.5;
	iI = 0.5;
	RigidBody = new Poly();
	RigidBody->body = this;
	RigidBody->Initialize();
}

Body2D::Body2D(Collider::Type type ,vec2 _position , real _radius)
{

	_typ = type;
	radius  =_radius;
	position = _position;

	velocity = Vec2( 0, 0 );
	angularVelocity = 0;
	torque = 0;
	force = Vec2( 0, 0 );
	SetOrient(0);

	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.5f;

	m = 5;
	im = 0.5;
	I = 0.5;
	iI = 0.5;

	RigidBody = new Circle();
	RigidBody->body = this;
	RigidBody->Initialize();
}


Body2D::~Body2D(void)
{
	delete RigidBody;
}



Collider::Type Body2D::GetCollider()
{
	return _typ;
}

void Body2D::SetOrient( real Degree )
{
	orient = Degree;
	u.Set(  orient );
}


void Body2D::ApplyForce( const Vec2& f )
{
	force += f;
}

void Body2D::ApplyImpulse( const Vec2& impulse, const Vec2& contactVector )
{
	velocity += im * impulse;
	angularVelocity += iI * Cross( contactVector, impulse );
}

void Body2D::SetStatic( void )
{
	I = 0.0f;
	iI = 0.0f;
	m =  0.0f;
	im = 0.0f;
}

