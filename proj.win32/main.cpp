

#include "main.h"
#include "controllers/GameController.h"
#include "cocos2d.h"

USING_NS_CC;

//win32���ڣ�Ĭ����ں���
int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    GameController app;    //һ��˽�м̳���Application����
    return Application::getInstance()->run();   //����ʵ��,�൱��((Application*) &app)->run()
}
