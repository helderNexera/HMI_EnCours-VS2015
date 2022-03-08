#include "VacuumSettingsScreen.h"

using namespace Projet1;

void VacuumSettingsScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_INT i_l_Data;

		for each (Control^ ctrl in this->tableLayoutPanel1->Controls)
		{
			LabelOffset^ lbl = dynamic_cast<LabelOffset ^>(ctrl);
			if (lbl != nullptr)
			{
				ReadTCManOffsetData(lbl->Offset, i_l_Data);
				lbl->Text = String::Format("{0:D}", i_l_Data);
			}
		}
		lblTurnOver->Visible = b_g_UseTurnover;
		lblTurnOverBlowing->Visible = b_g_UseTurnover;
		lblTurnOverWaitVacuumOk->Visible = b_g_UseTurnover;
		lblTurnOverErrorDelay->Visible = b_g_UseTurnover;
	}
}

void VacuumSettingsScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);
}
