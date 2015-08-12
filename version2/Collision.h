

#ifndef COLLISION_H
#define COLLISION_H

class Manifold;
class Body;


void CircletoCircle( Manifold *m, Body *a, Body *b );
void CircletoPolygon( Manifold *m, Body *a, Body *b );
void PolygontoCircle( Manifold *m, Body *a, Body *b );
void PolygontoPolygon( Manifold *m, Body *a, Body *b );

#endif // COLLISION_H