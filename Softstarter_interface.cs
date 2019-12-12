using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {

        
        public Form1()
        {

            InitializeComponent();
            label3.Text = "5";
            label4.Text = "5";


        }
       
       
    private void TextBox1_TextChanged(object sender, EventArgs e)
        {


        }

        private void Button1_Click(object sender, EventArgs e)
        {

            serialPort1.Open();
            serialPort1.Write("ts"); //tempo subida
            if(trackBar1.Value <10)
            {
                serialPort1.Write("0");
            }
            serialPort1.Write(label3.Text);
            serialPort1.Close();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Button2_Click(object sender, EventArgs e)
        {
            serialPort1.Open();
            serialPort1.Write("td"); //tempo descida
            if (trackBar2.Value < 10)
            {
                serialPort1.Write("0");
            }
            serialPort1.Write(label4.Text);
            serialPort1.Close();
        }

        private void TrackBar1_Scroll(object sender, EventArgs e)
        {
            label3.Text = trackBar1.Value.ToString();
        }

        private void TrackBar2_Scroll(object sender, EventArgs e)
        {
            label4.Text = trackBar2.Value.ToString();
        }

        private void Button5_Click(object sender, EventArgs e)
        {
          

        }

        private void Button3_Click(object sender, EventArgs e) //iniciar
        {
      
            serialPort1.Open();
            serialPort1.Write("in"); //displaychange
            serialPort1.Write("03");
            serialPort1.Close();
        }

        private void Button4_Click(object sender, EventArgs e)
        {
            serialPort1.Open();
            serialPort1.Write("ou"); //displaychange
            serialPort1.Write("04");
            serialPort1.Close();
        }

        private void Button5_Click_1(object sender, EventArgs e)
        {
            serialPort1.Open();
            serialPort1.Write("re"); //displaychange
            serialPort1.Write("00");
            serialPort1.Close();
        }

        private void Button6_Click(object sender, EventArgs e)
        {
            serialPort1.Open();
            serialPort1.Write("dc"); //displaychange
            serialPort1.Write("00");
            serialPort1.Close();
        }

        private void Button7_Click(object sender, EventArgs e)
        {
            serialPort1.Open();
            serialPort1.Write("d1"); //displaychange
            serialPort1.Write("00");
            serialPort1.Close();
        }
    }
}

