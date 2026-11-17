#pragma once

#include <glad/glad.h>
#include <string>

namespace core {

struct TextureConfig {
    GLenum wrapS = GL_REPEAT;
    GLenum wrapT = GL_REPEAT;
    GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR;
    GLenum magFilter = GL_LINEAR;
    bool flipVertically = true;
    bool generateMipmaps = true;
};

class Texture {
public:
    unsigned int ID{0};

    explicit Texture(const std::string& path, const TextureConfig& config = {});
    ~Texture();

    // Non-copyable to prevent accidental double-deletion of the OpenGL texture
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Movable
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind(unsigned int unit = 0) const;
    static void unbind();

    [[nodiscard]] int getWidth() const { return m_width; }
    [[nodiscard]] int getHeight() const { return m_height; }
    [[nodiscard]] int getChannels() const { return m_channels; }

private:
    int m_width{0};
    int m_height{0};
    int m_channels{0};
};

} // namespace core
