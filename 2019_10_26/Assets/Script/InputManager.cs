using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputManager : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
    }
    public bool RightMove()
    {
        if (Input.GetKeyDown(KeyCode.RightArrow) || Input.GetKeyDown(KeyCode.D))
        {
            return true;
        }
        return false;
    }
    public bool LeftMove()
    {
        if (Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyDown(KeyCode.A))
        {
            return true;
        }
        return false;
    }
    public bool DownMove()
    {
        if (Input.GetKey(KeyCode.DownArrow) || Input.GetKeyDown(KeyCode.S))
        {
            return true;
        }
        return false;
    }
    public bool RightRote()
    {
        if (Input.GetKeyDown(KeyCode.E))
        {
            return true;
        }
        return false;
    }
    public bool LeftRote()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            return true;
        }
        return false;
    }
}
