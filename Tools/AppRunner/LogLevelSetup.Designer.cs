namespace AppRunner
{
	partial class LogLevelSetup
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
			this.btnLogLevelSetupSave = new System.Windows.Forms.Button();
			this.dgvLogTable = new System.Windows.Forms.DataGridView();
			this.btnLogLevelSetupRefreshTable = new System.Windows.Forms.Button();
			this.btnLogLevelSetupEnableAll = new System.Windows.Forms.Button();
			this.btnLogLevelSetupDisableAll = new System.Windows.Forms.Button();
			this.LogEnabled = new System.Windows.Forms.DataGridViewCheckBoxColumn();
			this.LogCategory = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.LogValue = new System.Windows.Forms.DataGridViewComboBoxColumn();
			((System.ComponentModel.ISupportInitialize)(this.dgvLogTable)).BeginInit();
			this.SuspendLayout();
			// 
			// btnLogLevelSetupSave
			// 
			this.btnLogLevelSetupSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.btnLogLevelSetupSave.Location = new System.Drawing.Point(12, 336);
			this.btnLogLevelSetupSave.Name = "btnLogLevelSetupSave";
			this.btnLogLevelSetupSave.Size = new System.Drawing.Size(334, 23);
			this.btnLogLevelSetupSave.TabIndex = 0;
			this.btnLogLevelSetupSave.Text = "Save all changes and close this window";
			this.btnLogLevelSetupSave.UseVisualStyleBackColor = true;
			this.btnLogLevelSetupSave.Click += new System.EventHandler(this.btnLogLevelSetupSave_Click);
			// 
			// dgvLogTable
			// 
			this.dgvLogTable.AllowUserToAddRows = false;
			this.dgvLogTable.AllowUserToDeleteRows = false;
			this.dgvLogTable.AllowUserToResizeColumns = false;
			this.dgvLogTable.AllowUserToResizeRows = false;
			this.dgvLogTable.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.LogEnabled,
            this.LogCategory,
            this.LogValue});
			this.dgvLogTable.Location = new System.Drawing.Point(12, 46);
			this.dgvLogTable.MultiSelect = false;
			this.dgvLogTable.Name = "dgvLogTable";
			this.dgvLogTable.RowHeadersVisible = false;
			this.dgvLogTable.RowTemplate.Resizable = System.Windows.Forms.DataGridViewTriState.False;
			this.dgvLogTable.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.dgvLogTable.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
			this.dgvLogTable.Size = new System.Drawing.Size(334, 284);
			this.dgvLogTable.TabIndex = 22;
			// 
			// btnLogLevelSetupRefreshTable
			// 
			this.btnLogLevelSetupRefreshTable.Location = new System.Drawing.Point(175, 13);
			this.btnLogLevelSetupRefreshTable.Name = "btnLogLevelSetupRefreshTable";
			this.btnLogLevelSetupRefreshTable.Size = new System.Drawing.Size(171, 23);
			this.btnLogLevelSetupRefreshTable.TabIndex = 23;
			this.btnLogLevelSetupRefreshTable.Text = "Refresh table (re-read config file)";
			this.btnLogLevelSetupRefreshTable.UseVisualStyleBackColor = true;
			this.btnLogLevelSetupRefreshTable.Click += new System.EventHandler(this.btnLogLevelSetupRefreshTable_Click);
			// 
			// btnLogLevelSetupEnableAll
			// 
			this.btnLogLevelSetupEnableAll.Location = new System.Drawing.Point(13, 13);
			this.btnLogLevelSetupEnableAll.Name = "btnLogLevelSetupEnableAll";
			this.btnLogLevelSetupEnableAll.Size = new System.Drawing.Size(75, 23);
			this.btnLogLevelSetupEnableAll.TabIndex = 24;
			this.btnLogLevelSetupEnableAll.Text = "Enable all";
			this.btnLogLevelSetupEnableAll.UseVisualStyleBackColor = true;
			this.btnLogLevelSetupEnableAll.Click += new System.EventHandler(this.btnLogLevelSetupEnableAll_Click);
			// 
			// btnLogLevelSetupDisableAll
			// 
			this.btnLogLevelSetupDisableAll.Location = new System.Drawing.Point(94, 13);
			this.btnLogLevelSetupDisableAll.Name = "btnLogLevelSetupDisableAll";
			this.btnLogLevelSetupDisableAll.Size = new System.Drawing.Size(75, 23);
			this.btnLogLevelSetupDisableAll.TabIndex = 25;
			this.btnLogLevelSetupDisableAll.Text = "Disable all";
			this.btnLogLevelSetupDisableAll.UseVisualStyleBackColor = true;
			this.btnLogLevelSetupDisableAll.Click += new System.EventHandler(this.btnLogLevelSetupDisableAll_Click);
			// 
			// LogEnabled
			// 
			this.LogEnabled.HeaderText = "Enabled";
			this.LogEnabled.Name = "LogEnabled";
			this.LogEnabled.Width = 50;
			// 
			// LogCategory
			// 
			this.LogCategory.HeaderText = "Category";
			this.LogCategory.Name = "LogCategory";
			this.LogCategory.Width = 160;
			// 
			// LogValue
			// 
			this.LogValue.HeaderText = "Value";
			this.LogValue.Items.AddRange(new object[] {
            "Off",
            "All",
            "Verbose",
            "VeryVerbose",
            "Log",
            "Warning",
            "Error"});
			this.LogValue.Name = "LogValue";
			// 
			// LogLevelSetup
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(358, 368);
			this.Controls.Add(this.btnLogLevelSetupDisableAll);
			this.Controls.Add(this.btnLogLevelSetupEnableAll);
			this.Controls.Add(this.btnLogLevelSetupRefreshTable);
			this.Controls.Add(this.dgvLogTable);
			this.Controls.Add(this.btnLogLevelSetupSave);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.Name = "LogLevelSetup";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "Log Levels Setup";
			((System.ComponentModel.ISupportInitialize)(this.dgvLogTable)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button btnLogLevelSetupSave;
		private System.Windows.Forms.DataGridView dgvLogTable;
		private System.Windows.Forms.Button btnLogLevelSetupRefreshTable;
		private System.Windows.Forms.Button btnLogLevelSetupEnableAll;
		private System.Windows.Forms.Button btnLogLevelSetupDisableAll;
		private System.Windows.Forms.DataGridViewCheckBoxColumn LogEnabled;
		private System.Windows.Forms.DataGridViewTextBoxColumn LogCategory;
		private System.Windows.Forms.DataGridViewComboBoxColumn LogValue;
	}
}