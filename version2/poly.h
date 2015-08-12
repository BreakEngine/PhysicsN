#pragma once

#include "Precompiled.h"

/*
polygon example ,,,
*/
class soso : public RigidBody
{
public:
	soso(){}
	~soso(){}

	void Draw( void ) const;


};



void soso::Draw( void ) const
{
	glColor3f( body->r, body->g, body->b );
	glBegin( GL_LINE_LOOP );
	for(uint32 i = 0; i < body->m_vertexCount; ++i)
	{
		Vec2 v = body->position + body->u * body->m_vertices[i];
		glVertex2f( v.x, v.y );
	}
	glEnd( );
}