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

        string strfilename;
        string filetext;
        int flag_it = 0;
        string aux;
        string speed;
        public Form1()
        {
            InitializeComponent();
            timer1.Interval = 100;
            timer1.Tick += Update_speed;
            timer1.Start();

            
        }
        //string valor;
       
    private void TextBox1_TextChanged(object sender, EventArgs e)
        {


        }

        private void Button1_Click(object sender, EventArgs e)
        {
            
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            
           
           if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                flag_it = 1;
                
                strfilename = openFileDialog1.FileName;
                aux = strfilename;
              
          
                //string aux = strfilename;
               
           }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Button2_Click(object sender, EventArgs e)
        {
            if (flag_it == 1)
            {
                strfilename = aux;
                filetext = File.ReadAllText(strfilename);
                richTextBox1.Text = filetext;
            }
        }

        private void Update_speed(object sender, EventArgs e)
        {
            try
            {
                if (flag_it == 1)
                {
                    string source = @"C:\Users\Maria Eduarda\Desktop\Softstarter com mario kart\Frappe Snowland Training\BizHawk-1.12.2\teste.txt";
                    string destination = @"C:\Users\Maria Eduarda\Desktop\Softstarter com mario kart\Frappe Snowland Training\BizHawk-1.12.2\teste1.txt";
                    speed = File.ReadAllText(source);
                    File.WriteAllText(destination, speed);
                    strfilename = aux;
                    filetext = File.ReadAllText(destination);
                    richTextBox1.Text = filetext;
                    serialPort1.Open();
                    serialPort1.Write(filetext);
                    serialPort1.Close();

                }
            }
            catch
            {
                
            }
           
        }
    }
}

