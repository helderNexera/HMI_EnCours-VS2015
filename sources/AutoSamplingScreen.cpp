#include "AutoSamplingScreen.h"

using namespace Projet1;

void AutoSamplingScreen::UpdateUI(void)
{
	TC_INT i_l_Data;

	if (this->Visible)
	{
		TUtilities::UpdateMonostableButton(GetTCData(s_ProductionCmd.PC_RequestSample), btnRequestSample);
		ReadTCData(s_ProductionCmd.PC_AutoSampling.AS_PeriodCnt, i_l_Data);
		lblASPeriodCounter->Text = "(" + String::Format("{0:D}", i_l_Data) + ")";
		ReadTCData(s_ProductionCmd.PC_AutoSampling.AS_BatchCnt, i_l_Data);
		lblASBatchCounter->Text = "(" + String::Format("{0:D}", i_l_Data) + ")";

	}
}

void AutoSamplingScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
}

