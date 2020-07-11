#pragma once

#include "cpptoml.h"


class BoidConfig{
    public:
        std::string get_current_dir();
        BoidConfig();

        std::string FontLocation();
        std::string RootPath();
        std::string PreySprite();
        std::string PredSprite();

    private:
        std::shared_ptr<cpptoml::table> _config;

};