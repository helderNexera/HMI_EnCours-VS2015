#pragma once

#include "global.h"
#include "TJobLogger.h"
#include "TUtilities.h"

using namespace System::Globalization;


static TJobLogger::TJobLogger()
{
	pS_JobFile = nullptr;
	pS_LastRejectPlate = "";
	apS_RejectPart = gcnew Dictionary<String^, List<PartData^>^>();
}

void TJobLogger::CloseJobFile()
{
	if (pS_JobFile)
		delete (IDisposable^)pS_JobFile;
	pS_JobFile = nullptr;
}

void TJobLogger::CreateLog()
{
	CloseJobFile();
	String^ pS_l_LogLine = gcnew String("");
	String^ pS_JobFileName = C_APP_ORDER_PATH + ProductionOrder::pS_GetName() + ".csv";

	bool b_x_NewJob = !File::Exists(pS_JobFileName);

	FileStream^ fs = gcnew FileStream(pS_JobFileName, FileMode::OpenOrCreate, FileAccess::Write);
	pS_JobFile = gcnew StreamWriter(fs);
	//pS_JobFile = gcnew StreamWriter(pS_JobFileName);
	//pS_JobFile = File::AppendText(pS_JobFileName);
	//pS_JobFile = File::CreateText(pS_JobFileName);
	//pS_JobFile = gcnew StreamWriter(pS_JobFileName,true);
	//pS_JobFile = File::CreateText(pS_JobFileName,);
	pS_JobFile->BaseStream->Seek(0, SeekOrigin::End);
	pS_JobFile->AutoFlush = true;
	if (b_x_NewJob)
	{
		pS_JobFile->WriteLine(pS_Header1);
		pS_l_LogLine = TUtilities::pS_FormatDateTime(nullptr) + ";" +
			"000:00:00;" +
			ProductionOrder::pS_GetReference() + ";" +
			ProductionOrder::i_GetQuantity().ToString();
		pS_JobFile->WriteLine(pS_l_LogLine);
		pS_JobFile->WriteLine(pS_Header2);
		pS_JobFile->Flush();
	}
}

void TJobLogger::UpdateStartTime(DateTime^ dtStartTime)
{
	String^ pS_l_LogLine = gcnew String("");
	
	if (pS_JobFile == nullptr) return;

	String^ sHeader = pS_Header1 + Environment::NewLine;
	pS_JobFile->BaseStream->Seek(GetWriteLength(sHeader), SeekOrigin::Begin);
	pS_l_LogLine = TUtilities::pS_FormatDateTime(dtStartTime);
	pS_JobFile->Write(pS_l_LogLine);
	pS_JobFile->BaseStream->Seek(0, SeekOrigin::End);
	pS_JobFile->Flush();
}

void TJobLogger::UpdateDuration(TimeSpan^ tDuration)
{
	String^ pS_l_LogLine = gcnew String("");

	if (pS_JobFile == nullptr) return;
	if (*tDuration > TimeSpan(999, 59, 59)) tDuration = TimeSpan(999, 59, 59);
	String^ sHeader = pS_Header1 + Environment::NewLine + TUtilities::pS_FormatDateTime(nullptr) + ";";
	pS_JobFile->BaseStream->Seek(GetWriteLength(sHeader), SeekOrigin::Begin);
	pS_l_LogLine = ((int)Math::Truncate(tDuration->TotalHours)).ToString("D3") + ":" + tDuration->Minutes.ToString("D2") + ":" + tDuration->Seconds.ToString("D2");
	pS_JobFile->Write(pS_l_LogLine);
	pS_JobFile->BaseStream->Seek(0, SeekOrigin::End);
	pS_JobFile->Flush();
}

int TJobLogger::GetWriteLength(String^ sText)
{
	int iSize = pS_JobFile->Encoding->GetByteCount(sText);
	return iSize;
}


void TJobLogger::CloseLog()
{
	CloseJobFile();
}

String^ TJobLogger::FormatTime(TimeSpan^ tTime)
{
	return ((int)Math::Truncate(tTime->TotalMinutes)).ToString() + ":" + tTime->Seconds.ToString("D2");
}

TimeSpan^  TJobLogger::ReadTime(String^ sTime)
{
	int iHours = 0;
	int iMinutes = 0;
	int iSeconds = 0;

	array<String^>^ paS_l_Splitdata = sTime->Split(':');
	if (paS_l_Splitdata->Length == 2)
	{
		iMinutes = int::Parse(paS_l_Splitdata[0]);
		iSeconds = int::Parse(paS_l_Splitdata[1]);
	}
	else
	{
		iHours = int::Parse(paS_l_Splitdata[0]);
		iMinutes = int::Parse(paS_l_Splitdata[1]);
		iSeconds = int::Parse(paS_l_Splitdata[2]);
	}
	return gcnew TimeSpan(iHours, iMinutes, iSeconds);
}

void TJobLogger::AddJobPartLog(PART_DATA s_x_PartData,bool bEndOfProd)
{
	String^ pS_l_LogLine = gcnew String("");

	if (pS_JobFile != nullptr)
	{
		PartData^ oPart = gcnew PartData(s_x_PartData);
		String^ sStatus = "";

		// Add a line with part data in the log for the current job
		// Format : DateTime;OK;Station error
		String^ sDate = TUtilities::pS_FormatDateTime(DateTime::Now);
		if (bEndOfProd)
		{
			ProductionOrder::SetEndDate(sDate);
		}
		pS_l_LogLine = sDate + ";";
		pS_l_LogLine += FormatTime(oPart->tProductionInTime) + ";";
		pS_l_LogLine += FormatTime(oPart->tProductionOutTime) + ";";
		pS_l_LogLine += FormatTime(oPart->tProductionTime) + ";";
		if (oPart->bRejected)
		{
			sStatus = "Chute";
			AddRejectPart(oPart);
			UpdateRejectPart(oPart->iPlateOutPos);
		}
		else if (oPart->bSample)
		{
			sStatus = "Sample";
			AddRejectPart(oPart);
			UpdateRejectPart(oPart->iPlateOutPos);
		}
		else
		{
			sStatus = "OK";
		}
		pS_l_LogLine += sStatus + ";";
		pS_l_LogLine += String::Join("/", oPart->RejectReason) + ";";
		pS_l_LogLine += oPart->PlateInQRCode + ";";
		pS_l_LogLine += oPart->iPlateInPos + ";";
		pS_l_LogLine += oPart->PlateOutQRCode + ";";
		pS_l_LogLine += oPart->iPlateOutPos + ";";
		pS_JobFile->WriteLine(pS_l_LogLine);
		pS_JobFile->Flush();
	}
}


enum JobFileCheckResult TJobLogger::e_GetJobLogData(String^ pS_x_JobName, String^ pS_x_Caliber, Int32 i_x_Quantity, unsigned long* pn_x_GoodQty, unsigned long* pn_x_TotalQty, String^% pS_x_StartDate, String^% pS_x_EndDate, TimeSpan^% pS_x_Duration)
{
	enum JobFileCheckResult e_l_Result = JFCR_NoFile;
	String^ pS_l_Delimiter = ";";
	array<Char>^ pac_l_Delimiter = pS_l_Delimiter->ToCharArray();
	array<String^>^ paS_l_Splitdata;
	String^ pS_l_Line;

	String^ pS_l_JobFileName = C_APP_ORDER_PATH + pS_x_JobName + ".csv";

	// Clear reject plate list
	apS_RejectPart->Clear();
	pS_LastRejectPlate = "";

	if (File::Exists(pS_l_JobFileName))
	{
		StreamReader^ pT_l_ReadFile = gcnew StreamReader(pS_l_JobFileName);
		*pn_x_GoodQty = 0;
		*pn_x_TotalQty = 0;

		try
		{
			int iLastPos = -1;

			e_l_Result = JFCR_BadData;
			// Read job data
			pS_l_Line = pT_l_ReadFile->ReadLine(); // Header1
			pS_l_Line = pT_l_ReadFile->ReadLine(); // Data
			paS_l_Splitdata = pS_l_Line->Split(pac_l_Delimiter);
			pS_l_Line = pT_l_ReadFile->ReadLine(); // Header2
			pS_x_Duration = ReadTime(paS_l_Splitdata[1]);
			if ((pS_x_Caliber == paS_l_Splitdata[2]) && (i_x_Quantity.ToString() == paS_l_Splitdata[3]))
			{
				pS_x_StartDate = paS_l_Splitdata[0];
				if (pS_x_StartDate->StartsWith("?")) pS_x_StartDate = "";
				// Read parts data until end of file
				while (pS_l_Line = pT_l_ReadFile->ReadLine())
				{
					(*pn_x_TotalQty)++;
					paS_l_Splitdata = pS_l_Line->Split(pac_l_Delimiter);
					// Fill reject data
					PartData^ oPart = gcnew PartData();
					oPart->tProductionInTime = ReadTime(paS_l_Splitdata[1]);
					oPart->tProductionOutTime = ReadTime(paS_l_Splitdata[2]);
					oPart->tProductionTime = ReadTime(paS_l_Splitdata[3]);
					String^ sStatus = paS_l_Splitdata[4];
					oPart->RejectReason->AddRange(paS_l_Splitdata[5]->Split('/'));
					oPart->PlateInQRCode = paS_l_Splitdata[6];
					oPart->iPlateInPos = int::Parse(paS_l_Splitdata[7]);
					oPart->PlateOutQRCode = paS_l_Splitdata[8];
					oPart->iPlateOutPos = int::Parse(paS_l_Splitdata[9]);

					if ("OK" == sStatus)
					{
						(*pn_x_GoodQty)++;
						oPart->bSample = false;
						oPart->bRejected = false;
					}
					else if ("Sample" == sStatus)
					{
						(*pn_x_GoodQty)++;
						oPart->bSample = true;
						oPart->bRejected = false;
						AddRejectPart(oPart);
						iLastPos = oPart->iPlateOutPos;
					}
					else if ("Chute" == sStatus)
					{
						oPart->bSample = false;
						oPart->bRejected = true;
						AddRejectPart(oPart);
						iLastPos = oPart->iPlateOutPos;
					}
				}
				if ((int)(*pn_x_GoodQty) >= i_x_Quantity)
				{
					pS_x_EndDate = paS_l_Splitdata[0];
				}
				e_l_Result = JFCR_OK;
				UpdateRejectPart(iLastPos);
			}
		}
		finally
		{
			if (pT_l_ReadFile)
				delete (IDisposable^)pT_l_ReadFile;
		}
	}
	return e_l_Result;
}


void TJobLogger::AddRejectPart(PartData^ oPart)
{
	String^ sPlateQRCode = oPart->PlateOutQRCode;
	if (!apS_RejectPart->ContainsKey(sPlateQRCode))
	{
		apS_RejectPart->Add(sPlateQRCode, gcnew List<PartData^>());
	}
	for each (PartData^ oPartEnum in apS_RejectPart[sPlateQRCode])
	{
		if (oPartEnum->iPlateOutPos == oPart->iPlateOutPos)
		{
			apS_RejectPart[sPlateQRCode]->Remove(oPartEnum);
			break;
		}
	}
	apS_RejectPart[sPlateQRCode]->Add(oPart);
	pS_LastRejectPlate = sPlateQRCode;
}

Dictionary<String^, List<PartData^>^>^ TJobLogger::GetRejectedParts([Out] String^% sLastRejectPlate)
{
	sLastRejectPlate = pS_LastRejectPlate;
	return apS_RejectPart;
}

