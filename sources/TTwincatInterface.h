#pragma once

#include "stddef.h"

using namespace std;
using namespace System;
using namespace System::Threading;

// Special types for Twincat ADS
#define NULL 0
typedef int                 BOOL;

// Special types for ADS variables
#define TC_STRING_SIZE		81
typedef unsigned char		TC_BOOL;		// 8 bits
typedef unsigned char		TC_BYTE;		// 8 bits
typedef short				TC_INT;			// 16 bits
typedef unsigned short		TC_UINT;		// 16 bits
typedef unsigned long		TC_DWORD;		// 32 bits
typedef float				TC_REAL;		// 32 bits
typedef double				TC_LREAL;		// 64 bits
typedef char				TC_CHAR;

#include "global.h"
#include "C:\TwinCAT\ADSApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\ADSApi\TcAdsDll\Include\TcAdsApi.h"

enum DataVarType {DVT_Global = 0,DVT_Manual,DVT_Config};

enum MachineModes { MM_Stopped = 0, MM_Init, MM_Ready, MM_Running, MM_Dashboard, MM_Stopping, MM_Manual,MM_Pause,MM_Pausing,MM_ForceStop,MM_Purging};
enum SideIndex {SI_LEFT,SI_RIGHT};

#define C_MAX_NB_OF_ERRORS 160
#define C_MAX_NB_OF_PARTS_ON_PLATE 100

#pragma pack(push,Twincat,1)

struct TC_TIME
{
	TC_UINT			T_Year;
	TC_UINT			T_Month;
	TC_UINT			T_DayOfWeek;
	TC_UINT			T_Day;
	TC_UINT			T_Hour;
	TC_UINT			T_Minute;
	TC_UINT			T_Second;
	TC_UINT			T_Milliseconds;
};

struct MACHINE_MODE_MASK
{
	TC_BOOL			MMM_Stop;
	TC_BOOL			MMM_Init;
	TC_BOOL			MMM_Run;
	TC_BOOL			MMM_Manual;
	TC_BOOL			MMM_Purge;
	TC_BOOL			MMM_Pause;
	TC_BOOL			MMM_Dashboard;
};

struct PRODUCTION_LOT
{
	TC_DWORD		PL_LotQty;
	TC_DWORD		PL_ProdQty;
	TC_DWORD		PL_GoodQty;
	TC_DWORD		PL_LoadedQty;
	TC_DWORD		PL_EstimatedPartTime;
	TC_DWORD		PL_EstimatedTimeLeft;
	TC_DWORD		PL_ProductionTime;
};

struct PRODUCTION_STATS
{
	TC_REAL			PL_QualityRate;
	TC_REAL			PL_EfficiencyRate;
	TC_REAL			PL_AvailabilityRate;
};

struct MODULE_DATA
{
	TC_BOOL			MD_InitDone;
	TC_BOOL			MD_Running;
	TC_BOOL			MD_InError;
	TC_BOOL			MD_Interlocked;
	TC_BOOL			MD_Warning;
	TC_BOOL			MD_StepMode;
	TC_BOOL			MD_WaitStep;
	TC_INT			MD_Status;
	TC_INT			MD_Step;
};

struct MACHINE_OPTIONS
{
	TC_BOOL		MO_TurnOver;
	TC_BOOL		MO_RTPearling;
	TC_BOOL		MO_AutoSampling;
	TC_BOOL		MO_DisableCleanAfterPearling;
	TC_BOOL		MO_DisableVision;
	TC_BOOL		MO_SpeedModeSlow;
};

struct VISION_PART_DATA
{
	TC_LREAL	VPD_X;
	TC_LREAL	VPD_Y;
	TC_LREAL	VPD_Theta;
	TC_LREAL	VPD_Score;
	TC_BOOL		VPD_Valid;
	TC_BOOL		VPD_Present;
	TC_BOOL		VPD_ImageGrabbed;

};

struct PART_DATA
{
	TC_BOOL			CD_HasPart;
	TC_INT			CD_PartSide;
	TC_BOOL			CD_Rejected;
	TC_BOOL			CD_Sample;
	TC_BOOL			CD_HasPearls[2][2];
	TC_BOOL			CD_PearlingDone[2][2];
	TC_INT			CD_CurrentPearlNb[2][2];
	TC_BOOL			CD_BadPearling[2][2];
	TC_DWORD		CD_PlateInQRCode;
	TC_INT			CD_PlateInPos;
	TC_DWORD		CD_PlateOutQRCode;
	TC_INT			CD_PlateOutPos;
	TC_DWORD		CD_ProductionTime;
	TC_DWORD		CD_ProductionInTime;
	TC_DWORD		CD_ProductionOutTime;
};

struct DATA_LOG
{
	TC_BOOL			PDL_PartReady;
	TC_BOOL			PDL_EndOfProd;
	PART_DATA		PDL_PartStatus;
};

struct MACHINE_MANUAL
{
	TC_BOOL			MM_CanLockDoor;
	TC_BOOL			MM_LockDoor;
	TC_BOOL			MM_CanUnlockDoor;
	TC_BOOL			MM_UnlockDoor;
};

struct OPERATOR_REQ
{
	TC_BOOL			OR_FreeLift[2];
	TC_BOOL			OR_SampleRequest;
};

struct TC_MAN_BUTTON
{
	TC_BOOL			MB_Activate;
	TC_BOOL			MB_Enable;
};

struct TC_MAN_DRIVE
{
	TC_LREAL		MD_CurrentPos;
	TC_LREAL		MD_JogStep;
	TC_MAN_BUTTON	MD_Specific;
	TC_MAN_BUTTON	MD_ServoON;
	TC_MAN_BUTTON	MD_Home;
	TC_MAN_BUTTON	MD_MoveFw;
	TC_MAN_BUTTON	MD_MoveBw;
	TC_DWORD		MD_UseHours;
	TC_MAN_BUTTON	MD_ResetUseTime;
};

struct TC_MAN_DRIVE_POS
{
	TC_BOOL				MDP_Teach;
	TC_LREAL			MDP_TeachedPos;
	TC_MAN_BUTTON		MDP_MoveToTeach;
};

struct TC_STICK_DATA_MMI
{
	TC_INT				SD_CompenseWeight;
	TC_LREAL			SD_MCRCorrectionStep;
	TC_LREAL			SD_MA2MMFactor;
	TC_LREAL			SD_MCRRation;
};

struct TC_STICK_DATA_MMI_SHARED
{
	TC_INT				SDS_NbOfFwBwSharpen;
	TC_INT				SDS_NbOfFwBwBeforeTapeMove;
	TC_LREAL			SDS_SharpenSpeed;
	TC_LREAL			SDS_SharpenHeight;
	TC_BOOL				SDS_RestartBeginOfArea;
	TC_LREAL			SDS_MinHoldLength;
	TC_BOOL				SDS_StopOnVacuumLoss;
	TC_BOOL				SDS_StopOnStickBreak;
	TC_INT				SDS_MCRSharpenSpeed;
	TC_INT				SDS_WeightTolerance;
	TC_BOOL				SDS_StopOnWeightOutOfTolerance;
};


struct TC_PEARL_DATA
{
	TC_BOOL				PD_NewPearl;
	TC_BOOL				PD_NewPart;
	TC_INT				PD_PearlNb;
	TC_INT				PD_Rate;
	TC_BOOL				PD_PearlingTop;
	TC_LREAL			PD_PearlingCalcPos;
	TC_LREAL			PD_PearlingMeasurePos;
	TC_LREAL			PD_DeltaCurrent;
	TC_LREAL			PD_CorrectionMCR;
	TC_LREAL			PD_Dispersion;
	TC_LREAL			PD_SensorProbePos;
	TC_LREAL			PD_SensorPearlPos;
	TC_LREAL			PD_DeltaWeight;
	TC_INT				PD_VacuumFlow;
};

struct TC_POSITIONXY
{

	TC_LREAL			PXY_X;
	TC_LREAL			PXY_Y;
};

struct TC_PLATE_DATA
{
	TC_LREAL			PD_Height;
	TC_LREAL			PD_Edge;
	TC_POSITIONXY		PD_PartOnPlate[C_MAX_NB_OF_PARTS_ON_PLATE];
	TC_INT				PD_NbPartOnPlate;
	TC_POSITIONXY		PD_TakerPlatePos;
	TC_LREAL			PD_RejectCorrectionY;
	TC_BOOL				PD_UseVisionForDrop;
};

struct TC_PART_DATA_MMI
{
	TC_LREAL			PRD_PartOffsetZLiftTake;
	TC_LREAL			PRD_PartOffsetZLiftBadTake;
	TC_LREAL			PRD_PartOffsetZLiftDrop;
	TC_LREAL			PRD_PartOffsetThetaLiftDrop;		
	TC_LREAL			PRD_PartOffsetXLiftDrop;
	TC_LREAL			PRD_PartOffsetYLiftDrop;
	TC_LREAL			PRD_PartOffsetZLayeringTake;
	TC_LREAL			PRD_PartOffsetZLayeringDrop;
	TC_LREAL			PRD_PartOffsetZTurnOverDrop;
	TC_LREAL			PRD_PartOffsetZCleaning;
	TC_POSITIONXY		PRD_SensorOffset[2];
	TC_POSITIONXY		PRD_PartOffsetLayering[2];
	TC_LREAL			PRD_PartAndLayeringHeight;
	TC_LREAL			PRD_PartAndHeadHeight;
	TC_LREAL			PRD_LayeringAndPartAndHeadHeight;
	TC_LREAL			PRD_HeadSusPartHeadSousHeight;
	TC_LREAL			PRD_PlateZOffsetForLift;
	TC_POSITIONXY		PRD_HeadOffset;
	TC_INT				PRD_DropModeTable;
	TC_INT				PRD_DropModeTurnOver;
	TC_INT				PRD_TakeModeLift;
	TC_BOOL				PRD_DropInBox;
};

struct  DASHBOARD_CMD
{
	TC_MAN_BUTTON	DC_Pearling;
	TC_MAN_BUTTON	DC_LoaderEndOfRecipe;
	TC_MAN_BUTTON	DC_TableTurn;
	TC_MAN_BUTTON	DC_LoaderScanPlateLift1;
	TC_MAN_BUTTON	DC_LoaderScanPlateLift2;
	TC_MAN_BUTTON	DC_LoaderScanPlateReject;
	TC_MAN_BUTTON	DC_PickPlace;
	TC_INT			DC_ScanModel;
	TC_INT			DC_MaxScanModel;
	TC_INT			DC_ScanPlateOK[3];
	TC_INT			DC_ScanPlateTotal[3];
};

struct  AUTO_SAMPLING
{
	TC_BOOL			AS_AutoSampling;
	TC_INT			AS_Period;
	TC_INT			AS_BatchSize;
	TC_INT			AS_PeriodCnt;
	TC_INT			AS_BatchCnt;
};

struct  PRODUCTION_CMD
{
	TC_MAN_BUTTON	PC_RequestSample;
	AUTO_SAMPLING	PC_AutoSampling;
};

struct PROBING_LOG
{
	TC_BOOL				PL_NewLog;
	TC_INT				PL_ProbingArea;
	TC_LREAL			PL_ProbingPos[2];
	TC_INT				PL_ProbingThreshold;
	TC_INT				PL_PreviousProbingThreshold;
};

struct PROD_COUNTER
{
	TC_DWORD			PC_ProdQty;
	TC_DWORD			PC_GoodQty;
};

struct TC_COUNTER
{
	PROD_COUNTER		TC_Prod;
	TC_BOOL				TC_ResetMTBF;
	TC_DWORD			TC_MeanMTBF;
	TC_DWORD			TC_PearlingMotorUseTime[2];
	TC_DWORD			TC_PearlingSpindleUseTime[2];
	TC_DWORD			TC_AspirationUseTime;
	TC_DWORD			TC_VacuumUseTime;
	TC_DWORD			TC_MachineOnTime;
	TC_DWORD			TC_InProdTime;
};

struct MACHINE_DATA
{
	TC_BOOL						b_ReadyForChangeJob;
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
	DATA_LOG					s_PartData4Log;
	MACHINE_MANUAL				s_MachineSafety;
	OPERATOR_REQ				s_OperatorRequest;
	TC_STICK_DATA_MMI			as_StickDataMMI[2];
	TC_PEARL_DATA				as_PearlsData[2];
	TC_STICK_DATA_MMI_SHARED	s_StickDataShared;
	TC_BOOL						b_EmergencyStop;
	TC_BOOL						b_DoorsPearling;
	TC_BOOL						b_DoorsLoader;
	TC_BOOL						b_SavePersistent;
	TC_INT						e_ManagerRunStep;
	DASHBOARD_CMD				s_DashboardCmd;
	TC_BOOL						b_SimPearling;
	PROBING_LOG					as_ProbingLog[2];
	PRODUCTION_CMD				s_ProductionCmd;
	TC_DWORD					dw_StartJobElapsedTime;
	TC_COUNTER					s_Counter;
};

struct MAN_LOADER
{
	TC_INT				ML_TableSide;
	TC_BOOL				ML_AxisZSafe[2];
	TC_MAN_DRIVE		ML_Axis[5];
	TC_MAN_DRIVE_POS	ML_AxisRobotPos[5];
	TC_MAN_BUTTON		ML_Safe;
	TC_MAN_BUTTON		ML_VisionCalibration;
	TC_MAN_BUTTON		ML_Head1Vacuum;
	TC_MAN_BUTTON		ML_Head2Vacuum;
	TC_MAN_BUTTON		ML_PlateVacuum;
	TC_LREAL			MT_VacuumValue[2];
	TC_LREAL			MT_VacuumThreshold[2];
	TC_MAN_BUTTON		ML_MovePlateTakerDown;
	TC_MAN_BUTTON		ML_AspirationBrush;
	TC_LREAL			ML_SensorAdjust;
	TC_LREAL			ML_SensorMeasure;
	TC_UINT				ML_RobotPos;
	TC_MAN_BUTTON		ML_ZSensorTeach;
	TC_MAN_BUTTON		ML_MoveVision2Table;
	TC_MAN_BUTTON		ML_MoveVision2Lift;
	TC_UINT				ML_MoveVision2LiftPos;
};

struct MAN_TABLE
{
	TC_MAN_DRIVE		MT_AxisTable;
	TC_MAN_DRIVE_POS	MT_AxisTableLoading12Pos;
	TC_MAN_DRIVE_POS	MT_AxisTableLoading34Pos;
	TC_MAN_DRIVE		MT_AxisBrush;
	TC_MAN_DRIVE_POS	MT_AxisBrushParkPos[2];
	TC_MAN_DRIVE_POS	MT_AxisBrushWorkPos[2];
	TC_MAN_BUTTON		MT_AspirationDown;
	TC_MAN_BUTTON		MT_IndexTable;
	TC_MAN_BUTTON		MT_VacuumPos1;
	TC_MAN_BUTTON		MT_VacuumPos2;
	TC_MAN_BUTTON		MT_VacuumPos3;
	TC_MAN_BUTTON		MT_VacuumPos4;
	TC_LREAL			MT_VacuumValue[4];
	TC_LREAL			MT_VacuumThreshold[4];
	TC_MAN_BUTTON		MT_AspirationBrush;
	TC_MAN_BUTTON		MT_CleanBrushDown;
};

struct MAN_PEARLING
{
	TC_INT				MP_TeachPos;
	TC_INT				MP_TableSide;
	TC_BOOL				MP_AxisZSafe[2];
	TC_INT				MP_MotorSpeed[2];
	TC_REAL				MP_MotorCurrent[2];
	TC_DWORD			MP_MotorUseTime[2];
	TC_DWORD			MP_SpindleUseTime[2];
	TC_MAN_DRIVE		MP_Axis[4];
	TC_MAN_DRIVE_POS	MP_AxisPos[4];
	TC_MAN_BUTTON		MP_StartMotor[2];
	TC_MAN_BUTTON		MP_OpenChuck[2];
	TC_MAN_BUTTON		MP_EjectStick[2];
	TC_MAN_BUTTON		MP_Blowing[2];
	TC_MAN_BUTTON		MP_Safe;
	TC_MAN_BUTTON		MP_CalibrateWeight[2];
	TC_MAN_BUTTON		MP_RAZMotorUseTime[2];
	TC_MAN_BUTTON		MP_RAZSpindleUseTime[2];
	TC_LREAL			MP_WeightStepOnZ;
	TC_LREAL			MP_WeightTableLeft[26];
	TC_LREAL			MP_WeightTableRight[26];
	TC_BOOL				MP_WeightTableLeftValid;
	TC_BOOL				MP_WeightTableRightValid;
	TC_MAN_BUTTON		MP_ActivateAspirationTable[2];
	TC_MAN_BUTTON		MP_ActivateAspirationSharpen;
	TC_INT				MP_SpindleSpeedSetpoint[2];
	TC_INT				MP_CurrentMotorMinTh;
	TC_INT				MP_CurrentMotorWarnTh;
	TC_INT				MP_CurrentMotorMaxTh;
	TC_INT				MP_MotorStartedTimeout[2];
	TC_INT				MP_MotorStoppedTimeout[2];
	TC_LREAL			MP_Ratiog2mm[2];
	TC_INT				MP_DistanceSensor[2];
	TC_INT				MP_WeightSensor;
	TC_DWORD			MP_PearlsCounter[2];
};

struct MAN_TURN_OVER
{
	TC_MAN_DRIVE		MTO_Axis;
	TC_MAN_DRIVE_POS	MTO_AxisCWPos;
	TC_MAN_DRIVE_POS	MTO_AxisCCWPos;
	TC_MAN_BUTTON		MTO_MoveJackUp;
	TC_MAN_BUTTON		MTO_ArmVacuum;
	TC_MAN_BUTTON		MTO_FixVacuum;
	TC_MAN_BUTTON		MTO_ActivateCleaningBlow;
};

struct MAN_BARREL_AXIS_POSITION
{
	TC_MAN_BUTTON		MBAP_Move1Step;
	TC_MAN_BUTTON		MBAP_MoveSectionA;
	TC_MAN_BUTTON		MBAP_MoveSectionB;
	TC_MAN_BUTTON		MBAP_MoveSectionC;
	TC_MAN_BUTTON		MBAP_MoveSectionD;
};

struct MAN_BARREL
{
	TC_INT						MB_IndexSection;
	TC_INT						MB_IndexPosition;
	TC_INT						MB_Position;
	TC_BOOL						MB_StickPresent;
	TC_MAN_DRIVE				MB_Axis;
	TC_MAN_DRIVE_POS			MB_AxisTakenPos;
	TC_MAN_DRIVE_POS			MB_AxisCheckPos;
	TC_MAN_BUTTON				MB_MoveJackUp;
	TC_MAN_BUTTON				MB_IndexUp;
	MAN_BARREL_AXIS_POSITION	MB_MoveTaken;
	MAN_BARREL_AXIS_POSITION	MB_MoveCheck;
};

struct MAN_SHARPEN
{
	TC_MAN_DRIVE		MS_Axis;
	TC_MAN_BUTTON		MS_Move2NextPos;
	TC_BOOL				MS_TapeNotEmpty;
	TC_LREAL			MS_Step;
};

struct MAN_LIFT
{
	TC_MAN_DRIVE		ML_Axis;
	TC_MAN_DRIVE_POS	ML_AxisFullPos;
	TC_MAN_DRIVE_POS	ML_AxisEmptyPos;
	TC_MAN_DRIVE_POS	ML_AxisLoadPos;
	TC_MAN_DRIVE_POS	ML_AxisZOffset;
	TC_MAN_BUTTON		ML_MoveToPlate;
	TC_MAN_BUTTON		ML_MoveToPlateVision;
	TC_BOOL				ML_DrawerInPos;
	TC_BOOL				ML_PlateInPos;
	TC_LREAL			ML_PlatePos;
	TC_MAN_BUTTON		ML_LockDrawer;
	TC_MAN_BUTTON		ML_LockPlate;
};

struct MAN_REJECT
{
	TC_BOOL				MR_DrawerInPos;
	TC_BOOL				MR_PlateInPos;
};

struct MAN_VISION
{
	TC_MAN_BUTTON		MV_Init;
	TC_MAN_BUTTON		MV_Analyse;
	TC_MAN_BUTTON		MV_Run;
	TC_TIME				MV_InitTime;
	TC_TIME				MV_AnalyseTime;
	TC_CHAR				MV_VisionRecipeName[21];
	TC_BOOL				MV_Connected;
	TC_BOOL				MV_Ready;
	TC_BOOL				MV_SimRecipe;
	TC_INT				MV_UseModel;
	TC_INT				MV_MaxModel;
	VISION_PART_DATA	MV_PartData;
	TC_BOOL				MV_PartDataValid;
	TC_MAN_BUTTON		MV_ConfigMode;
};

struct MAN_UTILITIES
{
	TC_MAN_BUTTON		MU_Aspiration;
	TC_MAN_BUTTON		MU_Vacuum;
	TC_BOOL				MU_PowerIsOn;
	TC_BOOL				MU_DrivesIsOn;
	TC_BOOL				MU_24VOK;
	TC_BOOL				MU_48VOK;
	TC_BOOL				MU_AirPressureOK;
	TC_BOOL				MU_MainVacuumOK;
	TC_BOOL				MU_AspirationOK;
	TC_BOOL				MU_AspirationIsOn;
	TC_MAN_BUTTON		MU_ResetAspirationUseTime;
	TC_DWORD			MU_AspirationUseTime;
	TC_MAN_BUTTON		MU_ResetVacuumUseTime;
	TC_DWORD			MU_VacuumUseTime;
};

struct VACUUM_SETTINGS
{
	TC_INT				VS_Blowing;
	TC_INT				VS_WaitWhenVacuumOk;
	TC_INT				VS_ErrorDelay;
};

struct VACUUM_SETTINGS_MMI
{
	VACUUM_SETTINGS		VSM_Table;
	VACUUM_SETTINGS		VSM_LoaderHead;
	VACUUM_SETTINGS		VSM_LoaderPlate;
	VACUUM_SETTINGS		VSM_TurnOver;
	TC_INT				VSM_TablePartialDelay;
};

struct MANUAL_DATA
{
	MAN_LOADER			s_LoaderManual;
	MAN_TABLE			s_TableManual;
	MAN_PEARLING		s_PearlingManual;
	MAN_SHARPEN			s_SharpenManual;
	MAN_TURN_OVER		s_TurnOverManual;
	MAN_BARREL			s_BarrelManual;
	MAN_LIFT			s_Lift1Manual;
	MAN_LIFT			s_Lift2Manual;
	MAN_REJECT			s_RejectManual;
	MAN_VISION			s_VisionManual;
	MAN_UTILITIES		s_UtilitiesManual;
	VACUUM_SETTINGS_MMI	s_VacuumSettings;
};

struct PEARLING_TABLE
{
	TC_INT				PT_Area;
	TC_BOOL				PT_NeedXYDispersion;
	TC_BOOL				PT_ForceSharpen;
	TC_BOOL				PT_Disable;
	TC_BOOL				PT_MoveToSafe;
	TC_LREAL			PT_X;
	TC_LREAL			PT_Y;
	TC_LREAL			PT_Z;
	TC_LREAL			PT_Rate;

};

struct TC_PEARLING_DATA_HEAD
{
	PEARLING_TABLE		PDH_PearlingData[C_MAX_NB_OF_PEARLS];
	TC_UINT				PDH_NbOfPearls;
	TC_LREAL			PDH_SecurityZ;
	TC_INT				PDH_DispersionXY;
	TC_INT				PDH_Weight;
	TC_INT				PDH_DispersionZ;
	TC_INT				PDH_SharpenFreq;
	TC_INT				PDH_MCRSpeed;
	TC_INT				PDH_PearlingTime;
};

struct TC_PEARLING_DATA
{
	TC_PEARLING_DATA_HEAD		PD_Head[2];
};


struct TC_STICK_DATA
{
	TC_INT				SD_BarrelPos;
	TC_LREAL			SD_Diameter;
	TC_LREAL			SD_OutLength;
	TC_LREAL			SD_TotalLength;
};

struct CONFIG_DATA
{
	TC_BOOL				CD_ParallelProd;
	TC_PEARLING_DATA	CD_PearlingData[2];
	TC_STICK_DATA		CD_StickData[2];
	TC_PLATE_DATA		CD_PlateData;
	TC_PART_DATA_MMI	CD_PartData;
	TC_CHAR				CD_VisionRefFileName[21];
};

#pragma pack(pop,Twincat)


// Macros to interface Twincat global Data
#define GetTCData(Data) (TTwincatInterface::GetTCVarAccess()->GetButtonData(offsetof(MACHINE_DATA,Data)))
#define ReadTCData(Data,Result) (TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global,offsetof(MACHINE_DATA,Data),&(Result)))
#define ReadTCError(Index,Result) (TTwincatInterface::GetTCVarAccess()->GetErrorData(Index,&(Result)))
#define ReadTCValError(Index,Result) (TTwincatInterface::GetTCVarAccess()->GetValErrorData(Index,&(Result)))
#define WriteTCData(a,b) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Global,offsetof(MACHINE_DATA,a),b))
#define WriteTCArray(a,b,c) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Global,offsetof(MACHINE_DATA,a),b,c))
#define SetTCData(a) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Global,offsetof(MACHINE_DATA,a),(TC_BOOL)true))
#define ClearTCData(a) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Global,offsetof(MACHINE_DATA,a),(TC_BOOL)false))

// Macros to interface Twincat manual Data
#define ReadTCManData(Data,Result) (TTwincatInterface::GetTCVarAccess()->GetData(DVT_Manual,offsetof(MANUAL_DATA,Data),&(Result)))
#define ReadTCManOffsetData(Data,Result) (TTwincatInterface::GetTCVarAccess()->GetData(DVT_Manual,Data,&(Result)))
#define WriteTCManData(a,b) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Manual,offsetof(MANUAL_DATA,a),b))
#define WriteTCManOffsetData(a,b) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Manual,a,b))
#define SetTCManData(a) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Manual,offsetof(MANUAL_DATA,a),(TC_BOOL)true))
#define ClearTCManData(a) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Manual,offsetof(MANUAL_DATA,a),(TC_BOOL)false))
#define GetTCManData(Data) (TTwincatInterface::GetTCVarAccess()->GetManButtonData(offsetof(MANUAL_DATA,Data)))
#define GetTCManOffsetData(Data) (TTwincatInterface::GetTCVarAccess()->GetManButtonData(Data))
#define GetTCManualOffset(Data) (offsetof(MANUAL_DATA,Data))
#define SetTCManOffsetData(a) (TTwincatInterface::GetTCVarAccess()->SetData(DVT_Manual,a,(TC_BOOL)true))

#define WriteConfigData(a) (TTwincatInterface::GetTCVarAccess()->WriteConfig(a))

#define InvTC(a) (TTwincatInterface::GetTCVarAccess()->bInvTC(a))

ref class TTwincatInterface
{
private:
	Mutex TCVarAccess;
	void WriteData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,void* pv_x_Value,unsigned long n_x_DataSize);
	private: static TTwincatInterface^ pTTwincatInterface;
public:
	TTwincatInterface(char* pc_x_MachineVarName,char* pc_x_ManualVarName,char* pc_x_ConfigVarName,String^ AutomationNetID);
	~TTwincatInterface(void);
	static bool IsConnected(void);
	static TTwincatInterface^ GetTCVarAccess(void);
	void SetThisPtr(TTwincatInterface^ NewPtr);
	bool bReadAllData(void);
	void GetErrorData(int i_x_Index,bool* pb_x_Value);
	void GetValErrorData(int i_x_Index,bool* pb_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_BYTE* py_x_Value);
	void SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_BYTE y_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_UINT* pn_x_Value);
	void SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_UINT n_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_INT* pi_x_Value);
	void SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_INT i_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_DWORD* pn_x_Value);
	void SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_DWORD n_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_REAL* pf_x_Value);
	void SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_REAL f_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_LREAL* pd_x_Value);
	void SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_LREAL d_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,DATA_LOG* ps_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_PEARL_DATA* ps_x_Value);
	void GetData(enum DataVarType e_x_DataVarType, unsigned int n_x_Offset, PROBING_LOG* ps_x_Value);
	void GetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_CHAR* pc_x_Value);
	void SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,TC_CHAR* pc_x_Value);
	void SetData(enum DataVarType e_x_DataVarType,unsigned int n_x_Offset,void* plr_x_Data,int i_x_DataSize);
	void GetData(enum DataVarType e_x_DataVarType, unsigned int n_x_Offset, TC_TIME* pn_x_Value);

	TC_BOOL bInvTC(TC_BOOL b_x_Data);
	TC_MAN_BUTTON GetManButtonData(unsigned int n_x_Offset);
	TC_MAN_BUTTON GetButtonData(unsigned int n_x_Offset);
	void WriteConfig(struct CONFIG_DATA* ps_x_ConfigData);
};
