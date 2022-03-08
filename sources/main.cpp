#include "MainWindow.h"
#include "TTwincatInterface.h"
#include "TLogger.h"
#include "login.h"
#include "global.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Projet1;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;
using namespace System::ComponentModel;
using namespace System::Management;

ref class ProcessWatchDog
{
private:
	ManualResetEvent^ m_oQuitThread;
	initonly String^ m_sProcess;
	initonly String^ m_sArgument;

	String^ ProcessExecutablePath(Process^ process)
	{
		try
		{
			return process->MainModule->FileName;
		}
		catch(Win32Exception^ ex)
		{
			if (ex->NativeErrorCode != 299)
			{
				throw;
			}
			String^ query = "SELECT ExecutablePath, ProcessID FROM Win32_Process";
			ManagementObjectSearcher^ searcher = gcnew ManagementObjectSearcher(query);

			for each(ManagementObject^ item in searcher->Get())
			{
				Object^ id = item["ProcessID"];
				Object^ path = item["ExecutablePath"];

				if ((path != nullptr) && (id->ToString() == process->Id.ToString()))
				{
					return path->ToString();
				}
			}
		}
		return "";
	}

	Process^ GetProcess()
	{
		String^ sProcName = Path::GetFileNameWithoutExtension(m_sProcess);
		array<Process^>^ aoProcess = Process::GetProcessesByName(sProcName);
		for each(Process^ oProcess in aoProcess)
		{
			try
			{
				String^ sName = ProcessExecutablePath(oProcess);
				if (sName == m_sProcess)
				{
					return oProcess;
				}
			}
			catch (Exception^)
			{
			}
		}
		return nullptr;
	}

	Process^ StartApp()
	{
		ProcessStartInfo^ Info = gcnew ProcessStartInfo(m_sProcess, m_sArgument);
		Info->WindowStyle = ProcessWindowStyle::Minimized;
		return Process::Start(Info);
	}
	
public:
	ProcessWatchDog(ManualResetEvent^ oQuitThread, String^ sProcess, String^ sArgument)
	{
		m_oQuitThread = oQuitThread;
		m_sProcess = sProcess;
		m_sArgument = sArgument;
	}

	void Watch()
	{
		Process^ oWatchProcess = nullptr;
		while (!m_oQuitThread->WaitOne(1000))
		{
			if (oWatchProcess == nullptr)
			{
				oWatchProcess = GetProcess();
			}
			if (oWatchProcess != nullptr)
			{
				if (oWatchProcess->HasExited)
				{
					Debug::Print("Closed");
					oWatchProcess = StartApp();
				}
				else
				{
					Debug::Print("Alive");
				}
			}
			else
			{
				Debug::Print("No process");
				oWatchProcess = StartApp();
			}
		}
	}
};

[System::STAThread]
#pragma warning( suppress : 4829 )
void main(array<String^>^ args){
	String^ sAdsAdress = args->Length >= 1 ? args[0] : nullptr;
	String^ sVisionApp = args->Length >= 2 ? args[1] : nullptr;
	Mutex^ mutex = gcnew Mutex(true, "{E51F62F7-BBCB-4E8B-8F86-3EB71AE1EEF4}");

	if (!mutex->WaitOne(TimeSpan::Zero, true))
	{
		MessageBox::Show(nullptr, "Application déjà démarrée", "Erreur", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if (String::IsNullOrEmpty(sAdsAdress))
	{
		MessageBox::Show(nullptr,"Pas d'adresse ADS définie","Erreur", MessageBoxButtons::OK,MessageBoxIcon::Error);
		return;
	}
	int^ pi_l_Result;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Configure default language
	RegistryKey^ pT_l_LanguageKey = Registry::LocalMachine->CreateSubKey("Software")->CreateSubKey("Nexera")->CreateSubKey(C_REG_BASE_KEY);
	pi_l_Result = (int^)pT_l_LanguageKey->GetValue("DefaultLanguage");
	if (nullptr == pi_l_Result)
		i_g_LanguageNb = 0;
	else
		i_g_LanguageNb = *pi_l_Result;
	pT_l_LanguageKey->Close();

	// Start the logger
	TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::StartApplication));

	ProductionOrder::ProductionOrder();
	// Display the login box
	login^ pT_l_LoginForm = gcnew login();
	pT_l_LoginForm->ShowDialog();


	// Launch vision app watchdog

	Thread^ oVisionWatchDog = nullptr;
	ManualResetEvent^ oQuitThread = nullptr;
	
	if (!String::IsNullOrEmpty(sVisionApp))
	{
		oQuitThread = gcnew ManualResetEvent(false);
		ProcessWatchDog^ oWatch = gcnew ProcessWatchDog(oQuitThread, sVisionApp,sAdsAdress);
		oVisionWatchDog = gcnew Thread(gcnew ThreadStart(oWatch, &ProcessWatchDog::Watch));
		oVisionWatchDog->Start();
	}
	
	MainForm^ form = gcnew MainForm(sAdsAdress);

	Application::Run(form);
	
	if (oVisionWatchDog != nullptr)
	{
		oQuitThread->Set();
		oVisionWatchDog->Join(10000);
		oVisionWatchDog = nullptr;
	}

	try
	{
		delete form;
	}
	catch(...)
	{
	}
}
