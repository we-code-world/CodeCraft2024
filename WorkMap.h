#ifndef WORK_MAP_H
#define WORK_MAP_H

#include "config.h"

class Position
{
private:
    int x, y;

public:
    Position();
    Position(int a, int b);
    Position(const Position &pos);
    ~Position();

    int get_x();
    int get_y();
    void set_x(int a);
    void set_y(int b);
    void set_xy(int a, int b);
    bool operator==(const Position &pos);
};

class AbstractBox : public Position
{
private:
    int next[MAP_SIZE][MAP_SIZE]; // 到达该位置的下一跳方向，2、3、1、0分别代表上下左右
    int distance[MAP_SIZE][MAP_SIZE]; // 距离该位置的实际帧数
public:
    AbstractBox();
    ~AbstractBox();

    void set_next(Position &now, int value);
    void set_distance(Position &now, int value);
    void set_next(int x, int y, int value);
    void set_distance(int x, int y, int value);
    int get_next(Position &now);
    int get_distance(Position &now);
    int get_next(int x, int y);
    int get_distance(int x, int y);

    virtual void init(queue<Position> &path) = 0;
    void calculate_path(bool reach_map[MAP_SIZE][MAP_SIZE]); // 根据可达表计算next表和distance表
};

class Berth : public AbstractBox
{
private:
    // time为轮船在该泊位与虚拟点之间的运输时间，velocity为该泊位每帧可以装载的物品数
    int time, velocity;

public:
    Berth();
    Berth(Position &pos, int time, int velocity);
    Berth(int x, int y, int time, int velocity);
    ~Berth();

    void set_time(int time);
    void set_velocity(int velocity);
    int get_time();
    int get_velocity();


    // 初始化泊点搜索路径队列
    void init(queue<Position> &path);
};

class Product : public AbstractBox
{
private:
    int value;

public:
    Product();
    Product(Position &pos, int value);
    Product(int x, int y, int value);
    ~Product();

    void set_value(int value);
    int get_value();
    // 初始化物品搜索路径队列
    void init(queue<Position> &path);
};

class WorkMap
{
private:
    vector<Product> goods; // 地图上的货物价值信息表
    Berth berth[BERTH_NUM]; // 
    bool land[MAP_SIZE][MAP_SIZE], ocean[MAP_SIZE][MAP_SIZE]; // land为陆地空地表，ocean为海洋可达表

public:
    WorkMap();
    ~WorkMap();
    WorkMap(char** map);

    // 根据输入地图字符串初始化工作地图
    void init(char** map_str);

    // 添加货物信息
    void add_goods(int x, int y, int value);

    // 添加泊点信息
    void add_berth(int id, int x, int y, int time, int velocity);

    // 返回距离最近的BERTH的id
    int get_min_bert(Position &pos);

    // 返回到达指定BERTH的下一跳的方向，2、3、1、0分别代表上下左右
    int get_next_to_bert(Position &pos, int berth_id);

    // 返回距离最近的BERTH的下一跳的方向，2、3、1、0分别代表上下左右
    int get_next_to_min_bert(Position &pos);
    
};

#endif