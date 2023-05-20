namespace Ubb.BikeContest.UserInterface;

partial class LoginView
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
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
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LoginView));
        usernameBox = new TextBox();
        passwordBox = new TextBox();
        button1 = new Button();
        SuspendLayout();
        // 
        // usernameBox
        // 
        usernameBox.Font = new Font("Segoe UI", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
        usernameBox.Location = new Point(32, 210);
        usernameBox.Multiline = true;
        usernameBox.Name = "usernameBox";
        usernameBox.Size = new Size(199, 39);
        usernameBox.TabIndex = 0;
        // 
        // passwordBox
        // 
        passwordBox.Font = new Font("Segoe UI", 14.25F, FontStyle.Regular, GraphicsUnit.Point);
        passwordBox.Location = new Point(32, 274);
        passwordBox.Multiline = true;
        passwordBox.Name = "passwordBox";
        passwordBox.Size = new Size(199, 39);
        passwordBox.TabIndex = 1;
        // 
        // button1
        // 
        button1.Location = new Point(32, 342);
        button1.Name = "button1";
        button1.Size = new Size(199, 39);
        button1.TabIndex = 2;
        button1.Text = "LOG IN";
        button1.UseVisualStyleBackColor = true;
        button1.Click += button1_Click;
        // 
        // LoginPage
        // 
        AutoScaleDimensions = new SizeF(7F, 15F);
        AutoScaleMode = AutoScaleMode.Font;
        BackgroundImage = (Image)resources.GetObject("$this.BackgroundImage");
        BackgroundImageLayout = ImageLayout.Stretch;
        ClientSize = new Size(800, 450);
        Controls.Add(button1);
        Controls.Add(passwordBox);
        Controls.Add(usernameBox);
        Name = "LoginPage";
        Text = "Form1";
        Load += Form1_Load;
        ResumeLayout(false);
        PerformLayout();
    }

    #endregion

    private TextBox usernameBox;
    private TextBox passwordBox;
    private Button button1;
}