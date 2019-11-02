using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckManager : MonoBehaviour
{
    const int HEIGHT = 20;
    const int WIDTH = 10;
    bool[][] deleteCheck = null;
    int deleteCount = 0;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void Delete()
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if(deleteCheck[i][j] == true)
                {
                    ++deleteCount;
                    if(deleteCount == WIDTH)
                    {

                    }
                }
            }
        }
    }
}
