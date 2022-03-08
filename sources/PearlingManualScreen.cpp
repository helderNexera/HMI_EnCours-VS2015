#include "PearlingManualScreen.h"

using namespace Projet1;

void PearlingManualScreen::UpdateUI(void)
{
	if (this->Visible)
	{
		TC_BOOL b_l_Data;
		TC_INT i_l_Data;
		TC_LREAL lr_l_Data;
		TC_REAL r_l_Data;
		TC_DWORD d_l_Data;

		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_StartMotor[0]),btnLeftMotor_ON,btnLeftMotor_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_StartMotor[1]),btnRightMotor_ON,btnRightMotor_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_OpenChuck[0]),btnOpenLeftChuck,btnCloseLeftChuck);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_OpenChuck[1]),btnOpenRightChuck,btnCloseRightChuck);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_EjectStick[0]),btnLeftEject_ON,btnLeftEject_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_EjectStick[1]),btnRightEject_ON,btnRightEject_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_Blowing[0]),btnLeftBlowing_ON,btnLeftBlowing_OFF);
		TUtilities::UpdateDoubleButton(GetTCManData(s_PearlingManual.MP_Blowing[1]),btnRightBlowing_ON,btnRightBlowing_OFF);
		TUtilities::UpdateMonostableButton(GetTCManData(s_PearlingManual.MP_CalibrateWeight[0]),btnCalibrateLeftWeight);
		TUtilities::UpdateMonostableButton(GetTCManData(s_PearlingManual.MP_CalibrateWeight[1]),btnCalibrateRightWeight);

		ReadTCManData(s_PearlingManual.MP_TeachPos, i_l_Data);
		if ((-1 == cobCalibrationPosition->SelectedIndex) || (((cbElement^)cobCalibrationPosition->SelectedItem)->Position != i_l_Data))
		{
			for each (cbElement^ obj in cobCalibrationPosition->Items)
			{
				if (obj->Position == i_l_Data)
				{
					cobCalibrationPosition->SelectedItem = obj;
					break;
				}
			}
		}
		else
		{
			cbElement^ oElement = (cbElement^)cobCalibrationPosition->SelectedItem;
			SetUI(oElement->Axis);
		}

		ReadTCManData(s_PearlingManual.MP_TableSide, i_l_Data);
		m_eTableSide = (E_TableSide)i_l_Data;


		ReadTCManData(s_PearlingManual.MP_AxisZSafe[0], b_l_Data);
		m_AxisZ1Safe = b_l_Data ? true : false;
		ReadTCManData(s_PearlingManual.MP_AxisZSafe[1], b_l_Data);
		m_AxisZ2Safe = b_l_Data ? true :  false;

		// Axis
		pT_XDrive->UpdateUI();
		pT_YDrive->UpdateUI();
		pT_Z1Drive->UpdateUI();
		pT_Z2Drive->UpdateUI();

		ReadTCManData(s_PearlingManual.MP_CurrentMotorMinTh, i_l_Data);
		lblCurrentMotorMinThreshold->Text = String::Format("{0:D3}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_CurrentMotorWarnTh, i_l_Data);
		lblCurrentMotorWarnThreshold->Text = String::Format("{0:D3}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_CurrentMotorMaxTh, i_l_Data);
		lblCurrentMotorMaxThreshold->Text = String::Format("{0:D3}", i_l_Data);

		ReadTCManData(s_PearlingManual.MP_MotorStartedTimeout[0], i_l_Data);
		lblLeftMotorStartTimeout->Text = String::Format("{0:D}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_MotorStartedTimeout[1], i_l_Data);
		lblRightMotorStartTimeout->Text = String::Format("{0:D}", i_l_Data);

		ReadTCManData(s_PearlingManual.MP_MotorStoppedTimeout[0], i_l_Data);
		lblLeftMotorStopTimeout->Text = String::Format("{0:D}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_MotorStoppedTimeout[1], i_l_Data);
		lblRightMotorStopTimeout->Text = String::Format("{0:D}", i_l_Data);
		if (bReloadParams)
		{
			/*ReadTCData(s_StickDataShared.SDS_MinHoldLength, lr_l_Data);
			tbMinHoldLength->Text = String::Format("{0:F2}", lr_l_Data);*/
			/*ReadTCData(s_StickDataShared.SDS_SharpenHeight, lr_l_Data);
			tbSharpenHeight->Text = String::Format("{0:F2}", lr_l_Data);*/
			/*ReadTCData(s_StickDataShared.SDS_SharpenSpeed, lr_l_Data);
			tbSharpenSpeed->Text = String::Format("{0:F0}", lr_l_Data);*/
			ReadTCData(s_StickDataShared.SDS_RestartBeginOfArea, b_l_Data);
			cbRestartBeginOfArea->Checked = (b_l_Data != 0);
			/*ReadTCData(s_StickDataShared.SDS_NbOfFwBwSharpen, i_l_Data);
			tbNbOfFwBwSharpen->Text = String::Format("{0:D}", i_l_Data);*/
			ReadTCData(s_StickDataShared.SDS_StopOnVacuumLoss, b_l_Data);
			cbStopOnVacuumLoss->Checked = (b_l_Data != 0);
			ReadTCData(s_StickDataShared.SDS_StopOnStickBreak, b_l_Data);
			cbStopOnStickBreak->Checked = (b_l_Data != 0);
			ReadTCData(b_SimPearling, b_l_Data);
			cbSimPearling->Checked = (b_l_Data != 0);
			ReadTCData(s_StickDataShared.SDS_StopOnWeightOutOfTolerance, b_l_Data);
			cbStopOnWeightOutOfTolerance->Checked = (b_l_Data != 0);
			bReloadParams = false;
		}
		ReadTCData(as_StickDataMMI[0].SD_MCRCorrectionStep, lr_l_Data);
		tbLeftCompensationStep->Text = String::Format("{0:F3}", lr_l_Data);
		ReadTCData(as_StickDataMMI[1].SD_MCRCorrectionStep, lr_l_Data);
		tbRightCompensationStep->Text = String::Format("{0:F3}", lr_l_Data);
		ReadTCData(s_StickDataShared.SDS_NbOfFwBwSharpen, i_l_Data);
		lblNbOfFwBwSharpenValue->Text = String::Format("{0:D}", i_l_Data);
		ReadTCData(s_StickDataShared.SDS_NbOfFwBwBeforeTapeMove, i_l_Data);
		lblNbOfFwBwBeforeTapeMoveValue->Text = String::Format("{0:D}", i_l_Data);
		ReadTCData(s_StickDataShared.SDS_SharpenHeight, lr_l_Data);
		lblSharpenHeightValue->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCData(s_StickDataShared.SDS_SharpenSpeed, lr_l_Data);
		lblSharpenSpeedValue->Text = String::Format("{0:F0}", lr_l_Data);
		ReadTCData(s_StickDataShared.SDS_MCRSharpenSpeed, i_l_Data);
		lblSpindleSharpenSpeedValue->Text = String::Format("{0:D}", i_l_Data);
		ReadTCData(s_StickDataShared.SDS_MinHoldLength, lr_l_Data);
		lblMinHoldLengthValue->Text = String::Format("{0:F0}", lr_l_Data);
		ReadTCData(s_StickDataShared.SDS_WeightTolerance, i_l_Data);
		lblWeightToleranceValue->Text = String::Format("{0:D}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_SpindleSpeedSetpoint[0], i_l_Data);
		lblLeftSpindleManualSpeedValue->Text = String::Format("{0:D}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_SpindleSpeedSetpoint[1], i_l_Data);
		lblRightSpindleManualSpeedValue->Text = String::Format("{0:D}", i_l_Data);
		ReadTCData(as_StickDataMMI[0].SD_MCRRation, lr_l_Data);
		lblLeftSpindleRatio->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCData(as_StickDataMMI[1].SD_MCRRation, lr_l_Data);
		lblRightSpindleRatio->Text = String::Format("{0:F2}", lr_l_Data);
		ReadTCData(as_StickDataMMI[0].SD_CompenseWeight, i_l_Data);
		lblLeftCompenseWeight->Text = String::Format("{0:D}", i_l_Data);
		ReadTCData(as_StickDataMMI[1].SD_CompenseWeight, i_l_Data);
		lblRightCompenseWeight->Text = String::Format("{0:D}", i_l_Data);

		TUtilities::UpdateMonostableButton(GetTCManData(s_PearlingManual.MP_RAZMotorUseTime[0]),btnRAZLeftMotorUseTime);
		TUtilities::UpdateMonostableButton(GetTCManData(s_PearlingManual.MP_RAZMotorUseTime[1]),btnRAZRightMotorUseTime);
		TUtilities::UpdateMonostableButton(GetTCManData(s_PearlingManual.MP_RAZSpindleUseTime[0]), btnRAZLeftSpindleUseTime);
		TUtilities::UpdateMonostableButton(GetTCManData(s_PearlingManual.MP_RAZSpindleUseTime[1]), btnRAZRightSpindleUseTime);
		TUtilities::UpdateMonostableButton(GetTCManData(s_PearlingManual.MP_Safe), btnSafe);
		
		ReadTCManData(s_PearlingManual.MP_MotorSpeed[0],i_l_Data);
		tbLeftMotorSpeed->Text = String::Format("{0:D}",i_l_Data);
		ReadTCManData(s_PearlingManual.MP_MotorSpeed[1],i_l_Data);
		tbRightMotorSpeed->Text = String::Format("{0:D}",i_l_Data);
		ReadTCManData(s_PearlingManual.MP_MotorCurrent[0],r_l_Data);
		tbLeftMotorCurrent->Text = String::Format("{0:F1}",r_l_Data);
		ReadTCManData(s_PearlingManual.MP_MotorCurrent[1],r_l_Data);
		tbRightMotorCurrent->Text = String::Format("{0:F1}",r_l_Data);
		ReadTCManData(s_PearlingManual.MP_MotorUseTime[0],d_l_Data);
		tbLeftMotorUseTime->Text = String::Format("{0:D}",d_l_Data);
		ReadTCManData(s_PearlingManual.MP_MotorUseTime[1],d_l_Data);
		tbRightMotorUseTime->Text = String::Format("{0:D}",d_l_Data);
		ReadTCManData(s_PearlingManual.MP_SpindleUseTime[0], d_l_Data);
		tbLeftSpindleUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCManData(s_PearlingManual.MP_SpindleUseTime[1], d_l_Data);
		tbRightSpindleUseTime->Text = String::Format("{0:D}", d_l_Data);
		ReadTCManData(s_PearlingManual.MP_DistanceSensor[0], i_l_Data);
		tbLeftHeightSensor->Text = String::Format("{0:D}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_DistanceSensor[1], i_l_Data);
		tbRightHeightSensor->Text = String::Format("{0:D}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_WeightSensor, i_l_Data);
		tbWeightSensor->Text = String::Format("{0:D}", i_l_Data);
		ReadTCManData(s_PearlingManual.MP_PearlsCounter[0], d_l_Data);
		tbLeftSpindlePearlsCounter->Text = String::Format("{0:D}", d_l_Data);
		ReadTCManData(s_PearlingManual.MP_PearlsCounter[1], d_l_Data);
		tbRightSpindlePearlsCounter->Text = String::Format("{0:D}", d_l_Data);

		// Update weight table if needed
		ReadTCManData(s_PearlingManual.MP_WeightTableLeftValid,b_l_Data);
		if (b_l_Data != 0)
		{
			bool ForceReload = false;
			if (m_CalibrationLeftData == nullptr)
			{
				m_CalibrationLeftData = gcnew array<TC_LREAL>(26);
				ForceReload = true;
			}		
			TC_LREAL lr_l_WeightStep;
			TC_LREAL lr_l_Ratiog2mm;
			ReadTCManData(s_PearlingManual.MP_WeightStepOnZ,lr_l_WeightStep);
			ReadTCManData(s_PearlingManual.MP_Ratiog2mm[0], lr_l_Ratiog2mm);

			
			for (int i=0;i<26;i++)
			{
				ReadTCManData(s_PearlingManual.MP_WeightTableLeft[i],lr_l_Data);
				if ((m_CalibrationLeftData[i] != lr_l_Data))
				{
					m_CalibrationLeftData[i] = lr_l_Data;
					ForceReload = true;
				}
			}
			if (ForceReload)
			{
				dgvWeightTableLeft->Rows->Clear();
				chrLeft->Series[0]->Points->Clear();
				chrLeft->Series[1]->Points->Clear();
				for (int i = 0; i < 26; i++)
				{
					double dWeight = i*lr_l_WeightStep - 0.1;
					dgvWeightTableLeft->Rows->Add(dWeight, m_CalibrationLeftData[i]);
					chrLeft->Series[0]->Points->AddXY(dWeight, m_CalibrationLeftData[i]);
					chrLeft->Series[1]->Points->AddXY(dWeight, dWeight > 0 ? dWeight * (1.0 / lr_l_Ratiog2mm) : 0);
				}
			}
		}
		else
		{
			dgvWeightTableLeft->Rows->Clear();
			chrLeft->Series[0]->Points->Clear();
			chrLeft->Series[1]->Points->Clear();
		}
		ReadTCManData(s_PearlingManual.MP_WeightTableRightValid, b_l_Data);
		if (b_l_Data != 0)
		{
			bool ForceReload = false;
			if (m_CalibrationRightData == nullptr)
			{
				m_CalibrationRightData = gcnew array<TC_LREAL>(26);
				ForceReload = true;
			}
			TC_LREAL lr_l_WeightStep;
			TC_LREAL lr_l_Ratiog2mm;
			ReadTCManData(s_PearlingManual.MP_WeightStepOnZ, lr_l_WeightStep);
			ReadTCManData(s_PearlingManual.MP_Ratiog2mm[1], lr_l_Ratiog2mm);
			for (int i = 0; i<26; i++)
			{
				ReadTCManData(s_PearlingManual.MP_WeightTableRight[i], lr_l_Data);
				if ((m_CalibrationRightData[i] != lr_l_Data))
				{
					m_CalibrationRightData[i] = lr_l_Data;
					ForceReload = true;
				}
			}
			if (ForceReload)
			{
				dgvWeightTableRight->Rows->Clear();
				chrRight->Series[0]->Points->Clear();
				chrRight->Series[1]->Points->Clear();
				for (int i = 0; i < 26; i++)
				{
					double dWeight = i*lr_l_WeightStep - 0.1;
					dgvWeightTableRight->Rows->Add(dWeight, m_CalibrationRightData[i]);
					chrRight->Series[0]->Points->AddXY(dWeight, m_CalibrationRightData[i]);
					chrRight->Series[1]->Points->AddXY(dWeight, dWeight > 0 ? dWeight * (1.0/lr_l_Ratiog2mm) : 0);
				}
			}
		}
		else
		{
			dgvWeightTableRight->Rows->Clear();
			chrRight->Series[0]->Points->Clear();
			chrRight->Series[1]->Points->Clear();
		}

	}
}

void PearlingManualScreen::SetUI(E_Axis eAxis)
{
	switch (eAxis)
	{
	case E_Axis::Z1:
		TUtilities::SetVisible(gbZ1axis, true);
		TUtilities::SetVisible(gbZ2axis, false);
		break;
	case E_Axis::Z2:
		TUtilities::SetVisible(gbZ1axis, false);
		TUtilities::SetVisible(gbZ2axis, true);
		break;
	case E_Axis::All:
		TUtilities::SetVisible(gbZ1axis, true);
		TUtilities::SetVisible(gbZ2axis, true);
		break;
	}
}

void PearlingManualScreen::OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e)
{
	TUtilities::SetVisible(gbLeftSpindle->Controls);
	TUtilities::SetVisible(gbRightSpindle->Controls);
	TUtilities::SetVisible(tabPageAxes->Controls);
	TUtilities::SetVisible(tabPageStick->Controls);
	TUtilities::SetVisible(tabPageRecipe->Controls);
	TUtilities::SetVisible(tabPageSharpen->Controls);
	TUtilities::SetVisible(tabPagePearling->Controls);
	TUtilities::SetVisible(tabPageCalibration->Controls);
}

