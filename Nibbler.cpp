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
	printf("파일 경로: %s \n", dir );

	strcpy( string , filename);
	pos = strrchr( string, '\\' );
	strcpy( fname, pos+1);
	printf("파일 이름: %s \n", fname);

	strcpy( title, fname);
	pos = strchr( title, '.' );
	*pos = '\0';
	printf("파일 제목 : %s \n", title );

	pos = strchr( fname, '.' );
	strcpy( ext, pos+1);
	printf("파일 확장자 : %s \n", ext );
}


//==================================================
// Getters, Setters
//==================================================


//==================================================
// Class Status Handling Functions
//==================================================

//열려있는 파일을 다른것으로 교체하는 메서드
void Nibbler::loadFile(char* filename){
	ifs.close();
	ifs.open(filename,ios_base::binary|ios_base::in);
	strcpy(origin,filename);

	strcpy(string , filename);
	pos = strrchr( string , '\\' );
	*pos = '\0';
	strcpy(dir,string);
	printf("파일 경로: %s \n", dir );

	strcpy( string , filename);
	pos = strrchr( string, '\\' );
	strcpy( fname, pos+1);
	printf("파일 이름: %s \n", fname);

	strcpy( title, fname);
	pos = strchr( title, '.' );
	*pos = '\0';
	printf("파일 제목 : %s \n", title );

	pos = strchr( fname, '.' );
	strcpy( ext, pos+1);
	printf("파일 확장자 : %s \n", ext );
}

//열려있는 모든 파일 입출력 스트림을 닫는 메서드
void Nibbler::closeAll(){
	ifs.close();
	ofs.close();
}



//==================================================
// Nibbling functions
//==================================================

//헤더 부분을 손상시키는 메서드
//mp4 파일헤더의 크기는 8byte 라고 한다.
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
	//버퍼 크기만큼씩 루프를 돌면서 파일을 복사함
	while (!ifs.eof() ) {
		ifs.read( buffer, BUFFER_SIZE);

		//손상시키는 루프
		for(int cnt = 0; cnt < BUFFER_SIZE;cnt++){
			//헤더범위에 있을때만
			if((loopcnt*BUFFER_SIZE) + cnt < byteSizeOfHeader){
				//퍼센테이지 확률만큼 비트손상
				buffer[cnt] = crashOneBit(buffer[cnt],percentage);
			}
		}

		//예외상황 핸들림
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

	//버퍼 크기만큼씩 루프를 돌면서 파일을 복사함
	while (!ifs.eof() ) {
		ifs.read( buffer, BUFFER_SIZE);

		//헤더 사이즈만큼 손상시키는 루프
		for(int cnt = 0; cnt < BUFFER_SIZE;cnt++){
			//헤더범위에 없을때만
			if(( loopcnt*BUFFER_SIZE) + cnt > byteSizeOfHeader){
				//퍼센테이지 확률만큼 비트손상
				buffer[cnt] = crashOneBit(buffer[cnt],percentage);
			}
		}

		//예외상황 핸들림
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

//구현보류 : 어느부분을 어떤식으로 블록으로 손상시킬지 미정
//뭉텅이 뭉텅이(블럭) 단위로 손상시키는 메서드
void Nibbler::nibbleBlock(int byteSizeOfBlock){
	//file open fail handling
	if(ifs == NULL){
		cerr << "THERE ARE NO OPENED FILE"<<endl;
		return;
	}
	//need impliment
}

//전체 길이를 랜덤으로 손상시키는 메서드(헤더 포함)
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

	//파일 전체를 복사하는 루프
	while (!ifs.eof()){
		ifs.read( buffer, BUFFER_SIZE);

		//손상시키는 루프
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