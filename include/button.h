#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Button
{
	//将需要用到Button的类定义为友员类，给app赋值
	friend class StartScene;
	friend class GameScene;
	friend class Menu;
public:

    enum Type {Texture_type, Shape_type};
    Type type; //是材质还是形状
    Color rectcolor;


	Button():app(NULL),isActive(false),PreBehRel(false),type(Texture_type),rectcolor(sf::Color(128,128,128)) {};
    Button(RenderWindow &window, Type button_type = Texture_type, Color color = sf::Color(128,128,128)):app(&window),isActive(false),PreBehRel(false),type(button_type),rectcolor(color) {};

	bool isActive;//按钮是否活跃状态,这个后面会解释
	bool PreBehRel;//松开之前是否按下，这个后面会解释


	void setTextrue(String s);//设置贴图路径
	void setScale(float x, float y);//大小

    void setShapeSize(float x, float y);
    void setPosition(int x, int y);//位置

	void draw();//显示按钮
	bool onClick(Event& e);//按钮响应
	Sprite s;//精灵
    RectangleShape rectangle; //矩形
    
	RenderWindow* app;//在app窗口中显示按钮
private:
    
	Texture t;//贴图
};
