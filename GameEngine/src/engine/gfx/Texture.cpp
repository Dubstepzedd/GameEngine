#include "engine/gfx/Texture.h"
#include <iostream>
#include <glad/glad.h> // or <GL/glew.h> depending on your setup
#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "engine/io/Resources.h"

Texture::Texture(const std::string& relativePath) {
    stbi_set_flip_vertically_on_load(1); // optional: flip image
    int width, height, nrChannels;
    std::string absolutePath = Resources::getRelativePath(relativePath);
    unsigned char* data = stbi_load(absolutePath.c_str(), &width, &height, &nrChannels, 0);
    spdlog::info("Absolute path to texture: {}", absolutePath);
    
    if (data) {
        m_Width = static_cast<unsigned int>(width);
        m_Height = static_cast<unsigned int>(height);
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
		spdlog::info("Texture loaded successfully from {}", absolutePath);
    }
    else {
        spdlog::error("Failed to create Texture instance with texture located at {}", absolutePath);
    }
    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererID);
}

void Texture::bind(unsigned int slot) {
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
