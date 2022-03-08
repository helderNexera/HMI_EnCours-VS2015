#include "RTPearlingScreen.h"

#define C_MM_TO_PIX 1000

#define C_CORRECTION_COLOR Color::MediumOrchid

using namespace Projet1;
using namespace System::Globalization;
using namespace System::Windows::Forms::DataVisualization::Charting;

void RTPearlingScreen::UpdateUI(void)
{
	int i,j;
	TC_PEARL_DATA as_l_PearlData[2];
	array<Chart^, 2>^ apT_l_Chart;
	String^ pS_l_CompleteLine = gcnew String("");
	String^ pS_l_FileName = gcnew String("");
	TC_BOOL ab_l_NewPart[2];
	TC_BOOL ab_l_NewPearl[2];
	int		ai_l_Side[2];
	array<Label^,2>^ apT_l_LblPearlNb;
	array<Label^,2>^ apT_l_LblCorrection;

	btnTLExport->Enabled = !ab_Export[0,0];
	btnBLExport->Enabled = !ab_Export[0,1];
	btnTRExport->Enabled = !ab_Export[1,0];
	btnBRExport->Enabled = !ab_Export[1,1];

	CleanUpExport();

	apT_l_LblPearlNb = gcnew array<Label^,2>(2,2);
	apT_l_LblPearlNb[0,0] = lblTLPearlNb;
	apT_l_LblPearlNb[0,1] = lblBLPearlNb;
	apT_l_LblPearlNb[1,0] = lblTRPearlNb;
	apT_l_LblPearlNb[1,1] = lblBRPearlNb;

	apT_l_LblCorrection = gcnew array<Label^,2>(2,2);
	apT_l_LblCorrection[0,0] = lblTLCorrection_um;
	apT_l_LblCorrection[0,1] = lblBLCorrection_um;
	apT_l_LblCorrection[1,0] = lblTRCorrection_um;
	apT_l_LblCorrection[1,1] = lblBRCorrection_um;

	apT_l_Chart = gcnew array<Chart^, 2>(2, 2);
	apT_l_Chart[0, 0] = chrTLGraph;
	apT_l_Chart[0, 1] = chrBLGraph;
	apT_l_Chart[1, 0] = chrTRGraph;
	apT_l_Chart[1, 1] = chrBRGraph;


	for (i=0;i<2;i++)
	{
		ReadTCData(as_PearlsData[i], as_l_PearlData[i]);
		ab_l_NewPart[i] = as_l_PearlData[i].PD_NewPart;
		ab_l_NewPearl[i] = as_l_PearlData[i].PD_NewPearl;
		ai_l_Side[i] = as_l_PearlData[i].PD_PearlingTop ? 0 : 1;
		if (ab_l_NewPart[i]) 
			ClearTCData(as_PearlsData[i].PD_NewPart);
		if (ab_l_NewPearl[i]) 
			ClearTCData(as_PearlsData[i].PD_NewPearl);
	}

	// Store pearls data
	for (i=0;i<2;i++)
	{
		for (j=0;j<2;j++)
		{
			if ((ab_l_NewPart[i]) && (ai_l_Side[i] == j))
			{
				ai_d_MaxValue[i, j] = 0;

				apT_l_Chart[i,j]->Series[0]->Points->Clear();
				apT_l_LblPearlNb[i, j]->Text = "Perle n° : ";
				apT_l_LblCorrection[i, j]->Text = "Compensation [um] : ";

				// Log data if needed
				if (ab_Export[i,j])
				{
					if (ab_Exporting[i,j])
					{
						//ab_Export[i,j] = false;
						ab_Exporting[i,j] = false;
						if (apT_ExportFile[i,j])
							delete (IDisposable^) apT_ExportFile[i,j];
					}
					if ((!ab_Exporting[i,j]) && (ab_Export[i, j]))
					{
						ab_Exporting[i,j] = true;
						// Close old file if needed
						// Open new export file
						DateTime T_l_TimeNow = DateTime::Now;
						pS_l_FileName = C_APP_EXPORT_PATH;
						pS_l_FileName += apT_FaceBaseName[i,j];
						pS_l_FileName += T_l_TimeNow.ToString("_dd_MM_yyyy - HH_mm_ss") + ".csv";
						apT_ExportFile[i,j] = File::AppendText(pS_l_FileName);
						apT_ExportFile[i, j]->AutoFlush = true;
						pS_l_CompleteLine = "N° perle;Taux;Pos. calculée;Compensation;Pos. capteur palpage;Pos. capteur perle;Delta Force Appui;VacuumFlow";
						apT_ExportFile[i,j]->WriteLine(pS_l_CompleteLine);
						apT_ExportFile[i,j]->Flush();
					}
				}
			}
			if (ab_l_NewPearl[i] && (ai_l_Side[i] == j))
			{
				double dCorrectionMCR = as_l_PearlData[i].PD_CorrectionMCR * 1000.0;

				if (ai_d_MaxValue[i, j] < Math::Abs(dCorrectionMCR))
					ai_d_MaxValue[i, j] = (int)Math::Abs(dCorrectionMCR);
				apT_l_LblPearlNb[i, j]->Text = "Perle n° : " + as_l_PearlData[i].PD_PearlNb.ToString();
				apT_l_LblCorrection[i, j]->Text = "Compensation [um] : " + dCorrectionMCR.ToString("F0");
				apT_l_Chart[i, j]->Series[0]->Points->AddXY(as_l_PearlData[i].PD_PearlNb, dCorrectionMCR);

				//Change scale if needed
				double dMaxScale = 100;
				while (dMaxScale < ai_d_MaxValue[i, j] + 1)
				{
					dMaxScale *= 2;
				}
				if (apT_l_Chart[i, j]->ChartAreas[0]->AxisY->Maximum != dMaxScale)
				{
					apT_l_Chart[i, j]->ChartAreas[0]->AxisY->Maximum = dMaxScale;
					apT_l_Chart[i, j]->ChartAreas[0]->AxisY->Minimum = -dMaxScale;
					apT_l_Chart[i, j]->ChartAreas[0]->AxisY->Interval = dMaxScale / 2;
				}

				// log data if needed : PearlNb,Rate,Zconsigne,Correction,DeltaI,Zmeasured
				if (ab_Exporting[i,j])
				{
					pS_l_CompleteLine = String::Format("{0:D};{1:F3};{2:F3};{3:F3};{4:F3};{5:F3};{6:F3};{7:D}", as_l_PearlData[i].PD_PearlNb, as_l_PearlData[i].PD_Rate,
							as_l_PearlData[i].PD_PearlingCalcPos,as_l_PearlData[i].PD_CorrectionMCR,as_l_PearlData[i].PD_SensorProbePos,as_l_PearlData[i].PD_SensorPearlPos, as_l_PearlData[i].PD_DeltaWeight, as_l_PearlData[i].PD_VacuumFlow);
					apT_ExportFile[i,j]->WriteLine(pS_l_CompleteLine);
					apT_ExportFile[i,j]->Flush();
				}
				ab_l_NewPearl[i] = false;
			}
		}
	}

	if (this->Visible)
	{
		bool b_l_ActiveAlarm;

		lblLastAlarm->Text = AlarmScreen::pS_GetLastAlarm(&b_l_ActiveAlarm);
		if (b_l_ActiveAlarm)
			lblLastAlarm->ForeColor = Color::Red;
		else
			lblLastAlarm->ForeColor = Color::Black;
	}
}

void RTPearlingScreen::CleanUpExport()
{
	if (!b_NeedCleanup)
	{
		if ((DateTime::Now.Date - t_LastCleanUp).Days > 0)
		{
			b_NeedCleanup = true;
		}
	}
	if (b_NeedCleanup)
	{
		DateTime Now = DateTime::Now.Date;
		t_LastCleanUp = Now;
		b_NeedCleanup = false;
		String^ sFolder = C_APP_EXPORT_PATH;
		sFolder = sFolder->Remove(sFolder->Length - 1);

		for each (String^ sFile in Directory::GetFiles(sFolder))
		{
			try
			{
				String^ sDate = sFile->Substring(sFile->Length - 25, 10);
				DateTime tDate = DateTime::ParseExact(sDate, "dd_MM_yyyy", CultureInfo::InvariantCulture, DateTimeStyles::None);
				if ((Now - tDate).Days > 30)
				{
					File::Delete(sFile);
				}
			}
			catch (...)
			{

			}
		}
	}

}

