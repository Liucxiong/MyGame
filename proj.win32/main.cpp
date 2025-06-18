

#include "main.h"
#include "controllers/GameController.h"
#include "cocos2d.h"

USING_NS_CC;

//win32窗口，默认入口函数
int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    GameController app;    //一个私有继承自Application的类
    return Application::getInstance()->run();   //启动实例,相当于((Application*) &app)->run()
}
