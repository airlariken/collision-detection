//
//  GameState.hpp
//  sfml draft
//
//  Created by 陈梓玮 on 2020/10/23.
//

#ifndef GameState_hpp
#define GameState_hpp

#include "state.hpp"
#include "ball.hpp"
class GameState :public state
{
private:


public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();
    
    //functions
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target = nullptr);
    virtual void endState();
        
    
};


#endif /* GameState_hpp */
