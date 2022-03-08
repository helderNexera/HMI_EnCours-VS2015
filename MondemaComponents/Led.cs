using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MondemaComponents
{
    public partial class Led : UserControl
    {
        public Led()
        {
            InitializeComponent();
            this.Size = this.DefaultSize;
            this.ResizeRedraw = true;
            ForeColor = Color.Gray;
            this.Refresh();
        }

        private void Led_Paint(object sender, PaintEventArgs e)
        {
            Rectangle Rec = e.ClipRectangle;
            e.Graphics.DrawRectangle(new Pen(this.BackColor), Rec);
            Rec.Inflate(-2, -2);
            e.Graphics.FillEllipse(new SolidBrush(ForeColor), Rec);
            e.Graphics.DrawEllipse(new Pen(Color.Black, 2), Rec);
        }

        [DefaultValue(typeof(Color), "Gray")]
        public override Color ForeColor
        {
            get
            {
                return base.ForeColor;
            }
            set
            {
                if (base.ForeColor != value) //check for avoid blinking
                {  
                    base.ForeColor = value;
                    Refresh();
                }
            }
        }

        protected override Size DefaultSize
        {
            get
            {
                return new Size(30, 30);
            }
        }

        public bool Value
        {
            set
            {
                ForeColor = value ? System.Drawing.Color.Lime : System.Drawing.Color.Red;
            }
        }
    }
}
