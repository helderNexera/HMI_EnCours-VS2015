#include "global.h"
#include "TLogger.h"
#include "TUtilities.h"
#include "MyMsgBox.h"

char* aac_MachineModes[] = { "Arrêtée","Init en cours", "Prêt", "En exécution","Tableau de bord", "Arrêt en cours", "En manuel","En pause","Demande de pause","Forçage Arrêt","Vidange"};
char* aac_ModuleStatus[] = { "Arrêté","Init en cours", "En exécution", "Prêt", "En manuel", "En pause" };
int i_g_LanguageNb;
bool b_g_UseTurnover = true;

static TUser::TUser(void)
{
	LockObj = gcnew System::Object();
}

void TUser::Clear(void)
{
	if (nullptr != S_Name)
		S_Name = "";
	if (nullptr != S_Team)
		S_Team = "";
	SetLevel(UL_Operator);
}

void TUser::SetName(String^ pS_x_NewName)
{
	if (nullptr == S_Name)
		S_Name = gcnew String("");
	S_Name = String::Copy( pS_x_NewName );
	SetLevel(UL_Operator);
}

void TUser::SetLevel(UserLevel s_x_NewLevel)
{
	s_Level = s_x_NewLevel;
	UserLevelChanged(nullptr, gcnew UserLevelChangedEventArgs(s_Level));
}

UserLevel TUser::GetLevel()
{
	return s_Level;
}

void TUser::SetTeam(String^ pS_x_NewTeam)
{
	if (nullptr == S_Team)
		S_Team = gcnew String("");
	S_Team = String::Copy( pS_x_NewTeam );
}

String^ TUser::pS_GetName(void)
{
	return S_Name;
}

String^ TUser::pS_GetTeam(void)
{
	return S_Team;
}

bool TUser::b_HasMaintenanceLevel(void)
{
	return ((s_Level == UL_Maintenance) || (s_Level == UL_Manager) || (s_Level == UL_System));
}

bool TUser::b_HasManagerLevel(void)
{
	return ((s_Level == UL_Manager) || (s_Level == UL_System));
}

bool TUser::b_HasSystemLevel(void)
{
	Monitor::Enter(LockObj);
	bool  bRet = (s_Level == UL_System);
	Monitor::Exit(LockObj);
	return bRet;
}

ProductionOrder::ProductionOrder(void)
{
	pS_OrderName = "";
	pS_ReferenceName = "";
	i_OrderQuantity = 0;
	pS_PlateType = "";
	pS_StartDate = "";
	pS_EndDate = "";
	ad_PartSensorOffset = gcnew array<double,2>(2,2) ;
	ad_PartOffset = gcnew array<double,2>(2,2) ;
	apT_PartsImage = gcnew array<Bitmap^>(2);
	pS_ReferenceName = "";

	ad_HeadOffset = gcnew array<double>(2);
	ad_HeadOffset[0] = 0;
	ad_HeadOffset[1] = 0;
	ad_PartSensorOffset[0,0] = 0;
	ad_PartSensorOffset[0,1] = 0;
	ad_PartSensorOffset[1,0] = 0;
	ad_PartSensorOffset[1,1] = 0;
	ad_PartOffset[0,0] = 0;
	ad_PartOffset[0,1] = 0;
	ad_PartOffset[1,0] = 0;
	ad_PartOffset[1,1] = 0;
	d_PartAndHeadHeight = 0;
	pS_VisionReferenceFileName = "";
	d_PartOffsetZLiftTake = 0;
	d_PartOffsetZLiftBadTake = 0;
	d_PartOffsetZLiftDrop = 0;
	d_PartOffsetThetaLiftDrop = 0;
	d_PartOffsetXLiftDrop = 0;
	d_PartOffsetYLiftDrop = 0;
	d_PartOffsetZLayeringTake = 0;
	d_PartOffsetZLayeringDrop = 0;
	d_PartOffsetZTurnOverDrop = 0;

	d_LayeringAndPartAndHeadHeight = 0;
	d_HeadSusPartHeadSousHeight = 0;
	d_PlateZOffsetForLift = 0;
	i_DropModeTable = 0;
	i_DropModeTurnOver = 0;
	i_TakeModeLift = 0;
	b_DropInBox = false;
}

void ProductionOrder::CloseOrder(void)
{
	pS_OrderName = "";
	pS_ReferenceName = "";
	i_OrderQuantity = 0;
	ad_HeadOffset[0] = 0;
	ad_HeadOffset[1] = 0;
	ad_PartSensorOffset[0,0] = 0;
	ad_PartSensorOffset[0,1] = 0;
	ad_PartSensorOffset[1,0] = 0;
	ad_PartSensorOffset[1,1] = 0;
	ad_PartOffset[0,0] = 0;
	ad_PartOffset[0,1] = 0;
	ad_PartOffset[1,0] = 0;
	ad_PartOffset[1,1] = 0;
	d_PartAndHeadHeight = 0;
	pS_VisionReferenceFileName = "";
	d_PartOffsetZLiftTake = 0;
	d_PartOffsetZLiftBadTake = 0;
	d_PartOffsetZLiftDrop = 0;
	d_PartOffsetThetaLiftDrop = 0;
	d_PartOffsetXLiftDrop = 0;
	d_PartOffsetYLiftDrop = 0;
	d_PartOffsetZLayeringTake = 0;
	d_PartOffsetZLayeringDrop = 0;
	d_PartOffsetZTurnOverDrop = 0;
	d_LayeringAndPartAndHeadHeight = 0;
	d_HeadSusPartHeadSousHeight = 0;
	d_PlateZOffsetForLift = 0;
	i_DropModeTable = 0;
	i_DropModeTurnOver = 0;
	i_TakeModeLift = 0;
	b_DropInBox = false;

}

void ProductionOrder::SetPartOffsetZLiftTake(double d_xZOffset)
{
	d_PartOffsetZLiftTake = d_xZOffset;
}

void ProductionOrder::SetPartOffsetZLiftBadTake(double d_xZOffset)
{
	d_PartOffsetZLiftBadTake = d_xZOffset;
}


void ProductionOrder::SetPartOffsetZLiftDrop(double d_xZOffset)
{
	d_PartOffsetZLiftDrop = d_xZOffset;
}

void ProductionOrder::SetPartOffsetThetaLiftDrop(double d_xZOffset)
{
	d_PartOffsetThetaLiftDrop = d_xZOffset;
}

void ProductionOrder::SetPartOffsetXLiftDrop(double d_xZOffset)
{
	d_PartOffsetXLiftDrop = d_xZOffset;
}

void ProductionOrder::SetPartOffsetYLiftDrop(double d_xZOffset)
{
	d_PartOffsetYLiftDrop = d_xZOffset;
}

void ProductionOrder::SetPartOffsetZLayeringTake(double d_xZOffset)
{
	d_PartOffsetZLayeringTake = d_xZOffset;
}

void ProductionOrder::SetPartOffsetZLayeringDrop(double d_xZOffset)
{
	d_PartOffsetZLayeringDrop = d_xZOffset;
}

void ProductionOrder::SetPartOffsetZTurnOverDrop(double d_xZOffset)
{
	d_PartOffsetZTurnOverDrop = d_xZOffset;
}

void ProductionOrder::SetPartOffsetZCleaning(double d_xZOffset)
{
	d_PartOffsetZCleaning = d_xZOffset;
}

double ProductionOrder::GetPartOffsetZLiftTake()
{
	return d_PartOffsetZLiftTake;
}

double ProductionOrder::GetPartOffsetZLiftBadTake()
{
	return d_PartOffsetZLiftBadTake;
}


double ProductionOrder::GetPartOffsetZLiftDrop()
{
	return d_PartOffsetZLiftDrop;
}

double ProductionOrder::GetPartOffsetThetaLiftDrop()
{
	return d_PartOffsetThetaLiftDrop;
}

double ProductionOrder::GetPartOffsetXLiftDrop()
{
	return d_PartOffsetXLiftDrop;
}

double ProductionOrder::GetPartOffsetYLiftDrop()
{
	return d_PartOffsetYLiftDrop;
}

double ProductionOrder::GetPartOffsetZLayeringTake()
{
	return d_PartOffsetZLayeringTake;
}

double ProductionOrder::GetPartOffsetZLayeringDrop()
{
	return d_PartOffsetZLayeringDrop;
}

double ProductionOrder::GetPartOffsetZTurnOverDrop()
{
	return d_PartOffsetZTurnOverDrop;
}

double ProductionOrder::GetPartOffsetZCleaning()
{
	return d_PartOffsetZCleaning;
}

void ProductionOrder::SetVisionReferenceFileName(String^ pS_x_VisionReferenceFileName)
{
	pS_VisionReferenceFileName = pS_x_VisionReferenceFileName;
}
String^ ProductionOrder::pS_GetVisionReferenceFileName(void)
{
	return pS_VisionReferenceFileName;
}

void ProductionOrder::SetName(String^ pS_x_NewName)
{
	pS_OrderName = gcnew String(pS_x_NewName);
}

void ProductionOrder::SetReference(String^ pS_x_ReferenceName)
{
	pS_ReferenceName = gcnew String(pS_x_ReferenceName);
	// Load reference data
	TUtilities::ReadReferenceFile(pS_ReferenceName);
}

void ProductionOrder::SetQuantity(int i_x_Quantity)
{
	i_OrderQuantity = i_x_Quantity;
}

void ProductionOrder::SetStartDate(String^ pS_x_StartDate)
{
	pS_StartDate = gcnew String(pS_x_StartDate);
}

void ProductionOrder::SetEndDate(String^ pS_x_EndDate)
{
	pS_EndDate = gcnew String(pS_x_EndDate);
}


String^ ProductionOrder::pS_GetName(void)
{
	return pS_OrderName;
}

String^ ProductionOrder::pS_GetReference(void)
{
	return pS_ReferenceName;
}

int ProductionOrder::i_GetQuantity(void)
{
	return i_OrderQuantity;
}

String^ ProductionOrder::pS_GetStartDate(void)
{
	return pS_StartDate;
}

String^ ProductionOrder::pS_GetEndDate(void)
{
	return pS_EndDate;
}

bool ProductionOrder::b_OrderStarted(void)
{
	return (pS_OrderName != "");
}

void ProductionOrder::SetPlateType(String^ pS_x_PlateName)
{
	pS_PlateType = gcnew String(pS_x_PlateName);
}

void ProductionOrder::SetPartSensorOffset(int i_x_Point,int i_x_Axis,double d_x_PartSensorOffset)
{
	ad_PartSensorOffset[i_x_Point,i_x_Axis] = d_x_PartSensorOffset;
}

void ProductionOrder::GetPartSensorOffset(int i_x_Point,double* ad_x_PartSensorOffset)
{
	ad_x_PartSensorOffset[0] = ad_PartSensorOffset[i_x_Point,0];
	ad_x_PartSensorOffset[1] = ad_PartSensorOffset[i_x_Point,1];
}

void ProductionOrder::SetHeadOffset(int i_x_Axis, double d_x_HeadOffset)
{
	ad_HeadOffset[i_x_Axis] = d_x_HeadOffset;
}

void ProductionOrder::GetHeadOffset(double* ad_x_HeadOffset)
{
	ad_x_HeadOffset[0] = ad_HeadOffset[0];
	ad_x_HeadOffset[1] = ad_HeadOffset[1];

}

void ProductionOrder::SetPartOffset(int i_x_Point,int i_x_Axis,double d_x_PartOffset)
{
	ad_PartOffset[i_x_Point,i_x_Axis] = d_x_PartOffset;
}

void ProductionOrder::GetPartOffset(int i_x_Point,double* ad_x_PartOffset)
{
	ad_x_PartOffset[0] = ad_PartOffset[i_x_Point,0];
	ad_x_PartOffset[1] = ad_PartOffset[i_x_Point,1];
}

void ProductionOrder::SetPartAndLayeringHeight(double d_x_PartAndLayeringHeight)
{
	d_PartAndLayeringHeight = d_x_PartAndLayeringHeight;
}

double ProductionOrder::d_GetPartAndLayeringHeight(void)
{
	return d_PartAndLayeringHeight;
}

void ProductionOrder::SetLayeringAndPartAndHeadHeight(double d_x_LayeringAndPartAndHeadHeight)
{
	d_LayeringAndPartAndHeadHeight = d_x_LayeringAndPartAndHeadHeight;
}

double ProductionOrder::d_GetLayeringAndPartAndHeadHeight(void)
{
	return d_LayeringAndPartAndHeadHeight;
}

void ProductionOrder::SetHeadSusPartHeadSousHeight(double d_x_HeadSusPartHeadSousHeight)
{
	d_HeadSusPartHeadSousHeight = d_x_HeadSusPartHeadSousHeight;
}

double ProductionOrder::d_GetHeadSusPartHeadSousHeight(void)
{
	return d_HeadSusPartHeadSousHeight;
}

void ProductionOrder::SetPlateZOffsetForLift(double d_x_PlateZOffsetForLift)
{
	d_PlateZOffsetForLift = d_x_PlateZOffsetForLift;
}

double ProductionOrder::d_GetPlateZOffsetForLift(void)
{
	return d_PlateZOffsetForLift;
}

void ProductionOrder::SetPartAndHeadHeight(double d_x_PartAndHeadHeight)
{
	d_PartAndHeadHeight = d_x_PartAndHeadHeight;
}

double ProductionOrder::d_GetPartAndHeadHeight(void)
{
	return d_PartAndHeadHeight;
}


void ProductionOrder::SetDropModeTable(int i_x_DropMode)
{
	i_DropModeTable = i_x_DropMode;
}

int ProductionOrder::i_GetDropModeTable(void)
{
	return i_DropModeTable;
}

void ProductionOrder::SetDropModeTurnOver(int i_x_DropMode)
{
	i_DropModeTurnOver = i_x_DropMode;
}

int ProductionOrder::i_GetDropModeTurnOver(void)
{
	return i_DropModeTurnOver;
}

void ProductionOrder::SetTakeModeLift(int i_x_TakeMode)
{
	i_TakeModeLift = i_x_TakeMode;
}

int ProductionOrder::i_GetTakeModeLift(void)
{
	return i_TakeModeLift;
}

void ProductionOrder::SetDropInBox(bool b_x_DropInBox)
{
	b_DropInBox = b_x_DropInBox;
}

bool ProductionOrder::b_GetDropInBox(void)
{
	return b_DropInBox;
}

void ProductionOrder::SetPartImage(Bitmap^ PartImage, int iIndex)
{
	apT_PartsImage[iIndex] = PartImage;
}

Bitmap^ ProductionOrder::GetPartImage(int iIndex)
{
	return apT_PartsImage[iIndex];
}

void ProductionOrder::GetPlateData(TC_PLATE_DATA* ps_x_PlateData)
{
	// Read the plate file to get plate data
	String^ pS_l_Delimiter = ";";
	array<Char>^ pac_l_Delimiter = pS_l_Delimiter->ToCharArray( );
	array<String^>^ paS_l_Splitdata;
	String^ pS_l_PlateFileName = gcnew String(C_APP_PLATES_PATH + pS_PlateType + ".MPC");
	int i_l_PlateSize = 0;
	int iLine = 0;
	String^ pS_l_CurrentLine = gcnew String("");
	bool b_l_FirstLine = true;

	ps_x_PlateData->PD_NbPartOnPlate = 0;
	for (int i=0;i<C_MAX_NB_OF_PARTS_ON_PLATE;i++)
	{
		ps_x_PlateData->PD_PartOnPlate[i].PXY_X = 0;
		ps_x_PlateData->PD_PartOnPlate[i].PXY_Y = 0;
	}
	try
	{
		if ( File::Exists(pS_l_PlateFileName) )
		{
			StreamReader^ pT_l_Reader = gcnew StreamReader(pS_l_PlateFileName,System::Text::Encoding::Default);
			try
			{
				while (pT_l_Reader->Peek() >= 0)
				{
					pS_l_CurrentLine = pT_l_Reader->ReadLine();
					if (b_l_FirstLine)
					{
						pS_l_CurrentLine = TUtilities::pS_DecryptBaseKey(pS_l_CurrentLine);
						b_l_FirstLine = false;
					}
					else
					{
						pS_l_CurrentLine = TUtilities::pS_Decrypt(pS_l_CurrentLine);
						paS_l_Splitdata = pS_l_CurrentLine->Split(pac_l_Delimiter);
						switch (iLine)
						{
						case 1:
							ps_x_PlateData->PD_UseVisionForDrop = (paS_l_Splitdata[0]->ToLower() == "true");
							break;
						case 2:
							ps_x_PlateData->PD_Height = Convert::ToDouble(paS_l_Splitdata[0]);
							break;
						case 3:
							ps_x_PlateData->PD_Edge = Convert::ToDouble(paS_l_Splitdata[0]);
							break;
						case 4:
							ps_x_PlateData->PD_TakerPlatePos.PXY_X = Convert::ToDouble(paS_l_Splitdata[0]);
							ps_x_PlateData->PD_TakerPlatePos.PXY_Y = Convert::ToDouble(paS_l_Splitdata[1]);
							break;
						case 5:
							ps_x_PlateData->PD_RejectCorrectionY = Convert::ToDouble(paS_l_Splitdata[0]);
							break;
						default:
							if (i_l_PlateSize >= C_MAX_NB_OF_PARTS_ON_PLATE)
							{
								MessageBox::Show("Error on plate file [" + pS_PlateType + "], too many lines", "ProductionOrder::GetPlateData");
								return;
							}
							else if (pS_l_CurrentLine->Length > 3)
							{
								ps_x_PlateData->PD_PartOnPlate[i_l_PlateSize].PXY_X = Convert::ToDouble(paS_l_Splitdata[0]);
								ps_x_PlateData->PD_PartOnPlate[i_l_PlateSize].PXY_Y = Convert::ToDouble(paS_l_Splitdata[1]);
								i_l_PlateSize++;
							}
							break;
						}
					}
					iLine++;
				}
			}
			finally
			{
				delete pT_l_Reader;
			}
		}
	}
	catch ( Exception^ e ) 
	{
		MessageBox::Show("Error on plate file :" + pS_l_PlateFileName + " with exception : " + e->Message, "ProductionOrder::GetPlateData");
	}
	ps_x_PlateData->PD_NbPartOnPlate = (TC_INT)i_l_PlateSize;

}
