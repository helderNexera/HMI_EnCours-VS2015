#pragma once

#include "TTwincatInterface.h"
#include "TextList.h"

using namespace System;
using namespace System::Text;
using namespace System::Security::Cryptography;
using namespace Microsoft::Win32;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

#define SetButtonText(T_m_Button,ac_m_TextON,ac_m_TextOff,b_m_Status) \
	if (b_m_Status) \
		T_m_Button->Text = ac_m_TextON; \
	else \
		T_m_Button->Text = ac_m_TextOff; 

ref class TUtilities
{
private:
	static Dictionary<String^,array<String^>^>^ apS_LangStrings;
	static String^ pS_BaseKey = gcnew String("MondemaIsTheWorldLeader");
	static String^ pS_CryptKey;
	static Object^ LockObj;

public:
	static TUtilities(void);
	// User management
	static String^ pS_Encrypt(String^ pS_x_Data);
	static bool b_UserExists(String^ pS_x_UserName);
	static bool b_CheckPassword(String^ pS_x_UserName,String^ pS_x_Password);
	static void CreateUser(String^ pS_x_UserName,String^ pS_x_Password,enum UserLevel e_x_UserLevel);
	static void DeleteUser(String^ pS_x_UserName);
	static void ReadReferenceFile(String^ pS_x_ReferenceName);
	static void ShowOSK(void);
	static String^ pS_FormatDate(DateTime^ pT_x_DateTime);
	static String^ pS_FormatDateTime(DateTime^ pT_x_DateTime);
	static String^ pS_FormatTimeSpan(TimeSpan^ pT_x_TimeSpan);
	static void UpdateDoubleButton(TC_MAN_BUTTON T_x_Data,CheckBox^ T_x_ActiveButton,CheckBox^ T_x_InactiveButton);
	static void UpdateBistableButton(TC_MAN_BUTTON T_x_Data,CheckBox^ T_x_ActiveButton);
	static void UpdateMonostableButton(TC_MAN_BUTTON T_x_Data,Button^ T_x_ActiveButton);
	static String^ pS_GetTextBool(bool b_x_BoolFlag);
	static int i_GetValueFromTag(Object^ pT_x_Tag);
	static void StringToCharArray(String^ pT_x_String,char* pc_x_CharArray);
	static String^ pS_LoadString(TextIndex i_x_StringIndex);
	static String^ pS_VerticalString(String^ pS_x_BaseString);
	static String^ pS_DecryptBaseKey(String^ pS_x_String2Decrypt);
	static String^ pS_Decrypt(String^ pS_x_String2Decrypt);
	static String^ pS_ReadAndDecryptData(StreamReader^ pT_x_File);
	static bool b_GetXMLData(String^ pS_l_CurrentLine, String^ %pS_l_XMLTag, String^ %pS_l_XMLValue);
	static Dictionary<String^, array<String^>^>^ LoadTranslation(String^ pS_l_FileName);
	static void SetVisible(Control^ oCtrl, bool bVisible);
	static void SetVisible(System::Windows::Forms::Control::ControlCollection^ Ctrls);
	
};
