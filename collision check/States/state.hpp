//
//  state.hpp
//  sfml draft
//
//  Created by 陈梓玮 on 2020/10/22.
//

#ifndef state_hpp
#define state_hpp
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
//#include "SFML/Audio.hpp"
//#include "SFML/Network.hpp"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <random>
//#include <map>
#define boundx 4000
#define boundy 2000
using namespace std;

class state
{
private:
    sf::RenderWindow* window;
    std::vector<sf::Texture> textures;
    
    
public:
    //constructor and destructor
    state(sf::RenderWindow* window);
    virtual ~state();
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    virtual void endState() = 0;
    
    
};

#endif /* state_hpp */
