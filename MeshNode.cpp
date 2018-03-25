#include "Shader.h"
#include "MeshNode.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using std::cout;
using std::endl;

void MeshNode::setup() const
{
	if (mesh)
		mesh->setup();

	for (auto child: children) {
		child.setup();
	}
}

void MeshNode::draw(Shader shader, const glm::mat4 &oldModel) const
{
	auto model = oldModel * trans;

	if (mesh) {
		shader.uniformMatrix4("model", glm::value_ptr(model));
		mesh->draw(shader);
	}

	for (auto child: children) {
		child.draw(shader, model);
	}
}
