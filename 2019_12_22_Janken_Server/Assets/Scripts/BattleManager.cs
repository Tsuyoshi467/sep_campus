using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Networking;

public class BattleManager : MonoBehaviour
{
    [SerializeField]
    GameObject []sceneObj = default;

    [SerializeField]
    Text judgText = default;

    [SerializeField]
    private Sprite []enemySprite = default;

    [SerializeField]
    private GameObject enemyHandObj = default;

    public class EnemyHand
    {
        public int computer;
    }

    public EnemyHand enemyHand = default;

    enum Hand
    {
        goo,
        choki,
        par,
    }

    enum Scene
    {
        Fast,
        Battle,
        Final,
        Aiko,
    }

    bool victoryJudg = false;
    int nowScene = (int)Scene.Fast;
    float elapsedTime = 0f;
    const float drwaTime = 1.0f;
    // Start is called before the first frame update
    void Start()
    {
        elapsedTime = drwaTime;
    }

    // Update is called once per frame
    void Update()
    {
        switch (nowScene)
        {
            case (int)Scene.Fast:
                SceneDraw();
                elapsedTime -= Time.deltaTime;
                if (elapsedTime <= 0.0f)
                {
                    elapsedTime = drwaTime;
                    nowScene = (int)Scene.Battle;
                }
                break;
            case (int)Scene.Battle:
                StartCoroutine(GetEnemyHand());
                break;
            case (int)Scene.Final:
                SceneDraw();
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
                SceneDraw(); elapsedTime -= Time.deltaTime;
                if (elapsedTime <= 0.0f)
                {
                    elapsedTime = drwaTime;
                    nowScene = (int)Scene.Battle;
                }
                break;
            default:
                Debug.Log("TrunError");
                break;
        }
    }

    private IEnumerator GetEnemyHand()
    {
        UnityWebRequest request = UnityWebRequest.Get("http://ec2-18-176-58-134.ap-northeast-1.compute.amazonaws.com/janken.php?you=0");
        yield return request.SendWebRequest();

        if (request.isHttpError || request.isNetworkError)
        {
            Debug.Log(request.error);
        }
        else
        {
            enemyHand = JsonUtility.FromJson<EnemyHand>(request.downloadHandler.text);
            SceneDraw();
            SpriteRenderer sprite = enemyHandObj.GetComponent<SpriteRenderer>();
            sprite.sprite = enemySprite[enemyHand.computer];
        }
    }

    public void GooButton()
    {
        switch (enemyHand.computer)
        {
            case (int)Hand.goo:
                nowScene = (int)Scene.Aiko;
                break;
            case (int)Hand.choki:
                victoryJudg = true;
                nowScene = (int)Scene.Final;
                break;
            case (int)Hand.par:
                victoryJudg = false;
                nowScene = (int)Scene.Final;
                break;
            default:
                Debug.Log("GooHandError");
                break;
        }
    }

    public void ChokiButton()
    {
        switch (enemyHand.computer)
        {
            case (int)Hand.goo:
                victoryJudg = false;
                nowScene = (int)Scene.Final;
                break;
            case (int)Hand.choki:
                nowScene = (int)Scene.Aiko;
                break;
            case (int)Hand.par:
                victoryJudg = true;
                nowScene = (int)Scene.Final;
                break;
            default:
                Debug.Log("ChokiHandError");
                break;
        }
    }

    public void ParButton()
    {
        switch (enemyHand.computer)
        {
            case (int)Hand.goo:
                victoryJudg = true;
                nowScene = (int)Scene.Final;
                break;
            case (int)Hand.choki:
                victoryJudg = false;
                nowScene = (int)Scene.Final;
                break;
            case (int)Hand.par:
                nowScene = (int)Scene.Aiko;
                break;
            default:
                Debug.Log("ParHandError");
                break;
        }
    }

    public void ReturnButton()
    {
        nowScene = (int)Scene.Fast;
    }

    void SceneDraw()
    {
        for (int i = 0; i < sceneObj.Length; i++)
        {
            sceneObj[i].SetActive(false);
        }
        sceneObj[nowScene].SetActive(true);
    }
}
