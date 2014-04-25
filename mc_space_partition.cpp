//
//  MCSpacePartition.cpp
//  TopOptApp3D_plugin
//
//  Created by Morten Nobel-Jørgensen on 16/04/14.
//  Copyright (c) 2014 Morten Nobel-Joergensen. All rights reserved.
//

#include "mc_space_partition.h"

#include <cfloat>
#include <algorithm>

using namespace std;
using namespace glm;

MCSpacePartition::MCSpacePartition(int width, int height, float epsilogDistance)
:width{width}, height{height},width1{width+1}, height1{height+1}{
    epsilogDistanceSqr = epsilogDistance*epsilogDistance;
    data = new vector<MCPair>[(width1)*(height1)];
}

MCSpacePartition::~MCSpacePartition(){
    delete [] data;
}

void MCSpacePartition::cleanUp(int z){
    for (int i=0;i<(width1)*(height1);i++){
        remove_if(data[i].begin(),data[i].end(),[&](MCPair& obj){
            return obj.z < z;
        });
    }
}

void MCSpacePartition::insertPoint(vec3 point, int index, ivec3 voxelIndex){
    data[getIndex(voxelIndex.x, voxelIndex.y)].push_back(MCPair{point, index, voxelIndex.z});
    if (voxelIndex.z != lastZ){
        cleanUp(lastZ);
        lastZ = voxelIndex.z;
    }
}

int MCSpacePartition::getIndex(int x, int y){
    return std::max(0,(x*(width1)+y)%((width1)*(height1)));
}

float sqrMagnitude(vec3 f){
    return dot(f,f);
}

int MCSpacePartition::findPoint(vec3 point, ivec3 voxelIndex){
    int closestPoint = -1;
    float closestSqrDistance = FLT_MAX;
    for (int x=0;x<2;x++){
        for (int y=0;y<2;y++){
            for (const auto& mcPair : data[getIndex(voxelIndex.x-x, voxelIndex.y-y)]){
                double sqrDist = sqrMagnitude(mcPair.point - point);
                if (sqrDist < epsilogDistanceSqr && sqrDist < closestSqrDistance){
                    closestSqrDistance = sqrDist;
                    closestPoint = mcPair.index;
                }
            }
        }
    }
    return closestPoint;
}
