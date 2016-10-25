namespace Tzb
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.B1 = new System.Windows.Forms.Button();
            this.B2 = new System.Windows.Forms.Button();
            this.B3 = new System.Windows.Forms.Button();
            this.B4 = new System.Windows.Forms.Button();
            this.B5 = new System.Windows.Forms.Button();
            this.B6 = new System.Windows.Forms.Button();
            this.B7 = new System.Windows.Forms.Button();
            this.B8 = new System.Windows.Forms.Button();
            this.identity_pic = new System.Windows.Forms.Button();
            this.textBox_Path = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.pictureBox_Oraginal = new System.Windows.Forms.PictureBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.identity_result = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Oraginal)).BeginInit();
            this.SuspendLayout();
            // 
            // B1
            // 
            this.B1.Location = new System.Drawing.Point(12, 12);
            this.B1.Name = "B1";
            this.B1.Size = new System.Drawing.Size(260, 23);
            this.B1.TabIndex = 0;
            this.B1.Text = "用DllImport调用DLL弹出提示框";
            this.B1.UseVisualStyleBackColor = true;
            this.B1.Click += new System.EventHandler(this.B1_Click);
            // 
            // B2
            // 
            this.B2.Location = new System.Drawing.Point(12, 41);
            this.B2.Name = "B2";
            this.B2.Size = new System.Drawing.Size(260, 23);
            this.B2.TabIndex = 1;
            this.B2.Text = "用DllImport调用DLL中count函数";
            this.B2.UseVisualStyleBackColor = true;
            this.B2.Click += new System.EventHandler(this.B2_Click);
            // 
            // B3
            // 
            this.B3.Location = new System.Drawing.Point(12, 70);
            this.B3.Name = "B3";
            this.B3.Size = new System.Drawing.Size(260, 23);
            this.B3.TabIndex = 2;
            this.B3.Text = "用LoadLibrary方法装载Count.dll";
            this.B3.UseVisualStyleBackColor = true;
            this.B3.Click += new System.EventHandler(this.B3_Click);
            // 
            // B4
            // 
            this.B4.Location = new System.Drawing.Point(12, 99);
            this.B4.Name = "B4";
            this.B4.Size = new System.Drawing.Size(260, 23);
            this.B4.TabIndex = 3;
            this.B4.Text = "调用count方法";
            this.B4.UseVisualStyleBackColor = true;
            this.B4.Click += new System.EventHandler(this.B4_Click);
            // 
            // B5
            // 
            this.B5.Location = new System.Drawing.Point(12, 128);
            this.B5.Name = "B5";
            this.B5.Size = new System.Drawing.Size(260, 23);
            this.B5.TabIndex = 4;
            this.B5.Text = "卸载Count.dll";
            this.B5.UseVisualStyleBackColor = true;
            this.B5.Click += new System.EventHandler(this.B5_Click);
            // 
            // B6
            // 
            this.B6.Location = new System.Drawing.Point(12, 157);
            this.B6.Name = "B6";
            this.B6.Size = new System.Drawing.Size(260, 23);
            this.B6.TabIndex = 5;
            this.B6.Text = "用Assembly类来动态调用托管DLL";
            this.B6.UseVisualStyleBackColor = true;
            this.B6.Click += new System.EventHandler(this.B6_Click);
            // 
            // B7
            // 
            this.B7.Location = new System.Drawing.Point(12, 186);
            this.B7.Name = "B7";
            this.B7.Size = new System.Drawing.Size(260, 23);
            this.B7.TabIndex = 6;
            this.B7.Text = "ldfs.Invoke调用count";
            this.B7.UseVisualStyleBackColor = true;
            this.B7.Click += new System.EventHandler(this.B7_Click);
            // 
            // B8
            // 
            this.B8.Location = new System.Drawing.Point(12, 215);
            this.B8.Name = "B8";
            this.B8.Size = new System.Drawing.Size(260, 23);
            this.B8.TabIndex = 7;
            this.B8.Text = "UnLoadDll";
            this.B8.UseVisualStyleBackColor = true;
            this.B8.Click += new System.EventHandler(this.B8_Click);
            // 
            // identity_pic
            // 
            this.identity_pic.Location = new System.Drawing.Point(12, 244);
            this.identity_pic.Name = "identity_pic";
            this.identity_pic.Size = new System.Drawing.Size(260, 23);
            this.identity_pic.TabIndex = 8;
            this.identity_pic.Text = "识别图片";
            this.identity_pic.UseVisualStyleBackColor = true;
            this.identity_pic.Click += new System.EventHandler(this.identity_pic_Click);
            // 
            // textBox_Path
            // 
            this.textBox_Path.Location = new System.Drawing.Point(278, 14);
            this.textBox_Path.Name = "textBox_Path";
            this.textBox_Path.ReadOnly = true;
            this.textBox_Path.Size = new System.Drawing.Size(386, 21);
            this.textBox_Path.TabIndex = 9;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(589, 41);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 10;
            this.button2.Text = "浏览";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // pictureBox_Oraginal
            // 
            this.pictureBox_Oraginal.Location = new System.Drawing.Point(278, 70);
            this.pictureBox_Oraginal.Name = "pictureBox_Oraginal";
            this.pictureBox_Oraginal.Size = new System.Drawing.Size(386, 400);
            this.pictureBox_Oraginal.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox_Oraginal.TabIndex = 11;
            this.pictureBox_Oraginal.TabStop = false;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(278, 43);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(117, 21);
            this.textBox1.TabIndex = 12;
            this.textBox1.Text = "识别结果";
            // 
            // identity_result
            // 
            this.identity_result.Location = new System.Drawing.Point(401, 43);
            this.identity_result.Name = "identity_result";
            this.identity_result.ReadOnly = true;
            this.identity_result.Size = new System.Drawing.Size(182, 21);
            this.identity_result.TabIndex = 13;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(676, 482);
            this.Controls.Add(this.identity_result);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.pictureBox_Oraginal);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.textBox_Path);
            this.Controls.Add(this.identity_pic);
            this.Controls.Add(this.B8);
            this.Controls.Add(this.B7);
            this.Controls.Add(this.B6);
            this.Controls.Add(this.B5);
            this.Controls.Add(this.B4);
            this.Controls.Add(this.B3);
            this.Controls.Add(this.B2);
            this.Controls.Add(this.B1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Oraginal)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button B1;
        private System.Windows.Forms.Button B2;
        private System.Windows.Forms.Button B3;
        private System.Windows.Forms.Button B4;
        private System.Windows.Forms.Button B5;
        private System.Windows.Forms.Button B6;
        private System.Windows.Forms.Button B7;
        private System.Windows.Forms.Button B8;
        private System.Windows.Forms.Button identity_pic;
        private System.Windows.Forms.TextBox textBox_Path;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.PictureBox pictureBox_Oraginal;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox identity_result;
    }
}

