/**
 * @file boidconfig.hpp
 * @author Susanna Hepp (https://github.com/SusannaMaria)
 * @brief TOML based configuration of Boids using https://github.com/skystrife/cpptoml
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include "cpptoml.hpp"


class BoidConfig{
    public:
        BoidConfig();

        std::string FontLocation() const;
        std::string RootPath() const;
        std::string PreySprite() const;
        std::string PredSprite() const;
        bool Multithreaded() const;
        int AmountPrey() const;
        float BP(std::string param) const;
        int AmountObstacles() const;
        int WindowHeight() const;
        int WindowWidth() const;
        void WindowHeight(int wh);
        void WindowWidth(int ww);
        int GridX() const;
        int GridY() const;

    private:
		const char *toml_config = R"TOMLCONFIG([boids]
version = 1.0
uistatfont = "assets/consola.ttf"
preysprite = "assets/fly16x16.png"
predsprite = "assets/fly16x16_red.png"
multithreaded = true
amountprey = 1000
desSep = 20.0
desAli = 70.0
desCoh = 25.0
sepW = 1.5
aliW = 1.0
cohW = 1.0
theta = 0.0
amountobstacles = 5
gridx = 4
gridy = 3

			)TOMLCONFIG";    
        std::shared_ptr<cpptoml::table> _config;
        int _window_height;
        int _window_width;

};