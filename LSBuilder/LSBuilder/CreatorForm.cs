using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using LSBuilderCore;

namespace LSBuilder
{
    public partial class CreatorForm : Form
    {
        public CreatorForm()
        {
            InitializeComponent();
        }

        private void workspaceButton_Click(object sender, EventArgs e)
        {
            if(folderBrowserDialog1.ShowDialog(this) == DialogResult.OK)
            {
                workspaceTextBox.Text = folderBrowserDialog1.SelectedPath;
            }
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            Workspace ws = new Workspace();
            ws.Create(workspaceTextBox.Text);
            Close();
        }

        private void workspaceTextBox_TextChanged(object sender, EventArgs e)
        {
            Workspace ws = new Workspace();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CreatorForm));
            int ret = ws.Load(workspaceTextBox.Text);
            if (!Directory.Exists(workspaceTextBox.Text))
            {
                resources.ApplyResources(stateLabel, "stateLabel");
                return;
            }

            if (ret == CommonDefine.EC_SUCCESS)
            {

                resources.ApplyResources(stateLabel, "stateLabel_success");
            }
            else
            {
                resources.ApplyResources(stateLabel, "stateLabel_failed");
            }
        }
    }
}
