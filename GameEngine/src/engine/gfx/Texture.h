#pragma once
#include <string>

class Texture {
public:
    explicit Texture(const std::string& path); // Must be implemented manually

    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = default;
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind(unsigned int slot = 0) const;

    unsigned int getWidth() const {
        return m_Width;
    }

    unsigned int getHeight() const {
        return m_Height;
    }

private:
    unsigned int m_Width = 0;
    unsigned int m_Height = 0;
    unsigned int m_TextureId = 0;
    unsigned int m_RendererID = 0;
};
