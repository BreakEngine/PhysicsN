
#include "Precompiled.h"

Body::Body(RigidBody *_rigBody, uint32 x, uint32 y ) : radius(1) , density (1) , width (4) , hight (4)
{
	rigBody = _rigBody;
	rigBody->body = this;
	position = Vec2( (real)x, (real)y );
	velocity = Vec2( 0, 0 );
	angularVelocity = 0;
	torque = 0;
	orient = Random( -PI, PI );
	force = Vec2( 0, 0 );


	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.5f;

	
		m_vertexCount = 4;
		m_vertices[0] = glm::vec2( -width, -hight );
		m_vertices[1] = glm::vec2(  width, -hight );
		m_vertices[2] = glm::vec2(  width,  hight );
		m_vertices[3] = glm::vec2( -width,  hight );
		m_normals[0]  = glm::vec2(  0.0f,  -1.0f );
		m_normals[1]  = glm::vec2(  1.0f,   0.0f );
		m_normals[2]  = glm::vec2(  0.0f,   1.0f );
		m_normals[3]  = glm::vec2( -1.0f,   0.0f );


	if(_type == RigidBody::eCircle)
	{
		m = PI * radius * radius * density;
		im = (m) ? 1.0f / m : 0.0f;
		I = m * radius * radius;
		iI = (I) ? 1.0f / I : 0.0f;
	}
	else if(_type == RigidBody::ePoly)
	{
		// Calculate centroid and moment of interia
		Vec2 c( 0.0f, 0.0f ); // centroid
		real area = 0.0f;
		real I = 0.0f;
		const real k_inv3 = 1.0f / 3.0f;

		for(uint32 i1 = 0; i1 < m_vertexCount; ++i1)
		{
			// Triangle vertices, third vertex implied as (0, 0)
			Vec2 p1( m_vertices[i1] );
			uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
			Vec2 p2( m_vertices[i2] );

			real D = Cross( p1, p2 );
			real triangleArea = 0.5f * D;

			area += triangleArea;

			// Use area to weight the centroid average, not just vertex position
			c += triangleArea * k_inv3 * (p1 + p2);

			real intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
			real inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
			I += (0.25f * k_inv3 * D) * (intx2 + inty2);
		}

		c *= 1.0f / area;

		// Translate vertices to centroid (make the centroid (0, 0)
		// for the polygon in model space)
		// Not really necessary, but I like doing this anyway
		for(uint32 i = 0; i < m_vertexCount; ++i)
			m_vertices[i] -= c;

		m = density * area;
		im = (m) ? 1.0f / m : 0.0f;
		I = I * density;
		iI = I ? 1.0f / I : 0.0f;

	}
	else
	{
		m = 5;
		im = 0.5;
		I = 0.5;
		iI = 0.5;
	}


	r = Random( 0.2f, 1.0f );
	g = Random( 0.2f, 1.0f );
	b = Random( 0.2f, 1.0f );
}

void Body::SetColliderType(RigidBody::Type type)
{
	_type = type;
}

RigidBody::Type Body::GetColliderType()
{
	return _type;
}

void Body::SetOrient( real Degree )
{
	orient = Degree;
	u.Set(  orient );
}

void Body::ApplyForce( const Vec2& f )
{
	force += f;
}

void Body::ApplyImpulse( const Vec2& impulse, const Vec2& contactVector )
{
	velocity += im * impulse;
	angularVelocity += iI * Cross( contactVector, impulse );
}

void Body::SetStatic( void )
{
	I = 0.0f;
	iI = 0.0f;
	m =  0.0f;
	im = 0.0f;
}
