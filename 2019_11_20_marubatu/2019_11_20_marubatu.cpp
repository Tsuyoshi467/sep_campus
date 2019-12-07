// 2019_11_20_marubatu.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
using namespace std;
#define MAPSIZE 3

enum Status
{
	Blank,  //空白
	Circle, //●
	Cross,  //×
};

void Start(int map[MAPSIZE][MAPSIZE],int &turn);    //初期化
void Input(int map[MAPSIZE][MAPSIZE], int& turn);   //マップ更新
void EndCheck(int map[MAPSIZE][MAPSIZE], int& turn);//終了判定
void Draw(int map[MAPSIZE][MAPSIZE]);               //表示

int main()
{
	int map[MAPSIZE][MAPSIZE];//マップ
	int turn = Circle;                //ターン 

	Start(map,turn);
	while (true)
	{
		Draw(map);
		Input(map, turn);
	}
}
void Start(int map[MAPSIZE][MAPSIZE], int& turn) 
{
	turn = Circle; //〇のターンにする

	//全て空白に初期化
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			map[i][j] = Blank;
		}
	}
}

void Input(int map[MAPSIZE][MAPSIZE], int& turn)
{
	char x = '0';//横入力用
	char y = '0';//縦入力用

	//ターン表示
	if (turn == Circle) {
		printf("●のターン");
	}
	else 
	{
		printf("×のターン");
	}

	//入力
	printf("\n");
	printf("列を選んでください A:左 B:中 C:右 >");
	cin >> x;
	printf("行を選んでください 1:上 2:中 3:下 >");
	cin >> y;
	printf("\n");
	switch (x)
	{
	case 'A':
		x = 0;
			break;
	case 'B':
		x = 1;
			break;
	case 'C':
		x = 2;
			break;
	default:
		break;
	}
	switch (y)
	{
	case '1':
		y = 0;
			break;
	case '2':
		y = 1;
			break;
	case '3':
		y = 2;
			break;
	default:
		break;
	}

	//マップ更新
	map[y][x] = turn;

	//ターン変更
	if (turn == Circle) {
		turn = Cross;
	}
	else if (turn == Cross) {
		turn = Circle;
	}
	//終了判定
	EndCheck(map, turn);
}

void EndCheck(int map[MAPSIZE][MAPSIZE], int& turn) {
	int  circleEndCounter = 0;//●カウント用
	int  crossEndCounter  = 0;//×カウント用
	int  drawCount = 0;       //引き分けカウント用
	const int endNumber = 3;  //何個そろうと勝利か
	int i = 0;
	int j = 0;

	//横判定
	for ( i = 0; i < MAPSIZE; i++)
	{
		circleEndCounter = 0;
		crossEndCounter  = 0;

		for ( j = 0; j < MAPSIZE; j++)
		{
			if (map[i][j] == Circle) {
				++circleEndCounter;
			}
			if (map[i][j] == Cross) {
				++crossEndCounter;
			}
		}
		if (circleEndCounter == endNumber) {
			Draw(map);
			printf("● Win\n");
			Start(map, turn);
		}
		if (crossEndCounter == endNumber) {
			Draw(map);
			printf("× Win\n");
			Start(map, turn);
		}
	}

	//縦判定
	for ( i = 0; i < MAPSIZE; i++)
	{
		circleEndCounter = 0;
		crossEndCounter  = 0;

		for ( j = 0; j < MAPSIZE; j++)
		{
			if (map[j][i] == Circle) {
				++circleEndCounter;
			}
			if (map[j][i] == Cross) {
				++crossEndCounter;
			}
		}
		if (circleEndCounter == endNumber) {
			Draw(map);
			printf("● Win\n");
			Start(map, turn);
		}
		if (crossEndCounter == endNumber) {
			Draw(map);
			printf("× Win\n");
			Start(map, turn);
		}
	}
	circleEndCounter = 0;
	crossEndCounter = 0;

	//斜め判定(左上から右下へ)
	for ( i = 0; i < MAPSIZE; i++)
	{
		if (map[i][i] == Circle) {
			++circleEndCounter;
		}
		if (map[i][i] == Cross) {
			++crossEndCounter;
		}
	}

	if (circleEndCounter == endNumber) {
		Draw(map);
		printf("● Win\n");
		Start(map, turn);
	}
	if (crossEndCounter == endNumber) {
		Draw(map);
		printf("× Win\n");
		Start(map, turn);
	}

	circleEndCounter = 0;
	crossEndCounter = 0;

	//斜め判定(右上から左下へ)
	for ( i = 0, j = MAPSIZE-1; i < MAPSIZE || j >= 0; i++,j--)
	{
		if (map[i][j] == Circle)
		{
			++circleEndCounter;
		}
		if (map[i][j] == Cross)
		{
			++crossEndCounter;
		}
	}
	
	if (circleEndCounter == endNumber) {
		Draw(map);
		printf("● Win\n");
		Start(map, turn);
	}
	if (crossEndCounter == endNumber) {
		Draw(map);
		printf("× Win\n");
		Start(map, turn);
	}
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			if (map[i][j] != Blank) {
				++drawCount;
			}
		}
	}
	if (drawCount == MAPSIZE * MAPSIZE) {
		Draw(map);
		printf("Draw\n");
		Start(map, turn);
	}
}

void Draw(int map[MAPSIZE][MAPSIZE]) {
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int k = 0; k < MAPSIZE; k++) {
			printf("┌───┐");
		}
		printf("\n");
		for (int j = 0; j < MAPSIZE; j++)
		{
			printf("│");
			if (map[i][j] == Circle)
			{
				printf(" ●");
			}
			else if (map[i][j] == Cross) 
			{
				printf(" ×");
			}
			else 
			{
				printf("　 ");
			}
			printf("│");
		}
		printf("\n");
		for (int k = 0; k < MAPSIZE; k++) {
			printf("└───┘");
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
