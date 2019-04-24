// MMCAccoutSettingsSwitcher.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/stat.h>

#include "json.hpp"


using json = nlohmann::json;

#ifdef _WIN32
	#define PATH_SEPARATOR '\\'
#else
	#define PATH_SEPARATOR '/'
#endif

std::string fileName(std::string const& path) {

	char s = PATH_SEPARATOR;

	size_t pos = path.rfind(s, path.length());
	if (pos != std::string::npos)
		return path.substr(pos + 1, path.length() - pos);

	return std::string();
}


bool fileExists(std::string const& name)
{
	struct stat bf;
	return (stat(name.c_str(), &bf) == 0);
}

void usage(std::string const& name)
{
	std::cerr << "USAGE: " << name << " start|stop" << std::endl;
	std::cerr << " use start before instance start, stop after instance finished" << std::endl;
}

int main(int argc, char *argv[])
{
	std::string pName(fileName(argv[0]));

	if (argc != 2) {
		usage(pName);
		return 1;
	}
	std::string command(argv[1]);

	if (command != "start" && command != "stop") {
		usage(pName);
		return 1;
	}

	if (getenv("INST_DIR") == nullptr) {
		std::cerr << "ERROR: Environment variable INST_DIR must be set!" << std::endl;
		return 1;
	}

	std::string instDir = getenv("INST_DIR");
	std::string mcDir = instDir + "/.minecraft/";

	if (!fileExists(mcDir)) {
		mcDir = instDir + "/minecraft/";
		if (!fileExists(mcDir)) {
			std::cerr << "ERROR: neither .minecraft nor minecraft found in " << instDir << std::endl;
			return 1;
		}
	}

	std::string settingsFile = mcDir + "options.txt";
	std::string lastUsedFile = mcDir + pName + ".current";
	
	if (command == "start") {
		// to prevent chaos when running multiple instances, do not copy if lastUsedFile exists:
		// note that this is still buggy, see stop case
		if (fileExists(lastUsedFile)) {
			std::cerr << " -> Instance already running! To prevent chaos, no settings will be copied back. " << std::endl;
			std::cerr << "    Please do not start one instance twice!" << std::endl;
			std::remove(lastUsedFile.c_str());
			return 1;
		}
		std::string   accounts = instDir + "/../../accounts.json";
		std::ifstream accFile(accounts);
		json          accData;

		accFile >> accData;
		std::string accName = accData["activeAccount"];

		if (accName.empty()) {
			std::cerr << "ERROR: no active account found!" << std::endl;
			return 1;
		}
		std::string useFile = mcDir + accName + "_options.txt";

		// according to https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c, stat is the fastest
		if (fileExists(useFile)) {
			std::ifstream in(useFile, std::ios::binary);
			std::ofstream dest(settingsFile, std::ios::binary);

			dest << in.rdbuf();
			std::cout << " -> settings file for account " << accName << " restored." << std::endl;

		}
		else {
			std::cout << " -> no stored settings file found." << std::endl;
		}
		std::ofstream luf(lastUsedFile);

		luf << accName;
		if (luf.good()) {
			std::cout << "Written last user to " << lastUsedFile << std::endl;
		}
		else {
			std::cerr << "ERROR writing last user to " << lastUsedFile << std::endl;
			return 1;
		}
	}
	else {
		if (fileExists(lastUsedFile)) {
			std::ifstream f(lastUsedFile);
			std::stringstream ss;
			ss << f.rdbuf();
			f.close(); // else remove won't work
			std::ofstream dstFile(mcDir + ss.str() + "_options.txt");
			std::ifstream in(settingsFile);

			dstFile << in.rdbuf();
			std::cout << "Settings saved for account " << ss.str() << std::endl;

			std::remove(lastUsedFile.c_str());
		}
		else {
			std::cerr << "No info about current user found. Did you call start before starting the instance?" << std::endl;
			return 1;
		}
	}

	return 0;
}

