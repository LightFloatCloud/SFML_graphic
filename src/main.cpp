#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <stdlib.h>

#include "button.h"

//sf::RenderWindow window(sf::VideoMode(800, 600), "myproject");

int width = 800, height = 600;

void paint_draw(sf::RenderWindow &window) 
{
    // 纹理部分
    sf::Texture texture;
    if (!texture.loadFromFile("./resourse/wood1.jpg",  sf::IntRect(0, 0, 800, 600)))
    {
        // error...
        std::cout << "ERRER OCCURED! --loadFromFile: Texture" << std::endl;
    }
    texture.setSmooth(true);
    texture.setRepeated(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    //sprite.setTextureRect(sf::IntRect(10, 10, 32, 32));
    //sprite.setColor(sf::Color(0, 255, 0)); // green
    //sprite.setColor(sf::Color(255, 255, 255, 128)); // half transparent

    // // position
    // sprite.setPosition(sf::Vector2f(10.f, 50.f)); // absolute position
    // sprite.move(sf::Vector2f(5.f, 10.f)); // offset relative to the current position

    // // rotation
    // sprite.setRotation(90.f); // absolute angle
    // sprite.rotate(15.f); // offset relative to the current angle

    // // scale
    // sprite.setScale(sf::Vector2f(0.5f, 2.f)); // absolute scale factor
    // sprite.scale(sf::Vector2f(1.5f, 3.f)); // factor relative to the current scale
    window.draw(sprite);

    // 形状
    float radius = 50.f;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Cyan);
    //circle.setFillColor(sf::Color(255, 0, 0));
    circle.setOutlineThickness(10.f);
    circle.setOutlineColor(sf::Color(250, 150, 100));
    
    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setPosition(sf::Vector2f(width/2, height/2));
    window.draw(circle);



    // 字体
    sf::Font font;
    if (!font.loadFromFile("./resourse/simhei.ttf"))
    {
        // error...
        std::cout << "ERRER OCCURED! --loadFromFile: Font" << std::endl;
    }

    sf::Text text;
    text.setFont(font); 
    text.setString(L"国际五子棋");
    text.setCharacterSize(48); 
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setLetterSpacing(4.0f);
    //std::cout<< text.findCharacterPos(2).x << " " << text.findCharacterPos(2).y <<std::endl;
    text.setOrigin(text.findCharacterPos(2) + sf::Vector2f(24.f,24.f));
    text.setPosition(sf::Vector2f(width/2, height/4));
    window.draw(text);







}





int main()
{
    system("chcp 65001");
    
    
    const wchar_t* title = L"中文标题 SFML程序";

    uint8_t win_state = 0;


    sf::RenderWindow window(sf::VideoMode(width, height), title);
    window.setFramerateLimit(10);
    window.setKeyRepeatEnabled(false);
    
    sf::Clock clock; // starts the clock

    Button bt_start(window);
    bt_start.type = Button::Shape_type;
    bt_start.setShapeSize(220.f, 60.f);//大小
    bt_start.setPosition(400, 440);//位置
    bt_start.rectangle.setFillColor(sf::Color(100,150,25));
    bt_start.isActive = true;

    while (window.isOpen())
    {
        window.clear(sf::Color(0, 0, 0, 0));
        paint_draw(window);  // 画背景


        

        



        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.scancode == sf::Keyboard::Scan::Escape)
                    {
                        std::cout << "the escape key was pressed" << std::endl;
                        std::cout << "scancode: " << event.key.scancode << std::endl;
                        std::cout << "code: " << event.key.code << std::endl;
                        std::cout << "control: " << event.key.control << std::endl;
                        std::cout << "alt: " << event.key.alt << std::endl;
                        std::cout << "shift: " << event.key.shift << std::endl;
                        std::cout << "system: " << event.key.system << std::endl;
                        std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
                        std::cout << "localize: " << sf::Keyboard::localize(event.key.scancode) << std::endl;
                        std::cout << "delocalize: " << sf::Keyboard::delocalize(event.key.code) << std::endl;
                    }
                    else {
                        std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
                    }
                    break;
                
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    }
                    else if(event.mouseButton.button == sf::Mouse::Left) {
                    //    if (event.mouseButton.x <)
                    }
                    break;

                default:
                    break;
            }

            bt_start.onClick(event); // 配置按钮
        }
        
        // 时间部分
        sf::Time elapsed = clock.getElapsedTime();
        //std::cout << elapsed.asSeconds() << std::endl;
        //clock.restart();


        
        



        switch (win_state)
        {
            Event e;
        case 0:
            
            bt_start.draw(); // 画按钮
            

            break;
        
        default:
            break;
        }

        
    
        window.display();
    }
}