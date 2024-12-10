//
// Created by catyqyang on 24-12-2.
//

#ifndef POSTMANALGORITHM_PATH_H
#define POSTMANALGORITHM_PATH_H

#include <cstdint>
#include "iostream"
#include "vector"


using namespace std;
struct Path
{
    //路径总长度
    uint32_t total_distance;
    //适应度
    double fitness;
    // 路径索引实例
    vector<uint32_t > path_idx;
    //路径实例
    vector<uint32_t> path;
};

struct BestPath
{
    uint32_t find_times;
    Path path;
};


#endif //POSTMANALGORITHM_PATH_H
