using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.ComponentModel;
using System.Diagnostics;

namespace MondemaComponents
{
    public interface IComboBoxAllowedItem
    {
        bool Selectable { get; }
    }

    public partial class ComboBoxAllowed :  CustomComboBox
    {


        const int ButtonSize = 60;
        const int ButtonVisible = 6;
        UserControl m_oDropDown = new UserControl();
        UserControl m_oListPanel = new UserControl();
        UserControl m_oScrollPanel = new UserControl();
        Button m_btnSelected = null;
        Button m_btnScrollUpEnd = new Button();
        Button m_btnScrollUp = new Button();
        Button m_btnScrollDown = new Button();
        Button m_btnScrollDownEnd = new Button();
        public event EventHandler<ItemEventArgs>  SetItem;

        public ComboBoxAllowed()
        {
            m_oListPanel.BorderStyle = BorderStyle.None;
            m_oDropDown.BorderStyle = BorderStyle.None;
            m_oScrollPanel.BorderStyle = BorderStyle.None;
            this.DropDownControl = m_oDropDown;
            AllowResizeDropDown = false;
            DropDownSizeMode = CustomComboBox.SizeMode.UseDropDownSize;
            m_oDropDown.Dock = DockStyle.Fill;
            //m_oListPanel.AutoScroll = true;
            base.DropDownStyle = ComboBoxStyle.DropDownList;
            this.DropDown += ComboBoxAllowed_DropDown;
            PreviewKeyDown += ComboBoxAllowed_PreviewKeyDown;
            this.DropDownShown += ComboBoxAllowed_DropDownShown;
            m_oDropDown.Controls.Add(m_oListPanel);
            m_oDropDown.Controls.Add(m_oScrollPanel);

            m_oListPanel.AutoScroll = false;
            m_oListPanel.VerticalScroll.Maximum = 0;
            m_oListPanel.VerticalScroll.Visible = false;
            m_oListPanel.AutoScroll = true;
            m_oListPanel.MouseWheel += M_oListPanel_MouseWheel;
            //m_oListPanel.PreviewKeyDown += M_oDropDown_PreviewKeyDown;
            SetupScrollButton(m_btnScrollUpEnd);
            SetupScrollButton(m_btnScrollUp);
            SetupScrollButton(m_btnScrollDown);
            SetupScrollButton(m_btnScrollDownEnd);
            m_btnScrollUpEnd.Image = ComboBoxAllowed.ScrollUpEnd;
            m_btnScrollUpEnd.Location = new Point(0,0);
            m_btnScrollUpEnd.Click += M_btnScrollUpEnd_Click;
            m_btnScrollUp.Image = ComboBoxAllowed.ScrollUp;
            m_btnScrollUp.Location = new Point(0, ButtonSize);
            m_btnScrollUp.Click += M_btnScrollUp_Click;
            m_btnScrollDown.Image = ComboBoxAllowed.ScrollDown;
            m_btnScrollDown.Location = new Point(0, (ButtonVisible - 2) * ButtonSize);
            m_btnScrollDown.Click += M_btnScrollDown_Click;
            m_btnScrollDownEnd.Image = ComboBoxAllowed.ScrollDownEnd;
            m_btnScrollDownEnd.Location = new Point(0, (ButtonVisible - 1) * ButtonSize);
            m_btnScrollDownEnd.Click += M_btnScrollDownEnd_Click;
            m_oScrollPanel.Controls.Add(m_btnScrollUpEnd);
            m_oScrollPanel.Controls.Add(m_btnScrollUp);
            m_oScrollPanel.Controls.Add(m_btnScrollDown);
            m_oScrollPanel.Controls.Add(m_btnScrollDownEnd);
            m_oScrollPanel.Size = new Size(ButtonSize, ButtonSize * ButtonVisible);
        }

        private void M_oListPanel_MouseWheel(object sender, MouseEventArgs e)
        {
            ScrollChanged();
        }

        private void ScrollChanged()
        {
            int y = -m_oListPanel.AutoScrollPosition.Y;
            if (y == 0)
            {
                m_btnScrollUp.Enabled = false;
                m_btnScrollUpEnd.Enabled = false;
            }
            else
            {
                m_btnScrollUp.Enabled = true;
                m_btnScrollUpEnd.Enabled = true;
            }
            if (y == MaxScroll)
            {
                m_btnScrollDown.Enabled = false;
                m_btnScrollDownEnd.Enabled = false;
            }
            else
            {
                m_btnScrollDown.Enabled = true;
                m_btnScrollDownEnd.Enabled = true;
            }
        }

        private int MaxScroll
        {
            get
            {
                if (Items.Count > ButtonVisible)
                {
                    return (Items.Count - ButtonVisible) * ButtonSize;
                }
                else
                {
                    return 0;
                }
            }
        }

        private void M_btnScrollUpEnd_Click(object sender, EventArgs e)
        {
            m_oListPanel.AutoScrollPosition = new Point(0,0);
            ScrollChanged();
        }

        private void M_btnScrollUp_Click(object sender, EventArgs e)
        {
            int y = -m_oListPanel.AutoScrollPosition.Y;
            y -= ButtonSize * 2;
            if (y < 0) y = 0;
            m_oListPanel.AutoScrollPosition = new Point(0, y);
            ScrollChanged();
        }

        private void M_btnScrollDown_Click(object sender, EventArgs e)
        {
            int y = -m_oListPanel.AutoScrollPosition.Y;
            y += ButtonSize * 2;
            if (y > MaxScroll) y = MaxScroll;
            m_oListPanel.AutoScrollPosition = new Point(0, y);
            ScrollChanged();

        }

        private void M_btnScrollDownEnd_Click(object sender, EventArgs e)
        {
            m_oListPanel.AutoScrollPosition = new Point(0, MaxScroll);
            ScrollChanged();
        }

        private void SetupScrollButton(Button btn)
        {
            btn.Size = new Size(ButtonSize, ButtonSize);
        }

        private void ComboBoxAllowed_DropDownShown(object sender, EventArgs e)
        {
            m_oListPanel.ActiveControl = m_btnSelected;
            ScrollChanged();
        }

        private void ComboBoxAllowed_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.Up:
                case Keys.Down:
                    if (!IsDroppedDown) e.IsInputKey = false;
                    break;
            }
        }

        private void ComboBoxAllowed_DropDown(object sender, EventArgs e)
        {
            int ClientSizeHeight = ButtonSize * Items.Count;
            int ClientSizeWidth = this.Width;
            bool bUseScroll = false;
            foreach (Button btn in m_oListPanel.Controls)
            {
                btn.Dispose();
            }
            m_oListPanel.Controls.Clear();

            
            if (ClientSizeHeight > ButtonSize * ButtonVisible)
            {  //use scroll
                ClientSizeHeight = ButtonSize * ButtonVisible;
                ClientSizeWidth += ButtonSize;
                bUseScroll = true;
            }
            m_oScrollPanel.Location = new Point(this.Width, 0);
            m_oListPanel.Size = new Size(this.Width, ClientSizeHeight);
            m_oDropDown.Size = new Size(ClientSizeWidth, ClientSizeHeight);


            DropSize = m_oDropDown.Size;
            for (int i = 0; i < Items.Count; i++)
            {
                IComboBoxAllowedItem item = (IComboBoxAllowedItem)Items[i];
                Button btn = new Button();
                btn.Text = item.ToString();
                btn.Size = new Size(this.Width, ButtonSize);
                btn.Location = new Point(0, i * btn.Height);
                m_oListPanel.Controls.Add(btn);
                btn.Enabled = item.Selectable;
                btn.Font = Font;
                btn.TextAlign = ContentAlignment.MiddleCenter;
                btn.Tag = item;
                btn.MouseWheel += Btn_MouseWheel;
                btn.KeyUp += Btn_KeyUp;
                if (item == SelectedItem)
                {
                    btn.ForeColor = SystemColors.HighlightText;
                    btn.BackColor = SystemColors.Highlight;
                    m_btnSelected = btn;
                }
                btn.Click += Btn_Click;
            }
            if (bUseScroll)
            {
                
            }
        }

        private void Btn_KeyUp(object sender, KeyEventArgs e)
        {
            ScrollChanged();
        }

        private void Btn_MouseWheel(object sender, MouseEventArgs e)
        {
            ScrollChanged();
        }

        private void Btn_Click(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            SelectedItem = btn.Tag;
            if (SetItem != null)
            {
                SetItem(this, new ItemEventArgs(btn.Tag));
            }
            HideDropDown();
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        [Browsable(false), ReadOnly(true)]
        public new ComboBoxStyle DropDownStyle
        {
            get { return base.DropDownStyle; }
            set { }
        }

        public new bool Sorted
        {
            get { return base.Sorted; }
            set { base.Sorted = value; }
        }
    }

    public class ItemEventArgs : EventArgs
    {
        public object Item { get; private set; }

        public ItemEventArgs(object _Item)
        {
            Item = _Item;
        }
    }

}
