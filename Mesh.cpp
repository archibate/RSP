#include "VertexObjects.h"
#include "Shader.h"
#include "Mesh.h"

void Mesh::setup() const
{
	vao.bind();
	vbo.bindData(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
	ebo.bindData(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);

	vao.attribEnable(0, GL_FLOAT, offsetof(Vertex, Position), 3, sizeof(Vertex));
	vao.attribEnable(1, GL_FLOAT, offsetof(Vertex, Normal), 3, sizeof(Vertex));
	vao.attribEnable(2, GL_FLOAT, offsetof(Vertex, TexCoords), 2, sizeof(Vertex));

	VertexBufferObject::unbind(GL_ARRAY_BUFFER);
	VertexArrayObject::unbind();
}

void Mesh::draw(Shader shader) const
{
	material.unify(shader);
	vao.bind();
	GL::drawElements(GL_TRIANGLES, indices.size());
	VertexArrayObject::unbind();
}

void Material::unify(Shader shader) const
{
	diffuse.activeBind(GL_TEXTURE1);
	specular.activeBind(GL_TEXTURE2);
	Texture::active(GL_TEXTURE0);

	shader.uniform("material.diffuse",   1);
	shader.uniform("material.specular",  2);
	shader.uniform("material.shininess", shininess);
}
