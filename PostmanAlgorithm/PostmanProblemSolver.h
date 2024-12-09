//
// Created by catyqyang on 24-12-2.
//

#ifndef POSTMANALGORITHM_POSTMANPROBLEMSOLVER_H
#define POSTMANALGORITHM_POSTMANPROBLEMSOLVER_H
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <map>
#include <memory>
#include "path.h"


using namespace std;
class PostmanProblemSolver {
private:
    // 存储所有节点（这里以字符表示）的向量，用于映射索引和字符
    vector<char> allPoint;
    // 存储节点间距离的对称矩阵
    vector<vector<uint32_t>> distanceMatrix;
    // 单例对象指针
    static PostmanProblemSolver* instance;
    // 私有构造函数，防止外部直接实例化，参数用于接收节点字符向量,首字符永远为起点
    explicit PostmanProblemSolver(const vector<char>& points);
    // 路径
    vector<Path> paths;
    //按照索引重置Path元素
    void ResetPathWhenNewIdxGet(Path & path);

    //当前最优解
    Path best_path;

    //地图对应用
    map<char,string> string_map;

    mt19937 gen;

public:
    // 获取单例实例的静态方法，参数用于接收节点字符向量
    static PostmanProblemSolver* getInstance(const vector<char>& points);
    // 根据节点字符获取其在allPoint中的索引
    static uint32_t GetPointIdx(const char& point) ;
    // 获取两个节点之间的距离（通过矩阵中对应索引位置的值）
    uint32_t GetDistance(const char& point1, const char& point2) const;
    // 打印两个节点之间的距离信息
    void PrintDistance(const char& point1, const char& point2) const;
    // 打印矩阵
    void PrintMatrix() const;
    // 生成[min, max]范围的随机数
    uint32_t GetRandomNum(const int &min, const int &max) ;
    double GetRandomNum(const double &min, const double &max);
    //创建路径索引实例
    void CreatPathIdx(uint32_t creat_num);
    // 打印路径索引实例
    void PrintPathIdx() const;
    //打印路径实例
    void PrintPath() const;

    //杂交操作
    void Hybrid();
    //突变操作，输入概率分子和分母
    void Mutation(const uint32_t &prob,const uint32_t & prob_total);
    //选择操作
    void ChosePath();

    //获取当前最优路径
    void PrintBestPath();
    uint32_t GetBestPathTotalDistance();


    void PrintMapPath() const;

};


#endif //POSTMANALGORITHM_POSTMANPROBLEMSOLVER_H
