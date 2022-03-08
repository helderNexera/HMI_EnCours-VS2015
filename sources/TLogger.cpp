#pragma once

#include "global.h"
#include "TLogger.h"
#include "TUtilities.h"

using namespace System::Globalization;

static TLogger::TLogger()
{
	b_l_Mutex = gcnew Object();
	m_lsLogData = gcnew BindingList<LogData^>();
	b_NeedCleanup = true;
	//for (size_t i = 0; i < 10000; i++)
	//{
	//	m_lsLogData->Insert(0, gcnew LogData(i.ToString(), "Test", "Test", "Test", "Test", DateTime::Now));
	//}
}

TLogger::~TLogger(void)
{
}

void TLogger::AddLogFile(String^ pS_x_Message,String^ pS_x_AppearTime, String^ pS_x_DisappearTime)
{
	Monitor::Enter(b_l_Mutex);

	CleanUp();
	DateTime T_l_TimeNow = DateTime::Now;
	String^ CompleteLine = gcnew String("");
	StreamWriter^  pT_l_LogFile = File::AppendText(C_APP_LOGS_PATH + T_l_TimeNow.ToString("d_M_yyyy") + ".log");
	try
	{
		CompleteLine = String::Format("[{0}] - [{1}] : {2} - {3}",pS_x_AppearTime,pS_x_DisappearTime,TUser::pS_GetName(),pS_x_Message);
		pT_l_LogFile->WriteLine(CompleteLine);
	}
	finally
	{
		if ( pT_l_LogFile )
			delete (IDisposable^)pT_l_LogFile;
	}
	Monitor::Exit(b_l_Mutex);
}

void TLogger::AddLog(String^ pS_x_Message)
{
	TLogger::AddLog(pS_x_Message,DateTime::Now, nullptr);
}

void TLogger::AddLog(String^ pS_x_Message,DateTime^ pT_x_AppearTime, DateTime^ pT_x_DisappearTime)
{
	String^ pS_l_AppearTime = gcnew String("");
	String^ pS_l_DisappearTime = gcnew String("");

	if (nullptr != pT_x_AppearTime)
		pS_l_AppearTime = TUtilities::pS_FormatDateTime(pT_x_AppearTime);
	if (nullptr != pT_x_DisappearTime)
		pS_l_DisappearTime = TUtilities::pS_FormatDateTime(pT_x_DisappearTime);
	// Add it to log file
	AddLogFile(pS_x_Message,pS_l_AppearTime,pS_l_DisappearTime);
	// And memorize it
	DateTime dtNow = DateTime::Now;
	m_lsLogData->Insert(0,gcnew LogData(pS_l_AppearTime, pS_l_DisappearTime, TUser::pS_GetName(), TUser::pS_GetTeam(), pS_x_Message, dtNow));
	for (int i = m_lsLogData->Count - 1; i >= 0; i--)
	{
		if ((dtNow - *m_lsLogData[i]->TimeAdded).TotalHours >= 24.0)
		{
			m_lsLogData->RemoveAt(i);
		}
		else
		{
			break;
		}
	}
	LogUpdated(nullptr,EventArgs::Empty);
}

void TLogger::AddManualLog(String^ pS_x_Message)
{
	String^ pS_l_ManualString = gcnew String("Manual - ");

	pS_l_ManualString += pS_x_Message;
	TLogger::AddLog(pS_l_ManualString,DateTime::Now, nullptr);
}

BindingList<LogData^>^ TLogger::GetLog()
{
	return m_lsLogData;
}

void TLogger::CleanUp()
{
	if (!b_NeedCleanup)
	{
		if ((DateTime::Now.Date - t_LastCleanUp).Days > 0)
		{
			b_NeedCleanup = true;
		}
	}
	if (b_NeedCleanup)
	{
		DateTime Now = DateTime::Now.Date;
		t_LastCleanUp = Now;
		b_NeedCleanup = false;
		String^ sFolder = C_APP_LOGS_PATH;
		sFolder = sFolder->Remove(sFolder->Length - 1);

		for each (String^ sFile in Directory::GetFiles(sFolder))
		{
			try
			{
				String^ sDate = Path::GetFileNameWithoutExtension(sFile);
				DateTime tDate = DateTime::ParseExact(sDate, "d_M_yyyy", CultureInfo::InvariantCulture, DateTimeStyles::None);
				if ((Now - tDate).Days > 30)
				{
					File::Delete(sFile);
				}
			}
			catch (...)
			{

			}
		}
	}
}

