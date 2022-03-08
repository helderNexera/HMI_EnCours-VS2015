using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MondemaComponents
{
    public class LabelOffset : Label
    {
        public LabelOffset()
        {
            Offset = 0;
            EditText = "";
        }

        public uint Offset
        {
            get; set;
        }

        public string EditText
        {
            get; set;
        }


    }
}
