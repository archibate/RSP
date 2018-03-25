#include "Camera.h"

void Camera::updateByInput(float speed)
{
	if (input.forward)
		pos -= speed * front;
	if (input.backward)
		pos += speed * front;
	if (input.left)
		pos += speed * glm::normalize(glm::cross(up, front));
	if (input.right)
		pos -= speed * glm::normalize(glm::cross(up, front));
	if (input.up)
		pos += speed * up;
	if (input.down)
		pos -= speed * up;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(pos, pos + front, up);
}
