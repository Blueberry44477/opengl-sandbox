#pragma once

#include <string>

namespace core {

class Shader {
public:
    unsigned int ID{0};

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    // Non-copyable to prevent accidental double-deletion of the shader program
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // Movable
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void use() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setMat4(const std::string &name, const float* matrixData) const;
};

} // namespace core
