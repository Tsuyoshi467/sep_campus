using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockController : MonoBehaviour
{
    InputManager inputManager;

    private GameObject[] floor;
    private GameObject[] iBlock;
    private GameObject[] jBlock;
    private GameObject[] lBlock;
    private GameObject[] oBlock;
    private GameObject[] sBlock;
    private GameObject[] tBlock;
    private GameObject[] zBlock;

    [SerializeField]
    private GameObject[] children;

    const int HEIGHT = 20;
    const int WIDTH = 10;
    const float RIGHTMAX = 4.5f;
    const float LEFTMAX = -4.5f;
    int count = 0;
    int childrenSize = 0;  //子オブジェクトの数
    int hitBlocksSize = 0;  //当たり判定のあるブロック数
    GameObject checkBlock = null;
    float Y = HEIGHT;//縦座標
    float X = 0;//横座標
    bool moveYCheck = true;

    // Use this for initialization
   
    void Start()
    {
        inputManager = GetComponent<InputManager>();       
        this.tag = "Untagged";
        childrenSize = this.transform.childCount;
        floor = GameObject.FindGameObjectsWithTag("Floor");
        iBlock = GameObject.FindGameObjectsWithTag("IBlock");
        jBlock = GameObject.FindGameObjectsWithTag("JBlock");
        lBlock = GameObject.FindGameObjectsWithTag("LBlock");
        oBlock = GameObject.FindGameObjectsWithTag("OBlock");
        sBlock = GameObject.FindGameObjectsWithTag("SBlock");
        tBlock = GameObject.FindGameObjectsWithTag("TBlock");
        zBlock = GameObject.FindGameObjectsWithTag("ZBlock");
        for (int i = 0; i < childrenSize; i++)
        {
            children[i] = transform.GetChild(i).gameObject;
            children[i].tag = "Untagged";
        }
        checkBlock = children[0];
        for (int i = 1; i < childrenSize; i++)
        {
            if (children[i].transform.position.y < checkBlock.transform.position.y)
            {
                checkBlock = children[i];
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        Move();
        Rotation();
        ++count;
    }


    //移動
    void Move()
    {
        Vector3 pos = transform.position;

        if (inputManager.RightMove() == true && X < RIGHTMAX)
        {
            ++X;
        }
        if (inputManager.LeftMove() == true && X > LEFTMAX)
        {
            --X;
        }
        pos.x = X;
        if (count % 60 == 0 || inputManager.DownMove() && moveYCheck == true)
        {
            --Y;
        }

        HitCheck(floor, floor.Length);
        HitCheck(iBlock, iBlock.Length);
        HitCheck(jBlock, jBlock.Length);
        HitCheck(lBlock, lBlock.Length);
        HitCheck(oBlock, oBlock.Length);
        HitCheck(sBlock, sBlock.Length);
        HitCheck(tBlock, tBlock.Length);
        HitCheck(zBlock, zBlock.Length);

        if (moveYCheck == false)
        {
            Destroy(this);
        }
        pos.y = Y;
        transform.position = pos;
    }

    //回転
    void Rotation()
    {
        if (inputManager.RightRote() == true)
        {
            transform.Rotate(new Vector3(0, 0, 90));
        }
        if (inputManager.LeftRote() == true)
        {
            transform.Rotate(new Vector3(0, 0, -90));
        }
        for (int i = 0; i < childrenSize; i++)
        {
            if (children[i].transform.position.y < checkBlock.transform.position.y)
            {
                checkBlock = children[i];
            }
        }
    }
    void HitCheck(GameObject []checkObject, int checkCount)
    {
        for (int i = 0; i < checkCount; i++)
        {
            if(checkBlock.transform.position.y - 1<= checkObject[i].transform.position.y )
            {
                switch (this.name)
                {
                    case "I(Clone)":
                        this.tag = "IBlock";
                        for(int j = 0; j < childrenSize; j++)
                        {
                            children[j].tag = "IBlock";
                        }
                        break;
                    case "J(Clone)":
                        this.tag = "JBlock";
                        for (int j = 0; j < childrenSize; j++)
                        {
                            children[j].tag = "IBlock";
                        }
                        break;
                    case "L(Clone)":
                        this.tag = "LBlock";
                        for (int j = 0; j < childrenSize; j++)
                        {
                            children[j].tag = "IBlock";
                        }
                        break;
                    case "O(Clone)":
                        this.tag = "OBlock";
                        for (int j = 0; j < childrenSize; j++)
                        {
                            children[j].tag = "IBlock";
                        }
                        break;
                    case "S(Clone)":
                        this.tag = "SBlock";
                        for (int j = 0; j < childrenSize; j++)
                        {
                            children[j].tag = "IBlock";
                        }
                        break;
                    case "T(Clone)":
                        this.tag = "TBlock";
                        for (int j = 0; j < childrenSize; j++)
                        {
                            children[j].tag = "IBlock";
                        }
                        break;
                    case "Z(Clone)":
                        this.tag = "ZBlock";
                        for (int j = 0; j < childrenSize; j++)
                        {
                            children[j].tag = "IBlock";
                        }
                        break;
                }
                moveYCheck = false;
            }
        }
    }
}

