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

        public bool loaded = false;
        private XmlDocument doc = new XmlDocument();
        private DirectoryInfo path;
        private List<Server> serverList = new List<Server>();
        private int serverCount = 0;
        private CMakeSln cmakeFile = new CMakeSln();

        public int Load(string filePath)
        {
            string xmlPath = filePath + "/" + configDir + "/" + configFilename;
            if (!File.Exists(xmlPath))
                return CommonDefine.EC_NOT_EXIST | CommonDefine.CT_WORKSPACE;
      
            doc.Load(xmlPath);
            if (doc.DocumentElement.Name != CommonDefine.xs_root)
            {
                return CommonDefine.EC_MISMATCH | CommonDefine.CT_WORKSPACE;
            }
            path = new DirectoryInfo(filePath);
            if (path.Name != doc.DocumentElement.GetAttribute(CommonDefine.xs_nameAttr))
                return CommonDefine.EC_MISMATCH | CommonDefine.CT_WORKSPACE;
            cmakeFile.Load(filePath);

            serverCount = 0;
            foreach (XmlElement listNode in doc.DocumentElement.GetElementsByTagName(CommonDefine.xs_serverList))
            {
                serverCount += int.Parse(listNode.GetAttribute(CommonDefine.xs_countAttr));
                foreach (XmlElement serverNode in listNode.GetElementsByTagName(CommonDefine.xs_server))
                {
                    string serverName = serverNode.GetAttribute(CommonDefine.xs_nameAttr);
                    string serverPath = serverNode.GetAttribute(CommonDefine.xs_pathAttr);
                    Server server = new Server(this);
                    server.Load(serverName, serverPath);
                }
            }
            loaded = true;
            return CommonDefine.EC_SUCCESS;
        }

        public int Save()
        {
            if(loaded)
            {
                doc.RemoveAll();
                XmlDeclaration decl = doc.CreateXmlDeclaration("1.0", null, null);
                doc.AppendChild(decl);
                //XmlProcessingInstruction proc = doc.CreateProcessingInstruction("xml-stylesheet", "type=\"text/lsb\" href=\"test.lsb\"");
                //doc.AppendChild(proc);
                //XmlDocumentType doctype = doc.CreateDocumentType("server", null, null, null);
                //doc.AppendChild(doctype);
                XmlElement rootElement = doc.CreateElement(CommonDefine.xs_root);
                rootElement.SetAttribute(CommonDefine.xs_nameAttr, path.Name);
                XmlElement serverListElement = doc.CreateElement(CommonDefine.xs_serverList);
                serverListElement.SetAttribute(CommonDefine.xs_countAttr, serverCount.ToString());
                foreach(Server server in serverList)
                {
                    XmlElement serverElement = doc.CreateElement(CommonDefine.xs_server);
                    serverElement.SetAttribute(CommonDefine.xs_nameAttr,server.Name);
                    serverElement.SetAttribute(CommonDefine.xs_pathAttr, server.Path);
                    serverListElement.AppendChild(serverElement);
                }
                rootElement.AppendChild(serverListElement);
                doc.AppendChild(rootElement);

                doc.Save(path.FullName + "/" + configDir + "/" + configFilename);
                return CommonDefine.EC_SUCCESS;
            }
            return CommonDefine.EC_INVALID | CommonDefine.CT_WORKSPACE;
        }

        public int Create(string filepath)
        {
            if(!Directory.Exists(filepath))
                return CommonDefine.EC_NOT_EXIST | CommonDefine.CT_WORKSPACE;
            string configPath = filepath + "/" + configDir;
            if(Directory.Exists(configPath))
                Directory.Delete(configPath,true);

            DirectoryInfo di = Directory.CreateDirectory(configPath);
            path = di.Parent;

            loaded = true;
            return Save();
        }

        public int OnCreateServer(Server server)
        {
            if (!loaded)
                return CommonDefine.EC_INVALID | CommonDefine.CT_WORKSPACE;
            serverList.Add(server);
            serverCount++;
            return CommonDefine.EC_SUCCESS;
        }

    }
}
