using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Forms;

namespace MondemaComponents
{
    public class CheckedListBoxHeightItem : CheckedListBox
    {
        private int m_ItemHeight;

        public CheckedListBoxHeightItem()
        {
            m_ItemHeight = 20;
        }

        [DefaultValue(typeof(int), "20")]
        public int ItemSize
        {
            get
            {
                return ItemHeight;
            }
            set
            {
                ItemHeight = value;
            }
        }

        public override int ItemHeight
        {
            get
            {
                return m_ItemHeight;
            }
            set
            {
                if (m_ItemHeight != value) //check for avoid blinking
                {
                    m_ItemHeight = value;
                    Refresh();
                    Invalidate();
                }
            }
        }
    }
}
