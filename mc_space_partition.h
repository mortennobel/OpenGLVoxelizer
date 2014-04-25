//
//  MCSpacePartition.h
//  TopOptApp3D_plugin
//
//  Created by Morten Nobel-Jørgensen on 16/04/14.
//  Copyright (c) 2014 Morten Nobel-Joergensen. All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>
#include "glm/glm.hpp"

class MCSpacePartition {
    
public:
    MCSpacePartition(int width, int height, float epsilogDistance = 0.01f);
    ~MCSpacePartition();
    
    
    void insertPoint(glm::vec3 point, int index, glm::ivec3  voxelIndex);
    int findPoint(glm::vec3  point, glm::ivec3  voxelIndex);
private:
    int getIndex(int x, int y);
    // removes vectors with voxelIndex less than z
    void cleanUp(int z);
    struct MCPair {
        glm::vec3 point;
        int index;
        int z;
    };
    
	float epsilogDistanceSqr;
    std::vector<MCPair> *data;
    int width;
    int height;
    int width1;
    int height1;
	int lastZ = -1;
};
