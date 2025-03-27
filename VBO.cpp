#include"VBO.h"

/**
* VBO constructor that generates a VBO object and links it to the vertices
* @param vertices - the vertices to be linked to the VBO
* @param size - the size of the vertices
*/
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Bind the VBO to the GL_ARRAY_BUFFER target
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbind the VBO from the GL_ARRAY_BUFFER target
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Delete the VBO from the GPU
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}
