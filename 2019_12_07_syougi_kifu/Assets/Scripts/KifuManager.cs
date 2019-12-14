using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KifuManager : MonoBehaviour
{
    [SerializeField]
    GameObject []pieceDate;//駒オブジェクト取得

    [SerializeField]
    TextAsset textAsset;  //読み込むテキスト
    string loadText;      //読み込んだ文字を一つにする  
    string[] splitText;   //1行
    string[] splitDate;   //カンマ区切り

    public enum Piece
    {
        //通常の駒(Player1) 
        王,
        金,
        銀,
        飛,
        角,
        桂,
        香,
        歩,

        //通常の駒(Player2) 
        王2,
        金2,
        銀2,
        飛2,
        角2,
        桂2,
        香2,
        歩2,

        //成り状態の駒(Player1) 
        銀成,
        飛成,
        角成,
        桂成,
        香成,
        歩成,

        //成り状態の駒(Player2) 
        銀成2,
        飛成2,
        角成2,
        桂成2,
        香成2,
        歩成2,

        空,

    };
    //棋譜構造体
    struct Kifu
    {
        public int nextY;//移動先座標Y
        public int nextX;//移動先座標X
        public int nowY; //移動元座標Y
        public int nowX; //移動元座標X
        public int piece;//移動先にあった駒
    }

    int kifuCounter = 0;
    
    Kifu[] kifu;                //棋譜構造体

    Vector3 pos;                //駒座標取得用 
    int [,]board;               //盤面の二次元配列
    public int[] splitStete;   //読み込んだデータをひとつひとつ
    const int boardY_start = -4;//boardとUnity上の座標Yの差
    const int boardX_start = -4;//boardとUnity上の座標Xの差
    const int height = 9;　　　 //高さ最大値
    const int width = 9;        //幅最大値
    const int notPiece = 99;    //駒がないとき用
    const int piece_kara = 28;  //読み込んだ駒が空
    const int moveTime = 30;    //移動間隔
    public int kifuNumber = 0;　//行数
    private int dateNumber = 0; //総文字数
    private int splitCounter = 0;//文字カウンター
    private int drawTimer = 0;   //表示タイマー

    // Start is called before the first frame update
    void Start()
    {
        loadText = textAsset.text;
        splitText = loadText.Split('\n');    //行の終わり
        splitDate = loadText.Split(',','\n');//カンマ
        kifuNumber = splitText.Length;       //行の長さ取得
        dateNumber = splitDate.Length;       //文字の数取得
        kifu = new Kifu[kifuNumber];         //棋譜生成
        splitStete = new int[dateNumber];　　//総文字数の要素数の配列
        board = new int[height, width];      //計算用二次元配列

        for(int i = 0;i < dateNumber -1; i++)
        {
            splitStete[i] = int.Parse(splitDate[i]);//カンマ区切りで配列に入れる
        }

        //文字を入れていく
        for (int i = 0; i < kifuNumber; i++)
        {
            if (splitCounter < dateNumber - 1)
            {
                kifu[i].nowY = splitStete[splitCounter];
                ++splitCounter;
                kifu[i].nowX = splitStete[splitCounter];
                ++splitCounter;
                kifu[i].nextY = splitStete[splitCounter];
                ++splitCounter;
                kifu[i].nextX = splitStete[splitCounter];
                ++splitCounter;
                kifu[i].piece = splitStete[splitCounter];
                ++splitCounter;
            }
        }

        //board初期化
        for(int i = 0; i < height; i++)
        {
            for(int j = 0;j < width; j++)
            {
                board[i, j] = notPiece;
            }
        }
        //boardに駒を配置
        for(int i = 0; i < pieceDate.Length; i++)
        {
            pos = pieceDate[i].transform.position;
            board[Mathf.Abs((int)pos.y + boardY_start), (int)Mathf.Abs((int)pos.x + boardX_start)] = i;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (kifuCounter < kifuNumber-1)
        {
            if (drawTimer % moveTime == 0)
            {
                Draw();　　　　//表示
                kifuCounter++;//棋譜カウント更新
            }
            ++drawTimer;//表示タイマー更新
        }
    }

    //描画
    void Draw()
    {
        //駒がとられたとき非表示にする
        if(board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX] != notPiece)
        {
            pieceDate[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].SetActive(false);//駒を非表示にする
        }
        if (kifu[kifuCounter].nowY == notPiece || kifu[kifuCounter].nowX == notPiece)
        {
            switch (kifu[kifuCounter].piece)
            {
                case (int)Piece.金:
                case (int)Piece.金2:
                    MotigomaMove("Kin");
                    break;
                case (int)Piece.銀:
                case (int)Piece.銀2:
                    MotigomaMove("Gin");
                    break;
                case (int)Piece.飛:
                case (int)Piece.飛2:
                    MotigomaMove("Hisya");
                    break;
                case (int)Piece.角:
                case (int)Piece.角2:
                    
                    MotigomaMove("Kaku");
                    break;
                case (int)Piece.桂:
                case (int)Piece.桂2:
                    MotigomaMove("Keima");
                    break;
                case (int)Piece.香:
                case (int)Piece.香2:
                    MotigomaMove("Kyousya");
                    break;
                case (int)Piece.歩:
                case (int)Piece.歩2:
                    MotigomaMove("Fu");
                    break;
                default:
                    Debug.LogError("タグがありません");
                    break;
            }

        }
        else if (kifu[kifuCounter].nowY != notPiece || kifu[kifuCounter].nowX != notPiece)
        {
            //棋譜をもとに配列を更新
            board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX] = board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX];
            //移動元の中身を消す
            board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX] = notPiece;
            //移動した差を入れる
            pos.y = (kifu[kifuCounter].nextY - kifu[kifuCounter].nowY) * -1;
            pos.x = (kifu[kifuCounter].nextX - kifu[kifuCounter].nowX) * -1;
            pos.z = 0;
            //入れられた差をオブジェクトに反映
            pieceDate[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].transform.position += pos;
        }

    }
    //持ち駒使用時の表示
    //引数：駒のタグ名
    void MotigomaMove(string pieceName)
    {
        for (int i = 0; i < pieceDate.Length; i++)
        {
            if (pieceDate[i].activeSelf == false && pieceDate[i].tag == pieceName)
            {
                pieceDate[i].transform.Rotate(new Vector3(0, 0, 180));//駒の向きを変える
                pos = pieceDate[i].transform.position;                //消えている駒の座標取得
                pos.y = (kifu[kifuCounter].nextY + boardY_start) * -1;//座標Y変更
                pos.x = (kifu[kifuCounter].nextX + boardX_start) * -1;//座標X変更
                pieceDate[i].transform.position = pos;                //駒の座標を変更
                pieceDate[i].SetActive(true);                         //駒を表示
                break;
            }
        }
    }
}
