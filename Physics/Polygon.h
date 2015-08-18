#pragma once
#include "IShape.h"

class Poly : public Shape
{
public:
	Poly(void);
	~Poly(void);


	void Initialize();

	void Draw(GLuint programID , glm::mat4 VP , GLuint MatrixID );

private:
	GLuint vertexbuffer;
};

