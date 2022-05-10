#pragma once
#include "Header.h"

void SetWindowSize(SHORT width, SHORT height)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Right = width;
	WindowSize.Bottom = height;
	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

// Khởi tạo ban đầu
void CaiDat() {
	GameOver = false; // Trò chơi chưa kết thúc
	dieukhien = DUNG;
	x = width / 2;
	y = height / 2;
	baitX = rand() % width;
	baitY = rand() % height;
	score = 0;
	length = 0;
} 

// Vẽ rắn + mồi + map
void Ve() {
	system("cls"); 
	// Vẽ tường trên
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	// Vẽ rắn + mồi + tường trái phải
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0) // In tường trái
				cout << "#";
			if (i == y && j == x)
				cout << key; // Cái đầu rắn 
			else if (i == baitY && j == baitX)
				cout << "o";  // In ra mồi
			else
			{
				bool print = false;
				for (int k = 0; k < length; k++)
				{
					if (tail[k].x == j && tail[k].y == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			// In ra tường phải
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	// Vẽ tường dưới
	for (int i = 0; i < width + 2; i++)
		cout << "#";

	// Xuất điểm cao + chiều dài rắn
	cout << endl;
	cout << "Score:" << score << "       " << "Highscore: " << highscore << endl;
	cout << "CurrentLength: " << length << endl;
	cout << "Player: " << player << endl;
	
	
}

// Xử lí dữ kiện bàn phím
void Input() {
	if (_kbhit()) {
		int key = _getch();
		switch (key) {
		case 'a':
		case 'A':
		case 75:
			if (dieukhien!=PHAI)
				dieukhien = TRAI;
			break;
		case 'w':
		case 'W':
		case 72:
			if (dieukhien!=XUONG)
			dieukhien = LEN;
			break;
		case 's':
		case 'S':
		case 80:
			if(dieukhien!=LEN)
			dieukhien = XUONG;
			break;
		case 'd':
		case 'D':
		case 77:
			if(dieukhien!=TRAI)
			dieukhien = PHAI;
			break;
		case 'x':
		case 'X':
			GameOver = true;
			break;
		}
	}
}	

// Mode chạm tường 
void Mode1() {
	if (x > width || x < 0 || y > height || y < 0)
	  GameOver = true;
}

// Mode xuyên tường
void Mode2() {
	if (x >= width) x = 0;
	else if (x <= 0) x = width - 1;
	if (y >= height) y = 0;
	else if (y <= 0) y = height - 1;
}

// Menu chọn mode chơi
void PlayMode() {
	system("cls");
	cout << "================= MOI BAN CHON CHE DO CHOI =================" << endl;
	cout << "| 1. Che do choi binh thuong - ran se chet khi dung tuong. |" << endl;
	cout << "| 2. Che do choi xuyen tuong - ran co the di xuyen tuong.  |" << endl;
	cout << "============================================================" << endl;
	do
	{
		cout << "Che do choi: ";
		cin >> playmode;
	} while (playmode!=1 && playmode!=2);
	cout << "Username: ";
	cin >> player;
}

//Logic game
void Game() {
	// Xử lý chuyển động của rắn
	int x1 = tail[0].x;
	int y1 = tail[0].y;
	int x2;
	int y2;
	tail[0].x = x;
	tail[0].y = y;
	for (int i = 1; i < length; i++) {
		x2 = tail[i].x;
		y2 = tail[i].y;
		tail[i].x = x1;
		tail[i].y = y1;
		x1 = x2;
		y1 = y2;
}

	// Điều khiển 
	switch (dieukhien)
	{
	case TRAI:
		x--;
		key = '<';
		break;
	case PHAI:
		x++;
		key = '>';
		break;
	case LEN:
		y--;
		key = '^';
		break;
	case XUONG:
		y++;
		key = 'v';
		break;
	default:
		break;
	}
	// Chế độ chơi
	if (playmode == 1) 
		Mode1();
	else Mode2();
	// Khi rắn tự chạm bản thân
	for (int i = 0; i < length; i++) {
		if (x == tail[i].x && y == tail[i].y)
			GameOver = true;
	}
	// Rắn ăn mồi
	if (x == baitX && y == baitY) {
		score += 10; // Cộng điểm
		// Sinh ra mồi khác có toạ độ ngẫu nhiên
		baitX = rand() % width;
		baitY = rand() % height;
		// Tăng chiều dài
		length++;
	}
	// Điểm cao
	if (score > highscore) {
		highscore = score;
	}
}

// Hướng dẫn chơi 
void menu2() {
	cout << "-------------------------HUONG DAN CHOI-------------------------" << endl;
	cout << "| Dung cac phim A W S D de di chuyen va an moi. Khi  ran cham  |" << endl;
	cout << "| tuong hay ran cham chinh ban than minh, tro choi se ket thuc.|" << endl;
	cout << "----------------------------------------------------------------" << endl;
}
// Credit
void credit() {
	cout << "------------------- About --------------------" << endl;
	cout << "| Game made by :  Doan Tan Hai                |" << endl;
	cout << "|                 Le Thi Hien                 |" << endl;
	cout << "|                 Nguyen Thi Minh Tinh        |" << endl;
	cout << "-----------------------------------------------" << endl;
}
// Menu
void menu()
{
	GameOver = false;
	int choice;
	do
	{
		cout << "----------------MENU----------------" << endl;
		cout << "|          1. Choi moi             |" << endl;
		cout << "|          2. Huong dan choi       |" << endl;
		cout << "|          3. About                |" << endl;
		cout << "|          0. Thoat                |" << endl;
		cout << "------------------------------------" << endl;
		cout << "Choice : ";
		cin >> choice;
	} while (choice!=0 && choice !=1 && choice !=2 && choice!=3);

	// Lựa chọn
	if (choice == 1) {
		PlayMode();
		CaiDat();
		while (!GameOver) {
			Ve();
			Input();
			Game();
			Sleep(50);
		}
		menu();
	}
	if (choice == 2) {
		system("cls");
		menu2();
		Sleep(2000);
		system("cls");
		menu();
	}
	if (choice == 3) {
		system("cls");
		credit();
		Sleep(2000);
		system("cls");
		menu();
	}
	if (choice == 0)
		return;
}
