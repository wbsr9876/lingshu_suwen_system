using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LSBuilderCore
{
    public class Server
    {
        private Workspace parent;
        private bool loaded = false;
        private string name;
        public string Name
        {
            get { return name; }
            //set { name = value; }
        }
        private string path;
        public string Path
        {
            get { return path; }
            //set { path = value; }
        }
        public Server(Workspace workspace)
        {
            parent = workspace;
        }

        public int Load(string name,string path)
        {
            loaded = true;
            return CommonDefine.EC_SUCCESS;
        }
    }
}
