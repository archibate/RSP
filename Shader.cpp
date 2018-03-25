#include "Shader.h"

char *ShaderCode::getError() const
{
	if (getiv(GL_COMPILE_STATUS))
		return nullptr;

	int infoLogLength = getiv(GL_INFO_LOG_LENGTH);
	auto infoLog = new char[infoLogLength];

	glGetShaderInfoLog(id, infoLogLength, nullptr, infoLog);
	return infoLog;
}

char *Shader::getError() const
{
	if (getiv(GL_LINK_STATUS))
		return nullptr;

	int infoLogLength = getiv(GL_INFO_LOG_LENGTH);
	auto infoLog = new char[infoLogLength];
	glGetProgramInfoLog(id, infoLogLength, nullptr, infoLog);
	return infoLog;
}
