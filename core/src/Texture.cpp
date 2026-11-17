#define GL_SILENCE_DEPRECATION
#include <core/Texture.hpp>
#include <stb/stb_image.h>

#include <filesystem>
#include <iostream>

namespace {

std::string resolveTexturePath(const std::string& path) {
    if (std::filesystem::exists(path)) {
        return path;
    }

    const std::filesystem::path fallbacks[] = {
        std::filesystem::path("../") / path,
        std::filesystem::path("../../") / path,
        std::filesystem::path("../../../") / path
    };

    for (const auto& fallback : fallbacks) {
        if (std::filesystem::exists(fallback)) {
            return fallback.string();
        }
    }
    return path;
}

GLenum getGLFormat(const int channels) {
    switch (channels) {
        case 1: return GL_RED;
        case 3: return GL_RGB;
        case 4: return GL_RGBA;
        default: return GL_RGB;
    }
}

} // anonymous namespace

namespace core {

Texture::Texture(const std::string& path, const TextureConfig& config) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(config.wrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(config.wrapT));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(config.minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(config.magFilter));

    stbi_set_flip_vertically_on_load(config.flipVertically ? 1 : 0);

    const std::string resolvedPath = resolveTexturePath(path);
    unsigned char* data = stbi_load(resolvedPath.c_str(), &m_width, &m_height, &m_channels, 0);

    if (data) {
        const GLenum format = getGLFormat(m_channels);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

        if (config.generateMipmaps) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    } else {
        std::cerr << "ERROR::TEXTURE::FAILED_TO_LOAD\n"
                  << "  Path: " << resolvedPath << "\n"
                  << "  Reason: " << stbi_failure_reason() << std::endl;
    }

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    if (ID) {
        glDeleteTextures(1, &ID);
        ID = 0;
    }
}

Texture::Texture(Texture&& other) noexcept
    : ID(other.ID),
      m_width(other.m_width),
      m_height(other.m_height),
      m_channels(other.m_channels) {
    other.ID = 0;
    other.m_width = 0;
    other.m_height = 0;
    other.m_channels = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        if (ID) {
            glDeleteTextures(1, &ID);
        }
        ID = other.ID;
        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;

        other.ID = 0;
        other.m_width = 0;
        other.m_height = 0;
        other.m_channels = 0;
    }
    return *this;
}

void Texture::bind(unsigned int unit) const {
    if (ID) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, ID);
    }
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace core
