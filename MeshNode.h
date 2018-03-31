#pragma once

#include "Mesh.h"

class MeshNode {
protected:
public://
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

	MeshNode(const char *filename) {
		std::ifstream fin(filename);
		fromFile(fin);
		fin.close();
	}

	void setup() const;

	void draw(Shader shader, const glm::mat4 &model) const;

	void fromFile(std::ifstream &fin);
private:
	bool parseDefs(std::ifstream &fin, vector<Mesh *> meshlists);
	bool parseNode(std::ifstream &fin, vector<Mesh *> meshlists);
};
