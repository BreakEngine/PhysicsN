#pragma once
#include "IShape.h"

class Circle : public Shape
{
public:
	Circle(void);
	~Circle(void);


	void Initialize();

	void Draw(GLuint programID , glm::mat4 VP , GLuint MatrixID );


private:
	GLuint vertexbuffer;
};

