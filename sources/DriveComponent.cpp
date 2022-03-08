#include "DriveComponent.h"

using namespace Projet1;

#include "stddef.h"
#include "TUtilities.h"

using namespace std;
using namespace System;
using namespace System::Threading;

void DriveComponent::UsePosition(int i_x_Position,String^ s_x_PostionName)
{
	a_lblPosName[i_x_Position]->Text = s_x_PostionName;
	a_lblPosName[i_x_Position]->Tag = "1";
	a_lblAxisPos[i_x_Position]->Tag = "1";
	a_btnAxisMove2Pos[i_x_Position]->Tag = "1";
	a_btnAxisTeachPos[i_x_Position]->Tag = "2";
}

void DriveComponent::UsePosition(int i_x_Position,String^ s_x_PostionName,int i_x_MinValue,int i_x_MaxValue)
{
	UsePosition(i_x_Position,s_x_PostionName);
	this->a_cobAxisListPos[i_x_Position]->Tag = "1";
	for (int i=i_x_MinValue;i<=(i_x_MaxValue);i++)
		a_cobAxisListPos[i_x_Position]->Items->Add(i);
}

void DriveComponent::UpdateUI(void)
{
	int i;
	TC_INT i_l_Data;
	TC_LREAL d_l_Data;

	TUtilities::UpdateBistableButton(GetTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_ServoON)), btnAxisServo);
	TUtilities::UpdateBistableButton(GetTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_Home)), btnAxisHome);
	TUtilities::UpdateBistableButton(GetTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_Specific)), btnAxisSpecific);

	ReadTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_JogStep), d_l_Data);
	tbaxisJogStep->Text = String::Format("{0:F3}", d_l_Data);

	ReadTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_CurrentPos), d_l_Data);
	lblAxisCurrentPos->Text = String::Format("{0:F3}", d_l_Data);
	TUtilities::UpdateMonostableButton(GetTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_MoveFw)), btnaxisJogP);
	TUtilities::UpdateMonostableButton(GetTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_MoveBw)), btnaxisJogN);
	for (i = 0; i < 4; i++)
	{
		if (a_btnAxisMove2Pos[i]->Visible)
		{
			TUtilities::UpdateMonostableButton(GetTCManOffsetData(a_PositionDataOffset[i] + offsetof(TC_MAN_DRIVE_POS, MDP_MoveToTeach)), a_btnAxisMove2Pos[i]);
			ReadTCManOffsetData(a_PositionDataOffset[i] + offsetof(TC_MAN_DRIVE_POS, MDP_TeachedPos), d_l_Data);
			a_lblAxisPos[i]->Text = String::Format("{0:F3}", d_l_Data);
		}
		if (a_cobAxisListPos[i]->Visible)
		{
			if (-1 == a_cobAxisListPos[i]->SelectedIndex)
			{
				ReadTCManOffsetData(a_CobDataOffset[i], i_l_Data);
				a_cobAxisListPos[i]->SelectedIndex = i_l_Data;
			}
		}
	}

	bool bRefreshPosition = false;
	if (btnAxisHome->Visible != TUser::b_HasSystemLevel())
	{
		bRefreshPosition = true;
		btnAxisHome->Visible = TUser::b_HasSystemLevel();
	}
	if (btnAxisSpecific->Visible != b_UseSpecificButton)
	{
		bRefreshPosition = true;
		btnAxisSpecific->Visible = b_UseSpecificButton;
	}
	if (bRefreshPosition)
	{
		this->btnAxisHome->Location = System::Drawing::Point(10, 33);
		this->btnAxisHome->Size = System::Drawing::Size(75, 60);
		this->btnAxisSpecific->Location = System::Drawing::Point(10, 33);
		this->btnAxisSpecific->Size = System::Drawing::Size(75, 60);
		if (b_UseSpecificButton && TUser::b_HasSystemLevel())
		{
			int Size = btnAxisHome->Height + 50;
			int Pos = btnAxisHome->Top - 15;
			btnAxisHome->Top = Pos;
			btnAxisHome->Height = Size / 2 - 5;
			btnAxisSpecific->Top = btnAxisHome->Top + btnAxisHome->Height + 5 * 2;
			btnAxisSpecific->Height = Size / 2 - 5;
		}
	}
}

void DriveComponent::ReloadComponent(void)
{
	for (int i=0;i<4;i++)
	{
		a_btnAxisMove2Pos[i]->Text = TUtilities::pS_LoadString(TextIndex::MoveTo);
		a_btnAxisTeachPos[i]->Text = TUtilities::pS_LoadString(TextIndex::Teach);
	}
	btnAxisServo->Text = TUtilities::pS_LoadString(TextIndex::Servo);
	btnAxisHome->Text = TUtilities::pS_LoadString(TextIndex::Home);
	lblAxisCurrentPos->Text = TUtilities::pS_LoadString(TextIndex::Position);
}
void DriveComponent::SetPositionName(int i_x_Position,String^ pS_x_PositionName)
{
	a_lblPosName[i_x_Position]->Text = pS_x_PositionName;
}

void DriveComponent::SetDriveName(String^ pS_x_DriveName,String^ pS_x_SpecificName)
{
	s_ComponentName = pS_x_DriveName;
	btnAxisSpecific->Text = pS_x_SpecificName;
}

void DriveComponent::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(pT_MyContainer->Controls);
}

