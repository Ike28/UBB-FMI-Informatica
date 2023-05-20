namespace Ubb.BikeContest.UserInterface
{
    partial class RegisterToRace
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RegisterToRace));
            participantBox = new ComboBox();
            label1 = new Label();
            raceView = new ListView();
            racesLabel = new Label();
            confirmButton = new Button();
            SuspendLayout();
            // 
            // participantBox
            // 
            participantBox.Font = new Font("Lato Semibold", 18F, FontStyle.Bold, GraphicsUnit.Point);
            participantBox.FormattingEnabled = true;
            participantBox.Location = new Point(45, 261);
            participantBox.Name = "participantBox";
            participantBox.Size = new Size(378, 37);
            participantBox.TabIndex = 5;
            participantBox.SelectedIndexChanged += participantBox_SelectedIndexChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.BackColor = Color.Transparent;
            label1.Font = new Font("Lato Black", 39.75F, FontStyle.Bold, GraphicsUnit.Point);
            label1.ForeColor = Color.White;
            label1.Location = new Point(32, 157);
            label1.Name = "label1";
            label1.Size = new Size(502, 63);
            label1.TabIndex = 6;
            label1.Text = "REGISTER TO RACE";
            // 
            // raceView
            // 
            raceView.Font = new Font("Lato Semibold", 15.7499981F, FontStyle.Bold, GraphicsUnit.Point);
            raceView.Location = new Point(45, 331);
            raceView.Name = "raceView";
            raceView.Size = new Size(378, 191);
            raceView.TabIndex = 7;
            raceView.UseCompatibleStateImageBehavior = false;
            // 
            // racesLabel
            // 
            racesLabel.AutoSize = true;
            racesLabel.BackColor = Color.Transparent;
            racesLabel.Font = new Font("Lato", 18F, FontStyle.Bold, GraphicsUnit.Point);
            racesLabel.ForeColor = Color.White;
            racesLabel.Location = new Point(45, 537);
            racesLabel.Name = "racesLabel";
            racesLabel.Size = new Size(181, 29);
            racesLabel.TabIndex = 9;
            racesLabel.Text = "RACES FOUND";
            // 
            // confirmButton
            // 
            confirmButton.Font = new Font("Lato Black", 15.7499981F, FontStyle.Bold, GraphicsUnit.Point);
            confirmButton.ForeColor = Color.DeepPink;
            confirmButton.Location = new Point(45, 584);
            confirmButton.Name = "confirmButton";
            confirmButton.Size = new Size(378, 47);
            confirmButton.TabIndex = 10;
            confirmButton.Text = "CONFIRM ENTRIES";
            confirmButton.UseVisualStyleBackColor = true;
            confirmButton.Click += confirmButton_Click;
            // 
            // RegisterToRace
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            BackgroundImage = (Image)resources.GetObject("$this.BackgroundImage");
            BackgroundImageLayout = ImageLayout.Stretch;
            ClientSize = new Size(944, 681);
            Controls.Add(confirmButton);
            Controls.Add(racesLabel);
            Controls.Add(raceView);
            Controls.Add(label1);
            Controls.Add(participantBox);
            Name = "RegisterToRace";
            Text = "RegisterToRace";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ComboBox participantBox;
        private Label label1;
        private ListView raceView;
        private Label racesLabel;
        private Button confirmButton;
    }
}