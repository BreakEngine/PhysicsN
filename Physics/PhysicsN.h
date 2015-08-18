#pragma once
#include "IEMath.h"

class PhysicsN
{
public:
	PhysicsN(void);
	~PhysicsN(void);



	void Update_physics();
	void Step( void );
	void IntegrateVelocity( Body2D *b, real dt );
	void IntegrateForces( Body2D *b, real dt );


	Body2D *Add(Collider::Type type ,vec2 _position , Vec2 Width_hight);
	Body2D *Add(Collider::Type type ,vec2 _position , real _radius);


	Clock _clock;
	Body2D *b;
	f32 m_dt;
	uint32 m_iterations;
	double accumulator;
	std::vector<Body2D*> bodies;
	std::vector<Manifold> contacts;
};

