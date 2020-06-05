#pragma once

typedef struct ST_SERIAL_DP_PROTOCOL_3
{
	char start;
	char id;
	char comm;
	char startAdd[2];
	// 2Byte
	// 1x : ��� ��Ƽ		dUt
	// 2x : ��� �ð�		t-P
	// 3x : ������ �ð�	t-d
	// Ax : �Է� ����		Inv
	// Bx : �ð� ����		Unt
	// 81 : TRG���� 0	OUTPUT
	// 82 : TRG���� 1	OUTPUT
	// FF : ��ż��� ����
	char data[3];
	char end[2];
}DPPROTOCOL3;

typedef struct ST_SERIAL_DP_PROTOCOL_1
{
	char start;
	char id;
	char comm;
	char startAdd[2];
	// 2Byte
	// 1x : ��� ��Ƽ		dUt
	// 2x : ��� �ð�		t-P
	// 3x : ������ �ð�	t-d
	// Ax : �Է� ����		Inv
	// Bx : �ð� ����		Unt
	// 81 : TRG���� 0	OUTPUT
	// 82 : TRG���� 1	OUTPUT
	// 
	char data[1];
	char end[2];
}DPPROTOCOL1;