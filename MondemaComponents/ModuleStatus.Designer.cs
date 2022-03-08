namespace MondemaComponents
{
    partial class ModuleStatus
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnStep = new System.Windows.Forms.Button();
            this.btnDebug = new System.Windows.Forms.CheckBox();
            this.ledInterlock = new MondemaComponents.Led();
            this.ledWarning = new MondemaComponents.Led();
            this.ledAlarm = new MondemaComponents.Led();
            this.ledRun = new MondemaComponents.Led();
            this.SuspendLayout();
            // 
            // btnStep
            // 
            this.btnStep.Location = new System.Drawing.Point(20, 44);
            this.btnStep.Name = "btnStep";
            this.btnStep.Size = new System.Drawing.Size(22, 22);
            this.btnStep.TabIndex = 5;
            this.btnStep.Text = "S";
            this.btnStep.UseVisualStyleBackColor = true;
            this.btnStep.Click += new System.EventHandler(this.btnStep_Click);
            // 
            // btnDebug
            // 
            this.btnDebug.Appearance = System.Windows.Forms.Appearance.Button;
            this.btnDebug.Location = new System.Drawing.Point(20, 5);
            this.btnDebug.Name = "btnDebug";
            this.btnDebug.Size = new System.Drawing.Size(22, 22);
            this.btnDebug.TabIndex = 6;
            this.btnDebug.Text = "D";
            this.btnDebug.UseVisualStyleBackColor = true;
            // 
            // ledInterlock
            // 
            this.ledInterlock.ForeColor = System.Drawing.Color.Orange;
            this.ledInterlock.Location = new System.Drawing.Point(0, 56);
            this.ledInterlock.Name = "ledInterlock";
            this.ledInterlock.Size = new System.Drawing.Size(20, 14);
            this.ledInterlock.TabIndex = 3;
            // 
            // ledWarning
            // 
            this.ledWarning.ForeColor = System.Drawing.Color.Blue;
            this.ledWarning.Location = new System.Drawing.Point(0, 36);
            this.ledWarning.Name = "ledWarning";
            this.ledWarning.Size = new System.Drawing.Size(20, 14);
            this.ledWarning.TabIndex = 2;
            // 
            // ledAlarm
            // 
            this.ledAlarm.ForeColor = System.Drawing.Color.Red;
            this.ledAlarm.Location = new System.Drawing.Point(0, 18);
            this.ledAlarm.Name = "ledAlarm";
            this.ledAlarm.Size = new System.Drawing.Size(20, 14);
            this.ledAlarm.TabIndex = 1;
            // 
            // ledRun
            // 
            this.ledRun.ForeColor = System.Drawing.Color.Lime;
            this.ledRun.Location = new System.Drawing.Point(0, 0);
            this.ledRun.Name = "ledRun";
            this.ledRun.Size = new System.Drawing.Size(20, 14);
            this.ledRun.TabIndex = 0;
            // 
            // ModuleStatus
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Transparent;
            this.Controls.Add(this.btnDebug);
            this.Controls.Add(this.btnStep);
            this.Controls.Add(this.ledInterlock);
            this.Controls.Add(this.ledWarning);
            this.Controls.Add(this.ledAlarm);
            this.Controls.Add(this.ledRun);
            this.Name = "ModuleStatus";
            this.Size = new System.Drawing.Size(41, 73);
            this.ResumeLayout(false);

        }

        #endregion

        private MondemaComponents.Led ledRun;
        private MondemaComponents.Led ledAlarm;
        private MondemaComponents.Led ledWarning;
        private Led ledInterlock;
        private System.Windows.Forms.Button btnStep;
        private System.Windows.Forms.CheckBox btnDebug;
    }
}
