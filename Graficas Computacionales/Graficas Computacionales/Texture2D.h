#pragma once

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>

class Texture2D 
{
public:
	Texture2D();
	~Texture2D();
	void LoadTexture(std::string path);
	void Bind();
	void Unbind();
private:
	GLuint _textureId;
};