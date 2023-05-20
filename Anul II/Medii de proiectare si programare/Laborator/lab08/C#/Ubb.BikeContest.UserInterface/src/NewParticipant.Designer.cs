namespace Ubb.BikeContest.UserInterface
{
    partial class NewParticipant
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(NewParticipant));
            label1 = new Label();
            firstnameField = new TextBox();
            lastnameField = new TextBox();
            teamBox = new ComboBox();
            confirmButton = new Button();
            engineField = new NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)engineField).BeginInit();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.Transparent;
            label1.Font = new Font("Lato Black", 39.75F, FontStyle.Bold, GraphicsUnit.Point);
            label1.ForeColor = Color.White;
            label1.Location = new Point(48, 174);
            label1.Name = "label1";
            label1.Size = new Size(320, 63);
            label1.TabIndex = 0;
            label1.Text = "NEW RIDER";
            // 
            // firstnameField
            // 
            firstnameField.Font = new Font("Lato Semibold", 15.7499981F, FontStyle.Bold, GraphicsUnit.Point);
            firstnameField.Location = new Point(58, 255);
            firstnameField.Multiline = true;
            firstnameField.Name = "firstnameField";
            firstnameField.Size = new Size(339, 47);
            firstnameField.TabIndex = 1;
            // 
            // lastnameField
            // 
            lastnameField.Font = new Font("Lato Semibold", 15.7499981F, FontStyle.Bold, GraphicsUnit.Point);
            lastnameField.Location = new Point(58, 338);
            lastnameField.Multiline = true;
            lastnameField.Name = "lastnameField";
            lastnameField.Size = new Size(339, 47);
            lastnameField.TabIndex = 2;
            // 
            // teamBox
            // 
            teamBox.Font = new Font("Lato Semibold", 18F, FontStyle.Bold, GraphicsUnit.Point);
            teamBox.FormattingEnabled = true;
            teamBox.Location = new Point(58, 495);
            teamBox.Name = "teamBox";
            teamBox.Size = new Size(339, 37);
            teamBox.TabIndex = 4;
            // 
            // confirmButton
            // 
            confirmButton.Font = new Font("Lato Black", 15.7499981F, FontStyle.Bold, GraphicsUnit.Point);
            confirmButton.ForeColor = Color.DeepPink;
            confirmButton.Location = new Point(58, 562);
            confirmButton.Name = "confirmButton";
            confirmButton.Size = new Size(339, 47);
            confirmButton.TabIndex = 5;
            confirmButton.Text = "CONFIRM";
            confirmButton.UseVisualStyleBackColor = true;
            confirmButton.Click += button1_Click;
            // 
            // engineField
            // 
            engineField.Font = new Font("Lato Semibold", 15.7499981F, FontStyle.Bold, GraphicsUnit.Point);
            engineField.Location = new Point(58, 420);
            engineField.Name = "engineField";
            engineField.Size = new Size(339, 33);
            engineField.TabIndex = 6;
            // 
            // NewParticipant
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackgroundImage = (Image)resources.GetObject("$this.BackgroundImage");
            BackgroundImageLayout = ImageLayout.Stretch;
            ClientSize = new Size(944, 681);
            Controls.Add(engineField);
            Controls.Add(confirmButton);
            Controls.Add(teamBox);
            Controls.Add(lastnameField);
            Controls.Add(firstnameField);
            Controls.Add(label1);
            Name = "NewParticipant";
            Text = "NewParticipant";
            ((System.ComponentModel.ISupportInitialize)engineField).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private TextBox firstnameField;
        private TextBox lastnameField;
        private ComboBox teamBox;
        private Button confirmButton;
        private NumericUpDown engineField;
    }
}