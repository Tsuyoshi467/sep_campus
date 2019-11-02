using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    [SerializeField]
    private GameObject[] Blocks;
    [SerializeField]
    private GameObject SpawnPoint;
    Vector3 spawn;
    int size = 0;
    // Start is called before the first frame update

    void Start()
    {
        spawn = new Vector3(0,20,0) ;
        size = Blocks.Length;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.O))
        {
            BlockSelect();
        }
    }

    void BlockSelect()
    {
        int select = Random.Range(0,size);
        GameObject obj = Instantiate(Blocks[select], spawn,SpawnPoint.transform.rotation);   
    }
}
