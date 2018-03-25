#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Shader.h"

struct Light {
	glm::vec3 position;
	glm::vec3 direction;
	float innerCutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light() {}
	Light
		( const glm::vec3 &position
		, const glm::vec3 &color
		, const glm::vec3 &direction
		, float innerCutOff
		, float outerCutOff
		);

	void unify(Shader shader, std::string name) const;
	void unify(Shader shader, int index) const;
	void enableUnify(Shader shader, int index) const;
	void unifyEnable(Shader shader, int index) const {
		unify(shader, index);
		enableUnify(shader, index);
	}
};
