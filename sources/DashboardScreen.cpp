#include "DashboardScreen.h"

using namespace System::Globalization;

using namespace Projet1;

void DashboardScreen::UpdateUI()
{
	if (this->Visible)
	{
		TC_INT i_l_Status;
		TC_INT i_l_ScanOK,i_l_ScanTotal;

		ReadTCData(s_DashboardCmd.DC_MaxScanModel, i_l_Status);
		if (i_l_Status != cobModel->Items->Count)
		{
			cobModel->Items->Clear();
			for (int i = 0; i < i_l_Status; i++)
				cobModel->Items->Add((i + 1).ToString());
			if (i_l_Status > 0)
				cobModel->SelectedIndex = 0;
		}
		ReadTCData(s_DashboardCmd.DC_ScanModel, i_l_Status);
		if ((cobModel->Items->Count > 0) && (i_l_Status < cobModel->Items->Count))
		{
			if ((cobModel->SelectedIndex != i_l_Status) && (!cobModel->DroppedDown))
			{
				cobModel->SelectedIndex = i_l_Status;
			}
		}
		TUtilities::UpdateDoubleButton(GetTCData(s_DashboardCmd.DC_PickPlace), btnPickPlace_ON, btnPickPlace_OFF);
		TUtilities::UpdateMonostableButton(GetTCData(s_DashboardCmd.DC_Pearling), btnMovePearling);
		TUtilities::UpdateMonostableButton(GetTCData(s_DashboardCmd.DC_LoaderEndOfRecipe), btnMoveLiftLoader);
		TUtilities::UpdateMonostableButton(GetTCData(s_DashboardCmd.DC_TableTurn), btnMoveTable);
		TUtilities::UpdateMonostableButton(GetTCData(s_DashboardCmd.DC_LoaderScanPlateLift1), btnScanLift1);
		TUtilities::UpdateMonostableButton(GetTCData(s_DashboardCmd.DC_LoaderScanPlateLift2), btnScanLift2);
		TUtilities::UpdateMonostableButton(GetTCData(s_DashboardCmd.DC_LoaderScanPlateReject), btnScanReject);

		// Update scan results
		ReadTCData(s_DashboardCmd.DC_ScanPlateOK[0], i_l_ScanOK);
		ReadTCData(s_DashboardCmd.DC_ScanPlateTotal[0], i_l_ScanTotal);
		lblLift1ScanResult->Text = "(" + i_l_ScanOK + "/" + i_l_ScanTotal + ")";
		ReadTCData(s_DashboardCmd.DC_ScanPlateOK[1], i_l_ScanOK);
		ReadTCData(s_DashboardCmd.DC_ScanPlateTotal[1], i_l_ScanTotal);
		lblLift2ScanResult->Text = "(" + i_l_ScanOK + "/" + i_l_ScanTotal + ")";
		ReadTCData(s_DashboardCmd.DC_ScanPlateOK[2], i_l_ScanOK);
		ReadTCData(s_DashboardCmd.DC_ScanPlateTotal[2], i_l_ScanTotal);
		lblRejectScanResult->Text = "(" + i_l_ScanOK + "/" + i_l_ScanTotal + ")";
	}

}

void DashboardScreen::Reload(void)
{
	b_ScreenReloaded = true;
}


void DashboardScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(this->Controls);
}

