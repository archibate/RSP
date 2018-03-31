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

	glm::vec3 diffuse;
	glm::vec3 specular;

	Light() {}
	Light
		( const glm::vec3 &position
		, const glm::vec3 &color
		, const glm::vec3 &direction
		, float innerCutOff = -2.0f
		, float outerCutOff = -2.0f
		);

	void unify(Shader shader, std::string name) const;
	void unify(Shader shader, int index) const;
	void setEnable(Shader shader, int index, bool enable = true) const;
	void unifyEnable(Shader shader, int index) const {
		unify(shader, index);
		setEnable(shader, index);
	}
};

struct DirLight {
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	DirLight() {}
	DirLight
		( const glm::vec3 &direction
		, const glm::vec3 &color
		);

	void unify(Shader shader, std::string name) const;
	void unify(Shader shader) const;
	void setEnable(Shader shader, bool enable = true) const;
	void unifyEnable(Shader shader) const {
		unify(shader);
		setEnable(shader);
	}
};
