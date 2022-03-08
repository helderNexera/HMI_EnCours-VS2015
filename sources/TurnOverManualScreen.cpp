#include "TurnOverManualScreen.h"

using namespace Projet1;

void TurnOverManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TUtilities::UpdateDoubleButton(GetTCManData(s_TurnOverManual.MTO_MoveJackUp),btnMoveArmUp,btnMoveArmDown);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TurnOverManual.MTO_ArmVacuum),btnArmVacuum_ON,btnArmVacuum_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TurnOverManual.MTO_FixVacuum),btnFixVacuum_ON,btnFixVacuum_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_LoaderManual.ML_AspirationBrush), btnAspiration_ON, btnAspiration_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_TurnOverManual.MTO_ActivateCleaningBlow), btnBlow_ON, btnBlow_OFF);

		pT_Drive->UpdateUI();
	}
}


void Projet1::TurnOverManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tbTurnOver->Controls);
}

