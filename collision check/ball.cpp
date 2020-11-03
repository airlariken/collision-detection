//
//  ball.cpp
//  sfml draft
//
//  Created by 陈梓玮 on 2020/10/23.
//

#include "ball.hpp"


//constructor$destructor
ball::ball()
{
    random_device rd;
    uniform_int_distribution<int> un(-1, 1);
    uniform_int_distribution<int> un1(0, boundx);
    uniform_int_distribution<int> un2(0, boundy);
//    srand((unsigned)time(NULL));
//    dx = (rand()% (10-0))+0;
//    dy = (rand()% (10-0))+0;
    //处理等于0的情况
    
    dx = un(rd);
    dy = un(rd);
    if(dx==0&&dy==0)
        dx = -1;
    m_ball.setPosition(un1(rd),un2(rd));//randow pos
    m_ball.setRadius(ball_r);
    m_ball.setFillColor(sf::Color::Red);

    
}



//functions


