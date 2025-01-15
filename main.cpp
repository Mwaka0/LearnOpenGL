#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// Shader sources
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);\n"
"}\n\0";

// Function prototypes
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {

	// Initialize GLFW and GLAD
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLfloat vertices[] = {
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};
	
	// Create a window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Load GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	    std::cout << "Failed to initialize GLAD" << std::endl;
	    return -1;
	} 

	// Create a vertex buffer object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach the shader source code to the shader object and compile the shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	// If the compilation failed, print the error message
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create a shader program
	GLuint shaderProgram = glCreateProgram();
	
	// Attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link the shaders
	glLinkProgram(shaderProgram);

	// Check for linking errors	
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create a vertex buffer object (VBO) and vertex array object (VAO)
	GLuint VAO, VBO;

	// Generate a vertex array object
	glGenVertexArrays(1, &VAO); 
	// Generate a buffer object
	glGenBuffers(1, &VBO);

	// Bind the vertex array object to the GL_VERTEX_ARRAY target
	glBindVertexArray(VAO); 

	// Bind the buffer object to the GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy the vertex data into the buffer's memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Main render loop
	while(!glfwWindowShouldClose(window)) {

		// Input
		processInput(window);

		// Rendering commands here
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); 

		// Swap the buffers
	    glfwSwapBuffers(window);
	    glfwPollEvents();    
	}

	// De-allocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Terminate GLFW
  	glfwTerminate();
    return 0;
}

/**
* Callback function for window resize
* @param window The window that was resized
* @param width The new width of the window
* @param height The new height of the window
*/
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

/*
* Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
* @param window The window to check input for
*/
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}