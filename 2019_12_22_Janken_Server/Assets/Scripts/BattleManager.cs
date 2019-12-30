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
    private Sprite []enemySprite = default;//表示するエネミーの手の画像

    [SerializeField]
    private GameObject enemyHandObj = default;//エネミーの手のオブジェクト


    public class EnemyHand
    {
        public int computer;//読み取るエネミーの手
        public string message;
    }

    public EnemyHand enemyHand = default;//エネミークラス

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
        Aiko,  //あいこ
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
                //勝敗に応じてテキストを変更
                if (victoryJudg == true)
                {
                    judgText.text = "player Win";
                }
                else
                {
                    judgText.text = "player Lose";
                }
                break;
            case (int)Scene.Aiko:
                SceneDraw();
                elapsedTime -= Time.deltaTime;//時間を減らす
                //指定した時間以下の時処理
                if (elapsedTime <= 0.0f)
                {
                    elapsedTime = drwaTime;//表示する時間をセット
                    nowScene = (int)Scene.Battle;//シーン番号切り替え
                }
                break;
            default:
                Debug.Log("TrunError");
                break;
        }
    }

    private IEnumerator GetEnemyHand(string url, string JsonString)
    {

        var postRequest = new UnityWebRequest(url, "POST");
        //json(string)をbyte[]に変換
        byte[] bodyRaw = System.Text.Encoding.UTF8.GetBytes(JsonString);

        //jsonを設定
        postRequest.uploadHandler = (UploadHandler)new UploadHandlerRaw(bodyRaw);
        postRequest.downloadHandler = (DownloadHandler)new DownloadHandlerBuffer();

        //ヘッダーにタイプを設定
        postRequest.SetRequestHeader("Content-Type", "application/json");
        yield return postRequest.SendWebRequest();

        UnityWebRequest  request = UnityWebRequest.Get(url);//URLの内容を取得
        yield return request.SendWebRequest();

        //エラー判定
        if (request.isHttpError || request.isNetworkError)
        {
            Debug.Log(request.error);
        }
        else
        {
            enemyHand = JsonUtility.FromJson<EnemyHand>(request.downloadHandler.text);//エネミークラスにキャスト

            SpriteRenderer sprite = enemyHandObj.GetComponent<SpriteRenderer>();//エネミーの画像を取得
            handCheck();
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

    void handCheck()
    {
        switch (enemyHand.message)
        {
            case "win":
                victoryJudg = true;//勝利判定
                nowScene = (int)Scene.Final;
                break;
            case "loss":
                victoryJudg = false;//敗北判定
                nowScene = (int)Scene.Final;
                break;
            case "draw":
                nowScene = (int)Scene.Aiko;//引き分け判定
                break;
            default:
                Debug.Log("HandError");
                break;
        }
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
