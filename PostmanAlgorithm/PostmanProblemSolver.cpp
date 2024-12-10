#include "PostmanProblemSolver.h"


PostmanProblemSolver::PostmanProblemSolver(const uint32_t & point_num) {
    random_device rd;
    gen = std::mt19937(rd());
    if (point_num < 2) {
    throw std::invalid_argument("point_num must be at least 2");
    }

    for (uint32_t i = 0; i < point_num; ++i) {
        allPoint.push_back(i);
    }

    //生成随机矩阵
    uint32_t n = allPoint.size();
    distanceMatrix = std::vector<std::vector<uint32_t>>(n, std::vector<uint32_t>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            auto randomValue = PostmanProblemSolver::GetRandomNum(1, 9);
            distanceMatrix[i][j] = randomValue;
            distanceMatrix[j][i] = randomValue;  // 沿对角线对称
        }
    }

    //初始化打印值
    SetOutPutMap(n);

    //初始化最优路径长度
    best_path.total_distance = 0;

}


PostmanProblemSolver::PostmanProblemSolver(string & param)
{
    random_device rd;
    gen = std::mt19937(rd());

    if(param =="LiaoNing")
    {
        //辽宁6市旅游最短路径
        distanceMatrix = {
                {0,400,300,450,420,380},
                {400,0,100,80,120,220},
                {300,100,0,60,80,180},
                {450,80,60,0,50,160},
                {420,120,80,50,0,140},
                {380,220,180,160,140,0}
        };
        // 插入键值对，将字符与对应的城市名称关联起来
        out_put_string_map[0] = "大连";
        out_put_string_map[1] = "沈阳";
        out_put_string_map[2] = "鞍山";
        out_put_string_map[3] = "抚顺";
        out_put_string_map[4] = "本溪";
        out_put_string_map[5] = "锦州";
    }

    for (uint32_t i = 0; i < distanceMatrix.size(); ++i) {
        allPoint.push_back(i);
    }

    //初始化最优路径长度
    best_path.total_distance = 0;
}

PostmanProblemSolver::PostmanProblemSolver(const vector<vector<uint32_t>> & distanceMatrix)
{
    random_device rd;
    gen = std::mt19937(rd());
    //固定矩阵26*26演示
    this->distanceMatrix = distanceMatrix;
    for (uint32_t i = 0; i < distanceMatrix.size(); ++i) {
        allPoint.push_back(i);
    }

    //初始化打印值
    SetOutPutMap(distanceMatrix.size());
    //初始化最优路径长度
    best_path.total_distance = 0;
}

PostmanProblemSolver::PostmanProblemSolver(const std::vector<uint32_t> &points) : allPoint(points) {

    //随机矩阵
    uint32_t n = allPoint.size();
    distanceMatrix = std::vector<std::vector<uint32_t>>(n, std::vector<uint32_t>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            auto randomValue = PostmanProblemSolver::GetRandomNum(1, 30);
            distanceMatrix[i][j] = randomValue;
            distanceMatrix[j][i] = randomValue;  // 沿对角线对称
        }
    }

    //初始化打印值
    SetOutPutMap(n);

    //初始化最优路径长度
    best_path.total_distance = 0;
}

uint32_t PostmanProblemSolver::GetDistance(const uint32_t &point1, const uint32_t &point2) const {
    return distanceMatrix.at(point1).at(point2);
}

void PostmanProblemSolver::PrintDistance(const uint32_t &point1, const uint32_t &point2) const {
    std::cout << out_put_string_map.at(point1)<< "<------" << GetDistance(point1, point2) << "------>" << out_put_string_map.at(point2) << std::endl;
}

void PostmanProblemSolver::PrintMatrix() const {
    for (const auto &row: distanceMatrix) {
        for (auto value: row) {
            std::cout << value << " | ";
        }
        std::cout << std::endl;
    }
}

uint32_t PostmanProblemSolver::GetRandomNum(const int &min, const int &max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

double PostmanProblemSolver::GetRandomNum(const double &min, const double &max) {
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

void PostmanProblemSolver::CreatPathIdx(uint32_t creat_num) {

    while (creat_num--) {
        Path path;
        path.total_distance = 0;
        vector<uint32_t> path_idx_temp;
        vector<uint32_t> path_temp;
        vector<uint32_t> allPointTemp = allPoint;
        int point_num = allPoint.size() - 1;

        //设置路程起点
        const uint32_t begin_point_idx = 0;
        path_idx_temp.push_back(begin_point_idx);
        uint32_t creat_point = allPointTemp.at(begin_point_idx);
        path_temp.push_back(creat_point);
        uint32_t begin_point = creat_point;
        auto it = allPointTemp.begin() + begin_point_idx;
        allPointTemp.erase(it);

        //设置路程点
        uint32_t before_point = begin_point;
        do {
            //生成索引
            auto idx = GetRandomNum(0, --point_num);
            path_idx_temp.push_back(idx);
            //生成路径
            creat_point = allPointTemp.at(idx);
            path_temp.push_back(creat_point);
            it = allPointTemp.begin() + idx;
            allPointTemp.erase(it);
            path.total_distance += GetDistance(before_point, creat_point);
            before_point = creat_point;
        } while (point_num > 0);

        //计算终点返回起点距离
        path.total_distance += GetDistance(begin_point, creat_point);
        path.fitness = 1.0 / path.total_distance;

        //放入索引和路径
        path.path_idx = path_idx_temp;
        path.path = path_temp;
        paths.push_back(path);
        if (best_path.total_distance == 0) {
            best_path = path;
        } else if (best_path.total_distance > path.total_distance) {
            best_path = path;
        }
    }
}

void PostmanProblemSolver::PrintPathIdx() const {
    for (const auto &row: paths) {
        for (auto element: row.path_idx) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

void PostmanProblemSolver::PrintPath() const {

    for (const auto &row: paths) {
        vector<uint32_t> allPointTemp = allPoint;
        for (auto element: row.path) {
            std::cout << out_put_string_map.at(element) << " ";
        }
        cout << "\t长度:" << row.total_distance;
        std::cout << std::endl;
    }
}

void PostmanProblemSolver::ChosePath() {
    //生成概率区间
    vector<double> cumulative_probabilities;
    double total_fitness = 0;

    vector<Path> new_paths;
    vector<Path> min_paths;
    uint32_t min_total_distance = paths.at(0).total_distance;
    for (auto path: paths) {
        //将最短路径放入队列，不进行筛选
        //查找到新的最小数
        if (path.total_distance < min_total_distance) {
            for (auto min_path: min_paths) {
                total_fitness += min_path.fitness;
                cumulative_probabilities.push_back(total_fitness);
                new_paths.push_back(min_path);
            }
            min_paths.clear();
            min_paths.push_back(path);
            min_total_distance = path.total_distance;
        } else {
            total_fitness += path.fitness;
            cumulative_probabilities.push_back(total_fitness);
            new_paths.push_back(path);
        }
    }

    paths.clear();
    //将当前最优解存入队列中
    paths.insert(paths.end(), min_paths.begin(), min_paths.end());
    if (min_paths.size() != 0) {
        if (best_path.total_distance > min_paths.at(0).total_distance) {
            best_path = min_paths.at(0);
        }
    }

    //开始随机筛选可以留下的路径
    auto loop = new_paths.size();

    double random = 0.0;
    for (auto path_mem: new_paths) {
        random = GetRandomNum(0.0, cumulative_probabilities.back());
        auto it = lower_bound(cumulative_probabilities.begin(), cumulative_probabilities.end(), random);
        size_t index = distance(cumulative_probabilities.begin(), it);
        paths.push_back(new_paths.at(index));
    }

}


void PostmanProblemSolver::Hybrid(const uint32_t &prob, const uint32_t &prob_total) {

    vector<Path> min_paths;
    vector<Path> hybrid_paths;

    auto min_total_distance = paths.at(0).total_distance;

    for (auto path: paths) {
        //最优解不参与杂交
        //查找到新的最小数
        if (path.total_distance < min_total_distance) {
            for (auto min_path: min_paths) {
                hybrid_paths.push_back(min_path);
            }
            min_paths.clear();
            min_paths.push_back(path);
            min_total_distance = path.total_distance;
        } else {
            hybrid_paths.push_back(path);
        }
    }

    paths.clear();
    //将当前最优解存入队列中
    paths.insert(paths.end(), min_paths.begin(), min_paths.end());
    //只有一个待杂交路径，直接放弃杂交
    if (hybrid_paths.size() == 1) {
        paths.push_back(hybrid_paths.at(0));
    } else if (hybrid_paths.size() % 2 != 0 && hybrid_paths.size() != 0) {
        auto it = hybrid_paths.end() - 1;
        paths.push_back(*it);
        hybrid_paths.erase(it);
    }
    //开始杂交
    if (hybrid_paths.size() > 1) {
        for (auto idx = 0; idx < hybrid_paths.size(); idx += 2) {
            auto &path_a = hybrid_paths.at(idx);
            auto &path_b = hybrid_paths.at(idx + 1);
            //概率发生杂交
            if(GetRandomNum(1,prob_total)>prob)
            {
                paths.push_back(path_a);
                paths.push_back(path_b);
                continue;
            }

            //总里程相等不杂交
            if (path_a.total_distance == path_b.total_distance) {
                paths.push_back(path_a);
                paths.push_back(path_b);
                continue;
            }
            //从第random位交换
            auto random = GetRandomNum(1, allPoint.size() - 1);
            for (; random < allPoint.size(); random++) {
                auto temp_idx = path_a.path_idx.at(random);
                path_a.path_idx.at(random) = path_b.path_idx.at(random);
                path_b.path_idx.at(random) = temp_idx;
            }
            ResetPathWhenNewIdxGet(path_a);
            ResetPathWhenNewIdxGet(path_b);
            paths.push_back(path_a);
            paths.push_back(path_b);
        }

    }
}

void PostmanProblemSolver::Mutation(const uint32_t &prob, const uint32_t &prob_total) {
    vector<Path> min_paths;
    vector<Path> mutation_paths;
    auto min_total_distance = paths.at(0).total_distance;
    for (auto path: paths) {
        //最优解不参与杂交
        //查找到新的最小数
        if (path.total_distance < min_total_distance) {
            for (auto min_path: min_paths) {
                mutation_paths.push_back(min_path);
            }
            min_paths.clear();
            min_paths.push_back(path);
            min_total_distance = path.total_distance;
        } else {
            mutation_paths.push_back(path);
        }
    }

    paths.clear();
    //将当前最优解存入队列中
    paths.insert(paths.end(), min_paths.begin(), min_paths.end());

    for (auto idx = 0; idx < mutation_paths.size(); idx++) {
        auto random = GetRandomNum(1, prob_total);
        Path &path = mutation_paths.at(idx);
        if (random > prob)//不变异
        {
            paths.push_back(path);
            continue;
        }
        //获取变异索引位点，起点不能改变
        random = GetRandomNum(1, allPoint.size() - 1);


        while (random < allPoint.size())
        {
            auto new_point_idx = GetRandomNum(0, allPoint.size() - 1 - random);
            path.path_idx.at(random) = new_point_idx;
            random++;
        }
        ResetPathWhenNewIdxGet(path);
        paths.push_back(path);
    }
}

void PostmanProblemSolver::ResetPathWhenNewIdxGet(Path &path) {
    const vector<uint32_t> &path_idx = path.path_idx;
    path.total_distance = 0;
    path.fitness = 0;
    path.path.clear();
    auto allPointTemp = allPoint;

    path.path.push_back(*allPointTemp.begin());
    //擦除起点
    auto it = allPointTemp.begin();
    allPointTemp.erase(it);

    //设置上一路程点
    for (auto idx = 1; idx < path_idx.size(); idx++) {
        it = allPointTemp.begin() + path_idx.at(idx);
        path.path.push_back(*it);
        path.total_distance += GetDistance(path.path.at(idx - 1), path.path.at(idx));
        allPointTemp.erase(it);
    }
    //计算终点返回起点距离
    path.total_distance += GetDistance(*path.path.begin(), path.path.back());

    path.fitness = 1.0 / path.total_distance;

    if (best_path.total_distance > path.total_distance) {
        best_path = path;
    }

}

void PostmanProblemSolver::PrintBestPath() {
    vector<uint32_t > allPointTemp = allPoint;
    for (auto element: best_path.path) {
        std::cout << out_put_string_map.at(element) << " ";
    }
    cout << "\t长度:" << best_path.total_distance;
    std::cout << std::endl;
}

uint32_t PostmanProblemSolver::GetBestPathTotalDistance() {
    return best_path.total_distance;
}

void PostmanProblemSolver::SetOutPutMap(const uint32_t map_size) {
    for (uint32_t i = 0; i < map_size; ++i) {
        if(i+1<10)
        {
            out_put_string_map[i] = "地点" +to_string(0) +to_string(i+1);
        }
        else
        {
            out_put_string_map[i] = "地点" + to_string(i+1);
        }

    }
}


