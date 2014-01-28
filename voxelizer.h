#pragma once

#include <functional>
#include <vector>
#include <array>

typedef std::array<float,3> vec3;
typedef std::array<int,3> vec3i;

class Voxelizer
{
public:
    Voxelizer(std::function<float(vec3i)> getDensityFn, int domainMin = -10, int domainMax = 10, float isolevel = 1.0f);

    std::vector<float> getData();
private:
    std::vector<vec3> march(vec3i pos);
    vec3 getGradient(vec3 pos);
    std::function<float(vec3i)> getDensityFn;
    float isolevel;

    std::vector<vec3> vertexPositions;
    std::vector<vec3> vertexNormals;
};
