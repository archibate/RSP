#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

struct Camera {
	struct InputMovements {
		bool backward, forward;
		bool left, right;
		bool up, down;
	} input;

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;

	Camera
		( const glm::vec3 &pos
		, const glm::vec3 &front
		, const glm::vec3 &up
		)
		: pos(pos)
		, front(front)
		, up(up)
	{}

	void updateByInput(float speed);
	void unify(Shader shader) {
		shader.uniform3v("viewPos", &pos[0]);
	}

	glm::mat4 getViewMatrix() const;
};
