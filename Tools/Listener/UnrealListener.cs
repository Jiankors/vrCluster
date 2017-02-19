using System;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;
using System.Text;
using System.IO;

//using System.Threading;
using System.Collections.Generic;

namespace UnrealTools
{
	class UnrealListener
	{
		
		static Int32 port = 9777;
		static IPAddress localAddr = IPAddress.Parse("0.0.0.0");

		static string unrealExeName = "UnrealEngine.exe";

		static Int32  processPid  = 0;
		static string processName = "";

        static string startCmd = "start ";
        static string killCmd = "kill ";

        static void Main(string[] args)
		{
			TcpListener server = null;
			try
			{
				server = new TcpListener(localAddr, port);

				server.Start();
				Console.WriteLine("PixelaLabs, 2016\n");

				Console.WriteLine("UnrealListener started on {0}:{1}. Waiting connection...\n", localAddr.ToString(), port.ToString());

				Console.WriteLine(@"Commands: info, status, kill, stop, forcekill, start (with app path)");
				Console.WriteLine(@"Example : start C:\Windows\SysWOW64\notepad.exe");
				Console.WriteLine(@"---------------------------------------------------------");

				// waiting connection
				while (true)
				{
					ProcessingRequest(server.AcceptTcpClient());
				}
			}
			catch (SocketException e)
			{
				Console.WriteLine("SocketException: {0}", e);
			}
			finally
			{
				server.Stop();
			}
		}

		private static void ProcessingRequest(object client_obj)
		{
			Console.WriteLine("Processing Request");

			TcpClient client = (TcpClient)client_obj;

			NetworkStream stream = client.GetStream();
            string clientIP = ((IPEndPoint)client.Client.RemoteEndPoint).Address.ToString();

			Console.WriteLine("Client [{0}] connected.", clientIP);

			Byte[] bytes = new Byte[8096];
			String data = String.Empty;
			int i = 0;

			while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
			{
				string cmd = Encoding.ASCII.GetString(bytes, 0, i);
				ParseData(cmd);
			}

			Console.WriteLine("Client [{0}] disconnected.", clientIP);
			client.Close();
		}

		private static void ParseData(string data)
		{
			if (data.Length == 0)
			{
                Console.WriteLine("Empty data received.");
                return;
			}

            Console.WriteLine("Command [{0}] received.", data);

            if (data.Contains(startCmd))
			{
                // remove "start "
                int cmdLen = startCmd.Length;
                data = data.Substring(cmdLen, data.Length - cmdLen);                
                StartApplication(data);
			}else
            if (data.Contains(killCmd))
            {
                int cmdLen = killCmd.Length;
                data = data.Substring(cmdLen, data.Length - cmdLen);
                KillApplication(data);
            }
            else
            if (data.Contains("info") || data.Contains("status"))
            {
                PrintStatus();
            }
            else
            {

                Console.WriteLine("Error! Unknown command : " + data);
            }
        }

		private static void StartApplication(string appPath)
		{			
			if (appPath == String.Empty)
			{
				Console.WriteLine("Application path is empty. Stop.");
				return;
			}

			try {
                // parse
                string[] launchStrings = appPath.Split(' ');

                string executablePath = launchStrings[0];
                string arguments = "";
                for(int i = 1; i < launchStrings.Length; i++)
                {
                    arguments += launchStrings[i] + " ";
                }

                Process appProccess = new Process();

				appProccess.StartInfo.FileName = executablePath;
                appProccess.StartInfo.Arguments = arguments;
                appProccess.Start();

				try
				{
					processPid = appProccess.Id;
					processName = Path.GetFileName(executablePath);
					Console.WriteLine("Started " + GetAppInfo());
				}
				catch (InvalidOperationException)
				{
					processPid = 0;
				}
			}
			catch(Exception e){
                Console.WriteLine(e.ToString());
			}			
		}

		private static void KillApplication(string data)
		{
            processName = Path.GetFileNameWithoutExtension(data);

            try
			{
				Process proc = Process.GetProcessById(processPid);                
                Console.WriteLine("Killed " + GetAppInfo());
				proc.Kill();
			}
			catch {
				Console.WriteLine("Can't kill it, pid [{0}]", processPid);
			}

            // try to kill by name all processes
            try {
                KillProcessesByName(processName);
                KillProcessesByName(unrealExeName);
            }
            catch(Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

		private static void KillProcessesByName(string procName)
		{
            List<Process> processes = new List<Process>();
            processes.AddRange(Process.GetProcessesByName(procName));

            if (processes.Count == 0)
			{
                List<Process> allProcesses = new List<Process>();
                allProcesses.AddRange(Process.GetProcesses());
                foreach (Process p in allProcesses)
                {
                    if (p.ProcessName.Contains(procName))
                        processes.Add(p);
                }
            }

			foreach (Process p in processes)
			{
				p.Kill();
			}
		}

		private static void PrintStatus()
		{
			if (processPid == 0)
			{
				Console.WriteLine("No application runned.");
				return;
			}
			
			Console.WriteLine("Runned " + GetAppInfo());
		}

		private static string GetAppInfo()
		{
			string appInfo = "---";
			try
			{
				Process app = Process.GetProcessById(processPid);
				appInfo = "application [" + app.MainModule.FileName + "] with pid [" + processPid + "]";
			}catch{

			}
			
			return appInfo; 
		}
	}
}