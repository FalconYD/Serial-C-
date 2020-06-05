#pragma once

typedef struct ST_SERIAL_DP_PROTOCOL_3
{
	char start;
	char id;
	char comm;
	char startAdd[2];
	// 2Byte
	// 1x : 출력 듀티		dUt
	// 2x : 출력 시간		t-P
	// 3x : 딜레이 시간	t-d
	// Ax : 입력 설정		Inv
	// Bx : 시간 단위		Unt
	// 81 : TRG제어 0	OUTPUT
	// 82 : TRG제어 1	OUTPUT
	// FF : 통신설정 저장
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
	// 1x : 출력 듀티		dUt
	// 2x : 출력 시간		t-P
	// 3x : 딜레이 시간	t-d
	// Ax : 입력 설정		Inv
	// Bx : 시간 단위		Unt
	// 81 : TRG제어 0	OUTPUT
	// 82 : TRG제어 1	OUTPUT
	// 
	char data[1];
	char end[2];
}DPPROTOCOL1;