#include "EngineFiles.h"


Poly::Poly(void)
{
}


Poly::~Poly(void)
{
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
}


void Poly::Initialize()
{
	static const GLfloat g_vertex_buffer_data[] = 
	{ 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  -1.0f, 0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	m_vertexCount = 4;
	m_vertices[0] = glm::vec2( -body->width, -body->hight );
	m_vertices[1] = glm::vec2(  body->width, -body->hight );
	m_vertices[2] = glm::vec2(  body->width,  body->hight );
	m_vertices[3] = glm::vec2( -body->width,  body->hight );
	m_normals[0]  = glm::vec2(  0.0f,  -1.0f );
	m_normals[1]  = glm::vec2(  1.0f,   0.0f );
	m_normals[2]  = glm::vec2(  0.0f,   1.0f );
	m_normals[3]  = glm::vec2( -1.0f,   0.0f );

}

void Poly::Draw(GLuint programID , glm::mat4 VP , GLuint MatrixID )
{
	glUseProgram(programID);


	VP *= translate(body->position.x , body->position.y , 0.0f ) * rotate((body->orient * 180 ) / PI , 0.0f,0.0f,1.0f) * scale(body->width,body->hight,1.0f);

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, (void*)0);

	// Draw the triangle !
	glDrawArrays(GL_LINE_LOOP, 0, 6); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
}
