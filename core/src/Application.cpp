#define GL_SILENCE_DEPRECATION
#include <core/Application.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>

namespace core {

Application::Application(WindowConfig config)
    : m_config(std::move(config)) {}

Application::~Application() {
    shutdown();
}

bool Application::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    // Configure OpenGL context: Core Profile 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(
        m_config.width,
        m_config.height,
        m_config.title.c_str(),
        nullptr,
        nullptr
    );

    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    // V-Sync configuration
    glfwSwapInterval(m_config.vsync ? 1 : 0);

    // Initialize GLAD function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(m_window);
        m_window = nullptr;
        glfwTerminate();
        return false;
    }

    // Store 'this' pointer inside GLFW window to access application instance from callbacks
    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (app) {
            app->onResize(width, height);
        }
    });

    // Account for Retina / HiDPI framebuffers
    int fbWidth = 0;
    int fbHeight = 0;
    glfwGetFramebufferSize(m_window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GPU:            " << glGetString(GL_RENDERER) << "\n";

    return true;
}

void Application::onResize(int width, int height) {
    m_config.width = width;
    m_config.height = height;
    glViewport(0, 0, width, height);
}

void Application::processInput() {
    if (m_window && glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        close();
    }
}

void Application::close() {
    m_isRunning = false;
    if (m_window) {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
}

int Application::run() {
    if (!init()) {
        return -1;
    }

    m_isRunning = true;
    onInit();

    float lastFrameTime = static_cast<float>(glfwGetTime());

    while (m_isRunning && !glfwWindowShouldClose(m_window)) {
        const float currentTime = static_cast<float>(glfwGetTime());
        const float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        processInput();
        onUpdate(deltaTime);
        onRender();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    // Call onDestroy before terminating OpenGL context so OpenGL cleanup calls remain valid
    onDestroy();
    shutdown();

    return 0;
}

void Application::shutdown() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
        glfwTerminate();
    }
}

} // namespace core
