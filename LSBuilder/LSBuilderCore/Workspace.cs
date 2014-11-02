using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;

namespace LSBuilderCore
{
    public class Workspace
    {
        private const string configDir = ".LBSConfig";
        private const string configFilename = "workspace.lsb";
        //lbsxml string
        private const string xs_root = "Workspace";
        private const string xs_serverList = "ServerList";
        private const string xs_server = "Server";
        private const string xs_nameAttr = "Name";
        private const string xs_countAttr = "Count";
        private const string xs_pathAttr = "Path";
        public bool loaded = false;
        private XmlDocument doc = new XmlDocument();
        private DirectoryInfo path;
        private List<Server> serverList = new List<Server>();

        public enum ErrorCode
        {
            EC_SUCCESS = 0x0,
            EC_NO_DATA = 0x1,
            EC_WRONG_FILE = 0x2,
            EC_INVAILD_WORKSPACE = 0x3,
            EC_WRONG_SPACE_NAME = 0x4,
            EC_UNKNOWN_ERROR = 0xFFFFFFF 
        };
        public ErrorCode Load(string filePath)
        {
            string xmlPath = filePath + "/" + configDir + "/" + configFilename;
            if (!File.Exists(xmlPath))
                return ErrorCode.EC_INVAILD_WORKSPACE;
      
            doc.Load(xmlPath);
            if (doc.DocumentElement.Name != xs_root)
            {
                return ErrorCode.EC_WRONG_FILE;
            }
            path = new DirectoryInfo(filePath);
            if (path.Name != doc.DocumentElement.GetAttribute(xs_nameAttr))
                return ErrorCode.EC_WRONG_SPACE_NAME;

            foreach(XmlElement listNode in doc.DocumentElement.GetElementsByTagName(xs_serverList))
            {
                int count = int.Parse(listNode.GetAttribute(xs_countAttr));
                foreach(XmlElement serverNode in listNode.GetElementsByTagName(xs_server))
                {
                    string serverName = serverNode.GetAttribute(xs_nameAttr);
                    string serverPath = serverNode.GetAttribute(xs_pathAttr);
                }
            }
            loaded = true;
            return ErrorCode.EC_SUCCESS;
        }

        public ErrorCode Save()
        {
            if(loaded)
            {
                doc.Save(configFilename);
                return ErrorCode.EC_SUCCESS;
            }
            return ErrorCode.EC_NO_DATA;
        }

        public ErrorCode Create(string filepath)
        {
            if(!Directory.Exists(filepath))
                return ErrorCode.EC_INVAILD_WORKSPACE;
            string configPath = filepath + "/" + configDir;
            if(Directory.Exists(configPath))
                Directory.Delete(configPath,true);

            DirectoryInfo di = Directory.CreateDirectory(configPath);
            
            if (loaded)
                doc.RemoveAll();

            XmlDeclaration decl = doc.CreateXmlDeclaration("1.0", null, null);
            doc.AppendChild(decl);
            //XmlProcessingInstruction proc = doc.CreateProcessingInstruction("xml-stylesheet", "type=\"text/lsb\" href=\"test.lsb\"");
            //doc.AppendChild(proc);
            //XmlDocumentType doctype = doc.CreateDocumentType("server", null, null, null);
            //doc.AppendChild(doctype);
            XmlElement rootElement = doc.CreateElement(xs_root);
            rootElement.SetAttribute(xs_nameAttr, di.Parent.Name);
            XmlElement serverListElement = doc.CreateElement(xs_serverList);
            serverListElement.SetAttribute(xs_countAttr,"0");
            rootElement.AppendChild(serverListElement);
            doc.AppendChild(rootElement);

            doc.Save(di.FullName + "/" + configFilename);
            return ErrorCode.EC_SUCCESS;
        }
    }
}
