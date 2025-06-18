

#ifndef  _GAME_DELEGATE_H_
#define  _GAME_DELEGATE_H_

#include "cocos2d.h"
#include "../services/GameModelFromLevelGenerator.h"
#include "../services/UndoService.h"
/**
@brief    The cocos2d Application.全局游戏控制器
私有继承 对director隐藏部分接口
Private inheritance here hides part of interface from Director.
*/
class  GameController : private cocos2d::Application
{
public:
    GameController();
    virtual ~GameController();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here. 初始化函数
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  Called when the application moves to the background，程序移动到后台时调用
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  Called when the application reenters the foreground，程序即将进入前台时执行
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

};

#endif // _APP_DELEGATE_H_

