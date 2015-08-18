#pragma once
class Body2D;

class Shape
{
public:
	Shape(){}
	virtual void Initialize() = 0;
	virtual void Draw(GLuint programID , glm::mat4 VP , GLuint MatrixID )= 0;

	Body2D *body;

	uint32 m_vertexCount;
	Vec2 m_vertices[4];
	Vec2 m_normals [4];
};