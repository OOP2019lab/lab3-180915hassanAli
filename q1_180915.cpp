#include <iostream>
#include <string>
#include <fstream>

#include "gitHubUserq1.h"

using namespace std;

//reads all the folders of passed user from file
void ReadgitHubFoldersFromFile(gitHubUser * &Users, int UserCount, ifstream& File) {
	//temp variable to read from file
	string LOT;

	Users[UserCount].gitHubFolders = new string[Users[UserCount].folderCount];

	for (int fCount = 0; fCount < Users[UserCount].folderCount; ++fCount) {

		getline(File, LOT);
		Users[UserCount].gitHubFolders[fCount] = LOT;
	}
}

//reads all the data of a user from passed File
void ReadUserFromFile(gitHubUser * &Users, int UserCount,ifstream& File) {
	//temp variable to read from file
	string LOT;

	getline(File, LOT);
	Users[UserCount].firstName = LOT;

	getline(File, LOT);
	Users[UserCount].userName = LOT;

	getline(File, LOT);
	Users[UserCount].email = LOT;

	getline(File, LOT);
	Users[UserCount].folderCount = stoi(LOT);

	ReadgitHubFoldersFromFile(Users,UserCount, File);

	Users[UserCount].institute_name=nullptr;
	Users[UserCount].qualification_level=nullptr;
}

//reads User data from file
//returns number of users read
int readDataFromFile(gitHubUser * &Users, string filepath) {
	//read user data from
	ifstream File(filepath);

	//temp variable to read from file
	string LOT;

	getline(File, LOT);
	//number of users in file
	int NumOfUsers = stoi(LOT);

	Users = new gitHubUser[NumOfUsers];

	for (int UserCount = 0; UserCount < NumOfUsers; ++UserCount) {

		ReadUserFromFile(Users, UserCount, File);
	}

	File.close();

	return NumOfUsers;
}

//sets background information for the passed user
void setEduBckGrnd(gitHubUser &user){
	//assign memory
	user.institute_name=new string();
	user.qualification_level=new string();

	//set values
	cout<<user.firstName<<" enter your institution name: ";
	cin>>*user.institute_name;

	cout<<user.firstName<<" enter your qualification level: ";
	cin>>*user.qualification_level;
}

//print passed user
void print(gitHubUser &user){
	cout<<endl;
	cout<<"Name: "<<user.firstName;

	cout<<endl;
	cout<<"Username: "<<user.userName;

	cout<<endl;
	cout<<"Email: "<<user.email;

	cout<<endl;
	cout<<"Password: "<<user.password;

	cout<<endl;
	cout<<"Folder Count: "<<user.folderCount;
	cout<<endl;

	cout<<"User has "<<user.folderCount<<" folders."<<endl;
	for (int c=0;c<user.folderCount;++c){
		cout<<user.gitHubFolders[c];
		cout<<endl;
	}

	if (user.institute_name!=nullptr){
		cout<<"institution name: "<<*user.institute_name;
	}
	cout<<endl;

	if (user.qualification_level!=nullptr){
		cout<<"qualification level: "<<*user.qualification_level;
	}
}

//remove background info of passed user
void remove(gitHubUser &user){
	delete user.institute_name;
	delete user.qualification_level;

	user.institute_name=nullptr;
	user.qualification_level=nullptr;
}

void backup(gitHubUser * originalArry, gitHubUser * backupArry, int userCount){
	//assign memory
	backupArry=new gitHubUser[userCount];

	//loop runs through users and copies each user
	for (int c=0;c<userCount;++c){

		backupArry[c]=originalArry[c];

		//copies folders
		backupArry[c].gitHubFolders=new string[originalArry[c].folderCount];

		for (int folder=0;folder<originalArry[c].folderCount;++folder){
			backupArry[c].gitHubFolders[folder]=originalArry[c].gitHubFolders[folder];
		}

		//copies institution data
		backupArry[c].institute_name=new string();
		backupArry[c].institute_name=originalArry[c].institute_name;

		//copies qualification data
		backupArry[c].qualification_level=new string();
		backupArry[c].qualification_level=originalArry[c].qualification_level;

	}
}

//sets background info for inputed user
void SetBackGrndMenu(gitHubUser * &user,int userCount){
	cout<<endl<<"Enter the user for which to add information";
	int userNum;
	cin>>userNum;

	//validation
	while (!(userNum>=0 && userNum<userCount)){
		cout<<"Enter a valid user number ";
		cin>>userNum;
	}

	setEduBckGrnd(user[userNum]);
}

//remove background info for inputed user
void RemoveBackGrndMenu(gitHubUser * &user,int userCount){
	cout<<endl<<"Enter the user for which to remove information";
	int userNum;
	cin>>userNum;

	//validation
	while (!(userNum>=0 && userNum<userCount)){
		cout<<"Enter a valid user number ";
		cin>>userNum;
	}

	remove(user[userNum]);
}

//prints menu options and inputs choice
int getMenuOption(){
	cout<<"Menu :D"<<endl<<endl;
	cout<<"1: Set background information for users "<<endl;
	cout<<"2: Remove background information for users "<<endl;
	cout<<"3: Backup user data "<<endl;
	cout<<"4: print user "<<endl;
	cout<<"-1 to exit"<<endl;

	int choice;
	cin>>choice;
	while (!(choice>=1 && choice<=4 || choice==-1)){
		cout<<"enter a valid option ";
		cin>>choice;
	}

	return choice;
}

//asks which users to print
void printMenu(gitHubUser * user,int userCount){
	cout<<"which user to print\n enter -1 to print all users";
	int userNum;
	cin>>userNum;

	if (userNum==-1){
		//all users
		for (int c=0;c<userCount;++c){
			print(user[c]);
		}
	}
	else{
		//validation
		while (!(userNum>=0 && userNum<userCount)){
			cout<<"Enter a valid user number ";
			cin>>userNum;
		}
		print(user[userNum]);
	}
}

//interface of the program. calls relevant functions
bool Menu(gitHubUser * &user,gitHubUser * &userBackUp,int userCount){
	int choice=getMenuOption();

	switch (choice)
	{
	case 1: SetBackGrndMenu(user,userCount);break;

	case 2: RemoveBackGrndMenu(user,userCount); break;

	case 3: backup(user,userBackUp,userCount); break;

	case 4: printMenu(user,userCount);

	case -1: return 1;

	default:
		break;
	}

	return 0;
}

void main() {
	//array of type gitHubUser
	gitHubUser * arr=nullptr;
	gitHubUser * backup=nullptr;

	int userCount=readDataFromFile(arr, "input.txt");

	while (Menu(arr,backup,userCount)==0);

	//deallocation
	delete [] arr;
	if (backup!=nullptr) delete [] backup;
	arr=nullptr;
	backup=nullptr;

	int dum;
	cin >> dum;
}