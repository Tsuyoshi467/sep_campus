// 2019_10_29_labyrinth.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include<time.h>
#define SIZE(array)(sizeof(array)/sizeof *(array));
#define HEIGHTMAX 30
#define WIDTHMAX 30

enum Status {
	start,
	goal,
	road,
	wall,
	outside,
};
enum Check
{
	plus = 1,
	minus = -1,
};
enum Direction
{
	up,
	down,
	right,
	left,

	directionSize,
};
enum RoadSize
{
	Normal = 1,
	Branch = 3,
};

void RoadSelect(int labyrinth[HEIGHTMAX][WIDTHMAX],int &Y,int &X,int &branch);
void Draw(int labyrinth[HEIGHTMAX][WIDTHMAX]);

int main()
{
	int labyrinth[HEIGHTMAX][WIDTHMAX];
	int Y = 0;
	int X = 0;
	int branch = 5;//最低分岐数
	
	//初期化	
	for (int i = 0; i < HEIGHTMAX; i++)
	{
		for (int j = 0; j < WIDTHMAX; j++)
		{
			if (i == 0 || i == HEIGHTMAX-1 || j == 0 || j == WIDTHMAX-1) {
				labyrinth[i][j] = outside;
			}
			else 
			{
				labyrinth[i][j] = wall;
			}
				
		}
	}	
	//ゴールを設定
	srand((unsigned int)time(NULL));

	do
	{
		X = rand() % HEIGHTMAX;
		Y = rand() % WIDTHMAX;
	} while (Y != 0 && Y != HEIGHTMAX - 1&& X != 0 && X != WIDTHMAX - 1);
	labyrinth[Y][X] = goal;
	RoadSelect(labyrinth,Y,X,branch);
	//スタートを設定
	labyrinth[Y][X] = start;
	
	bool loopCheck = true;
		while (loopCheck == true)
		{
			for (int i = 0; i < HEIGHTMAX; i++)
			{
				for (int j = 0; j < WIDTHMAX; j++)
				{
					if (labyrinth[i][j] == road && labyrinth[i + 1][j] == road && labyrinth[i - 1][j] == road && labyrinth[i][j + 1] == wall && labyrinth[i][j - 1] == wall) {
	
						RoadSelect(labyrinth, i, j, branch);
					}
					else if (labyrinth[i][j] == road && labyrinth[i + 1][j] == wall && labyrinth[i - 1][j] == wall && labyrinth[i][j + 1] == road && labyrinth[i][j - 1] == road) {
					
						RoadSelect(labyrinth, i, j, branch);
					}
						loopCheck = false;
					
				}
			}
		}
	Draw(labyrinth);
}

void RoadSelect(int labyrinth[HEIGHTMAX][WIDTHMAX], int &Y, int &X,int &branch) {

	int checkCount = 0;
	bool checkDirection[directionSize] = { true };
	int roadSize = 0;
	roadSize = Branch;
	while (true)
	{
		/*if (branch > 0) {
			roadSize = Branch;
			--branch;
		}
		else
		{
			switch (rand() % 2)
			{
			case 0:
				roadSize = Normal;
				break;
			case 1:
				roadSize = Branch;
				break;
			default:
				roadSize = Normal;
				break;
			}
		}*/
		roadSize = Branch;
		//上が壁かチェック
		if (Y >= roadSize) {
			if (labyrinth[Y + minus][X] != wall) {
				checkDirection[up] = false;
			}
			else
			{
				for (int i = 1; i < roadSize + 1; i++)
				{
					if (labyrinth[Y - i - 1][X] == road || labyrinth[Y - i][X + plus] == road || labyrinth[Y - i][X + minus] == road ||
						labyrinth[Y - i - 1][X] == outside||
						labyrinth[Y - i - 1][X] == start || labyrinth[Y - i][X + plus] == start || labyrinth[Y - i][X + minus] == start) {
						checkDirection[up] = false;
					}
					else
					{
						checkDirection[up] = true;
					}
				}
			}
		}
		else
		{
			checkDirection[up] = false;
		}
		//下が壁かチェック
			if (labyrinth[Y + plus][X] != wall) {
				checkDirection[down] = false;
			}
			else
			{
				for (int i = 1; i < roadSize + 1; i++)
				{
					if (labyrinth[Y + i + 1][X] == outside){
				
					}
					if (labyrinth[Y + i +1][X] == road || labyrinth[Y + i][X + plus] == road || labyrinth[Y + i][X + minus] == road ||
						labyrinth[Y + i + 1][X] == outside ||
						labyrinth[Y + i + 1][X] == start || labyrinth[Y + i][X + plus] == start || labyrinth[Y + i][X + minus] == start) {
						checkDirection[down] = false;
					}
					else
					{
						checkDirection[down] = true;
					}
				}
			}
		//右が壁かチェック
			if (labyrinth[Y][X + plus] != wall) {
				checkDirection[right] = false;
			}
			else
			{
				for (int i = 1; i < roadSize + 1; i++)
				{
					if (labyrinth[Y][X + i + 1] == outside) {
					
					}
					if (labyrinth[Y][X + i + 1] == road || labyrinth[Y + minus][X + i] == road || labyrinth[Y + plus][X + i] == road ||
						labyrinth[Y][X + i + 1] == outside || 
						labyrinth[Y][X + i + 1] == start || labyrinth[Y + minus][X + i] == start || labyrinth[Y + plus][X + i] == start) {
						checkDirection[right] = false;
					}
					else
					{
						checkDirection[right] = true;
					}
				}
			}
		
		//左が壁かチェック
		if (X > roadSize) {
			if (labyrinth[Y][X + minus] != wall) {

				checkDirection[left] = false;
			}
			else
			{
				for (int i = 1; i < roadSize + 1; i++)
				{
					if (labyrinth[Y][X - i - 1] == outside) {
					
					}
					if (labyrinth[Y][X - i - 1] == road || labyrinth[Y + minus][X - i] == road || labyrinth[Y + plus][X - i] == road ||
						labyrinth[Y][X - i - 1] == outside || 
						labyrinth[Y][X - i - 1] == start || labyrinth[Y + minus][X - i] == start || labyrinth[Y + plus][X - i] == start) {
						checkDirection[left] = false;
					}
					else
					{
						checkDirection[left] = true;
					}
				}
			}
		}
		else
		{
			checkDirection[left] = false;
		}
		if (checkDirection[up] == false && checkDirection[down] == false && checkDirection[right] == false && checkDirection[left] == false) {
			break;
		}
		//進む方向を選択
		do
		{
			checkCount = rand() % directionSize;
		} while (checkDirection[checkCount] == false);
	
		//選択された座標へ動かす
		switch (checkCount)
		{
		case up:
			if (roadSize == Normal) {
				labyrinth[Y - Normal][X] = road;
				Y -= Normal;
			}
			else
			{
				labyrinth[Y + minus][X] = road;
				labyrinth[Y + minus + minus][X] = road;
				labyrinth[Y + minus + minus + minus][X] = road;
				Y -= Branch;
			}
			break;
		case down:
			if (roadSize == Normal) {
				labyrinth[Y + Normal][X] = road;
				Y += Normal;
			}
			else
			{
				labyrinth[Y + plus][X] = road;
				labyrinth[Y + plus + plus][X] = road;
				labyrinth[Y + plus + plus + plus][X] = road;
				Y += Branch;
			}
			break;
		case right:
			if (roadSize == Normal) {
				labyrinth[Y][X + Normal] = road;
				X += Normal;
			}
			else
			{
				labyrinth[Y][X + plus] = road;
				labyrinth[Y][X + plus + plus] = road;
				labyrinth[Y][X + plus + plus + plus] = road;
				X += Branch;
			}
			break;
		case left:
			if (roadSize == Normal) {
				labyrinth[Y][X - Normal] = road;
				X -= Normal;
			}
			else
			{
				labyrinth[Y][X + minus] = road;
				labyrinth[Y][X + minus + minus] = road;
				labyrinth[Y][X + minus + minus + minus] = road;
				X -= Branch;
			}
			break;
		default:
			break;
		}
	}
}

void Draw(int labyrinth[HEIGHTMAX][WIDTHMAX]) {
	//描画
	printf("\n");
	for (int i = 0; i < HEIGHTMAX; i++)
	{
		for (int j = 0; j < WIDTHMAX; j++)
		{
			switch (labyrinth[i][j])
			{
			case start:
				printf(" S");
				break;
			case goal:
				printf(" G");
				break;
			case road:
				printf("  ");
				break;
			case wall:
				printf("■");
				break;
			case outside:
				printf("□");
				break;
			default:
				printf("E");
				break;
			}
		}
		printf("\n");
	}
}
// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
