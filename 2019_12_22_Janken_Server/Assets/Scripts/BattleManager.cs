using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Networking;

public class BattleManager : MonoBehaviour
{
    [SerializeField]
    GameObject []sceneObj = default;//表示するオブジェクト

    [SerializeField]
    Text judgText = default;//表示するテキスト

    [SerializeField]
    private Sprite []handSprite = default;//表示するエネミーの手の画像

    [SerializeField]
    private GameObject plaerHandObj = default;//プレイヤーの手のオブジェクト
    [SerializeField]
    private GameObject enemyHandObj = default;//エネミーの手のオブジェクト

    [SerializeField]
    GameObject retryButton = default;

    public class AcquiredData
    {
        public int computer;//読み取るエネミーの手
        public string message;
    }

    public AcquiredData acquiredData = default;//エネミークラス

    enum Hand
    {
        goo,　//0:グー
        choki,//1:チョキ
        par,　//2:パー
    }

    enum Scene
    {
        Fast,  //じゃんけんの文字表示
        Battle,//じゃんけんをする
        Final, //結果
    }

    bool victoryJudg = false;//勝ったかどうか
    int nowScene = (int)Scene.Fast;
    float elapsedTime = 0f;//経過時間
    const float drwaTime = 1.0f;//表示するまでの時間

    string myHand = "0";
    // Start is called before the first frame update
    void Start()
    {
        elapsedTime = drwaTime;//表示する時間をセット
    }

    // Update is called once per frame
    void Update()
    {
        //シーンで処理を変える
        switch (nowScene)
        {
            case (int)Scene.Fast:
                SceneDraw();
                elapsedTime -= Time.deltaTime;//時間を減らす
                //指定した時間以下の時処理
                if (elapsedTime <= 0.0f)
                {
                    elapsedTime = drwaTime;//表示する時間をセット
                    nowScene = (int)Scene.Battle;//シーン番号切り替え
                }
                break;
            case (int)Scene.Battle:
                SceneDraw();
                break;
            case (int)Scene.Final:
                SceneDraw();
                SpriteRenderer enemySprite = enemyHandObj.GetComponent<SpriteRenderer>();//エネミーの画像を取得
                SpriteRenderer playerSprite = plaerHandObj.GetComponent<SpriteRenderer>();//エネミーの画像を取得
                
                enemySprite.sprite = handSprite[acquiredData.computer];

                switch (myHand)
                {
                    case "0":
                        playerSprite.sprite = handSprite[(int)Hand.goo];
                        break;
                    case "1":
                        playerSprite.sprite = handSprite[(int)Hand.choki];
                        break;
                    case "2":
                        playerSprite.sprite = handSprite[(int)Hand.par];
                        break;
                }

                switch (acquiredData.message)
                {
                    case "win":
                        judgText.text = "player Win";
                        break;
                    case "loss":
                        judgText.text = "player Lose";
                        break;
                    case "draw":
                        retryButton.SetActive(false);
                        judgText.text = "あいこで!";
                        elapsedTime -= Time.deltaTime;//時間を減らす
                                                      //指定した時間以下の時処理
                        if (elapsedTime <= 0.0f)
                        {
                            elapsedTime = drwaTime;//表示する時間をセット
                            nowScene = (int)Scene.Battle;//シーン番号切り替え
                        }
                        break;
                    default:
                        Debug.Log("HandError");
                        break;
                }
                break;
            default:
                Debug.Log("TrunError");
                break;
        }
    }

    private IEnumerator GetEnemyHand(string url, string JsonString)
    {
        var postRequest = UnityWebRequest.Get(string.Format("{0}?you={1}", url, JsonString));
        
        //json(string)をbyte[]に変換
        byte[] bodyRaw = System.Text.Encoding.UTF8.GetBytes(JsonString);

        //jsonを設定
        postRequest.uploadHandler = (UploadHandler)new UploadHandlerRaw(bodyRaw);
        postRequest.downloadHandler = (DownloadHandler)new DownloadHandlerBuffer();

        //ヘッダーにタイプを設定
        postRequest.SetRequestHeader("Content-Type", "application/json");
        yield return postRequest.SendWebRequest();

        UnityWebRequest  request = UnityWebRequest.Get(postRequest.url);//URLの内容を取得
        yield return request.SendWebRequest();

        //エラー判定
        if (request.isHttpError || request.isNetworkError)
        {
            Debug.Log(request.error);
        }
        else
        {
            acquiredData = JsonUtility.FromJson<AcquiredData>(request.downloadHandler.text);//エネミークラスにキャスト
            nowScene = (int)Scene.Final;
        }
    }

    //グーボタンが押されたとき
    public void GooButton()
    {
        myHand = "0";

        StartCoroutine(GetEnemyHand("http://ec2-18-176-58-134.ap-northeast-1.compute.amazonaws.com/janken.php", myHand));
    }

    //チョキボタンが押されたとき
    public void ChokiButton()
    {
        myHand = "1";

        StartCoroutine(GetEnemyHand("http://ec2-18-176-58-134.ap-northeast-1.compute.amazonaws.com/janken.php", myHand));
    }

    //パーボタンが押されたとき
    public void ParButton()
    {
        myHand = "2";

        StartCoroutine(GetEnemyHand("http://ec2-18-176-58-134.ap-northeast-1.compute.amazonaws.com/janken.php", myHand));
    }

    public void ReturnButton()
    {
        nowScene = (int)Scene.Fast;
    }

    void SceneDraw()
    {
        //すべて非表示
        for (int i = 0; i < sceneObj.Length; i++)
        {
            sceneObj[i].SetActive(false);
        }
        //シーンに応じて表示
        sceneObj[nowScene].SetActive(true);
    }
}
