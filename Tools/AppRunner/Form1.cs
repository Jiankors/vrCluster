using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Data;
using System.Linq;
using System.Windows.Forms;
using System.IO;
using System.IO.Compression;

//using System.Text;
//using System.Drawing;
//using System.Threading.Tasks;
//using System.ComponentModel;

namespace AppRunner
{
	public partial class Form1 : Form
	{
		// net
		public const int nodeListenerPort = 9777;

		// conf files
		public const string confFileApp     = "appList.conf";
		public const string confFileNodes   = "nodeList.conf";
		public const string confFileConfig  = "confList.conf";
		public const string confFileCameras = "camList.conf";

		public static string logLevels = "";

		private const string logFilenamePrefix = "LogUVR_";

		private const string temporaryZipDir = @"\__dirForZIP\";

		// cluster commands
		private const string cCmdStart  = "start ";  // [space] is required here
		private const string cCmdKill   = "kill ";
		private const string cCmdStatus = "status";

		// run application params\keys
		private const string uvrParamStatic = " -uvr_cluster -fullscreen -nosplash";

		private const string uvrParamConfig        = " uvr_cfg=";     // note:  no need [-] before it
		private const string uvrParamLogFilename   = " log=";         // note:  no need [-] before it
		private const string uvrParamCameraDefault = " uvr_camera=";  // note:  no need [-] before it

		// switches
		private const string uvrParamOpenGL3   = " -opengl3";
		private const string uvrParamOpenGL4   = " -opengl4";
		private const string uvrParamStereo    = " -quad_buffer_stereo -nohmd -vr";
		private const string uvrParamNoSound   = " -nosound";
		private const string uvrParamFixedSeed = " -fixedseed";
		private const string uvrParamNoWrite   = " -nowrite";

		private const string uvrParamForceLogFlush        = " -forcelogflush";
		private const string uvrParamNoTextureStreaming   = " -notexturestreaming";
		private const string uvrParamUseAllAvailableCores = " -useallavailablecores";

		private Form logLevelSetupForm = null;

		public enum ClusterCommandType {
			Run,
			Kill,
			Status,

			COUNT
		}

		public Form1()
		{
			InitializeComponent();

			ReloadConfigLists();

			// create form2
			logLevelSetupForm = new LogLevelSetup();
			// add handler for update after form2 will closed
			logLevelSetupForm.FormClosed += new FormClosedEventHandler(EventRefreshRunCommandFormClosed);
		}

		private void ReloadConfigLists()
		{
			ReloadAppList();
			ReloadConfList();
			ReloadNodeList();
			ReloadCameraList();
		}

		private void btnReloadApplication_Click(object sender, EventArgs e)
		{
			ReloadAppList();
		}

		private void btnReloadConfigs_Click(object sender, EventArgs e)
		{
			ReloadConfList();
		}

		private void btnReloadNodes_Click(object sender, EventArgs e)
		{
			ReloadNodeList();
		}

		private void btnRun_Click(object sender, EventArgs e)
		{
			ClusterCommand(ClusterCommandType.Run);
		}

		private void btnKill_Click(object sender, EventArgs e)
		{
			ClusterCommand(ClusterCommandType.Kill);
		}

		private void btnStatus_Click(object sender, EventArgs e)
		{
			ClusterCommand(ClusterCommandType.Status);
		}

		private void ClusterCommand(ClusterCommandType ccType)
		{
			// get all nodes address
			List<string> nodes = GetNodes();

			if (nodes.Count == 0)
			{
				return;
			}

			// gen.command for cluster nodes
			string clusterCmd = "";

			switch (ccType)
			{
				case ClusterCommandType.Run:
					clusterCmd = cCmdStart + GenerateCmdStartApp();
					break;

				case ClusterCommandType.Kill:
					clusterCmd = cCmdKill + GetSelectedAppPath();
					break;

				case ClusterCommandType.Status:
					clusterCmd = cCmdStatus;
					break;
			}

			// send cmd for each node
			LogInfo("Command for client is :  " + clusterCmd);

			foreach (string node in nodes)
			{
				SendDaemonCommand(node, clusterCmd);
			}
		}

		private void SendDaemonCommand(string nodeAddress, string cmd)
		{
			TcpClient nodeClient = new TcpClient();

			try{
				nodeClient.Connect(nodeAddress, nodeListenerPort);
				NetworkStream networkStream = nodeClient.GetStream();
				StreamWriter clientStreamWriter = new StreamWriter(networkStream);

				if (networkStream.CanWrite)
				{
					clientStreamWriter.Write(cmd);
					clientStreamWriter.Flush();
				}
				else
				{
					LogInfo("Can't write to client on node [" + nodeAddress + "]");
				}

				nodeClient.Close();
			}
			catch(Exception exception)
			{
				LogInfo("Can't connect to node " + nodeAddress + ". EXCEPTION: " + exception.Message);
			}			
		}

		private List<string> GetNodes()
		{
			return listboxNode.CheckedItems.Cast<string>().ToList();
		}

		private List<string> ReadConfigFile(string confFilePath)
		{
			List<string> infoList = new List<string>();

			try
			{
				string[] lines = System.IO.File.ReadAllLines(confFilePath);
				infoList = lines.ToList();

				LogInfo("Read file [" + confFilePath + "] finished.");
			}
			catch(Exception exception)
			{
				LogInfo("Can't read file [" + confFilePath + "]. EXCEPTION: " + exception.Message);
			}			

			return infoList;
		}

		private void ReloadAppList()
		{
			ReloadListBox(confFileApp, listboxApp);
		}

		private void btnReloadCameras_Click(object sender, EventArgs e)
		{
			ReloadCameraList();
		}

		private void ReloadConfList()
		{
			ReloadListBox(confFileConfig, listboxConfig);
		}

		private void ReloadNodeList()
		{
			ReloadCheckedListBox(confFileNodes, listboxNode);
		}

		private void ReloadCameraList()
		{
			ReloadComboBox(confFileCameras, cbDefaultCamera);
		}

		private void ReloadComboBox(string filePath, ComboBox comboBox)
		{
			// save value
			int selectedId = comboBox.SelectedIndex;

			// clear
			comboBox.Items.Clear();

			// get new items
			comboBox.Items.AddRange(ReadConfigFile(filePath).ToArray());

			// set selected first item
			int itemsCount = comboBox.Items.Count;
			if (itemsCount <= 0)
			{
				return;
			}

			if (itemsCount < selectedId + 1 || selectedId < 0)
			{
				// select first
				selectedId = 0;
			}

			// set item selection
			comboBox.SelectedIndex = selectedId;
		}
		private void ReloadListBox(string filePath, ListBox listBox)
		{
			// save value
			int selectedId = listBox.SelectedIndex;

			// clear
			listBox.Items.Clear();

			// get new items
			listBox.Items.AddRange(ReadConfigFile(filePath).ToArray());

			// set selected first item
			int itemsCount = listBox.Items.Count;
			if (itemsCount <= 0)
			{
				return;
			}

			if (itemsCount < selectedId + 1 || selectedId < 0)
			{
				// select first
				selectedId = 0;
			}

			// set item selection
			listBox.SetSelected(selectedId, true);
		}

		private void ReloadCheckedListBox(string filePath, CheckedListBox checkBox)
		{
			// clear
			checkBox.Items.Clear();

			// get new items
			checkBox.Items.AddRange(ReadConfigFile(filePath).ToArray());
			
			// enable all nodes
			for (int i=0; i<checkBox.Items.Count; i++)
			{
				string itemName = checkBox.Items[i].ToString();
				if (itemName.StartsWith("#") == true)
				{
					itemName = itemName.Substring(1, itemName.Length - 1);
					checkBox.Items[i] = itemName;
					checkBox.SetItemChecked(i, false);
				}
				else{
					checkBox.SetItemChecked(i, true);
				}
			}
		}

		private string GetListboxSelected(ListBox listBox)
		{
			if (listBox.Items.Count == 0)
			{
				return "";
			}

			return listBox.SelectedItem.ToString();
		}

		public void EventRefreshRunCommandFormClosed(object sender, FormClosedEventArgs e)
		{
			GenerateCmdStartApp();
		}

		public void EventRefreshRunCommand(object sender, EventArgs e)
		{
			GenerateCmdStartApp();
		}

		public void SetEnableLoggingOptions(object sender, EventArgs e)
		{
			// enable\disable control
			gbLoggingOption.Enabled = cbOptionLoggingEnabled.Checked;

			// update
			GenerateCmdStartApp();
		}

		public void SetEnableUseCamera(object sender, EventArgs e)
		{
			// enable\disable control
			cbDefaultCamera.Enabled = cbUseSelectedCamera.Checked;
			
			// update
			GenerateCmdStartApp();
		}

		public void SetEnableUseCustomLogFileName(object sender, EventArgs e)
		{
			// enable\disable control
			tbCustomLogFilename.Enabled = cbUseCustomLogFileName.Checked;

			// update
			GenerateCmdStartApp();
		}

		public string GetSelectedAppPath()
        {
            return GetListboxSelected(listboxApp);
        }

		private string GenerateCmdStartApp()
		{
            string appPath = GetSelectedAppPath();
            string confString = uvrParamConfig + GetListboxSelected(listboxConfig);

			// switches
			string swOpengl = (brOptionOpenGLv3.Checked) ? uvrParamOpenGL3 : uvrParamOpenGL4;
			string swStereo = (cbOptionStereoEnabled.Checked) ? uvrParamStereo : "";
			string swNoSound = (cbOptionNoSound.Checked) ? uvrParamNoSound : "";
			string swFixedSeed = (cbOptionFixedSeed.Checked) ? uvrParamFixedSeed : "";

			string swNoTextureStreaming = (cbOptionNoTexturesStreaming.Checked) ? uvrParamNoTextureStreaming : "";
			string swUseAllAvailableCores = (cbOptionUseAllAvailableCores.Checked) ? uvrParamUseAllAvailableCores : "";

			// logging params
			bool loggingEnabled = cbOptionLoggingEnabled.Checked;
			string swNoWrite = (loggingEnabled) ? "" : uvrParamNoWrite;

			string swForceLogFlush = "";
			string paramLogFilename = "";

			if (loggingEnabled)
			{
				swForceLogFlush = (cbOptionForceLogFlush.Checked) ? uvrParamForceLogFlush : "";
				// if use custom name for log file = enabled
				if (cbUseCustomLogFileName.Checked)
				{
					paramLogFilename = uvrParamLogFilename + tbCustomLogFilename.Text;
				}
			}

			// camera by default
			string paramDefaultCamera = "";
			if (cbDefaultCamera.Items.Count != 0 && cbUseSelectedCamera.Checked)
			{
				paramDefaultCamera = uvrParamCameraDefault + cbDefaultCamera.SelectedItem;
			}

			// additional params
			string additionalParams =  (tbAdditionalParams.Text.Length != 0) ? " " + tbAdditionalParams.Text : "";

			// cmd
			string cmd = appPath + swOpengl + uvrParamStatic + confString + swStereo + swNoSound + swFixedSeed
								 + swNoTextureStreaming + swUseAllAvailableCores + swForceLogFlush + swNoWrite
								 + paramLogFilename + paramDefaultCamera + additionalParams + logLevels;

			if (cbDebugRun.Checked == false)
			{
				// this is for debug only! Run application WITHOUT any params
				cmd = appPath;
			}

			// set value
			tbCommand.Text = cmd;

			return cmd;
		}

		private void LogInfo(string info)
		{
			if (info == "")
			{
				tbConsole.AppendText("--//----------------------------------------" + Environment.NewLine);
				return;
			}

			tbConsole.AppendText("[" + DateTime.Now.ToString() + "] " + info + Environment.NewLine);
		}

		private void CollectLogFiles()
		{
			List<string> nodes = GetNodes();

			FolderBrowserDialog fbDialog = new FolderBrowserDialog();
			//fbDialog.Description = "Select a folder for save log files from nodes :";
			if (fbDialog.ShowDialog() != DialogResult.OK || nodes.Count == 0)
			{
				return;
			}

			// clean all files except *.zip, *.rar


			// list of new files
			List<string> fileList = new List<string>();

			// copy + rename
			foreach (string node in nodes)
			{
				string logFilename = tbCustomLogFilename.Text;

				string logFilenameSep = (logFilename == string.Empty) ? "" : ("_");

				string srcLogPath = GetLogFolder(node) + logFilename;
				string dstLogPath = fbDialog.SelectedPath + @"\" + logFilenamePrefix + node + logFilenameSep + logFilename;
				string logMsg = "[" + srcLogPath + "] to [" + dstLogPath + "]";

				// add to list
				fileList.Add(dstLogPath);

				try
				{
					File.Copy(srcLogPath, dstLogPath);
					LogInfo("Copied file from " + logMsg);
				}
				catch(Exception exception)
				{
					LogInfo("Can't copy file from " + logMsg + ". EXCEPTION: " + exception.Message);
				}
			}

			// create archive
			if (cbLogToolZip.Checked == false)
			{
				return;
			}

			string currentTime = DateTime.Now.ToString("HHmmss");
			string currentDate = DateTime.Now.ToString("yyyyMMdd");

			string zipFilename = fbDialog.SelectedPath + @"\" + logFilenamePrefix + currentDate + "_" + currentTime + ".zip";

			CreateZipLogs(zipFilename, fileList);

			// clean *.log-files
			if (cbLogToolRemoveAfterZip.Checked == true)
			{
				RemoveListOfFiles(fileList);
			}
		}
		private string GetLogFolder(string node)
		{
			//get path
			string appPath = GetSelectedAppPath();
			// remove drive-name, like      [C:]
			appPath = appPath.Substring(2, appPath.Length - 2);
			// remove filename and extension
			string logPath = Path.GetDirectoryName(appPath);

			// replace slash to back-slash
			logPath.Replace("/", "\\");

			string projectName = Path.GetFileNameWithoutExtension(appPath);
			string fullpath = @"\\" + node + logPath + @"\" + projectName + @"\Saved\Logs\";

			return fullpath;
		}
		private void btnConsoleCopy_Click(object sender, EventArgs e)
		{
			CopyToClipboard(tbConsole.Text);
		}

		private void btnConsoleClear_Click(object sender, EventArgs e)
		{
			tbConsole.Clear();
		}

		private void btnCommandCopy_Click(object sender, EventArgs e)
		{
			CopyToClipboard(tbCommand.Text);
		}

		private void CopyToClipboard(string text)
		{
			if (text != String.Empty)
			{
				Clipboard.SetText(text);
			}
		}

		private void btnCleanLogs_Click(object sender, EventArgs e)
		{
			DialogResult dialogResult = MessageBox.Show("Are sure?", "Warning!", MessageBoxButtons.YesNo);
			if (dialogResult == DialogResult.Yes)
			{
				CleanLogFolders();
			}
			else if (dialogResult == DialogResult.No)
			{
				//do nothing
			}
		}

		private void CleanLogFolders()
		{
			List<string> nodes = GetNodes();
			foreach (string node in nodes)
			{
				string dirPath = GetLogFolder(node);
				RemoveAllRecursively(dirPath);
				LogInfo("Removed all files in : " + dirPath);
			}
		}

		private void RemoveAllRecursively(string rootDir)
		{
			try
			{
				// remove all files
				var allFilesToDelete = Directory.EnumerateFiles(rootDir, "*.*", SearchOption.AllDirectories);
				foreach (var file in allFilesToDelete)
				{
					File.Delete(file);
				}

				// remove all directories
				DirectoryInfo diRoot = new DirectoryInfo(rootDir);
				foreach (DirectoryInfo subDir in diRoot.GetDirectories())
				{
					subDir.Delete(true);
				}				
			}
			catch(Exception exception)
			{
				LogInfo("RemoveAllRecursively. EXCEPTION: " + exception.Message);
			}
		}

		private void btnCollectLogFiles_Click(object sender, EventArgs e)
		{
			CollectLogFiles();
		}

		private void CreateZipLogs(string zipFilename, List<string> files)
		{
			if (files.Count == 0)
			{
				return;
			}

			string currentDir = Path.GetDirectoryName(zipFilename);

			string dirForZip = currentDir + temporaryZipDir;
			
			// create tmp-dir
			Directory.CreateDirectory(dirForZip);
			
			// copy to temporary folder for zip
			foreach (string file in files)
			{
				File.Copy(file, dirForZip + Path.GetFileName(file));
			}

			try
			{
				// pack it
				ZipFile.CreateFromDirectory(dirForZip, zipFilename, CompressionLevel.Optimal, false);
				
				// remove tmp dir and all files after ZIP
				RemoveAllRecursively(dirForZip);
				Directory.Delete(dirForZip);
			}
			catch(Exception exception)
			{
				LogInfo("CreateZipLogs. EXCEPTION: " + exception.Message);
			}
		}

		private void RemoveListOfFiles(List<string> fList)
		{
			foreach (string file in fList)
			{
				File.Delete(file);
			}
		}

		private void cbLogToolZip_CheckedChanged(object sender, EventArgs e)
		{
			bool zipToolEnabled = cbLogToolZip.Checked;
			if (zipToolEnabled == false)
			{
				cbLogToolRemoveAfterZip.Checked = false;
			}

			cbLogToolRemoveAfterZip.Enabled = zipToolEnabled;
		}

		private void btnLogLevelSetup_Click(object sender, EventArgs e)
		{
			logLevelSetupForm.ShowDialog();
		}
	}
}
