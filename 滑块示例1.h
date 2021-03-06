//
//  Created by 关东升 on 15/12/10.
//  本书网站：http://www.51work6.com
//  智捷课堂在线课堂：http://www.zhijieketang.com/
//  智捷课堂微信公共号：zhijieketang
//  作者微博：@tony_关东升
//  作者微信：tony关东升
//  QQ：569418560 邮箱：eorient@sina.com
//  QQ交流群：162030268
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//UI控件所需的头文件
#include "ui/CocosGUI.h"

//UI控件所需要命名空间
using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Layer
{
	cocos2d::ui::Text* label2;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	//Slider滑动事件回调函数
	void onChangedSlider(Ref* pSender, Slider::EventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
