#include "Light.h"
#include <sstream>

Light::Light
	( const glm::vec3 &position
	, const glm::vec3 &color
	, const glm::vec3 &direction
	, float innerCutOff
	, float outerCutOff
	)
	: position    (position)
	, direction   (direction)
	, innerCutOff (innerCutOff)
	, outerCutOff (outerCutOff)
	, ambient     (0.2f * color)
	, diffuse     (0.5f * color)
	, specular    (1.0f * color)
	, constant    (1.0f)
	, linear      (0.09f)
	, quadratic   (0.032f)
{}

void Light::unify(Shader shader, std::string name) const
{
	shader.uniform3v((name + ".position").c_str(), &position[0]);
	shader.uniform3v((name + ".direction").c_str(), &direction[0]);
	shader.uniform((name + ".innerCutOff").c_str(), innerCutOff);
	shader.uniform((name + ".outerCutOff").c_str(), outerCutOff);
	shader.uniform3v((name + ".ambient").c_str(),  &ambient[0]);
	shader.uniform3v((name + ".diffuse").c_str(),  &diffuse[0]);
	shader.uniform3v((name + ".specular").c_str(), &specular[0]);
	shader.uniform((name + ".constant").c_str(),  constant);
	shader.uniform((name + ".linear").c_str(),    linear);
	shader.uniform((name + ".quadratic").c_str(), quadratic);
}

void Light::unify(Shader shader, int index) const
{
	std::ostringstream os;
	os << "lights[" << index << "]";
	unify(shader, os.str());
}

void Light::enableUnify(Shader shader, int index) const
{
	std::ostringstream os;
	os << "lightEnables[" << index << "]";
	shader.uniform(os.str().c_str(), true);
}
