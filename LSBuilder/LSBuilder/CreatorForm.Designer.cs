namespace LSBuilder
{
    partial class CreatorForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CreatorForm));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.serverPage = new System.Windows.Forms.TabPage();
            this.contentGroupBox = new System.Windows.Forms.GroupBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.locationGroupBox = new System.Windows.Forms.GroupBox();
            this.workspaceButton = new System.Windows.Forms.Button();
            this.workspaceTextBox = new System.Windows.Forms.TextBox();
            this.workspaceLabel = new System.Windows.Forms.Label();
            this.objectPage = new System.Windows.Forms.TabPage();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.serverNameLabel = new System.Windows.Forms.Label();
            this.serverNameTextBox = new System.Windows.Forms.TextBox();
            this.stateLabel = new System.Windows.Forms.Label();
            this.tabControl1.SuspendLayout();
            this.serverPage.SuspendLayout();
            this.contentGroupBox.SuspendLayout();
            this.panel1.SuspendLayout();
            this.locationGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.serverPage);
            this.tabControl1.Controls.Add(this.objectPage);
            resources.ApplyResources(this.tabControl1, "tabControl1");
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            // 
            // serverPage
            // 
            this.serverPage.Controls.Add(this.contentGroupBox);
            this.serverPage.Controls.Add(this.panel1);
            this.serverPage.Controls.Add(this.locationGroupBox);
            resources.ApplyResources(this.serverPage, "serverPage");
            this.serverPage.Name = "serverPage";
            this.serverPage.UseVisualStyleBackColor = true;
            // 
            // contentGroupBox
            // 
            this.contentGroupBox.Controls.Add(this.serverNameTextBox);
            this.contentGroupBox.Controls.Add(this.serverNameLabel);
            resources.ApplyResources(this.contentGroupBox, "contentGroupBox");
            this.contentGroupBox.Name = "contentGroupBox";
            this.contentGroupBox.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.okButton);
            this.panel1.Controls.Add(this.cancelButton);
            resources.ApplyResources(this.panel1, "panel1");
            this.panel1.Name = "panel1";
            // 
            // okButton
            // 
            resources.ApplyResources(this.okButton, "okButton");
            this.okButton.Name = "okButton";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // cancelButton
            // 
            resources.ApplyResources(this.cancelButton, "cancelButton");
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // locationGroupBox
            // 
            this.locationGroupBox.Controls.Add(this.stateLabel);
            this.locationGroupBox.Controls.Add(this.workspaceButton);
            this.locationGroupBox.Controls.Add(this.workspaceTextBox);
            this.locationGroupBox.Controls.Add(this.workspaceLabel);
            resources.ApplyResources(this.locationGroupBox, "locationGroupBox");
            this.locationGroupBox.Name = "locationGroupBox";
            this.locationGroupBox.TabStop = false;
            // 
            // workspaceButton
            // 
            resources.ApplyResources(this.workspaceButton, "workspaceButton");
            this.workspaceButton.Name = "workspaceButton";
            this.workspaceButton.UseVisualStyleBackColor = true;
            this.workspaceButton.Click += new System.EventHandler(this.workspaceButton_Click);
            // 
            // workspaceTextBox
            // 
            resources.ApplyResources(this.workspaceTextBox, "workspaceTextBox");
            this.workspaceTextBox.Name = "workspaceTextBox";
            this.workspaceTextBox.TextChanged += new System.EventHandler(this.workspaceTextBox_TextChanged);
            // 
            // workspaceLabel
            // 
            resources.ApplyResources(this.workspaceLabel, "workspaceLabel");
            this.workspaceLabel.Name = "workspaceLabel";
            // 
            // objectPage
            // 
            resources.ApplyResources(this.objectPage, "objectPage");
            this.objectPage.Name = "objectPage";
            this.objectPage.UseVisualStyleBackColor = true;
            // 
            // serverNameLabel
            // 
            resources.ApplyResources(this.serverNameLabel, "serverNameLabel");
            this.serverNameLabel.Name = "serverNameLabel";
            // 
            // serverNameTextBox
            // 
            resources.ApplyResources(this.serverNameTextBox, "serverNameTextBox");
            this.serverNameTextBox.Name = "serverNameTextBox";
            // 
            // stateLabel
            // 
            this.stateLabel.AutoEllipsis = true;
            resources.ApplyResources(this.stateLabel, "stateLabel");
            this.stateLabel.Name = "stateLabel";
            // 
            // CreatorForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tabControl1);
            this.Name = "CreatorForm";
            this.tabControl1.ResumeLayout(false);
            this.serverPage.ResumeLayout(false);
            this.contentGroupBox.ResumeLayout(false);
            this.contentGroupBox.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.locationGroupBox.ResumeLayout(false);
            this.locationGroupBox.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage serverPage;
        private System.Windows.Forms.TabPage objectPage;
        private System.Windows.Forms.Button workspaceButton;
        private System.Windows.Forms.TextBox workspaceTextBox;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.GroupBox contentGroupBox;
        private System.Windows.Forms.GroupBox locationGroupBox;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label workspaceLabel;
        private System.Windows.Forms.Label serverNameLabel;
        private System.Windows.Forms.TextBox serverNameTextBox;
        private System.Windows.Forms.Label stateLabel;
    }
}