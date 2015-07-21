#include "Polygon.h"


PolygonShape::PolygonShape()
{
}

void PolygonShape::Initialize( void )
{
	ComputeMass(  1.0f );  //<<+++==============
}

Shape* PolygonShape::Clone( void ) const
{
	PolygonShape *poly = new PolygonShape( );
	poly->u = u;
	for(uint32 i = 0; i < m_vertexCount; ++i)
	{
		poly->m_vertices[i] = m_vertices[i];
		poly->m_normals[i] = m_normals[i];
	}
	poly->m_vertexCount = m_vertexCount;
	return poly;
}

void PolygonShape::ComputeMass( real density )
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

	body->m = density * area;
	body->im = (body->m) ? 1.0f / body->m : 0.0f;
	body->I = I * density;
	body->iI = body->I ? 1.0f / body->I : 0.0f;
}

void PolygonShape::SetOrient( real Radiance )
{
	u.Set(  Radiance );
}

void PolygonShape::DSet_Orient(real Degree )
{
	real rad = Degree * ( PI / 180);
	u.Set(  rad );
}


void PolygonShape::Draw( void ) const
{
	glColor3f( body->r, body->g, body->b );
	glBegin( GL_LINE_LOOP );
	for(uint32 i = 0; i < m_vertexCount; ++i)
	{
		Vec2 m = u * m_vertices[i] ;
		Vec2 v = body->position + u * m_vertices[i];
		glVertex2f( v.x, v.y );
	}
	glEnd( );
}

PolygonShape::Type  PolygonShape::GetType( void ) const
{
	return ePoly;
}

// Half width and half height
void PolygonShape::SetBox( real hw, real hh )
{
	m_vertexCount = 4;
	m_vertices[0] = glm::vec2( -hw, -hh );
	m_vertices[1] = glm::vec2(  hw, -hh );
	m_vertices[2] = glm::vec2(  hw,  hh );
	m_vertices[3] = glm::vec2( -hw,  hh );
	m_normals[0] = glm::vec2(  0.0f,  -1.0f );
	m_normals[1] = glm::vec2(  1.0f,   0.0f );
	m_normals[2] = glm::vec2(  0.0f,   1.0f );
	m_normals[3] = glm::vec2( -1.0f,   0.0f );
}

void PolygonShape::Set( Vec2 *vertices, uint32 count )
{
	// No hulls with less than 3 vertices (ensure actual polygon)
	assert( count > 2 && count <= MaxPolyVertexCount );
	count = std::min( (int32)count, MaxPolyVertexCount );

	// Find the right most point on the hull
	int32 rightMost = 0;
	real highestXCoord = vertices[0].x;
	for(uint32 i = 1; i < count; ++i)
	{
		real x = vertices[i].x;
		if(x > highestXCoord)
		{
			highestXCoord = x;
			rightMost = i;
		}

		// If matching x then take farthest negative y
		else if(x == highestXCoord)
			if(vertices[i].y < vertices[rightMost].y)
				rightMost = i;
	}

	int32 hull[MaxPolyVertexCount];
	int32 outCount = 0;
	int32 indexHull = rightMost;

	for (;;)
	{
		hull[outCount] = indexHull;

		// Search for next index that wraps around the hull
		// by computing cross products to find the most counter-clockwise
		// vertex in the set, given the previos hull index
		int32 nextHullIndex = 0;
		for(int32 i = 1; i < (int32)count; ++i)
		{
			// Skip if same coordinate as we need three unique
			// points in the set to perform a cross product
			if(nextHullIndex == indexHull)
			{
				nextHullIndex = i;
				continue;
			}

			// Cross every set of three unique vertices
			// Record each counter clockwise third vertex and add
			// to the output hull
			Vec2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
			Vec2 e2 = vertices[i] - vertices[hull[outCount]];
			real c = Cross( e1, e2 );
			if(c < 0.0f)
				nextHullIndex = i;

			// Cross product is zero then e vectors are on same line
			// therefor want to record vertex farthest along that line
			if(c == 0.0f && LenSqr( e2 ) > LenSqr( e1 ))
				nextHullIndex = i;
		}

		++outCount;
		indexHull = nextHullIndex;

		// Conclude algorithm upon wrap-around
		if(nextHullIndex == rightMost)
		{
			m_vertexCount = outCount;
			break;
		}
	}

	// Copy vertices into shape's vertices
	for(uint32 i = 0; i < m_vertexCount; ++i)
		m_vertices[i] = vertices[hull[i]];

	// Compute face normals
	for(uint32 i1 = 0; i1 < m_vertexCount; ++i1)
	{
		uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
		Vec2 face = m_vertices[i2] - m_vertices[i1];

		// Ensure no zero-length edges, because that's bad
		assert( LenSqr( face ) > EPSILON * EPSILON );

		// Calculate normal with 2D cross product between vector and scalar
		m_normals[i1] = Vec2( face.y, -face.x );
		m_normals[i1] = Normalize(  m_normals[i1] );
	}
}

// The extreme point along a direction within a polygon
Vec2 PolygonShape::GetSupport( const Vec2& dir )
{
	real bestProjection = -FLT_MAX;
	Vec2 bestVertex;

	for(uint32 i = 0; i < m_vertexCount; ++i)
	{
		Vec2 v = m_vertices[i];
		real projection = Dot( v, dir );

		if(projection > bestProjection)
		{
			bestVertex = v;
			bestProjection = projection;
		}
	}

	return bestVertex;
}