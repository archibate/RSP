#include "Mesh.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using std::string;
using std::istringstream;
using std::getline;
using std::ifstream;

static istringstream &operator>>(istringstream &ss, glm::vec3 &v) {
	ss >> v.x >> v.y >> v.z;
	return ss;
}

static istringstream &operator>>(istringstream &ss, glm::vec2 &v) {
	ss >> v.x >> v.y;
	return ss;
}

static istringstream &operator>>(istringstream &ss, Vertex &vertex) {
	ss >> vertex.Position >> vertex.Normal >> vertex.TexCoords;
	return ss;
}

static istringstream &operator>>(istringstream &ss, Material &material) {
	string diffuse, specular;
	ss >> diffuse;
	ss >> specular;
	ss >> material.shininess;
	material.diffuse = Texture(diffuse.c_str());
	material.specular = Texture(specular.c_str());
	return ss;
}

void Mesh::fromFile(ifstream &fin)
{
	string line;
	while (true) {
		if (!getline(fin, line))
			goto end;
inst:
		if (line == "#vertices")
			goto vertices;
		if (line == "#indices")
			goto indices;
		if (line == "#material")
			goto material;
		if (line == "#end")
			goto end;
	}

vertices:
	while (true) {
		if (!getline(fin, line))
			goto end;
		if (line.length() == 0)
			continue;
		if (line[0] == '#')
			goto inst;

		istringstream ss(line);
		Vertex vertex;
		ss >> vertex;
		vertices.push_back(vertex);
	}

indices:
	while (true) {
		if (!getline(fin, line))
			goto end;
		if (line.length() == 0)
			continue;
		if (line[0] == '#')
			goto inst;

		istringstream ss(line);
		unsigned int index;
		ss >> index;
		indices.push_back(index);
	}

material:
	do {
		if (!getline(fin, line))
			goto end;
		if (line.length() == 0)
			goto material;
		if (line[0] == '#')
			goto inst;

		istringstream ss(line);
		ss >> material;
	} while (false);

end:
	return;
}
