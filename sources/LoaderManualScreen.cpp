#include "LoaderManualScreen.h"

using namespace Projet1;

void LoaderManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_INT i_l_Data;
		TC_LREAL lr_l_Data;
		TC_BOOL b_l_Data;
		bool b_l_Test = false;
		// Loader robot
		TUtilities::UpdateDoubleButton(GetTCManData(s_LoaderManual.ML_Head1Vacuum),btnHead1VacuumON,btnHead1VacuumOFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_LoaderManual.ML_Head2Vacuum),btnHead2VacuumON,btnHead2VacuumOFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_LoaderManual.ML_PlateVacuum),btnVacuumPlate_ON,btnVacuumPlate_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_LoaderManual.ML_MovePlateTakerDown),btnMovePlateTakerDown,btnMovePlateTakerUp);
		TUtilities::UpdateMonostableButton(GetTCManData(s_LoaderManual.ML_Safe), btnRobotSafe);
		TUtilities::UpdateMonostableButton(GetTCManData(s_LoaderManual.ML_VisionCalibration), btnVisionCalibration);
		TUtilities::UpdateMonostableButton(GetTCManData(s_LoaderManual.ML_ZSensorTeach), btnZSensorTeach);
		ReadTCData(s_MachineOpt.MO_DisableVision, b_l_Data);
		cbDisableVision->Checked = (b_l_Data != 0);
		ReadTCData(s_MachineOpt.MO_SpeedModeSlow, b_l_Data);
		cbSpeedModeSlow->Checked = (b_l_Data != 0);

		ReadTCManData(s_LoaderManual.ML_RobotPos, i_l_Data);
		if ((-1 == cobRobotPosition->SelectedIndex) || (((cbElement^)cobRobotPosition->SelectedItem)->Position != i_l_Data))
		{
			for each (cbElement^ obj in cobRobotPosition->Items)
			{
				if (obj->Position == i_l_Data)
				{
					cobRobotPosition->SelectedItem = obj;
					break;
				}
			}
		}
		else
		{
			cbElement^ oElement = (cbElement^)cobRobotPosition->SelectedItem;
			SetUI(oElement->Axis);
		}

		ReadTCManData(s_LoaderManual.ML_TableSide, i_l_Data);
		m_eTableSide = (E_TableSide)i_l_Data;


		ReadTCManData(s_LoaderManual.ML_AxisZSafe[0], b_l_Data);
		m_AxisZ1Safe = b_l_Data ? true : false;
		ReadTCManData(s_LoaderManual.ML_AxisZSafe[1], b_l_Data);
		m_AxisZ2Safe = b_l_Data ? true : false;

		pT_RobotXDrive->UpdateUI();
		pT_RobotYDrive->UpdateUI();
		pT_RobotZ1Drive->UpdateUI();
		pT_RobotZ2Drive->UpdateUI();
		pT_RobotThetaDrive->UpdateUI();

		// Sensor adjustment. Visible only with system access

		ReadTCManData(s_LoaderManual.ML_SensorAdjust, lr_l_Data);
		lblValueSensorCorrection->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManData(s_LoaderManual.ML_SensorMeasure, lr_l_Data);
		lblValueSensorMeasure->Text = String::Format("{0:F2}", lr_l_Data);
		if (bReloadParams)
			bReloadParams = false;

		ReadTCManData(s_LoaderManual.MT_VacuumValue[0], lr_l_Data);
		tbVacuumHead1->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManData(s_LoaderManual.MT_VacuumValue[1], lr_l_Data);
		tbVacuumHead2->Text = String::Format("{0:F2}", lr_l_Data);

		ReadTCManOffsetData(lblVacuumThresholdHead1->Offset, lr_l_Data);
		lblVacuumThresholdHead1->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCManOffsetData(lblVacuumThresholdHead2->Offset, lr_l_Data);
		lblVacuumThresholdHead2->Text = String::Format("{0:F2}", lr_l_Data);
		
	}
}

void LoaderManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(tabOther->Controls);
	TUtilities::SetVisible(tabRobot->Controls);
}


void LoaderManualScreen::SetUI(E_Axis eAxis)
{
	switch (eAxis)
	{
		case E_Axis::Z1:
			TUtilities::SetVisible(gbRobotZ1axis, true);
			TUtilities::SetVisible(gbRobotZ2axis, false);
			TUtilities::SetVisible(gbRobotThetaaxis,true);
			break;
		case E_Axis::Z2:
			TUtilities::SetVisible(gbRobotZ1axis, false);
			TUtilities::SetVisible(gbRobotZ2axis, true);
			TUtilities::SetVisible(gbRobotThetaaxis, true);
			break;
		case E_Axis::Plate:
		case E_Axis::Vision:
		case E_Axis::ZSensor:
			TUtilities::SetVisible(gbRobotZ1axis,false);
			TUtilities::SetVisible(gbRobotZ2axis,false);
			TUtilities::SetVisible(gbRobotThetaaxis,false);
			break;
	}
}

