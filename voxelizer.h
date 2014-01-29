#pragma once

#include <functional>
#include <vector>
#include <array>

typedef std::array<float,3> vec3;
typedef std::array<int,3> vec3i;

enum class Interpolation {
    Analytic,
    ComponentWiseLinear,
    Linear
};

class Voxelizer
{
public:
    Voxelizer(std::function<float(vec3i)> getDensityFn, int domainMin = -10, int domainMax = 10, float isolevel = 1.0f);
    std::vector<float> getData();
    void setInterpolation(Interpolation i){ interpolation = i; }
    Interpolation getInterpolation(){ return interpolation; }
private:
    std::vector<vec3> march(vec3i pos);
    vec3 getGradientLinear(vec3 pos);
    vec3 getGradientComponentWiseLinear(vec3 pos);
    std::function<float(vec3i)> getDensityFn;
    float isolevel;
    int domainMin;
    int domainMax;
    Interpolation interpolation = Interpolation::ComponentWiseLinear;
};
