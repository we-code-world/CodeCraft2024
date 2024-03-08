#include <bits/stdc++.h>
#include "Robot.h"

Robot::Robot() {
    x = 0;
    y = 0;
    has_goods = false;
}

Robot::Robot(int startX, int startY) {
    Robot();
    x = startX;
    y = startY;
}

Robot::~Robot() {
}

int Robot::get_robot_id(){
    return robot_id;
}

void Robot::update(bool goodsadd, int now_x, int now_y, int now_status){
    has_goods = goodsadd;
    x = now_x;
    y = now_y;
    status = now_status;
}

const char* get_action(){
    return "move";
}