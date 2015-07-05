#pragma once
#include<fstream>
using namespace std;

class Nibbler{
private:
	char origin[200];	//원본파일
	char string[200];	//버퍼
	char dir[150];		//경로
	char fname[100];	//파일이름
	char title[100];	//파일제목
	char ext[100];		//확장자
	char *pos;			//파일포인터

	ifstream ifs;
	ofstream ofs;
	streambuf *sb;

public:
	//constructor
	Nibbler();
	Nibbler(char* filename);

	//functions
	void loadFile(char* filename);
	void closeAll();

	void nibbleHeader(int byteSizeOfHeader,double percentage);
	void nibbleBody(int byteSizeOfHeader,double percentage);
	void nibbleBlock(int byteSizeOfBlock);
	void nibbleRandom(double percentageForNibble);
};
