namespace Ubb.BikeContest.UserInterface
{
    partial class MainView
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
            label1 = new Label();
            label2 = new Label();
            teamBox = new ComboBox();
            label3 = new Label();
            usernameLabel = new Label();
            raceList = new ListView();
            participantsView = new ListView();
            participantButton = new Button();
            registerButton = new Button();
            newRaceButton = new Button();
            logOutButton = new Button();
            label4 = new Label();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 18F, FontStyle.Regular, GraphicsUnit.Point);
            label1.Location = new Point(27, 121);
            label1.Name = "label1";
            label1.Size = new Size(83, 32);
            label1.TabIndex = 2;
            label1.Text = "RACES";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 18F, FontStyle.Regular, GraphicsUnit.Point);
            label2.Location = new Point(618, 121);
            label2.Name = "label2";
            label2.Size = new Size(163, 32);
            label2.TabIndex = 3;
            label2.Text = "PARTICIPANTS";
            // 
            // teamBox
            // 
            teamBox.FormattingEnabled = true;
            teamBox.Location = new Point(837, 130);
            teamBox.Name = "teamBox";
            teamBox.Size = new Size(226, 23);
            teamBox.TabIndex = 4;
            teamBox.SelectedIndexChanged += teamBox_SelectedIndexChanged;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI Semibold", 15.75F, FontStyle.Bold | FontStyle.Italic, GraphicsUnit.Point);
            label3.Location = new Point(27, 46);
            label3.Name = "label3";
            label3.Size = new Size(144, 30);
            label3.TabIndex = 5;
            label3.Text = "Logged in as :";
            // 
            // usernameLabel
            // 
            usernameLabel.AutoSize = true;
            usernameLabel.Font = new Font("Segoe UI Black", 15.75F, FontStyle.Bold | FontStyle.Italic, GraphicsUnit.Point);
            usernameLabel.Location = new Point(177, 46);
            usernameLabel.Name = "usernameLabel";
            usernameLabel.Size = new Size(78, 30);
            usernameLabel.TabIndex = 6;
            usernameLabel.Text = "admin";
            // 
            // raceList
            // 
            raceList.Font = new Font("Segoe UI", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
            raceList.Location = new Point(27, 179);
            raceList.Name = "raceList";
            raceList.Size = new Size(519, 394);
            raceList.TabIndex = 7;
            raceList.UseCompatibleStateImageBehavior = false;
            // 
            // participantsView
            // 
            participantsView.Font = new Font("Segoe UI", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
            participantsView.Location = new Point(618, 179);
            participantsView.Name = "participantsView";
            participantsView.Size = new Size(445, 394);
            participantsView.TabIndex = 8;
            participantsView.UseCompatibleStateImageBehavior = false;
            // 
            // participantButton
            // 
            participantButton.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            participantButton.Location = new Point(390, 46);
            participantButton.Name = "participantButton";
            participantButton.Size = new Size(156, 30);
            participantButton.TabIndex = 9;
            participantButton.Text = "NEW PARTICIPANT";
            participantButton.UseVisualStyleBackColor = true;
            participantButton.Click += participantButton_Click;
            // 
            // registerButton
            // 
            registerButton.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            registerButton.Location = new Point(577, 46);
            registerButton.Name = "registerButton";
            registerButton.Size = new Size(156, 30);
            registerButton.TabIndex = 10;
            registerButton.Text = "REGISTER TO RACE";
            registerButton.UseVisualStyleBackColor = true;
            registerButton.Click += registerButton_Click;
            // 
            // newRaceButton
            // 
            newRaceButton.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            newRaceButton.Location = new Point(766, 46);
            newRaceButton.Name = "newRaceButton";
            newRaceButton.Size = new Size(156, 30);
            newRaceButton.TabIndex = 11;
            newRaceButton.Text = "NEW RACE";
            newRaceButton.UseVisualStyleBackColor = true;
            // 
            // logOutButton
            // 
            logOutButton.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            logOutButton.Location = new Point(950, 46);
            logOutButton.Name = "logOutButton";
            logOutButton.Size = new Size(113, 30);
            logOutButton.TabIndex = 12;
            logOutButton.Text = "LOG OUT";
            logOutButton.UseVisualStyleBackColor = true;
            logOutButton.Click += logOutButton_Click;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            label4.Location = new Point(972, 106);
            label4.Name = "label4";
            label4.Size = new Size(91, 21);
            label4.TabIndex = 13;
            label4.Text = "Select Team";
            // 
            // MainPage
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1102, 619);
            Controls.Add(label4);
            Controls.Add(logOutButton);
            Controls.Add(newRaceButton);
            Controls.Add(registerButton);
            Controls.Add(participantButton);
            Controls.Add(participantsView);
            Controls.Add(raceList);
            Controls.Add(usernameLabel);
            Controls.Add(label3);
            Controls.Add(teamBox);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "MainPage";
            Text = "MainPage";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private Label label1;
        private Label label2;
        private ComboBox teamBox;
        private Label label3;
        private Label usernameLabel;
        private ListView raceList;
        private ListView participantsView;
        private Button participantButton;
        private Button registerButton;
        private Button newRaceButton;
        private Button logOutButton;
        private Label label4;
    }
}