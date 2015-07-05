#include<iostream>
#include"Nibbler.h"
#include<time.h>

#define DEMOFILE "C:\\data\\testvid.mp4"
void main()
{
	srand(time(NULL));
	//파일경로를 파라미터로 클래스 생성 
	Nibbler testfile = Nibbler(DEMOFILE);


	//파일을 손상시키는 함수
	//1. nibbleRandom
	//	전체 구간에서 랜덤으로 파일을 손상시킴
	//	파라미터1 : 손상시킬 퍼센테이지 (소수점 4자리까지 입력가능)

	//2. nibbleGeader
	//	헤더 구간에서 지정된 확률만큼 파일을 손상시킴
	//	파라미터1 : 헤더크기(바이트)
	//	파라미터2 : 손상시킬 퍼센테이지 (소수점 4자리까지 입력가능)
	
	//3. nibbleBody
	//	헤더를 제외한 구간에서 지정된 확률만큼 파일을 손상시킴
	//	파라미터1 : 헤더크기(바이트)
	//	파라미터2 : 손상시킬 퍼센테이지 (소수점 4자리까지 입력가능)

	testfile.nibbleRandom	(0.0001);
	//헤더는 7%이상 손상 시키면 재생이 불가능해진다.
	testfile.nibbleHeader	(8	,2);
	testfile.nibbleBody		(8	,0.01);


}