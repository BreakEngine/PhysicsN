#include "Precompiled.h"

Body::Body( Shape *shape_, uint32 x, uint32 y ) : shape( shape_->Clone( ) )
{
	shape->body = this;
	position = Vec2( (real)x, (real)y );
	velocity = Vec2( 0, 0 );
	angularVelocity = 0;
	torque = 0;
	orient = Random( -PI, PI );
	force = Vec2( 0, 0 );

	//physics probs initial..
	//staticFriction = 0.5f;
	//dynamicFriction = 0.3f;
	//restitution = 0.2f;

	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.5f;


	shape->Initialize( );   //compute shape mass..


	r = Random( 0.2f, 1.0f );
	g = Random( 0.2f, 1.0f );
	b = Random( 0.2f, 1.0f );
}

void Body::SetOrient( real Degree )
{
	orient = Degree;
	shape->DSet_Orient( Degree );
}

void Body::RSetOrient(real Radians)
{
	orient = Radians;
	shape->SetOrient( orient );
}

void Body::ApplyForce( const Vec2& f )
{
	force += f;
}

void Body::ApplyImpulse( const Vec2& impulse, const Vec2& contactVector )
{
	velocity += im * impulse;
	angularVelocity += iI * Cross( contactVector, impulse );
}

void Body::SetStatic( void )
{
	I = 0.0f;
	iI = 0.0f;
	m =  0.0f;
	im = 0.0f;
}
