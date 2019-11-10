// 2019_11_09_question3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>


void Fibonacci(unsigned  long * list,int listSize) {
	unsigned long leftSide = 0;
	unsigned long  rightSide = 1;
	unsigned long  anser = 0;
	for (int i = 0; i < listSize; i++)
	{
		list[i] = anser;
		anser = leftSide + rightSide;
		leftSide = anser - leftSide;
		rightSide = anser;
		printf("%d %lu\n",i,list[i]);
	}
}

int main()
{
	unsigned long  list[100] = { 0 };
	int listSize = sizeof list / sizeof * list;
	Fibonacci(list,listSize);

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
