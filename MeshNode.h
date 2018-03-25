#pragma once

#include "Mesh.h"

class MeshNode {
protected:
	const Mesh *mesh;
	glm::mat4 trans;
	vector<MeshNode> children;

public:
	MeshNode
		( const Mesh *mesh = nullptr
		, const glm::mat4 &trans = glm::mat4()
		, const vector<MeshNode> &children = {}
		)
		: mesh(mesh)
		, trans(trans)
		, children(children)
	{}

	void setup() const;
	void draw(Shader shader, const glm::mat4 &model) const;
};
