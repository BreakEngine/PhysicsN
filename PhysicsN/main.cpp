#include "PhysicsN.h"

#define ESC_KEY 27

PhysicsN *phys;
Body *body;

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
				glm::vec2 _vec = m - body->position ;
				_vec *= 500; 
				body->ApplyForce(_vec);


				//  //create polygon ...
				//      PolygonShape poly;
				//      uint32 count = (uint32)Random( 3, MaxPolyVertexCount );
				//      Vec2 *vertices = new Vec2[count];

				//      real e = Random( 5, 10 );

				//      for(uint32 i = 0; i < count; ++i)
				//	vertices[i] = glm::vec2( Random( -e, e ), Random( -e, e ) );


				//      poly.Set( vertices, count );

				//Body *b = phys->Add_Body(&poly, glm::vec2(x,y));        // scene.Add( &poly, x, y );

				/////physics probs...
				//      b->SetOrient( Random( -PI, PI ) );
				//      b->restitution = 0.2f;
				//      b->dynamicFriction = 0.2f;
				//      b->staticFriction = 0.4f;
				//      delete [] vertices;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			{
				Circle c( 1.0f );
				body = phys->Add_Body(&c, glm::vec2(x,y));        //scene.Add( &c, x, y );
			}
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

	phys->Update_Physics();


	phys->Render_Physics();

	glutSwapBuffers( );
}






int main(int argc, char** argv)
{
	phys = new PhysicsN();
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "PhyEngine" );


	//  update function
	glutDisplayFunc( PhysicsLoop );


	//input
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



	PolygonShape box;  // as box static...
	box.SetBox( 3.0f, 2.0f );
	Body *bo =  phys->Add_Body(&box, glm::vec2(20,60));
	bo->SetOrient( 0 );
	bo->dynamicFriction = 0.2f;
	bo->staticFriction = 0.4f;

	PolygonShape box2;  // as box static...
	box2.SetBox( 2.0f, 2.0f );
	Body *bo2 =  phys->Add_Body(&box2, glm::vec2(20,55));
	bo2->SetOrient( 0 );
	bo2->dynamicFriction = 0.2f;
	bo2->staticFriction = 0.4f;

	PolygonShape box3;  // as box static...
	box3.SetBox( 1.0f, 1.0f );
	Body *bo3 =  phys->Add_Body(&box3, glm::vec2(20,40));
	bo3->SetOrient( 0 );
	bo3->dynamicFriction = 0.2f;
	bo3->staticFriction = 0.4f;

	//PolygonShape box4;  // as box static...
	//box4.SetBox( 1.0f, 1.0f );
	//Body *bo4 =  phys->Add_Body(&box4, glm::vec2(20,45));
	//bo4->SetOrient( 0 );
	//bo4->dynamicFriction = 0.2f;
	//bo4->staticFriction = 0.4f;


	//PolygonShape box5;  // as box static...
	//box5.SetBox( 2.0f, 2.0f );
	//Body *bo5 =  phys->Add_Body(&box5, glm::vec2(20,60));
	//bo5->SetOrient( 0 );
	//bo5->restitution = 0;



	/////////////////////////////////////////////////////////////////////////////////////////
	/// ground ...

	//polygon object ... 
	PolygonShape poly;  // as box static...
	poly.SetBox( 50.0f, 1.0f );
	Body *b =  phys->Add_Body(&poly, glm::vec2(40,60));                    //scene.Add( &poly, 40, 55 );
	b->SetStatic( );
	b->SetOrient( 0 );

	PolygonShape poly2;  // as box static...
	poly2.SetBox( 30.0f, 1.0f );
	Body *b2 =  phys->Add_Body(&poly2, glm::vec2(80,30));                    //scene.Add( &poly, 40, 55 );
	b2->SetStatic( );
	b2->SetOrient( 90 );


	PolygonShape poly3;  // as box static...
	poly3.SetBox( 30.0f, 1.0f );
	Body *b3 =  phys->Add_Body(&poly3, glm::vec2(0,30));                    //scene.Add( &poly, 40, 55 );
	b3->SetStatic( );
	b3->SetOrient( 90 );

	srand( 1 );
	glutMainLoop( );

	return 0;
}



//
//#include "Precompiled.h"
//
//#define ESC_KEY 27
//
//Scene scene( 1.0f / 60.0f, 10 );
//
//Clock g_Clock;
//
//bool frameStepping = false;
//bool canStep = false;
//
/////////////////////////////////////////////////
////mouse handling input.....
////////////////////////////////////////////////
//void Mouse( int button, int state, int x, int y )
//{
//  x /= 10.0f;
//  y /= 10.0f;
//
//  if(state == GLUT_DOWN)
//    switch(button)
//    {
//    case GLUT_LEFT_BUTTON:
//      {
//
//		  //create polygon ...
//        PolygonShape poly;
//        uint32 count = (uint32)Random( 3, MaxPolyVertexCount );
//        Vec2 *vertices = new Vec2[count];
//
//        real e = Random( 5, 10 );
//
//        for(uint32 i = 0; i < count; ++i)
//			vertices[i] = glm::vec2( Random( -e, e ), Random( -e, e ) );
//
//
//        poly.Set( vertices, count );
//
//        Body *b = scene.Add( &poly, x, y );
//
//		///physics probs...
//        b->SetOrient( Random( -PI, PI ) );
//        b->restitution = 0.2f;
//        b->dynamicFriction = 0.2f;
//        b->staticFriction = 0.4f;
//        delete [] vertices;
//      }
//      break;
//    case GLUT_RIGHT_BUTTON:
//      {
//        Circle c( Random( 1.0f, 3.0f ) );
//        Body *b = scene.Add( &c, x, y );
//      }
//      break;
//    }
//}
//
//
////////////////////////////////////////////////////////
////Keyboard handling input...
////////////////////////////////////////////////////////
//
//void Keyboard(unsigned char key, int x, int y)
//{
//  switch(key)
//  {
//  case ESC_KEY:
//    exit( 0 );
//    break;
//  case 's':
//    {
//      //Circle c( 25.0f );
//      //scene.Add( &c, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
//      //OBB obb;
//      //real e = Random( 10.0f, 35.0f );
//      //obb.extents.Set( e, e );
//      //Body *b = scene.Add( &obb, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
//      //b->SetOrient( PI / 4.0f );
//      //b->restitution = 0.2f;
//      //b->dynamicFriction = 0.2f;
//      //b->staticFriction = 0.4f;
//    }
//    break;
//  case 'd':
//    {
//      //Circle c( 25.0f );
//      //scene.Add( &c, 420, 50 );
//    }
//      break;
//  case 'f':
//    frameStepping = frameStepping ? false : true;
//      break;
//  case ' ':
//    canStep = true;
//    break;
//  }
//}
//
//
//
////////////////////////////////////////////////////////////
////    main physics update....
/////////////////////////////////////////////////////
//
//void PhysicsLoop( void )
//{
//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//  glClearColor(0,0,0.5,0);
//  //RenderString( 1, 2, "Left click to spawn a polygon" );
//  //RenderString( 1, 4, "Right click to spawn a circle" );
//
//  static double accumulator = 0;
//
//  // Different time mechanisms for Linux and Windows
//#ifdef WIN32
//  accumulator += g_Clock.Elapsed( );
//#else
//  accumulator += g_Clock.Elapsed( ) / static_cast<double>(std::chrono::duration_cast<clock_freq>(std::chrono::seconds(1)).count());
//#endif
//
//  g_Clock.Start( );
//
//  accumulator = Clamp( 0.0f, 0.1f, accumulator );
//  while(accumulator >= dt)
//  {
//    if(!frameStepping)
//      scene.Step( );
//    else
//    {
//      if(canStep)
//      {
//        scene.Step( );
//        canStep = false;
//      }
//    }
//    accumulator -= dt;
//  }
//
//  g_Clock.Stop( );
//
//  scene.Render( );
//
//  glutSwapBuffers( );
//}
//
//
//
//
//
//
//int main(int argc, char** argv)
//{
//  glutInit(&argc, argv);
//  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
//  glutInitWindowSize( 800, 600 );
//  glutCreateWindow( "PhyEngine" );
//
//
//  //  update function
//  glutDisplayFunc( PhysicsLoop );
//
//
//  //input
//  glutKeyboardFunc( Keyboard );
//  glutMouseFunc( Mouse );
//
//  //idle
//  glutIdleFunc( PhysicsLoop );
//
//
//
//  //  mvp or view matrix....
//  glMatrixMode( GL_PROJECTION );
//  glPushMatrix( );
//  glLoadIdentity( );
//  gluOrtho2D( 0, 80, 60, 0 );
//  glMatrixMode( GL_MODELVIEW );
//  glPushMatrix( );
//  glLoadIdentity( );
//
//
//
//  //circle object ... radious = 0.5;
//  Circle c( 5.0f );
//  Body *b = scene.Add( &c, 60, 40 );  //mark this circle as body 
//  b->SetStatic( );                    // set this body as static... no physics
//
//  Circle c2( 5.0f );
//  Body *_b = scene.Add( &c2, 20, 40 );  //mark this circle as body 
//  _b->SetStatic( );                    // set this body as static... no physics
//
//  //polygon object ... 
//  PolygonShape poly;  // as box static...
//  poly.SetBox( 30.0f, 1.0f );
//  b = scene.Add( &poly, 40, 55 );
//  b->SetStatic( );
//  b->SetOrient( 0 );
//
//  srand( 1 );
//  glutMainLoop( );
//
//  return 0;
//}









//#include "Precompiled.h"
//
//#define ESC_KEY 27
//
//Scene scene( 1.0f / 60.0f, 10 );
//
//Clock g_Clock;
//
//bool frameStepping = false;
//bool canStep = false;
//
/////////////////////////////////////////////////
////mouse handling input.....
////////////////////////////////////////////////
//void Mouse( int button, int state, int x, int y )
//{
//  x /= 10.0f;
//  y /= 10.0f;
//
//  if(state == GLUT_DOWN)
//    switch(button)
//    {
//    case GLUT_LEFT_BUTTON:
//      {
//
//		  //create polygon ...
//        PolygonShape poly;
//        uint32 count = (uint32)Random( 3, MaxPolyVertexCount );
//        Vec2 *vertices = new Vec2[count];
//
//        real e = Random( 5, 10 );
//
//        for(uint32 i = 0; i < count; ++i)
//			vertices[i] = glm::vec2( Random( -e, e ), Random( -e, e ) );
//
//
//        poly.Set( vertices, count );
//
//        Body *b = scene.Add( &poly, x, y );
//
//		///physics probs...
//        b->SetOrient( Random( -PI, PI ) );
//        b->restitution = 0.2f;
//        b->dynamicFriction = 0.2f;
//        b->staticFriction = 0.4f;
//        delete [] vertices;
//      }
//      break;
//    case GLUT_RIGHT_BUTTON:
//      {
//        Circle c( Random( 1.0f, 3.0f ) );
//        Body *b = scene.Add( &c, x, y );
//      }
//      break;
//    }
//}
//
//
////////////////////////////////////////////////////////
////Keyboard handling input...
////////////////////////////////////////////////////////
//
//void Keyboard(unsigned char key, int x, int y)
//{
//  switch(key)
//  {
//  case ESC_KEY:
//    exit( 0 );
//    break;
//  case 's':
//    {
//      //Circle c( 25.0f );
//      //scene.Add( &c, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
//      //OBB obb;
//      //real e = Random( 10.0f, 35.0f );
//      //obb.extents.Set( e, e );
//      //Body *b = scene.Add( &obb, 400 + (rand( ) % 250) * ((rand( ) % 2 == 1) ? 1 : -1), 50 );
//      //b->SetOrient( PI / 4.0f );
//      //b->restitution = 0.2f;
//      //b->dynamicFriction = 0.2f;
//      //b->staticFriction = 0.4f;
//    }
//    break;
//  case 'd':
//    {
//      //Circle c( 25.0f );
//      //scene.Add( &c, 420, 50 );
//    }
//      break;
//  case 'f':
//    frameStepping = frameStepping ? false : true;
//      break;
//  case ' ':
//    canStep = true;
//    break;
//  }
//}
//
//
//
////////////////////////////////////////////////////////////
////    main physics update....
/////////////////////////////////////////////////////
//
//void PhysicsLoop( void )
//{
//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//  glClearColor(0,0,0.5,0);
//  //RenderString( 1, 2, "Left click to spawn a polygon" );
//  //RenderString( 1, 4, "Right click to spawn a circle" );
//
//  static double accumulator = 0;
//
//  // Different time mechanisms for Linux and Windows
//#ifdef WIN32
//  accumulator += g_Clock.Elapsed( );
//#else
//  accumulator += g_Clock.Elapsed( ) / static_cast<double>(std::chrono::duration_cast<clock_freq>(std::chrono::seconds(1)).count());
//#endif
//
//  g_Clock.Start( );
//
//  accumulator = Clamp( 0.0f, 0.1f, accumulator );
//  while(accumulator >= dt)
//  {
//    if(!frameStepping)
//      scene.Step( );
//    else
//    {
//      if(canStep)
//      {
//        scene.Step( );
//        canStep = false;
//      }
//    }
//    accumulator -= dt;
//  }
//
//  g_Clock.Stop( );
//
//  scene.Render( );
//
//  glutSwapBuffers( );
//}
//
//
//
//
//
//
//int main(int argc, char** argv)
//{
//  glutInit(&argc, argv);
//  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
//  glutInitWindowSize( 800, 600 );
//  glutCreateWindow( "PhyEngine" );
//
//
//  //  update function
//  glutDisplayFunc( PhysicsLoop );
//
//
//  //input
//  glutKeyboardFunc( Keyboard );
//  glutMouseFunc( Mouse );
//
//  //idle
//  glutIdleFunc( PhysicsLoop );
//
//
//
//  //  mvp or view matrix....
//  glMatrixMode( GL_PROJECTION );
//  glPushMatrix( );
//  glLoadIdentity( );
//  gluOrtho2D( 0, 80, 60, 0 );
//  glMatrixMode( GL_MODELVIEW );
//  glPushMatrix( );
//  glLoadIdentity( );
//
//
//
//  //circle object ... radious = 0.5;
//  Circle c( 5.0f );
//  Body *b = scene.Add( &c, 60, 40 );  //mark this circle as body 
//  b->SetStatic( );                    // set this body as static... no physics
//
//  Circle c2( 5.0f );
//  Body *_b = scene.Add( &c2, 20, 40 );  //mark this circle as body 
//  _b->SetStatic( );                    // set this body as static... no physics
//
//  //polygon object ... 
//  PolygonShape poly;  // as box static...
//  poly.SetBox( 30.0f, 1.0f );
//  b = scene.Add( &poly, 40, 55 );
//  b->SetStatic( );
//  b->SetOrient( 0 );
//
//  srand( 1 );
//  glutMainLoop( );
//
//  return 0;
//}
