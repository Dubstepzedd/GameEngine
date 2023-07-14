#include "model.h"
#include <GL/glew.h>
#include <iostream>

void Model::draw() {
	std::cout << this->size / (sizeof(float) * this->attribSize) << std::endl;
	glBindVertexArray(this->vao);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, this->size / (sizeof(float) * this->attribSize)); //TODO Hardcoded
	glBindVertexArray(0);
}

void Model::create(float vertices[], unsigned int size, unsigned int attribSize) {
	this->size = size;
	this->attribSize = attribSize;

	glGenVertexArrays(1, &(this->vao));
	glBindVertexArray(this->vao);

	glGenBuffers(1, &(this->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, attribSize, GL_FLOAT, GL_FALSE, attribSize * sizeof(float), 0); //TODO Hardcoded

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}