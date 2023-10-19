#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <stdlib.h>
#include <sstream> // 小数输出
#include <iomanip>

#include "button.h"

//sf::RenderWindow window(sf::VideoMode(800, 600), "myproject");

int width = 800, height = 600;

int qipan[15][15] = {0};

sf::Font font;

sf::Texture texture;
sf::Texture qizi;

int turn = 0; //黑棋先
const float time_chaoshi = 10.f;

void background_draw(sf::RenderWindow &window)
{
    // 纹理部分
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
}

void paint_start_draw(sf::RenderWindow &window) 
{


    // 形状
    float radius = 30.f;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    //circle.setFillColor(sf::Color(255, 0, 0));
    circle.setOutlineThickness(20.f);
    circle.setOutlineColor(sf::Color::Black);
    
    circle.setOrigin(sf::Vector2f(radius, radius));
    circle.setPosition(sf::Vector2f(width/2, height/2));
    window.draw(circle);



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


const float pixel_gap = 36;
const int top = 48;
const int left = 148;
const int cell = 15 - 1;


sf::Vector2i latest_pos(-1, -1);

void paint_qipan(sf::RenderWindow &window) 
{

    const float thickness = 2.0f;
    const Color line_color(0, 0, 0, 255);

    for(int i = 0; i < cell; i++) {
        
        for(int j = 0; j < cell; j++) {
            float x = left + pixel_gap * i;
            float y = top + pixel_gap * j;

            //std::vector<sf::Vertex> vertices;
            //vertices.push_back(sf::Vertex(...));
            // sf::Vertex vertices[5] =
            // {
            //     sf::Vertex(sf::Vector2f(x, y), Color(0, 0, 0, 255)),
            //     sf::Vertex(sf::Vector2f(x + pixel_gap, y), Color(0, 0, 0, 255)),
            //     sf::Vertex(sf::Vector2f(x + pixel_gap, y + pixel_gap), Color(0, 0, 0, 255)),
            //     sf::Vertex(sf::Vector2f(x, y + pixel_gap), Color(0, 0, 0, 255)),
            //     sf::Vertex(sf::Vector2f(x, y), Color(0, 0, 0, 255))
            // };
            // window.draw(vertices, 5, sf::LineStrip);

            sf::RectangleShape line1(sf::Vector2f(pixel_gap, thickness));
            line1.setPosition(x, y);
            line1.setFillColor(line_color);
            sf::RectangleShape line2(sf::Vector2f(pixel_gap, thickness));
            line2.rotate(90.f);
            line2.setPosition(x, y);
            line2.setFillColor(line_color);
            sf::RectangleShape line3(sf::Vector2f(pixel_gap, thickness));
            line3.setPosition(x, y + pixel_gap);
            line3.setFillColor(line_color);
            sf::RectangleShape line4(sf::Vector2f(pixel_gap, thickness));
            line4.rotate(90.f);
            line4.setPosition(x + pixel_gap, y);
            line4.setFillColor(line_color);

            window.draw(line1);
            window.draw(line2);
            window.draw(line3);
            window.draw(line4);

        }
        
    }

    qizi.setSmooth(true);
    //qizi.setRepeated(true);

    sf::Sprite baiqi, heiqi;
    
    

    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            if(qipan[i][j] == 1) { // 黑棋
                sf::Sprite heiqi;
                heiqi.setTexture(qizi);
                heiqi.setTextureRect(sf::IntRect(0, 0, 64, 64));

                heiqi.setOrigin(32, 32);
                heiqi.setScale(pixel_gap/64, pixel_gap/64);

                heiqi.setPosition(left + j * pixel_gap, top + i * pixel_gap);
                window.draw(heiqi);

            }
            else if(qipan[i][j] == 2) {
                baiqi.setTexture(qizi);
                baiqi.setTextureRect(sf::IntRect(64, 0, 64, 64));
                baiqi.setOrigin(32, 32);
                baiqi.setScale(pixel_gap/64, pixel_gap/64);
                baiqi.setPosition(left + j * pixel_gap, top + i * pixel_gap);
                window.draw(baiqi);
            }
        }
    }

    if(latest_pos.x >= 0 && latest_pos.y >= 0) {
        // 形状
        float radius = pixel_gap / 6;
        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::Red);
        //circle.setOutlineThickness(10.f);
        //circle.setOutlineColor(sf::Color(250, 150, 100));
        
        circle.setOrigin(sf::Vector2f(radius, radius));
        circle.setPosition(left + latest_pos.x * pixel_gap, top + latest_pos.y * pixel_gap);
        window.draw(circle);

    }




}

void paint_time(sf::RenderWindow &window, sf::Clock clock)
{
    float now = clock.getElapsedTime().asSeconds();

    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << now;
    std::string strValue = ss.str();


    sf::Text text;
    text.setFont(font); 
    text.setString(L"读秒: " + strValue);
    text.setCharacterSize(24); 
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setLetterSpacing(1.0f);
    //text.setOrigin(text.findCharacterPos(0) + sf::Vector2f(12.f,12.f));
    text.setPosition(sf::Vector2f(15.f, 30.f));
    window.draw(text);
    
}

int is_finished()
{
    if(latest_pos.x < 0 || latest_pos.y < 0) {
        return 0;
    }
    else {
        int current_qizi = qipan[latest_pos.y][latest_pos.x];

        int dx[] = {1, 0, 1, 1};  // 方向数组，分别代表水平、垂直、左上到右下、左下到右上
        int dy[] = {0, 1, 1, -1};

        for(int dst = 0; dst < 4; dst ++) {
            int line_qizi = 1;
            for(int k = 1; k <= 4; k++) {
                int newX = latest_pos.x + k * dx[dst];
                int newY = latest_pos.y + k * dy[dst];

                if (newX >= 0 && newX < 15 && newY >= 0 && newY < 15 && qipan[newY][newX] == current_qizi) {
                    line_qizi++;
                } else {
                    break;
                }
            }
            for(int k = 1; k <= 4; k++) {
                int newX = latest_pos.x - k * dx[dst];
                int newY = latest_pos.y - k * dy[dst];

                if (newX >= 0 && newX < 15 && newY >= 0 && newY < 15 && qipan[newY][newX] == current_qizi) {
                    line_qizi++;
                } else {
                    break;
                }
            }

            if(line_qizi >= 5) {
                return current_qizi;
            }
            
        }
        
        
        return 0;
        
    }
}

int main()
{
    //system("chcp 65001");
    
    
    const wchar_t* title = L"中文标题 SFML程序";
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


// 窗口初始化
    sf::RenderWindow window(sf::VideoMode(width, height), title, Style::Default - Style::Resize, settings);
    window.setFramerateLimit(10);
    window.setKeyRepeatEnabled(false);
    
    sf::Clock clock; // starts the clock


// 按钮初始化
    Button bt_start(window);
    bt_start.type = Button::Shape_type;
    bt_start.setShapeSize(220.f, 60.f);//大小
    bt_start.setPosition(400, 440);//位置
    bt_start.rectangle.setFillColor(sf::Color(100,150,25));
    bt_start.isActive = true;

// 贴图初始化
    if (!texture.loadFromFile("./resourse/wood2.jpg",  sf::IntRect(0, 0, 800, 600))) {
        // error...
        std::cout << "ERRER OCCURED! --loadFromFile: Texture" << std::endl;
    }
    if (!qizi.loadFromFile("./resourse/qizi.png")) {
        // error...
        std::cout << "ERRER OCCURED! --loadFromFile: Qizi" << std::endl;
    }
    // 字体
    if (!font.loadFromFile("./resourse/simhei.ttf"))
    {
        // error...
        std::cout << "ERRER OCCURED! --loadFromFile: Font" << std::endl;
    }

    
    uint8_t win_state = 0;


    while (window.isOpen())
    {
        window.clear(sf::Color(0, 0, 0, 0));
        background_draw(window);    // 画背景
        


        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                // case sf::Event::KeyPressed:
                //     if (event.key.scancode == sf::Keyboard::Scan::Escape)
                //     {
                //         std::cout << "the escape key was pressed" << std::endl;
                //         std::cout << "scancode: " << event.key.scancode << std::endl;
                //         std::cout << "code: " << event.key.code << std::endl;
                //         std::cout << "control: " << event.key.control << std::endl;
                //         std::cout << "alt: " << event.key.alt << std::endl;
                //         std::cout << "shift: " << event.key.shift << std::endl;
                //         std::cout << "system: " << event.key.system << std::endl;
                //         std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
                //         std::cout << "localize: " << sf::Keyboard::localize(event.key.scancode) << std::endl;
                //         std::cout << "delocalize: " << sf::Keyboard::delocalize(event.key.code) << std::endl;
                //     }
                //     else {
                //         std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
                //     }
                //     break;
                
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        // std::cout << "the right button was pressed" << std::endl;
                        // std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        // std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    }
                    else if(event.mouseButton.button == sf::Mouse::Left) {
                    //    if (event.mouseButton.x <)
                        int mousex = Mouse::getPosition(window).x;
                        int mousey = Mouse::getPosition(window).y;
                        if(win_state == 1 && mousex >= left - pixel_gap/2 && mousex < left + cell * pixel_gap + pixel_gap/2
                            && mousey >= top - pixel_gap/2 && mousey < top + cell * pixel_gap + pixel_gap/2) {

                                int pos_index_x = (mousex + pixel_gap/2 - left) / pixel_gap;
                                int pos_index_y = (mousey + pixel_gap/2 - top) / pixel_gap;
                                if(qipan[pos_index_y][pos_index_x] != 0) {
                                    break;
                                }

                                if(turn == 0) {
                                    turn = 1;
                                    qipan[pos_index_y][pos_index_x] = 1;
                                }
                                else if (turn == 1)
                                {
                                    turn = 0;
                                    qipan[pos_index_y][pos_index_x] = 2;
                                }
                                latest_pos.x = pos_index_x;
                                latest_pos.y = pos_index_y;
                                

                                clock.restart();
                        }
                    }
                    break;

                default:
                    break;
            }

            if(bt_start.onClick(event) == true) {
                win_state = 1;
                bt_start.isActive = false;
                clock.restart();
            } // 配置按钮
        }
        
        // 时间部分
        sf::Time elapsed = clock.getElapsedTime();
        //std::cout << elapsed.asSeconds() << std::endl;
        //clock.restart();


        
        


        sf::Text text;
        switch (win_state)
        {
            
        case 0:
            paint_start_draw(window);  
            bt_start.draw(); // 画按钮
            
            break;
        case 1:
            paint_qipan(window);
            paint_time(window, clock);
            if(elapsed.asSeconds() > time_chaoshi || is_finished() != 0) {
                //return 1;
                win_state = 2;
                clock.restart();
            }

            break;
        
        case 2:
            paint_qipan(window);
            if(elapsed.asSeconds() > 3.f) {
                return 0;
            }

            
            text.setFont(font); 

            {
                int res = is_finished();
                if(res == 0) {
                    text.setString(L"超 时");
                    text.setFillColor(sf::Color::Red);
                }
                else if(res == 1) {
                    text.setString(L"黑棋胜");
                    text.setFillColor(sf::Color::Black);
                }
                else if(res == 2) {
                    text.setString(L"白棋胜");
                    text.setFillColor(sf::Color::White);
                }
            }
            
            text.setCharacterSize(48); 
            text.setStyle(sf::Text::Bold);
            text.setLetterSpacing(2.0f);
            text.setOrigin(text.findCharacterPos(1) + sf::Vector2f(24.f,24.f));
            text.setPosition(sf::Vector2f(width/2, height *2/5));
            window.draw(text);

            break;

        default:
            break;
        }

        
    
        window.display();
    }


    return 0;
}