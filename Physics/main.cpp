#include <vld.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
#include <stdlib.h>
#include <string.h>
#include "EngineFiles.h"

GLFWwindow* window;
glm::mat4 Projection;
glm::mat4 View ;
GLuint programID;
GLuint MatrixID;
GLuint VertexArrayID;
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);


PhysicsN *phys;

glm::mat4 vp;

glm::mat4 circmodel;
Body2D *_bodyCircle;


Body2D *_body;
Body2D *_body2;
Body2D *_body3;

void init()
{

	 phys= new PhysicsN();


	_bodyCircle = phys->Add(Collider::Circular , glm::vec2(31.0f,0.0f) , 3);

	
	_body = phys->Add(Collider::Rectangles,glm::vec2(0.0f,0.0f) , glm::vec2( 2 , 2) );

	_body2 = phys->Add(Collider::Rectangles,glm::vec2(0.0f,50.0f) , glm::vec2( 30 , 2));
	_body2->SetStatic();



	_body3 = phys->Add(Collider::Rectangles,glm::vec2(31.0f,20.0f) ,glm::vec2( 2 , 2));

}


void update()
{

	if(  glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS )
	{
		Body2D *b;
		b = phys->Add(Collider::Circular, glm::vec2(0.0f,0.0f) , 3);
	}

	phys->Update_physics();
}

void Draw()
{
	vp = Projection * View ;

	for(int i=0 ; i < phys->bodies.size() ; i++)
	{
		phys->bodies[i]->RigidBody->Draw(programID , vp , MatrixID);
	}

}








int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 800, 600, "PhysicsN Opengl 3.3", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. \n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	programID = LoadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader" );


	MatrixID = glGetUniformLocation(programID, "MVP");


	Projection = glm::ortho(100.0f,-100.0f,100.0f,-100.0f,0.0f,100.0f); // In world coordinates
	//glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	View = glm::lookAt(
		glm::vec3(0,0,3), 
		glm::vec3(0,0,0), 
		glm::vec3(0,1,0));
	init();


	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );
		// Dark blue background
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		update();
		Draw();


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0 );

	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	delete phys;
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}



	GLint Result = GL_FALSE;
	int InfoLogLength;



	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}