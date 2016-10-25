using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Reflection;

namespace Tzb
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        [DllImport("user32.dll", EntryPoint = "MessageBoxA")]
        static extern int MsgBox(int hWnd, string msg, string caption, int type);
        
        private void B1_Click(object sender, EventArgs e)
        {
            MsgBox(0," 这就是用 DllImport 调用 DLL 弹出的提示框哦！ "," 挑战杯 ",0x30);
        }


        [DllImport("Count.dll")]
        static extern int count(int init);

        [DllImport("Count.dll")]
        static extern int count1(int init);

        [DllImport("idtetity.dll")]
        static extern int identity1(int init);

        private void B2_Click(object sender, EventArgs e)
        {
            MessageBox.Show(" 用 DllImport 调用 DLL 中的 count 函数， \n 传入的实参为 0 ，得到的结果是： " + count(0).ToString(), " 挑战杯 ");
            MessageBox.Show(" 用 DllImport 调用 DLL 中的 count 函数， \n 传入的实参为 10 ，得到的结果是： " + count(10).ToString() + "\n 结果可不是想要的 11 哦！！！ ", " 挑战杯 ");
            MessageBox.Show(" 所得结果表明： \n 用 DllImport 调用 DLL 中的非托管 \n 函数是全局的、静态的函数！！！ ", " 挑战杯 ");
        }

        /// <summary>
        /// 创建一个 dld 类对象
        /// </summary>
        private dld myfun = new dld();

        private void B3_Click(object sender, EventArgs e)
        {
            myfun.LoadDll("Count.dll"); // 加载 "Count.dll"
            myfun.LoadFun("_count@4"); // 调入函数 count, "_count@4" 是它的入口，可通过 Depends 查看
        }

        private void B4_Click(object sender, EventArgs e)
        {
            object[] Parameters = new object[] { (int)0 }; // 实参为 0
            Type[] ParameterTypes = new Type[] { typeof(int) }; // 实参类型为 int
            ModePass[] themode = new ModePass[] { ModePass.ByValue }; // 传送方式为值传
            Type Type_Return = typeof(int); // 返回类型为 int
            // 弹出提示框，显示调用 myfun.Invoke 方法的结果，即调用 count 函数
            MessageBox.Show(" 这是您装载该 Dll 后第 " + myfun.Invoke(Parameters, ParameterTypes, themode, Type_Return).ToString()
            + " 次点击此按钮。 ", " 挑战杯 ");
        }

        private void B5_Click(object sender, EventArgs e)
        {
            myfun.UnLoadDll();
        }

        private object Invoke(string lpFileName, string Namespace, string ClassName, string lpProcName, object[] ObjArray_Parameter)

        {

            try 
            { // 载入程序集

                Assembly MyAssembly=Assembly.LoadFrom(lpFileName);

                Type[] type=MyAssembly.GetTypes();

                foreach(Type t in type)

                {// 查找要调用的命名空间及类

                    if(t.Namespace==Namespace&&t.Name==ClassName)

                    {// 查找要调用的方法并进行调用

                        MethodInfo m=t.GetMethod(lpProcName);

                        if(m!=null)

                        {

                            object o=Activator.CreateInstance(t);

                            return m.Invoke(o,ObjArray_Parameter);

                        }

                        else MessageBox.Show(" 装载出错 !");

                    }

                }

            }//try

            catch(System.NullReferenceException e)

            {

                MessageBox.Show(e.Message);

            }//catch

            return (object)0;

        }// Invoke


        private void B6_Click(object sender, EventArgs e)
        {
            // 显示 count(0) 返回的值
            MessageBox.Show(" 这是您第 " + Invoke("CsCount.dll", "CsCount", "Class1", "count", new object[] { (int)0 }).ToString() + " 次点击此按钮。 ", " 挑战杯 ");

        }

        private ldfs tmp = new ldfs();
        
        private void B7_Click(object sender, EventArgs e)
        {
            // 调用 count(0), 并使用期提示框显示其返回值
            MessageBox.Show(" 这是您第 " + tmp.Invoke("CsCount.dll", "CsCount", "Class1", "count", new object[] { (int)0 }).ToString() + " 次点击此按钮。 ", " 挑战杯 ");

        }

        private void B8_Click(object sender, EventArgs e)
        {
            // 卸载 DLL
            tmp.UnLoadDll();

        }

        [DllImport("idtetity.dll")]
        static extern int identity3(string init);

        private void identity_pic_Click(object sender, EventArgs e)
        {
            if (textBox_Path.Text.ToString()!="") 
            {
                MessageBox.Show(" 识别结果" + identity3(textBox_Path.Text).ToString(), " 识别结果 ");

                if (identity3(textBox_Path.Text).ToString() == "1")
                {
                    identity_result.Text = "有";
                }
                else if (identity3(textBox_Path.Text).ToString() == "0")
                {
                    identity_result.Text = "无";
                }
            }
            else if (textBox_Path.Text.ToString() == "")
            {
                MessageBox.Show("没有选定图片", " 识别结果 ");

            }
                
        }

        private void button2_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "(*.jpg,*.gif,*.bmp,*.png,*.jpeg)|*.JPG;*.GIF;*.BMP;*.PNG;*.JPEG";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                textBox_Path.Text = ofd.FileName;
                Bitmap bmp = new Bitmap(textBox_Path.Text);
                pictureBox_Oraginal.Image = bmp;
            }
        }
    }
}
