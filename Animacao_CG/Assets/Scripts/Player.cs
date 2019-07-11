using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Player : MonoBehaviour
{
    private int count;
    public Text countText;
    public Text winText;
    public AudioSource som;

    private Animator anim;
    //public Rigidbody rb;
    private CharacterController controller;
    public float speed = 6.0f;
    public float turnSpeed = 60.0f;
    public float gravity = 20.0f;
    private Vector3 moveDirection;

    // Start is called before the first frame update
    void Start()
    {
        som = GetComponent<AudioSource>();
        this.count = 0;
        anim = gameObject.GetComponentInChildren<Animator>();
        //rb = GetComponent<Rigidbody>();
        controller = GetComponent<CharacterController>();
        moveDirection = Vector3.zero;
        this.setCountText();
        this.winText.text = "";
    }

    void FixedUpdate()
    {
        if(Input.GetAxis("Vertical") != 0 || Input.GetAxis("Horizontal") != 0)
        {
            anim.SetInteger("AnimParam", 1);
            if(Input.GetAxis("Jump") != 0)
            {
                anim.SetInteger("AnimParam", 2);
            }
        }
        else
        {
            anim.SetInteger("AnimParam", 0);
            if (Input.GetAxis("Jump") != 0)
            {
                anim.SetInteger("AnimParam", 2);
            }
        }

        if(controller.isGrounded)
        {
            moveDirection = transform.forward * Input.GetAxis("Vertical") * speed;
        }

        float turn = Input.GetAxis("Horizontal");
        transform.Rotate(0, turn * turnSpeed * Time.deltaTime, 0);
        controller.Move(moveDirection * Time.deltaTime);
        moveDirection.y -= gravity * Time.deltaTime;

        //float moveHor = Input.GetAxis("Horizontal");
        //float moveVer = Input.GetAxis("Vertical");
        //float inputJump = Input.GetAxis("Jump");
        //Vector3 movement = new Vector3(moveHor, 1.5f * inputJump, moveVer);
        //rb.AddForce(movement * speed);
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Pick Up"))
        {
            som.Play();
            other.gameObject.SetActive(false);
            count++;
            this.setCountText();
            if (count == 8)
            {
                this.winText.text = "You win!";
            }
        }
    }

    void setCountText()
    {
        countText.text = "INE5420 - Computação Gráfica - 2019 / 1 - Trabalho III " +
                         "- Animação com GameEngine\n Pontuação: " + count;
    }
}

