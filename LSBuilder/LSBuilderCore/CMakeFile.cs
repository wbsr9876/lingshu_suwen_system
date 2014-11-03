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
        protected string path;
        protected bool loaded = false;
        protected string minVersion;
        protected string projectName;
        protected List<string[]> subDirList = new List<string[]>();// src_dir bin_dir
        protected List<string[]> srcDirList = new List<string[]>();// src_dir define_name
        public int CMAKE_MINIMUM_REQUIRED(string args)
        {
            int index = args.IndexOf(" ");
            minVersion = args.Substring(index + 1);
            return CommonDefine.EC_SUCCESS;
        }

        public int __CMAKE_MINIMUM_REQUIRED(StreamWriter sw)
        {
            sw.WriteLine("CMAKE_MINIMUM_REQUIRED(VERSION {0})",minVersion);
            return CommonDefine.EC_SUCCESS;
        }

        public int ADD_SUBDIRECTORY(string args)
        {
            string[] dir = args.Split(' ');
            subDirList.Add(dir);
            return CommonDefine.EC_SUCCESS;
        }

        public int __ADD_SUBDIRECTORY(StreamWriter sw,string[] dir)
        {
            sw.WriteLine("ADD_SUBDIRECTORY({0} {1})", dir[0], dir[1]);
            return CommonDefine.EC_SUCCESS;
        }

        public int PROJECT(string args)
        {
            projectName = args;
            return CommonDefine.EC_SUCCESS;
        }

        public int __PROJECT(StreamWriter sw)
        {
            sw.WriteLine("PROJECT({0})", projectName);
            return CommonDefine.EC_SUCCESS;
        }

        public int AUX_SOURCE_DIRECTORY(string args)
        {
            string[] dir = args.Split(' ');
            srcDirList.Add(dir);
            return CommonDefine.EC_SUCCESS;
        }

        public int __AUX_SOURCE_DIRECTORY(StreamWriter sw, string[] dir)
        {
            sw.WriteLine("AUX_SOURCE_DIRECTORY({0} {1})", dir[0], dir[1]);
            return CommonDefine.EC_SUCCESS;
        }

        public virtual int Create(string filePath,string name)
        {
            path = filePath;
            projectName = name;
            minVersion = "2.8";
            return Save();
        }

        public int Load(string filePath)
        {
            path = filePath;
            if (!File.Exists(path + "/CMakeLists.txt"))
                return CommonDefine.EC_NOT_EXIST | CommonDefine.CT_CMAKEFILE;
            using (StreamReader stream = new StreamReader(path + "/CMakeLists.txt"))
            {
                if (stream == null)
                    return CommonDefine.EC_NOT_EXIST | CommonDefine.CT_CMAKEFILE;
                string curLine;
                while ((curLine = stream.ReadLine()) != null)
                {
                    int index = curLine.IndexOf("(");
                    string header = curLine.Substring(0, index);
                    string other = curLine.Substring(index);
                    char[] trim = { '(', ')' };
                    other.Trim(trim);
                    MethodInfo mi = GetType().GetMethod(header);
                    object[] objParams = new object[] { other };
                    int ret = (int)mi.Invoke(this, objParams);
                }
            }
            return CommonDefine.EC_SUCCESS;
        }

        public virtual int Save()
        {
            return CommonDefine.EC_SUCCESS;
        }
    }

    public class CMakeSln : CMakeFile
    {
        public override int Save()
        {
            using (StreamWriter stream = new StreamWriter(path + "/CMakeLists.txt",false))
            {
                __CMAKE_MINIMUM_REQUIRED(stream);
                __PROJECT(stream);
                foreach (string[] dir in subDirList)
                {
                    __ADD_SUBDIRECTORY(stream, dir);
                }
            }
            return CommonDefine.EC_SUCCESS;
        }

    }
}
