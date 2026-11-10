#include <core/Application.hpp>
#include <core/Shader.hpp>

#include <glad/glad.h>
#include <memory>

namespace {

class PrimitivesApp : public core::Application {
public:
    PrimitivesApp()
        : Application({ "Lab 01: Primitives (Hello Triangle)", 800, 600, true }) {}

    void onInit() override {
        // Compile and link shaders using core::Shader
        m_shader = std::make_unique<core::Shader>(
            "shaders/triangle.vert",
            "shaders/triangle.frag"
        );

        // Vertex positions (XYZ) and vertex colors (RGB)
        constexpr float vertices[] = {
            // Positions          // Colors
            0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // Bottom-right (Red)
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // Bottom-left  (Green)
            0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // Top          (Blue)
        };

        // Generate and bind VAO & VBO
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Attribute 0: Vertex Position (vec3) -> layout (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(0);

        // Attribute 1: Vertex Color (vec3) -> layout (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

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
        m_shader.reset();
    }

private:
    std::unique_ptr<core::Shader> m_shader;
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
};

}

int main() {
    PrimitivesApp app;
    return app.run();
}
