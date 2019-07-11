using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    private int count;
    public Text countText;
    public Text winText;
    public AudioSource som;

    public Rigidbody rb;
    public float speed;
   
    void Start()
    {
        som = GetComponent<AudioSource>();
        this.count = 0;
        rb = GetComponent<Rigidbody>();
        this.setCountText();
        this.winText.text = "";
    }

    void FixedUpdate()
    {
        float moveHor = Input.GetAxis("Horizontal");
        float moveVer = Input.GetAxis("Vertical");
        float inputJump = Input.GetAxis("Jump");
        Vector3 movement = new Vector3(moveHor, 1.5f * inputJump, moveVer);
        rb.AddForce(movement * speed);
    }

    void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("Pick Up"))
        {
            som.Play();
            other.gameObject.SetActive(false);
            count++;
            this.setCountText();
            if(count == 8)
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
