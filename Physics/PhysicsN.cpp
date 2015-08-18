#include "EngineFiles.h"


PhysicsN::PhysicsN(void) : m_dt( 1.0f / 60.0f ) , m_iterations( 10 )
{
}


PhysicsN::~PhysicsN(void)
{
	for(int i = 0 ; i < bodies.size() ; ++i)
	{
		delete bodies[i];
	}
}


void PhysicsN::IntegrateForces( Body2D *b, real dt )
{
	if(b->im == 0.0f)
		return;

	b->velocity += (b->force * b->im + gravity) * (dt / 2.0f);
	b->angularVelocity += b->torque * b->iI * (dt / 2.0f);
}

void PhysicsN::IntegrateVelocity( Body2D *b, real dt )
{
	if(b->im == 0.0f)
		return;

	b->position += b->velocity * dt;
	b->orient += b->angularVelocity * dt;
	b->SetOrient( b->orient );
	IntegrateForces( b, dt );
}

void PhysicsN::Step( void )
{
	// Generate new collision info
	contacts.clear( );
	for(uint32 i = 0; i < bodies.size( ); ++i)
	{
		Body2D *A = bodies[i];

		for(uint32 j = i + 1; j < bodies.size( ); ++j)
		{
			Body2D *B = bodies[j];
			if(A->im == 0 && B->im == 0)
				continue;
			Manifold m( A, B );
			m.Solve( );
			if(m.contact_count)
				contacts.emplace_back( m );
		}
	}

	// Integrate forces
	for(uint32 i = 0; i < bodies.size( ); ++i)
		IntegrateForces( bodies[i], m_dt );

	// Initialize collision
	for(uint32 i = 0; i < contacts.size( ); ++i)
		contacts[i].Initialize( );

	// Solve collisions
	for(uint32 j = 0; j < m_iterations; ++j)
		for(uint32 i = 0; i < contacts.size( ); ++i)
			contacts[i].ApplyImpulse( );

	// Integrate velocities
	for(uint32 i = 0; i < bodies.size( ); ++i)
		IntegrateVelocity( bodies[i], m_dt );

	// Correct positions
	for(uint32 i = 0; i < contacts.size( ); ++i)
		contacts[i].PositionalCorrection( );

	// Clear all forces
	for(uint32 i = 0; i < bodies.size( ); ++i)
	{
		Body2D *b = bodies[i];
		b->force = Vec2( 0, 0 );
		b->torque = 0;
	}
}


Body2D *PhysicsN::Add(Collider::Type type ,vec2 _position , Vec2 Width_hight)
{
	b = new Body2D(type,_position , Width_hight);
	bodies.push_back( b );
	return b;
}


Body2D *PhysicsN::Add(Collider::Type type ,vec2 _position , real _radius)
{
	b = new Body2D(type,_position , _radius);
	bodies.push_back( b );
	return b;
}



void PhysicsN::Update_physics()
{
	accumulator += _clock.Elapsed();


	/////////////////////////////// updating physics
	_clock.Start();
	accumulator = Clamp( 0.0f, 0.1f, accumulator );
	while(accumulator >= dt)
	{
		Step( );
		accumulator -= dt;
	}

	_clock.Stop();
}