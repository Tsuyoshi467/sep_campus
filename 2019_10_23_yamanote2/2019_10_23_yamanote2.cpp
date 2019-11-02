// 2019_10_23_yamanote2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#define Time 2
enum StationDate //駅ID
{
	St1,
	St2,
	St3,
	St4,
	St5,
	St6,
	St7,
	St8,
	St9,
	St10,

	StMax
};
enum StationTime //駅Time
{
	Time1  = 3,
	Time2  = 5,
	Time3  = 8,
	Time4  = 7,
	Time5  = 6,
	Time6  = 4,
	Time7  = 9,
	Time8  = 5,
	Time9  = 1,
	Time10 = 7,
};

struct Date //駅データ
{
	int id;
	int time;
};

int main()
{
	//駅IdとTimeを入れる
	int station[StMax][Time] = { {St1, Time1 },
						      {St2, Time2 },
						      {St3, Time3 },
						      {St4, Time4 },
						      {St5, Time5 },
						      {St6, Time6 },
						      {St7, Time7 },
						      {St8, Time8 },
						      {St9, Time9 },
						      {St10,Time10},
	};

	int start = 0;//乗車
	int goal  = 0;//降車
	int right = 0;//右回り
	int left  = 0;//左回り
	int anser = 0;//所要時間
	int now = 0;//経過駅
	start = St7;//乗車駅を設定
	goal = St1; //降車駅を設定

	if (start < goal) {
		for (int i = start; i < goal; i++)
		{
			right += station[i][1];//StのTimeを加算

			//iが最大駅数まで行ったら0に
			if (i == StMax - 1) {
				i = 0;
			}
		}
		now = start-1;
		if (now < 0) {
			now = StMax-1;
		}
		while (now != goal-1)
		{
			left += station[now][1];//StのTimeを加算
			if (now <= St1) {
				now = StMax;
			}
			now--;
		}
	}
	else
	{
		for (int i = goal; i < start; i++)
		{
			left += station[i][1];//StのTimeを加算
			if (i == StMax - 1) {
				i = 0;
			}
		}	
		now = start;
		while (now != goal)
		{
			right += station[now][1];//StのTimeを加算
			++now; 
			if (now == StMax) {
				now = 0;
			}
		}
	}

	if (right > left) {
		anser = left;
	}
	else if (right < left) {
		anser = right;
	}
	printf("%d分 %d分", right, left);
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
