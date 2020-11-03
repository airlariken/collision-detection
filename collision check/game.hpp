//
//  game.hpp
//  sfml draft
//
//  Created by 陈梓玮 on 2020/10/22.
//

#ifndef game_hpp
#define game_hpp
#include "QuadTree.hpp"
//#include "GameState.hpp"
//#include "ball.hpp"
//#include <thread>
class game
{
private:
    //variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock dtclock;
    float dt;   //计算每一帧所需时间
    
    sf::Vector2f bound;//存储边界数据
    
    QuadTree m_tree;
//    vector<ball*> v;
    //top是目前的窗口，不断刷新维护该窗口
//    stack<state*> states;//virtual class, only pointer 可以指向派生类对象
    vector<ball*> balls;


    //initialization
    void iniwindow();
    void inistate();//暂时用不上
public:
    //construcitor&destructor
    game(long int);
    virtual ~game();
    //functions
    virtual void update();
    virtual void render();
    virtual void endState(){}
    void updateSFMLEvents();
    void updateDt();
    void run();
    void qua_tree_col_check();

    static long int num;//小球目前个数（朴素）
    char code;//朴素or四叉树选择
    
    long int ball_number;//小球个数
    
    void simple_collision_check();
    
    
};



#endif /* game_hpp */
