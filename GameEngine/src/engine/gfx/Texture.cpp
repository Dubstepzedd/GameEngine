#include "engine/gfx/Texture.h"
#include <glad/glad.h> // or your OpenGL loader
#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "engine/io/Resources.h"

Texture::Texture(const std::string& path)
    : Asset(path), m_RendererID(0), m_Width(0), m_Height(0) {
}

bool Texture::load() {
    stbi_set_flip_vertically_on_load(1);

    int width, height, nrChannels;
    std::string absolutePath = Resources::getFullPath(m_Path);
    unsigned char* data = stbi_load(absolutePath.c_str(), &width, &height, &nrChannels, 0);

    if (!data) {
        spdlog::error("Failed to load texture from path: {}", absolutePath);
        return false;
    }

    m_Width = static_cast<unsigned int>(width);
    m_Height = static_cast<unsigned int>(height);

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    GLenum internalFormat = (nrChannels == 4) ? GL_RGBA8 : GL_RGB8;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    spdlog::info("Texture loaded successfully from {}", absolutePath);

    return true;
}

Texture::~Texture() {
    if (m_RendererID != 0) {
        glDeleteTextures(1, &m_RendererID);
    }
}

void Texture::bind(unsigned int slot) const {
    if (m_RendererID == 0) {
        spdlog::warn("Attempted to bind invalid texture.");
        return;
    }
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::unbind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}
