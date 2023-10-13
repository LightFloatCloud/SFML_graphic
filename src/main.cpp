#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <stdlib.h>

//sf::RenderWindow window(sf::VideoMode(800, 600), "myproject");

int main()
{
    //auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    //sf::Window window(sf::VideoMode(800, 600), "myproject");
    system("chcp 65001");
    
    int width = 800, height = 600;
    const wchar_t* title = L"中文标题 SFML程序";




    sf::RenderWindow window(sf::VideoMode(width, height), title);
    window.setFramerateLimit(2);
    window.setKeyRepeatEnabled(false);
    
    sf::Clock clock; // starts the clock
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                // we don't process other types of events
                case sf::Event::Resized:
                    std::cout << "new width: " << event.size.width << std::endl;
                    std::cout << "new height: " << event.size.height << std::endl;
                    break;

                case sf::Event::LostFocus:
                    std::cout << "Lose Focus!" << std::endl;
                    break;
                case sf::Event::GainedFocus:
                    std::cout << "Gained Focus!" << std::endl;
                    break;

                case sf::Event::TextEntered:
                    if (event.text.unicode < 128)
                        std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
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
                
                case sf::Event::MouseWheelScrolled:
                    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                        std::cout << "wheel type: vertical" << std::endl;
                    else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                        std::cout << "wheel type: horizontal" << std::endl;
                    else
                        std::cout << "wheel type: unknown" << std::endl;
                    std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                    std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                    std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    }
                    break;

                default:
                    break;
            }
        }
        
        // 时间部分
        sf::Time elapsed = clock.getElapsedTime();
        //std::cout << elapsed.asSeconds() << std::endl;
        //clock.restart();


        // std::random_device rd;  // 随机设备，用于获取种子
        // std::mt19937 gen(rd());  // Mersenne Twister 伪随机数生成器
        // std::uniform_int_distribution<int> distribution(0, 1000);  // 定义随机数分布

        // int random_x = distribution(gen);  // 生成随机整数
        // int random_y = distribution(gen);  // 生成随机整数
        // std::cout << "随机整数: " << random_x << " " << random_y << std::endl;
        // window.setPosition(sf::Vector2i(random_x, random_y));
        
        window.clear(sf::Color(0, 0, 0, 0));

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
        text.setString(L"国 际 五 子 棋");
        text.setCharacterSize(48); 
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        window.draw(text);

    

        window.display();
    }
}