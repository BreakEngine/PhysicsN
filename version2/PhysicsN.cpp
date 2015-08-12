#include "PhysicsN.h"


PhysicsN::PhysicsN(void)
{
	_Pause = false;
    canStep = false;

	 accumulator = 0;

	dt =  1.0f / 60.0f;
	itrations =  10;
	scene = new World( dt, itrations );
}


PhysicsN::~PhysicsN(void)
{
	delete scene;
}


Body* PhysicsN::Add_Body(RigidBody *_rigBody , glm::vec2 _position)
{
	Body *body;
	body = scene->Add(_rigBody,_position.x, _position.y);

	return body;
}

void PhysicsN::Update_Physics()
{

	accumulator += _clock.Elapsed();


	/////////////////////////////// updating physics
	_clock.Start();
  accumulator = Clamp( 0.0f, 0.1f, accumulator );
  while(accumulator >= dt)
  {
	  if(!_Pause)
      scene->Step( );
    else
    {
      if(canStep)
      {
        scene->Step( );
        canStep = false;
      }
    }
    accumulator -= dt;
  }

  _clock.Stop();
}

void PhysicsN::Render_Physics()
{
	scene->Render();
}

void PhysicsN::Pause_Physics()
{
	_Pause = true;
}

void PhysicsN::Play_Physics()
{
	_Pause = false;
}
