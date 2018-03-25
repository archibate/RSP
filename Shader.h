#pragma once

#include <GL/glew.h>
#include <string>

struct ShaderCode {
	GLuint id;
	ShaderCode(GLenum type) {
		id = glCreateShader(type);
	}

	~ShaderCode() {
		glDeleteShader(id);
	}

	void source(const char *source) {
		glShaderSource(id, 1, &source, nullptr);
	}

	void compile() const {
		glCompileShader(id);
	}

	char *getError() const;

	char *compileGetError() const {
		compile();
		return getError();
	}

	int getiv(GLenum key) const {
		int value;
		glGetShaderiv(id, key, &value);
		return value;
	}
};

struct Shader {
	GLuint id;

	Shader() {
		id = glCreateProgram();
	}

	~Shader() {
		glDeleteProgram(id);
	}

	void attach(ShaderCode shader) const {
		glAttachShader(id, shader.id);
	}

	void link() const {
		glLinkProgram(id);
	}

	char *getError() const;

	char *linkGetError() const {
		link();
		return getError();
	}

	int getiv(GLenum key) const {
		int value;
		glGetProgramiv(id, key, &value);
		return value;
	}

	void use() const {
		glUseProgram(id);
	}

	int locationOf(const char *name) const {
		return glGetUniformLocation(id, name);
	}

	template <typename T>
	void uniform1v(const char *name, const T *v) const {
		uniform1v(locationOf(name), v);
	}

	template <typename T>
	void uniform2v(const char *name, const T *v) const {
		uniform2v(locationOf(name), v);
	}

	template <typename T>
	void uniform3v(const char *name, const T *v) const {
		uniform3v(locationOf(name), v);
	}

	template <typename T>
	void uniform4v(const char *name, const T *v) const {
		uniform4v(locationOf(name), v);
	}

	template <typename T>
	void uniform(const char *name, T x) const {
		uniform(locationOf(name), x);
	}

	template <typename T>
	void uniform(const char *name, T x, T y) const {
		uniform(locationOf(name), x, y);
	}

	template <typename T>
	void uniform(const char *name, T x, T y, T z) const {
		uniform(locationOf(name), x, y, z);
	}

	template <typename T>
	void uniform(const char *name, T x, T y, T z, T w) const {
		uniform(locationOf(name), x, y, z, w);
	}

	template <typename T>
	void uniformMatrix2(const char *name, T x) const {
		uniformMatrix2v(locationOf(name), x);
	}

	template <typename T>
	void uniformMatrix3(const char *name, T x) const {
		uniformMatrix3v(locationOf(name), x);
	}

	template <typename T>
	void uniformMatrix4(const char *name, T x) const {
		uniformMatrix4v(locationOf(name), x);
	}

	static void uniformMatrix2v(int location, const float *v) {
		glUniformMatrix2fv(location, 1, GL_FALSE, v);
	}

	static void uniformMatrix3v(int location, const float *v) {
		glUniformMatrix3fv(location, 1, GL_FALSE, v);
	}

	static void uniformMatrix4v(int location, const float *v) {
		glUniformMatrix4fv(location, 1, GL_FALSE, v);
	}

	static void uniformMatrix2v(int location, const double *v) {
		glUniformMatrix2dv(location, 1, GL_FALSE, v);
	}

	static void uniformMatrix3v(int location, const double *v) {
		glUniformMatrix3dv(location, 1, GL_FALSE, v);
	}

	static void uniformMatrix4v(int location, const double *v) {
		glUniformMatrix4dv(location, 1, GL_FALSE, v);
	}

	static void uniform1v(int location, const int *v) {
		glUniform1iv(location, 1, v);
	}

	static void uniform2v(int location, const int *v) {
		glUniform2iv(location, 1, v);
	}

	static void uniform3v(int location, const int *v) {
		glUniform3iv(location, 1, v);
	}

	static void uniform4v(int location, const int *v) {
		glUniform4iv(location, 1, v);
	}

	static void uniform1v(int location, const unsigned int *v) {
		glUniform1uiv(location, 1, v);
	}

	static void uniform2v(int location, const unsigned int *v) {
		glUniform2uiv(location, 1, v);
	}

	static void uniform3v(int location, const unsigned int *v) {
		glUniform3uiv(location, 1, v);
	}

	static void uniform4v(int location, const unsigned int *v) {
		glUniform4uiv(location, 1, v);
	}

	static void uniform1v(int location, const float *v) {
		glUniform1fv(location, 1, v);
	}

	static void uniform2v(int location, const float *v) {
		glUniform2fv(location, 1, v);
	}

	static void uniform3v(int location, const float *v) {
		glUniform3fv(location, 1, v);
	}

	static void uniform4v(int location, const float *v) {
		glUniform4fv(location, 1, v);
	}

	static void uniform1v(int location, const double *v) {
		glUniform1dv(location, 1, v);
	}

	static void uniform2v(int location, const double *v) {
		glUniform2dv(location, 1, v);
	}

	static void uniform3v(int location, const double *v) {
		glUniform3dv(location, 1, v);
	}

	static void uniform4v(int location, const double *v) {
		glUniform4dv(location, 1, v);
	}

	static void uniform(int location, int x) {
		glUniform1i(location, x);
	}

	static void uniform(int location, int x, int y) {
		glUniform2i(location, x, y);
	}

	static void uniform(int location, int x, int y, int z) {
		glUniform3i(location, x, y, z);
	}

	static void uniform(int location, int x, int y, int z, int w) {
		glUniform4i(location, x, y, z, w);
	}

	static void uniform(int location, unsigned int x) {
		glUniform1f(location, x);
	}

	static void uniform(int location, unsigned int x, unsigned int y) {
		glUniform2f(location, x, y);
	}

	static void uniform(int location, unsigned int x, unsigned int y,
			unsigned int z) {
		glUniform3f(location, x, y, z);
	}

	static void uniform(int location, unsigned int x, unsigned int y,
			unsigned int z, unsigned int w) {
		glUniform4f(location, x, y, z, w);
	}

	static void uniform(int location, float x) {
		glUniform1f(location, x);
	}

	static void uniform(int location, float x, float y) {
		glUniform2f(location, x, y);
	}

	static void uniform(int location, float x, float y, float z) {
		glUniform3f(location, x, y, z);
	}

	static void uniform(int location, float x, float y, float z, float w) {
		glUniform4f(location, x, y, z, w);
	}

	static void uniform(int location, double x) {
		glUniform1d(location, x);
	}

	static void uniform(int location, double x, double y) {
		glUniform2d(location, x, y);
	}

	static void uniform(int location, double x, double y, double z) {
		glUniform3d(location, x, y, z);
	}

	static void uniform(int location, double x, double y, double z, double w) {
		glUniform4d(location, x, y, z, w);
	}
};
