#pragma once
class Body2D;


class Manifold
{
public:
	Manifold( Body2D *a, Body2D *b ) : A( a ) , B( b ){}

	void Solve( void );                 // Generate contact information
	void Initialize( void );            // Precalculations for impulse solving
	void ApplyImpulse( void );          // Solve impulse and apply
	void PositionalCorrection( void );  // Naive correction of positional penetration
	void InfiniteMassCorrection( void );

	Body2D *A;
	Body2D *B;

	

	real penetration;     // Depth of penetration from collision
	Vec2 normal;          // From A to B
	Vec2 contacts[2];     // Points of contact during collision
	uint32 contact_count; // Number of contacts that occured during collision
	real e;               // Mixed restitution
	real df;              // Mixed dynamic friction
	real sf;              // Mixed static friction
};