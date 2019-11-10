// 2019_11_09_question2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

char * Composition(char* anser,char *alphabet,char *number, int alphabetSIze, int numberSize) {
	
	
	anser[0] = alphabet[0];
	anser[1] = number[0];
	anser[2] = alphabet[1];
	anser[3] = number[1];
	anser[4] = alphabet[2];
	anser[5] = number[2];
	
	return anser;
}

int main()
{
	char alphabet[] = { 'a','b','c' };
	char number[]   = { '1','2','3' }; 
	
	int alphabetSize = sizeof alphabet / sizeof *alphabet;
	int numberSize = sizeof number / sizeof * number;
	
	char* anser = new char[alphabetSize + numberSize];
	int anserSize = alphabetSize + numberSize;

	Composition(anser,alphabet, number, alphabetSize, numberSize);
	
	for (int i = 0; i < anserSize; i++)
	{
		printf("%c", anser[i]);
	}
	printf("%c", anser[0]);
	
	
	delete[]anser;
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
