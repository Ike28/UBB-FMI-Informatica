namespace Laborator_2
{
    partial class Form1
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
            dataGridViewParent = new DataGridView();
            dataGridViewSon = new DataGridView();
            addButton = new Button();
            deleteButton = new Button();
            updateButton = new Button();
            panel1 = new FlowLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewSon).BeginInit();
            SuspendLayout();
            // 
            // dataGridViewParent
            // 
            dataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewParent.Location = new Point(28, 37);
            dataGridViewParent.Name = "dataGridViewParent";
            dataGridViewParent.RowTemplate.Height = 25;
            dataGridViewParent.Size = new Size(481, 280);
            dataGridViewParent.TabIndex = 0;
            // 
            // dataGridViewSon
            // 
            dataGridViewSon.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewSon.Location = new Point(542, 37);
            dataGridViewSon.Name = "dataGridViewSon";
            dataGridViewSon.RowTemplate.Height = 25;
            dataGridViewSon.Size = new Size(548, 417);
            dataGridViewSon.TabIndex = 1;
            // 
            // addButton
            // 
            addButton.Location = new Point(542, 478);
            addButton.Name = "addButton";
            addButton.Size = new Size(134, 43);
            addButton.TabIndex = 2;
            addButton.Text = "ADD";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // deleteButton
            // 
            deleteButton.Location = new Point(698, 478);
            deleteButton.Name = "deleteButton";
            deleteButton.Size = new Size(134, 43);
            deleteButton.TabIndex = 3;
            deleteButton.Text = "DELETE";
            deleteButton.UseVisualStyleBackColor = true;
            deleteButton.Click += deleteButton_Click;
            // 
            // updateButton
            // 
            updateButton.Location = new Point(851, 478);
            updateButton.Name = "updateButton";
            updateButton.Size = new Size(134, 43);
            updateButton.TabIndex = 4;
            updateButton.Text = "UPDATE";
            updateButton.UseVisualStyleBackColor = true;
            updateButton.Click += updateButton_Click;
            // 
            // panel1
            // 
            panel1.Location = new Point(28, 354);
            panel1.Name = "panel1";
            panel1.Size = new Size(481, 167);
            panel1.TabIndex = 5;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1111, 588);
            Controls.Add(panel1);
            Controls.Add(updateButton);
            Controls.Add(deleteButton);
            Controls.Add(addButton);
            Controls.Add(dataGridViewSon);
            Controls.Add(dataGridViewParent);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)dataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridViewSon).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private DataGridView dataGridViewParent;
        private DataGridView dataGridViewSon;
        private Button addButton;
        private Button deleteButton;
        private Button updateButton;
        private FlowLayoutPanel panel1;
    }
}