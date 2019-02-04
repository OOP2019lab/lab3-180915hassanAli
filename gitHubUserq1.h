#pragma once

#include <string>

using namespace std;

struct gitHubUser {
	string firstName;
	string userName;
	string password;
	string email;
	int folderCount;
	string * gitHubFolders;
	string * institute_name;
	string * qualification_level;
};
