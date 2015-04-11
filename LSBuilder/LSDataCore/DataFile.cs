using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace LSDataCore
{
    public class DataFile
    {
        protected string path;
        protected bool loaded = false;
        protected uint version;
        public int Load(string filePath)
        {
            path = filePath;
            if (!File.Exists(path + "/LSData.dat"))
                return CommonDefine.EC_NOT_EXIST | CommonDefine.CT_DATAFILE;
            FileStream file = new FileStream(path + "/LSData.dat",FileMode.Open,FileAccess.Read);
            using (BinaryReader binary = new BinaryReader(file))
            {
                try
                {
                    uint version = binary.ReadUInt32();
                    if (version != CommonDefine.VERSION)
                    {
                        binary.Close();
                        return CommonDefine.EC_MISMATCH | CommonDefine.CT_DATAFILE;
                    }

                    while(binary.BaseStream.Position < binary.BaseStream.Length)
                    {
                        int tableSize = binary.ReadInt32();
                        if (tableSize > 0)
                        {
                            int dataSize = binary.ReadInt32();
                            byte[] buffer = binary.ReadBytes(dataSize);
                        }
                    }
                }
                catch(System.Exception e)
                {
                    binary.Close();
                    return CommonDefine.EC_UNKNOWN_ERROR | CommonDefine.CT_DATAFILE;
                }
            }
            return 0;
        }
    }
}
