#include "PostmanProblemSolver.h"

PostmanProblemSolver *PostmanProblemSolver::instance = nullptr;

PostmanProblemSolver::PostmanProblemSolver(const std::vector<char> &points) : allPoint(points) {

    random_device rd;
    gen = std::mt19937(rd());

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


    //固定矩阵26*26演示
//    distanceMatrix = {
//            { 0 , 1 , 7 , 3 , 6 , 9 , 3 , 6 , 4 , 6 , 2 , 4 , 3 , 1 , 6 , 1 , 3 , 7 , 1 , 2 , 5 , 2 , 3 , 1 , 4 , 4 },
//            { 1 , 0 , 2 , 8 , 5 , 4 , 5 , 7 , 6 , 9 , 2 , 8 , 1 , 4 , 3 , 2 , 3 , 4 , 3 , 2 , 7 , 3 , 3 , 9 , 6 , 4 },
//            { 7 , 2 , 0 , 6 , 6 , 2 , 8 , 9 , 4 , 6 , 2 , 9 , 1 , 5 , 6 , 6 , 7 , 6 , 8 , 7 , 1 , 4 , 5 , 1 , 9 , 7 },
//            { 3 , 8 , 6 , 0 , 1 , 1 , 6 , 7 , 7 , 9 , 3 , 4 , 6 , 3 , 6 , 5 , 5 , 7 , 5 , 2 , 1 , 2 , 7 , 4 , 5 , 9 },
//            { 6 , 5 , 6 , 1 , 0 , 8 , 7 , 4 , 1 , 4 , 1 , 5 , 1 , 7 , 4 , 6 , 8 , 7 , 6 , 7 , 9 , 6 , 4 , 2 , 8 , 6 },
//            { 9 , 4 , 2 , 1 , 8 , 0 , 3 , 8 , 4 , 3 , 4 , 6 , 2 , 2 , 7 , 9 , 5 , 6 , 4 , 7 , 4 , 9 , 5 , 4 , 9 , 1 },
//            { 3 , 5 , 8 , 6 , 7 , 3 , 0 , 9 , 2 , 1 , 8 , 2 , 2 , 4 , 4 , 5 , 6 , 9 , 5 , 6 , 4 , 4 , 4 , 9 , 5 , 2 },
//            { 6 , 7 , 9 , 7 , 4 , 8 , 9 , 0 , 6 , 1 , 6 , 6 , 5 , 4 , 9 , 6 , 8 , 4 , 8 , 4 , 5 , 9 , 1 , 4 , 8 , 3 },
//            { 4 , 6 , 4 , 7 , 1 , 4 , 2 , 6 , 0 , 5 , 5 , 9 , 3 , 3 , 3 , 9 , 9 , 8 , 6 , 1 , 4 , 4 , 8 , 9 , 8 , 1 },
//            { 6 , 9 , 6 , 9 , 4 , 3 , 1 , 1 , 5 , 0 , 3 , 1 , 9 , 1 , 4 , 2 , 3 , 8 , 3 , 9 , 2 , 9 , 7 , 4 , 7 , 1 },
//            { 2 , 2 , 2 , 3 , 1 , 4 , 8 , 6 , 5 , 3 , 0 , 8 , 7 , 9 , 8 , 3 , 1 , 8 , 6 , 8 , 1 , 7 , 8 , 8 , 1 , 7 },
//            { 4 , 8 , 9 , 4 , 5 , 6 , 2 , 6 , 9 , 1 , 8 , 0 , 3 , 6 , 3 , 9 , 1 , 1 , 3 , 2 , 5 , 9 , 7 , 6 , 7 , 3 },
//            { 3 , 1 , 1 , 6 , 1 , 2 , 2 , 5 , 3 , 9 , 7 , 3 , 0 , 2 , 9 , 8 , 6 , 7 , 8 , 4 , 3 , 5 , 7 , 8 , 4 , 3 },
//            { 1 , 4 , 5 , 3 , 7 , 2 , 4 , 4 , 3 , 1 , 9 , 6 , 2 , 0 , 5 , 3 , 8 , 7 , 7 , 3 , 6 , 6 , 2 , 6 , 8 , 8 },
//            { 6 , 3 , 6 , 6 , 4 , 7 , 4 , 9 , 3 , 4 , 8 , 3 , 9 , 5 , 0 , 6 , 9 , 7 , 3 , 7 , 5 , 7 , 1 , 8 , 2 , 3 },
//            { 1 , 2 , 6 , 5 , 6 , 9 , 5 , 6 , 9 , 2 , 3 , 9 , 8 , 3 , 6 , 0 , 6 , 6 , 5 , 5 , 4 , 1 , 3 , 5 , 1 , 9 },
//            { 3 , 3 , 7 , 5 , 8 , 5 , 6 , 8 , 9 , 3 , 1 , 1 , 6 , 8 , 9 , 6 , 0 , 4 , 6 , 7 , 7 , 1 , 8 , 2 , 3 , 2 },
//            { 7 , 4 , 6 , 7 , 7 , 6 , 9 , 4 , 8 , 8 , 8 , 1 , 7 , 7 , 7 , 6 , 4 , 0 , 9 , 7 , 6 , 6 , 4 , 5 , 3 , 4 },
//            { 1 , 3 , 8 , 5 , 6 , 4 , 5 , 8 , 6 , 3 , 6 , 3 , 8 , 7 , 3 , 5 , 6 , 9 , 0 , 3 , 4 , 8 , 1 , 2 , 7 , 4 },
//            { 2 , 2 , 7 , 2 , 7 , 7 , 6 , 4 , 1 , 9 , 8 , 2 , 4 , 3 , 7 , 5 , 7 , 7 , 3 , 0 , 3 , 8 , 4 , 5 , 9 , 3 },
//            { 5 , 7 , 1 , 1 , 9 , 4 , 4 , 5 , 4 , 2 , 1 , 5 , 3 , 6 , 5 , 4 , 7 , 6 , 4 , 3 , 0 , 8 , 8 , 8 , 5 , 8 },
//            { 2 , 3 , 4 , 2 , 6 , 9 , 4 , 9 , 4 , 9 , 7 , 9 , 5 , 6 , 7 , 1 , 1 , 6 , 8 , 8 , 8 , 0 , 6 , 1 , 1 , 5 },
//            { 3 , 3 , 5 , 7 , 4 , 5 , 4 , 1 , 8 , 7 , 8 , 7 , 7 , 2 , 1 , 3 , 8 , 4 , 1 , 4 , 8 , 6 , 0 , 3 , 7 , 6 },
//            { 1 , 9 , 1 , 4 , 2 , 4 , 9 , 4 , 9 , 4 , 8 , 6 , 8 , 6 , 8 , 5 , 2 , 5 , 2 , 5 , 8 , 1 , 3 , 0 , 7 , 6 },
//            { 4 , 6 , 9 , 5 , 8 , 9 , 5 , 8 , 8 , 7 , 1 , 7 , 4 , 8 , 2 , 1 , 3 , 3 , 7 , 9 , 5 , 1 , 7 , 7 , 0 , 7 },
//            { 4 , 4 , 7 , 9 , 6 , 1 , 2 , 3 , 1 , 1 , 7 , 3 , 3 , 8 , 3 , 9 , 2 , 4 , 4 , 3 , 8 , 5 , 6 , 6 , 7 , 0 }
//    };

    //辽宁6市旅游最短路径
    /*distanceMatrix = {
            {0,400,300,450,420,380},
            {400,0,100,80,120,220},
            {300,100,0,60,80,180},
            {450,80,60,0,50,160},
            {420,120,80,50,0,140},
            {380,220,180,160,140,0}
    };
    // 插入键值对，将字符与对应的城市名称关联起来
    string_map['A'] = "大连";
    string_map['B'] = "沈阳";
    string_map['C'] = "鞍山";
    string_map['D'] = "抚顺";
    string_map['E'] = "本溪";
    string_map['F'] = "锦州";*/

    //初始化最优路径长度
    best_path.total_distance = 0;
}

PostmanProblemSolver *PostmanProblemSolver::getInstance(const std::vector<char> &points) {
    if (instance == nullptr) {
        instance = new PostmanProblemSolver(points);
    }
    return instance;
}

uint32_t PostmanProblemSolver::GetPointIdx(const char &point) {
    return point - 65;
}

uint32_t PostmanProblemSolver::GetDistance(const char &point1, const char &point2) const {

    return distanceMatrix.at(GetPointIdx(point1)).at(GetPointIdx(point2));
}

void PostmanProblemSolver::PrintDistance(const char &point1, const char &point2) const {
    std::cout << point1 << "<------" << GetDistance(point1, point2) << "------>" << point2 << std::endl;
}

void PostmanProblemSolver::PrintMatrix() const {
    for (const auto &row: distanceMatrix) {
        for (auto value: row) {
            std::cout << value << " | ";
        }
        std::cout << std::endl;
    }
    cout << "----------------" << endl;
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
        vector<char> path_temp;
        vector<char> allPointTemp = allPoint;
        int point_num = allPoint.size() - 1;


        //设置路程起点
        const uint32_t begin_point_idx = 0;
        path_idx_temp.push_back(begin_point_idx);
        char creat_point = allPointTemp.at(begin_point_idx);
        path_temp.push_back(creat_point);
        char begin_point = creat_point;
        std::vector<char>::iterator it = allPointTemp.begin() + begin_point_idx;
        allPointTemp.erase(it);

        //设置路程点
        char before_point = begin_point;
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
    cout << "----------------" << endl;
}

void PostmanProblemSolver::PrintPath() const {

    for (const auto &row: paths) {
        vector<char> allPointTemp = allPoint;
        for (auto element: row.path) {
            std::cout << element << " ";
        }
        cout << " " << row.total_distance;
        std::cout << std::endl;
    }
    cout << "----------------" << endl;
}

void PostmanProblemSolver::PrintMapPath() const {

    for (const auto &row: paths) {
        vector<char> allPointTemp = allPoint;
        for (auto element: row.path) {
            auto it = string_map.find(element);
            std::cout << (it->second) << " ";
        }
        cout << " " << row.total_distance;
        std::cout << std::endl;
    }
    cout << "----------------" << endl;
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


void PostmanProblemSolver::Hybrid() {

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


        while (random < allPoint.size()) {
            try {
                auto new_point_idx = GetRandomNum(0, allPoint.size() - 1 - random);
                path.path_idx.at(random) = new_point_idx;
            } catch (const std::out_of_range &e) {
                std::cerr << "在Mutation函数中出现越界访问: " << e.what() << std::endl;
                // 可以根据情况选择合适的处理方式，比如直接返回、修正索引等
                return;
            }
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
    vector<char> allPointTemp = allPoint;
    for (auto element: best_path.path) {
        std::cout << element << " ";
    }
    cout << " " << best_path.total_distance;
    std::cout << std::endl;
    cout << "----------------" << endl;
}

uint32_t PostmanProblemSolver::GetBestPathTotalDistance() {
    return best_path.total_distance;
}
