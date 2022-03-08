using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MondemaComponents
{
    public partial class frmNumericKeypad : Form
    {
        private string m_sFormat;
        private double? m_dMin;
        private double? m_dMax;
        private double m_dValue = 0;

        public frmNumericKeypad(string sTitle, double dCurrentValue) : this(sTitle, dCurrentValue,null,null)
        {
        }

        public frmNumericKeypad(string sTitle, double dCurrentValue, double dMin, double dMax) : this(sTitle, dCurrentValue, dMin, dMax,"F3")
        {
        }

        public frmNumericKeypad(string sTitle, double dCurrentValue, double dMin, double dMax, string sFormat) : this(sTitle, dCurrentValue, (double?)dMin, (double?)dMax, sFormat)
        {

        }

        public frmNumericKeypad(string sTitle, double dCurrentValue, double? dMin = null, double? dMax = null, string sFormat = "F3")
        {
            InitializeComponent();
            m_sFormat = sFormat;
            m_dMin = dMin;
            m_dMax = dMax;

            this.Text = sTitle;
            lblNumber.Text = "0";
            lblCurrent.Text = dCurrentValue.ToString(m_sFormat);
            if (dMin.HasValue) lblMin.Text = dMin.Value.ToString(m_sFormat);
            grbMin.Visible = dMin.HasValue;
            if (dMax.HasValue) lblMax.Text = dMax.Value.ToString(m_sFormat);
            grbMax.Visible = dMax.HasValue;
        }

        private void btnNum_Click(object sender, EventArgs e)
        {
            char sNum = ((Button)sender).Text[0];
            string sNewValue = lblNumber.Text + sNum;

            if ((lblNumber.Text == "0") && (sNum >= '1') && (sNum <= '9')) sNewValue = sNum.ToString();
            if ((lblNumber.Text == "0") && (sNum == '0')) sNewValue = sNum.ToString();
            if (double.TryParse(sNewValue, out m_dValue))
            {
                lblNumber.Text = sNewValue;
            }
        }

        private void btnDot_Click(object sender, EventArgs e)
        {
            if (lblNumber.Text.IndexOf('.')==-1)
                lblNumber.Text = lblNumber.Text + ".";
        }

        private void btnSign_Click(object sender, EventArgs e)
        {
            m_dValue = -m_dValue;
            if (lblNumber.Text.IndexOf('-')==-1)
                lblNumber.Text = "-" + lblNumber.Text;
            else
                lblNumber.Text = lblNumber.Text.Substring(1);
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            lblNumber.Text = "0";
            m_dValue = 0;
        }

        private void btnQuit_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            if (m_dMin.HasValue)
            {
                if (m_dValue < m_dMin.Value)
                {
                    this.DialogResult = DialogResult.None;
                    MessageBox.Show(this, "Valeur en dehors des limites", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
            if (m_dMax.HasValue)
            {
                if (m_dValue > m_dMax.Value)
                {
                    this.DialogResult = DialogResult.None;
                    MessageBox.Show(this, "Valeur en dehors des limites", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
            this.DialogResult = DialogResult.OK;
        }

        private void btnErase_Click(object sender, EventArgs e)
        {
            string sNewValue = lblNumber.Text;

            if (sNewValue.Length > 0) sNewValue = sNewValue.Substring(0, sNewValue.Length - 1);
            if ((sNewValue == "-") || (sNewValue.Length == 0)) sNewValue = "0";
            if (double.TryParse(sNewValue, out m_dValue))
            {
                lblNumber.Text = sNewValue;
            }
        }

        public double Value
        {
            get
            {
                return m_dValue;
            }
        }

        private void frmNumericKeypad_KeyPress(object sender, KeyPressEventArgs e)
        {
            System.Diagnostics.Debug.Print("6");
            e.Handled = true;
            switch (e.KeyChar)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    Button btn = new Button();
                    btn.Text = e.KeyChar.ToString();
                    btnNum_Click(btn, EventArgs.Empty);
                    break;
                case '.':
                    btnDot_Click(null, EventArgs.Empty);
                    break;
                case '-':
                    btnSign_Click(null, EventArgs.Empty);
                    break;
                case (char)27:
                    btnQuit_Click(null, EventArgs.Empty);
                    break;
                case (char)8:
                    btnErase_Click(null, EventArgs.Empty);
                    break;
                default:
                    e.Handled = false;
                    break;
            }
        }

        private void frmNumericKeypad_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Enter:
                    btnOk_Click(null, EventArgs.Empty);
                    e.Handled = true;
                    break;
                case Keys.Delete:
                    btnClear_Click(null, EventArgs.Empty);
                    e.Handled = true;
                    break;
            }
        }

        private void btn_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                e.IsInputKey = true;
        }
    }
}
