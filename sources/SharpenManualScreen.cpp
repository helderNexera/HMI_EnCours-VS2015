#include "SharpenManualScreen.h"

using namespace Projet1;

void SharpenManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_BOOL b_l_Status;
		TC_LREAL lr_l_Data;

		ReadTCManData(s_SharpenManual.MS_Move2NextPos.MB_Enable,b_l_Status);
		btnMove2NextStep->Enabled = (b_l_Status != 0);

		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_ActivateAspirationSharpen),btnAspiration_ON,btnAspiration_OFF);

		ReadTCManData(s_SharpenManual.MS_TapeNotEmpty, b_l_Status);
		this->ledTapeNotEmpty->Value = !!b_l_Status;

		//if (bReloadParams)
		{
			ReadTCManData(s_SharpenManual.MS_Step, lr_l_Data);
			lblStepValue->Text = String::Format("{0:F1}", lr_l_Data);
			bReloadParams = false;
		}

		// Axis
		pT_Drive->UpdateUI();
	}
}


void SharpenManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);
}

