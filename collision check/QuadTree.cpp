//
//  QuadTree.cpp
//  四叉树
//
//  Created by 陈梓玮 on 2020/10/23.
//

#include "QuadTree.hpp"
//long int QuadTree::count = 0;
//construtor&destructor
QuadTree::QuadTree()
{
    root = new QuadTreeNode;
    cout<<"quadtree in"<<endl;
}
QuadTree::~QuadTree()
{
    pre_order(root, del_ball);
    del_tree(root);
    if (root !=nullptr)
        delete root;
    root = nullptr;
    }

//functions
//4，3，2，1，0分别对应 右下 右上 左下 左上 和 坐标轴上 的5个分区
int QuadTree::get_index(ball* b,QuadTreeNode* &cur)
{
    int bx = b->m_ball.getPosition().x, by = b->m_ball.getPosition().y;
    if ( by == cur->bound.y+cur->bound_height/2)//b->m_ball.getPosition().y
        return 3;//y轴坐标轴上的归入第四象限
    
    if(bx > cur->bound.x+cur->bound_wide/2){//b->m_ball.getPosition().x
        if (by > cur->bound.y+cur->bound_height/2)//b->m_ball.getPosition().y
            return 3;
        else
            return 2;
    }
    else if((bx < cur->bound.x+cur->bound_wide/2)){//b->m_ball.getPosition().x
            if(by>cur->bound.y+cur->bound_height/2)//b->m_ball.getPosition().y
                return 1;
            else    return 0;
        }
    else return 0;//x坐标轴归入第一象限
}
void QuadTree::insert_obj(ball *b,QuadTreeNode* &cur,int index)//将该元素插入的对于子树（象限）的节点内
{
    cur->Quadrant[index]->balls.push_back(b);
}

void QuadTree::divide(QuadTreeNode* &cur)
{
    if (cur->Quadrant[0]==NULL) {       //如果没有子树，则new，有的话直接分配下去
        for (int i = 0 ; i<4 ; i++) {
            cur->Quadrant[i] = new QuadTreeNode;
            cur->Quadrant[i]->depth = cur->depth+1;
            cur->Quadrant[i]->bound_height = cur->bound_height/2;
            cur->Quadrant[i]->bound_wide = cur->bound_wide/2;
        }
        cur->Quadrant[3]->bound.x = cur->bound.x+cur->bound_wide/2;
        cur->Quadrant[3]->bound.y = cur->bound.y+cur->bound_height/2;
        cur->Quadrant[2]->bound.x = cur->bound.x+cur->bound_wide/2;
        cur->Quadrant[2]->bound.y = cur->bound.y;
        cur->Quadrant[1]->bound.y = cur->bound.y+cur->bound_height/2;
        cur->Quadrant[1]->bound.x = cur->bound.x;
        cur->Quadrant[0]->bound.x = cur->bound.x;
        cur->Quadrant[0]->bound.y = cur->bound.y;
    }
    
    int n = (int)cur->balls.size();
    int pos = n-1;
    for (int i = 0; i < n; ++i) {
        
        int index = get_index(cur->balls[pos],cur);
        if( index != -1){   //判断ball的象限，并塞入该象限中
            insert_obj(cur->balls[pos], cur, index);
            cur->balls.pop_back();
        }
        pos--;
    }
}
void QuadTree::test_full(QuadTreeNode* &cur)
{
    if (cur->depth<max_depth&&cur->balls.size()>max_size)
        divide(cur);
}
void QuadTree::pre_order(QuadTreeNode* &cur, fp v)
{
    if (cur == nullptr) return;
    v(cur);
    for (int i = 0; i<4; ++i) {
        pre_order(cur->Quadrant[i],v);
    }
}
void QuadTree::insert_by_index(ball *b)
{
    QuadTreeNode* cur = root;
    while (cur->Quadrant[0]!=nullptr) {
        int index = get_index(b, cur);
        if (index != -1)
            cur = cur->Quadrant[index];
        else
            break;
    }
    cur->balls.push_back(b);
//    test_full(cur);//把该函数内容直接copy过来
    if (cur->depth<max_depth&&cur->balls.size()>max_size)
        divide(cur);
}
//下面这个用不上了
void QuadTree::search_obj(ball* b)
{
    QuadTreeNode* cur = root;
    while (cur->Quadrant[0]!=nullptr) {
        int index = get_index(b, cur);
        if (index != -1)
            cur = cur->Quadrant[index];
        else
            break;
    }
    for (int i = 0; i < cur->balls.size(); ++i) {
        int x =cur->balls[i]->m_ball.getPosition().x-b->m_ball.getPosition().x;
        int y =cur->balls[i]->m_ball.getPosition().y-b->m_ball.getPosition().y;
        if(x*x+y*y<=4*ball_r*ball_r /*&& cur->balls[i] != b*/){
            cout<<cur->balls[i]<<'\t'<<b;
        }
    }
}

void QuadTree::check_obj_colli(QuadTreeNode* &cur)//每个节点查里面的小球是否发生碰撞
{
    int x, y;
    for (int i = 0; i < (int)cur->balls.size()-1; ++i) {
        for (int j = i+1; j <(int)cur->balls.size()-1; ++j) {
            x = cur->balls[i]->m_ball.getPosition().x-cur->balls[j]->m_ball.getPosition().x;
            y = cur->balls[i]->m_ball.getPosition().y-cur->balls[j]->m_ball.getPosition().y;
            if(x*x+y*y<ball_r*ball_r*4){//碰撞了，但是没进行操作，还没写呢
//                cout<<cur->balls[i]<<'\t'<<cur->balls[j]<<endl;
                cur->balls[i]->reverse_dirction();
                cur->balls[j]->reverse_dirction();
//                count++;
                if (x*x+y*y<ball_r*ball_r*3) {        //对于贴太近的
                    cur->balls[i]->move_ball();
                    cur->balls[i]->move_ball();
                }
            }
        }
    }
}

void QuadTree::show_ball(sf::RenderWindow *window,QuadTreeNode *&cur)
{
    if (cur == nullptr) return;
    for (int i = 0; i<cur->balls.size(); ++i) {
        cur->balls[i]->move_ball();     //移动小球
        window->draw(cur->balls[i]->m_ball);//画出小球
    }
    for (int i = 0; i<4; ++i)
        show_ball(window,cur->Quadrant[i]);
}

void QuadTree::maintain_tr(QuadTreeNode *&cur)
{
    if (cur == nullptr) return;
    ball* temp = NULL;
    int pos = (int)cur->balls.size()-1;
    for (;pos>=0; --pos) {
//        if (is_still_in(cur, cur->balls[pos])) {
//            pos--;
//            continue;
//        }
        temp = cur->balls[pos];
        cur->balls.erase(cur->balls.begin()+pos);
        insert_by_index(temp);
    }
    for (int i = 0; i<4; ++i)
        maintain_tr(cur->Quadrant[i]);
}

void QuadTree::check_obj_gra_bound(QuadTreeNode* &cur)      //边界检查，可以去掉，让画布大于屏幕
{
    for (int i = 0; i < (int)cur->balls.size()-1; ++i) {
        if (cur->balls[i]->m_ball.getPosition().x+ball_r > boundx)
            cur->balls[i]->rev_x();
        else if(cur->balls[i]->m_ball.getPosition().x-ball_r < 0)
            cur->balls[i]->rev_x();
        
        if (cur->balls[i]->m_ball.getPosition().y+ball_r > boundy)
            cur->balls[i]->rev_y();
        else if(cur->balls[i]->m_ball.getPosition().y-ball_r < 0)
                cur->balls[i]->rev_y();
    }
}
void QuadTree::check_bound(QuadTreeNode* &cur, fp vs)
{
    if (cur == nullptr) return;
    vs(cur);
    for (int i = 0; i<4; ++i) {
        pre_order(cur->Quadrant[i],vs);
    }
}
bool QuadTree::is_still_in(QuadTreeNode* &cur, ball *b)
{
    QuadTreeNode* p = cur;
    while (p->Quadrant[0]!=nullptr) {
        int index = get_index(b, cur);
        if (index == 0)
//            p = p->Quadrant[index];
            p = NULL;
        else
            break;
    }
    if (cur == p){
//        cout<<"find it still here!"<<b->m_ball.getPosition().x<<'\t'<<b->m_ball.getPosition().y<<endl;
        return true;
    }
    else
        return false;
}
