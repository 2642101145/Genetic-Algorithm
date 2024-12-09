#include "PostmanProblemSolver.h"

//固定矩阵26*26演示
vector<vector<uint32_t>> distanceMatrix = {
            { 0 , 1 , 7 , 3 , 6 , 9 , 3 , 6 , 4 , 6 , 2 , 4 , 3 , 1 , 6 , 1 , 3 , 7 , 1 , 2 , 5 , 2 , 3 , 1 , 4 , 4 },
            { 1 , 0 , 2 , 8 , 5 , 4 , 5 , 7 , 6 , 9 , 2 , 8 , 1 , 4 , 3 , 2 , 3 , 4 , 3 , 2 , 7 , 3 , 3 , 9 , 6 , 4 },
            { 7 , 2 , 0 , 6 , 6 , 2 , 8 , 9 , 4 , 6 , 2 , 9 , 1 , 5 , 6 , 6 , 7 , 6 , 8 , 7 , 1 , 4 , 5 , 1 , 9 , 7 },
            { 3 , 8 , 6 , 0 , 1 , 1 , 6 , 7 , 7 , 9 , 3 , 4 , 6 , 3 , 6 , 5 , 5 , 7 , 5 , 2 , 1 , 2 , 7 , 4 , 5 , 9 },
            { 6 , 5 , 6 , 1 , 0 , 8 , 7 , 4 , 1 , 4 , 1 , 5 , 1 , 7 , 4 , 6 , 8 , 7 , 6 , 7 , 9 , 6 , 4 , 2 , 8 , 6 },
            { 9 , 4 , 2 , 1 , 8 , 0 , 3 , 8 , 4 , 3 , 4 , 6 , 2 , 2 , 7 , 9 , 5 , 6 , 4 , 7 , 4 , 9 , 5 , 4 , 9 , 1 },
            { 3 , 5 , 8 , 6 , 7 , 3 , 0 , 9 , 2 , 1 , 8 , 2 , 2 , 4 , 4 , 5 , 6 , 9 , 5 , 6 , 4 , 4 , 4 , 9 , 5 , 2 },
            { 6 , 7 , 9 , 7 , 4 , 8 , 9 , 0 , 6 , 1 , 6 , 6 , 5 , 4 , 9 , 6 , 8 , 4 , 8 , 4 , 5 , 9 , 1 , 4 , 8 , 3 },
            { 4 , 6 , 4 , 7 , 1 , 4 , 2 , 6 , 0 , 5 , 5 , 9 , 3 , 3 , 3 , 9 , 9 , 8 , 6 , 1 , 4 , 4 , 8 , 9 , 8 , 1 },
            { 6 , 9 , 6 , 9 , 4 , 3 , 1 , 1 , 5 , 0 , 3 , 1 , 9 , 1 , 4 , 2 , 3 , 8 , 3 , 9 , 2 , 9 , 7 , 4 , 7 , 1 },
            { 2 , 2 , 2 , 3 , 1 , 4 , 8 , 6 , 5 , 3 , 0 , 8 , 7 , 9 , 8 , 3 , 1 , 8 , 6 , 8 , 1 , 7 , 8 , 8 , 1 , 7 },
            { 4 , 8 , 9 , 4 , 5 , 6 , 2 , 6 , 9 , 1 , 8 , 0 , 3 , 6 , 3 , 9 , 1 , 1 , 3 , 2 , 5 , 9 , 7 , 6 , 7 , 3 },
            { 3 , 1 , 1 , 6 , 1 , 2 , 2 , 5 , 3 , 9 , 7 , 3 , 0 , 2 , 9 , 8 , 6 , 7 , 8 , 4 , 3 , 5 , 7 , 8 , 4 , 3 },
            { 1 , 4 , 5 , 3 , 7 , 2 , 4 , 4 , 3 , 1 , 9 , 6 , 2 , 0 , 5 , 3 , 8 , 7 , 7 , 3 , 6 , 6 , 2 , 6 , 8 , 8 },
            { 6 , 3 , 6 , 6 , 4 , 7 , 4 , 9 , 3 , 4 , 8 , 3 , 9 , 5 , 0 , 6 , 9 , 7 , 3 , 7 , 5 , 7 , 1 , 8 , 2 , 3 },
            { 1 , 2 , 6 , 5 , 6 , 9 , 5 , 6 , 9 , 2 , 3 , 9 , 8 , 3 , 6 , 0 , 6 , 6 , 5 , 5 , 4 , 1 , 3 , 5 , 1 , 9 },
            { 3 , 3 , 7 , 5 , 8 , 5 , 6 , 8 , 9 , 3 , 1 , 1 , 6 , 8 , 9 , 6 , 0 , 4 , 6 , 7 , 7 , 1 , 8 , 2 , 3 , 2 },
            { 7 , 4 , 6 , 7 , 7 , 6 , 9 , 4 , 8 , 8 , 8 , 1 , 7 , 7 , 7 , 6 , 4 , 0 , 9 , 7 , 6 , 6 , 4 , 5 , 3 , 4 },
            { 1 , 3 , 8 , 5 , 6 , 4 , 5 , 8 , 6 , 3 , 6 , 3 , 8 , 7 , 3 , 5 , 6 , 9 , 0 , 3 , 4 , 8 , 1 , 2 , 7 , 4 },
            { 2 , 2 , 7 , 2 , 7 , 7 , 6 , 4 , 1 , 9 , 8 , 2 , 4 , 3 , 7 , 5 , 7 , 7 , 3 , 0 , 3 , 8 , 4 , 5 , 9 , 3 },
            { 5 , 7 , 1 , 1 , 9 , 4 , 4 , 5 , 4 , 2 , 1 , 5 , 3 , 6 , 5 , 4 , 7 , 6 , 4 , 3 , 0 , 8 , 8 , 8 , 5 , 8 },
            { 2 , 3 , 4 , 2 , 6 , 9 , 4 , 9 , 4 , 9 , 7 , 9 , 5 , 6 , 7 , 1 , 1 , 6 , 8 , 8 , 8 , 0 , 6 , 1 , 1 , 5 },
            { 3 , 3 , 5 , 7 , 4 , 5 , 4 , 1 , 8 , 7 , 8 , 7 , 7 , 2 , 1 , 3 , 8 , 4 , 1 , 4 , 8 , 6 , 0 , 3 , 7 , 6 },
            { 1 , 9 , 1 , 4 , 2 , 4 , 9 , 4 , 9 , 4 , 8 , 6 , 8 , 6 , 8 , 5 , 2 , 5 , 2 , 5 , 8 , 1 , 3 , 0 , 7 , 6 },
            { 4 , 6 , 9 , 5 , 8 , 9 , 5 , 8 , 8 , 7 , 1 , 7 , 4 , 8 , 2 , 1 , 3 , 3 , 7 , 9 , 5 , 1 , 7 , 7 , 0 , 7 },
            { 4 , 4 , 7 , 9 , 6 , 1 , 2 , 3 , 1 , 1 , 7 , 3 , 3 , 8 , 3 , 9 , 2 , 4 , 4 , 3 , 8 , 5 , 6 , 6 , 7 , 0 }
    };


int main() {

    uint32_t best_path_total_distance = 0;

    uint32_t loop = 0;
    auto reset_loop = loop;

    PostmanProblemSolver solver;
    int type = 0;
    cout<<"选择生成类型:\n1.固定26*26距离矩阵\n2.随机距离矩阵\n3.固定辽宁省6地图矩阵\n";
    cin>>type;
    switch (type) {
        case 1:
        {

            loop = 200000;
            PostmanProblemSolver static_26x26_solver(distanceMatrix);
            solver = static_26x26_solver;
        }break;
        case 2:
        {
            uint32_t point_num;
            cout<<"输入地点数量和查找力度:地点数量 查找力度"<<endl;
            cin>>point_num>>loop;
            PostmanProblemSolver random_solver(point_num);
            solver = random_solver;
        }break;
        case 3: {
            string param = "LiaoNing";
            loop = 700;
            PostmanProblemSolver liao_ning_solver(param);
            solver = liao_ning_solver;
        }break;
        default:
        {
            cout<<"类型参数错误"<<endl;
        }
    }
    reset_loop = loop;

    cout<<"--------------------打印矩阵信息-----------------------"<<endl;
    solver.PrintMatrix();

    cout<<"--------------------创建初代成员-----------------------"<<endl;
    solver.CreatPathIdx(10);
    solver.PrintPath();

    reset_loop = loop+1;
    best_path_total_distance =0;
    do {
        //cout<<"------------------loop"<< loop<<"---------------------"<<endl;
        //选择
        solver.ChosePath();
        //solver.PrintPath();
        //杂交
        solver.Hybrid();
        //solver.PrintPath();
        //变异
        solver.Mutation(60,100);
        //solver.PrintPath();
        //solver.PrintBestPath();
        //初始化结束条件
        if(best_path_total_distance==0)
        {
            best_path_total_distance = solver.GetBestPathTotalDistance();
        } else
        {
            //找到新的解，继续循环
            if(solver.GetBestPathTotalDistance()<best_path_total_distance)
            {
                best_path_total_distance = solver.GetBestPathTotalDistance();
                //输出新的最优解最短路径
                cout<<"当前最短距离:"<<best_path_total_distance<<endl;
                loop = reset_loop;
                continue;
            }
        }
    }
    while(loop--);

    cout<<"---------最终解------------"<<endl;
    solver.PrintBestPath();
    solver.PrintPath();
    if(type==3){
        solver.PrintMapPath();
    }


    return 0;
}