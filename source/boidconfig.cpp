/**
 * @file config.cpp
 * @author Susanna Hepp (https://github.com/SusannaMaria)
 * @brief TOML based configuration of Boids using https://github.com/skystrife/cpptoml
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "boidconfig.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "cpptoml.hpp"
#include <filesystem>
using namespace std;

/**
 * @brief Construct a new BoidConfig Object
 * Please note! If a existing configuration can not be parsed it will be overidden by a default
 * 
 */
BoidConfig::BoidConfig()
{
	// Get location in which the application is executed, c++17 feature
	string curlocation = std::filesystem::current_path().string();

	// Standard  locations 
	// 1. same location as executable(current directory)
	// 2. parent directory of current directory
	const static vector<string> locpos{curlocation, curlocation + "/.."};
	// Name of Configurationfile
	const static string cfgfile = "/boids.toml";

	for (auto loc : locpos)
	{
		try
		{
			cout << loc << endl;
			_config = cpptoml::parse_file(loc + cfgfile);
		}
		catch (const cpptoml::parse_exception &e)
		{
			continue;
		}
	}

	if (_config.get() == nullptr)
	{
		auto path = curlocation + cfgfile;

		std::cerr << "Failed to parse config, create: " << path << std::endl;

		ofstream ofs(path);

		if (!ofs)
		{
			cout << "Error writing default config file" << endl;
			exit(1);
		}
		// autogeneration of absolute rootpath
		ofs << toml_config << endl
			<< "rootpath = \"" << curlocation << "/..\"";
		ofs.close();

		// After generation try to load the newly generated configfile
		try
		{
			_config = cpptoml::parse_file(path);
		}
		catch (const cpptoml::parse_exception &e)
		{
			std::cerr << "Failed to parse " << path << std::endl;
			exit(1);
		}
	}
}
/**
 * @brief Provide path to font usind for ui
 * 
 * @return string 
 */
string BoidConfig::FontLocation() const
{
	auto val1 = RootPath();
	auto val2 = *(_config->get_qualified_as<std::string>("boids.uistatfont"));
	return val1 + "/" + val2;
}

/**
 * @brief Provide root path of application
 * 
 * @return string 
 */
string BoidConfig::RootPath() const
{
	auto val1 = *(_config->get_qualified_as<std::string>("boids.rootpath"));
	return val1;
}

/**
 * @brief Provide path to sprite image of prey boids
 * 
 * @return string 
 */
string BoidConfig::PreySprite() const
{
	auto val1 = RootPath();
	auto val2 = *(_config->get_qualified_as<std::string>("boids.preysprite"));
	return val1 + "/" + val2;
}
/**
 * @brief Provide path to sprite image of predator boids
 * 
 * @return string 
 */
string BoidConfig::PredSprite() const
{
	auto val1 = RootPath();
	auto val2 = *(_config->get_qualified_as<std::string>("boids.predsprite"));
	return val1 + "/" + val2;
}

/**
 * @brief Execution of flocking multithreaded
 * 
 * @return true Multithreaded
 * @return false Singlethreaded
 */
bool BoidConfig::Multithreaded() const
{
	bool result = *(_config->get_qualified_as<bool>("boids.multithreaded"));
	return result;
}
/**
 * @brief Amount of starting Preys (can be increased during run with <space> key)
 * 
 * @return int 
 */
int BoidConfig::AmountPrey() const
{
	int result = *(_config->get_qualified_as<int>("boids.amountprey"));
	return result;
}
/**
 * @brief Provide specific Boid Parameter
 * 
 * @param param 
 * @return float 
 */
float BoidConfig::BP(std::string param) const
{
	const std::string key = "boids." + param;
	float result = *(_config->get_qualified_as<double>(key));
	return result;
}

/**
 * @brief Amount of Obstacles
 * 
 * @return int 
 */
int BoidConfig::AmountObstacles() const
{
	int result = *(_config->get_qualified_as<int>("boids.amountobstacles"));
	return result;
}

int BoidConfig::GridX() const
{
	int result = *(_config->get_qualified_as<int>("boids.gridx"));
	return result;
}

int BoidConfig::GridY() const
{
	int result = *(_config->get_qualified_as<int>("boids.gridy"));
	return result;
}