#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include "Texture.h"
#include "VertexObjects.h"

struct Shader;

using std::vector;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	Vertex() {}
	Vertex
		( glm::vec3 Position
		, glm::vec3 Normal
		, glm::vec2 TexCoords
		)
		: Position(Position)
		, Normal(Normal)
		, TexCoords(TexCoords)
	{}
};

struct Material {
	Texture diffuse;
	Texture specular;
	float shininess;

	Material() {}
	Material
		( Texture diffuse
		, Texture specular
		, float   shininess
		)
		: diffuse   (diffuse)
		, specular  (specular)
		, shininess (shininess)
	{}

	void unify(Shader shader) const;
};

class Mesh {
private:
	VertexArrayObject vao;
	VertexBufferObject vbo;
	VertexBufferObject ebo;

public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	Material material;

	Mesh() {}
	Mesh(const char *filename) {
		std::ifstream fin;
		fin.open(filename);
		fromFile(fin);
		fin.close();
	}
	Mesh
		( const vector<Vertex> &       vertices
		, const vector<unsigned int> & indices
		, const Material &             material
		)
		: vertices (vertices)
		, indices  (indices)
		, material (material)
	{}

	void setup() const;

	void draw(Shader shader) const;

	void fromFile(std::ifstream &fin);
};
