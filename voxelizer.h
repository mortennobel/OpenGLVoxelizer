#pragma once

#include <functional>
#include <vector>
#include <array>

#include "glm/glm.hpp"

enum class Interpolation {
    None,
    ComponentWiseLinear,
    Linear,
    Sobel
};

class Voxelizer
{
public:
    // mirrorAxis +1 means mirror on domainMax for that axis
    // mirrorAxis -1 means mirror on domainMin for that axis
    Voxelizer(std::function<float(glm::ivec3)> getDensityFn, glm::ivec3 domainMin, glm::ivec3 domainMax, glm::ivec3 mirrorAxis, float isolevel = 1.0f);
    void getData(std::vector<glm::vec3> &vertexPositions, std::vector<glm::vec3> &vertexNormals, std::vector<int> &indices);
    void setInterpolation(Interpolation i);
    Interpolation getInterpolation();
    bool isAngleWeightedNormals() const;
    void setAngleWeightedNormals(bool angleWeightedNormals);
private:
    std::vector<glm::vec3> march(glm::ivec3 pos);
    glm::vec3 getGradientLinear(glm::vec3 pos);
    float getLinearInterpolate(glm::vec3 pos);
    glm::vec3 getGradientComponentWiseLinear(glm::vec3 pos);
    glm::vec3 getGradientSobel(glm::vec3 pos);
    float getDensity(glm::ivec3 p);
    std::function<float(glm::ivec3)> getDensityFn;
    float isolevel;
    glm::ivec3 domainMin;
    glm::ivec3 domainMax;
    glm::ivec3 mirrorAxis;
    Interpolation interpolation = Interpolation::Linear;
    bool angleWeightedNormals = false;
    void computeAngleWeightedNormals(std::vector<glm::vec3> &vertexPositions, std::vector<glm::vec3> &vertexNormals, std::vector<int> &indices);
    void computeNormals(std::vector<glm::vec3> &vertexPositions, std::vector<glm::vec3> &vertexNormals, std::vector<int> &indices);
};
