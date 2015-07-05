#pragma once
#include<fstream>
using namespace std;

class Nibbler{
private:
	char origin[200];	//��������
	char string[200];	//����
	char dir[150];		//���
	char fname[100];	//�����̸�
	char title[100];	//��������
	char ext[100];		//Ȯ����
	char *pos;			//����������

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
