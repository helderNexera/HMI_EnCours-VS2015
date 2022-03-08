#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

#include "global.h"
#include "TTwincatInterface.h"

enum JobFileCheckResult { JFCR_OK, JFCR_NoFile, JFCR_BadData };


ref class PartData
{
private:
	String^ m_sPlateInQRCode;
	int m_iPlateInPos;
	String^ m_sPlateOutQRCode;
	int m_iPlateOutPos;
	bool m_bRejected;
	bool m_bSample;
	TimeSpan^ m_tProductionTime;
	TimeSpan^ m_tProductionInTime;
	TimeSpan^ m_tProductionOutTime;
	List<String^>^ m_lsRejectReason;

public:
	PartData()
	{
		m_sPlateInQRCode = "";
		m_sPlateOutQRCode = "";
		m_iPlateInPos = 0;
		m_iPlateOutPos = 0;
		m_bRejected = false;
		m_bSample = false;
		m_tProductionTime = TimeSpan::Zero;
		m_tProductionInTime = TimeSpan::Zero;
		m_tProductionOutTime = TimeSpan::Zero;
		m_lsRejectReason = gcnew List<String^>();
	}

	PartData(struct PART_DATA s_x_PartData)
	{
		array<String^>^ asRejectReasonHead = { "Perlage Tête 1","Perlage Tête 2" };
		array<String^>^ asRejectReasonSide = { "Sus","Sous" };

		
		m_iPlateInPos = s_x_PartData.CD_PlateInPos;
		m_iPlateOutPos = s_x_PartData.CD_PlateOutPos;
		m_bRejected = (s_x_PartData.CD_Rejected != 0);
		m_bSample = (s_x_PartData.CD_Sample != 0);
		m_sPlateInQRCode = s_x_PartData.CD_PlateInQRCode == 0 ? "" : s_x_PartData.CD_PlateInQRCode.ToString();
		m_sPlateOutQRCode = s_x_PartData.CD_PlateOutQRCode == 0 ? "" : s_x_PartData.CD_PlateOutQRCode.ToString();
		m_tProductionTime = TimeSpan::FromMilliseconds(s_x_PartData.CD_ProductionTime);
		m_tProductionInTime = TimeSpan::FromMilliseconds(s_x_PartData.CD_ProductionInTime);
		m_tProductionOutTime = TimeSpan::FromMilliseconds(s_x_PartData.CD_ProductionOutTime);

		m_lsRejectReason = gcnew List<String^>();
		for (int iHead = 0; iHead < 2; iHead++)
		{
			for (int iSide = 0; iSide < 2; iSide++)
			{
				bool bBadPearling = ((s_x_PartData.CD_BadPearling[iHead][iSide]) != 0);
				if (bBadPearling)
				{
					String^ sRejectReason = asRejectReasonHead[iHead] + " " + asRejectReasonSide[iSide];
					m_lsRejectReason->Add(sRejectReason);
				}
			}
		}
	}
	

	property bool bRejected
	{
		bool get()
		{
			return m_bRejected;
		}

		void set(bool value)
		{
			m_bRejected = value;
		}
	}

	property bool bSample
	{
		bool get()
		{
			return m_bSample;
		}

		void set(bool value)
		{
			m_bSample = value;
		}
	}


	property int iPlateInPos
	{
		int get()
		{
			return m_iPlateInPos;
		}

		void set(int value)
		{
			m_iPlateInPos = value;
		}
	}

	property int iPlateOutPos
	{
		int get()
		{
			return m_iPlateOutPos;
		}

		void set(int value)
		{
			m_iPlateOutPos = value;
		}
	}

	property TimeSpan^ tProductionTime
	{
		TimeSpan^ get()
		{
			return m_tProductionTime;
		}

		void set(TimeSpan^ value)
		{
			m_tProductionTime = value;
		}
	}

	property TimeSpan^ tProductionInTime
	{
		TimeSpan^ get()
		{
			return m_tProductionInTime;
		}

		void set(TimeSpan^ value)
		{
			m_tProductionInTime = value;
		}
	}

	property TimeSpan^ tProductionOutTime
	{
		TimeSpan^ get()
		{
			return m_tProductionOutTime;
		}

		void set(TimeSpan^ value)
		{
			m_tProductionOutTime = value;
		}
	}

	property List<String^>^ RejectReason
	{
		List<String^>^ get()
		{
			return m_lsRejectReason;
		}

		void set(List<String^>^ value)
		{
			m_lsRejectReason = value;
		}
	}

	property String^ PlateOutQRCode
	{
		String^ get()
		{
			return m_sPlateOutQRCode;
		}

		void set(String^ value)
		{
			m_sPlateOutQRCode = value;
		}
	}

	property String^ PlateInQRCode
	{
		String^ get()
		{
			return m_sPlateInQRCode;
		}

		void set(String^ value)
		{
			m_sPlateInQRCode = value;
		}
	}


};

delegate void EventUpdateRejectPart(int);

ref class TJobLogger
{

private:
	literal String^ pS_Header1 = "Date;Durée;Référence;Quantité";
	literal String^ pS_Header2 = "Date;Entrée de production;Sortie de production;Durée de production;État;Raison du rejet;Réference Palette entrée;Position palette entrée;Réference Palette sortie;Position palette sortie";

	static Dictionary<String^, List<PartData^>^>^ apS_RejectPart;
	static StreamWriter^ pS_JobFile;
	static String^ pS_LastRejectPlate;

	static void AddRejectPart(PartData^ oPart);
	static String^ FormatTime(TimeSpan^ tTime);
	static TimeSpan^ ReadTime(String^ sTime);
	static int GetWriteLength(String^ sText);
	static void CloseJobFile();

public:
	static TJobLogger();

	static event EventUpdateRejectPart^ UpdateRejectPart;
	static void CreateLog();
	static void CloseLog();
	static enum JobFileCheckResult e_GetJobLogData(String^ pS_x_Message, String^ pS_x_Caliber, Int32 i_x_Quantity, unsigned long* pn_x_GoodQty, unsigned long* pn_l_TotalQty, String^% pS_x_StartDate, String^% pS_x_EndDate, TimeSpan^% pS_x_Duration);
	static void AddJobPartLog(struct PART_DATA s_x_PartData, bool bEndOfProd);
	static Dictionary<String^, List<PartData^>^>^ GetRejectedParts([Out] String^% sLastRejectPlate);
	static void UpdateStartTime(DateTime^ dtStartTime);
	static void UpdateDuration(TimeSpan^ tDuration);
};

