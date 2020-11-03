//
//  QuadTree.hpp
//  四叉树
//
//  Created by 陈梓玮 on 2020/10/23.
//

#ifndef QuadTree_hpp
#define QuadTree_hpp

#include <iostream>
#include <vector>
#include "ball.hpp"
//#include "state.hpp"
using namespace std;
struct QuadTreeNode
{
    //variable
    vector<ball*>balls;
    
    short int depth = 0;
    
    //subtree node
    QuadTreeNode* Quadrant[4];//一个指向4个子树的数组指针
    int bound_wide = boundx;
    int bound_height = boundy;
//    bool tag = false;//是否已经divide
    sf::Vector2<int>bound = {0,0};    //左上边界，其他边界可由wide和height推出
    //constrctor&destructor
    QuadTreeNode(){
        for(int i = 0; i < 4; ++i)
            Quadrant[i] = nullptr;
    }

    
//    ~QuadTreeNode()
//    {
//    }

};
class QuadTree
{
private:
    
    short int max_size = 60;//单个节点的最大存储个数
    short int max_depth = 10;

    
public:
//    static long int count;
    QuadTreeNode* root = NULL;//暂时放到public用于测试
    QuadTree();
    ~QuadTree();
    void del_tree(QuadTreeNode* &cur){
        if (cur->Quadrant[0] == nullptr)    return;
        for (int i = 0; i < 4; ++i) {
            del_tree(cur->Quadrant[i]);
            delete cur->Quadrant[i];
            cur->Quadrant[i] = nullptr;
        }
    };
    
    using fp = void (*)(QuadTreeNode* &);
    
    int get_index(ball* b,QuadTreeNode* &cur);
    void insert_obj(ball *b,QuadTreeNode* &cur,int index);  //按index插入小球
    void divide(QuadTreeNode* &cur);        //分裂
    void test_full(QuadTreeNode* &cur); //判断是否达到分裂条件
//    void insert(ball* b){root->balls.push_back(b);}
    void pre_order(QuadTreeNode* &cur, fp v);
    static void del_ball(QuadTreeNode* &cur){
        int n = (int)cur->balls.size();
        for(int i = 0; i < n; ++i){
            if(cur->balls[i]!=nullptr)
                delete cur->balls[i];
            cur->balls[i] = nullptr;
        }
    }

    static void check_obj_colli(QuadTreeNode* &cur);    //检查碰撞
//    void post_order(QuadTreeNode* &cur, fp vs); //后序遍历
    void insert_by_index(ball* b);  //插入小球到对应象限
    void search_obj(ball* b);       //查找小球是否与该象限的碰撞
    inline void check_colli(){/*count = 0; */   pre_order(root, check_obj_colli);}
    void show_ball(sf::RenderWindow* window,QuadTreeNode* &cur);
    void maintain_tr(QuadTreeNode* &cur);
    void check_bound(QuadTreeNode* &cur, fp vs);//边界碰撞，传入参数为边界检测函数
    static void check_obj_gra_bound(QuadTreeNode* &cur);//边界检测函数
    bool is_still_in(QuadTreeNode* &cur, ball* b);  //判断该小球移动后是否仍然在该节点中

};


#endif /* QuadTree_hpp */
