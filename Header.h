#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

char player[255];  // Tên người chơi 
bool GameOver; // Biến kiểm tra trò chơi đã kết thúc chưa
const int height = 23;
const int width = 23;

int highscore = 0; // Lưu điểm cao

int x, y; // Toạ độ đầu rắn
int  score = 0;
int baitX, baitY;

enum DieuKhien {
	DUNG = 0,
	LEN, XUONG, TRAI, PHAI
};

struct TAIL {  
	int x;
	int y;
};

TAIL tail[100];
int length=0;

DieuKhien dieukhien;

char key = '>'; 

int playmode;