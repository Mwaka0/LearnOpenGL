#include"shaderClass.h"

/**
 * getFileContents
 */
std::string getFileContents(const char* filename) {
	std::ifstream file(filename, std::ios::binary);
	if (file) {
		std::string contents;
		file.seekg(0, std::ios::end);
		contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&contents[0], contents.size());
		file.close();
		return contents;
	} 
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create a vertex buffer object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach the shader source code to the shader object and compile the shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the shader
	glCompileShader(vertexShader);
	// Check for shader compile errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	// If the compilation failed, print the error message
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create a fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	// Check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	// If the compilation failed, print the error message
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create a shader program
	ID = glCreateProgram();
	
	// Attach the vertex and fragment shaders to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Link the shaders
	glLinkProgram(ID);

	// Check for linking errors	
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}