//
//  game.cpp
//  sfml draft
//
//  Created by 陈梓玮 on 2020/10/22.
//

#include "game.hpp"
//#define ball_num 1000
//initialization
long int game::num = 0;
void game::iniwindow()
{
    //暂时用不上下方setting
//    sf::ContextSettings::
    bound.x = boundx;
    bound.y = boundy;
    this->window = new sf::RenderWindow(sf::VideoMode(bound.x,bound.y), "my fxxking window");
    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
        
}
//暂时用不上
void game::inistate()
{
//    this->states.push(new GameState(this->window));
}
//construcitor&destructor
game::game(long int a)
{
    ball_number = a;
    this->iniwindow();
//    this->inistate();
//    cin>>ball_number;
    for (int i = 0; i <ball_number; ++i)            //四叉树建立
        m_tree.insert_by_index(new ball);
}

game::~game()
{

    delete this->window;
    
    //暂时用不上
//    while (!this->states.empty()) {
//        delete states.top();
//        states.pop();
//    }
    
    //朴素碰撞内存管理
//    for (int i = 0; i < balls.size(); ++i){
//        delete balls[i];
//    }

}


//Functions
void game::update()
{
    this->updateSFMLEvents();
//    if (!this->states.empty()) {
//        this->states.top()->update(dt);
//    }
}

void game::render()
{
    window->clear();
    switch (code) {
        case '1':
            simple_collision_check();
            break;
        case '2':
    qua_tree_col_check();
            break;
        default:
            break;
    }
    //暂时用不上
//    if (!this->states.empty()) {
//        this->states.top()->render();
//    }
    

    
 

//    cout<<num;
    
    
    window->display();
}
void game::updateSFMLEvents()
{
    while (this->window->pollEvent(sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}
void game::updateDt()
{
    //update the dt variable with the time it takes to update and render one frame.
    system("clear");
    this->dt = this->dtclock.restart().asSeconds();
    cout<<this->dt<<endl;
}
void game::run()
{
    while (this->window->isOpen()) {
        this->updateDt();
        this->render();
        this->update();
    }
}

void game::qua_tree_col_check()//四叉树碰撞检测
{   
    m_tree.check_colli();
//    cout<<m_tree.count<<endl;
    m_tree.check_bound(m_tree.root, m_tree.check_obj_gra_bound);
    m_tree.show_ball(this->window, m_tree.root);
    m_tree.maintain_tr(m_tree.root);
}

void game::simple_collision_check()//朴素碰撞检测
{
    //render item
    //每一帧添加一个小球ball_number
    for (; num < ball_number; ++num){
        balls.push_back(new ball);
    }

    //每一帧移动各个小球
    for (int i = 0; i < num; ++i){
        balls[i]->move_ball();
        window->draw(balls[i]->m_ball);
    }
    //朴素碰撞检测
    for (int i = 0;  i < num; ++i) {
        for (int j = i+1; j < num; ++j) {
            int x =balls[i]->m_ball.getPosition().x - balls[j]->m_ball.getPosition().x;
            int y = balls[i]->m_ball.getPosition().y-balls[j]->m_ball.getPosition().y;
            if (x*x+y*y<ball_r*ball_r*5) {
                balls[i]->reverse_dirction();
                balls[j]->reverse_dirction();

//                if (x*x+y*y<ball_r*ball_r*4){//对于贴太近的。。。还没搞好
//                    balls[i]->reverse_dirction();
//                    balls[j]->reverse_dirction();
//                    for(int x = 0; x < 5;++x){
//                        balls[i]->move_ball();
//                        balls[j]->move_ball();
//                    }
//                }
            }
        }
    }
    
//    int ball_radius = 10;
    //边界检测
    for (int i = 0;  i < num; ++i) {
            if (bound.x-balls[i]->m_ball.getPosition().x<ball_r || balls[i]->m_ball.getPosition().x<ball_r)
                balls[i]->rev_x();
        if (bound.y-balls[i]->m_ball.getPosition().y<ball_r || balls[i]->m_ball.getPosition().y<ball_r)
            balls[i]->rev_y();
    }
    
    //总共的小球个数
    if (num<ball_number)
        num += 10;
}
