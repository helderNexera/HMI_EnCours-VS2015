using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.ComponentModel;

namespace MondemaComponents
{
    public class RoundedBorderPanel : Panel
    {
        private Color m_BorderColor = SystemColors.ControlText;
        private int m_iBorderSize = 1;
        private int m_iBorderCornerRadius = 1;
        private bool m_bDisplayBorder = false;

        public RoundedBorderPanel()
        {
            this.Paint += BorderPanel_Paint;
        }

        private void BorderPanel_Paint(object sender, PaintEventArgs e)
        {
            if (m_bDisplayBorder)
            {
                int halfThickness = m_iBorderSize / 2;
                using (Pen p = new Pen(m_BorderColor, m_iBorderSize))
                {
                    Utilities.DrawRoundedRectangle(e.Graphics,p, new Rectangle(halfThickness,
                                                              halfThickness,
                                                              this.ClientSize.Width - m_iBorderSize,
                                                              this.ClientSize.Height - m_iBorderSize), m_iBorderCornerRadius);
                }
            }
        }

        [DefaultValue(typeof(Color), "ControlText")]
        public Color BorderColor
        {
            get
            {
                return m_BorderColor;
            }
            set
            {
                if (m_BorderColor != value) //check for avoid blinking
                {
                    m_BorderColor = value;
                    Refresh();
                }
            }
        }

        [DefaultValue(typeof(int), "1")]
        public int BorderSize
        {
            get
            {
                return m_iBorderSize;
            }
            set
            {
                if (m_iBorderSize < 0) throw new ArgumentException();
                if (m_iBorderSize != value) //check for avoid blinking
                {
                    m_iBorderSize = value;
                    Refresh();
                }
            }
        }

        [DefaultValue(typeof(int), "1")]
        public int BorderCornerRadius
        {
            get
            {
                return m_iBorderCornerRadius;
            }
            set
            {
                if (m_iBorderCornerRadius < 0) throw new ArgumentException();
                if (m_iBorderCornerRadius != value) //check for avoid blinking
                {
                    m_iBorderCornerRadius = value;
                    Refresh();
                }
            }
        }


        [DefaultValue(typeof(bool), "false")]
        public bool DisplayBorder
        {
            get
            {
                return m_bDisplayBorder;
            }
            set
            {
                if (m_bDisplayBorder != value) //check for avoid blinking
                {
                    m_bDisplayBorder = value;
                    Refresh();
                }
            }
        }


    }


}
