#include <iostream>
#include <core/Application.hpp>
#include <core/Shader.hpp>
#include <stb/stb_image.h>

#include <glad/glad.h>
#include <memory>

namespace {

class PrimitivesApp : public core::Application {
public:
    PrimitivesApp()
        : Application({ "Textures", 800, 600, true }) {}

    void onInit() override {
        m_shader = std::make_unique<core::Shader>(
            "shaders/triangle.vert",
            "shaders/triangle.frag"
        );

        // Define texture
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load texture
        int width, height, nrChannels;
        const auto data = stbi_load("../../assets/textures/fabric.jpg", &width, &height, &nrChannels, 0);

        if (data) {
            const GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);

        constexpr float vertices[] = {
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
             0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 1.0f
        };

        // Generate and bind VAO & VBO
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Attribute 0: Vertex Position (vec3) -> layout (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(0);

        // Attribute 1: Vertex Color (vec3) -> layout (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Attribute 2: Vertex Texture (vec2) -> layout (location = 2)
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void onRender() override {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (m_shader) {
            m_shader->use();
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    void onDestroy() override {
        // Clean up GPU buffer objects
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
            m_vao = 0;
        }
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
            m_vbo = 0;
        }
        if (m_texture) {
            glDeleteTextures(1, &m_texture);
            m_texture = 0;
        }
        m_shader.reset();
    }

private:
    std::unique_ptr<core::Shader> m_shader;
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;

    unsigned int m_texture = 0;
};

}

int main() {
    PrimitivesApp app;
    return app.run();
}
