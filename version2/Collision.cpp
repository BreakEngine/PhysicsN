#include "Precompiled.h"


void CircletoCircle( Manifold *m, Body *a, Body *b )
{
	// Calculate translational vector, which is normal
	Vec2 normal = b->position - a->position;

	real dist_sqr = LenSqr( normal );
	real radius = a->radius + b->radius;

	// Not in contact
	if(dist_sqr >= radius * radius)
	{
		m->contact_count = 0;
		return;
	}

	real distance = std::sqrt( dist_sqr );

	m->contact_count = 1;

	if(distance == 0.0f)
	{
		m->penetration = a->radius;
		m->normal = Vec2( 1, 0 );
		m->contacts [0] = a->position;
	}
	else
	{
		m->penetration = radius - distance;
		m->normal = normal / distance; // Faster than using Normalized since we already performed sqrt
		m->contacts[0] = m->normal * a->radius + a->position;
	}
}

void CircletoPolygon( Manifold *m, Body *a, Body *b )
{
	m->contact_count = 0;

	// Transform circle center to Polygon model space
	Vec2 center = a->position;
	center = b->u.Transpose( ) * (center - b->position);

	// Find edge with minimum penetration
	// Exact concept as using support points in Polygon vs Polygon
	real separation = -FLT_MAX;
	uint32 faceNormal = 0;
	for(uint32 i = 0; i < b->m_vertexCount; ++i)
	{
		real s = Dot( b->m_normals[i], center - b->m_vertices[i] );

		if(s > a->radius)
			return;

		if(s > separation)
		{
			separation = s;
			faceNormal = i;
		}
	}

	// Grab face's vertices
	Vec2 v1 = b->m_vertices[faceNormal];
	uint32 i2 = faceNormal + 1 < b->m_vertexCount ? faceNormal + 1 : 0;
	Vec2 v2 = b->m_vertices[i2];

	// Check to see if center is within polygon
	if(separation < EPSILON)
	{
		m->contact_count = 1;
		m->normal = -(b->u * b->m_normals[faceNormal]);
		m->contacts[0] = m->normal * a->radius + a->position;
		m->penetration = a->radius;
		return;
	}

	// Determine which voronoi region of the edge center of circle lies within
	real dot1 = Dot( center - v1, v2 - v1 );
	real dot2 = Dot( center - v2, v1 - v2 );
	m->penetration = a->radius - separation;

	// Closest to v1
	if(dot1 <= 0.0f)
	{
		if(DistSqr( center, v1 ) > a->radius * a->radius)
			return;

		m->contact_count = 1;
		Vec2 n = v1 - center;
		n = b->u * n;
		n = Normalize( n );
		m->normal = n;
		v1 = b->u * v1 + b->position;
		m->contacts[0] = v1;
	}

	// Closest to v2
	else if(dot2 <= 0.0f)
	{
		if(DistSqr( center, v2 ) > a->radius * a->radius)
			return;

		m->contact_count = 1;
		Vec2 n = v2 - center;
		v2 = b->u * v2 + b->position;
		m->contacts[0] = v2;
		n = b->u * n;
		n = Normalize( n );
		m->normal = n;
	}

	// Closest to face
	else
	{
		Vec2 n = b->m_normals[faceNormal];
		if(Dot( center - v1, n ) > a->radius)
			return;

		n = b->u * n;
		m->normal = -n;
		m->contacts[0] = m->normal * a->radius + a->position;
		m->contact_count = 1;
	}
}

void PolygontoCircle( Manifold *m, Body *a, Body *b )
{
	CircletoPolygon( m, b, a );
	m->normal = -m->normal;
}




real FindAxisLeastPenetration( uint32 *faceIndex, Body *A, Body *B )
{
	real bestDistance = -FLT_MAX;
	uint32 bestIndex;

	for(uint32 i = 0; i < A->m_vertexCount; ++i)
	{
		// Retrieve a face normal from A
		Vec2 n = A->m_normals[i];
		Vec2 nw = A->u * n;

		// Transform face normal into B's model space
		Mat2 buT = B->u.Transpose( );
		n = buT * nw;

		// Retrieve support point from B along -n
		real bestProjection = -FLT_MAX;
		Vec2 bestVertex;

		for(uint32 _i = 0; _i < B->m_vertexCount; ++_i)
		{
			Vec2 v = B->m_vertices[_i];
			real projection = Dot( v, -n );

			if(projection > bestProjection)
			{
				bestVertex = v;
				bestProjection = projection;
			}
		}

		Vec2 s = bestVertex;

		// Retrieve vertex on face from A, transform into
		// B's model space
		Vec2 v = A->m_vertices[i];
		v = A->u * v + A->position;
		v -= B->position;
		v = buT * v;

		// Compute penetration distance (in B's model space)
		real d = Dot( n, s - v );

		// Store greatest distance
		if(d > bestDistance)
		{
			bestDistance = d;
			bestIndex = i;
		}
	}

	*faceIndex = bestIndex;
	return bestDistance;
}

void FindIncidentFace( Vec2 *v, Body *RefPoly, Body *IncPoly, uint32 referenceIndex )
{
	Vec2 referenceNormal = RefPoly->m_normals[referenceIndex];

	// Calculate normal in incident's frame of reference
	referenceNormal = RefPoly->u * referenceNormal; // To world space
	referenceNormal = IncPoly->u.Transpose( ) * referenceNormal; // To incident's model space

	// Find most anti-normal face on incident polygon
	int32 incidentFace = 0;
	real minDot = FLT_MAX;
	for(uint32 i = 0; i < IncPoly->m_vertexCount; ++i)
	{
		real dot = Dot( referenceNormal, IncPoly->m_normals[i] );
		if(dot < minDot)
		{
			minDot = dot;
			incidentFace = i;
		}
	}

	// Assign face vertices for incidentFace
	v[0] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->position;
	incidentFace = incidentFace + 1 >= (int32)IncPoly->m_vertexCount ? 0 : incidentFace + 1;
	v[1] = IncPoly->u * IncPoly->m_vertices[incidentFace] + IncPoly->position;
}



int32 Clip( Vec2 n, real c, Vec2 *face )
{
	uint32 sp = 0;
	Vec2 out[2] = {
		face[0],
		face[1]
	};

	// Retrieve distances from each endpoint to the line
	// d = ax + by - c
	real d1 = Dot( n, face[0] ) - c;
	real d2 = Dot( n, face[1] ) - c;

	// If negative (behind plane) clip
	if(d1 <= 0.0f) out[sp++] = face[0];
	if(d2 <= 0.0f) out[sp++] = face[1];

	// If the points are on different sides of the plane
	if(d1 * d2 < 0.0f) // less than to ignore -0.0f
	{
		// Push interesection point
		real alpha = d1 / (d1 - d2);
		out[sp] = face[0] + alpha * (face[1] - face[0]);
		++sp;
	}

	// Assign our new converted values
	face[0] = out[0];
	face[1] = out[1];

	assert( sp != 3 );

	return sp;
}



void PolygontoPolygon( Manifold *m, Body *a, Body *b )
{
	m->contact_count = 0;

	// Check for a separating axis with A's face planes
	uint32 faceA;
	real penetrationA = FindAxisLeastPenetration( &faceA, a, b );
	if(penetrationA >= 0.0f)
		return;

	// Check for a separating axis with B's face planes
	uint32 faceB;
	real penetrationB = FindAxisLeastPenetration( &faceB, b, a );
	if(penetrationB >= 0.0f)
		return;

	uint32 referenceIndex;
	bool flip; // Always point from a to b

	Body *RefPoly; // Reference
	Body *IncPoly; // Incident

	// Determine which shape contains reference face
	if(BiasGreaterThan( penetrationA, penetrationB ))
	{
		RefPoly = a;
		IncPoly = b;
		referenceIndex = faceA;
		flip = false;
	}

	else
	{
		RefPoly = b;
		IncPoly = a;
		referenceIndex = faceB;
		flip = true;
	}

	// World space incident face
	Vec2 incidentFace[2];
	FindIncidentFace( incidentFace, RefPoly, IncPoly, referenceIndex );

	//        y
	//        ^  ->n       ^
	//      +---c ------posPlane--
	//  x < | i |\
	//      +---+ c-----negPlane--
	//             \       v
	//              r
	//
	//  r : reference face
	//  i : incident poly
	//  c : clipped point
	//  n : incident normal

	// Setup reference face vertices
	Vec2 v1 = RefPoly->m_vertices[referenceIndex];
	referenceIndex = referenceIndex + 1 == RefPoly->m_vertexCount ? 0 : referenceIndex + 1;
	Vec2 v2 = RefPoly->m_vertices[referenceIndex];

	// Transform vertices to world space
	v1 = RefPoly->u * v1 + RefPoly->position;
	v2 = RefPoly->u * v2 + RefPoly->position;

	// Calculate reference face side normal in world space
	Vec2 sidePlaneNormal = (v2 - v1);
	sidePlaneNormal = Normalize( sidePlaneNormal );

	// Orthogonalize
	Vec2 refFaceNormal( sidePlaneNormal.y, -sidePlaneNormal.x );

	// ax + by = c
	// c is distance from origin
	real refC = Dot( refFaceNormal, v1 );
	real negSide = -Dot( sidePlaneNormal, v1 );
	real posSide =  Dot( sidePlaneNormal, v2 );

	// Clip incident face to reference face side planes
	if(Clip( -sidePlaneNormal, negSide, incidentFace ) < 2)
		return; // Due to floating point error, possible to not have required points

	if(Clip(  sidePlaneNormal, posSide, incidentFace ) < 2)
		return; // Due to floating point error, possible to not have required points

	// Flip
	m->normal = flip ? -refFaceNormal : refFaceNormal;

	// Keep points behind reference face
	uint32 cp = 0; // clipped points behind reference face
	real separation = Dot( refFaceNormal, incidentFace[0] ) - refC;
	if(separation <= 0.0f)
	{
		m->contacts[cp] = incidentFace[0];
		m->penetration = -separation;
		++cp;
	}
	else
		m->penetration = 0;

	separation = Dot( refFaceNormal, incidentFace[1] ) - refC;
	if(separation <= 0.0f)
	{
		m->contacts[cp] = incidentFace[1];

		m->penetration += -separation;
		++cp;

		// Average penetration
		m->penetration /= (real)cp;
	}

	m->contact_count = cp;
}
