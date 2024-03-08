#ifndef SHIP_H
#define SHIP_H

#include "WorkMap.h"

class Ship
{
private:
    int ship_id, berth_id, status, capacity, max_capacity;

public:
    Ship();
    Ship(int ship_id, int max_capacity);
    ~Ship();

    int get_status();
    int get_ship_id();
    int get_berth_id();
    int get_capacity();
    void set_status(int stu);
    void set_ship_id(int id);
    void set_berth_id(int id);
    void set_capacity(int num);
    void set_max_capacity(int cap);

    void update(int stu, int id);

    // 获取Ship运行指令
    const char* get_action();
};

#endif