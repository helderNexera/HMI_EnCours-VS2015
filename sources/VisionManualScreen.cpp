#include "VisionManualScreen.h"

using namespace Projet1;

void VisionManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_BOOL b_l_Status;
		TC_INT i_l_Status;
		TC_LREAL lr_l_Data;
		TC_TIME stTime;

		TUtilities::UpdateMonostableButton(GetTCManData(s_LoaderManual.ML_MoveVision2Table), btnMoveVisionToTable);
		TUtilities::UpdateMonostableButton(GetTCManData(s_LoaderManual.ML_MoveVision2Lift), btnMoveVisionToLift);

		ReadTCManData(s_VisionManual.MV_Analyse.MB_Enable, b_l_Status);
		btnAnalyse->Enabled = (b_l_Status != 0);
		ReadTCManData(s_VisionManual.MV_Init.MB_Enable, b_l_Status);
		btnInit->Enabled = (b_l_Status != 0);
		ReadTCManData(s_VisionManual.MV_PartData.VPD_Valid, b_l_Status);
		ledValid->Value = (b_l_Status != 0);
		ReadTCManData(s_VisionManual.MV_PartData.VPD_Present, b_l_Status);
		ledPartPresent->Value = (b_l_Status != 0);

		ReadTCManData(s_VisionManual.MV_PartDataValid, b_l_Status);
		TUtilities::SetVisible(gbResult,b_l_Status ? true : false);

		ReadTCManData(s_VisionManual.MV_PartData.VPD_Score, lr_l_Data);
		lblValueScore->Text = String::Format("{0:F2}%" , lr_l_Data*100);
		ReadTCManData(s_VisionManual.MV_PartData.VPD_Theta, lr_l_Data);
		lblValueTheta->Text = String::Format("{0:F1}", lr_l_Data);
		ReadTCManData(s_VisionManual.MV_PartData.VPD_X, lr_l_Data);
		lblValueX->Text = String::Format("{0:F3}", lr_l_Data);
		ReadTCManData(s_VisionManual.MV_PartData.VPD_Y, lr_l_Data);
		lblValueY->Text = String::Format("{0:F3}", lr_l_Data);

		ReadTCManData(s_VisionManual.MV_Connected, b_l_Status);
		this->ledConnected->Value = !!b_l_Status;
		ReadTCManData(s_VisionManual.MV_Ready, b_l_Status);
		this->ledReady->Value = !!b_l_Status;
		ReadTCManData(s_VisionManual.MV_SimRecipe, b_l_Status);
		this->ledSimulation->Value = !!b_l_Status;
		ReadTCManData(s_VisionManual.MV_InitTime, stTime);
		lblInitTime->Text = FormatTime(stTime);
		ReadTCManData(s_VisionManual.MV_AnalyseTime, stTime);
		lblAnalyseTime->Text = FormatTime(stTime);

		TUtilities::UpdateBistableButton(GetTCManData(s_VisionManual.MV_Run), btnRun);
		TUtilities::UpdateBistableButton(GetTCManData(s_VisionManual.MV_ConfigMode), btnConfigMode);

		ReadTCManData(s_VisionManual.MV_MaxModel, i_l_Status);
		if (i_l_Status != cobModel->Items->Count)
		{
			cobModel->Items->Clear();
			for (int i = 0; i < i_l_Status; i++)
				cobModel->Items->Add((i+1).ToString());
			if (i_l_Status>0)
				cobModel->SelectedIndex = 0;
		}

		ReadTCManData(s_VisionManual.MV_UseModel, i_l_Status);
		if ((cobModel->Items->Count > 0) && (i_l_Status < cobModel->Items->Count))
		{
			if ((cobModel->SelectedIndex != i_l_Status) && (!cobModel->DroppedDown))
			{
				cobModel->SelectedIndex = i_l_Status;
			}
		}

		if (bReloadParams)
		{
			char ac_l_RecipeName[255];
			TTwincatInterface::GetTCVarAccess()->GetData(DVT_Manual, offsetof(MANUAL_DATA, s_VisionManual.MV_VisionRecipeName), ac_l_RecipeName);
			tbRecipe->Text = gcnew String(ac_l_RecipeName);
			bReloadParams = false;
		}
	}

}

String^ VisionManualScreen::FormatTime(TC_TIME stTime)
{
	return stTime.T_Hour.ToString("D2") + ":" + stTime.T_Minute.ToString("D2") + ":" + stTime.T_Second.ToString("D2");
}

void VisionManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);
	TUtilities::SetVisible(gbResult->Controls);
	TUtilities::SetVisible(gbStatus->Controls);
}

