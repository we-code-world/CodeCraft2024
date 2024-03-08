#include "Ship.h"

Ship::Ship(){
    ship_id = 0;
    berth_id = 0;
    status = 0;
    capacity = 0;
    max_capacity = 0;
}

Ship::Ship(int id, int cap){
    Ship();
    ship_id = id;
    max_capacity = cap;
    capacity = cap;
}

Ship::~Ship(){
}

void Ship::set_capacity(int num){
    capacity = num;
}

void Ship::set_status(int stu){
    status = stu;
}

void Ship::set_ship_id(int id){
    ship_id = id;
}

void Ship::set_berth_id(int id){
    berth_id = id;
}

//void Ship::set_capacity(int cap){
//    capacity = cap;
//}

void Ship::set_max_capacity(int cap){
    max_capacity = cap;
}

int Ship::get_capacity(){
    return capacity;
}

int Ship::get_status(){
    return status;
}

int Ship::get_ship_id(){
    return ship_id;
}

int Ship::get_berth_id(){
    return berth_id;
} 

void Ship::update(int stu, int id){
    status = stu;
    berth_id = id;
}

// 获取Ship运行指令
const char* Ship::get_action(){
    return "go";
}