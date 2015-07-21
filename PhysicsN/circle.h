#pragma once

#include "Precompiled.h"



class Circle : public Shape
{
public: 
	Circle( real r );

	Shape *Clone( void ) const;

	void Initialize( void );

	void ComputeMass( real density );

	void SetOrient( real Radians );

	void DSet_Orient( real Degree );

	void Draw( void ) const;

	Type GetType( void ) const;
};

