using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Data;
using System.Drawing;

namespace AppRunner
{
	public partial class LogLevelSetup : Form
	{
		public const string confFileLogCategories = "logCategoriesList.conf";

		private List<string> logCategories = new List<string>();

		public LogLevelSetup()
		{
			InitializeComponent();

			LogLevelSetupInit();
		}

		private void LogLevelSetupInit()
		{
			logCategories.Clear();
			logCategories = ReadConfigFile(confFileLogCategories);

			FillDataGrid(logCategories);
		}

		private void FillDataGrid(List<string> items)
		{
			if (logCategories.Count <= 0)
			{
				return;
			}

			// clear all rows
			dgvLogTable.Rows.Clear();

			foreach (string item in items)
			{
				// add new item
				dgvLogTable.Rows.Add(new object[] { true, item});
				
				// index of last row in table
				int idx = dgvLogTable.RowCount-1;

				// get comboBoxCell
				DataGridViewComboBoxCell cbCell = dgvLogTable.Rows[idx].Cells[2] as DataGridViewComboBoxCell;
				
				// set default value
				cbCell.Value = "All";
			}
		}

		private List<string> ReadConfigFile(string confFilePath)
		{
			List<string> infoList = new List<string>();
			try
			{
				string[] lines = System.IO.File.ReadAllLines(confFilePath);
				infoList = lines.ToList();
			}
			catch (Exception exception)
			{
				MessageBox.Show("Can't read file [" + confFilePath + "]. EXCEPTION: " + exception.Message);
			}
			return infoList;
		}

		private string GenerateLogLevelsString()
		{
			string resString = String.Empty;
			List<string> logsList = new List<string>();

			foreach (DataGridViewRow dgvRow in dgvLogTable.Rows)
			{
				bool rowEnabled = Convert.ToBoolean(dgvRow.Cells[0].Value);
				if (rowEnabled)
				{
					string logCat = dgvRow.Cells[1].Value as string;
					string logCatValue = dgvRow.Cells[2].Value as string;
					logsList.Add(logCat + " " + logCatValue);
				}
			}

			// create one string-param
			if (logsList.Count == 0)
			{
				return resString;
			}

			resString = " -LogCmds=\"";

			for (int i = 0; i < logsList.Count-1; i++)
			{
				resString += logsList[i] + ", ";
			}

			resString += logsList[logsList.Count-1] + "\"";

			return resString;
		}

		private void btnLogLevelSetupSave_Click(object sender, EventArgs e)
		{
			// check table and generate string and setup it
			Form1.logLevels = GenerateLogLevelsString();

			// close it
			this.Close();
		}

		private void btnLogLevelSetupRefreshTable_Click(object sender, EventArgs e)
		{
			LogLevelSetupInit();
		}

		private void btnLogLevelSetupEnableAll_Click(object sender, EventArgs e)
		{
			SetEnabledForAll(true);
		}

		private void btnLogLevelSetupDisableAll_Click(object sender, EventArgs e)
		{
			SetEnabledForAll(false);
		}

		private void SetEnabledForAll(bool en)
		{
			foreach (DataGridViewRow dgvRow in dgvLogTable.Rows)
			{
				dgvRow.Cells[0].Value = en;
			}
		}
	}
}
