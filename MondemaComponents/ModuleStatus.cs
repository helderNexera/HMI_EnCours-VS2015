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
    public partial class ModuleStatus : UserControl
    {
        static readonly private Color OffColor = Color.White;

        private debug m_Debug = null;
        private step m_Step = null;

        public ModuleStatus()
        {
            InitializeComponent();
            ledAlarm.Tag = ledAlarm.ForeColor;
            ledWarning.Tag = ledWarning.ForeColor;
            ledRun.Tag = ledRun.ForeColor;
            ledInterlock.Tag = ledInterlock.ForeColor;
            ledAlarm.Click += Self_Click;
            ledWarning.Click += Self_Click;
            ledRun.Click += Self_Click;
            ledInterlock.Click += Self_Click;
            this.m_Debug = new debug(btnDebug,this);
            m_Step = new step(btnStep, this);
            btnStep.BackColor = Color.Orange;
        }

        private void Self_Click(object sender, EventArgs e)
        {
            this.InvokeOnClick(this, e);
        }

        public uint Offset
        {
            get;
            set;
        }

        public bool Alarm
        {
            set
            {
                UpdateLed(ledAlarm, value);
            }
        }

        public bool Warning
        {
            set
            {
                UpdateLed(ledWarning, value);
            }
        }

        public bool Run
        {
            set
            {
                UpdateLed(ledRun, value);
            }
        }

        public bool Interlock
        {
            set
            {
                UpdateLed(ledInterlock, value);
            }
        }


        private void UpdateLed(Led led,bool Value)
        {
            led.ForeColor = Value ? (Color)led.Tag : OffColor;
        }

        protected override Size DefaultSize
        {
            get
            {
                return new Size(20,74);
            }
        }

        public debug Debug
        {
            get
            {
                return m_Debug;
            }
        }

        public step Step
        {
            get
            {
                return m_Step;
            }
        }


        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
        public new Size Size { get { return base.Size; } private set { base.Size = value; } }

        private void btnDebug_Click(object sender, EventArgs e)
        {

        }

        private void btnStep_Click(object sender, EventArgs e)
        {

        }

        public class debug
        {
            private CheckBox btn = null;
            private ModuleStatus Owner = null;

            internal debug(CheckBox _btn, ModuleStatus _Owner)
            {
                Owner = _Owner;
                btn = _btn;
                btn.Click += Btn_Click;
            }

            private void Btn_Click(object sender, EventArgs e)
            {
                if (Click != null) Click(Owner, e);
            }

            public event EventHandler Click = null;

            public bool Visible
            {
                set
                {
                    btn.Visible = value;
                }
            }

            public bool Checked
            {
                get
                {
                    return btn.Checked;
                }

                set
                {
                    btn.Checked = value;
                    if (value)
                    {
                        btn.BackColor = Color.Red;
                    }
                    else
                    {
                        btn.BackColor = Color.Transparent;
                    }
                }
            }
        }

        public class step
        {
            private Button btn = null;
            private ModuleStatus Owner = null;

            internal step(Button _btn, ModuleStatus _Owner)
            {
                Owner = _Owner;
                btn = _btn;
                btn.Click += Btn_Click;
            }

            private void Btn_Click(object sender, EventArgs e)
            {
                if (Click != null) Click(Owner, e);
            }

            public event EventHandler Click = null;

            public bool Visible
            {
                set
                {
                    btn.Visible = value;
                }
            }
        }
    }
}
