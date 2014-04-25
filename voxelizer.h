#pragma once

#include <functional>
#include <vector>
#include <array>

#include "glm/glm.hpp"

enum class Interpolation {
    Analytic,
    ComponentWiseLinear,
    Linear,
    Sobel
};

class Voxelizer
{
public:
    Voxelizer(std::function<float(glm::ivec3)> getDensityFn, glm::ivec3 domainMin, glm::ivec3 domainMax, float isolevel = 1.0f);
    void getData(std::vector<glm::vec3> &vertexPositions, std::vector<glm::vec3> &vertexNormals, std::vector<int> &indices);
    void setInterpolation(Interpolation i){ interpolation = i; }
    Interpolation getInterpolation(){ return interpolation; }
private:
    std::vector<glm::vec3> march(glm::ivec3 pos);
    glm::vec3 getGradientLinear(glm::vec3 pos);
    float getLinearInterpolate(glm::vec3 pos);
    glm::vec3 getGradientComponentWiseLinear(glm::vec3 pos);
    glm::vec3 getGradientSobel(glm::vec3 pos);
    std::function<float(glm::ivec3)> getDensityFn;
    float isolevel;
    glm::ivec3 domainMin;
    glm::ivec3 domainMax;
    Interpolation interpolation = Interpolation::ComponentWiseLinear;
};
