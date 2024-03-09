#include "Controller.h"
//using namespace std;

int main() {
    // 控制器对象
    Controller main_controller;

    // 初始化状态信息
    main_controller.init();

    // 控制器运行
    main_controller.run();

    return 0;
}