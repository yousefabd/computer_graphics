#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
class Texture {
private:
	int image_width;
	int image_height;
	int image_nrChannels;
	void load_image(std::string path) {
		stbi_set_flip_vertically_on_load(true);
		unsigned char* image = stbi_load(path.c_str(), &image_width, &image_height, &image_nrChannels, 0);
		if (image) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		else {
			std::cout << "failed to load image\n" <<path;
		}
		stbi_image_free(image);
	}

public:
	unsigned int genTexture(std::string image_path) {
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		load_image(image_path);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		return texture;
	}
	void activate(unsigned int texture, int value) {
		glActiveTexture(value);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	unsigned int make_sky_box(std::vector <std::string> faces)
	{
		stbi_set_flip_vertically_on_load(false);
		int width, height, nrChannels;
		unsigned int sky_box;
		glGenTextures(1, &sky_box);
		glBindTexture(GL_TEXTURE_CUBE_MAP,sky_box);
		for (unsigned int i = 0; i < faces.size(); i++) {
			unsigned char *data= stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else {
				std::cout << "failed to load image" << std::endl;
			}
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}
		return sky_box;
	}
};
#endif