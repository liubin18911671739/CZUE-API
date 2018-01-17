using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace EtOcxExDemo
{
    public class CZURCallback
    {
        public void CZUR_CALLBACK(int iUploadCnt, object file1, object file2)
        {
            //Program.czurForm.Msg(iUploadCnt, file1, file2);
        }

        public void CZUR_PDF_CALLBACK(int iPdfStatus)
        {
            switch (iPdfStatus)
            {
            case 0:
                {
                    //合成pdf成功
                }
                break;
            case 1:
                {
                    //合成pdf失败
                }
                break;
            }
        }
    }
}
