#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

// Function prototypes
std::string getFileContents(const char* filename);

/**
 * Shader Class
 */
class Shader {
	public: 
		GLuint ID;
		// Constructor
		Shader(const char* vertexFile, const char* fragmentFile);
		// Fucntion prototypes
		void Activate();
		void Delete();
}

#endif;