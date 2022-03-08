#include "MachineScreen.h"
#include "MainWindow.h"

using namespace Projet1;

void MachineScreen::UpdateStatus(ModuleStatus^ ms,Label^ lblStep, Label^ lblStatus)
{
	TC_BOOL b_l_Status;
	TC_INT i_l_Value;

	TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_Running), &(b_l_Status));
	ms->Run = b_l_Status ? true : false;
	TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_Warning), &(b_l_Status));
	ms->Warning = b_l_Status ? true : false;
	TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_InError), &(b_l_Status));
	ms->Alarm = b_l_Status ? true : false;
	TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_Interlocked), &(b_l_Status));
	ms->Interlock = b_l_Status ? true : false;
	
	if (TUser::b_HasSystemLevel())
	{
		TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_StepMode), &(b_l_Status));
		ms->Debug->Checked = b_l_Status ? true : false;
		TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_WaitStep), &(b_l_Status));
		ms->Step->Visible = b_l_Status ? true : false;
		ms->Debug->Visible = true;
	}
	else
	{
		ms->Debug->Visible = false;
		ms->Step->Visible = false;
	}
	if (TUser::b_HasMaintenanceLevel())
	{
		TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_Step), &(i_l_Value));
		lblStep->Text = GetStepStr(i_l_Value);

		TTwincatInterface::GetTCVarAccess()->GetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_Status), &(i_l_Value));
		lblStatus->Text = gcnew String(aac_ModuleStatus[i_l_Value]);

		lblStep->Visible = true;
		lblStatus->Visible = true;
	}
	else
	{
		lblStep->Text = "";
		lblStatus->Text = "";
		lblStep->Visible = false;
		lblStatus->Visible = false;
	}
}

String^ MachineScreen::GetStepStr(TC_INT eStep)
{
	int iStep = (eStep % 1000);
	int iStepMod = (eStep / 1000);
	String^ ModText = "";
	switch (iStepMod)
	{
	case 0:
		ModText = "Init";
		break;
	case 1:
		ModText = "Run";
		break;
	case 2:
		ModText = "Man";
		break;
	}
	return TUtilities::pS_LoadString(TextIndex::Step) + " : " + ModText + " " + iStep;
}



void MachineScreen::UpdateUI(void)
{
	TC_BOOL b_l_Value;
	TC_INT i_l_Value;
	bool b_l_ManualMode;
	bool b_l_RunMode;
	bool b_l_Visible;

	TC_INT i_l_MajorVersion,i_l_MinorVersion;

	ReadTCData(e_CurrentMode,i_l_Value);
	b_l_ManualMode = (MM_Manual == i_l_Value);
#ifdef C_SIMULATION
	b_l_ManualMode = true;
#endif
	b_l_RunMode = (MM_Running == i_l_Value);
	ReadTCData(e_ManagerRunStep, i_l_Value);
	lblManagerRunStep->Text = "Manager " + GetStepStr(i_l_Value);
	lblManagerRunStep->Visible = TUser::b_HasMaintenanceLevel();


	// Update version
	ReadTCData(i_MajorVersion,i_l_MajorVersion);
	ReadTCData(i_MinorVersion,i_l_MinorVersion);
	lblAutomationVersion->Text = String::Format(TUtilities::pS_LoadString(TextIndex::Automation) + " v. {0:d2}.{1:d2}",i_l_MajorVersion,i_l_MinorVersion);
	lblMMIVersion->Text = String::Format(TUtilities::pS_LoadString(TextIndex::HMI) + " v. {0:d2}.{1:d2}",(int)C_MAJOR_VERSION,(int)C_MINOR_VERSION);

	UpdateStatus(msLoader, lblStepLoader,lblLoaderStatus);
	UpdateStatus(msTable, lblStepTable,lblTableStatus);
	UpdateStatus(msPearling, lblStepPearling,lblPearlingStatus);
	UpdateStatus(msTurnOver, lblStepTurnover, lblTurnOverStatus);
	UpdateStatus(msBarrel, lblStepBarrel, lblBarrelStatus);
	UpdateStatus(msSharpen, lblStepSharpening,lblSharpenStatus);
	UpdateStatus(msLift1, lblStepLift1, lblLift1Status);
	UpdateStatus(msLift2, lblStepLift2,lblLift2Status);
	UpdateStatus(msReject, lblStepReject,lblRejectStatus);
	UpdateStatus(msVision, lblStepVision,lblVisionStatus);
	UpdateStatus(msUtilities, lblStepUtilities,lblUtilitiesStatus);

	ReadTCData(b_EmergencyStop, b_l_Value);
	b_l_Visible = b_l_Value ? true : false;
	pbEmergency1->Visible = b_l_Visible;
	pbEmergency2->Visible = b_l_Visible;
	pbEmergency3->Visible = b_l_Visible;
	ReadTCData(b_DoorsPearling, b_l_Value);
	b_l_Visible = b_l_Value ? true : false;
	pbDoorsPearling1->Visible = b_l_Visible;
	pbDoorsPearling2->Visible = b_l_Visible;
	ReadTCData(b_DoorsLoader, b_l_Value);
	b_l_Visible = b_l_Value ? true : false;
	pbDoorsLoader1->Visible = b_l_Visible;
	pbDoorsLoader2->Visible = b_l_Visible;

	ReadTCData(b_SavePersistent, b_l_Value);
	btnSavePersistent->Checked = b_l_Value ? true : false;
	btnSavePersistent->Visible = TUser::b_HasSystemLevel();

	if (b_ScreensCreated) {

		// Enable manual areas in manual mode only
		if (b_l_ManualMode){
			pT_LoaderManualForm->UpdateUI();
			pT_TableManualForm->UpdateUI();
			pT_PearlingManualForm->UpdateUI();
			pT_TurnOverManualForm->UpdateUI();
			pT_BarrelManualForm->UpdateUI();
			pT_SharpenManualForm->UpdateUI();
			pT_Lift1ManualForm->UpdateUI();
			pT_Lift2ManualForm->UpdateUI();
			pT_RejectManualForm->UpdateUI();
			pT_VisionManualForm->UpdateUI();
			pT_UtilitiesManualForm->UpdateUI();
			pT_VacuumSettingsForm->UpdateUI();
		} else {
			HideManualScreens();
		}
		pnlLoader->Enabled = b_l_ManualMode;
		pnlTable->Enabled = b_l_ManualMode;
		pnlPearling->Enabled = b_l_ManualMode;
		pnlTurnOver->Enabled = b_l_ManualMode;
		pnlBarrel->Enabled = b_l_ManualMode;
		pnlSharpen->Enabled = b_l_ManualMode;
		pnlLift1->Enabled = b_l_ManualMode;
		pnlLift2->Enabled = b_l_ManualMode;
		pnlReject->Enabled = b_l_ManualMode;
		pnlVision->Enabled = b_l_ManualMode;
		pnlUtilities->Enabled = b_l_ManualMode;
		pnlVacuum->Enabled = b_l_ManualMode;
	}
	// Update module options
	ReadTCData(s_MachineOpt.MO_TurnOver, b_l_Value);
	b_g_UseTurnover = b_l_Value ? true : false;
	if (!b_g_UseTurnover)
	{
		pnlTurnOver->Enabled = false;
		lblTurnover->Visible = false;
		lblTurnOverStatus->Visible = false;
		lblStepTurnover->Visible = false;
		msTurnOver->Visible = false;
		pnlImageTurnOver->Visible = false;
	}
}

void MachineScreen::Reload(void)
{
	if (b_ScreensCreated) 
	{
		HideManualScreens();
	}
}

void MachineScreen::MinimizeAll(void)
{
	if (b_ScreensCreated) 
	{
		HideManualScreens();
	}
}

System::Void MachineScreen::pnlCounter_Click(System::Object^  sender, System::EventArgs^  e) {
	((MainForm^)pT_frmMain)->SetCounterScreen();
}

