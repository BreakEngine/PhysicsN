

#ifndef COLLISION_H
#define COLLISION_H

class Manifold;
class Body2D;


void CircletoCircle( Manifold *m, Body2D *a, Body2D *b );
void CircletoPolygon( Manifold *m, Body2D *a, Body2D *b );
void PolygontoCircle( Manifold *m, Body2D *a, Body2D *b );
void PolygontoPolygon( Manifold *m, Body2D *a, Body2D *b );

#endif // COLLISION_H