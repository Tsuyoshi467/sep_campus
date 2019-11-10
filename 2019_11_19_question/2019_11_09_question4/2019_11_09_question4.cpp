// 2019_11_09_question4.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#define ARRAT_SIZE(array) (sizeof (array)/sizeof *(array)) 

int MaxNum(int* list,int listSize) {

	//解答の戻り値
	int anser = 0;
	//入れ替え用
	int temp = 0;
	//何個の数字があるかカウント
	int singleListSize = 0;

	//数字の数を数える
	for (int i = 0; i < listSize; i++) {
		
		//listの数字が10以下か判定
		if (list[i] / 10 == 0)
		{
			++singleListSize;
		}
		else
		{
			singleListSize += 2;
		}

	}
	int singleList[5];
	//singleListCounterの要素数を増やす
	int singleListCounter = 0;
	for (int i = 0; i < listSize; i++) {
	
		if (list[i] / 10 == 0)
		{

			singleList[singleListCounter] = list[i];
		}
		else 
		{
			singleList[singleListCounter] = list[i] / 10;

			++singleListCounter;
			singleList[singleListCounter + 1]  = list[i] % 10;
			
		}
		++singleListCounter;

	}
	//ソート
	for (int i = 0; i < singleListSize; i++) {
		for (int j = i + 1; j < singleListSize; j++) {
			if (singleList[i] < singleList[j]) {
				temp = singleList[i];
				singleList[i] = singleList[j];
				singleList[j] = temp;
			}
		}
	}
	for (int i = 0; i < singleListSize; i++) {

		int k = singleList[i]; 
		for (int j = singleListSize - 1 - i; j > 0; j--) {
			k *= 10;
		}
		anser += k;
	}
	return anser;
}
int main()
{
	int list[] = { 50, 2, 1, 9 };
	int listSize = ARRAT_SIZE(list);
	printf("%d", MaxNum(list, listSize));
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
