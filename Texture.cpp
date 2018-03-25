#include "Texture.h"
#include "stb_image.h"
#include "ssthrow.h"
#include <sstream>
#include <array>

void Texture::load2D(const char *filename) const {
	bind(GL_TEXTURE_2D);
	simpleParameterSetup2D();
	if (!loadFromFile(GL_TEXTURE_2D, filename)) {
		SSTHROW("ERROR::TEXTURE::IMAGE::LOAD_FAILED\n"
			<< "Failed to load texture: " << filename);
	}
}

void Texture::loadCubeMap(const char *basename, const char *extname) const {
	bind(GL_TEXTURE_2D);
	simpleParameterSetup2D();

	std::array<std::string, 6> facenames = {
		"right", "left",
		"top", "bottom",
		"front", "back",
	};

	for (GLuint i = 0; i < 6; i++) {
		auto filename = std::string(basename) + facenames[i] + extname;
		if (!loadFromFile(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					filename.c_str())) {
			SSTHROW("ERROR::TEXTURE::IMAGE::LOAD_FAILED\n"
					<< "Failed to load texture: " << filename);
		}
	}
}

bool Texture::loadFromFile(GLenum mode, const char *filename)
{
	int width, height, nchannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filename,
			&width, &height, &nchannels, 0);
	if (!data)
		return false;

	int ret = false;
	GLenum rgbType;
	switch (nchannels) {
		case 3: rgbType = GL_RGB; break;
		case 4: rgbType = GL_RGBA; break;
		default: goto out;
	};
	loadTexImage(mode, width, height, data, rgbType, rgbType);
	ret = true;
out:
	stbi_image_free(data);
	return ret;
}

void Texture::loadTexImage(GLenum mode,
		GLsizei width, GLsizei height, const void *data,
		GLenum srcRgbType, GLenum dstRgbType, GLenum srcDataType)
{
	glTexImage2D(mode, 0, dstRgbType,
			width, height, 0, srcRgbType, srcDataType, data);
}

void Texture::simpleParameterSetup2D()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::simpleParameterSetupCubeMap()
{
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
