#include "TableManualScreen.h"

using namespace Projet1;

void TableManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_LREAL lr_l_Data;
		TC_BOOL b_l_Data;

		// buttons
		TUtilities::UpdateDoubleButton(GetTCManData(s_TableManual.MT_AspirationDown),btnAspirationDown,btnAspirationUp);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TableManual.MT_IndexTable),btnIndexMoveUp,btnIndexMoveDown);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TableManual.MT_VacuumPos1),btnVacuum1_ON,btnVacuum1_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TableManual.MT_VacuumPos2),btnVacuum2_ON,btnVacuum2_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TableManual.MT_VacuumPos3),btnVacuum3_ON,btnVacuum3_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TableManual.MT_VacuumPos4),btnVacuum4_ON,btnVacuum4_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_ActivateAspirationTable[0]), btnPearling1Aspiration_ON, btnPearling1Aspiration_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_ActivateAspirationTable[1]), btnPearling2Aspiration_ON, btnPearling2Aspiration_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TableManual.MT_AspirationBrush), btnBrushAspiration_ON, btnBrushAspiration_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TableManual.MT_CleanBrushDown), btnCleanBrushDown, btnCleanBrushUp);

		ReadTCData(s_MachineOpt.MO_DisableCleanAfterPearling, b_l_Data);
		cbDisableCleanAfterPearl->Checked = (b_l_Data != 0);

		//Value
		ReadTCManData(s_TableManual.MT_VacuumValue[0], lr_l_Data);
		tbVacuum1->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManData(s_TableManual.MT_VacuumValue[1], lr_l_Data);
		tbVacuum2->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManData(s_TableManual.MT_VacuumValue[2], lr_l_Data);
		tbVacuum3->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManData(s_TableManual.MT_VacuumValue[3], lr_l_Data);
		tbVacuum4->Text = String::Format("{0:F2}", lr_l_Data);

		ReadTCManOffsetData(lblVacuumThreshold1->Offset, lr_l_Data);
		lblVacuumThreshold1->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManOffsetData(lblVacuumThreshold2->Offset, lr_l_Data);
		lblVacuumThreshold2->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManOffsetData(lblVacuumThreshold3->Offset, lr_l_Data);
		lblVacuumThreshold3->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManOffsetData(lblVacuumThreshold4->Offset, lr_l_Data);
		lblVacuumThreshold4->Text = String::Format("{0:F2}", lr_l_Data);


		// Axis
		pT_DriveTable->UpdateUI();
		pT_DriveBrush->UpdateUI();

	}
}

void TableManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);
	TUtilities::SetVisible(tabPage2->Controls);
	TUtilities::SetVisible(tabPage3->Controls);
}

