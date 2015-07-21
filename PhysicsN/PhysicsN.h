#pragma once
#include "Precompiled.h"

class PhysicsN
{
private:
	float dt;
	float itrations;
	Scene *scene;

	bool _Pause;
	bool canStep;
    double accumulator;
public:
	PhysicsN();
	~PhysicsN(void);

	Clock _clock;

	Body* Add_Body(Shape *_shape , glm::vec2 _position);
	void Update_Physics();
	void Render_Physics();


	void Pause_Physics();
	void Play_Physics();
};

