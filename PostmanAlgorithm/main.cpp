#include "PostmanProblemSolver.h"

int main() {
    //26*26矩阵初始
    uint32_t loop = 200000;
    vector<char> all_point{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','[','\\',']', '^'};
    //6*6矩阵初始
    //uint32_t loop = 700;
    //vector<char> all_point{'A', 'B', 'C', 'D', 'E', 'F'};
    //5*5矩阵初始
    //uint32_t loop = 500;
    //vector<char> all_point{'A', 'B', 'C', 'D', 'E'};

    PostmanProblemSolver* solver = PostmanProblemSolver::getInstance(all_point);
    cout<<"--------------------打印矩阵信息-----------------------"<<endl;
    solver->PrintMatrix();
    solver->CreatPathIdx(10);
    cout<<"--------------------创建初代成员-----------------------"<<endl;
    solver->PrintPath();

    auto reset_loop = loop+1;
    uint32_t best_path_total_distance =0;
    do {
        //cout<<"------------------loop"<< loop<<"---------------------"<<endl;
        //选择
        solver->ChosePath();
        //solver->PrintPath();
        //杂交
        solver->Hybrid();
        //solver->PrintPath();
        //变异
        solver->Mutation(60,100);
        //solver->PrintPath();
        //solver->PrintBestPath();
        //初始化结束条件
        if(best_path_total_distance==0)
        {
            best_path_total_distance = solver->GetBestPathTotalDistance();
        } else
        {
            //找到新的解，继续循环
            if(solver->GetBestPathTotalDistance()<best_path_total_distance)
            {
                best_path_total_distance = solver->GetBestPathTotalDistance();
                //输出新的最优解最短路径
                cout<<"当前最短距离:"<<best_path_total_distance<<endl;
                loop = reset_loop;
                continue;
            }
        }
    }
    while(loop--);

    cout<<"---------最终解------------"<<endl;
    solver->PrintBestPath();
    solver->PrintPath();
    //solver->PrintMapPath();

    return 0;
}