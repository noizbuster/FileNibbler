#include<iostream>
#include<stdlib.h>
#include<windows.h>

int yw_rand(){
	int a,b,c;
	a = rand()&0x0fff;
	b = (rand()&0x0fff)<<12;
	c = (rand()&0x007f)<<24;
	return(a|b|c);
}

int yw_random(int max){
	return (yw_rand()%max);
}

int yw_ipow(int a,int b){
	int temp = 1;
	for(int cnt = 0 ; cnt < b; cnt++){
		temp*=a;
	}
	return temp;
}

char crashOneBit(char input, double percentage){
	char temp = 0;
	for(int cnt = 0; cnt < 8 ;cnt++){
		if(yw_random(1000000)<percentage*10000){
			temp += yw_ipow(2,cnt);
		}
	}
	return input ^ temp;
}

void ywprint(char* input){
	printf("%s",input);
}