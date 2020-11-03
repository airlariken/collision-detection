//
//  QuadTree.cpp
//  四叉树
//
//  Created by 陈梓玮 on 2020/10/20.
//
#include "game.hpp"
int main()
{
    long int n;
    cout<<"enter the number the ball :";
    cin>>n;
    
    char co = ' ';
    cout<<"1.simple_collision_check     2.quadtree_collision_check"<<endl;
    cin>>co;
    
    game m_game(n);


    m_game.code = co;
    
    m_game.run();
    cout<<"window closed!"<<endl;
}

//test
//    clock_t start,stop;
//    double duration;
//    start = clock();
//
//    QuadTree m_tree;
//    for (int i = 0; i <10000; ++i)
//        m_tree.insert_by_index(new ball);
//
//
//    stop = clock();
//    duration = (double)(stop-start)/CLOCKS_PER_SEC;
//    cout<<duration<<endl;
//
////    ball* m_speci_ball = new ball;
////    m_tree.insert_by_index(m_speci_ball);
//
//
//    m_tree.check_colli();
