#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// Reference ID of the Element Buffer Object
	GLuint ID;
	
	EBO(GLuint* indices, GLsizeiptr size);
	
	void Bind();
	
	void Unbind();
	
	void Delete();
};

#endif // !EBO_CLASS_H

