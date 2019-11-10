// 2019_11_09_question5.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#define ARRAY_SIZE(array) (sizeof (array)/sizeof *(array))

enum ChangePattern
{
	
	no,//記号なし
	plus,//＋
	minus,//-

	chagePatternSize,
};

//確認する記号の変更
void CounterChenger(int *pattern,int patternCounter) {
	
	pattern[patternCounter] = pattern[patternCounter] + 1;
	if (pattern[patternCounter] == 3) {
		pattern[patternCounter] = no;
		CounterChenger(pattern, patternCounter + 1);
	}
}

void HundredCheck()
{
	//リスト
	int list[] = { 1,2,3,4,5,6,7,8,9 };
	//記号パターン
	int pattern[9] = {0};
	//値保存
	int temp[10];
	
	//リストの要素数
	int listSize = ARRAY_SIZE(list);

	//パターンの要素数
	int patternSize = ARRAY_SIZE(pattern);

	//値保存用の要素数
	int	tempSize = ARRAY_SIZE(temp);
	
	//答えが100か確認
	int anser = 0;

	//値保存用配列の要素数
	int tempCounter = 0;
	
	//リストの要素数
	int listCounter = 0;
	
	//パターンの要素数
	int patternCounter = 0;

	while (true)
	{
		//初期化
		patternCounter = 0;
		listCounter = 0;
		tempCounter = 0;
		anser = 0;
		for (int i = 0; i < tempSize; i++)
		{
			temp[i] = 0;
		}

		//確認する記号を変更
		CounterChenger(pattern, patternCounter);
		
		//確認が終わったかのチェック
		if (pattern[patternSize - 1] == plus) {
			break;
		}
		temp[0] = list[0];


		for (int i = 0; i < listSize; i++)
		{
			//値を保存
			switch (pattern[i])
			{
			case plus:
				++tempCounter;
				temp[tempCounter] = list[listCounter + 1];
				++listCounter;
				
				break;
			case minus:
				++tempCounter;
				temp[tempCounter] = list[listCounter + 1];
				++listCounter;

				break;
			case no:
				temp[tempCounter] = temp[tempCounter] * 10 + list[listCounter + 1];
				++listCounter;

				break;
			}
			//最後まで行ったかチェック
			if (listCounter == listSize - 1) {
				break;
			}
		}

		//0番目の要素を追加
		anser = temp[0];
		tempCounter = 0;
		
		for (int i = 0; i < listSize; i++)
		{
			//記号によりプラスマイナスを決める
			switch (pattern[i])
			{
			case plus:
				anser = anser + temp[tempCounter + 1];
				++tempCounter;
				break;
			case minus:	
				anser = anser - temp[tempCounter + 1];
				++tempCounter;
				break;
			}
		}
		//答えの確認
		if (anser == 100) {
			printf("1");
			for (int i = 0; i < listSize-1; i++)
			{
				switch (pattern[i])
				{
				case plus:						
					printf(" + ");
					printf("%d", i + 2);

					break;
				case minus:	
					printf(" - ");
					printf("%d", i + 2);


					break;
				case no:
					printf("%d", i + 2);

					break;
				}
				
			}
			printf(" = 100");
			printf("\n");
		}
	}
}


int main()
{
	HundredCheck();
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
