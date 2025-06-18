

#ifndef  _GAME_DELEGATE_H_
#define  _GAME_DELEGATE_H_

#include "cocos2d.h"
#include "../services/GameModelFromLevelGenerator.h"
#include "../services/UndoService.h"
/**
@brief    The cocos2d Application.ȫ����Ϸ������
˽�м̳� ��director���ز��ֽӿ�
Private inheritance here hides part of interface from Director.
*/
class  GameController : private cocos2d::Application
{
public:
    GameController();
    virtual ~GameController();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here. ��ʼ������
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  Called when the application moves to the background�������ƶ�����̨ʱ����
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  Called when the application reenters the foreground�����򼴽�����ǰ̨ʱִ��
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

};

#endif // _APP_DELEGATE_H_

