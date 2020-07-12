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
    private:
        std::shared_ptr<cpptoml::table> _config;

};