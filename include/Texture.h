#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <vector>

struct TextureParameter
{
	GLenum type = 0;
	GLint value = 0;
};

class Texture
{
public:
	Texture(unsigned char* pixels, GLuint width, GLuint height, GLuint channels);

	void setID(GLuint id);
	void setType(GLchar type);
	void setParameters(std::vector<TextureParameter> parameters);

	GLuint getID();
	GLchar getType();
private:
	GLuint id;
	GLchar type;
};

#endif // !TEXTURE_H
