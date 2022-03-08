
#include <string.h>
#include "global.h"
#include "TUtilities.h"
#include "MainWindow.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace System::Xml;
using namespace System::Diagnostics;
using namespace System::Globalization;
using namespace MondemaComponents;
using namespace System::Net::NetworkInformation;
using namespace System::Management;

#ifdef _WIN64
	#ifdef _DEBUG
	[DllImport("dpwin64debug", CharSet = CharSet::Ansi)]
	#else
	[DllImport("dpwin64", CharSet = CharSet::Ansi)]
	#endif
#else
	#ifdef _DEBUG
	[DllImport("dpwin32debug", CharSet = CharSet::Ansi)]
	#else
	[DllImport("dpwin32", CharSet = CharSet::Ansi)]
	#endif
#endif

static TUtilities::TUtilities(void)
{
	LockObj = gcnew System::Object();
}

String^ TUtilities::pS_Encrypt(String^ pS_x_Data)
{
	array<Byte>^ py_l_data;
	array<Byte>^ py_l_result;
	String^ pS_l_Result;
	System::Text::ASCIIEncoding^ pT_l_Converter = gcnew System::Text::ASCIIEncoding; 
			
	// Convert String to array of bytes
	py_l_data = pT_l_Converter->GetBytes(pS_x_Data);
	// Compute the encrypted data
	SHA256Managed^ pT_l_Encriptor = gcnew SHA256Managed;
	py_l_result = pT_l_Encriptor->ComputeHash(py_l_data);
	//Create a HexaString of encrypted data
	int Numberbytes = pT_l_Encriptor->HashSize/8;
	pS_l_Result = gcnew String("");
	for (int i = 0; i < Numberbytes; i++)
		pS_l_Result += System::Convert::ToString(py_l_result[i]);
	return pS_l_Result;
}

bool TUtilities::b_UserExists(String^ pS_x_UserName)
{
	bool b_l_Result = false;
	String^ pS_l_EncryptedUser;

	RegistryKey^ pT_l_UserKey = Registry::LocalMachine->CreateSubKey("Software")->CreateSubKey("Nexera")->CreateSubKey(C_REG_BASE_KEY)->CreateSubKey("Users");
	// Encrypt user name
	pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName);
	b_l_Result = (nullptr != pT_l_UserKey->GetValue(pS_l_EncryptedUser));
	if (!b_l_Result)
	{
		pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName + "0");
		b_l_Result = (nullptr != pT_l_UserKey->GetValue(pS_l_EncryptedUser));
		if (!b_l_Result)
		{
			pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName + "1");
			b_l_Result = (nullptr != pT_l_UserKey->GetValue(pS_l_EncryptedUser));
		}
	}
	pT_l_UserKey->Close();
	return b_l_Result;
}

bool TUtilities::b_CheckPassword(String^ pS_x_UserName,String^ pS_x_Password)
{
	String^ Result;
	bool b_l_Result;
	String^ pS_l_EncryptedUser;
	String^ pS_l_EncryptedPassword;

	// Encrypt user name
	pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName);
	// Encrypt password
	pS_l_EncryptedPassword = TUtilities::pS_Encrypt(pS_x_Password);
	// Get password if user exists
	RegistryKey^ pT_l_UserKey = Registry::LocalMachine->CreateSubKey("Software")->CreateSubKey("Nexera")->CreateSubKey(C_REG_BASE_KEY)->CreateSubKey("Users");
	Result = (String^)pT_l_UserKey->GetValue(pS_l_EncryptedUser);
	b_l_Result = (0 == String::Compare(pS_l_EncryptedPassword,Result));
	pT_l_UserKey->Close();
	return b_l_Result;
}

void TUtilities::CreateUser(String^ pS_x_UserName,String^ pS_x_Password,enum UserLevel e_x_UserLevel)
{
	String^ pS_l_EncryptedUser;
	String^ pS_l_EncryptedPassword;

	// Encrypt user name
	if (UL_Maintenance == e_x_UserLevel)
		pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName + "0");
	else if (UL_Manager == e_x_UserLevel)
		pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName + "1");
	else
		pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName);
	// Encrypt password
	pS_l_EncryptedPassword = TUtilities::pS_Encrypt(pS_x_Password);
	// Save it in user file
	RegistryKey^ pT_l_UserKey = Registry::LocalMachine->CreateSubKey("Software")->CreateSubKey("Nexera")->CreateSubKey(C_REG_BASE_KEY)->CreateSubKey("Users");
	pT_l_UserKey->SetValue(pS_l_EncryptedUser, pS_l_EncryptedPassword );
	pT_l_UserKey->Close();
	String^ pS_l_LogString = String::Format(TUtilities::pS_LoadString(TextIndex::NewUserCreated),pS_x_UserName);
	TLogger::AddLog(pS_l_LogString);

}

void TUtilities::DeleteUser(String^ pS_x_UserName)
{
	String^ pS_l_EncryptedUser;

	// Delete it in user file
	RegistryKey^ pT_l_UserKey = Registry::LocalMachine->CreateSubKey("Software")->CreateSubKey("Nexera")->CreateSubKey(C_REG_BASE_KEY)->CreateSubKey("Users");
	// Encrypt user name
	try
	{
		pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName);
		pT_l_UserKey->DeleteValue(pS_l_EncryptedUser);
	}
	catch (...)
	{

	}
	// Also for maintenance
	try
	{
		pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName + "0");
		pT_l_UserKey->DeleteValue(pS_l_EncryptedUser);
	}
	catch (...)
	{

	}
	
	// Also for manager
	try
	{
		pS_l_EncryptedUser = TUtilities::pS_Encrypt(pS_x_UserName + "1");
		pT_l_UserKey->DeleteValue(pS_l_EncryptedUser);
	}
	catch (...)
	{

	}
	
	pT_l_UserKey->Close();
	String^ pS_l_LogString = String::Format(TUtilities::pS_LoadString(TextIndex::UserDeleted),pS_x_UserName);
	TLogger::AddLog(pS_l_LogString);

}

void TUtilities::ReadReferenceFile(String^ pS_x_ReferenceName)
{
	String^ pS_l_CurrentLine = gcnew String("");
	bool b_l_FirstLine = true;
	String^ pS_l_XMLTag;
	String^ pS_l_XMLValue;

	try
	{
		StreamReader^ pT_l_Reader = gcnew StreamReader(C_APP_REFERENCES_PATH + pS_x_ReferenceName + ".mrc", System::Text::Encoding::Default);
		try
		{
			while (pT_l_Reader->Peek() >= 0)
			{
				pS_l_CurrentLine = pT_l_Reader->ReadLine();
				// First line gives the crypting key
				if (b_l_FirstLine)
				{
					pS_l_CurrentLine = TUtilities::pS_DecryptBaseKey(pS_l_CurrentLine);
					b_l_FirstLine = false;
				}
				// Else it is a data line
				else
				{
					pS_l_CurrentLine = TUtilities::pS_Decrypt(pS_l_CurrentLine);
					// Check XMLstructure
					if (TUtilities::b_GetXMLData(pS_l_CurrentLine, pS_l_XMLTag, pS_l_XMLValue))
					{
						// Check datas
						if ("plate" == pS_l_XMLTag)
						{
							ProductionOrder::SetPlateType(Path::GetFileNameWithoutExtension(pS_l_XMLValue));
						}
						else if ("VisionReferenceFileName" == pS_l_XMLTag)
							ProductionOrder::SetVisionReferenceFileName(pS_l_XMLValue);
						else if ("PartOffsetZLiftTake" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetZLiftTake(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetZLiftBadTake" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetZLiftBadTake(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetZLiftDrop" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetZLiftDrop(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetThetaLiftDrop" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetThetaLiftDrop(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetXLiftDrop" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetXLiftDrop(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetYLiftDrop" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetYLiftDrop(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetZLayeringTake" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetZLayeringTake(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetZLayeringDrop" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetZLayeringDrop(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetZTurnOverDrop" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetZTurnOverDrop(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetZCleaning" == pS_l_XMLTag)
							ProductionOrder::SetPartOffsetZCleaning(Convert::ToDouble(pS_l_XMLValue));
						else if ("SensorOffsetX1" == pS_l_XMLTag)
							ProductionOrder::SetPartSensorOffset(0, 0, Convert::ToDouble(pS_l_XMLValue));
						else if ("SensorOffsetY1" == pS_l_XMLTag)
							ProductionOrder::SetPartSensorOffset(0, 1, Convert::ToDouble(pS_l_XMLValue));
						else if ("SensorOffsetX2" == pS_l_XMLTag)
							ProductionOrder::SetPartSensorOffset(1, 0, Convert::ToDouble(pS_l_XMLValue));
						else if ("SensorOffsetY2" == pS_l_XMLTag)
							ProductionOrder::SetPartSensorOffset(1, 1, Convert::ToDouble(pS_l_XMLValue));
						else if ("PartAndLayeringHeight" == pS_l_XMLTag)
							ProductionOrder::SetPartAndLayeringHeight(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartAndHeadHeight" == pS_l_XMLTag)
							ProductionOrder::SetPartAndHeadHeight(Convert::ToDouble(pS_l_XMLValue));
						else if ("LayeringAndPartAndHeadHeight" == pS_l_XMLTag)
							ProductionOrder::SetLayeringAndPartAndHeadHeight(Convert::ToDouble(pS_l_XMLValue));
						else if ("HeadSusPartHeadSousHeight" == pS_l_XMLTag)
							ProductionOrder::SetHeadSusPartHeadSousHeight(Convert::ToDouble(pS_l_XMLValue));
						else if ("PlateZOffsetForLift" == pS_l_XMLTag)
							ProductionOrder::SetPlateZOffsetForLift(Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetX1" == pS_l_XMLTag)
							ProductionOrder::SetPartOffset(0, 0, Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetY1" == pS_l_XMLTag)
							ProductionOrder::SetPartOffset(0, 1, Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetX2" == pS_l_XMLTag)
							ProductionOrder::SetPartOffset(1, 0, Convert::ToDouble(pS_l_XMLValue));
						else if ("PartOffsetY2" == pS_l_XMLTag)
							ProductionOrder::SetPartOffset(1, 1, Convert::ToDouble(pS_l_XMLValue));
						else if ("HeadOffsetX" == pS_l_XMLTag)
							ProductionOrder::SetHeadOffset(0, Convert::ToDouble(pS_l_XMLValue));
						else if ("HeadOffsetY" == pS_l_XMLTag)
							ProductionOrder::SetHeadOffset(1, Convert::ToDouble(pS_l_XMLValue));
						else if ("DropModeTable" == pS_l_XMLTag)
							ProductionOrder::SetDropModeTable(Convert::ToInt32(pS_l_XMLValue));
						else if ("DropModeTurnOver" == pS_l_XMLTag)
							ProductionOrder::SetDropModeTurnOver(Convert::ToInt32(pS_l_XMLValue));
						else if ("TakeModeLift" == pS_l_XMLTag)
							ProductionOrder::SetTakeModeLift(Convert::ToInt32(pS_l_XMLValue));
						else if ("DropInBox" == pS_l_XMLTag)
							ProductionOrder::SetDropInBox(Convert::ToBoolean(pS_l_XMLValue));
					}
				}
			}
		}
		finally
		{
			delete pT_l_Reader;
		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show("Error on part file : " + e->Message, "TUtilities::ReadReferenceFile");
	}
}

void TUtilities::ShowOSK(void)
{
	Version^ ver = Environment::OSVersion->Version;
	if (ver >= gcnew Version(6, 2)) return;

	array<Process^>^localByName = Process::GetProcessesByName( "osk" );
	int i_l_NbOfProcess = localByName->GetLength(0);

	while (i_l_NbOfProcess-- > 0)
	{
		localByName[i_l_NbOfProcess]->Kill();

	}
	Process ^proc = gcnew Process();
	proc->StartInfo->FileName = Environment::SystemDirectory + "\\osk.exe";
	proc->Start();
	proc->Close();
}

String^ TUtilities::pS_FormatDate(DateTime^ pT_x_DateTime)
{
	IFormatProvider^ culture = gcnew CultureInfo("fr-FR", true);

	return pT_x_DateTime->ToString("d",culture);
}

String^ TUtilities::pS_FormatDateTime(DateTime^ pT_x_DateTime)
{
	if (pT_x_DateTime != nullptr)
	{
		IFormatProvider^ culture = gcnew CultureInfo("fr-FR", true);

		return pT_x_DateTime->ToString("G", culture);
	}
	return "??/??/???? ??:??:??";
}

String^ TUtilities::pS_FormatTimeSpan(TimeSpan^ pT_x_TimeSpan)
{
	if (pT_x_TimeSpan->TotalHours >= 1.0)
	{
		return ((int)Math::Truncate(pT_x_TimeSpan->TotalHours)).ToString() + ":" + pT_x_TimeSpan->Minutes.ToString("D2") + ":" + pT_x_TimeSpan->Seconds.ToString("D2");
	}
	else
	{
		return "0:" + ((int)Math::Truncate(pT_x_TimeSpan->TotalMinutes)).ToString("D2") + ":" + pT_x_TimeSpan->Seconds.ToString("D2");
	}
}

void TUtilities::UpdateDoubleButton(TC_MAN_BUTTON T_x_Data,CheckBox^ T_x_ActiveButton,CheckBox^ T_x_InactiveButton)
{
	TC_BOOL b_l_Status;

	b_l_Status = T_x_Data.MB_Activate;
	T_x_ActiveButton->Checked = (b_l_Status != 0);
	T_x_InactiveButton->Checked = !T_x_ActiveButton->Checked;
	b_l_Status = T_x_Data.MB_Enable;
	T_x_ActiveButton->Enabled = (b_l_Status != 0) && !T_x_ActiveButton->Checked;
	T_x_InactiveButton->Enabled = (b_l_Status != 0) && !T_x_InactiveButton->Checked;
}

void TUtilities::UpdateBistableButton(TC_MAN_BUTTON T_x_Data,CheckBox^ T_x_ActiveButton)
{
	TC_BOOL b_l_Status;

	b_l_Status = T_x_Data.MB_Activate;
	T_x_ActiveButton->Checked = (b_l_Status != 0);
	b_l_Status = T_x_Data.MB_Enable;
	T_x_ActiveButton->Enabled = (b_l_Status != 0);
}

void TUtilities::UpdateMonostableButton(TC_MAN_BUTTON T_x_Data,Button^ T_x_ActiveButton)
{
	TC_BOOL b_l_Status;

	b_l_Status = T_x_Data.MB_Enable;
	T_x_ActiveButton->Enabled = (b_l_Status != 0);
}

String^ TUtilities::pS_GetTextBool(bool b_x_BoolFlag)
{
	if (b_x_BoolFlag)
		return "ON";
	else
		return "OFF";
}

int TUtilities::i_GetValueFromTag(Object^ pT_x_Tag)
{
	return System::Convert::ToInt32(pT_x_Tag->ToString());
}

void TUtilities::StringToCharArray(String^ pT_x_String,char* pc_x_CharArray)
{
	IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(pT_x_String);
	char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer());
	int i=strlen(nativeString);
	while (*nativeString)
		*(pc_x_CharArray++) = *(nativeString++);
	*pc_x_CharArray = 0;
//	strcpy_s(pc_x_CharArray,strlen(nativeString),nativeString);
}

Dictionary<String^, array<String^>^>^ TUtilities::LoadTranslation(String^ pS_l_FileName)
{
	Dictionary<String^, array<String^>^>^ apS_l_LangStrings = gcnew Dictionary<String^, array<String^>^>();
	String^ pS_l_Delimiter = ";";
	array<Char>^ pac_l_Delimiter = pS_l_Delimiter->ToCharArray();
	array<String^>^ paS_l_Splitdata;

	try
	{
		array<String^>^ aS_l_ReaderLines = File::ReadAllLines(pS_l_FileName, System::Text::Encoding::UTF8);
		for (int i = 0; i < aS_l_ReaderLines->Length; i++)
		{
			paS_l_Splitdata = aS_l_ReaderLines[i]->Split(pac_l_Delimiter, StringSplitOptions::RemoveEmptyEntries);
			if (paS_l_Splitdata->Length == 0) continue; //skip emtpy lines
			int iNumLanguage = paS_l_Splitdata->Length - 1;
			array<String^>^ paS_l_Translate = gcnew array<String^>(iNumLanguage);
			for (int i_l_LanguageNb = 0; i_l_LanguageNb<iNumLanguage; i_l_LanguageNb++)
				paS_l_Translate[i_l_LanguageNb] = paS_l_Splitdata[i_l_LanguageNb + 1];
			apS_l_LangStrings->Add(paS_l_Splitdata[0], paS_l_Translate);
		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show("Error on string file reading :" + pS_l_FileName + " with exception : " + e->Message, "TUtilities::LoadTranslation");
	}
	return apS_l_LangStrings;

}

String^ TUtilities::pS_LoadString(TextIndex i_x_StringIndex)
{
	String^ pS_l_Keys = i_x_StringIndex.ToString();

	if (apS_LangStrings == nullptr)
	{
		apS_LangStrings = LoadTranslation(C_APP_CONFIG_PATH + "texts.csv");
		if (apS_LangStrings->Count > 0)
		{
			List<String^> lsMissingTranslation = gcnew List<String^>();
			for each(TextIndex Index in Enum::GetValues(TextIndex::typeid))
			{
				if (!apS_LangStrings->ContainsKey(Index.ToString()))
				{
					lsMissingTranslation.Add(Index.ToString());
				}
			}
			if (lsMissingTranslation.Count > 0)
			{
				MessageBox::Show("Missing Translation :" + Environment::NewLine + String::Join(Environment::NewLine, lsMissingTranslation.ToArray()), "TUtilities::pS_LoadString");
			}
		}
	}
	// return the needed string

	if (apS_LangStrings->ContainsKey(pS_l_Keys))

		return apS_LangStrings[pS_l_Keys][i_g_LanguageNb];
	else
	{
		
		return pS_l_Keys;
	}
}

String^ TUtilities::pS_VerticalString(String^ pS_x_BaseString)
{
	String^ pS_l_VerticalString = pS_x_BaseString->Substring(0,1);
	
	for (int i=1;i<pS_x_BaseString->Length;i++)
	{
		pS_l_VerticalString += "\r\n" + pS_x_BaseString->Substring(i,1);
	}
	return pS_l_VerticalString;
}

String^ TUtilities::pS_DecryptBaseKey(String^ pS_x_String2Decrypt)
{
	pS_CryptKey = pS_BaseKey;
	pS_CryptKey = pS_Decrypt(pS_x_String2Decrypt);
	return pS_CryptKey;
}

String^ TUtilities::pS_Decrypt(String^ pS_x_String2Decrypt)
{
	Byte y_l_Data;
	array<Byte>^ py_l_CryptKey;
	array<Byte>^ py_l_Result;
	String^ pS_l_Result;
	int i_l_StringSize;
	System::Text::ASCIIEncoding^ pT_l_Converter = gcnew System::Text::ASCIIEncoding; 

	py_l_CryptKey = pT_l_Converter->GetBytes(pS_CryptKey);
	i_l_StringSize = pT_l_Converter->GetByteCount(pS_x_String2Decrypt)/2;
    py_l_Result = gcnew array<Byte>(i_l_StringSize);
	pS_l_Result = gcnew String("");

	for (int i=0;i<i_l_StringSize;i++)
	{
		// Convert hexa String to array of bytes
		y_l_Data = Convert::ToByte(pS_x_String2Decrypt->Substring(i*2,2), 16);
		py_l_Result[i] = y_l_Data^py_l_CryptKey[i%(pT_l_Converter->GetByteCount(pS_CryptKey)/sizeof(char))];
    }
	pS_l_Result = pT_l_Converter->GetString(py_l_Result);
	return pS_l_Result;
}

String^ TUtilities::pS_ReadAndDecryptData(StreamReader^ pT_x_File)
{
	return(pS_Decrypt(pT_x_File->ReadLine()));
}

bool TUtilities::b_GetXMLData(String^ pS_x_CurrentLine, String^ %pS_x_XMLTag, String^ %pS_x_XMLValue)
{
	bool b_l_Result = false;
	String^ pS_l_Delimiter = "<>";
	array<Char>^ pac_l_Delimiter = pS_l_Delimiter->ToCharArray();
	array<String^>^ paS_l_Splitdata;

	paS_l_Splitdata = pS_x_CurrentLine->Split(pac_l_Delimiter);
	if (paS_l_Splitdata->Length == 5)
	{
		pS_x_XMLTag = gcnew String(paS_l_Splitdata[1]);
		pS_x_XMLValue = gcnew String(paS_l_Splitdata[2]);
		b_l_Result = true;
	}
	return b_l_Result;
}


void TUtilities::SetVisible(Control^ oCtrl,bool bVisible)
{
	if (!bVisible)
	{
		oCtrl->Visible = false;
		return;
	}
	if (dynamic_cast<String ^>(oCtrl->Tag) != nullptr)
	{
		if (oCtrl->Tag == "0")
		{
			bVisible = true;
		}
		else if (oCtrl->Tag == "1")
		{
			bVisible = TUser::b_HasMaintenanceLevel();
		}
		else if (oCtrl->Tag == "2")
		{
			bVisible = TUser::b_HasSystemLevel();
		}
		else if (oCtrl->Tag == "10")
		{
			bVisible = false;
		}
		else
		{
			bVisible = true;
		}
	}
	else
	{
		bVisible = true;
	}
	oCtrl->Visible = bVisible;
}

void TUtilities::SetVisible(System::Windows::Forms::Control::ControlCollection^ Ctrls)
{
	for each (Control^ ctrl in Ctrls)
	{
		bool bVisible = false;
		bool bChangeVisible = true;

		if (dynamic_cast<String ^>(ctrl->Tag) != nullptr)
		{
			if (ctrl->Tag == "0")
			{
				bVisible = true;
			}
			else if (ctrl->Tag == "1")
			{
				bVisible = TUser::b_HasMaintenanceLevel();
			}
			else if (ctrl->Tag == "2")
			{
				bVisible = TUser::b_HasSystemLevel();
			}
			else if (ctrl->Tag == "10")
			{
				bVisible = false;
			}
			else
			{
				bChangeVisible = false;
			}
		}
		else
		{
			bChangeVisible = false;
		}
		if (bChangeVisible) ctrl->Visible = bVisible;
	}
}


