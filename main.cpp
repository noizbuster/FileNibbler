#include<iostream>
#include"Nibbler.h"
#include<time.h>

#define DEMOFILE "C:\\data\\testvid.mp4"
void main()
{
	srand(time(NULL));
	//���ϰ�θ� �Ķ���ͷ� Ŭ���� ���� 
	Nibbler testfile = Nibbler(DEMOFILE);


	//������ �ջ��Ű�� �Լ�
	//1. nibbleRandom
	//	��ü �������� �������� ������ �ջ��Ŵ
	//	�Ķ����1 : �ջ��ų �ۼ������� (�Ҽ��� 4�ڸ����� �Է°���)

	//2. nibbleGeader
	//	��� �������� ������ Ȯ����ŭ ������ �ջ��Ŵ
	//	�Ķ����1 : ���ũ��(����Ʈ)
	//	�Ķ����2 : �ջ��ų �ۼ������� (�Ҽ��� 4�ڸ����� �Է°���)
	
	//3. nibbleBody
	//	����� ������ �������� ������ Ȯ����ŭ ������ �ջ��Ŵ
	//	�Ķ����1 : ���ũ��(����Ʈ)
	//	�Ķ����2 : �ջ��ų �ۼ������� (�Ҽ��� 4�ڸ����� �Է°���)

	testfile.nibbleRandom	(0.0001);
	//����� 7%�̻� �ջ� ��Ű�� ����� �Ұ���������.
	testfile.nibbleHeader	(8	,2);
	testfile.nibbleBody		(8	,0.01);


}