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
			std::cout << "failed to load image\n";
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
};
#endif