using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace EtOcxExDemo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Program.czurForm = this;
        }

        private void CZUR_Load(object sender, EventArgs e)
        {
            //初始化控件变量

            /*
             * 【隐藏网格】对应序号为0， 
             * 【显示网格】对应序号为1，

             * 根据CZURGrid.SelectedIndex调用CZUR_DisplayGrid接口，
             */
            displaygrid = new string[2] { "隐藏网格", "显示网格" };
      
            CZURGrid.DataSource = displaygrid;
            CZURGrid.SelectedIndex = 0;

            /*
             * 【无模式】对应序号为0，
             * 【彩色模式】对应序号为1，
             * 【白纸印章模式】对应序号为2，
             * 【证件底纹模式】对应序号为3，
             * 【黑白模式】对应序号为4，
             * 【灰度模式】对应序号为5，

             * 根据CZURClrmode.SelectedIndex调用CZUR_ClrMode接口
             */
            clrmode = new string[6] { "无模式", "彩色模式", "白纸印章模式", "证件底纹模式", "黑白模式", "灰度模式" };
            CZURClrMode.DataSource = clrmode;
            CZURClrMode.SelectedIndex = 0;

            /*
             * 【不旋转】对应序号为0，
             * 【顺时针旋转90°]对应序号为1，
             * 【顺时针旋转180°】对应序号为2，
             * 【顺时针旋转270°】对应序号为3，
          
             * 根据CZURRatate.SelectedIndex调用CZUR_Rotate接口
             */
            rotate = new string[4] { "不旋转", "顺时针旋转90°", "顺时针旋转180°", "顺时针旋转270°" };
            CZURRatate.DataSource = rotate;
            CZURRatate.SelectedIndex = 0;

            mode = new string[4] { "不处理", "自动裁边", "书籍展平(不拆分)", "书籍展平(拆分)" };
            CZURMode.DataSource = mode;
            CZURMode.SelectedIndex = 0;
        }

        public void Msg(int iUploadCnt, object file1, object file2)
        {
            //对于书籍展平不拆分双页来说，file2为空

            string f1 = file1 as string;
            string f2 = file2 as string;

            string text = "上传文件：" + iUploadCnt + "，图片1：" + f1 + "，图片2：" + f2;

            MessageBox.Show(text);
        }

        //调用EtOcxEx控件中的 CZUR_Initialize 接口
        private void CZUR_Initialize_Click(object sender, EventArgs e)
        {
            /*
             * CZUR_Initialize(...)
             * 参数1：     一个COM组件对象，C#中，可直接传递一个普通的对象
             * 参数2：     日志文件的名称，根据该名称，在注册的EtOcxEx控件所在目录生成对应的日志文件名称
             * 返回值：    0(失败)、1(成功)
            */

            cbObject = new CZURCallback();
            if(0 == axEtOcxEx1.CZUR_Initialize(cbObject, "C#_OOX.log"))
            {
               MessageBox.Show("初始化EtOcxEx资源失败");
            }
        }

        //调用EtOcxEx控件中的 CZUR_Deinitialize 接口
        private void CZUR_Deinitialize_Click(object sender, EventArgs e)
        {
            /*
            * CZUR_Deinitialize(...)
            * 清除调用CZUR_Initialize接口初始化的EtOcxEx资源，该函数没有参数和返回值
           */
            axEtOcxEx1.CZUR_Deinitialize();
        }

        //调用EtOcxEx控件中的 CZUR_Http_URL 接口
        private void CZUR_Http_URL_Click(object sender, EventArgs e)
        {
            string url = HttpURL_Text.Text;
            string name = HttpFile_Text.Text;

            axEtOcxEx1.CZUR_Http_URL(url, name);
        }

        //调用EtOcxEx控件中的 CZUR_Http_User_Pwd 接口
        private void CZUR_Http_User_Pwd_Click(object sender, EventArgs e)
        {
            /*
             * CZUR_Http_User_Pwd(...)
             * 参数1：     http的用户名
             * 参数2：     http的密码
            */
            string user = HttpUser_Text.Text;
            string pwd = HttpPwd_Text.Text;

            axEtOcxEx1.CZUR_Http_User_Pwd(user, pwd);
        }

        //调用EtOcxEx控件中的 CZUR_Http_Form 接口
        private void CZUR_Http_Form_Click(object sender, EventArgs e)
        {
            /*
             * CZUR_Http_Form(...)
             * 参数1：     form中的属性名称
             * 参数2：     form中的属性内容
            */
            string formname = HttpForm_Text.Text;
            string content = HttpContent_Text.Text;
            axEtOcxEx1.CZUR_Http_Form(formname, content);
        }

        //调用EtOcxEx控件中的 CZUR_OpenDevice 接口
        private void CZUR_OpenDevice_Click(object sender, EventArgs e)
        {
            if (0 == axEtOcxEx1.CZUR_OpenDevice())
            {
                 MessageBox.Show("打开设备失败");
            }
        }

        //调用EtOcxEx控件中的 CZUR_CloseDevice 接口
        private void CZUR_CloseDevice_Click(object sender, EventArgs e)
        {
            axEtOcxEx1.CZUR_CloseDevice();
        }

        //调用EtOcxEx控件中的 CZUR_GrabSingleImage 接口
        private void CZUR_GrabSingleImage_Click(object sender, EventArgs e)
        {
            if (0 == axEtOcxEx1.CZUR_GrabSingleImage())
            {
                MessageBox.Show("触发拍照失败");
            }
        }

        //调用EtOcxEx控件中的 CZUR_Path 接口
        private void CZUR_Path_Click(object sender, EventArgs e)
        {
            string path = CZURPath_Text.Text;
            if ("" == path)
            {
                MessageBox.Show("输入的路径有误", "错误");
            }
            else
            {
                //设置图片的保存路径
                axEtOcxEx1.CZUR_Path(path);
            }
        }

        //调用EtOcxEx控件中的 CZUR_DPI 接口
        private void CZUR_DPI_Click(object sender, EventArgs e)
        {
            string text = CZURDPI_Text.Text;

            ushort udpi = 0;
            if (ushort.TryParse(text, out udpi))
            {
                //设置图片的DPI
                axEtOcxEx1.CZUR_DPI(udpi);
            }
            else
            {
                MessageBox.Show("输入的dpi有误", "错误");
            }
        }

        //调用EtOcxEx控件中的 CZUR_Custom 接口
        private void CZUR_Custom_Click(object sender, EventArgs e)
        {
            string prefix = CZURPrefix_Text.Text;

            string text = CUZRNumber_Text.Text;

            int initnumber = 0;
            if(int.TryParse(text, out initnumber))
            {
                //自定义图片的命名规则：图片前缀 + 序号
                axEtOcxEx1.CZUR_Custom(prefix, initnumber);
            }
            else
            {
                MessageBox.Show("输入的起始序号有误", "错误");
            }
        }

        //调用EtOcxEx控件中的 CZUR_Zoom 接口
        private void CZUR_Zoom_Click(object sender, EventArgs e)
        {
            string hortext = HORResolut_Text.Text;
            string verttext = VertResolut_Text.Text;

            int horresolut  = 0;
            int vertresolut = 0;
            if (int.TryParse(hortext, out horresolut) && int.TryParse(verttext, out vertresolut))
            {
                //缩放图片的分辨率，建议， 横向分辨率：纵向分辨率 = 4：3
                axEtOcxEx1.CZUR_Zoom(horresolut, vertresolut);
            }
            else
            {
                MessageBox.Show("输入的分辨率有误", "错误");
            }
        }

        //调用EtOcxEx控件中的 CZUR_Format_Bmp 接口
        private void CZUR_Format_Bmp_Click(object sender, EventArgs e)
        {
            //设置图片的保存格式为bmp，这种格式的图片相对较大
            axEtOcxEx1.CZUR_Format_Bmp();
        }

        //调用EtOcxEx控件中的 CZUR_Format_Jpg 接口
        private void CZUR_Format_Jpg_Click(object sender, EventArgs e)
        {
            string text = JpgQuality_Text.Text;

            int iQuality = 0;
            if (int.TryParse(text, out iQuality))
            {
                if (iQuality >= 0 && iQuality <= 100)
                {
                    //设置图片的保存格式为jpg，支持jpg质量的调整，0~100，该值越大，图片越大，但质量越低
                    axEtOcxEx1.CZUR_Format_Jpg(iQuality);
                }
                else
                {
                    MessageBox.Show("输入的jpg质量有误，应在0~100", "错误");
                }
            }
            else
            {
                MessageBox.Show("输入的jpg质量有误", "错误");
            }
        }

        //调用EtOcxEx控件中的 CZUR_Rotate 接口
        private void ComboRatateDropClosede(object sender, EventArgs e)
        {
            axEtOcxEx1.CZUR_Rotate(CZURRatate.SelectedIndex * 90);
        }

        //调用EtOcxEx控件中的 CZUR_ClrMode 接口
        private void ComboClrModeDropClosed(object sender, EventArgs e)
        {
            axEtOcxEx1.CZUR_ClrMode(CZURClrMode.SelectedIndex);
        }

        //调用EtOcxEx控件中的 CZUR_DisplayGrid 接口
        private void ComboGridDropClosed(object sender, EventArgs e)
        {
            axEtOcxEx1.CZUR_DisplayGrid(CZURGrid.SelectedIndex);
        }

        private void ComboModeDropClosed(object sender, EventArgs e)
        {
            switch (CZURMode.SelectedIndex)
            {
                case 0:
                    {
                        //原图不处理
                        axEtOcxEx1.CZUR_Original();
                    }
                    break;
                case 1:
                    {
                        //自动裁边
                        axEtOcxEx1.CZUR_EdgeCutting();
                    }
                    break;
                case 2:
                    {
                        //书籍展平但不拆分为左图、右图
                        axEtOcxEx1.CZUR_CurveFlatten(0);
                    }
                    break;
                case 3:
                    {
                        //书籍展平并拆分为左图、右图
                        axEtOcxEx1.CZUR_CurveFlatten(1);
                    }
                    break;
            }
        }
    }
}
