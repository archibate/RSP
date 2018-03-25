#pragma once

#include "GL/glew.h"
#include <vector>

/*template <typename T>
struct gl_type_enum {
	static const GLenum type = 0;
};

template <>
struct gl_type_enum<float> {
	static const GLenum type = GL_FLOAT;
};

template <>
struct gl_type_enum<unsigned int> {
	static const GLenum type = GL_UNSIGNED_INT;
};*/

struct VertexBufferObject {
	GLuint id;

	VertexBufferObject() {
		glGenBuffers(1, &id);
	}

	~VertexBufferObject() {
		glDeleteBuffers(1, &id);
	}

	void bind(GLenum type) const {
		glBindBuffer(type, id);
	}

	void setData(GLenum type, GLsizei size, const void *arr, GLenum drawType) const
	{
		glBufferData(type, size, arr, drawType);
	}

	void bindData(GLenum type, GLsizei size, const void *arr, GLenum drawType) const
	{
		bind(type);
		setData(type, size, arr, drawType);
	}

	template <typename T>
	void setData(GLenum type, const std::vector<T> &arr, GLenum drawType) const
	{
		setData(type, sizeof(T) * arr.size(), arr.data(), drawType);
	}

	template <typename T>
	void bindData(GLenum type, const std::vector<T> &arr, GLenum drawType) const
	{
		bind(type);
		setData(type, arr, drawType);
	}
	
	static void unbind(GLenum type) {
		glBindBuffer(type, 0);
	}
};

struct VertexArrayObject {
	GLuint id;

	VertexArrayObject() {
		glGenVertexArrays(1, &id);
	}

	~VertexArrayObject() {
		glDeleteVertexArrays(1, &id);
	}

	void bind() const {
		glBindVertexArray(id);
	}

	void enableAttrib(GLuint index) const {
		glEnableVertexAttribArray(index);
	}

	void disableAttrib(GLuint index) const {
		glDisableVertexAttribArray(index);
	}

	void attrib(GLuint index, GLenum type, GLuint pointer, GLuint count,
			GLuint stride, GLboolean normalized = GL_FALSE) const
	{
		glVertexAttribPointer(index, count, type, normalized,
				stride, (void *) pointer);
	}

	void attribEnable(GLuint index, GLenum type,
			GLuint pointer, GLuint count,
			GLuint stride, GLboolean normalized = GL_FALSE) const
	{
		attrib(index, type, pointer, count, stride, normalized);
		enableAttrib(index);
	}

	static void unbind() {
		glBindVertexArray(0);
	}
};

namespace GL {
	static void drawArrays(GLenum mode, GLuint first, GLuint count) {
		glDrawArrays(mode, first, count);
	}

	static void drawElements(GLenum mode, GLuint count) {
		glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
	}
}
