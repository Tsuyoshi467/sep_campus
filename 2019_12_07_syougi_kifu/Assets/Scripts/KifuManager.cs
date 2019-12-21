using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class KifuManager : MonoBehaviour
{
    [SerializeField]
    GameObject []pieceDate = default;//駒オブジェクト取得

    [SerializeField]
    TextAsset textAsset = default;  //読み込むテキスト
    
    [SerializeField]
    SpriteRenderer []pieceSpriteRenderer = default;//オブジェクトの絵柄取得用

    [SerializeField]
    Sprite [] pieceSpriteDate = default;//使う絵柄

    [SerializeField]
    Text []kifuText = default;//棋譜を表示するテキスト

    [SerializeField]
    GameObject basePiece = default;//board[0,0]の位置にある駒

    string loadText;      //読み込んだ文字を一つにする  
    string[] splitText;   //1行
    string[] splitDate;   //カンマ区切り

    //駒の種類
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

    //駒の絵柄
    enum PieceSprite
    {
        Gin,        //銀
        Hisya,      //飛車
        Kaku,       //角
        Keima,      //桂馬
        Kyousya,    //香車
        Fu,         //歩
        GinNari,    //成った銀
        HisyaNari,  //成った飛車
        KakuNari,   //成った角
        KeimaNari,  //成った桂馬
        KyousyaNari,//成った香車
        FuNari,     //成った歩

        PieceSpriteLength,
    }

    //棋譜のテキストの種類
    enum TextState
    {
        Turn, //先手化後手か
        X,    //動かした駒のX座標
        Y,    //動かした駒のY座標
        Piece,//動かした駒
    }

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
    public int[] splitStete;    //読み込んだデータをひとつひとつ
    int boardY_start = 0;       //boardとUnity上の座標Yの差
    int boardX_start = 0;       //boardとUnity上の座標Xの差
    const int height = 9;　　　 //高さ最大値
    const int width = 9;        //幅最大値
    const int notPiece = 99;    //駒がないとき用
    const int piece_kara = 28;  //読み込んだ駒が空
    const int moveTime = 80;    //移動間隔
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
        pieceSpriteRenderer = new SpriteRenderer[pieceDate.Length];
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

        boardX_start = 0 - (int)basePiece.transform.position.x;  //boardのx0とUnity上の座標xの差を出す
        boardY_start = 0 - (int)basePiece.transform.position.y;  //boardのy0とUnity上の座標yの差を出す

        //board初期化
        for (int i = 0; i < height; i++)
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
        //boardに駒を配置
        for(int i = 0; i < pieceDate.Length; i++)
        {
            pieceSpriteRenderer[i] = pieceDate[i].GetComponent<SpriteRenderer>();
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
                KifuText();    //棋譜のテキスト更新
                kifuCounter++; //棋譜カウント更新
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
            //動かした駒のタグで分岐
            switch (pieceDate[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].tag)
            {
                case "Gin":
                    pieceSpriteRenderer[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].sprite = pieceSpriteDate[(int)PieceSprite.Gin];
                    break;
                case "Hisya":
                    pieceSpriteRenderer[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].sprite = pieceSpriteDate[(int)PieceSprite.Hisya];
                    break;
                case "kaku":
                    pieceSpriteRenderer[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].sprite = pieceSpriteDate[(int)PieceSprite.Kaku];
                    break;
                case "Keima":
                    pieceSpriteRenderer[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].sprite = pieceSpriteDate[(int)PieceSprite.Keima];
                    break;
                case "Kyousya":
                    pieceSpriteRenderer[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].sprite = pieceSpriteDate[(int)PieceSprite.Kyousya];
                    break;
                case "Fu":
                    pieceSpriteRenderer[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].sprite = pieceSpriteDate[(int)PieceSprite.Fu];
                    break;
                default:
                    break;
            }
            pieceDate[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].SetActive(false);//駒を非表示にする
        }
        //持ち駒を使ったとき
        if (kifu[kifuCounter].nowY == notPiece || kifu[kifuCounter].nowX == notPiece)
        {
            //動かした駒の種類で分岐
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
        //盤の駒を動かした時
        else if (kifu[kifuCounter].nowY != notPiece && kifu[kifuCounter].nowX != notPiece)
        {
            //動かした駒が成っていたら絵柄を変更
            switch (kifu[kifuCounter].piece)
            {
                case (int)Piece.銀成:
                case (int)Piece.銀成2:
                    pieceSpriteRenderer[board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX]].sprite = pieceSpriteDate[(int)PieceSprite.GinNari];
                    break;
                case (int)Piece.飛成:
                case (int)Piece.飛成2:
                    pieceSpriteRenderer[board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX]].sprite = pieceSpriteDate[(int)PieceSprite.HisyaNari];
                    break;
                case (int)Piece.角成:
                case (int)Piece.角成2:
                    pieceSpriteRenderer[board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX]].sprite = pieceSpriteDate[(int)PieceSprite.KakuNari];
                    break;
                case (int)Piece.桂成:
                case (int)Piece.桂成2:
                    pieceSpriteRenderer[board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX]].sprite = pieceSpriteDate[(int)PieceSprite.KeimaNari];
                    break;
                case (int)Piece.香成:
                case (int)Piece.香成2:
                    pieceSpriteRenderer[board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX]].sprite = pieceSpriteDate[(int)PieceSprite.KyousyaNari];
                    break;
                case (int)Piece.歩成:
                case (int)Piece.歩成2:
                    pieceSpriteRenderer[board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX]].sprite = pieceSpriteDate[(int)PieceSprite.FuNari];
                    break;
                default:
                    break;
            }
            //棋譜をもとに配列を更新
            board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX] = board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX];
            //移動元の中身を消す
            board[kifu[kifuCounter].nowY, kifu[kifuCounter].nowX] = notPiece;
            //移動した差を入れる
            pos.y = (kifu[kifuCounter].nextY - kifu[kifuCounter].nowY) * -1;
            pos.x = (kifu[kifuCounter].nextX - kifu[kifuCounter].nowX) * -1;
            pos.z = 0;
            //入れられた差をオブジェクトに反映
            pos.y =  pieceDate[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].transform.position.y + pos.y;
            pos.x =  pieceDate[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].transform.position.x + pos.x;
            pos.z =  pieceDate[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].transform.position.z + pos.z;
            pieceDate[board[kifu[kifuCounter].nextY, kifu[kifuCounter].nextX]].transform.DOMove(pos,1f);
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
                if(kifuCounter % 2 == 0)
                {
                    pieceDate[i].transform.rotation = Quaternion.Euler(0, 0,0);//駒の向きを変える
                }
                else
                {
                    pieceDate[i].transform.rotation = Quaternion.Euler(0, 0, 180f);//駒の向きを変える
                }
                pos = pieceDate[i].transform.position;                //消えている駒の座標取得
                pos.y = (kifu[kifuCounter].nextY + boardY_start) * -1;//座標Y変更
                pos.x = (kifu[kifuCounter].nextX + boardX_start) * -1;//座標X変更
                pieceDate[i].transform.position = pos;                //駒の座標を変更
                board[Mathf.Abs((int)pos.y + boardY_start), (int)Mathf.Abs((int)pos.x + boardX_start)] = i;
                pieceDate[i].SetActive(true);                         //駒を表示
                break;
            }
        }
    }

    //棋譜のテキスト更新
    //引数:無し
    void KifuText()
    {
        //棋譜の番号で先手後手を判断
        if(kifuCounter % 2 == 0)
        {
            kifuText[(int)TextState.Turn].text = "先手";
        }
        else
        {
            kifuText[(int)TextState.Turn].text = "後手";
        }
        //棋譜のnextXで分岐し数字に変換しテキストを更新
        switch (kifu[kifuCounter].nextX)
        {
            case 0:
                kifuText[(int)TextState.X].text = "1";
                break;
            case 1:
                kifuText[(int)TextState.X].text = "2";
                break;
            case 2:
                kifuText[(int)TextState.X].text = "3";
                break;
            case 3:
                kifuText[(int)TextState.X].text = "4";
                break;
            case 4:
                kifuText[(int)TextState.X].text = "5";
                break;
            case 5:
                kifuText[(int)TextState.X].text = "6";
                break;
            case 6:
                kifuText[(int)TextState.X].text = "7";
                break;
            case 7:
                kifuText[(int)TextState.X].text = "8";
                break;
            case 8:
                kifuText[(int)TextState.X].text = "9";
                break;
            default:
                kifuText[(int)TextState.X].text = "0";
                break;
        }
        //棋譜のnextYで分岐し漢字に変換しテキストを更新
        switch (kifu[kifuCounter].nextY)
        {
            case 0:
                kifuText[(int)TextState.Y].text = "一";
                break;
            case 1:
                kifuText[(int)TextState.Y].text = "二";
                break;
            case 2:
                kifuText[(int)TextState.Y].text = "三";
                break;
            case 3:
                kifuText[(int)TextState.Y].text = "四";
                break;
            case 4:
                kifuText[(int)TextState.Y].text = "五";
                break;
            case 5:
                kifuText[(int)TextState.Y].text = "六";
                break;
            case 6:
                kifuText[(int)TextState.Y].text = "七";
                break;
            case 7:
                kifuText[(int)TextState.Y].text = "八";
                break;
            case 8:
                kifuText[(int)TextState.Y].text = "九";
                break;
            default:
                kifuText[(int)TextState.Y].text = "零";
                break;
        }
        //棋譜のpieceで分岐し対応する駒に変換しテキストを更新
        switch (kifu[kifuCounter].piece)
        {
            case (int)Piece.王:
            case (int)Piece.王2:
                kifuText[(int)TextState.Piece].text = "王";
                break;
            case (int)Piece.金:
            case (int)Piece.金2:
                kifuText[(int)TextState.Piece].text = "金";
                break;
            case (int)Piece.銀:
            case (int)Piece.銀2:
                kifuText[(int)TextState.Piece].text = "銀";
                break;
            case (int)Piece.飛:
            case (int)Piece.飛2:
                kifuText[(int)TextState.Piece].text = "飛";
                break;
            case (int)Piece.角:
            case (int)Piece.角2:
                kifuText[(int)TextState.Piece].text = "角";
                break;
            case (int)Piece.桂:
            case (int)Piece.桂2:
                kifuText[(int)TextState.Piece].text = "桂";
                break;
            case (int)Piece.香:
            case (int)Piece.香2:
                kifuText[(int)TextState.Piece].text = "香";
                break;
            case (int)Piece.歩:
            case (int)Piece.歩2:
                kifuText[(int)TextState.Piece].text = "歩";
                break;
            case (int)Piece.銀成:
            case (int)Piece.銀成2:
                kifuText[(int)TextState.Piece].text = "銀成";
                break;
            case (int)Piece.飛成:
            case (int)Piece.飛成2:
                kifuText[(int)TextState.Piece].text = "飛成";
                break;
            case (int)Piece.角成:
            case (int)Piece.角成2:
                kifuText[(int)TextState.Piece].text = "角成";
                break;
            case (int)Piece.桂成:
            case (int)Piece.桂成2:
                kifuText[(int)TextState.Piece].text = "桂成";
                break;
            case (int)Piece.香成:
            case (int)Piece.香成2:
                kifuText[(int)TextState.Piece].text = "香成";
                break;
            case (int)Piece.歩成:
            case (int)Piece.歩成2:
                kifuText[(int)TextState.Piece].text = "歩成";
                break;
            default:
                kifuText[(int)TextState.Piece].text = "空";
                break;
        }
    }
}
