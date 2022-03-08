#include "AlarmScreen.h"
#include "TUtilities.h"
#include "MyMsgBox.h"

using namespace Projet1;

String^ AlarmScreen::pS_GetAlarm(int i_x_AlarmID)
{
	String^ pS_l_Keys = i_x_AlarmID.ToString();

	if (apS_AlarmText->ContainsKey(pS_l_Keys))

		return apS_AlarmText[pS_l_Keys][i_g_LanguageNb];
	else
	{
		return "L'alarme avec un ID de " + pS_l_Keys + " n'a pas été trouvée dans la liste";;
	}
}

String^ AlarmScreen::pS_GetLastAlarm(bool* pb_x_IsActive)
{
	String^ pS_l_LastAlarm = "";
	bool b_l_IsACtive = false;

	for (int i=0;i<AlarmScreen::pT_This->dgvAlarmsList->RowCount;i++)
	{
		if (Color::Red == AlarmScreen::pT_This->dgvAlarmsList->Rows[i]->Cells[1]->Style->ForeColor)
		{
			pS_l_LastAlarm = (AlarmScreen::pT_This->dgvAlarmsList->Rows[i]->Cells[0]->Value + "          " + AlarmScreen::pT_This->dgvAlarmsList->Rows[i]->Cells[1]->Value);
			b_l_IsACtive = true;
			break;
		}
	}
	if (!b_l_IsACtive && (AlarmScreen::pT_This->dgvAlarmsList->RowCount > 0))
		pS_l_LastAlarm = (AlarmScreen::pT_This->dgvAlarmsList->Rows[0]->Cells[0]->Value + "          " + AlarmScreen::pT_This->dgvAlarmsList->Rows[0]->Cells[1]->Value);
	*pb_x_IsActive = b_l_IsACtive;
	return pS_l_LastAlarm;
}

void AlarmScreen::UpdateAlarmsTable(void)
{
	bool b_l_AlarmStatus;
	int i_l_ActualRow;
	String^ pS_l_AlarmText;
	bool b_l_AlarmsChanged = false;
	int i;

	// Check if the alarm table has changed
	for (i=0;i<C_MAX_NB_OF_ERRORS;i++)
	{
		ReadTCError(i,b_l_AlarmStatus);
		if (ab_AlarmsStatus[i] != b_l_AlarmStatus)
		{
			b_l_AlarmsChanged = true;
			break;
		}
	}
	
	if (b_l_AlarmsChanged || b_ForceRefresh)
	{
		dgvAlarmsList->Rows->Clear();
		for (i=0;i<C_MAX_NB_OF_ERRORS;i++)
		{
			pS_l_AlarmText = pS_GetAlarm(i);
			ReadTCError(i,b_l_AlarmStatus);
			if (b_l_AlarmStatus)
			{
				// Check if it was not active before
				if (!ab_AlarmWasOn[i] || ab_AlarmIsOff[i])
				{
					ab_AlarmWasOn[i] = true;
					ab_AlarmIsOff[i] = false;
					// It is a new alarm, load appearance time
					aT_AlarmAppearanceTime[i] = DateTime::Now;
					// And log it
					TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::AlarmAppeared) + " : " + pS_l_AlarmText);
				}
				i_l_ActualRow = dgvAlarmsList->Rows->Add(TUtilities::pS_FormatDateTime(aT_AlarmAppearanceTime[i]),pS_l_AlarmText,aT_AlarmAppearanceTime[i].ToString("u"));
				dgvAlarmsList->Rows[i_l_ActualRow]->Cells[1]->Style->ForeColor = Color::Red; 
			}
			else
			{
				if (ab_AlarmWasOn[i])
				{
					if (!ab_AlarmIsOff[i])
					{
						// Alarm has disappeared
						if (b_ForceRefresh)
							ab_AlarmWasOn[i] = false;
						else
							ab_AlarmIsOff[i] = true;
						// And log it
						TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::AlarmDisappeared) + " : " + pS_l_AlarmText,aT_AlarmAppearanceTime[i],DateTime::Now);
					}
					if (!b_ForceRefresh)
					{
						i_l_ActualRow = dgvAlarmsList->Rows->Add(TUtilities::pS_FormatDateTime(aT_AlarmAppearanceTime[i]),pS_l_AlarmText,aT_AlarmAppearanceTime[i].ToString("u"));
						dgvAlarmsList->Rows[i_l_ActualRow]->Cells[1]->Style->ForeColor = Color::Black; 
					}
				}
			}
			ab_AlarmsStatus[i] = b_l_AlarmStatus;
		}
		dgvAlarmsList->Sort(dgvAlarmsList->Columns[2],ListSortDirection::Descending);
		b_ForceRefresh = false;
	}
	// Check if a validation is needed
	if (b_NoValidation)
	{
		for (i=0;i<C_MAX_NB_OF_ERRORS;i++)
		{
			ReadTCValError(i,b_l_AlarmStatus);
			if (b_l_AlarmStatus)
			{
				b_NoValidation = false;
				pS_l_AlarmText = pS_GetAlarm(i);
				MyMsgBox^ pT_l_ValidateAlarm = gcnew MyMsgBox(pS_l_AlarmText,"Alarme à valider",MessageBoxButtons::OK);
				pT_l_ValidateAlarm->ShowDialog();
				WriteTCData(ab_ValErrors[i],(TC_BOOL)false);
				b_NoValidation = true;
				break;
			}
		}
	}
}

void AlarmScreen::ResetAlarmList(void)
{
	AlarmScreen::b_ForceRefresh = true;
	for (int i=0;i<C_MAX_NB_OF_ERRORS;i++)
	{
		if (AlarmScreen::pT_This->ab_AlarmIsOff[i])
		{
			AlarmScreen::pT_This->ab_AlarmWasOn[i] = false;
			AlarmScreen::pT_This->ab_AlarmIsOff[i] = false;
		}
	}
}

void AlarmScreen::Reload(void)
{
	AlarmScreen_VisibleChanged(nullptr,nullptr);
	AlarmScreen::b_ForceRefresh = true;
}
