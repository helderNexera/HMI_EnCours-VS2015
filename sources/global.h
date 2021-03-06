#pragma once

using namespace System;
using namespace System::Drawing;

#define C_MAJOR_VERSION 1
#define C_MINOR_VERSION 5

#define C_REG_BASE_KEY L"PERLAGE_HMI"

#define C_APP_ROOT_PATH L"C:\\MPS_HMI\\"
#define C_APP_CONFIG_PATH C_APP_ROOT_PATH + L"config\\"
#define C_APP_REFERENCES_PATH C_APP_ROOT_PATH + L"references\\"
#define C_APP_PLATES_PATH C_APP_REFERENCES_PATH + L"plates\\"
#define C_APP_LOGS_PATH C_APP_ROOT_PATH + L"logs\\"
#define C_APP_RSC_PATH C_APP_ROOT_PATH + L"ressources\\"
#define C_APP_ORDER_PATH C_APP_ROOT_PATH + L"of\\"
#define C_APP_PARAMS_PATH C_APP_ROOT_PATH + L"params\\"
#define C_APP_IMAGES_PATH C_APP_ROOT_PATH + "images\\"
#define C_APP_EXPORT_PATH C_APP_ROOT_PATH + L"exports\\"
#define C_APP_PROBING_LOGS_PATH C_APP_ROOT_PATH + L"probing\\"

#define C_AUTOMATION_VAR "MAIN.sMMI_SyncVar"
#define C_MANUAL_VAR "MAIN.sMMI_ManualVar"
#define C_CONFIG_VAR "MAIN.sMMI_ConfigFileData"

#define C_VISION_APP "PearlingVision"
#define C_VISION_SW C_APP_ROOT_PATH + "bin\\" + C_VISION_APP + ".exe"

//#define C_SIMULATION

#define C_NB_OF_LANGUAGES 2

#define C_NB_OF_REJECT_PLATES 500
#define C_MAX_NB_OF_PEARLS 601

#define C_PROD_RATE_ARRAY_SIZE 3

enum UserLevel {UL_Operator,UL_Maintenance,UL_Manager,UL_System};
extern char* aac_MachineModes[];
extern char* aac_ModuleStatus[];
extern int i_g_LanguageNb;
extern bool b_g_UseTurnover;

ref class UserLevelChangedEventArgs
{
private:
	UserLevel m_eLevel;
public:
	UserLevelChangedEventArgs(UserLevel _Level)
	{
		Level = _Level;
	}

	property UserLevel Level
	{
		UserLevel get() {
			return m_eLevel;
		}

		private: void set(UserLevel value) {
			m_eLevel = value;
		}
	}
};

ref class TUser
{
private:
	static String^ S_Name = nullptr;
	static String^ S_Team = nullptr;
	static UserLevel s_Level;
	static Object^ LockObj;

	
public:
	delegate void UserLevelChangedEvent(Object^ sender, UserLevelChangedEventArgs^ e);
	static event UserLevelChangedEvent^ UserLevelChanged;

	static TUser(void);
	static void Clear(void);
	static void SetName(String^ pS_x_NewName);
	static void SetLevel(UserLevel s_x_NewLevel);
	static UserLevel GetLevel();
	static void SetTeam(String^ pS_x_NewTeam);
	static String^ pS_GetName(void);
	static bool b_HasMaintenanceLevel(void);
	static bool b_HasManagerLevel(void);
	static bool b_HasSystemLevel(void);
	static String^ pS_GetTeam(void);
};

ref class ProductionOrder
{
private:
	static String^ pS_OrderName;
	static int i_OrderQuantity;
	static String^ pS_ReferenceName;
	static String^ pS_PlateType;
	static String^ pS_StartDate;
	static String^ pS_EndDate;
	static array<Bitmap^>^ apT_PartsImage;

	static double d_PartOffsetZLiftTake;
	static double d_PartOffsetZLiftBadTake;
	static double d_PartOffsetZLiftDrop;
	static double d_PartOffsetThetaLiftDrop;
	static double d_PartOffsetXLiftDrop;
	static double d_PartOffsetYLiftDrop;
	static double d_PartOffsetZLayeringTake;
	static double d_PartOffsetZLayeringDrop;
	static double d_PartOffsetZTurnOverDrop;
	static double d_PartOffsetZCleaning;
	static array<double,2>^ ad_PartOffset;
	static array<double>^ ad_HeadOffset;
	static array<double, 2>^ ad_PartSensorOffset;
	static double d_PartAndLayeringHeight;
	static double d_PartAndHeadHeight;
	static String^ pS_VisionReferenceFileName;
	static double d_LayeringAndPartAndHeadHeight;
	static double d_HeadSusPartHeadSousHeight;
	static double d_PlateZOffsetForLift;
	static int i_DropModeTable;
	static int i_DropModeTurnOver;
	static int i_TakeModeLift;
	static bool b_DropInBox;

public:
	ProductionOrder(void);
	static void CloseOrder(void);
	static void SetName(String^ pS_x_NewName);
	static void SetReference(String^ pS_x_ReferenceName);
	static void SetQuantity(int i_x_Quantity);
	static void SetStartDate(String^ pS_x_StartDate);
	static void SetEndDate(String^ pS_x_EndDate);
	static String^ pS_GetName(void);
	static String^ pS_GetReference(void);
	static int i_GetQuantity(void);
	static String^ pS_GetStartDate(void);
	static String^ pS_GetEndDate(void);
	static bool b_OrderStarted(void);
	static void SetPlateType(String^ pS_x_PlateName);

	static void SetVisionReferenceFileName(String^ pS_x_VisionReferenceFileName);
	static String^ pS_GetVisionReferenceFileName(void);

	static void SetPartOffsetZLiftTake(double d_xZOffset);
	static void SetPartOffsetZLiftBadTake(double d_xZOffset);
	static void SetPartOffsetZLiftDrop(double d_xZOffset);
	static void SetPartOffsetThetaLiftDrop(double d_xZOffset);
	static void SetPartOffsetXLiftDrop(double d_xZOffset);
	static void SetPartOffsetYLiftDrop(double d_xZOffset);
	static void SetPartOffsetZLayeringTake(double d_xZOffset);
	static void SetPartOffsetZLayeringDrop(double d_xZOffset);
	static void SetPartOffsetZTurnOverDrop(double d_xZOffset);
	static void SetPartOffsetZCleaning(double d_xZOffset);
	static double GetPartOffsetZLiftTake();
	static double GetPartOffsetZLiftBadTake();
	static double GetPartOffsetZLiftDrop();
	static double GetPartOffsetThetaLiftDrop();
	static double GetPartOffsetXLiftDrop();
	static double GetPartOffsetYLiftDrop();
	static double GetPartOffsetZLayeringTake();
	static double GetPartOffsetZLayeringDrop();
	static double GetPartOffsetZTurnOverDrop();
	static double GetPartOffsetZCleaning();

	static void SetPartSensorOffset(int i_x_Point,int i_x_Axis,double d_x_PartSensorOffset);
	static void GetPartSensorOffset(int i_x_Point,double* ad_x_PartSensorOffset);
	static void SetPartOffset(int i_x_Point,int i_x_Axis,double d_x_PartOffset);
	static void GetPartOffset(int i_x_Point,double* ad_x_PartOffset);
	static void SetPartAndHeadHeight(double d_x_PartAndHeadHeight);
	static double d_GetPartAndHeadHeight(void);
	static void GetPlateData(struct TC_PLATE_DATA* ps_x_PlateData);
	static void SetPartAndLayeringHeight(double d_x_PartAndLayeringHeight);
	static double d_GetPartAndLayeringHeight(void);
	static void SetHeadOffset(int i_x_Axis, double d_x_PartOffset);
	static void GetHeadOffset(double* ad_x_PartOffset);

	static void SetDropModeTable(int i_x_DropMode);
	static int i_GetDropModeTable(void);
	static void SetDropModeTurnOver(int i_x_DropMode);
	static int i_GetDropModeTurnOver(void);
	static void SetTakeModeLift(int i_x_TakeMode);
	static int i_GetTakeModeLift(void);
	static void SetDropInBox(bool b_x_DropInBox);
	static bool b_GetDropInBox(void);

	static void SetLayeringAndPartAndHeadHeight(double d_x_LayeringAndPartAndHeadHeight);
	static double d_GetLayeringAndPartAndHeadHeight(void);
	static void SetHeadSusPartHeadSousHeight(double d_x_HeadSusPartHeadSousHeight);
	static double d_GetHeadSusPartHeadSousHeight(void);
	static void SetPlateZOffsetForLift(double d_x_PlateZOffsetForLift);
	static double d_GetPlateZOffsetForLift(void);
	static void SetPartImage(Bitmap^ PartImage, int iIndex);
	static Bitmap^ GetPartImage(int iIndex);
};
