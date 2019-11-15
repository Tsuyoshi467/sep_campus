using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class BlockController : MonoBehaviour
{
    //操作受付用
    InputManager inputManager;

    //ブロックの種類
    enum BlockNumber
    {
        IBlock,
        JBlock,
        LBlock,
        OBlock,
        SBlock,
        TBlock,
        ZBlock,

        NullBlock,
    }

    const int HEIGHTMAX = 20; //高さ最大値
    const int HEIGHTMIN = 0; //高さ最小値
    const int WIDTHMAX = 10; //幅最大値
    const int WIDTHMIN = 0; //幅最小値


    const int BLOCKARRAYSIZE = 5; //ブロックの配列の大きさ
    const int BLOCKNUM = 4;       //ブロックの数

    const int INBLOCK = 1;  //ブロックがある
    const int NOTBLOCK = 0; //ブロックがない

    const int BLOCKCENTER = 2; //ブロックの中心


    int[,] blockDate = new int[BLOCKARRAYSIZE, BLOCKARRAYSIZE]; //ブロック用
    int[,] saveblock = new int[BLOCKARRAYSIZE, BLOCKARRAYSIZE]; //ブロックの状態保存


    int[,] moveBlock = new int[HEIGHTMAX, WIDTHMAX];                  //動かすブロック
    int[,] zangaiBlock = new int[HEIGHTMAX + BLOCKARRAYSIZE, WIDTHMAX]; //積みあがるブロック

    int[] offsetY = new int[BLOCKNUM]; //ブロックの中心との高さの差
    int[] offsetX = new int[BLOCKNUM]; //ブロックの中心との幅の差


    [SerializeField]
    private GameObject block; //表示するオブジェクト


    GameObject[] moveBlockObj = new GameObject[BLOCKNUM];            //moveBlockのオブジェクト
    GameObject[,] zangaiBlockObj = new GameObject[HEIGHTMAX, WIDTHMAX]; //zangaiのオブジェクト


    Vector3[] blockPositon = new Vector3[BLOCKNUM];//moveBlockの座標

    Vector3 zangaiPositon; //zangaiの座標

    int Y = 0; //縦
    int X = 0; //横

    int blockDownTimer = 0;         //下移動判定用

    bool endTimerCheck = false; //ブロックを設置するかどうか
    int endTime = 0;                //遷移するまでの時間

    // Use this for initialization
    void Start()
    {
        inputManager = GetComponent<InputManager>();

        for (int i = 0; i < HEIGHTMAX; i++)
        {
            for (int j = 0; j < WIDTHMAX; j++)
            {
                moveBlock[Y, X] = 0;
                zangaiBlock[i, j] = 0;
                zangaiBlockObj[Y, X] = null;
            }
        }
        BlockSelect();
    }
    // Update is called once per frame
    void Update()
    {
        Move();
        Draw();
    }

    //表示するブロックを設定
    void BlockSelect()
    {
        int blockSelect = 0; //表示するブロック

        //座標
        int StartPositonY = HEIGHTMAX - BLOCKARRAYSIZE;
        int StartPositonX = WIDTHMAX / 2;
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                moveBlock[Y, X] = 0;
            }
        }

        //出現するブロックを選択
        blockSelect = Random.Range((int)BlockNumber.IBlock, (int)BlockNumber.NullBlock);

        switch (blockSelect)
        {
            case (int)BlockNumber.IBlock:
                blockDate = new int[,]{{ 0,0,1,0,0},
                                       { 0,0,1,0,0},
                                       { 0,0,1,0,0},
                                       { 0,0,1,0,0},
                                       { 0,0,0,0,0}};
                break;
            case (int)BlockNumber.JBlock:
                blockDate = new int[,]{{ 0,0,0,0,0},
                                       { 0,1,0,0,0},
                                       { 0,1,1,1,0},
                                       { 0,0,0,0,0},
                                       { 0,0,0,0,0}};
                break;
            case (int)BlockNumber.LBlock:
                blockDate = new int[,]{{ 0,0,0,0,0},
                                       { 0,0,0,1,0},
                                       { 0,1,1,1,0},
                                       { 0,0,0,0,0},
                                       { 0,0,0,0,0}};
                break;
            case (int)BlockNumber.OBlock:
                blockDate = new int[,]{{ 0,0,0,0,0},
                                       { 0,1,1,0,0},
                                       { 0,1,1,0,0},
                                       { 0,0,0,0,0},
                                       { 0,0,0,0,0}};
                break;
            case (int)BlockNumber.SBlock:
                blockDate = new int[,]{{ 0,0,0,0,0},
                                       { 0,0,1,1,0},
                                       { 0,1,1,0,0},
                                       { 0,0,0,0,0},
                                       { 0,0,0,0,0}};
                break;
            case (int)BlockNumber.TBlock:
                blockDate = new int[,]{{ 0,0,0,0,0},
                                       { 0,0,1,0,0},
                                       { 0,1,1,1,0},
                                       { 0,0,0,0,0},
                                       { 0,0,0,0,0}};
                break;
            case (int)BlockNumber.ZBlock:
                blockDate = new int[,]{{ 0,0,0,0,0},
                                       { 0,1,1,0,0},
                                       { 0,0,1,1,0},
                                       { 0,0,0,0,0},
                                       { 0,0,0,0,0}};
                break;
            default:
                blockDate = new int[,]{{ 0,0,1,0,0},
                                       { 0,0,1,0,0},
                                       { 0,0,1,0,0},
                                       { 0,0,1,0,0},
                                       { 0,0,0,0,0}};
                break;
        }

        //ブロックの座標を入れる
        for (Y = HEIGHTMIN; Y < BLOCKARRAYSIZE; Y++)
        {
            for (X = WIDTHMIN; X < BLOCKARRAYSIZE; X++)
            {
                moveBlock[Y + StartPositonY, X + StartPositonX] = blockDate[Y, X];
                saveblock[Y, X] = blockDate[Y, X];
            }
            if (zangaiBlock[Y + StartPositonY, 7] != NOTBLOCK)
            {
                GameOver();
            }
        }

        //ブロックの種類判別用
        int blockCounter = 0;
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                if (moveBlock[Y, X] == INBLOCK)
                {
                    blockPositon[blockCounter].y = Y;
                    blockPositon[blockCounter].x = X;
                    moveBlockObj[blockCounter] = Instantiate(block, blockPositon[blockCounter], Quaternion.identity);
                    ++blockCounter;
                }

            }
        }
    }

    void Move()
    {

        int[,] moveBlockTemp = new int[HEIGHTMAX, WIDTHMAX];            //移動先保存用
        int[,] blockTemp = new int[BLOCKARRAYSIZE, BLOCKARRAYSIZE]; //回転の状態保存用
        int[] tempPostionY = new int[BLOCKNUM];                       //高さ座標一次保存用
        int[] tempPostionX = new int[BLOCKNUM];                       //幅座標一次保存用

        int center = 0;                 //moveBlockの中心

        int endExitCount = 0;           //他ブロックに接触後再び移動できるかの判定用

        int blockTempCounter = 0;       //座標を確認するブロック更新用
        int centerCounter = 0;       //センターのブロック確認用

        bool xPlus = true;        //右に移動できるかの判定用
        bool xMinus = true;        //左に移動できるかの判定用　
        bool rightRoteCheck = true;//右に回転できるかの判定用
        bool LeftRoteCheck = true;//左に回転できるのかの判定用


        ++blockDownTimer; //時間経過

        //X移動確認
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN + 1; X < WIDTHMAX - 1; X++)
            {
                //一番右側の座標にいるかどうか
                if (moveBlock[Y, WIDTHMAX - 1] == INBLOCK)
                {
                    xPlus = false;
                }
                //一番左側の座標にいるかどうか
                if (moveBlock[Y, WIDTHMIN] == INBLOCK)
                {
                    xMinus = false;
                }
                //右側にブロックがあるかどうか
                if (moveBlock[Y, X] == INBLOCK && zangaiBlock[Y, X + 1] == INBLOCK)
                {
                    xPlus = false;
                }
                //左側にブロックがあるかどうか
                if (moveBlock[Y, X] == INBLOCK && zangaiBlock[Y, X - 1] == INBLOCK)
                {
                    xMinus = false;
                }
            }
        }

        //下移動
        if (endTimerCheck == false)
        {
            if (blockDownTimer % 10 == 0)
            {
                for (Y = HEIGHTMIN; Y < HEIGHTMAX - 1; Y++)
                {
                    for (X = WIDTHMIN; X < WIDTHMAX; X++)
                    {
                        moveBlock[Y, X] = moveBlock[Y + 1, X];

                        if (Y == HEIGHTMAX - 2)
                        {
                            moveBlock[Y + 1, X] = NOTBLOCK;
                        }
                    }
                }
            }
        }

        //右移動
        if (inputManager.RightMove())
        {
            if (xPlus == true)
            {
                for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
                {
                    for (X = WIDTHMIN; X < WIDTHMAX; X++)
                    {
                        if (moveBlock[Y, X] == INBLOCK)
                        {
                            moveBlockTemp[Y, X + 1] = moveBlock[Y, X];
                        }
                    }
                }
                for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
                {
                    for (X = WIDTHMIN; X < WIDTHMAX; X++)
                    {
                        moveBlock[Y, X] = moveBlockTemp[Y, X];
                    }
                }
            }

            //zangaiに当たった後移動可能かどうか
            for (Y = HEIGHTMIN + 1; Y < HEIGHTMAX; Y++)
            {
                for (X = WIDTHMIN; X < WIDTHMAX; X++)
                {
                    if ((moveBlock[Y, X] == INBLOCK && zangaiBlock[Y - 1, X] != INBLOCK))
                    {
                        ++endExitCount;
                    }
                }
            }

            //移動可能フラグ
            if (endExitCount != 0)
            {
                endTime = 0;
                endTimerCheck = false;
            }
        }

        //左移動
        if (inputManager.LeftMove())
        {
            if (xMinus == true)
            {
                for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
                {
                    for (X = WIDTHMIN; X < WIDTHMAX; X++)
                    {
                        if (moveBlock[Y, X] == INBLOCK)
                        {
                            moveBlockTemp[Y, X - 1] = moveBlock[Y, X];
                        }
                    }
                }
                for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
                {
                    for (X = WIDTHMIN; X < WIDTHMAX; X++)
                    {
                        moveBlock[Y, X] = moveBlockTemp[Y, X];
                    }
                }
            }

            //zangaiに当たった後移動可能かどうか
            for (Y = HEIGHTMIN + 1; Y < HEIGHTMAX; Y++)
            {
                for (X = WIDTHMIN; X < WIDTHMAX; X++)
                {
                    if ((moveBlock[Y, X] == INBLOCK && zangaiBlock[Y - 1, X] != INBLOCK))
                    {
                        ++endExitCount;
                    }
                }
            }

            //移動可能フラグ
            if (endExitCount != 0)
            {
                endTime = 0;
                endTimerCheck = false;
            }
        }

        //現在の座標取得
        for (Y = HEIGHTMAX - 1; Y > HEIGHTMIN; Y--)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                if (moveBlock[Y, X] == INBLOCK)
                {
                    tempPostionY[blockTempCounter] = Y;
                    tempPostionX[blockTempCounter] = X;
                    ++blockTempCounter;
                }
            }
        }

        //中心値の取得
        for (Y = HEIGHTMIN; Y < BLOCKARRAYSIZE; Y++)
        {
            for (X = WIDTHMIN; X < BLOCKARRAYSIZE; X++)
            {

                if (saveblock[Y, X] == INBLOCK)
                {
                    ++centerCounter;
                    if (Y == BLOCKCENTER && X == BLOCKCENTER)
                    {
                        center = centerCounter;
                    }
                }
            }
        }

        blockTempCounter = 0;

        //中心値との差を出す
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                if (moveBlock[Y, X] == INBLOCK)
                {
                    offsetY[blockTempCounter] = tempPostionY[center - 1] - tempPostionY[blockTempCounter];
                    offsetX[blockTempCounter] = tempPostionX[center - 1] - tempPostionX[blockTempCounter];

                    ++blockTempCounter;
                }
            }
        }

        blockTempCounter = 0;

        //回転可能かどうかの判定
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                if (moveBlock[Y, X] == INBLOCK)
                {
                    if (X + (offsetY[blockTempCounter] * -1) >= WIDTHMAX)
                    {
                        rightRoteCheck = false;
                        LeftRoteCheck = false;
                    }
                    if (X + (offsetY[blockTempCounter] * -1) < WIDTHMIN)
                    {
                        rightRoteCheck = false;
                        LeftRoteCheck = false;
                    }
                    ++blockTempCounter;
                }
            }
        }

        //右回転
        if (inputManager.RightRote())
        {
            if (rightRoteCheck == true)
            {
                //回転
                for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
                {
                    for (X = WIDTHMIN; X < WIDTHMAX; X++)
                    {
                        moveBlock[Y, X] = NOTBLOCK;
                    }
                }
                for (Y = HEIGHTMIN; Y < BLOCKARRAYSIZE; Y++)
                {
                    for (X = WIDTHMIN; X < BLOCKARRAYSIZE; X++)
                    {
                        blockTemp[X, BLOCKNUM - Y] = saveblock[Y, X];
                    }
                }

                blockTempCounter = 0;

                //座標の修正
                for (Y = 0; Y < BLOCKARRAYSIZE; Y++)
                {
                    for (X = 0; X < BLOCKARRAYSIZE; X++)
                    {
                        saveblock[Y, X] = blockTemp[Y, X];

                        if (blockTemp[Y, X] == INBLOCK)
                        {
                            if (offsetY[blockTempCounter] >= 1)
                            {
                                offsetY[blockTempCounter] *= -1;
                            }
                            else
                            {
                                offsetY[blockTempCounter] *= -1;
                            }

                            moveBlock[tempPostionY[center - 1] + offsetX[blockTempCounter], tempPostionX[center - 1] + offsetY[blockTempCounter]] = blockTemp[Y, X];

                            ++blockTempCounter;
                        }
                    }
                }
            }
        }

        //左回転
        if (inputManager.LeftRote())
        {
            if (LeftRoteCheck == true)
            {
                //回転
                for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
                {
                    for (X = WIDTHMIN; X < WIDTHMAX; X++)
                    {
                        moveBlock[Y, X] = NOTBLOCK;
                    }
                }
                for (Y = HEIGHTMIN; Y < BLOCKARRAYSIZE; Y++)
                {
                    for (X = WIDTHMIN; X < BLOCKARRAYSIZE; X++)
                    {
                        blockTemp[BLOCKNUM - X, Y] = saveblock[Y, X];
                    }
                }

                blockTempCounter = 0;

                //座標の修正
                for (Y = 0; Y < BLOCKARRAYSIZE; Y++)
                {
                    for (X = 0; X < BLOCKARRAYSIZE; X++)
                    {
                        saveblock[Y, X] = blockTemp[Y, X];
                        if (saveblock[Y, X] == INBLOCK)
                        {
                            if (offsetY[blockTempCounter] >= 1)
                            {

                                offsetY[blockTempCounter] *= -1;
                            }
                            else
                            {
                                offsetY[blockTempCounter] *= -1;
                            }
                            moveBlock[tempPostionY[center - 1] + offsetX[blockTempCounter], tempPostionX[center - 1] + offsetY[blockTempCounter]] = blockTemp[Y, X];
                            ++blockTempCounter;
                        }
                    }
                }
            }
        }

        //当たり判定
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                if ((moveBlock[Y, X] == INBLOCK && Y == HEIGHTMIN) || (moveBlock[Y, X] == INBLOCK && zangaiBlock[Y - 1, X] == INBLOCK))
                {
                    endTimerCheck = true;
                }
            }
        }

        if (endTimerCheck == true)
        {
            ++endTime;

            if (endTime > 60)
            {
                endTime = 0;
                endTimerCheck = false;
                ZangaiBlock();
            }
        }
    }

    //ブロック消去判定
    void ZangaiBlock()
    {
        int blockCount = 0; //そろっているブロックカウント用

        bool[] deletePostion = new bool[HEIGHTMAX]; //消去したブロックの高さを保存用

        //deletePostion初期化
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            deletePostion[Y] = false;
        }

        //zangaiBlockにmoveBlockのデータを入れる
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                zangaiBlock[Y, X] += moveBlock[Y, X];
            }
        }
        //moveBlockを消去
        for (int i = 0; i < BLOCKNUM; i++)
        {
            Destroy(moveBlockObj[i]);
        }

        for (int Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            deletePostion[Y] = false;
        }

        //そろっているか確認
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            blockCount = 0;
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                if (zangaiBlock[Y, X] == INBLOCK)
                {
                    ++blockCount;
                }
                if (blockCount == WIDTHMAX)
                {
                    deletePostion[Y] = true;
                }
                else
                {
                    deletePostion[Y] = false;
                }
            }
        }

        //ブロックを消去
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            if (deletePostion[Y] == true)
            {
                for (X = WIDTHMIN; X < WIDTHMAX; X++)
                {
                    zangaiBlock[Y, X] = NOTBLOCK;
                }
            }
        }

        //空いた行を詰める
        for (Y = HEIGHTMAX - 1; Y >= HEIGHTMIN; Y--)
        {
            if (deletePostion[Y] == true)
            {
                for (int YY = Y; YY < HEIGHTMAX; YY++)
                {
                    for (X = WIDTHMIN; X < WIDTHMAX; X++)
                    {
                        zangaiBlock[YY, X] = zangaiBlock[YY + 1, X];
                    }
                }

            }
        }

        //zangai更新
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                //ブロック生成
                if (zangaiBlock[Y, X] == INBLOCK && zangaiBlockObj[Y, X] == null)
                {
                    zangaiPositon.y = Y;
                    zangaiPositon.x = X;
                    zangaiBlockObj[Y, X] = Instantiate(block, zangaiPositon, Quaternion.identity);
                }

                //ブロック消去
                if (zangaiBlock[Y, X] == NOTBLOCK && zangaiBlockObj[Y, X] != null)
                {
                    Destroy(zangaiBlockObj[Y, X]);
                }
            }
        }

        //次のブロック生成
        BlockSelect();
    }

    //ゲームオーバー処理
    void GameOver()
    {
        for (Y = HEIGHTMIN; Y < HEIGHTMAX; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                Destroy(zangaiBlockObj[Y, X]);
            }
        }
        BlockSelect();
    }

    //描画
    void Draw()
    {
        int blockCounter = 0;
        for (Y = HEIGHTMIN; Y < HEIGHTMAX - 1; Y++)
        {
            for (X = WIDTHMIN; X < WIDTHMAX; X++)
            {
                //ブロック座標更新
                if (moveBlock[Y, X] == INBLOCK)
                {
                    blockPositon[blockCounter] = moveBlockObj[blockCounter].transform.position;
                    blockPositon[blockCounter].y = Y;
                    blockPositon[blockCounter].x = X;
                    moveBlockObj[blockCounter].transform.position = blockPositon[blockCounter];

                    ++blockCounter;
                    if (blockCounter >= 4)
                    {
                        blockCounter = 0;
                    }
                }

            }
        }
    }
}