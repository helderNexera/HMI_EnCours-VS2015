#include "string.h"

#include "MainWindow.h"
#include "TTwincatInterface.h"
#include "TLogger.h"
#include "global.h"
#include "MyMsgBox.h"

using namespace std;
using namespace Projet1;

//TTwincatInterface* pTTwincatInterface;
static bool	b_Connected;
static struct MACHINE_DATA s_MachineData; 
static struct MANUAL_DATA s_ManualData; 
static AmsAddr Addr; 
static PAmsAddr pAddr; 
static unsigned long n_TCMachineIndexOffset;
static unsigned long n_TCMachineIndexGroup;
static unsigned long n_TCManualIndexOffset;
static unsigned long n_TCManualIndexGroup;
static unsigned long n_TCConfigIndexGroup;
static unsigned long n_TCConfigIndexOffset;

TTwincatInterface::TTwincatInterface(char* pc_x_MachineVarName,char* pc_x_ManualVarName,char* pc_x_ConfigVarName,String^ AutomationNetID)
{
	long l_l_AdsError; 
	String^ pS_l_LogString;
	long l_l_Port; 
	unsigned char ay_l_buffer[0xFFFF];
	PAdsSymbolEntry ps_l_AdsSymbolEntry;

	b_Connected = false;

	l_l_Port = AdsPortOpen();
	pAddr = &Addr;
 	pAddr->port = AMSPORT_R0_PLC_TC3 /* AMSPORT_R0_PLC_RTS1*/;

	// Get the AMS net ID from command line
	String^ delimStr = " ,.:\t";
	array<Char>^ delimiter = delimStr->ToCharArray( );
   	array<String^>^ NetId = AutomationNetID->Split(delimiter);
	for (int i=0;i<6;i++)
		pAddr->netId.b[i] = Convert::ToByte(NetId[i]);

	// Get the information about the PLC-variable  
	l_l_AdsError = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_INFOBYNAMEEX, 0, sizeof(ay_l_buffer), ay_l_buffer, strlen(pc_x_MachineVarName)+1, pc_x_MachineVarName);
	if (l_l_AdsError) 
	{
		pS_l_LogString = String::Format("Error {0} on AdsSyncReadWriteReq with variable named {1}",l_l_AdsError.ToString(),gcnew String(pc_x_MachineVarName));
		TLogger::AddLog(pS_l_LogString);
	}
	else
	{
		ps_l_AdsSymbolEntry = (PAdsSymbolEntry)ay_l_buffer;
		if (ps_l_AdsSymbolEntry->size != sizeof(struct MACHINE_DATA))
		{
			int i_SizeStruct;

/*			TC_BOOL						b_ReadyForChangeJob;
			TC_BOOL						b_MachineInitDone;
			TC_BOOL						b_ResetErrors;
			TC_BOOL						b_ClearRates;
			TC_BOOL						b_NewJob;
			TC_BOOL						b_CloseJob;
			TC_BOOL						b_PurgeJob;
			TC_BOOL						b_MondemaMode;
			TC_BOOL						ab_Errors[C_MAX_NB_OF_ERRORS];
			TC_BOOL						ab_ValErrors[C_MAX_NB_OF_ERRORS];
			TC_INT						e_CurrentMode;
			TC_CHAR						ac_PartName[9];
			TC_INT						i_MajorVersion;
			TC_INT						i_MinorVersion;
			MACHINE_MODE_MASK			s_ModeMask;
			MACHINE_MODE_MASK			s_ModeReq;
			MODULE_DATA					s_ModLoader;
			MODULE_DATA					s_ModTable;
			MODULE_DATA					s_ModPearling;
			MODULE_DATA					s_ModSharpen;
			MODULE_DATA					s_ModTurnOver;
			MODULE_DATA					s_ModBarrel;
			MODULE_DATA					s_ModLift1;
			MODULE_DATA					s_ModLift2;
			MODULE_DATA					s_ModReject;
			MODULE_DATA					s_ModVision;
			MODULE_DATA					s_ModUtilities;
			MACHINE_OPTIONS				s_MachineOpt;
			PRODUCTION_LOT				s_ProdData;
			PRODUCTION_STATS			s_ProdStats;
			*/ i_SizeStruct = sizeof(DATA_LOG);/*
			DATA_LOG					s_PartData4Log;
			*/ i_SizeStruct = sizeof(MACHINE_MANUAL);/*
			MACHINE_MANUAL				s_MachineSafety;
			*/ i_SizeStruct = sizeof(OPERATOR_REQ);/*
			OPERATOR_REQ				s_OperatorRequest;
			*/ i_SizeStruct = sizeof(TC_STICK_DATA_MMI);/*
			TC_STICK_DATA_MMI			as_StickDataMMI[2];
			*/ i_SizeStruct = sizeof(TC_PEARL_DATA);/*
			TC_PEARL_DATA				as_PearlsData[2];
			*/ i_SizeStruct = sizeof(TC_STICK_DATA_MMI_SHARED);/*
			TC_STICK_DATA_MMI_SHARED	s_StickDataShared;
			TC_BOOL						b_EmergencyStop;
			TC_BOOL						b_DoorsPearling;
			TC_BOOL						b_DoorsLoader;
			TC_BOOL						b_SavePersistent;
			TC_INT						e_ManagerRunStep;
			*/ i_SizeStruct = sizeof(DASHBOARD_CMD);/*
			DASHBOARD_CMD				s_DashboardCmd;
			TC_BOOL						b_SimPearling;
			*/ i_SizeStruct = sizeof(PROBING_LOG);/*
			PROBING_LOG					as_ProbingLog[2];
			*/ i_SizeStruct = sizeof(PRODUCTION_CMD);/*
			PRODUCTION_CMD				s_ProductionCmd;
			TC_DWORD					dw_StartJobElapsedTime;
			*/ i_SizeStruct = sizeof(TC_COUNTER);/*
			TC_COUNTER					s_Counter;
*/
			i_SizeStruct = sizeof( TC_BOOL);
			i_SizeStruct = sizeof(struct TC_PLATE_DATA);
			i_SizeStruct = sizeof(struct TC_PART_DATA_MMI);
			i_SizeStruct = sizeof( TC_INT);
			i_SizeStruct = sizeof( TC_CHAR);
			i_SizeStruct = sizeof(struct MACHINE_MODE_MASK);
			i_SizeStruct = sizeof(struct MODULE_DATA);
			i_SizeStruct = sizeof(struct MACHINE_OPTIONS);
			i_SizeStruct = sizeof(struct PRODUCTION_LOT);
			i_SizeStruct = sizeof(struct PRODUCTION_STATS);
			i_SizeStruct = sizeof(struct DATA_LOG);
			i_SizeStruct = sizeof(struct MACHINE_MANUAL);
			i_SizeStruct = sizeof(struct OPERATOR_REQ);
			i_SizeStruct = sizeof(struct TC_STICK_DATA_MMI);
			i_SizeStruct = sizeof(struct TC_PEARL_DATA);


			pS_l_LogString = String::Format("The communication machine variable has not the same size. CPU : {0}, MMI : {1}",ps_l_AdsSymbolEntry->size.ToString(),sizeof(struct MACHINE_DATA));
			TLogger::AddLog(pS_l_LogString);
			l_l_AdsError = 1;
		}
		else
		{
			n_TCMachineIndexGroup = ps_l_AdsSymbolEntry->iGroup;
			n_TCMachineIndexOffset = ps_l_AdsSymbolEntry->iOffs;
			l_l_AdsError = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_INFOBYNAMEEX, 0, sizeof(ay_l_buffer), ay_l_buffer, strlen(pc_x_ManualVarName)+1, pc_x_ManualVarName);
			if (l_l_AdsError) 
			{
				pS_l_LogString = String::Format("Error {0} on AdsSyncReadWriteReq with variable named {1}",l_l_AdsError.ToString(),gcnew String(pc_x_ManualVarName));
				TLogger::AddLog(pS_l_LogString);
			}
			else
			{
				ps_l_AdsSymbolEntry = (PAdsSymbolEntry)ay_l_buffer;
				if (ps_l_AdsSymbolEntry->size != sizeof(struct MANUAL_DATA))
				{
					int i_SizeStruct;
					
					i_SizeStruct = sizeof(TC_LREAL);
					i_SizeStruct = sizeof(struct TC_MAN_DRIVE);
					i_SizeStruct = sizeof(struct TC_MAN_DRIVE_POS);
					i_SizeStruct = sizeof(struct MAN_LOADER);
					i_SizeStruct = sizeof(struct MAN_TABLE);
					i_SizeStruct = sizeof(struct MAN_PEARLING);
					i_SizeStruct = sizeof(struct MAN_TURN_OVER);
					i_SizeStruct = sizeof(struct MAN_BARREL);
					i_SizeStruct = sizeof(struct MAN_SHARPEN);
					i_SizeStruct = sizeof(struct MANUAL_DATA);

					pS_l_LogString = String::Format("The communication manual variable has not the same size. CPU : {0}, MMI : {1}",ps_l_AdsSymbolEntry->size.ToString(),sizeof(struct MANUAL_DATA));
					TLogger::AddLog(pS_l_LogString);
					l_l_AdsError = 1;
				}
				else
				{
					n_TCManualIndexGroup = ps_l_AdsSymbolEntry->iGroup;
					n_TCManualIndexOffset = ps_l_AdsSymbolEntry->iOffs;
					l_l_AdsError = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_INFOBYNAMEEX, 0, sizeof(ay_l_buffer), ay_l_buffer, strlen(pc_x_ConfigVarName)+1, pc_x_ConfigVarName);
					if (l_l_AdsError) 
					{
						pS_l_LogString = String::Format("Error {0} on AdsSyncReadWriteReq with variable named {1}",l_l_AdsError.ToString(),gcnew String(pc_x_ConfigVarName));
						TLogger::AddLog(pS_l_LogString);
					}
					else
					{
						ps_l_AdsSymbolEntry = (PAdsSymbolEntry)ay_l_buffer;
						if (ps_l_AdsSymbolEntry->size != sizeof(struct CONFIG_DATA))
						{
							int i_SizeStruct;

							i_SizeStruct = sizeof(struct PEARLING_TABLE);
							i_SizeStruct = sizeof(struct TC_STICK_DATA);
							i_SizeStruct = sizeof(struct CONFIG_DATA);
							i_SizeStruct = sizeof(struct TC_PEARLING_DATA);
							i_SizeStruct = sizeof(struct CONFIG_DATA);

							pS_l_LogString = String::Format("The communication config variable has not the same size. CPU : {0}, MMI : {1}",ps_l_AdsSymbolEntry->size.ToString(),sizeof(struct CONFIG_DATA));
							TLogger::AddLog(pS_l_LogString);
							l_l_AdsError = 1;
						}
						else
						{
							n_TCConfigIndexGroup = ps_l_AdsSymbolEntry->iGroup;
							n_TCConfigIndexOffset = ps_l_AdsSymbolEntry->iOffs;
							b_Connected = true;
						}
					}
				}
			}
		}
	}
	if (l_l_AdsError) 
	{
		MyMsgBox^ pT_l_ADSError = gcnew MyMsgBox("Erreur au niveau de la connexion Twincat ADS !\n\rPlus de détails se trouvent dans le fichier log.\n\r\n\rL'application ne fonctionnera pas correctement.","Erreur fatal Twincat ADS",MessageBoxButtons::OK);
		pT_l_ADSError->ShowDialog();
	}
}

TTwincatInterface::~TTwincatInterface(void)
{
	long l_l_AdsError;

	l_l_AdsError = AdsPortClose();
}

bool TTwincatInterface::IsConnected(void)
{
#ifdef C_SIMULATION
	return true;
#else
	return b_Connected;
#endif
}

TTwincatInterface^ TTwincatInterface::GetTCVarAccess(void)
{
	return pTTwincatInterface;
}

void TTwincatInterface::SetThisPtr(TTwincatInterface^ NewPtr)
{
	pTTwincatInterface = NewPtr;
}

bool TTwincatInterface::bReadAllData(void)
{
	bool b_l_Result = false;
	long l_l_AdsError = 0;
	String^ S_l_LogString;

	if (b_Connected){
		l_l_AdsError = AdsSyncReadReq( pAddr, n_TCMachineIndexGroup, n_TCMachineIndexOffset, sizeof(s_MachineData), &s_MachineData ); 
	    if (l_l_AdsError){
			S_l_LogString = String::Format("Error {0} on AdsSyncReadReq with machiine variable",l_l_AdsError.ToString());
			TLogger::AddLog(S_l_LogString);
		} else {
			// Check if we must read also manual data
			if (MM_Manual == s_MachineData.e_CurrentMode)
			{
				l_l_AdsError = AdsSyncReadReq( pAddr, n_TCManualIndexGroup, n_TCManualIndexOffset, sizeof(s_ManualData), &s_ManualData ); 
				if (l_l_AdsError){
					S_l_LogString = String::Format("Error {0} on AdsSyncReadReq with manual variable",l_l_AdsError.ToString());
					TLogger::AddLog(S_l_LogString);
				}
			}
		}
	}
	return (l_l_AdsError == 0);
}

void TTwincatInterface::GetErrorData(int i_x_Index,bool* pb_x_Value)
{
	this->TCVarAccess.WaitOne();
	*pb_x_Value = (0 != s_MachineData.ab_Errors[i_x_Index]);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::GetValErrorData(int i_x_Index,bool* pb_x_Value)
{
	this->TCVarAccess.WaitOne();
	*pb_x_Value = (0 != s_MachineData.ab_ValErrors[i_x_Index]);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::WriteData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,void* pv_x_Value,unsigned long n_x_DataSize)
{
	long l_l_AdsError;
	String^ S_l_LogString;

	if (b_Connected){
		this->TCVarAccess.WaitOne();
		if (b_Connected){
			if (DVT_Global == e_x_DataVarType){
				l_l_AdsError = AdsSyncWriteReq( pAddr, n_TCMachineIndexGroup, n_TCMachineIndexOffset + n_x_Offset, n_x_DataSize, pv_x_Value );
				if (l_l_AdsError){
					S_l_LogString = String::Format("Error {0} on AdsSyncReadReq with variable at adress {1}",l_l_AdsError.ToString(),n_x_Offset.ToString());
					TLogger::AddLog(S_l_LogString);
				}
			} else if (DVT_Manual == e_x_DataVarType) {
				l_l_AdsError = AdsSyncWriteReq( pAddr, n_TCManualIndexGroup, n_TCManualIndexOffset + n_x_Offset, n_x_DataSize, pv_x_Value );
				if (l_l_AdsError){
					S_l_LogString = String::Format("Error {0} on AdsSyncReadReq with variable at adress {1}",l_l_AdsError.ToString(),n_x_Offset.ToString());
					TLogger::AddLog(S_l_LogString);
				}
			} else if (DVT_Config == e_x_DataVarType) {
				l_l_AdsError = AdsSyncWriteReq( pAddr, n_TCConfigIndexGroup, n_TCConfigIndexOffset + n_x_Offset, n_x_DataSize, pv_x_Value );
				if (l_l_AdsError){
					S_l_LogString = String::Format("Error {0} on AdsSyncReadReq with variable at adress {1}",l_l_AdsError.ToString(),n_x_Offset.ToString());
					TLogger::AddLog(S_l_LogString);
				}
			}
		}
		this->TCVarAccess.ReleaseMutex();
	}
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_BYTE* py_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*py_x_Value = *((TC_BYTE*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_BYTE y_x_Value)
{
	WriteData(e_x_DataVarType,n_x_Offset,&y_x_Value,sizeof(TC_BYTE));
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_UINT* pn_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*pn_x_Value = *((TC_UINT*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_UINT n_x_Value)
{
	WriteData(e_x_DataVarType,n_x_Offset,&n_x_Value,sizeof(TC_UINT));
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_INT* pi_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*pi_x_Value = *((TC_INT*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_INT i_x_Value)
{
	WriteData(e_x_DataVarType,n_x_Offset,&i_x_Value,sizeof(TC_INT));
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_DWORD* pn_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*pn_x_Value = *((TC_DWORD*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_DWORD d_x_Value)
{
	WriteData(e_x_DataVarType,n_x_Offset,&d_x_Value,sizeof(TC_DWORD));
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_REAL* pf_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*pf_x_Value = *((TC_REAL*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_REAL f_x_Value)
{
	WriteData(e_x_DataVarType,n_x_Offset,&f_x_Value,sizeof(TC_REAL));
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_LREAL* pd_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*pd_x_Value = *((TC_LREAL*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_LREAL d_x_Value)
{
	WriteData(e_x_DataVarType,n_x_Offset,&d_x_Value,sizeof(TC_LREAL));
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,DATA_LOG* ps_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*ps_x_Value = *((DATA_LOG*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_PEARL_DATA* ps_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*ps_x_Value = *((TC_PEARL_DATA*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType, unsigned int n_x_Offset, PROBING_LOG* ps_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType) ? (unsigned char*)(&s_MachineData) : (unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*ps_x_Value = *((PROBING_LOG*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}


void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_CHAR* pc_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType)?(unsigned char*)(&s_MachineData):(unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	strcpy_s(pc_x_Value,TC_STRING_SIZE,(TC_CHAR*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}

void TTwincatInterface::GetData(enum DataVarType e_x_DataVarType, unsigned int n_x_Offset, TC_TIME* ps_x_Value)
{
	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (DVT_Global == e_x_DataVarType) ? (unsigned char*)(&s_MachineData) : (unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	*ps_x_Value = *((TC_TIME*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
}


void TTwincatInterface::SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_CHAR* pc_x_Value)
{
	WriteData(e_x_DataVarType,n_x_Offset,pc_x_Value,strlen(pc_x_Value)+1);
}

void TTwincatInterface::SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,void* plr_x_Data,int i_x_DataSize)
{
	WriteData(e_x_DataVarType,n_x_Offset,plr_x_Data,i_x_DataSize * sizeof(TC_LREAL));
}

TC_BOOL TTwincatInterface::bInvTC(TC_BOOL b_x_Data)
{
	return (b_x_Data?0:1);
}

TC_MAN_BUTTON TTwincatInterface::GetManButtonData(unsigned int n_x_Offset)
{
	TC_MAN_BUTTON T_l_ManButton;

	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (unsigned char*)(&s_ManualData);
	py_l_Data += n_x_Offset;
	T_l_ManButton = *((TC_MAN_BUTTON*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
	return T_l_ManButton;
}

TC_MAN_BUTTON TTwincatInterface::GetButtonData(unsigned int n_x_Offset)
{
	TC_MAN_BUTTON T_l_ManButton;

	this->TCVarAccess.WaitOne();
	unsigned char* py_l_Data = (unsigned char*)(&s_MachineData);
	py_l_Data += n_x_Offset;
	T_l_ManButton = *((TC_MAN_BUTTON*)py_l_Data);
	this->TCVarAccess.ReleaseMutex();
	return T_l_ManButton;
}

void TTwincatInterface::WriteConfig(struct CONFIG_DATA* ps_x_ConfigData)
{
	WriteData(DVT_Config,0,ps_x_ConfigData,sizeof(struct CONFIG_DATA));
}
