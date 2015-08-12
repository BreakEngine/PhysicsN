#pragma once

class Body;

class RigidBody
{
public:
	enum Type
	{
		eCircle,
		ePoly
	};

	RigidBody( ) {}

	virtual void Draw( void ) const = 0;

	Body *body;
};













