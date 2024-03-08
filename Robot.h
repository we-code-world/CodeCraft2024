#ifndef ROBOT_H
#define ROBOT_H

#include "WorkMap.h"

class Robot
{
private:
    int robot_id;
    int x, y, goods_id;
    bool has_goods, status;

public:
    Robot();
    Robot(int startX, int startY);
    ~Robot();

    // 获取Robot编号
    int get_robot_id();

    // 更新Robot信息
    void update(bool goodsadd, int now_x, int now_y, int now_status);

    // 获取Robot运行指令
    const char* get_action();
};

#endif