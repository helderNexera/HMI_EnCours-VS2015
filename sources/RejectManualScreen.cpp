#include "RejectManualScreen.h"

using namespace Projet1;

void RejectManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_BOOL b_l_StatusDrawerInPos;
		TC_BOOL b_l_StatusPlateInPos;

		// Access restriction
		ReadTCManData(s_RejectManual.MR_DrawerInPos, b_l_StatusDrawerInPos);
		ReadTCManData(s_RejectManual.MR_PlateInPos, b_l_StatusPlateInPos);
		this->ledDrawerInPos->Value = !!b_l_StatusDrawerInPos;
		this->ledPlateInPos->Value = !!b_l_StatusPlateInPos;

		// Axis
	}
}

void RejectManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);

}
