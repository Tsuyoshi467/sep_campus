// 2019_11_22_syougi.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include<string>
using namespace std;

#define HEIGHTMAX 9          //高さ
#define WIDTHMAX 9           //横

#define TURNMIN 0            //最低ターン
#define TURNMAX 199          //最高ターン

#define PIECENUMBER   8            //基本駒数

#define UNDOTURNMIN 2        //一手戻せるターン
#define HOLDINGOFFSET 72     //アルファベットを数字に変換
#define PLAYER1NORMALOFFSET 8//通常
#define PLAYER1NARIOFFSET 20 //成

#define PLAYER2NORMALOFFSET 0//通常
#define PLAYER2NARIOFFSET 14 //成

#define  PLAYER1NARIMIN 0    //プレイヤー1が成れる最低ライン
#define  PLAYER1NARIMAX 2    //プレイヤー1が成れる最ライン
#define  PLAYER2NARIMIN 6    //プレイヤー2が成れる最低ライン
#define  PLAYER2NARIMAX 8    //プレイヤー2が成れる最高ライン

#define YMOTIGOMA 99
#define XMOTIGOMA 99

//棋譜構造体
struct Kifu
{
	int turn;       //経過時間
	int nextY;      //移動先Y
	int nextX;      //移動先X
	int piece;      //動かした駒
	int deletePiece;//移動先の駒
	int nowY;       //移動元Y
	int nowX;       //移動元X
	int playerTurn; //先手か後手か
};

//駒情報
enum Piece
{

	//通常の駒
	王,
	金,
	銀,
	飛,
	角,
	桂,
	香,
	歩,

	王2,
	金2,
	銀2,
	飛2,
	角2,
	桂2,
	香2,
	歩2,

	//成り状態の駒
	銀成,
	飛成,
	角成,
	桂成,
	香成,
	歩成,

	銀成2,
	飛成2,
	角成2,
	桂成2,
	香成2,
	歩成2,

	空,

};

//持ち駒情報
enum PieceState
{
	Player1,//プレイヤー1
	Player2,//プレイヤー2

	PlayerCount,//プレイヤー数
};
//更新
void Input(int board[HEIGHTMAX][WIDTHMAX], Kifu* kifu);
//表示
void Draw(int board[HEIGHTMAX][WIDTHMAX], Kifu* kifu);
//一手戻す
void Undo(int board[HEIGHTMAX][WIDTHMAX], Kifu* kifu);

int counter = 0;//ターン
int playerTurn = Player1;//ターン情報

int holding[PlayerCount][8] = { 0 };//持ち駒

int main()
{
	//駒情報
	int board[HEIGHTMAX][WIDTHMAX] = { {香2,桂2,銀2,金2,王2,金2,銀2,桂2, 香2},
									   {空,飛2,空,空,空,空,空,角2,空},
									   {歩2,歩2,歩2,歩2,歩2,歩2,歩2,歩2,歩2},
									   {空,空,空,空,空,空,空,空,空},
									   {空,空,空,空,空,空,空,空,空},
									   {空,空,空,空,空,空,空,空,空},
									   {歩,歩,歩,歩,歩,歩,歩,歩,歩},
									   {空,角,空,空,空,空,空,飛,空},
									   {香,桂,銀,金,王,金,銀,桂,香}
	};

	//晩
	Kifu kifu[200] = { 0 };

	while (TURNMAX)
	{
		//system("cls");     //画面更新
		Draw(board, kifu); //表示
		Input(board, kifu);//移動
	}
}

void Input(int board[HEIGHTMAX][WIDTHMAX], Kifu* kifu) {

	int nextY = 0;        //移動位置Y
	int nextX = 0;        //移動位置X
	int nowY = 0;        //現在位置Y
	int nowX = 0;        //現在位置X
	int undo = 0;         //一手戻る判定
	int holdingNomber = 0;//持ち駒引数用
	int nariCheck = 0;    //成チェック
	int pieceSearchStartY = 0;//Y判定スタート用
	int pieceSearchStartX = 0;//X判定スタート用
	int pieceSearchGoalY = 0;//Y判定ゴール用
	int pieceSearchGoalX = 0;//X判定ゴール用

	char tempIn = 0;      //駒入力

	bool movePiece = false; //移動判定用
	bool inputCheck = false;//入力判定用
	bool nifuCheck = false;

	if (counter >= UNDOTURNMIN) {
		printf("一手戻しますか? 0:No 1:Yes>");
		cin >> undo;
		if (undo == 1) {
			Undo(board, kifu);
			system("cls");
			Draw(board, kifu);
		}
	}

	//移動可能判定
	while (inputCheck == false)
	{
		//移動元判定
		while (true)
		{
			printf("どれを動かしますか？\n");
			printf("行を選んでください 盤:1～9 持ち駒:10>");
			cin >> nowX;

			nowX--;

			if (nowX == 9)
			{
				printf("駒を選んでください A～G>");
			}
			else
			{
				printf("列を選んでください 1～9>");
			}
			cin >> tempIn;
			nowY = tempIn - '0';
			if (tempIn >= '1' && tempIn <= '9') {
				nowY--;
				//移動元に自分の駒があるか
				if ((playerTurn == Player1 && (board[nowY][nowX] >= 王 && board[nowY][nowX] <= 歩) || (board[nowY][nowX] >= 銀成 && board[nowY][nowX] <= 歩成)) ||
					(playerTurn == Player2 && (board[nowY][nowX] >= 王2 && board[nowY][nowX] <= 歩2) || (board[nowY][nowX] >= 銀成2 && board[nowY][nowX] <= 歩成2)))
				{
					break;
				}
				else
				{
					printf("選べません\n");
				}
			}
			else if (tempIn >= 'A' && tempIn <= 'G') {
				holdingNomber = HOLDINGOFFSET - tempIn;

				if (holding[playerTurn][holdingNomber] != 0) {
					break;
				}
				else
				{
					printf("駒がありません\n");
				}
			}
			printf("\n");

		}

		//移動先判定
		printf("どこに動かしますか？\n");
		printf("行を選んでください 1～9>");
		cin >> nextX;
		nextX--;
		printf("列を選んでください 1～9>");
		cin >> nextY;
		nextY--;
		printf("\n");

		//盤の駒を移動するとき
		if (tempIn >= '1' && tempIn <= '9') {

			//移動先判定用
			if (nextY == nowY) 
			{
				pieceSearchStartY = nextY;
				pieceSearchGoalY = nowY;
			}
			else if (nextY < nowY) {
				pieceSearchStartY = nextY + 1;
				pieceSearchGoalY = nowY;
			}
			else if(nextY > nowY)
			{
				pieceSearchStartY = nowY + 1;
				pieceSearchGoalY = nextY;
			}

			if (nextX == nowX) 
			{
				pieceSearchStartX = nextX;
				pieceSearchGoalX = nowX;
			}
			else if (nextX < nowX) 
			{
				pieceSearchStartX = nextX + 1;
				pieceSearchGoalX = nowX;
			}
			else if(nextX > nowX)
			{
				pieceSearchStartX = nowX + 1;
				pieceSearchGoalX = nextX;
			}


			//移動先判定
			if (board[nextY][nextX] == 空 || (playerTurn == Player1 && ((board[nextY][nextX] >= 王2 && board[nextY][nextX] <= 歩2) || (board[nextY][nextX] >= 銀成2 && board[nextY][nextX] <= 歩成2))) || (playerTurn == Player2 && ((board[nextY][nextX] >= 王 && board[nextY][nextX] <= 歩) || (board[nextY][nextX] >= 銀成 && board[nextY][nextX] <= 歩成2)))) {

				switch (board[nowY][nowX])
				{
				case 王:
				case 王2:
					if ((nextY - nowY == -1 || nextY - nowY == 1 || nextY - nowY == 0) && (nextX - nowX == -1 || nextX - nowX == 1 || nextX - nowX == 0)) {
						inputCheck = true;
					}
					break;
				case 金:
				case 銀成:
				case 桂成:
				case 香成:
				case 歩成:
					//下移動(左下)(右下)(下)
					if ((nextY - nowY == 1 && nextX - nowX == -1) || (nextY - nowY == 1 && nextX - nowX == 1) || (nextY - nowY == 1 && nextX - nowX == 0)) {
						inputCheck = true;
					}
					//上移動
					else if (nextY - nowY == -1 && (nextX - nowX == -1 || nextX - nowX == 1 || nextX - nowX == 0)) {
						inputCheck = true;
					}
					//横移動
					else if (nextY - nowY == 0 && (nextX - nowX == -1 || nextX - nowX == 1)) {
						inputCheck = true;
					}
					break;
				case 金2:
				case 銀成2:
				case 桂成2:
				case 香成2:
				case 歩成2:
					//下移動(左下)(右下)(下)
					if ((nextY - nowY == -1 && nextX - nowX == -1) || (nextY - nowY == -1 && nextX - nowX == 1) || (nextY - nowY == -1 && nextX - nowX == 0)) {
						inputCheck = true;
					}
					//上移動
					else if (nextY - nowY == 1 && (nextX - nowX == -1 || nextX - nowX == 1 || nextX - nowX == 0)) {
						inputCheck = true;
					}
					//横移動
					else if (nextY - nowY == 0 && (nextX - nowX == -1 || nextX - nowX == 1)) {
						inputCheck = true;
					}
					break;
				case 銀:
					if (((nextY - nowY == 1 || nextY - nowY == -1) && (nextX - nowX == 1 || nextX - nowX == -1)) || (nextY - nowY == -1 && nextX - nextX == 0)) {
						inputCheck = true;
					}
					break;
				case 銀2:
					if ((nextY - nowY == 1 || nextY - nowY == -1) && (nextX - nowX == 1 || nextX - nowX == -1) || (nextY - nowY == 1 && nextX - nextX == 0)) {
						inputCheck = true;
					}
					break;
				case 飛:
				case 飛2:
				case 飛成:
				case 飛成2:
					//移動先までの間に駒がないか
					//Y判定
					for (int i = pieceSearchStartY; i < pieceSearchGoalY-1; i++)
					{
						if (board[i][nowX] != 空) {
							movePiece = false;
							break;
						}
						else
						{
							movePiece = true;
						}
					}
					//移動先までの間に駒がないか
					//X判定
					for (int i = pieceSearchStartX; i < pieceSearchGoalX; i++)
					{
						if (board[nowY][i] != 空) {
							movePiece = false;
							break;
						}
						else
						{
							movePiece = true;
						}
					}

					//右1マス判定
					if (nextY - nowY == 0 && nextX - nowX == 1) {
						movePiece = true;
					}
					//下1マス判定
					if (nextY - nowY == 1 && nextX - nowX == 0) {
						movePiece = true;
					}

					//成っているときだけ
					if (board[nowY][nowX] == 飛成 || board[nowY][nowX] == 飛成2)
					{
						if (nextY - nowY == -1 || nextY - nowY == 1) {
							movePiece = true;
						}
						if (nextX - nowX == -1 || nextX - nowX == 1) {
							movePiece = true;
						}
					}

					//移動可能判定
					if (movePiece == true) {
						inputCheck = true;
					}
					break;
				case 角:
				case 角2:
				case 角成:
				case 角成2:
					//移動先までの間に駒がないか
					if (pieceSearchStartY == pieceSearchStartX)
					{
						for (int i = pieceSearchStartY; i < pieceSearchGoalY; i++)
						{
							if (board[i][nowX] != 空)
							{
								movePiece = false;
								break;
							}
							else
							{
								movePiece = true;
							}
						}
					}
					else if (pieceSearchStartY > pieceSearchStartX)
					{
						for (int i = pieceSearchStartX; i < pieceSearchGoalX; i++)
						{
							if (board[pieceSearchGoalY - 1][i] != 空)
							{
								movePiece = false;
								break;
							}
							else
							{
								movePiece = true;
							}
							pieceSearchGoalY--;

						}
					}
					else if (pieceSearchStartY < pieceSearchStartX)
					{
						for (int i = pieceSearchStartY; i < pieceSearchGoalY; i++)
						{
							if (board[i][pieceSearchGoalX - 1] != 空)
							{
								movePiece = false;
								break;
							}
							else
							{
								movePiece = true;
							}
							pieceSearchGoalX--;

						}
					}

					//成っているときだけ
					if (board[nowY][nowX] == 角成 || board[nowY][nowX] == 角成2)
					{
						if (nextY - nowY == -1 || nextY - nowY == 1) {
							movePiece = true;
						}
						if (nextX - nowX == -1 || nextX - nowX == 1) {
							movePiece = true;
						}
					}

					//移動可能判定
					if (movePiece == true) {
						inputCheck = true;
					}
					break;
				case 桂:
					if ((nextX - nowX == 1 || nextX - nowX == -1) && (nextY - nowY == -2)) {
						inputCheck = true;
					}

					break;
				case 桂2:
					if ((nextX - nowX == 1 || nextX - nowX == -1) && (nextY - nowY == 2)) {
						inputCheck = true;
					}

					break;
				case 香:
					//移動先までの間に駒がないか
					if (nextY < nowY) 
					{
						for (int i = pieceSearchStartY; i < pieceSearchGoalY; i++)
						{
							if (board[i][nowX] != 空) {
								movePiece = false;
								break;
							}
							else
							{
								movePiece = true;
							}
						}
						if (nextY - nowY == -1) {
							movePiece = true;
						}
					}
					if (movePiece == true) {
						inputCheck = true;
					}
					break;
				case 香2:
					//移動先までの間に駒がないか
					if (nextY > nowY) {
						for (int i = pieceSearchStartY; i < pieceSearchGoalY; i++)
						{
							if (board[i][nowX] != 空) {
								movePiece = false;
								break;
							}
							else
							{
								movePiece = true;
							}
						}
						if (nextY - nowY == 1) {
							movePiece = true;
						}
					}
					if (movePiece == true) {
						inputCheck = true;
					}
					break;
				case 歩:
					if (nextX == nowX && nextY - nowY == -1) {
						inputCheck = true;
					}

					break;
				case 歩2:
					if (nextX == nowX && nextY - nowY == 1) {
						inputCheck = true;
					}

					break;
				case 空:
					inputCheck = false;
					break;
				default:
					inputCheck = false;
					break;
				}
			}
			//持ち駒更新
			if (board[nextY][nextX] != 空)
			{
				if (playerTurn == Player1)
				{
					if (board[nextY][nextX] >= 王2 && board[nextY][nextX] <= 歩2)
					{
						holding[playerTurn][board[nextY][nextX] - PLAYER1NORMALOFFSET]++;
					}
					else if (board[nextY][nextX] >= 銀成2 && board[nextY][nextX] <= 歩成2)
					{
						holding[playerTurn][board[nextY][nextX] - PLAYER2NARIOFFSET]++;
					}
				}
				else if (playerTurn == Player2)
				{
					if (board[nextY][nextX] >= 王 && board[nextY][nextX] <= 歩)
					{
						holding[playerTurn][board[nextY][nextX] - PLAYER2NORMALOFFSET]++;
					}
					else if (board[nextY][nextX] >= 銀成 && board[nextY][nextX] <= 歩成)
					{
						holding[playerTurn][board[nextY][nextX] - PLAYER2NARIOFFSET]++;
					}
				}
			}
		}
		//持ち駒を移動するとき
		else if (tempIn >= 'A' && tempIn <= 'G') {
			if (board[nextY][nextX] == 空) {
				switch (holdingNomber)
				{
				case 歩:
				case 香:
				case 桂:
					if (playerTurn == Player1)
					{
						if (nextY == 0)
						{
							inputCheck = false;
							break;
						}
						else
						{
							//2歩判定
							if (holdingNomber == 歩)
							{
								for (int i = 0; i < HEIGHTMAX; i++)
								{
									//歩があるか
									if (board[i][nextX] == 歩)
									{
										nifuCheck = true;
										break;
									}
								}

								//歩が無かったら置く
								if (nifuCheck == false)
								{
									board[nextY][nextX] = holdingNomber;
									holding[playerTurn][holdingNomber]--;
									inputCheck = true;
								}
								else
								{
									inputCheck = false;
								}
							}
							else
							{
								board[nextY][nextX] = holdingNomber;
								holding[playerTurn][holdingNomber]--;
								inputCheck = true;
							}
						}
					}
					else if (playerTurn == Player2)
					{
						if (nextY == HEIGHTMAX - 1)
						{
							inputCheck = false;
							break;
						}
						else
						{
							if (holdingNomber == 歩)
							{
								for (int i = 0; i < HEIGHTMAX; i++)
								{
									//歩があるか
									if (board[i][nextX] == 歩2)
									{
										nifuCheck = true;
										break;
									}
								}
								//歩が無かったら置く
								if (nifuCheck == false)
								{
									board[nextY][nextX] = holdingNomber + PIECENUMBER;
									holding[playerTurn][holdingNomber]--;
									inputCheck = true;
								}
								else
								{
									inputCheck = false;
								}
							}
							else
							{
								board[nextY][nextX] = holdingNomber + PIECENUMBER;
								holding[playerTurn][holdingNomber]--;
								inputCheck = true;
							}
						}
					}
					break;
				default:
					if (playerTurn == Player1)
					{
						board[nextY][nextX] = holdingNomber;
						holding[playerTurn][holdingNomber]--;
						inputCheck = true;

					}
					else if (playerTurn == Player2)
					{
						board[nextY][nextX] = holdingNomber + PIECENUMBER;
						holding[playerTurn][holdingNomber]--;
						inputCheck = true;

					}
					break;
				}
			}
			else
			{
				inputCheck = false;
			}
		}

	}
	counter++;//ターン増加

	//場面の情報更新
	if (tempIn >= '1' && tempIn <= '9') {

		//移動前の情報確保
		kifu[counter].deletePiece = board[nextY][nextX];

		//成チェック
		if (playerTurn == Player1)
		{
			if (board[nowY][nowX] == 歩 || board[nowY][nowX] == 香 || board[nowY][nowX] == 桂 || board[nowY][nowX] == 角 || board[nowY][nowX] == 飛 || board[nowY][nowX] == 銀) {
				if (nextY >= PLAYER1NARIMIN && nextY <= PLAYER1NARIMAX)
				{
					printf("成りますか？0:No 1:Yes>");
					cin >> nariCheck;
				}
			}
		}
		else if (playerTurn == Player2)
		{
			if (board[nowY][nowX] == 歩2 || board[nowY][nowX] == 香2 || board[nowY][nowX] == 桂2 || board[nowY][nowX] == 角2 || board[nowY][nowX] == 飛2 || board[nowY][nowX] == 銀2) {
				if (nextY >= PLAYER2NARIMIN && nextY <= PLAYER2NARIMAX)
				{
					printf("成りますか？0:No 1:Yes>");
					cin >> nariCheck;
				}
			}
		}

		//成
		if (nariCheck == 1)
		{
			switch (board[nowY][nowX])
			{
			case 銀:
				board[nextY][nextX] = 銀成;
				break;
			case 銀2:
				board[nextY][nextX] = 銀成2;
				break;
			case 飛:
				board[nextY][nextX] = 飛成;
				break;
			case 飛2:
				board[nextY][nextX] = 飛成2;
				break;
			case 角:
				board[nextY][nextX] = 角成;
				break;
			case 角2:
				board[nextY][nextX] = 角成2;
				break;
			case 桂:
				board[nextY][nextX] = 桂成;
				break;
			case 桂2:
				board[nextY][nextX] = 桂成2;
				break;
			case 香:
				board[nextY][nextX] = 香成;
				break;
			case 香2:
				board[nextY][nextX] = 香成2;
				break;
			case 歩:
				board[nextY][nextX] = 歩成;
				break;
			case 歩2:
				board[nextY][nextX] = 歩成2;
				break;
			default:
				break;

			}
			kifu[counter].piece = board[nextY][nextX];
			board[nowY][nowX] = 空;
		}
		else
		{
			kifu[counter].piece = board[nowY][nowX];
			board[nextY][nextX] = board[nowY][nowX];
			board[nowY][nowX] = 空;
		}

	}
	else
	{
		kifu[counter].piece = holdingNomber;
		kifu[counter].deletePiece = 空;
	}
	//移動を反映
	kifu[counter].turn = counter;
	kifu[counter].playerTurn = playerTurn;
	kifu[counter].nextY = nextY;
	kifu[counter].nextX = nextX;
	if (tempIn >= 'A' && tempIn <= 'G')
	{
		nowY = YMOTIGOMA;
		nowX = XMOTIGOMA;
	}
	kifu[counter].nowY = nowY;
	kifu[counter].nowX = nowX;

	//ターン変更
	if (playerTurn == Player1) {
		playerTurn = Player2;
	}
	else
	{
		playerTurn = Player1;
	}
}

void Draw(int board[HEIGHTMAX][WIDTHMAX], Kifu* kifu)
{
	string turn = "0";//ターン
	string kanji = "0";//X
	string koma = "0";
	string boardDraw[HEIGHTMAX];

	for (int i = 0; i < HEIGHTMAX; i++)
	{
		for (int j = 0; j < WIDTHMAX; j++)
		{
			switch (board[i][j])
			{
			case 王:
				boardDraw[i] += "│ 王│";
				break;
			case 王2:
				boardDraw[i] += "│ \033[31m王\033[m│";
				break;
			case 金:
			case 銀成:
			case 桂成:
			case 香成:
				boardDraw[i] += "│ 金│";

				break;
			case 金2:
			case 銀成2:
			case 桂成2:
			case 香成2:
				boardDraw[i] += "│ \033[31m金\033[m│";

				break;
			case 銀:
				boardDraw[i] += "│ 銀│";

				break;
			case 銀2:
				boardDraw[i] += "│ \033[31m銀\033[m│";

				break;
			case 飛:
				boardDraw[i] += "│ 飛│";

				break;
			case 飛2:
				boardDraw[i] += "│ \033[31m飛\033[m│";

				break;
			case 角:
				boardDraw[i] += "│ 角│";

				break;
			case 角2:
				boardDraw[i] += "│ \033[31m角\033[m│";

				break;
			case 飛成:
				boardDraw[i] += "│ 龍│";

				break;
			case 飛成2:
				boardDraw[i] += "│ \033[31m龍\033[m│";

				break;
			case 角成:
				boardDraw[i] += "│ 馬│";

				break;
			case 角成2:
				boardDraw[i] += "│ \033[31m馬\033[m│";

				break;
			case 桂:
				boardDraw[i] += "│ 桂│";

				break;
			case 桂2:
				boardDraw[i] += "│ \033[31m桂\033[m│";

				break;
			case 香:
				boardDraw[i] += "│ 香│";

				break;
			case 香2:
				boardDraw[i] += "│ \033[31m香\033[m│";

				break;
			case 歩:
				boardDraw[i] += "│ 歩│";

				break;
			case 歩2:
				boardDraw[i] += "│ \033[31m歩\033[m│";

				break;
			case 歩成:
				boardDraw[i] += "│ ふ│";

				break;
			case 歩成2:
				boardDraw[i] += "│ \033[31mふ\033[m│";

				break;
			case 空:
				boardDraw[i] += "│　 │";

				break;
			default:
				break;
			}
		}
	}

	printf("　　一　 二　 三　 四　 五　 六　 七　 八　 九\n");

	for (int i = 0; i < HEIGHTMAX; i++)
	{
		printf("　┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐┌───┐\n");
		printf("%d ", i + 1);
		printf("%s\n", boardDraw[i].c_str());
		printf("　└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘└───┘\n");
	}

	printf("持ち駒\n");
	printf("　　Ａ　 　Ｂ　 　Ｃ　 　Ｄ　 　Ｅ　 　Ｆ　 　Ｇ\n");
	for (int i = 0; i < 2; i++)
	{
		if (i == 0) {
			printf("先　");
		}
		else
		{
			printf("後　");
		}
		for (int j = 7; j > 0; j--)
		{
			switch (holding[i][j])
			{
			case 0:
				printf("　　 　");
				break;
			case 1:
				switch (j)
				{
				case 王:
				case 王2:
					printf("王　");
					break;
				case 金:
				case 金2:
					printf("金　");
					break;
				case 銀:
				case 銀2:
				case 銀成:
				case 銀成2:
					printf("銀　");
					break;
				case 飛:
				case 飛2:
				case 飛成:
				case 飛成2:
					printf("飛　");
					break;
				case 角:
				case 角2:
				case 角成:
				case 角成2:
					printf("角　");
					break;
				case 桂:
				case 桂2:
				case 桂成:
				case 桂成2:
					printf("桂　");
					break;
				case 香:
				case 香2:
				case 香成:
				case 香成2:
					printf("香　");
					break;
				case 歩:
				case 歩2:
				case 歩成:
				case 歩成2:
					printf("歩　");
					break;
				default:
					break;
				}
				break;
			default:
				switch (j)
				{
				case 王:
				case 王2:
					printf("王×%d　", holding[i][j]);
					break;
				case 金:
				case 金2:
					printf("金×%d　", holding[i][j]);
					break;
				case 銀:
				case 銀2:
				case 銀成:
				case 銀成2:
					printf("銀×%d　", holding[i][j]);
					break;
				case 飛:
				case 飛2:
				case 飛成:
				case 飛成2:
					printf("飛×%d　", holding[i][j]);
					break;
				case 角:
				case 角2:
				case 角成:
				case 角成2:
					printf("角×%d　", holding[i][j]);
					break;
				case 桂:
				case 桂2:
				case 桂成:
				case 桂成2:
					printf("桂×%d　", holding[i][j]);
					break;
				case 香:
				case 香2:
				case 香成:
				case 香成2:
					printf("香×%d　", holding[i][j]);
					break;
				case 歩:
				case 歩2:
				case 歩成:
				case 歩成2:
					printf("歩×%d　", holding[i][j]);
					break;
				default:
					break;
				}
				break;
			}
		}
		printf("\n");
	}
	printf("\n");

	if (kifu[counter].playerTurn == Player1)
	{
		turn = "先";
	}
	else
	{
		turn = "後";
	}
	switch (kifu[counter].nextX)
	{
	case 0:
		kanji = "一";
		break;
	case 1:
		kanji = "二";
		break;
	case 2:
		kanji = "三";
		break;
	case 3:
		kanji = "四";
		break;
	case 4:
		kanji = "五";
		break;
	case 5:
		kanji = "六";
		break;
	case 6:
		kanji = "七";
		break;
	case 7:
		kanji = "八";
		break;
	case 8:
		kanji = "九";
		break;
	default:
		break;
	}
	switch (kifu[counter].piece)
	{
	case 王:
	case 王2:
		koma = "王";
		break;
	case 金:
	case 金2:
		koma = "金";
		break;
	case 銀:
	case 銀2:
		koma = "銀";
		break;
	case 銀成:
	case 銀成2:
		koma = "銀成";
		break;
	case 飛:
	case 飛2:
		koma = "飛";
		break;
	case 飛成:
	case 飛成2:
		koma = "飛成";
		break;
	case 角:
	case 角2:
		koma = "角";
		break;
	case 角成:
	case 角成2:
		koma = "角成";
		break;
	case 桂:
	case 桂2:
		koma = "桂";
		break;
	case 桂成:
	case 桂成2:
		koma = "桂成";
		break;
	case 香:
	case 香2:
		koma = "香";
		break;
	case 香成:
	case 香成2:
		koma = "香成";
	case 歩:
	case 歩2:
		koma = "歩";
		break;
	case 歩成:
	case 歩成2:
		koma = "歩成";
		break;
	default:
		koma = "　";
		break;
	}
	if (counter != 0) {
		printf("%s %s %d %s\n", turn.c_str(), kanji.c_str(), kifu[counter].nextY + 1, koma.c_str());
	}

	printf("\n");
	if (playerTurn == Player1) {
		printf("先手の番です");
	}
	else
	{
		printf("後手の番です");
	}
	printf("\n");
}

void Undo(int board[HEIGHTMAX][WIDTHMAX], Kifu* kifu) {

	for (int i = 0; i < PlayerCount; i++)
	{
		//成っていたら元に戻す
		switch (kifu[counter].piece)
		{
		case 銀成:
			kifu[counter].piece = 銀;
			break;
		case 銀成2:
			kifu[counter].piece = 銀;
			break;
		case 飛成:
			kifu[counter].piece = 飛;
			break;
		case 飛成2:
			kifu[counter].piece = 飛2;
			break;
		case 角成:
			kifu[counter].piece = 角;
			break;
		case 角成2:
			kifu[counter].piece = 角2;
			break;
		case 桂成:
			kifu[counter].piece = 桂;
			break;
		case 桂成2:
			kifu[counter].piece = 桂2;
			break;
		case 香成:
			kifu[counter].piece = 香;
			break;
		case 香成2:
			kifu[counter].piece = 香2;
			break;
		case 歩成:
			kifu[counter].piece = 歩;
			break;
		case 歩成2:
			kifu[counter].piece = 歩2;
			break;
		default:
			break;

		}
		//盤の駒を動かした場合
		if (kifu[counter].nowY != YMOTIGOMA || kifu[counter].nowX != XMOTIGOMA)
		{
			//前にいた座標へ駒を戻す
			board[kifu[counter].nowY][kifu[counter].nowX] = kifu[counter].piece;
			//今いる場所に上書した駒を戻す
			board[kifu[counter].nextY][kifu[counter].nextX] = kifu[counter].deletePiece;

			//持ち駒を戻す
			if (kifu[counter].deletePiece != 空)
			{
				if (kifu[counter].playerTurn == Player1)
				{
					holding[kifu[counter].playerTurn][kifu[counter].deletePiece - PIECENUMBER]--;
				}
				else
				{
					holding[kifu[counter].playerTurn][kifu[counter].deletePiece]--;
				}
			}
		}
		//持ち駒を使った場合
		else if (kifu[counter].nowY == YMOTIGOMA || kifu[counter].nowX == XMOTIGOMA)
		{
			if (kifu[counter].playerTurn == Player1)
			{
				holding[kifu[counter].playerTurn][board[kifu[counter].nextY][kifu[counter].nextX]]++;
			}
			else if (kifu[counter].playerTurn == Player2)
			{
				holding[kifu[counter].playerTurn][board[kifu[counter].nextY][kifu[counter].nextX] - PIECENUMBER]++;
			}
			board[kifu[counter].nextY][kifu[counter].nextX] = kifu[counter].deletePiece;
		}
		counter--;
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
