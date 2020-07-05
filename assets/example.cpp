#include "AltSpriteHolder.hpp"
#include <SFML/Graphics.hpp> ///Just in case.
#include "PolarVector.hpp"
#include <SFML/OpenGL.hpp>
#include <random>
#include "timing.h"
#include <cmath>
#include <iostream>

using namespace std;


int duda()
{

    std::random_device rd;
    std::mt19937 eng(rd());



    float Pi{3.141529};
    sf::RenderWindow window(sf::VideoMode(1280, 800, 32), "Bullet Testing", sf::Style::Fullscreen);
    unsigned MaxNum = 200;
    AltSpriteHolder ASH(MaxNum);
    sf::Event event;
    sf::Texture T;
    if (!T.loadFromFile("fly32x32.png")) ///Change the path as needed.
        return -1;
    sf::Sprite M(T);

    sf::Texture T_red;
    if (!T_red.loadFromFile("fly32x32_red.png")) ///Change the path as needed.
        return -1;
    sf::Sprite M_red(T_red);

    ASH.setTexture(T);
    std::vector<PolarVector> PolVec;

    float Radius = 400;

    float Calc = (2 * Pi) / MaxNum;
    for (unsigned i = 0; i < MaxNum; ++i)
    {
        PolVec.push_back(PolarVector(Radius, i * Calc));
        ASH.setPosition(i, PolVec[i].TurnToRectangular());
    }

    ASH.globalMove(sf::Vector2f(400.f, 400.f));
    RED.globalMove(sf::Vector2f(400.f, 400.f));
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Swarm swarm100(&boids);
        // swarm100.Update(1);
        
        // for (unsigned int i = 0;i<MaxNum;i++){
        //     auto p = boids[i].Position;
        //     cout<<p.Z<<endl;
            
        //     ASH.setScale(i,(p.Z+4000)/200,(p.Z+4000)/200);
        //     ASH.setPosition(i,p.X,p.Y);
        // }
        
        
        for (unsigned int i = 0;i<MaxNum;i++){
            if (i%2==0){
                ASH.move(i,1.f,1.f);
                ASH.rotateAroundSelf(i,1.f);
            }else{
                
                ASH.move(i,-1.f,-1.f);
                ASH.rotateAroundSelf(i,-1.f);
            }
            
        }
        //ASH.globalRotateAroundSelf(1.f);

        window.draw(ASH);
        window.display();

        while (window.pollEvent(event))
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
    return 0;
}
