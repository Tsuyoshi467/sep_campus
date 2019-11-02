// 2019_10_24_tetorisu.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#define MAXHEIGHT 20
#define MAXWIDTH  10

enum Block
{
	TBlock,
	IBlock,
	OBlock,
	JBlock,
	LBlock,
	ZBlock,
	SBlock,

	BlockMax,
};
struct BlockDate
{
	//T字にブロックを設置 
	int T[MAXHEIGHT][MAXWIDTH] = {
	{ 0,1,0,0},
	{ 1,1,1,0},
	};
	//I字にブロックを設置 
	int I[MAXHEIGHT][MAXWIDTH] = {
	{ 0,1,0,0},
	{ 0,1,0,0},
	{ 0,1,0,0},
	{ 0,1,0,0},
	};
	//O字にブロックを設置 
	int O[MAXHEIGHT][MAXWIDTH] = {
	{ 1,1,0,0},
	{ 1,1,0,0},
	};
	//J字にブロックを設置 
	int J[MAXHEIGHT][MAXWIDTH] = {
	{ 0,1,0,0},
	{ 0,1,0,0},
	{ 1,1,0,0},
	};
	//L字にブロックを設置 
	int L[MAXHEIGHT][MAXWIDTH] = {
	{ 0,1,0,0},
	{ 0,1,0,0},
	{ 0,1,1,0},
	};
	//S字にブロックを設置 
	int S[MAXHEIGHT][MAXWIDTH] = {
	{ 0,1,1,0},
	{ 1,1,0,0},
	};
	//Z字にブロックを設置 
	int Z[MAXHEIGHT][MAXWIDTH] = {
	{ 1,1,0,0},
	{ 0,1,1,0},
	};
};
enum Input
{
	RightMove,
	LeftMove,
	RightRote,
	LeftRote,
};
void Start(BlockDate blocks, int Now[MAXHEIGHT][MAXWIDTH], int gousei[MAXHEIGHT][MAXWIDTH],int zangai[MAXHEIGHT][MAXWIDTH],bool& endCheck,int &select);//Start
void MoveBlock(int Now[MAXHEIGHT][MAXWIDTH],int gousei[MAXHEIGHT][MAXWIDTH],int zangai[MAXHEIGHT][MAXWIDTH], int input,bool &moveY, int& select,int rCount);//MoveBlock
void Zangai(int zamgai[MAXHEIGHT][MAXWIDTH], int gousei[MAXHEIGHT][MAXWIDTH], int Now[MAXHEIGHT][MAXWIDTH], bool &moveY);//Zangai
void Draw(int gousei[MAXHEIGHT][MAXWIDTH]);//Draw
void Reset(BlockDate blocks, int Now[MAXHEIGHT][MAXWIDTH],int gousei[MAXHEIGHT][MAXWIDTH],int zamgai[MAXHEIGHT][MAXWIDTH],bool &moveY, bool& endCheck, int& select);//Reset
int main()
{
	int Now[MAXHEIGHT][MAXWIDTH] = {0};
	BlockDate blocks;
	srand((unsigned int)time);
	//初期化
	int zangai[MAXHEIGHT][MAXWIDTH] = { 0 };//積み上がり
	int gousei[MAXHEIGHT][MAXWIDTH] = { 0 };//表示
	int select =0;//表示するブロック
	int input = 0;//入力
	int turn = 1;//経過時間	
	bool moveY = true;//下移動判定
	bool endCheck = false;//終了判定
	int rCount = 0;
	Start(blocks,Now, gousei,zangai,endCheck,select);
	Draw(gousei);
	while (endCheck == false)
	{
		switch (_getch())
		{
		case 'a':
			input = LeftMove;
			break;
		case 'd':
			input = RightMove;
			break;
		case 'e':
			input = RightRote;
			if (rCount >= 4) {
				rCount = 0;
			}
			++rCount;
			break;
		case 'q':
			input = LeftRote;
			if (rCount <= 0) {
				rCount = 4;
			}
			--rCount;
			break;
		default:
			input  = -1;
			break;
		}
		MoveBlock(Now,gousei,zangai, input,moveY,select,rCount);
		Zangai(zangai,gousei,Now,moveY);
		Reset(blocks,Now, gousei,zangai, moveY,endCheck,select);
		Draw(gousei);
		input = 0;
		++turn;
	}
}
void Start(BlockDate blocks,int Now[MAXHEIGHT][MAXWIDTH], int gousei[MAXHEIGHT][MAXWIDTH],int zangai[MAXHEIGHT][MAXWIDTH], bool& endCheck, int& select){

	select = rand() % BlockMax;
	select = JBlock;
	switch (select)
	{
		case TBlock:
			for (int i = 0; i < MAXHEIGHT; i++)
			{
				for (int j = 0; j < MAXWIDTH; j++)
				{
					Now[i][j] = blocks.T[i][j];
					if (Now[i][j] == 1 && zangai[i + 1][j] == 1) {
						endCheck = true;
					}
				}
			}
			break;
		case IBlock:
			for (int i = 0; i < MAXHEIGHT; i++)
			{
				for (int j = 0; j < MAXWIDTH; j++)
				{
					Now[i][j] = blocks.I[i][j];
					if (Now[i][j] == 1 && zangai[i + 1][j] == 1) {
						endCheck = true;
					}
				}
			}
			break;
		case OBlock:
			for (int i = 0; i < MAXHEIGHT; i++)
			{
				for (int j = 0; j < MAXWIDTH; j++)
				{
					Now[i][j] = blocks.O[i][j];
					if (Now[i][j] == 1 && zangai[i + 1][j] == 1) {
						endCheck = true;
					}
				}
			}
			break;
		case JBlock:
			for (int i = 0; i < MAXHEIGHT; i++)
			{
				for (int j = 0; j < MAXWIDTH; j++)
				{
					Now[i][j] = blocks.J[i][j];
					if (Now[i][j] == 1 && zangai[i + 1][j] == 1) {
						endCheck = true;
					}
				}
			}
			break;
		case LBlock:
			for (int i = 0; i < MAXHEIGHT; i++)
			{
				for (int j = 0; j < MAXWIDTH; j++)
				{
					Now[i][j] = blocks.L[i][j];
					if (Now[i][j] == 1 && zangai[i + 1][j] == 1) {
						endCheck = true;
					}
				}
			}
			break;
		case SBlock:
			for (int i = 0; i < MAXHEIGHT; i++)
			{
				for (int j = 0; j < MAXWIDTH; j++)
				{
					Now[i][j] = blocks.S[i][j];
					if (Now[i][j] == 1 && zangai[i + 1][j] == 1) {
						endCheck = true;
					}
				}
			}
			break;
		case ZBlock:
			for (int i = 0; i < MAXHEIGHT; i++)
			{
				for (int j = 0; j < MAXWIDTH; j++)
				{
					Now[i][j] = blocks.Z[i][j];
					if (Now[i][j] == 1 && zangai[i + 1][j] == 1) {
						endCheck = true;
					}
				}
			}
			break;
		default:
			break;
	}
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			gousei[i][j] += Now[i][j];
		}
	}
	for (int j = 0; j < MAXWIDTH; j++)
	{
		if (zangai[0][j] == 1) {
			endCheck = true;
		}
	}
}
void MoveBlock(int Now[MAXHEIGHT][MAXWIDTH], int gousei[MAXHEIGHT][MAXWIDTH],int zangai[MAXHEIGHT][MAXWIDTH], int input,bool& moveY, int& select, int rCount){

	int kakuho[MAXHEIGHT + 1][MAXWIDTH+1] = { 0 };
	bool movePlusX = true;
	bool moveMinusX = true;
	moveY = true;
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 1; j < MAXWIDTH; j++)
		{
			//右端にいるかチェック
			if (Now[i][MAXWIDTH - 1] == 1) {
				movePlusX = false;
			}
			//左端にいるかチェック
			if (Now[i][0] == 1) {
				moveMinusX = false;
			}
		}
	}
	//下入力
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			//下が床かチェック
			if (Now[MAXHEIGHT - 1][j] == 1) {
				moveY = false;
				break;
			}
			else
			{
				if (moveY == true) {
					kakuho[i + 1][j] = Now[i][j];
					Now[i][j] = kakuho[i][j];
				}
			}
		}
	}
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			kakuho[i][j] = 0;
		}
	}

	//左右入力	
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			if (movePlusX == true) {
				if (input == RightMove) {
					kakuho[i][j + 1] = Now[i][j];
					Now[i][j] = kakuho[i][j];
					Now[i][0] = 0;
				}
			}
			if (moveMinusX == true) {
				if (input == LeftMove)
				{
					kakuho[i][j] = Now[i][j];
					Now[i][j - 1] = kakuho[i][j];
				}
			}
		}
	}

	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			kakuho[i][j] = 0;
		}
	}
	//回転入力	
	bool inpuCheck = false;
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			if (input == RightRote || input == LeftRote) {
				if (Now[i][j] == 1) {
					switch (select)
					{
					case TBlock:
						//右回り

						if (input == RightRote) {
							//次のブロックの位置に移動
							if (Now[i][j + 1] == 0 && Now[i][j - 1] == 0) {
								if (Now[i + 1][j] == 1) {
									kakuho[i + 1][j - 1] = Now[i][j];
								}
								if (Now[i - 1][j] == 1) {
									kakuho[i - 1][j + 1] = Now[i][j];
								}
							}
							else if (Now[i + 1][j] == 0 && Now[i - 1][j] == 0) {

								if (Now[i][j + 1] == 1) {
									kakuho[i + 1][j + 1] = Now[i][j];
								}
								if (Now[i][j - 1] == 1) {
									kakuho[i - 1][j - 1] = Now[i][j];
								}
							}
							else
							{
								kakuho[i][j] = Now[i][j];
							}
						}
						//左回り
						if (input == LeftRote) {
							if (Now[i][j + 1] == 0 && Now[i][j - 1] == 0) {
								if (Now[i + 1][j] == 1) {
									kakuho[i + 1][j + 1] = Now[i][j];
								}
								if (Now[i - 1][j] == 1) {
									kakuho[i - 1][j - 1] = Now[i][j];
								}
							}
							else if (Now[i + 1][j] == 0 && Now[i - 1][j] == 0) {

								if (Now[i][j + 1] == 1) {
									kakuho[i - 1][j + 1] = Now[i][j];
								}
								if (Now[i][j - 1] == 1) {
									kakuho[i + 1][j - 1] = Now[i][j];
								}
							}
							else
							{
								kakuho[i][j] = Now[i][j];
							}
						}
						inpuCheck = true;
						break;
					case IBlock:

						//右回り
						if (input == RightRote) {
						/*	switch (rCount)
							{
							case 1:
							if (Now[i - 1][j] == 0) {
						
								kakuho[i + 1][j + 1] = Now[i][j];
							}
							else if(Now[i + 1][j] == 1 && Now[i - 2][j] == 1)
							{
								kakuho[i - 1][j - 1] = Now[i][j];
							}
							else if(Now[i - 3][j] == 1 && Now[i + 1][j] == 0)
							{
								kakuho[i - 2][j - 2] = Now[i][j];
							}
							case 2:
							if (Now[i - 1][j] == 0) {
						
								kakuho[i + 1][j + 1] = Now[i][j];
							}
							else if(Now[i + 1][j] == 1 && Now[i - 2][j] == 1)
							{
								kakuho[i - 1][j - 1] = Now[i][j];
							}
							else if(Now[i - 3][j] == 1 && Now[i + 1][j] == 0)
							{
								kakuho[i - 2][j - 2] = Now[i][j];
							}
							break;
							default:
								break;
							}*/
							if (Now[i - 1][j] == 0 && Now[i + 3][j] == 1) {
						
								kakuho[i + 1][j + 1] = Now[i][j];
							}
							else if(Now[i + 1][j] == 1 && Now[i - 2][j] == 1)
							{
								kakuho[i - 1][j - 1] = Now[i][j];
							}
							else if(Now[i - 3][j] == 1 && Now[i + 1][j] == 0)
							{
								kakuho[i - 2][j - 2] = Now[i][j];
							}

							else if (Now[i][j - 1] == 0 && Now[i][j + 3] == 1) {
						
								kakuho[i + 1][j + 1] = Now[i][j];
							}
							else if(Now[i][j + 1] == 1 && Now[i][j - 2] == 1)
							{
								kakuho[i - 1][j - 1] = Now[i][j];
							}
							else if(Now[i][j - 3] == 1 && Now[i][j + 1] == 0)
							{
								kakuho[i - 2][j - 2] = Now[i][j];
							}

							else
							{
								kakuho[i][j] = Now[i][j];
							}
						}
						//左回り
						if (input == LeftRote) {
							if (Now[i - 1][j] == 0 && Now[i + 3][j] == 1) {

								kakuho[i - 1][j - 1] = Now[i][j];
							}
							else if (Now[i + 1][j] == 1 && Now[i - 2][j] == 1)
							{
								kakuho[i + 1][j + 1] = Now[i][j];
							}
							else if (Now[i - 3][j] == 1 && Now[i + 1][j] == 0)
							{
								kakuho[i + 2][j + 2] = Now[i][j];
							}

							else if (Now[i][j - 1] == 0 && Now[i][j + 3] == 1) {

								kakuho[i + 1][j + 1] = Now[i][j];
							}
							else if (Now[i][j + 1] == 1 && Now[i][j - 2] == 1)
							{
								kakuho[i - 1][j - 1] = Now[i][j];
							}
							else if (Now[i][j - 3] == 1 && Now[i][j + 1] == 0)
							{
								kakuho[i - 2][j - 2] = Now[i][j];
							}

							else
							{
								kakuho[i][j] = Now[i][j];
							}
						}
						inpuCheck = true;
						break;
					case LBlock:

						//右回り
						if (input == RightRote) {
							switch (rCount)
							{
							case 1:
									if (Now[i + 1][j] == 1 && Now[i - 1][j] == 0) {

										kakuho[i + 1][j + 1] = Now[i][j];
									}
									else if (Now[i - 1][j] == 1 && Now[i][j + 1] == 1) {

										kakuho[i - 1][j - 1] = Now[i][j];
									}
									else if (Now[i][j - 1] == 1) {

										kakuho[i][j - 2] = Now[i][j];
									}
									else
									{
										kakuho[i][j] = Now[i][j];
									}
									break;
							case 2:
									if (Now[i+1][j] == 1 && Now[i][j + 1] == 1) {
								
										kakuho[i - 1][j+1] = Now[i][j];
									}
									else if (Now[i][j - 1] == 1 && Now[i][j + 1] == 0) {
								
										kakuho[i + 1][j - 1] = Now[i][j];
									}
									else if (Now[i + 1][j] == 0 && Now[i - 1][j] == 1) {
								
										kakuho[i-2][j] = Now[i][j];
									}
									else
									{
										kakuho[i][j] = Now[i][j];
									}
								break;
							case 3:
								if (Now[i][j + 1] == 1) {
									kakuho[i][j + 2] = Now[i][j];
								}
								else if (Now[i][j-1] == 1) {
									kakuho[i + 1][j + 1] = Now[i][j];
								}
								else if (Now[i+1][j] == 0&&Now[i-1][j] == 1) {
									kakuho[i - 1][j-1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 4:
								if (Now[i + 1][j] == 1) {

									kakuho[i + 2][j] = Now[i][j];
								}
								else if (Now[i][j + 1] == 1&&Now[i][j-1] == 0) {

									kakuho[i - 1][j + 1] = Now[i][j];
								}
								else if (Now[i-1][j] == 1&&Now[i][j - 1] == 1) {

									kakuho[i + 1][j - 1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							default:
								break;
							}
						}
						//左回り
						if (input == LeftRote) {
							switch (rCount)
							{
							case 3:
								if (Now[i + 1][j] == 1 && Now[i - 1][j] == 0) {

									kakuho[i + 1][j - 1] = Now[i][j];
								}
								else if (Now[i - 1][j] == 1 && Now[i][j + 1] == 1) {

									kakuho[i - 1][j + 1] = Now[i][j];
								}
								else if (Now[i][j - 1] == 1) {

									kakuho[i - 2][j] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 2:
								if (Now[i + 1][j] == 1) {

									kakuho[i][j - 2] = Now[i][j];
								}
								else if (Now[i][j + 1] == 1 && Now[i][j - 1] == 0) {

									kakuho[i + 1][j + 1] = Now[i][j];
								}
								else if (Now[i - 1][j] == 1 && Now[i][j - 1] == 1) {

									kakuho[i - 1][j - 1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 1:
								if (Now[i][j + 1] == 1) {
									kakuho[i + 2][j] = Now[i][j];
								}
								else if (Now[i][j - 1] == 1) {
									kakuho[i + 1][j - 1] = Now[i][j];
								}
								else if (Now[i + 1][j] == 0 && Now[i - 1][j] == 1) {
									kakuho[i - 1][j + 1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 0:
								if (Now[i + 1][j] == 1 && Now[i][j + 1] == 1) {

									kakuho[i + 1][j + 1] = Now[i][j];
								}
								else if (Now[i][j - 1] == 1 && Now[i][j + 1] == 0) {

									kakuho[i - 1][j - 1] = Now[i][j];
								}
								else if (Now[i + 1][j] == 0 && Now[i - 1][j] == 1) {

									kakuho[i][j + 2] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							default:
								break;
							}
						}
						inpuCheck = true;
						break;
					case JBlock:
						//右回り
						if (input == RightRote) {
							switch (rCount)
							{
							case 1:
								if (Now[i + 1][j] == 1 && Now[i - 1][j] == 0) {

									kakuho[i + 1][j + 1] = Now[i][j];
								}
								else if (Now[i - 1][j] == 1 && Now[i][j - 1] == 1) {

									kakuho[i - 1][j - 1] = Now[i][j];
								}
								else if (Now[i][j + 1] == 1) {

									kakuho[i - 2][j] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 2:
								if (Now[i + 1][j] == 1) {
									kakuho[i][j + 2] = Now[i][j];
								}
								else if (Now[i][j + 1] == 1 && Now[i - 1][j] == 1) {
						
									kakuho[i - 1][j + 1] = Now[i][j];
								}
								else if (Now[i][j+1] == 0 && Now[i ][j - 1] == 1) {
								
									kakuho[i + 1][j-1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 3:
								if (Now[i + 1][j] == 1&&Now[i][j+1] == 1) {

									kakuho[i + 1][j + 1] = Now[i][j];
								}
								else if (Now[i][j - 1] == 1) {

									kakuho[i + 2][j] = Now[i][j];
								}
								else if (Now[i - 1][j] == 1 && Now[i+1][j] == 0) {

									kakuho[i - 1][j - 1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 4:
								if (Now[i][j + 1] == 1&&Now[i][j - 1] == 0) {
									kakuho[i - 1][j + 1] = Now[i][j];
								}
								else if (Now[i + 1][j] == 1&&Now[i][j - 1] == 1) {
									kakuho[i + 1][j - 1] = Now[i][j];
								}
								else if ( Now[i - 1][j] == 1) {
									kakuho[i][j - 2] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							default:
								break;
							}
						}
						//左回り
						if (input == LeftRote) {
							switch (rCount)
							{
							case 3: 
								if (Now[i + 1][j] == 1 && Now[i - 1][j] == 0) {
									kakuho[i + 1][j - 1] = Now[i][j];
								}
								else if (Now[i][j + 1] == 1) {
									kakuho[i][j + 2] = Now[i][j];
								}
								else if (Now[i - 1][j] == 1 && Now[i][j - 1] == 1) {
									kakuho[i - 1][j + 1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 2:
								if (Now[i][j + 1] == 1&&Now[i][j - 1] == 0) {

									kakuho[i + 1][j + 1] = Now[i][j];
								}
								else if (Now[i + 1][j] == 1 && Now[i][j - 1] == 1) {

									kakuho[i - 1][j - 1] = Now[i][j];
								}
								else if (Now[i - 1][j] == 1) {

									kakuho[i - 2][j] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 1:
								if (Now[i + 1][j] == 1&&Now[i][j + 1] == 1) {
									kakuho[i + 1][j - 1] = Now[i][j];
								}
								else if (Now[i][j - 1] == 1) {
									kakuho[i][j - 2] = Now[i][j];
								}
								else if (Now[i - 1][j] == 1 && Now[i + 1][j] == 0) {
									kakuho[i-1][j + 1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							case 0:
								if (Now[i + 1][j] == 1) {

									kakuho[i + 2][j] = Now[i][j];
								}
								else if (Now[i - 1][j] == 1 && Now[i][j + 1] == 1) {

									kakuho[i + 1][j + 1] = Now[i][j];
								}
								else if (Now[i][j + 1] == 0 && Now[i][j-1] == 1) {

									kakuho[i-1][j -1] = Now[i][j];
								}
								else
								{
									kakuho[i][j] = Now[i][j];
								}
								break;
							default:
								break;
							}
						}
						inpuCheck = true;
						break;
					case ZBlock:
						//左右回り
						if (input == RightRote || input == LeftRote) {
					
							if (Now[i - 1][j] == 0 && Now[i + 1][j] == 0 && Now[i][j + 1] == 1) {
								kakuho[i + 2][j] = Now[i][j];

							}
							else if (Now[i + 1][j] == 1 && Now[i][j - 1] == 1) {

								kakuho[i + 1][j - 1] = Now[i][j];

							}
							else if (Now[i + 1][j] == 0 && Now[i - 1][j] == 0 && Now[i][j - 1] == 1) {

								kakuho[i - 1][j - 1] = Now[i][j];
							}
							else if (Now[i + 1][j] == 1 && Now[i][j + 1] == 0 && Now[i][j - 1] == 0) {

								kakuho[i + 1][j + 1] = Now[i][j];

							}
							else if (Now[i + 1][j] == 1 && Now[i][j + 1] == 1) {

								kakuho[i - 1][j + 1] = Now[i][j];
							}
							else if (Now[i - 1][j] == 1 && Now[i][j + 1] == 0 && Now[i][j - 1] == 0) {

								kakuho[i - 2][j] = Now[i][j];

							}
							else
							{
								kakuho[i][j] = Now[i][j];
							}
						}
						inpuCheck = true;
						break;
					case SBlock:
						//左右回り
						if (input == RightRote || input == LeftRote) {
						
							if (Now[i - 1][j] == 0 && Now[i + 1][j] == 0 && Now[i][j - 1] == 1) {
								kakuho[i + 2][j] = Now[i][j];

							}
							else if (Now[i + 1][j] == 1 && Now[i][j + 1] == 1) {

								kakuho[i + 1][j + 1] = Now[i][j];

							}
							else if (Now[i + 1][j] == 0 && Now[i - 1][j] == 0 && Now[i][j + 1] == 1) {

								kakuho[i - 1][j + 1] = Now[i][j];
							}
							else if (Now[i + 1][j] == 1 && Now[i][j + 1] == 0 && Now[i][j - 1] == 0) {

								kakuho[i + 1][j - 1] = Now[i][j];

							}
							else if (Now[i + 1][j] == 1 && Now[i][j - 1] == 1) {

								kakuho[i - 1][j - 1] = Now[i][j];
							}
							else if (Now[i - 1][j] == 1 && Now[i][j + 1] == 0 && Now[i][j - 1] == 0) {

								kakuho[i - 2][j] = Now[i][j];

							}
							else
							{
								kakuho[i][j] = Now[i][j];
							}
						}
						inpuCheck = true;
						break;
					default:
						break;
					}
				}
			}
			
		}
	}
	if (inpuCheck == true) {
		for (int i = 0; i < MAXHEIGHT; i++)
		{
			for (int j = 0; j < MAXWIDTH; j++)
			{
				Now[i][j] = kakuho[i][j];
			}
		}
	}
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			//下がブロックかチェック
			if (Now[i][j] == 1 && zangai[i + 1][j] == 1) {
				moveY = false;
			}
		}
	}

	if (moveY == true) {
		for (int i = 0; i < MAXHEIGHT; i++)
		{
			for (int j = 0; j < MAXWIDTH; j++)
			{
				gousei[i][j] += Now[i][j];
			}
		}
	}
	
}
void Zangai(int zangai[MAXHEIGHT][MAXWIDTH], int gousei[MAXHEIGHT][MAXWIDTH], int Now[MAXHEIGHT][MAXWIDTH] ,bool &moveY){

	//ブロックが止まったらzangaiに追加
	if (moveY == false) {
		for (int i = 0; i < MAXHEIGHT; i++)
		{
			for (int j = 0; j < MAXWIDTH; j++)
			{
				zangai[i][j] += Now[i][j];
			}
		}
	}
	int deleteCount = 0;
	int deletePoint = 0;
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		deleteCount = 0;
		for (int j = 0; j < MAXWIDTH; j++)
		{
			//横列を確認
			if (zangai[i][j] == 1) {
				++deleteCount;
			}
			if (deleteCount == MAXWIDTH) {
				deletePoint = i;
			}
			zangai[deletePoint][j] = 0;
		}
	}
	for (int i = deletePoint; i > 0; i--)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			zangai[i][j] = zangai[i-1][j];
		}
	}

	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			gousei[i][j] += zangai[i][j];
		}
	}
}
void Draw(int gousei[MAXHEIGHT][MAXWIDTH]) {

	printf("\n");
	for (int i = 0; i < MAXHEIGHT; i++)
	{
		for (int j = 0; j < MAXWIDTH; j++)
		{
			if (gousei[i][j] == 1) {
				printf("■");
			}
			else
			{
				printf("□");
			}
			gousei[i][j] = 0;
		}
		printf("\n");
	}

}

void Reset(BlockDate blocks, int Now[MAXHEIGHT][MAXWIDTH],int gousei[MAXHEIGHT][MAXWIDTH],int zangai[MAXHEIGHT][MAXWIDTH],bool &moveY, bool &endCheck, int& select) {
	if (moveY == false) {
		Start(blocks,Now, gousei,zangai,endCheck,select);
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
