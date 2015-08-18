#include "EngineFiles.h"


Circle::Circle(void)
{
}


Circle::~Circle(void)
{
}

void Circle::Initialize()
{
	static GLfloat g_vertex_buffer_data[100];

	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	for(i = 0; i <= lineAmount; i+=3) 
	{ 
		//glVertex2f(x + (3 * cos(i *  twicePi / lineAmount)), y + (3* sin(i * twicePi / lineAmount)));
		g_vertex_buffer_data[i] = (body->radius * cos(i *  twicePi / lineAmount));
		g_vertex_buffer_data[i+1] = (body->radius* sin(i * twicePi / lineAmount));
		g_vertex_buffer_data[i+2] = 0.0f;
	}


	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Circle::Draw(GLuint programID , glm::mat4 VP , GLuint MatrixID )
{

	glUseProgram(programID);

	VP *= translate(body->position.x , body->position.y , 0.0f ) *  rotate((body->orient * 180 ) / PI , 0.0f,0.0f,1.0f);


	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, (void*)0);

	// Draw the triangle !
	glDrawArrays(GL_LINE_STRIP, 0, 100); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
}


