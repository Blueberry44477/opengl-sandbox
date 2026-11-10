#pragma once

#include <string>

struct GLFWwindow;

namespace core {

struct WindowConfig {
    std::string title = "OpenGL Sandbox";
    int width = 800;
    int height = 600;
    bool vsync = true;
};

class Application {
public:
    explicit Application(WindowConfig config = {});
    virtual ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    int run();

    virtual void onInit() {}
    virtual void onUpdate(const float deltaTime) { (void)deltaTime; }
    virtual void onRender() = 0;
    virtual void onDestroy() {}
    virtual void onResize(int width, int height);

    [[nodiscard]] GLFWwindow* getNativeWindow() const { return m_window; }
    [[nodiscard]] int getWidth() const { return m_config.width; }
    [[nodiscard]] int getHeight() const { return m_config.height; }

    void close();

protected:
    void processInput();

private:
    bool init();
    void shutdown();

    WindowConfig m_config;
    GLFWwindow* m_window = nullptr;
    bool m_isRunning = false;
};

} // namespace core