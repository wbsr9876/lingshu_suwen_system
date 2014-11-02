using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.IO;

namespace LSBuilderCore
{
    public class CMakeFile
    {

        private bool loaded = false;
        private string minVersion;
        private List<string[]> subDirList;
        public int CMAKE_MINIMUM_REQUIRED(string args)
        {
            int index = args.IndexOf(" ");
            minVersion = args.Substring(index + 1);
            return CommonDefine.EC_SUCCESS;
        }

        public int ADD_SUBDIRECTORY(string args)
        {
            string[] dir = args.Split(' ');
            subDirList.Add(dir);
            return CommonDefine.EC_SUCCESS;
        }

        public int Create(string path)
        {
            
            return CommonDefine.EC_SUCCESS;
        }

        public int Load(string path)
        {
            StreamReader stream = File.OpenText(path + "/CMakeLists.txt");
            if (stream == null)
                return CommonDefine.EC_NOT_EXIST;
            string curLine;
            while ((curLine = stream.ReadLine())!= null)
            {
                int index = curLine.IndexOf("(");
                string header = curLine.Substring(0, index);
                string other = curLine.Substring(index);
                char[] trim = {'(',')'};
                other.Trim(trim);
                MethodInfo mi = GetType().GetMethod(header);
                object[] objParams = new object[] { other };
                int ret = (int)mi.Invoke(this, objParams);
            }
            return CommonDefine.EC_SUCCESS;
        }

        public int Save()
        {
            return CommonDefine.EC_SUCCESS;
        }
    }
}
