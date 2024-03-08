#include "WorkMap.h"

Position::Position(){
    x = 0;
    y = 0;
}

Position::Position(int a, int b){
    x = a;
    y = b;
}

Position::Position(const Position &pos){
    x = pos.x;
    y = pos.y;
}

Position::~Position(){

}

AbstractBox::AbstractBox(){
    memset(next, -1, sizeof(next));
    memset(distance, -1, sizeof(distance));
}

AbstractBox::~AbstractBox(){
}

Berth::Berth() {
    time = 0;
    velocity = 0;
}

Berth::Berth(Position &pos, int transport_time, int loading_speed) {
    Position(pos);
    time = transport_time;
    velocity = loading_speed;
}

Berth::Berth(int pos_x, int pos_y, int transport_time, int loading_speed) {
    set_xy(pos_x, pos_y);
    time = transport_time;
    velocity = loading_speed;
}

Berth::~Berth() {
}

Product::Product(){
    value = 0;
}
Product::Product(Position &pos, int value){
    Position(pos);
    set_value(value);
}
Product::Product(int x, int y, int value){
    set_xy(x, y);
    set_value(value);
}
Product::~Product(){
    
}

WorkMap::WorkMap(){
    memset(land, 0, sizeof(land));
    memset(ocean, 0, sizeof(ocean));
}


WorkMap::WorkMap(char** map_str){
    WorkMap();
    init(map_str);
}

WorkMap::~WorkMap(){
}

int Position::get_x(){
    return x;
}

int Position::get_y(){
    return y;
}

void Position::set_x(int a){
    x = a;
}

void Position::set_y(int b){
    y = b;
}

void Position::set_xy(int a, int b){
    x = a;
    y = b;
}

bool Position::operator==(const Position &pos){
    return x == pos.x && y == pos.y;
}

void AbstractBox::set_next(Position &now, int value){
    next[now.get_x()][now.get_y()] = value;
}

void AbstractBox::set_next(int x, int y, int value){
    next[x][y] = value;
}

int AbstractBox::get_next(Position &now){
    return next[now.get_x()][now.get_y()];
}

int AbstractBox::get_next(int x, int y){
    return next[x][y];
}

void AbstractBox::set_distance(Position &now, int value){
    distance[now.get_x()][now.get_y()] = value;
}

void AbstractBox::set_distance(int x, int y, int value){
    distance[x][y] = value;
}

int AbstractBox::get_distance(Position &now){
    return distance[now.get_x()][now.get_y()];
}

int AbstractBox::get_distance(int x, int y){
    return distance[x][y];
}

void Berth::set_time(int t){
    time = t;
}

int Berth::get_time(){
    return time;
}

void Berth::set_velocity(int v){
    velocity = v;
}

int Berth::get_velocity(){
    return velocity;
}

//根据给定的可达表计算next表和distance表
void AbstractBox::calculate_path(bool reach_map[MAP_SIZE][MAP_SIZE]){
    queue<Position> path;
    init(path);
    Position now;
    while(!path.empty()){
        now = path.front();
        path.pop();
        int dis = distance[now.get_x()][now.get_y()];
        // 向上搜索
        if(distance[now.get_x() - 1][now.get_y()] == -1){
            if(reach_map[now.get_x() - 1][now.get_y()] && next[now.get_x() - 1][now.get_y()] == -1){
                path.push(Position(now.get_x(), now.get_y()));
                next[now.get_x() - 1][now.get_y()] = 3; // next记录操作为下：3
                distance[now.get_x() - 1][now.get_y()] = dis + 1;
            }
        }
        // 向下搜索
        if(distance[now.get_x() + 1][now.get_y()] == -1){
            if(reach_map[now.get_x() + 1][now.get_y()] && next[now.get_x() + 1][now.get_y()] == -1){
                path.push(Position(now.get_x() + 1, now.get_y()));
                next[now.get_x() + 1][now.get_y()] = 2; // next记录操作为上：2
                distance[now.get_x() + 1][now.get_y()] = dis + 1;
            }
        }
        // 向左搜索
        if(distance[now.get_x()][now.get_y() - 1] == -1){
            if(reach_map[now.get_x()][now.get_y() - 1] && next[now.get_x()][now.get_y() - 1] == -1){
                path.push(Position(now.get_x(), now.get_y() - 1));
                next[now.get_x()][now.get_y() - 1] = 0; // next记录操作为右：0
                distance[now.get_x()][now.get_y() - 1] = dis + 1;
            }
        }
        // 向右搜索
        if(distance[now.get_x()][now.get_y() + 1] == -1){
            if(reach_map[now.get_x()][now.get_y() + 1] && next[now.get_x()][now.get_y() + 1] == -1){
                path.push(Position(now.get_x(), now.get_y() + 1));
                next[now.get_x()][now.get_y() + 1] = 1; // next记录操作为左：1
                distance[now.get_x()][now.get_y() + 1] = dis + 1;
            }
        }
    }
}

// 初始化泊点搜索路径队列
void Berth::init(queue<Position> &path) {
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++){
            set_distance(get_x() + i, get_y() + j, 0);
            if(i == 0 || j == 0 || i == 3 || j == 3) path.push(Position(get_x() + i, get_y() + j));
        }
    }
}

// 初始化物品搜索路径队列
void Product::init(queue<Position> &path) {
    set_distance(get_x(), get_y(), 0);
    path.push(Position(get_x(), get_y()));
}


// 根据输入地图字符串初始化工作地图
void WorkMap::init(char** map_str){
    for(int i = 0; i < MAP_SIZE; i ++){
        for(int j = 0; j < MAP_SIZE; j ++){
            if(map_str[i][j] == '.') land[i][j] = true;
            else if(map_str[i][j] == '*') ocean[i][j] = true;
        }
    }
    
}

// 添加货物信息
void WorkMap::add_goods(int x, int y, int value)
{
    goods.push_back(Product(x, y, value));
}

// 添加泊点信息
void WorkMap::add_berth(int id, int x, int y, int time, int velocity)
{
    berth[id] = Berth(x, y, time, velocity);
}

// 返回距离最近的BERTH的id
int WorkMap::get_min_bert(Position &pos){
    int min_dis=65535, id = -1, berth_dis = 0;
    for(int i = 0; i < BERTH_NUM; i++){
        berth_dis = berth[i].get_distance(pos);
        if(berth_dis != -1 && min_dis > berth_dis){
            id = i;
            min_dis = berth_dis;
        }
    }
    return id;
}

// 返回到达指定BERTH的下一跳的方向，2、3、1、0分别代表上下左右
int WorkMap::get_next_to_bert(Position &pos, int berth_id){
    return berth[berth_id].get_next(pos.get_x(), pos.get_y());
}

// 返回距离最近的BERTH的下一跳的方向，2、3、1、0分别代表上下左右
int WorkMap::get_next_to_min_bert(Position &pos){
    return get_next_to_bert(pos, get_min_bert(pos));
}