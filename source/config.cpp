#include "config.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#define GetCurrentDir getcwd

#include "cpptoml.hpp"
#include <filesystem>
using namespace std;

std::string BoidConfig::get_current_dir()
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	string current_working_dir(buff);
	return current_working_dir;
}

BoidConfig::BoidConfig()
{

	string curlocation = std::filesystem::current_path().string();

	vector<string> locpos{curlocation, curlocation + "/.."};

	string cfgfile = "/boids.toml";

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
		const char *vogon_poem = R"TOMLCONFIG([boids]
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
			)TOMLCONFIG";

		ofs << vogon_poem << endl << "rootpath = \"" << get_current_dir() << "/..\"";

		ofs.close();
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

string BoidConfig::FontLocation()
{
	auto val1 = RootPath();
	auto val2 = *(_config->get_qualified_as<std::string>("boids.uistatfont"));
	return val1 + "/" + val2;
}

string BoidConfig::RootPath()
{
	auto val1 = *(_config->get_qualified_as<std::string>("boids.rootpath"));
	return val1;
}

string BoidConfig::PreySprite()
{
	auto val1 = RootPath();
	auto val2 = *(_config->get_qualified_as<std::string>("boids.preysprite"));
	return val1 + "/" + val2;
}
string BoidConfig::PredSprite()
{
	auto val1 = RootPath();
	auto val2 = *(_config->get_qualified_as<std::string>("boids.predsprite"));
	return val1 + "/" + val2;
}

bool BoidConfig::Multithreaded()
{
	bool result = *(_config->get_qualified_as<bool>("boids.multithreaded"));
	return result;
}

int BoidConfig::AmountPrey()
{
	int result = *(_config->get_qualified_as<int>("boids.amountprey"));
	return result;
}

float BoidConfig::BP(std::string param)
{	
	const std::string key = "boids."+param;
	float result = *(_config->get_qualified_as<double>(key));
	return result;
}