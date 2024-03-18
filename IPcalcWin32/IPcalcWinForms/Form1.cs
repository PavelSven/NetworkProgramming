using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;

namespace IPcalcWinForms
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            //maskedTextBox1.Mask = ###.###.###.###;
            maskedTextBox1.ValidatingType = typeof(System.Net.IPAddress);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            IPAddress address;
            string strAddress = maskedTextBox1.Text.Replace(',', '.').Replace(' ', '0');
            bool parse = IPAddress.TryParse(strAddress, out address);
            MessageBox.Show(address.ToString());
        }
    }
}
