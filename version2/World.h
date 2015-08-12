#include "IEMath.h"


class World
{
public:
	World( f32 dt, uint32 iterations ) : m_dt( dt ) , m_iterations( iterations ) {}
	~World()
	{
		for(int i = 0 ; i < bodies.size() ; ++i)
		{
			delete bodies[i];
		}
	}

	void Step( void );
	void Render( void );
	Body *Add( RigidBody *rigBody, uint32 x, uint32 y );
	void Clear( void );

	f32 m_dt;
	uint32 m_iterations;
	std::vector<Body *> bodies;
	std::vector<Manifold> contacts;
};