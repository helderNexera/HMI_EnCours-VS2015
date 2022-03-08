#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;

#include "global.h"

ref class LogData
{
private:
	String^ pS_AppearanceTime;
	String^ pS_DisappearanceTime;
	String^ pS_UserName;
	String^ pS_Team;
	String^ pS_Message;
	DateTime^ pT_TimeAdded;

public:
	LogData()
	{
		pS_AppearanceTime = "";
		pS_DisappearanceTime = "";
		pS_UserName = "";
		pS_Team = "";
		pS_Message = "";
		pT_TimeAdded = DateTime::MinValue;
	}

	LogData(String^ pS_x_AppearanceTime, String^ pS_x_DisappearanceTime, String^ pS_x_UserName, String^ pS_x_Team, String^ pS_x_Message, DateTime^ pT_x_TimeAdded)
	{
		pS_AppearanceTime = pS_x_AppearanceTime;
		pS_DisappearanceTime = pS_x_DisappearanceTime;
		pS_UserName = pS_x_UserName;
		pS_Team = pS_x_Team;
		pS_Message = pS_x_Message;
		pT_TimeAdded = pT_x_TimeAdded;
	}


	property String^ AppearanceTime
	{
		String^ get()
		{
			return pS_AppearanceTime;
		}
	}

	property String^ DisappearanceTime
	{
		String^ get()
		{
			return pS_DisappearanceTime;
		}
	}

	property String^ UserName
	{
		String^ get()
		{
			return pS_UserName;
		}
	}

	property String^ Team
	{
		String^ get()
		{
			return pS_Team;
		}
	}

	property String^ Message
	{
		String^ get()
		{
			return pS_Message;
		}
	}

	property DateTime^ TimeAdded
	{
		DateTime^ get()
		{
			return pT_TimeAdded;
		}
	}

};


ref class TLogger
{
private:
	static bool b_NeedCleanup;
	static DateTime t_LastCleanUp;
	static Object^ b_l_Mutex;
	static BindingList<LogData^>^ m_lsLogData;

	static void AddLogFile(String^ pS_x_Message,String^ pS_x_AppearTime, String^ pS_x_DisappearTime);
	static void CleanUp();
public:
	static TLogger(void);
	~TLogger(void);
	static void AddLog(String^ pS_x_Message);
	static void AddLog(String^ pS_x_Message,DateTime^ pT_x_AppearTime, DateTime^ pT_x_DisappearTime);
	static void AddManualLog(String^ pS_x_Message);
	static BindingList<LogData^>^ GetLog();

	static event EventHandler^ LogUpdated;
	
};
