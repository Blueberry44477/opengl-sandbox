#include <core/Application.hpp>
#include <core/Shader.hpp>
#include <core/Texture.hpp>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <GLFW/glfw3.h>

namespace {

class TexturesApp : public core::Application {
public:
    TexturesApp()
        : Application({ "Lab 03: Transformations", 800, 600, true }) {}

    void onScroll(double , const double yOffset) override {
        m_scale += static_cast<float>(yOffset) * 0.1f;
        m_scale = std::clamp(m_scale, 0.1f, 5.0f);
    }

    void onInit() override {
        m_shader = std::make_unique<core::Shader>(
            "shaders/triangle.vert",
            "shaders/triangle.frag"
        );

        m_texture = std::make_unique<core::Texture>("assets/textures/fabric.jpg");

        m_shader->use();
        m_shader->setInt("ourTexture", 0);

        constexpr float vertices[] = {
            // Positions          // Colors           // Texture Coords
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
             0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 1.0f
        };

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
        if (m_texture) {
            m_texture->bind(0);
        }

        auto transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(m_scale, m_scale, 1.0f));
        transform = glm::rotate(transform, -static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

        m_shader->setMat4("transform", transform);

        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    void onDestroy() override {
        if (m_vao) {
            glDeleteVertexArrays(1, &m_vao);
            m_vao = 0;
        }
        if (m_vbo) {
            glDeleteBuffers(1, &m_vbo);
            m_vbo = 0;
        }
        m_texture.reset();
        m_shader.reset();
    }

private:
    std::unique_ptr<core::Shader> m_shader;
    std::unique_ptr<core::Texture> m_texture;
    float m_scale = 1.0f;

    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
};

} // namespace

int main() {
    TexturesApp app;
    return app.run();
}
