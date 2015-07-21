#include "circle.h"



Circle::Circle( real r )
{
	radius = r;
}

Shape* Circle::Clone( void ) const
{
	return new Circle( radius );
}

void Circle::Initialize( void )
{
	ComputeMass( 1.0f );
}

void Circle::ComputeMass( real density )
{
	body->m = PI * radius * radius * density;
	body->im = (body->m) ? 1.0f / body->m : 0.0f;
	body->I = body->m * radius * radius;
	body->iI = (body->I) ? 1.0f / body->I : 0.0f;
}

void Circle::SetOrient( real Radians )
{
}

void Circle::DSet_Orient(real Degree)
{
}

void Circle::Draw( void ) const
{
	const uint32 k_segments = 20;

	// Render a circle with a bunch of lines
	glColor3f( body->r, body->g, body->b );

	glBegin( GL_LINE_LOOP );
	real theta = body->orient;
	real inc = PI * 2.0f / (real)k_segments;
	for(uint32 i = 0; i < k_segments; ++i)
	{
		theta += inc;
		Vec2 p( std::cos( theta ), std::sin( theta ) );
		p *= radius;
		p += body->position;
		glVertex2f( p.x, p.y );
	}
	glEnd( );


	// Render line within circle so orientation is visible
	glBegin( GL_LINE_STRIP );
	Vec2 r( 0, 1.0f );
	real c = std::cos( body->orient );
	real s = std::sin( body->orient );
	r = Vec2( r.x * c - r.y * s, r.x * s + r.y * c );
	r *= radius;
	r = r + body->position;
	glVertex2f( body->position.x, body->position.y );
	glVertex2f( r.x, r.y );
	glEnd( );
}

Circle::Type Circle::GetType( void ) const
{
	return eCircle;
}