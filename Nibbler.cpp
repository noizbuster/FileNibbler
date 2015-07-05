#include"Nibbler.h"
#include"yww.h"
#include<iostream>

//==================================================
// constructor
//==================================================
Nibbler::Nibbler(char* filename){
	strcpy(origin,filename);

	strcpy(string , filename);
	pos = strrchr( string , '\\' );
	*pos = '\0';
	strcpy(dir,string);
	printf("���� ���: %s \n", dir );

	strcpy( string , filename);
	pos = strrchr( string, '\\' );
	strcpy( fname, pos+1);
	printf("���� �̸�: %s \n", fname);

	strcpy( title, fname);
	pos = strchr( title, '.' );
	*pos = '\0';
	printf("���� ���� : %s \n", title );

	pos = strchr( fname, '.' );
	strcpy( ext, pos+1);
	printf("���� Ȯ���� : %s \n", ext );
}


//==================================================
// Getters, Setters
//==================================================


//==================================================
// Class Status Handling Functions
//==================================================

//�����ִ� ������ �ٸ������� ��ü�ϴ� �޼���
void Nibbler::loadFile(char* filename){
	ifs.close();
	ifs.open(filename,ios_base::binary|ios_base::in);
	strcpy(origin,filename);

	strcpy(string , filename);
	pos = strrchr( string , '\\' );
	*pos = '\0';
	strcpy(dir,string);
	printf("���� ���: %s \n", dir );

	strcpy( string , filename);
	pos = strrchr( string, '\\' );
	strcpy( fname, pos+1);
	printf("���� �̸�: %s \n", fname);

	strcpy( title, fname);
	pos = strchr( title, '.' );
	*pos = '\0';
	printf("���� ���� : %s \n", title );

	pos = strchr( fname, '.' );
	strcpy( ext, pos+1);
	printf("���� Ȯ���� : %s \n", ext );
}

//�����ִ� ��� ���� ����� ��Ʈ���� �ݴ� �޼���
void Nibbler::closeAll(){
	ifs.close();
	ofs.close();
}



//==================================================
// Nibbling functions
//==================================================

//��� �κ��� �ջ��Ű�� �޼���
//mp4 ��������� ũ��� 8byte ��� �Ѵ�.
void Nibbler::nibbleHeader(int byteSizeOfHeader,double percentage){
	const int BUFFER_SIZE = 10000;
	char buffer[BUFFER_SIZE];
	int loopcnt = 0;

	cout << "Nibble header is call" << endl;

	//build output file address
	strcpy(string,dir);
	strcat(string,"\\");
	strcat(string,title);
	strcat(string,"_nibbleHeader.");
	strcat(string,ext);
		
	//io file stream setting
	ifs.close();
	ifs.open(origin, ios_base::in | ios_base::binary);
	ofs.open(string, ios_base::out | ios_base::trunc | ios_base::binary);

	//file open fail handling
	if(ifs == NULL){
		cerr << "THERE ARE NO OPENED FILE"<<endl;
		return;
	}

	//copy 
	//���� ũ�⸸ŭ�� ������ ���鼭 ������ ������
	while (!ifs.eof() ) {
		ifs.read( buffer, BUFFER_SIZE);

		//�ջ��Ű�� ����
		for(int cnt = 0; cnt < BUFFER_SIZE;cnt++){
			//��������� ��������
			if((loopcnt*BUFFER_SIZE) + cnt < byteSizeOfHeader){
				//�ۼ������� Ȯ����ŭ ��Ʈ�ջ�
				buffer[cnt] = crashOneBit(buffer[cnt],percentage);
			}
		}

		//���ܻ�Ȳ �ڵ鸲
		if (ifs.bad()) {
			cout << "Error reading data" << endl;
			exit(0);
		}
		else{
			ofs.write(buffer, ifs.gcount());
		}
		loopcnt++;
	};
	cout << "Finish Job : Header Nibbling"<<endl<<endl;
	closeAll();
}

void Nibbler::nibbleBody(int byteSizeOfHeader,double percentage){
	const int BUFFER_SIZE = 10000;
	char buffer[BUFFER_SIZE];
	int loopcnt = 0;

	cout << "Nibble body is call"<<endl;
	//build output file address
	strcpy(string,dir);
	strcat(string,"\\");
	strcat(string,title);
	strcat(string,"_nibbleBody.");
	strcat(string,ext);	
	
	//io file stream setting
	ifs.close();
	ifs.open(origin,ios_base::binary | ios_base::in);
	ofs.open(string,ios_base::out | ios_base::trunc | ios_base::binary);

	//file open fail handling
	if(ifs == NULL){
		cerr << "THERE ARE NO OPENED FILE"<<endl;
		return;
	}

	//���� ũ�⸸ŭ�� ������ ���鼭 ������ ������
	while (!ifs.eof() ) {
		ifs.read( buffer, BUFFER_SIZE);

		//��� �����ŭ �ջ��Ű�� ����
		for(int cnt = 0; cnt < BUFFER_SIZE;cnt++){
			//��������� ��������
			if(( loopcnt*BUFFER_SIZE) + cnt > byteSizeOfHeader){
				//�ۼ������� Ȯ����ŭ ��Ʈ�ջ�
				buffer[cnt] = crashOneBit(buffer[cnt],percentage);
			}
		}

		//���ܻ�Ȳ �ڵ鸲
		if (ifs.bad()) {
			cout << "Error reading data" << endl;
			exit(0);
		}
		else{
			ofs.write(buffer, ifs.gcount());
			//cout << "write : "<<ifs.gcount()<<endl;;
		}

		loopcnt++;
	};
	cout << "Finish Job : Body Nibbling"<<endl<<endl;
	closeAll();
}

//�������� : ����κ��� ������� ������� �ջ��ų�� ����
//������ ������(��) ������ �ջ��Ű�� �޼���
void Nibbler::nibbleBlock(int byteSizeOfBlock){
	//file open fail handling
	if(ifs == NULL){
		cerr << "THERE ARE NO OPENED FILE"<<endl;
		return;
	}
	//need impliment
}

//��ü ���̸� �������� �ջ��Ű�� �޼���(��� ����)
void Nibbler::nibbleRandom(double percentageForNibble){
	const int BUFFER_SIZE = 10000;
	char buffer[BUFFER_SIZE];

	cout << "Nibble random called"<<endl;
	//build output file address
	strcpy(string,dir);
	strcat(string,"\\");
	strcat(string,title);
	strcat(string,"_nibbleRandom.");
	strcat(string,ext);

	//io file stream setting
	ifs.close();
	ifs.open(origin, ios_base::in | ios_base::binary);
	ofs.open(string, ios_base::out | ios_base::trunc | ios_base::binary);

	//file open fail handling
	if (ifs == NULL){
		cerr << "THERE ARE NO OPENED FILE"<<endl;
		return;
	}

	//���� ��ü�� �����ϴ� ����
	while (!ifs.eof()){
		ifs.read( buffer, BUFFER_SIZE);

		//�ջ��Ű�� ����
		for(int cnt = 0; cnt < BUFFER_SIZE;cnt++){
				buffer[cnt] = crashOneBit(buffer[cnt],percentageForNibble);
		}

		if (ifs.bad()) {
			cout << "Error reading data" << endl;
			exit(0);
		}else {
			ofs.write(buffer, ifs.gcount());
		}
	};
	cout << "Finish Job : Random Nibbling"<<endl<<endl;
	closeAll();
}