#include "Controller.h"

Controller::Controller() {
    money = 0;
    frame_id = 0;
}

Controller::Controller(int m, int f) {
    money = m;
    frame_id = f;
}

Controller::~Controller() {
}

char map_strs[MAP_SIZE][MAP_SIZE];

// 初始化控制器状态信息
void Controller::init(){
    
    int id, x, y, time, velocity, max_capacity;

    for(int i = 0; i < MAP_SIZE; i ++){
        scanf("%s", map_strs[i]);
        // 初始化所有机器人
        // for(int j = 0; j < MAP_SIZE; j ++) if(map_strs[i][j] == 'A') robots.emplace_back(Robot(i, j));
    }

    for(int i = 0; i < BERTH_NUM; i ++)
    {
        scanf("%d%d%d%d%d", &id, &x, &y, &time, &velocity);
        //work_map.add_berth(id, x, y, time, velocity);
    }
    // 根据输入地图字符串构造工作地图
    // work_map.init(map_strs);

    scanf("%d", &max_capacity);
    //for(int i = 0; i < SHIP_NUM; i ++) ships[i].set_max_capacity(max_capacity);
    char ok[100];
    scanf("%s", ok);

    printf("OK\n");
    fflush(stdout);
}

// 处理数据，控制策略
void Controller::progress(){
    
}

// 控制输入输出
void Controller::control(){
    for (int j = 1; j <= 15000; j++) {

        // 输入处理
        scanf("%d%d", &frame_id, &money);
        
        int num;
        scanf("%d", &num);
        for(int i = 1; i <= num; i ++)
        {
            int x, y, value;
            scanf("%d%d%d", &x, &y, &value);
            //work_map.add_goods(x, y, value);
        }
        for(int i = 0; i < ROBOT_NUM; i ++)
        {
            int has_good, x, y, status;
            scanf("%d%d%d%d", &has_good, &x, &y, &status);
            //robots[i].update(has_good, x, y, status);
        }
        for(int i = 0; i < SHIP_NUM; i ++)
        {
            int status, berth_id;
            scanf("%d%d\n", &status, &berth_id);
            //ships[i].update(status, berth_id);
        }
        char ok[100];
        scanf("%s", ok);

        // 输出处理
        //for(int i = 0; i < ROBOT_NUM; i ++)
            // printf(robots[i].get_action());
            // printf("move %d %d\n", i, rand() % 4);
        //for(int i = 0; i < SHIP_NUM; i ++)
        //    printf(ships[i].get_action());
        puts("OK");
        fflush(stdout);
    }
}

void Controller::run(){
    control();
    /*thread control(Controller::control), progress(Controller::progress);
    control.join();
    progress.join();*/
}