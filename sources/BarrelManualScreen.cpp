#include "BarrelManualScreen.h"

using namespace Projet1;

void BarrelManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_BOOL b_l_Status;

		TUtilities::UpdateDoubleButton(GetTCManData(s_BarrelManual.MB_MoveJackUp),btnJackUp,btnJackDown);
		TUtilities::UpdateDoubleButton(GetTCManData(s_BarrelManual.MB_IndexUp),btnIndexUp,btnIndexDown);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_Move1Step),btnTakenMove1Step);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_MoveSectionA), btnTakenMoveSectionA);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_MoveSectionB), btnTakenMoveSectionB);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_MoveSectionC), btnTakenMoveSectionC);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_MoveSectionD), btnTakenMoveSectionD);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_Move1Step), btnCheckMove1Step);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_MoveSectionA), btnCheckMoveSectionA);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_MoveSectionB), btnCheckMoveSectionB);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_MoveSectionC), btnCheckMoveSectionC);
		TUtilities::UpdateMonostableButton(GetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_MoveSectionD), btnCheckMoveSectionD);

		ReadTCManData(s_BarrelManual.MB_StickPresent, b_l_Status);
		this->osStickPresent->Value = !!b_l_Status;

		TC_INT iIndexSection;
		TC_INT iIndexPosition;
		TC_INT iPosition;

		ReadTCManData(s_BarrelManual.MB_IndexSection, iIndexSection);
		ReadTCManData(s_BarrelManual.MB_IndexPosition, iIndexPosition);
		ReadTCManData(s_BarrelManual.MB_Position, iPosition);
		
		String^ sTextPosition = "";
		
		if (iPosition == 0)
		{
			sTextPosition = TUtilities::pS_LoadString(TextIndex::Position) + " : " + TUtilities::pS_LoadString(TextIndex::Unspecified);
		}
		else
		{
			String^ sPosition = "";
			String^ sSection = "";
			switch (iIndexSection)
			{
			case 1:
				sSection = TUtilities::pS_LoadString(TextIndex::MoveSectionA);
				break;
			case 2:
				sSection = TUtilities::pS_LoadString(TextIndex::MoveSectionB);
				break;
			case 3:
				sSection = TUtilities::pS_LoadString(TextIndex::MoveSectionC);
				break;
			case 4:
				sSection = TUtilities::pS_LoadString(TextIndex::MoveSectionD);
				break;
			default:
				sSection = TUtilities::pS_LoadString(TextIndex::DataError);
				break;
			}

			switch (iPosition)
			{
			case 1:
				sPosition = TUtilities::pS_LoadString(TextIndex::Take);
				break;
			case 2:
				sPosition = TUtilities::pS_LoadString(TextIndex::StickCheck);
				break;
			default:
				sPosition = TUtilities::pS_LoadString(TextIndex::DataError);
				break;
			}
			sTextPosition = TUtilities::pS_LoadString(TextIndex::Position) + " : " + sPosition + ", " + sSection + ", " + iIndexPosition.ToString();
		}

		this->lblPosition->Text = sTextPosition;

		// Axis
		pT_Drive->UpdateUI();
	}
}


void BarrelManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabPage1->Controls);
}
