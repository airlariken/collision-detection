//
//  ball.hpp
//  sfml draft
//
//  Created by 陈梓玮 on 2020/10/23.
//

#ifndef ball_hpp
#define ball_hpp

#include "state.hpp"
#define ball_r 1  //定义半径
//定义边界啊

class ball
{
private:
    int dx;
    int dy;
public:
     ball();
    sf::CircleShape m_ball;
    void draw(sf::RenderWindow* window){window->draw(m_ball);}
    inline void move_ball(){m_ball.move(dx, dy);}
    inline void reverse_dirction(){dx = -dx;dy = -dy;}
    inline void rev_x(){dx=-dx;}
    inline void rev_y(){dy=-dy;}
};



#endif /* ball_hpp */
