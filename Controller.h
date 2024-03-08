#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Ship.h"
#include "Robot.h"

class Controller
{
private:
    int money, frame_id;

    WorkMap work_map;
    Ship ships[SHIP_NUM];
    vector<Robot> robots;
    vector<Robot> unused_robots;

public:
    Controller();
    Controller(int m, int f);
    ~Controller();

    void init();
    void run();
    void control();
    void progress();
};

#endif