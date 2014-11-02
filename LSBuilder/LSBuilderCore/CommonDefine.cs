using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LSBuilderCore
{
    class CommonDefine
    {
        //CLASS_TYPE
        public const int CT_WORKSPACE = 0x10000;
        public const int CT_SERVER = 0x20000;
        //ERROR_CODE
        public const int EC_SUCCESS = 0x0;
        public const int EC_INVALID = 0x1;
        public const int EC_MISMATCH = 0x2;
        public const int EC_NOT_EXIST = 0x3;
        public const int EC_UNKNOWN_ERROR = 0xFF;

        //xml_string
        public const string xs_root = "Workspace";
        public const string xs_serverList = "ServerList";
        public const string xs_server = "Server";
        public const string xs_nameAttr = "Name";
        public const string xs_countAttr = "Count";
        public const string xs_pathAttr = "Path";
    }
}
