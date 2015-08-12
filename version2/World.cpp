#include "Precompiled.h"

void IntegrateForces( Body *b, real dt )
{
	if(b->im == 0.0f)
		return;

	b->velocity += (b->force * b->im + gravity) * (dt / 2.0f);
	b->angularVelocity += b->torque * b->iI * (dt / 2.0f);
}

void IntegrateVelocity( Body *b, real dt )
{
	if(b->im == 0.0f)
		return;

	b->position += b->velocity * dt;
	b->orient += b->angularVelocity * dt;
	b->SetOrient( b->orient );
	IntegrateForces( b, dt );
}


///////////////////////////////////
//update physics...
/////////////////////////////////// 

void World::Step( void )
{
	// Generate new collision info
	contacts.clear( );
	for(uint32 i = 0; i < bodies.size( ); ++i)
	{
		Body *A = bodies[i];

		for(uint32 j = i + 1; j < bodies.size( ); ++j)
		{
			Body *B = bodies[j];
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
		Body *b = bodies[i];
		b->force = Vec2( 0, 0 );
		b->torque = 0;
	}
}


// draw every change by this engine...
void World::Render( void )
{
	for(uint32 i = 0; i < bodies.size( ); ++i)
	{
		Body *b = bodies[i];
		b->rigBody->Draw();
	}

}

Body *World::Add(RigidBody *rigBody, uint32 x, uint32 y )
{
	assert( rigBody );
	Body *b = new Body(rigBody, x, y );
	bodies.push_back( b );
	return b;
}
