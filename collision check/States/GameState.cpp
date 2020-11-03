//
//  GameState.cpp
//  sfml draft
//
//  Created by 陈梓玮 on 2020/10/23.
//

#include "GameState.hpp"

GameState::GameState(sf::RenderWindow* window)  :state(window)
{
    
}

GameState::~GameState()
{
    
}

void GameState::update(const float& dt)
{
    cout<<"hello from gamestate!"<<endl;
}
void GameState::render(sf::RenderTarget* target)
{

}
void GameState::endState()
{
    
}
