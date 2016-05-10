#ifndef EDITLAYER_H
#define EDITLAYER_H

#include "cocos2d.h"
#include "ccTypes.h"

// ±à¼­²ã
using namespace cocos2d;
#define EDIT_LAYER_ALPHA	255
class EditLayer : public cocos2d::CCLayer
{
public:
	enum GLPenColor
	{
		GL_Red,
		GL_Blue, 
		GL_Green,
		GL_Black,
		GL_Pink,
		GL_Grey,
		GL_Yellow,
		GL_Orange,
		GL_Purple,
		GL_Brown,   
		GL_White,
		GL_Dark_Green,
		GL_Light_Blue,
		GL_Light_Grey,
		GL_Light_Pink,
		GL_Hollow
	};
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    //static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(EditLayer);

	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	virtual void draw();

protected:
	// ¹¤¾ßº¯Êý
	void RenderGraph();
	void RenderNavGraph();
	// ÇÐ»»ÑÕÉ«
	void ChangeColor(GLPenColor color);

private:
	ccColor4B	m_pTerrainColor;
};

#endif // EDITLAYER_H
