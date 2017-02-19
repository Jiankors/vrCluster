namespace AppRunner
{
	partial class Form1
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.listboxApp = new System.Windows.Forms.ListBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.listboxNode = new System.Windows.Forms.CheckedListBox();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.listboxConfig = new System.Windows.Forms.ListBox();
			this.groupBox4 = new System.Windows.Forms.GroupBox();
			this.btnReloadCameras = new System.Windows.Forms.Button();
			this.btnReloadNodes = new System.Windows.Forms.Button();
			this.btnReloadConfigs = new System.Windows.Forms.Button();
			this.btnReloadApplication = new System.Windows.Forms.Button();
			this.groupBox5 = new System.Windows.Forms.GroupBox();
			this.gbLoggingOption = new System.Windows.Forms.GroupBox();
			this.btnLogLevelSetup = new System.Windows.Forms.Button();
			this.cbUseCustomLogFileName = new System.Windows.Forms.CheckBox();
			this.cbOptionForceLogFlush = new System.Windows.Forms.CheckBox();
			this.tbCustomLogFilename = new System.Windows.Forms.TextBox();
			this.cbOptionLoggingEnabled = new System.Windows.Forms.CheckBox();
			this.groupBox7 = new System.Windows.Forms.GroupBox();
			this.cbLogToolRemoveAfterZip = new System.Windows.Forms.CheckBox();
			this.cbLogToolZip = new System.Windows.Forms.CheckBox();
			this.btnCleanLogs = new System.Windows.Forms.Button();
			this.btnCollectLogFiles = new System.Windows.Forms.Button();
			this.groupBox14 = new System.Windows.Forms.GroupBox();
			this.cbDefaultCamera = new System.Windows.Forms.ComboBox();
			this.cbUseSelectedCamera = new System.Windows.Forms.CheckBox();
			this.groupBox8 = new System.Windows.Forms.GroupBox();
			this.cbOptionStereoEnabled = new System.Windows.Forms.CheckBox();
			this.cbOptionFixedSeed = new System.Windows.Forms.CheckBox();
			this.cbOptionUseAllAvailableCores = new System.Windows.Forms.CheckBox();
			this.cbDebugRun = new System.Windows.Forms.CheckBox();
			this.cbOptionNoTexturesStreaming = new System.Windows.Forms.CheckBox();
			this.cbOptionNoSound = new System.Windows.Forms.CheckBox();
			this.groupBox10 = new System.Windows.Forms.GroupBox();
			this.tbAdditionalParams = new System.Windows.Forms.TextBox();
			this.groupBox6 = new System.Windows.Forms.GroupBox();
			this.brOptionOpenGLv4 = new System.Windows.Forms.RadioButton();
			this.brOptionOpenGLv3 = new System.Windows.Forms.RadioButton();
			this.groupBox9 = new System.Windows.Forms.GroupBox();
			this.btnStatus = new System.Windows.Forms.Button();
			this.btnKill = new System.Windows.Forms.Button();
			this.btnRun = new System.Windows.Forms.Button();
			this.guiToolTip = new System.Windows.Forms.ToolTip(this.components);
			this.groupBox11 = new System.Windows.Forms.GroupBox();
			this.btnCommandCopy = new System.Windows.Forms.Button();
			this.tbCommand = new System.Windows.Forms.TextBox();
			this.groupBox12 = new System.Windows.Forms.GroupBox();
			this.btnConsoleClear = new System.Windows.Forms.Button();
			this.btnConsoleCopy = new System.Windows.Forms.Button();
			this.tbConsole = new System.Windows.Forms.TextBox();
			this.statusStrip1 = new System.Windows.Forms.StatusStrip();
			this.performanceCounter1 = new System.Diagnostics.PerformanceCounter();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.groupBox3.SuspendLayout();
			this.groupBox4.SuspendLayout();
			this.groupBox5.SuspendLayout();
			this.gbLoggingOption.SuspendLayout();
			this.groupBox7.SuspendLayout();
			this.groupBox14.SuspendLayout();
			this.groupBox8.SuspendLayout();
			this.groupBox10.SuspendLayout();
			this.groupBox6.SuspendLayout();
			this.groupBox9.SuspendLayout();
			this.groupBox11.SuspendLayout();
			this.groupBox12.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.performanceCounter1)).BeginInit();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.listboxApp);
			this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox1.Location = new System.Drawing.Point(15, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(443, 119);
			this.groupBox1.TabIndex = 7;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Applications : ";
			// 
			// listboxApp
			// 
			this.listboxApp.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listboxApp.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.listboxApp.FormattingEnabled = true;
			this.listboxApp.Location = new System.Drawing.Point(6, 19);
			this.listboxApp.Name = "listboxApp";
			this.listboxApp.ScrollAlwaysVisible = true;
			this.listboxApp.Size = new System.Drawing.Size(431, 95);
			this.listboxApp.TabIndex = 3;
			this.listboxApp.SelectedIndexChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.listboxNode);
			this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox2.Location = new System.Drawing.Point(465, 12);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(160, 203);
			this.groupBox2.TabIndex = 8;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Active Nodes : ";
			// 
			// listboxNode
			// 
			this.listboxNode.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listboxNode.CheckOnClick = true;
			this.listboxNode.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.listboxNode.FormattingEnabled = true;
			this.listboxNode.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.listboxNode.Location = new System.Drawing.Point(9, 19);
			this.listboxNode.Name = "listboxNode";
			this.listboxNode.ScrollAlwaysVisible = true;
			this.listboxNode.Size = new System.Drawing.Size(145, 169);
			this.listboxNode.TabIndex = 4;
			this.listboxNode.ThreeDCheckBoxes = true;
			// 
			// groupBox3
			// 
			this.groupBox3.Controls.Add(this.listboxConfig);
			this.groupBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox3.Location = new System.Drawing.Point(15, 137);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(443, 78);
			this.groupBox3.TabIndex = 9;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "Config files : ";
			// 
			// listboxConfig
			// 
			this.listboxConfig.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.listboxConfig.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.listboxConfig.FormattingEnabled = true;
			this.listboxConfig.Location = new System.Drawing.Point(6, 19);
			this.listboxConfig.Name = "listboxConfig";
			this.listboxConfig.ScrollAlwaysVisible = true;
			this.listboxConfig.Size = new System.Drawing.Size(431, 56);
			this.listboxConfig.TabIndex = 3;
			this.listboxConfig.SelectedIndexChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// groupBox4
			// 
			this.groupBox4.Controls.Add(this.btnReloadCameras);
			this.groupBox4.Controls.Add(this.btnReloadNodes);
			this.groupBox4.Controls.Add(this.btnReloadConfigs);
			this.groupBox4.Controls.Add(this.btnReloadApplication);
			this.groupBox4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox4.Location = new System.Drawing.Point(15, 221);
			this.groupBox4.Name = "groupBox4";
			this.groupBox4.Size = new System.Drawing.Size(314, 51);
			this.groupBox4.TabIndex = 11;
			this.groupBox4.TabStop = false;
			this.groupBox4.Text = "Reload list of : ";
			// 
			// btnReloadCameras
			// 
			this.btnReloadCameras.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnReloadCameras.Location = new System.Drawing.Point(235, 19);
			this.btnReloadCameras.Name = "btnReloadCameras";
			this.btnReloadCameras.Size = new System.Drawing.Size(73, 24);
			this.btnReloadCameras.TabIndex = 15;
			this.btnReloadCameras.Text = "Cameras";
			this.btnReloadCameras.UseVisualStyleBackColor = true;
			this.btnReloadCameras.Click += new System.EventHandler(this.btnReloadCameras_Click);
			// 
			// btnReloadNodes
			// 
			this.btnReloadNodes.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnReloadNodes.Location = new System.Drawing.Point(82, 19);
			this.btnReloadNodes.Name = "btnReloadNodes";
			this.btnReloadNodes.Size = new System.Drawing.Size(72, 24);
			this.btnReloadNodes.TabIndex = 13;
			this.btnReloadNodes.Text = "Nodes";
			this.btnReloadNodes.UseVisualStyleBackColor = true;
			this.btnReloadNodes.Click += new System.EventHandler(this.btnReloadNodes_Click);
			// 
			// btnReloadConfigs
			// 
			this.btnReloadConfigs.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnReloadConfigs.Location = new System.Drawing.Point(157, 19);
			this.btnReloadConfigs.Name = "btnReloadConfigs";
			this.btnReloadConfigs.Size = new System.Drawing.Size(72, 24);
			this.btnReloadConfigs.TabIndex = 12;
			this.btnReloadConfigs.Text = "Configs";
			this.btnReloadConfigs.UseVisualStyleBackColor = true;
			this.btnReloadConfigs.Click += new System.EventHandler(this.btnReloadConfigs_Click);
			// 
			// btnReloadApplication
			// 
			this.btnReloadApplication.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnReloadApplication.Location = new System.Drawing.Point(6, 19);
			this.btnReloadApplication.Name = "btnReloadApplication";
			this.btnReloadApplication.Size = new System.Drawing.Size(73, 24);
			this.btnReloadApplication.TabIndex = 11;
			this.btnReloadApplication.Text = "Applications";
			this.btnReloadApplication.UseVisualStyleBackColor = true;
			this.btnReloadApplication.Click += new System.EventHandler(this.btnReloadApplication_Click);
			// 
			// groupBox5
			// 
			this.groupBox5.Controls.Add(this.gbLoggingOption);
			this.groupBox5.Controls.Add(this.cbOptionLoggingEnabled);
			this.groupBox5.Controls.Add(this.groupBox7);
			this.groupBox5.Controls.Add(this.groupBox14);
			this.groupBox5.Controls.Add(this.groupBox8);
			this.groupBox5.Controls.Add(this.groupBox6);
			this.groupBox5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox5.Location = new System.Drawing.Point(12, 278);
			this.groupBox5.Name = "groupBox5";
			this.groupBox5.Size = new System.Drawing.Size(613, 244);
			this.groupBox5.TabIndex = 12;
			this.groupBox5.TabStop = false;
			this.groupBox5.Text = "Options : ";
			// 
			// gbLoggingOption
			// 
			this.gbLoggingOption.Controls.Add(this.btnLogLevelSetup);
			this.gbLoggingOption.Controls.Add(this.cbUseCustomLogFileName);
			this.gbLoggingOption.Controls.Add(this.cbOptionForceLogFlush);
			this.gbLoggingOption.Controls.Add(this.tbCustomLogFilename);
			this.gbLoggingOption.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.gbLoggingOption.Location = new System.Drawing.Point(85, 71);
			this.gbLoggingOption.Name = "gbLoggingOption";
			this.gbLoggingOption.Size = new System.Drawing.Size(269, 66);
			this.gbLoggingOption.TabIndex = 25;
			this.gbLoggingOption.TabStop = false;
			this.gbLoggingOption.Text = "Logging options : ";
			// 
			// btnLogLevelSetup
			// 
			this.btnLogLevelSetup.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnLogLevelSetup.Location = new System.Drawing.Point(153, 38);
			this.btnLogLevelSetup.Name = "btnLogLevelSetup";
			this.btnLogLevelSetup.Size = new System.Drawing.Size(110, 23);
			this.btnLogLevelSetup.TabIndex = 10;
			this.btnLogLevelSetup.Text = "Log Level Setup";
			this.btnLogLevelSetup.UseVisualStyleBackColor = true;
			this.btnLogLevelSetup.Click += new System.EventHandler(this.btnLogLevelSetup_Click);
			// 
			// cbUseCustomLogFileName
			// 
			this.cbUseCustomLogFileName.AutoSize = true;
			this.cbUseCustomLogFileName.Checked = true;
			this.cbUseCustomLogFileName.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbUseCustomLogFileName.Location = new System.Drawing.Point(6, 19);
			this.cbUseCustomLogFileName.Name = "cbUseCustomLogFileName";
			this.cbUseCustomLogFileName.Size = new System.Drawing.Size(148, 17);
			this.cbUseCustomLogFileName.TabIndex = 9;
			this.cbUseCustomLogFileName.Text = "Use custom LogFile-name";
			this.cbUseCustomLogFileName.UseVisualStyleBackColor = true;
			this.cbUseCustomLogFileName.CheckedChanged += new System.EventHandler(this.SetEnableUseCustomLogFileName);
			// 
			// cbOptionForceLogFlush
			// 
			this.cbOptionForceLogFlush.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cbOptionForceLogFlush.Location = new System.Drawing.Point(160, 11);
			this.cbOptionForceLogFlush.Name = "cbOptionForceLogFlush";
			this.cbOptionForceLogFlush.Size = new System.Drawing.Size(103, 32);
			this.cbOptionForceLogFlush.TabIndex = 6;
			this.cbOptionForceLogFlush.Text = "Force Log Flush";
			this.cbOptionForceLogFlush.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.guiToolTip.SetToolTip(this.cbOptionForceLogFlush, "Force a log flush after each line.");
			this.cbOptionForceLogFlush.UseVisualStyleBackColor = true;
			this.cbOptionForceLogFlush.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// tbCustomLogFilename
			// 
			this.tbCustomLogFilename.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.tbCustomLogFilename.Location = new System.Drawing.Point(6, 40);
			this.tbCustomLogFilename.Name = "tbCustomLogFilename";
			this.tbCustomLogFilename.Size = new System.Drawing.Size(141, 20);
			this.tbCustomLogFilename.TabIndex = 1;
			this.tbCustomLogFilename.Text = "logFilename.log";
			this.tbCustomLogFilename.TextChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// cbOptionLoggingEnabled
			// 
			this.cbOptionLoggingEnabled.Checked = true;
			this.cbOptionLoggingEnabled.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbOptionLoggingEnabled.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cbOptionLoggingEnabled.Location = new System.Drawing.Point(6, 71);
			this.cbOptionLoggingEnabled.Name = "cbOptionLoggingEnabled";
			this.cbOptionLoggingEnabled.Size = new System.Drawing.Size(67, 66);
			this.cbOptionLoggingEnabled.TabIndex = 24;
			this.cbOptionLoggingEnabled.Text = "Logging options enabled";
			this.cbOptionLoggingEnabled.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.cbOptionLoggingEnabled.UseVisualStyleBackColor = true;
			this.cbOptionLoggingEnabled.CheckedChanged += new System.EventHandler(this.SetEnableLoggingOptions);
			// 
			// groupBox7
			// 
			this.groupBox7.Controls.Add(this.cbLogToolRemoveAfterZip);
			this.groupBox7.Controls.Add(this.cbLogToolZip);
			this.groupBox7.Controls.Add(this.btnCleanLogs);
			this.groupBox7.Controls.Add(this.btnCollectLogFiles);
			this.groupBox7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.groupBox7.Location = new System.Drawing.Point(360, 19);
			this.groupBox7.Name = "groupBox7";
			this.groupBox7.Size = new System.Drawing.Size(247, 118);
			this.groupBox7.TabIndex = 19;
			this.groupBox7.TabStop = false;
			this.groupBox7.Text = "Log Tools : ";
			// 
			// cbLogToolRemoveAfterZip
			// 
			this.cbLogToolRemoveAfterZip.AutoSize = true;
			this.cbLogToolRemoveAfterZip.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.cbLogToolRemoveAfterZip.Location = new System.Drawing.Point(112, 52);
			this.cbLogToolRemoveAfterZip.Name = "cbLogToolRemoveAfterZip";
			this.cbLogToolRemoveAfterZip.Size = new System.Drawing.Size(129, 17);
			this.cbLogToolRemoveAfterZip.TabIndex = 14;
			this.cbLogToolRemoveAfterZip.Text = "Remove files after Zip";
			this.cbLogToolRemoveAfterZip.UseVisualStyleBackColor = true;
			// 
			// cbLogToolZip
			// 
			this.cbLogToolZip.AutoSize = true;
			this.cbLogToolZip.Checked = true;
			this.cbLogToolZip.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbLogToolZip.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.cbLogToolZip.Location = new System.Drawing.Point(6, 52);
			this.cbLogToolZip.Name = "cbLogToolZip";
			this.cbLogToolZip.Size = new System.Drawing.Size(63, 17);
			this.cbLogToolZip.TabIndex = 13;
			this.cbLogToolZip.Text = "Zip logs";
			this.cbLogToolZip.UseVisualStyleBackColor = true;
			this.cbLogToolZip.CheckedChanged += new System.EventHandler(this.cbLogToolZip_CheckedChanged);
			// 
			// btnCleanLogs
			// 
			this.btnCleanLogs.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.btnCleanLogs.Location = new System.Drawing.Point(152, 90);
			this.btnCleanLogs.Name = "btnCleanLogs";
			this.btnCleanLogs.Size = new System.Drawing.Size(89, 22);
			this.btnCleanLogs.TabIndex = 12;
			this.btnCleanLogs.Text = "Clean all logs";
			this.btnCleanLogs.UseVisualStyleBackColor = true;
			this.btnCleanLogs.Click += new System.EventHandler(this.btnCleanLogs_Click);
			// 
			// btnCollectLogFiles
			// 
			this.btnCollectLogFiles.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.btnCollectLogFiles.Location = new System.Drawing.Point(6, 19);
			this.btnCollectLogFiles.Name = "btnCollectLogFiles";
			this.btnCollectLogFiles.Size = new System.Drawing.Size(235, 27);
			this.btnCollectLogFiles.TabIndex = 11;
			this.btnCollectLogFiles.Text = "Collect logs from all nodes to local folder";
			this.btnCollectLogFiles.UseVisualStyleBackColor = true;
			this.btnCollectLogFiles.Click += new System.EventHandler(this.btnCollectLogFiles_Click);
			// 
			// groupBox14
			// 
			this.groupBox14.Controls.Add(this.cbDefaultCamera);
			this.groupBox14.Controls.Add(this.cbUseSelectedCamera);
			this.groupBox14.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox14.Location = new System.Drawing.Point(160, 19);
			this.groupBox14.Name = "groupBox14";
			this.groupBox14.Size = new System.Drawing.Size(194, 45);
			this.groupBox14.TabIndex = 23;
			this.groupBox14.TabStop = false;
			this.groupBox14.Text = "Default Camera : ";
			// 
			// cbDefaultCamera
			// 
			this.cbDefaultCamera.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cbDefaultCamera.Items.AddRange(new object[] {
            "camera_static",
            "camera_dynamic"});
			this.cbDefaultCamera.Location = new System.Drawing.Point(76, 17);
			this.cbDefaultCamera.Name = "cbDefaultCamera";
			this.cbDefaultCamera.Size = new System.Drawing.Size(103, 21);
			this.cbDefaultCamera.TabIndex = 24;
			this.cbDefaultCamera.SelectedIndexChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// cbUseSelectedCamera
			// 
			this.cbUseSelectedCamera.AutoSize = true;
			this.cbUseSelectedCamera.Checked = true;
			this.cbUseSelectedCamera.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbUseSelectedCamera.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cbUseSelectedCamera.Location = new System.Drawing.Point(6, 19);
			this.cbUseSelectedCamera.Name = "cbUseSelectedCamera";
			this.cbUseSelectedCamera.Size = new System.Drawing.Size(70, 17);
			this.cbUseSelectedCamera.TabIndex = 23;
			this.cbUseSelectedCamera.Text = "Use this :";
			this.cbUseSelectedCamera.UseVisualStyleBackColor = true;
			this.cbUseSelectedCamera.CheckedChanged += new System.EventHandler(this.SetEnableUseCamera);
			// 
			// groupBox8
			// 
			this.groupBox8.Controls.Add(this.cbOptionStereoEnabled);
			this.groupBox8.Controls.Add(this.cbOptionFixedSeed);
			this.groupBox8.Controls.Add(this.cbOptionUseAllAvailableCores);
			this.groupBox8.Controls.Add(this.cbDebugRun);
			this.groupBox8.Controls.Add(this.cbOptionNoTexturesStreaming);
			this.groupBox8.Controls.Add(this.cbOptionNoSound);
			this.groupBox8.Controls.Add(this.groupBox10);
			this.groupBox8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox8.Location = new System.Drawing.Point(6, 143);
			this.groupBox8.Name = "groupBox8";
			this.groupBox8.Size = new System.Drawing.Size(601, 95);
			this.groupBox8.TabIndex = 11;
			this.groupBox8.TabStop = false;
			this.groupBox8.Text = "Misc : ";
			// 
			// cbOptionStereoEnabled
			// 
			this.cbOptionStereoEnabled.AutoSize = true;
			this.cbOptionStereoEnabled.Checked = true;
			this.cbOptionStereoEnabled.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbOptionStereoEnabled.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cbOptionStereoEnabled.Location = new System.Drawing.Point(6, 19);
			this.cbOptionStereoEnabled.Name = "cbOptionStereoEnabled";
			this.cbOptionStereoEnabled.Size = new System.Drawing.Size(98, 17);
			this.cbOptionStereoEnabled.TabIndex = 22;
			this.cbOptionStereoEnabled.Text = "Stereo enabled";
			this.cbOptionStereoEnabled.UseVisualStyleBackColor = true;
			this.cbOptionStereoEnabled.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// cbOptionFixedSeed
			// 
			this.cbOptionFixedSeed.AutoSize = true;
			this.cbOptionFixedSeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cbOptionFixedSeed.Location = new System.Drawing.Point(331, 19);
			this.cbOptionFixedSeed.Name = "cbOptionFixedSeed";
			this.cbOptionFixedSeed.Size = new System.Drawing.Size(79, 17);
			this.cbOptionFixedSeed.TabIndex = 14;
			this.cbOptionFixedSeed.Tag = "";
			this.cbOptionFixedSeed.Text = "Fixed Seed";
			this.guiToolTip.SetToolTip(this.cbOptionFixedSeed, "Initialize the random number generator with a fixed value, 0.");
			this.cbOptionFixedSeed.UseVisualStyleBackColor = true;
			this.cbOptionFixedSeed.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// cbOptionUseAllAvailableCores
			// 
			this.cbOptionUseAllAvailableCores.AutoSize = true;
			this.cbOptionUseAllAvailableCores.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cbOptionUseAllAvailableCores.Location = new System.Drawing.Point(190, 19);
			this.cbOptionUseAllAvailableCores.Name = "cbOptionUseAllAvailableCores";
			this.cbOptionUseAllAvailableCores.Size = new System.Drawing.Size(135, 17);
			this.cbOptionUseAllAvailableCores.TabIndex = 13;
			this.cbOptionUseAllAvailableCores.Text = "Use All Available Cores";
			this.guiToolTip.SetToolTip(this.cbOptionUseAllAvailableCores, "Force the use of all available cores on the target platform.");
			this.cbOptionUseAllAvailableCores.UseVisualStyleBackColor = true;
			this.cbOptionUseAllAvailableCores.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// cbDebugRun
			// 
			this.cbDebugRun.AutoSize = true;
			this.cbDebugRun.Checked = true;
			this.cbDebugRun.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbDebugRun.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.cbDebugRun.ForeColor = System.Drawing.Color.Red;
			this.cbDebugRun.Location = new System.Drawing.Point(436, 72);
			this.cbDebugRun.Name = "cbDebugRun";
			this.cbDebugRun.Size = new System.Drawing.Size(159, 17);
			this.cbDebugRun.TabIndex = 17;
			this.cbDebugRun.Text = "Run application with params";
			this.cbDebugRun.UseVisualStyleBackColor = true;
			this.cbDebugRun.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// cbOptionNoTexturesStreaming
			// 
			this.cbOptionNoTexturesStreaming.AutoSize = true;
			this.cbOptionNoTexturesStreaming.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cbOptionNoTexturesStreaming.Location = new System.Drawing.Point(416, 19);
			this.cbOptionNoTexturesStreaming.Name = "cbOptionNoTexturesStreaming";
			this.cbOptionNoTexturesStreaming.Size = new System.Drawing.Size(129, 17);
			this.cbOptionNoTexturesStreaming.TabIndex = 11;
			this.cbOptionNoTexturesStreaming.Text = "No Texture Streaming";
			this.guiToolTip.SetToolTip(this.cbOptionNoTexturesStreaming, "Disable texture streaming. Highest quality textures are always loaded.");
			this.cbOptionNoTexturesStreaming.UseVisualStyleBackColor = true;
			this.cbOptionNoTexturesStreaming.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// cbOptionNoSound
			// 
			this.cbOptionNoSound.AutoSize = true;
			this.cbOptionNoSound.Checked = true;
			this.cbOptionNoSound.CheckState = System.Windows.Forms.CheckState.Checked;
			this.cbOptionNoSound.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cbOptionNoSound.Location = new System.Drawing.Point(110, 19);
			this.cbOptionNoSound.Name = "cbOptionNoSound";
			this.cbOptionNoSound.Size = new System.Drawing.Size(74, 17);
			this.cbOptionNoSound.TabIndex = 10;
			this.cbOptionNoSound.Text = "No Sound";
			this.guiToolTip.SetToolTip(this.cbOptionNoSound, " Disable any sound output from the engine.");
			this.cbOptionNoSound.UseVisualStyleBackColor = true;
			this.cbOptionNoSound.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// groupBox10
			// 
			this.groupBox10.Controls.Add(this.tbAdditionalParams);
			this.groupBox10.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox10.Location = new System.Drawing.Point(6, 43);
			this.groupBox10.Name = "groupBox10";
			this.groupBox10.Size = new System.Drawing.Size(417, 46);
			this.groupBox10.TabIndex = 4;
			this.groupBox10.TabStop = false;
			this.groupBox10.Text = "Additional command line params : ";
			// 
			// tbAdditionalParams
			// 
			this.tbAdditionalParams.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.tbAdditionalParams.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.tbAdditionalParams.Location = new System.Drawing.Point(6, 19);
			this.tbAdditionalParams.Name = "tbAdditionalParams";
			this.tbAdditionalParams.Size = new System.Drawing.Size(405, 20);
			this.tbAdditionalParams.TabIndex = 7;
			this.tbAdditionalParams.TextChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// groupBox6
			// 
			this.groupBox6.Controls.Add(this.brOptionOpenGLv4);
			this.groupBox6.Controls.Add(this.brOptionOpenGLv3);
			this.groupBox6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox6.Location = new System.Drawing.Point(7, 19);
			this.groupBox6.Name = "groupBox6";
			this.groupBox6.Size = new System.Drawing.Size(147, 46);
			this.groupBox6.TabIndex = 0;
			this.groupBox6.TabStop = false;
			this.groupBox6.Text = "OpenGL : ";
			// 
			// brOptionOpenGLv4
			// 
			this.brOptionOpenGLv4.AutoSize = true;
			this.brOptionOpenGLv4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.brOptionOpenGLv4.Location = new System.Drawing.Point(79, 20);
			this.brOptionOpenGLv4.Name = "brOptionOpenGLv4";
			this.brOptionOpenGLv4.Size = new System.Drawing.Size(63, 17);
			this.brOptionOpenGLv4.TabIndex = 1;
			this.brOptionOpenGLv4.TabStop = true;
			this.brOptionOpenGLv4.Text = "opengl4";
			this.brOptionOpenGLv4.UseVisualStyleBackColor = true;
			this.brOptionOpenGLv4.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// brOptionOpenGLv3
			// 
			this.brOptionOpenGLv3.AutoSize = true;
			this.brOptionOpenGLv3.Checked = true;
			this.brOptionOpenGLv3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.brOptionOpenGLv3.Location = new System.Drawing.Point(10, 20);
			this.brOptionOpenGLv3.Name = "brOptionOpenGLv3";
			this.brOptionOpenGLv3.Size = new System.Drawing.Size(63, 17);
			this.brOptionOpenGLv3.TabIndex = 0;
			this.brOptionOpenGLv3.TabStop = true;
			this.brOptionOpenGLv3.Text = "opengl3";
			this.brOptionOpenGLv3.UseVisualStyleBackColor = true;
			this.brOptionOpenGLv3.CheckedChanged += new System.EventHandler(this.EventRefreshRunCommand);
			// 
			// groupBox9
			// 
			this.groupBox9.Controls.Add(this.btnStatus);
			this.groupBox9.Controls.Add(this.btnKill);
			this.groupBox9.Controls.Add(this.btnRun);
			this.groupBox9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox9.Location = new System.Drawing.Point(335, 221);
			this.groupBox9.Name = "groupBox9";
			this.groupBox9.Size = new System.Drawing.Size(290, 51);
			this.groupBox9.TabIndex = 13;
			this.groupBox9.TabStop = false;
			this.groupBox9.Text = "Controls : ";
			// 
			// btnStatus
			// 
			this.btnStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnStatus.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
			this.btnStatus.Location = new System.Drawing.Point(108, 17);
			this.btnStatus.Name = "btnStatus";
			this.btnStatus.Size = new System.Drawing.Size(78, 26);
			this.btnStatus.TabIndex = 15;
			this.btnStatus.Text = "Status";
			this.btnStatus.UseVisualStyleBackColor = true;
			this.btnStatus.Click += new System.EventHandler(this.btnStatus_Click);
			// 
			// btnKill
			// 
			this.btnKill.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnKill.ForeColor = System.Drawing.Color.Red;
			this.btnKill.Location = new System.Drawing.Point(206, 16);
			this.btnKill.Name = "btnKill";
			this.btnKill.Size = new System.Drawing.Size(78, 26);
			this.btnKill.TabIndex = 13;
			this.btnKill.Text = "Kill";
			this.btnKill.UseVisualStyleBackColor = true;
			this.btnKill.Click += new System.EventHandler(this.btnKill_Click);
			// 
			// btnRun
			// 
			this.btnRun.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnRun.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
			this.btnRun.Location = new System.Drawing.Point(6, 17);
			this.btnRun.Name = "btnRun";
			this.btnRun.Size = new System.Drawing.Size(78, 26);
			this.btnRun.TabIndex = 12;
			this.btnRun.Text = "Run";
			this.btnRun.UseVisualStyleBackColor = true;
			this.btnRun.Click += new System.EventHandler(this.btnRun_Click);
			// 
			// groupBox11
			// 
			this.groupBox11.Controls.Add(this.btnCommandCopy);
			this.groupBox11.Controls.Add(this.tbCommand);
			this.groupBox11.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox11.Location = new System.Drawing.Point(12, 528);
			this.groupBox11.Name = "groupBox11";
			this.groupBox11.Size = new System.Drawing.Size(613, 94);
			this.groupBox11.TabIndex = 15;
			this.groupBox11.TabStop = false;
			this.groupBox11.Text = "Command : ";
			// 
			// btnCommandCopy
			// 
			this.btnCommandCopy.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnCommandCopy.Location = new System.Drawing.Point(563, 19);
			this.btnCommandCopy.Name = "btnCommandCopy";
			this.btnCommandCopy.Size = new System.Drawing.Size(44, 69);
			this.btnCommandCopy.TabIndex = 16;
			this.btnCommandCopy.Text = "Copy";
			this.btnCommandCopy.UseVisualStyleBackColor = true;
			this.btnCommandCopy.Click += new System.EventHandler(this.btnCommandCopy_Click);
			// 
			// tbCommand
			// 
			this.tbCommand.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.tbCommand.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.tbCommand.Location = new System.Drawing.Point(6, 19);
			this.tbCommand.Multiline = true;
			this.tbCommand.Name = "tbCommand";
			this.tbCommand.ReadOnly = true;
			this.tbCommand.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.tbCommand.Size = new System.Drawing.Size(550, 69);
			this.tbCommand.TabIndex = 15;
			// 
			// groupBox12
			// 
			this.groupBox12.Controls.Add(this.btnConsoleClear);
			this.groupBox12.Controls.Add(this.btnConsoleCopy);
			this.groupBox12.Controls.Add(this.tbConsole);
			this.groupBox12.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.groupBox12.Location = new System.Drawing.Point(12, 628);
			this.groupBox12.Name = "groupBox12";
			this.groupBox12.Size = new System.Drawing.Size(613, 102);
			this.groupBox12.TabIndex = 16;
			this.groupBox12.TabStop = false;
			this.groupBox12.Text = "Console : ";
			// 
			// btnConsoleClear
			// 
			this.btnConsoleClear.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnConsoleClear.Location = new System.Drawing.Point(562, 62);
			this.btnConsoleClear.Name = "btnConsoleClear";
			this.btnConsoleClear.Size = new System.Drawing.Size(44, 34);
			this.btnConsoleClear.TabIndex = 2;
			this.btnConsoleClear.Text = "Clear";
			this.btnConsoleClear.UseVisualStyleBackColor = true;
			this.btnConsoleClear.Click += new System.EventHandler(this.btnConsoleClear_Click);
			// 
			// btnConsoleCopy
			// 
			this.btnConsoleCopy.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.btnConsoleCopy.Location = new System.Drawing.Point(562, 19);
			this.btnConsoleCopy.Name = "btnConsoleCopy";
			this.btnConsoleCopy.Size = new System.Drawing.Size(44, 34);
			this.btnConsoleCopy.TabIndex = 1;
			this.btnConsoleCopy.Text = "Copy";
			this.btnConsoleCopy.UseVisualStyleBackColor = true;
			this.btnConsoleCopy.Click += new System.EventHandler(this.btnConsoleCopy_Click);
			// 
			// tbConsole
			// 
			this.tbConsole.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.tbConsole.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.tbConsole.Location = new System.Drawing.Point(6, 19);
			this.tbConsole.Multiline = true;
			this.tbConsole.Name = "tbConsole";
			this.tbConsole.ReadOnly = true;
			this.tbConsole.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.tbConsole.Size = new System.Drawing.Size(550, 77);
			this.tbConsole.TabIndex = 0;
			// 
			// statusStrip1
			// 
			this.statusStrip1.Location = new System.Drawing.Point(0, 731);
			this.statusStrip1.Name = "statusStrip1";
			this.statusStrip1.Size = new System.Drawing.Size(637, 22);
			this.statusStrip1.TabIndex = 18;
			this.statusStrip1.Text = "statusStrip1";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(637, 753);
			this.Controls.Add(this.statusStrip1);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox12);
			this.Controls.Add(this.groupBox11);
			this.Controls.Add(this.groupBox9);
			this.Controls.Add(this.groupBox5);
			this.Controls.Add(this.groupBox4);
			this.Controls.Add(this.groupBox3);
			this.Controls.Add(this.groupBox1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MinimumSize = new System.Drawing.Size(16, 725);
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Unreal CAVE Application Runner";
			this.groupBox1.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			this.groupBox3.ResumeLayout(false);
			this.groupBox4.ResumeLayout(false);
			this.groupBox5.ResumeLayout(false);
			this.gbLoggingOption.ResumeLayout(false);
			this.gbLoggingOption.PerformLayout();
			this.groupBox7.ResumeLayout(false);
			this.groupBox7.PerformLayout();
			this.groupBox14.ResumeLayout(false);
			this.groupBox14.PerformLayout();
			this.groupBox8.ResumeLayout(false);
			this.groupBox8.PerformLayout();
			this.groupBox10.ResumeLayout(false);
			this.groupBox10.PerformLayout();
			this.groupBox6.ResumeLayout(false);
			this.groupBox6.PerformLayout();
			this.groupBox9.ResumeLayout(false);
			this.groupBox11.ResumeLayout(false);
			this.groupBox11.PerformLayout();
			this.groupBox12.ResumeLayout(false);
			this.groupBox12.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.ListBox listboxApp;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.CheckedListBox listboxNode;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.ListBox listboxConfig;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.Button btnReloadNodes;
		private System.Windows.Forms.Button btnReloadConfigs;
		private System.Windows.Forms.Button btnReloadApplication;
		private System.Windows.Forms.GroupBox groupBox5;
		private System.Windows.Forms.GroupBox groupBox6;
		private System.Windows.Forms.RadioButton brOptionOpenGLv4;
		private System.Windows.Forms.RadioButton brOptionOpenGLv3;
		private System.Windows.Forms.GroupBox groupBox9;
		private System.Windows.Forms.Button btnKill;
		private System.Windows.Forms.Button btnRun;
		private System.Windows.Forms.GroupBox groupBox10;
		private System.Windows.Forms.TextBox tbAdditionalParams;
		private System.Windows.Forms.GroupBox groupBox8;
		private System.Windows.Forms.CheckBox cbOptionUseAllAvailableCores;
		private System.Windows.Forms.CheckBox cbOptionNoTexturesStreaming;
		private System.Windows.Forms.CheckBox cbOptionNoSound;
		private System.Windows.Forms.CheckBox cbOptionFixedSeed;
		private System.Windows.Forms.ToolTip guiToolTip;
		private System.Windows.Forms.GroupBox groupBox11;
		private System.Windows.Forms.TextBox tbCommand;
		private System.Windows.Forms.GroupBox groupBox12;
		private System.Windows.Forms.TextBox tbConsole;
		private System.Windows.Forms.Button btnStatus;
		private System.Windows.Forms.CheckBox cbDebugRun;
		private System.Windows.Forms.GroupBox groupBox14;
		private System.Windows.Forms.CheckBox cbUseSelectedCamera;
		private System.Windows.Forms.ComboBox cbDefaultCamera;
		private System.Windows.Forms.CheckBox cbOptionStereoEnabled;
		private System.Windows.Forms.GroupBox gbLoggingOption;
		private System.Windows.Forms.CheckBox cbOptionForceLogFlush;
		private System.Windows.Forms.TextBox tbCustomLogFilename;
		private System.Windows.Forms.CheckBox cbOptionLoggingEnabled;
		private System.Windows.Forms.Button btnReloadCameras;
		private System.Windows.Forms.Button btnConsoleClear;
		private System.Windows.Forms.Button btnConsoleCopy;
		private System.Windows.Forms.CheckBox cbUseCustomLogFileName;
		private System.Windows.Forms.Button btnCommandCopy;
		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.GroupBox groupBox7;
		private System.Windows.Forms.Button btnCleanLogs;
		private System.Windows.Forms.Button btnCollectLogFiles;
		private System.Windows.Forms.CheckBox cbLogToolRemoveAfterZip;
		private System.Windows.Forms.CheckBox cbLogToolZip;
		private System.Windows.Forms.Button btnLogLevelSetup;
		private System.Diagnostics.PerformanceCounter performanceCounter1;
	}
}

