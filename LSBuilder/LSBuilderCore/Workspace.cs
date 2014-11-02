using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace LSBuilderCore
{
    public class Workspace
    {
        public bool loaded = false;
        private XmlDocument doc;
        public enum ErrorCode
        {
            EC_SUCCESS = 0x0,
            EC_NO_DATA = 0x1,
            EC_UNKNOWN_ERROR = 0xFFFFFFF 
        };
        public ErrorCode Load(string filename)
        {
            if(!loaded)
            {
                doc = new XmlDocument();
            }
            doc.Load(filename);
            loaded = true;
            return ErrorCode.EC_SUCCESS;
        }

        public ErrorCode Save(string filename)
        {
            if(loaded)
            {
                doc.Save(filename);
                return ErrorCode.EC_SUCCESS;
            }
            return ErrorCode.EC_NO_DATA;
        }

        public ErrorCode Create(string filename)
        {
            if (!loaded)
            {
                doc = new XmlDocument();
            }
            else
            {
                doc.RemoveAll();
            }
            XmlDeclaration decl = doc.CreateXmlDeclaration("1.0", "UTF-8", "yes");
            doc.AppendChild(decl);
            XmlProcessingInstruction proc = doc.CreateProcessingInstruction("xml-stylesheet", "type=\"text/lsb\" href=\"test.lsb\"");
            doc.AppendChild(proc);
            XmlDocumentType doctype = doc.CreateDocumentType("server", null, null, null);
            doc.AppendChild(doctype);
            doc.AppendChild(doc.CreateElement("server"));
            doc.Save(filename);
            return ErrorCode.EC_SUCCESS;
        }
    }
}
