#pragma once

#include <GL/glew.h>

struct Texture {
	GLuint id;

	Texture() {
		glGenTextures(1, &id);
	}

	Texture(const char *filename)
		: Texture()
	{
		load2D(filename);
	}

	void bind(GLenum type = GL_TEXTURE_2D) const {
		glBindTexture(type, id);
	}

	static void unbind(GLenum type = GL_TEXTURE_2D) {
		glBindTexture(type, 0);
	}

	void activeBind(GLenum tex, GLenum type = GL_TEXTURE_2D) const {
		active(tex);
		bind(type);
	}

	static void active(GLenum tex) {
		glActiveTexture(tex);
	}

	void load2D(const char *filename) const;
	void loadCubeMap(const char *basename, const char *extname) const;

	static bool loadFromFile(GLenum mode, const char *filename);
	static void loadTexImage(GLenum mode,
		GLsizei width, GLsizei height, const void *data,
		GLenum srcRgbType = GL_RGB, GLenum dstRgbType = GL_RGB,
		GLenum srcDataType = GL_UNSIGNED_BYTE);
	static void simpleParameterSetup2D();
	static void simpleParameterSetupCubeMap();
};
