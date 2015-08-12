#include <vld.h>

#include "PhysicsN.h"

#include "circ.h"
#include "poly.h"


#define ESC_KEY 27

PhysicsN *phys;          


koko *c;   //circle object



///////////////////////////////////////////////
//mouse handling input.....
//////////////////////////////////////////////
void Mouse( int button, int state, int x, int y )
{
	x /= 10.0f;
	y /= 10.0f;

	if(state == GLUT_DOWN)
		switch(button)
	{
		case GLUT_LEFT_BUTTON:
			{

				glm::vec2 m = glm::vec2(x,y);
				glm::vec2 _vec = m - c->body->position ;
				_vec *= 500; 
				c->body->ApplyForce(_vec);

			}
			break;
		case GLUT_RIGHT_BUTTON:
			{
				c = new koko();
				c->body = phys->Add_Body(c, glm::vec2(x,y));        //scene.Add( &c, x, y );
				c->body->SetColliderType(RigidBody::eCircle);
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			{
				soso *poly = new soso();  // as box static...

				poly->body =  phys->Add_Body(poly, glm::vec2(x,y));    
				poly->body->SetColliderType(RigidBody::ePoly);
				poly->body->SetOrient( 0 );
			}
			break;
	}
}


void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case ESC_KEY:
		delete phys;
		exit( 0 );
		break;
	}
}


//////////////////////////////////////////////////////////
//    main physics update....
///////////////////////////////////////////////////

void PhysicsLoop( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glClearColor(0,0,0.5,0);

	phys->Update_Physics();   ///<<========= 3


	phys->Render_Physics();    ///<<======== 4

	glutSwapBuffers( );
}






int main(int argc, char** argv)
{
	phys = new PhysicsN();  //<<============= 2


	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "PhyEngine" );


	//  update function
	glutDisplayFunc( PhysicsLoop );


	//input
	glutKeyboardFunc( Keyboard );
	glutMouseFunc( Mouse );

	//idle
	glutIdleFunc( PhysicsLoop );



	//  mvp or view matrix....
	glMatrixMode( GL_PROJECTION );
	glPushMatrix( );
	glLoadIdentity( );
	gluOrtho2D( 0, 80, 60, 0 );
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix( );
	glLoadIdentity( );



	soso *box = new soso();
	box->body =  phys->Add_Body(box, glm::vec2(35,30));

	box->body->SetColliderType(RigidBody::ePoly);
	box->body->SetOrient( 0 );
	box->body->width = 5;



	/////////////////////////////////////////////////////////////////////////////////////////
	/// ground ...

	//polygon object ... 
	soso *poly = new soso();  

	poly->body =  phys->Add_Body(poly, glm::vec2(40,60));            
	poly->body->SetColliderType(RigidBody::ePoly);
	poly->body->SetStatic( );
	poly->body->SetOrient( 0 );
	poly->body->width = 5;

	soso *poly2  = new soso();  

	poly2->body =  phys->Add_Body(poly2, glm::vec2(80,30));             
	poly2->body->SetColliderType(RigidBody::ePoly);
	poly2->body->SetStatic( );
	poly2->body->SetOrient( 0 );
	poly2->body->width = 5;


	soso *poly3  = new soso(); 

	poly3->body =  phys->Add_Body(poly3, glm::vec2(0,30));                    
	poly3->body->SetColliderType(RigidBody::ePoly);
	poly3->body->SetStatic( );
	poly3->body->SetOrient( 0 );
	poly3->body->width = 5;

	srand( 1 );
	glutMainLoop( );

	return 0;
}


