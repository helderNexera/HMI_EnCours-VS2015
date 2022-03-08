#include "LiftManualScreen.h"

using namespace Projet1;

void LiftManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_LREAL lr_l_PlatePos;
		TC_BOOL b_l_StatusMoveToPlateVision;
		TC_BOOL b_l_StatusMoveToPlate;
		TC_BOOL b_l_StatusDrawerInPos;
		TC_BOOL b_l_StatusPlateInPos;

		if (m_bIsGiver)
		{
			TUtilities::UpdateDoubleButton(GetTCManData(s_Lift1Manual.ML_LockDrawer), btnLockDrawer, btnUnlockDrawer);
			TUtilities::UpdateDoubleButton(GetTCManData(s_Lift1Manual.ML_LockPlate), btnLockPlate, btnUnlockPlate);
			ReadTCManData(s_Lift1Manual.ML_PlatePos, lr_l_PlatePos);
			ReadTCManData(s_Lift1Manual.ML_MoveToPlateVision.MB_Enable, b_l_StatusMoveToPlateVision);
			ReadTCManData(s_Lift1Manual.ML_MoveToPlate.MB_Enable, b_l_StatusMoveToPlate);
			ReadTCManData(s_Lift1Manual.ML_DrawerInPos, b_l_StatusDrawerInPos);
			ReadTCManData(s_Lift1Manual.ML_PlateInPos, b_l_StatusPlateInPos);
		}
		else
		{
			TUtilities::UpdateDoubleButton(GetTCManData(s_Lift2Manual.ML_LockDrawer), btnLockDrawer, btnUnlockDrawer);
			TUtilities::UpdateDoubleButton(GetTCManData(s_Lift2Manual.ML_LockPlate), btnLockPlate, btnUnlockPlate);
			ReadTCManData(s_Lift2Manual.ML_PlatePos, lr_l_PlatePos);
			ReadTCManData(s_Lift2Manual.ML_MoveToPlateVision.MB_Enable, b_l_StatusMoveToPlateVision);
			ReadTCManData(s_Lift2Manual.ML_MoveToPlate.MB_Enable, b_l_StatusMoveToPlate);
			ReadTCManData(s_Lift2Manual.ML_DrawerInPos, b_l_StatusDrawerInPos);
			ReadTCManData(s_Lift2Manual.ML_PlateInPos, b_l_StatusPlateInPos);
		}
		
		lblValuePlatePos->Text = String::Format("{0:F2}", lr_l_PlatePos);
		btnMoveToPlateVision->Enabled = (b_l_StatusMoveToPlateVision != 0);
		btnMoveToPlate->Enabled = (b_l_StatusMoveToPlate != 0);
		this->ledDrawerInPos->Value = !!b_l_StatusDrawerInPos;
		this->ledPlateInPos->Value = !!b_l_StatusPlateInPos;

		// Axis
		pT_Drive->UpdateUI();
	}
}

void LiftManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);
}

