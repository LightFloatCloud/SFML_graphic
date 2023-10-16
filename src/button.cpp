#include "button.h"

void Button::setTextrue(String s)
{
	this->t.loadFromFile(s);
	this->s.setTexture(this->t);
}

void Button::setPosition(int x, int y)
{
    if(this->type == Texture_type) {
        this->s.setPosition(x, y);
    }
    else if(this->type == Shape_type) {
        this->rectangle.setPosition(x, y);
    }
}

void Button::setScale(float x, float y)
{
	this->s.setScale(x, y);
}

void Button::setShapeSize(float x, float y)
{
	this->rectangle.setSize(sf::Vector2f(x, y));
    this->rectangle.setOrigin(sf::Vector2f(x/2, y/2));
}



bool Button::onClick(Event& e)
{
	if (!isActive) //如果按钮不是活跃状态（不显示），不响应
		return false;
	bool flag = false;
	FloatRect box;
    if (this->type == Texture_type) {
        box = s.getGlobalBounds();//获取按钮的有效点击范围
    }
    else if(this->type == Shape_type) {
        box = rectangle.getGlobalBounds();
    }

	if (Mouse::getPosition(*app).x >= box.left && Mouse::getPosition(*app).x <= (box.left + box.width) && Mouse::getPosition(*app).y >= box.top && Mouse::getPosition(*app).y <= (box.top + box.height))
	{
		if (e.type == Event::MouseButtonReleased && e.mouseButton.button == Mouse::Left && PreBehRel)
		{
			this->PreBehRel = false;//要先按下再松开才返回true，置于为什么要判断先按下，后面会讲
			flag = true;
		}
		else
			flag = false;
		if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
		{
            if (this->type == Texture_type) {
                this->s.setColor(Color(125, 125, 0, 255));//按钮按下时的颜色和不透明度
            }
            else if(this->type == Shape_type) {
                Color fillcolor = this->rectcolor;
                fillcolor.r = fillcolor.r * 0.8;
                fillcolor.g = fillcolor.g * 0.8;
                fillcolor.b = fillcolor.b * 0.8;
                fillcolor.a = 255;
                this->rectangle.setFillColor(fillcolor);
            }
			this->PreBehRel = true;
		}
		else
        {
            if (this->type == Texture_type) {
                this->s.setColor(Color(125, 125, 0, 100));//鼠标指着按钮但未按下时的颜色和不透明度
            }
            else if(this->type == Shape_type) {
                Color fillcolor = this->rectcolor;
                fillcolor.a = 100;
                this->rectangle.setFillColor(fillcolor); //鼠标指着按钮但未按下
            }
        }
			
	}
	else
    {
        if (this->type == Texture_type) {
            this->s.setColor(Color(255,255,255, 255));//默认状态的按钮颜色
        }
        else if(this->type == Shape_type) {
            Color fillcolor = this->rectcolor;
            fillcolor.a = 255;
            this->rectangle.setFillColor(fillcolor);//默认状态的按钮颜色
        }
    }
		
	return flag;
}

void Button::draw()
{
	isActive = true;//若要显示，则为活跃状态
    if (this->type == Texture_type) {
        (*app).draw(s);
    }
    else if(this->type == Shape_type) {
        (*app).draw(rectangle);
    }
	
}
