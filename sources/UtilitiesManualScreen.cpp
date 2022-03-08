#include "UtilitiesManualScreen.h"

using namespace Projet1;

void UtilitiesManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_BOOL b_l_Status;
		TC_DWORD d_l_Data;

		TUtilities::UpdateDoubleButton(GetTCManData(s_UtilitiesManual.MU_Aspiration), btnAspiration_ON, btnAspiration_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_UtilitiesManual.MU_Vacuum), btnVacuum_ON, btnVacuum_OFF);
		TUtilities::UpdateMonostableButton(GetTCManData(s_UtilitiesManual.MU_ResetAspirationUseTime), btnResetAspirationUseTime);
		TUtilities::UpdateMonostableButton(GetTCManData(s_UtilitiesManual.MU_ResetVacuumUseTime), btnResetVacuumUseTime);

		ReadTCManData(s_UtilitiesManual.MU_PowerIsOn, b_l_Status);
		this->ledPower->Value = !!b_l_Status;
		ReadTCManData(s_UtilitiesManual.MU_DrivesIsOn, b_l_Status);
		this->ledDrive->Value = !!b_l_Status;
		ReadTCManData(s_UtilitiesManual.MU_24VOK, b_l_Status);
		this->led24V->Value = !!b_l_Status;
		ReadTCManData(s_UtilitiesManual.MU_48VOK, b_l_Status);
		this->led48V->Value = !!b_l_Status;
		ReadTCManData(s_UtilitiesManual.MU_AirPressureOK, b_l_Status);
		this->ledAirPressure->Value = !!b_l_Status;
		ReadTCManData(s_UtilitiesManual.MU_MainVacuumOK, b_l_Status);
		this->ledVacuum->Value = !!b_l_Status;
		ReadTCManData(s_UtilitiesManual.MU_AspirationOK, b_l_Status);
		this->ledAspiration->Value = !!b_l_Status;
		ReadTCManData(s_UtilitiesManual.MU_AspirationIsOn, b_l_Status);
		this->ledAspirationOn->Value = !!b_l_Status;

		ReadTCManData(s_UtilitiesManual.MU_AspirationUseTime, d_l_Data);
		tbAspirationUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCManData(s_UtilitiesManual.MU_VacuumUseTime, d_l_Data);
		tbVacuumUseTime->Text = String::Format("{0:D}", d_l_Data);

		// Axis
	}
}

void Projet1::UtilitiesManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);
}
