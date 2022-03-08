#include "NewOrder.h"

using namespace Projet1;

void NewOrder::UpdateUI(void)
{
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

void NewOrder::ClearUI(void)
{
	// Clear data
	tbOrder->Text ="";
	lblPart->Text = "";
	tbQuantity->Text = "";
	tbQuantity->Text = "";
	btnValidate->Enabled = true;
	tbConfiguration->Text = "";


	lblLeftStick->Text = FormatStick(nullptr);
	lblRightStick->Text = FormatStick(nullptr);
	lblLeftDiameter->Text = FormatDiameter(nullptr);
	lblRightDiameter->Text = FormatDiameter(nullptr);
	lblTopLeftWeight->Text = FormatWeight(nullptr);
	lblBottomLeftWeight->Text = FormatWeight(nullptr);
	lblTopRightWeight->Text = FormatWeight(nullptr);
	lblBottomRightWeight->Text = FormatWeight(nullptr);
	SetImage(pbSus, nullptr);
	SetImage(pbSous, nullptr);

	// and rightcheckboxes
	for (int i = 0; i < clsCheckList->Items->Count; i++)
	{
		clsCheckList->SetItemChecked(i, false);
	}
	btnValidate->Enabled = false;
}

void NewOrder::LoadConfiguration(String^ pS_x_FileName)
{
	char ac_l_String[255];
	String^ pS_l_Delimiter = ";";
	array<Char>^ pac_l_Delimiter = pS_l_Delimiter->ToCharArray();
	array<String^>^ paS_l_Splitdata;
	String^ pS_l_CurrentLine = gcnew String("");
	int i_l_Head = 0;
	array<String^>^ apS_l_StickNames = gcnew array<String^>(2);
	array<String^>^ apS_l_ImageData = gcnew array<String^>(2);
	array<String^>^ apS_l_StickDiameter = gcnew array<String^>(2);
	array<String^, 2>^ apS_l_StickWeight = gcnew array<String^, 2>(2, 2);
	array<String^, 2>^ apS_l_StickDispersion = gcnew array<String^, 2>(2, 2);
	bool b_l_FirstLine = true;
	struct CONFIG_DATA s_l_ConfigData;
	int i_l_Side = 0;
	unsigned int n_l_NbOfPearl = 0;

	memset(&s_l_ConfigData, 0, sizeof(s_l_ConfigData));

		// Update information
		TUtilities::StringToCharArray(pS_x_FileName, ac_l_String);
		// Scan file to retrieve information
		try
		{
			if (File::Exists(pS_x_FileName))
			{
				StreamReader^ pT_l_Reader = gcnew StreamReader(pS_x_FileName, System::Text::Encoding::Default);
				try
				{
					while (pT_l_Reader->Peek() >= 0)
					{
						// Split line
						pS_l_CurrentLine = pT_l_Reader->ReadLine();
						if (b_l_FirstLine)
						{
							pS_l_CurrentLine = TUtilities::pS_DecryptBaseKey(pS_l_CurrentLine);
							b_l_FirstLine = false;
						}
						else
						{
							pS_l_CurrentLine = TUtilities::pS_Decrypt(pS_l_CurrentLine);
							paS_l_Splitdata = pS_l_CurrentLine->Split(pac_l_Delimiter);
							if ("HEADER" == paS_l_Splitdata[0]) {}
							else if ("END_OF_HEADER" == paS_l_Splitdata[0]) {}
							else if ("IMAGE_SUS" == paS_l_Splitdata[0]) {}
							else if ("IMAGE_SOUS" == paS_l_Splitdata[0]) {}
							else if ("IMAGE_SUS_DATA" == paS_l_Splitdata[0])
							{
								apS_l_ImageData[0] = paS_l_Splitdata[1];
							}
							else if ("IMAGE_SOUS_DATA" == paS_l_Splitdata[0])
							{
								apS_l_ImageData[1] = paS_l_Splitdata[1];
							}
							else if ("START_OF_PROCESS" == paS_l_Splitdata[0]) {}
							else if ("END_OF_PROCESS" == paS_l_Splitdata[0]) {}
							else if ("PROD_PARALLELE" == paS_l_Splitdata[0])
							{
								s_l_ConfigData.CD_ParallelProd = true;
							}
							else if ("REFERENCE" == paS_l_Splitdata[0])
							{
								TUtilities::StringToCharArray(paS_l_Splitdata[1], ac_l_String);
								ac_l_String[8] = 0;	// DLA force max part name size
								WriteTCData(ac_PartName, (TC_CHAR*)ac_l_String);
								lblPart->Text = paS_l_Splitdata[1];
							}
							else if ("APPUI" == paS_l_Splitdata[0])
							{
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_Weight = Convert::ToInt16(paS_l_Splitdata[1]);
								apS_l_StickWeight[i_l_Head, i_l_Side] = gcnew String(paS_l_Splitdata[1]);
							}
							else if ("DISPERSIONZ" == paS_l_Splitdata[0])
							{
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_DispersionZ = Convert::ToInt16(paS_l_Splitdata[1]);
								apS_l_StickDispersion[i_l_Head, i_l_Side] = gcnew String(paS_l_Splitdata[1]);
							}
							else if ("DISPERSIONXY" == paS_l_Splitdata[0])
							{
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_DispersionXY = Convert::ToInt16(paS_l_Splitdata[1]);
							}
							else if ("BATONNET" == paS_l_Splitdata[0])
								apS_l_StickNames[i_l_Head] = gcnew String(paS_l_Splitdata[1]);
							else if ("PERLAGE" == paS_l_Splitdata[0])
								i_l_Head = (("DROITE" == paS_l_Splitdata[1]) ? 1 : 0);
							else if ("DIAMETRE" == paS_l_Splitdata[0])
							{
								s_l_ConfigData.CD_StickData[i_l_Head].SD_Diameter = Convert::ToDouble(paS_l_Splitdata[1]);
								apS_l_StickDiameter[i_l_Head] = gcnew String(paS_l_Splitdata[1]);
							}
							else if ("FACE" == paS_l_Splitdata[0])
							{
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_NbOfPearls = (TC_UINT)n_l_NbOfPearl;
								i_l_Side = ("SOUS" == paS_l_Splitdata[1]) ? 1 : 0;
								n_l_NbOfPearl = 0;
							}
							else if ("LONGUEUR_SORTIE" == paS_l_Splitdata[0])
								s_l_ConfigData.CD_StickData[i_l_Head].SD_OutLength = Convert::ToDouble(paS_l_Splitdata[1]);
							else if ("LONGUEUR_TOTALE" == paS_l_Splitdata[0])
								s_l_ConfigData.CD_StickData[i_l_Head].SD_TotalLength = Convert::ToDouble(paS_l_Splitdata[1]);
							else if ("FREQUENCE_AFFUTAGE" == paS_l_Splitdata[0])
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_SharpenFreq = Convert::ToInt16(paS_l_Splitdata[1]);
							else if ("VITESSE BROCHE" == paS_l_Splitdata[0])
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_MCRSpeed = Convert::ToInt16(paS_l_Splitdata[1]);
							else if ("TEMPS PERLAGE" == paS_l_Splitdata[0])
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingTime = Convert::ToInt16(paS_l_Splitdata[1]);
							else if ("BARILLET" == paS_l_Splitdata[0])
								s_l_ConfigData.CD_StickData[i_l_Head].SD_BarrelPos = Convert::ToInt16(paS_l_Splitdata[1]);
							else if ("SECURITE" == paS_l_Splitdata[0])
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_SecurityZ = Convert::ToDouble(paS_l_Splitdata[1]);
							else
							{
								// Manage pearl positions
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_Area = Convert::ToInt16(paS_l_Splitdata[0]);
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_X = Convert::ToDouble(paS_l_Splitdata[1]);
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_Y = Convert::ToDouble(paS_l_Splitdata[2]);
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_Z = Convert::ToDouble(paS_l_Splitdata[3]);
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_Rate = Convert::ToDouble(paS_l_Splitdata[4]);
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_NeedXYDispersion = ("1" == paS_l_Splitdata[5] ? 1 : 0);
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_ForceSharpen = ("1" == paS_l_Splitdata[6] ? 1 : 0);
								s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_Disable = ("1" == paS_l_Splitdata[7] ? 1 : 0);
										if (paS_l_Splitdata->Length > 8)
											s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_PearlingData[n_l_NbOfPearl].PT_MoveToSafe = ("1" == paS_l_Splitdata[8] ? 1 : 0);
								n_l_NbOfPearl++;
							}
						}
					}
				}
				finally
				{
					delete pT_l_Reader;

					ProductionOrder::SetReference(lblPart->Text);

					s_l_ConfigData.CD_PearlingData[i_l_Side].PD_Head[i_l_Head].PDH_NbOfPearls = (TC_UINT)n_l_NbOfPearl;
					// In parallel prod use left data also for right
					if (s_l_ConfigData.CD_ParallelProd)
					{
						s_l_ConfigData.CD_StickData[SI_RIGHT] = s_l_ConfigData.CD_StickData[SI_LEFT];
						apS_l_StickWeight[SI_RIGHT, 0] = apS_l_StickWeight[SI_LEFT, 0];
						apS_l_StickDispersion[SI_RIGHT, 0] = apS_l_StickDispersion[SI_LEFT, 0];
						apS_l_StickNames[SI_RIGHT] = apS_l_StickNames[SI_LEFT];
						apS_l_StickDiameter[SI_RIGHT] = apS_l_StickDiameter[SI_LEFT];
						s_l_ConfigData.CD_PearlingData[0].PD_Head[SI_RIGHT] = s_l_ConfigData.CD_PearlingData[0].PD_Head[SI_LEFT];
					}
					// Check if pearling on top and bottom

					lblLeftStick->Text = FormatStick(apS_l_StickNames[0]);
					lblRightStick->Text = FormatStick(apS_l_StickNames[1]);
					lblLeftDiameter->Text = FormatDiameter(apS_l_StickDiameter[0]);
					lblRightDiameter->Text = FormatDiameter(apS_l_StickDiameter[1]);
					lblTopLeftWeight->Text = FormatWeight(&s_l_ConfigData.CD_PearlingData[0].PD_Head[0]);
					lblBottomLeftWeight->Text = FormatWeight(&s_l_ConfigData.CD_PearlingData[1].PD_Head[0]);
					lblTopRightWeight->Text = FormatWeight(&s_l_ConfigData.CD_PearlingData[0].PD_Head[1]);
					lblBottomRightWeight->Text = FormatWeight(&s_l_ConfigData.CD_PearlingData[1].PD_Head[1]);
					tbConfiguration->Text = pS_x_FileName;

					ProductionOrder::SetPartImage(TransformImage(pbSus, apS_l_ImageData[0]), 0);
					ProductionOrder::SetPartImage(TransformImage(pbSus, apS_l_ImageData[1]), 1);
					SetImage(pbSus, ProductionOrder::GetPartImage(0));
					SetImage(pbSous, ProductionOrder::GetPartImage(1));

					// Write part data
					double ad_l_Point[2];

					ProductionOrder::GetPlateData(&s_l_ConfigData.CD_PlateData);
					s_l_ConfigData.CD_PartData.PRD_PartAndLayeringHeight = ProductionOrder::d_GetPartAndLayeringHeight();
					s_l_ConfigData.CD_PartData.PRD_PartAndHeadHeight = ProductionOrder::d_GetPartAndHeadHeight();
					s_l_ConfigData.CD_PartData.PRD_LayeringAndPartAndHeadHeight = ProductionOrder::d_GetLayeringAndPartAndHeadHeight();
					s_l_ConfigData.CD_PartData.PRD_HeadSusPartHeadSousHeight = ProductionOrder::d_GetHeadSusPartHeadSousHeight();
					s_l_ConfigData.CD_PartData.PRD_PlateZOffsetForLift = ProductionOrder::d_GetPlateZOffsetForLift();
					ProductionOrder::GetPartOffset(0, ad_l_Point);
					s_l_ConfigData.CD_PartData.PRD_PartOffsetLayering[0].PXY_X = ad_l_Point[0];
					s_l_ConfigData.CD_PartData.PRD_PartOffsetLayering[0].PXY_Y = ad_l_Point[1];
					ProductionOrder::GetPartOffset(1, ad_l_Point);
					s_l_ConfigData.CD_PartData.PRD_PartOffsetLayering[1].PXY_X = ad_l_Point[0];
					s_l_ConfigData.CD_PartData.PRD_PartOffsetLayering[1].PXY_Y = ad_l_Point[1];
					ProductionOrder::GetPartSensorOffset(0, ad_l_Point);
					s_l_ConfigData.CD_PartData.PRD_SensorOffset[0].PXY_X = ad_l_Point[0];
					s_l_ConfigData.CD_PartData.PRD_SensorOffset[0].PXY_Y = ad_l_Point[1];
					ProductionOrder::GetPartSensorOffset(1, ad_l_Point);
					s_l_ConfigData.CD_PartData.PRD_SensorOffset[1].PXY_X = ad_l_Point[0];
					s_l_ConfigData.CD_PartData.PRD_SensorOffset[1].PXY_Y = ad_l_Point[1];
					ProductionOrder::GetHeadOffset(ad_l_Point);
					s_l_ConfigData.CD_PartData.PRD_HeadOffset.PXY_X = ad_l_Point[0];
					s_l_ConfigData.CD_PartData.PRD_HeadOffset.PXY_Y = ad_l_Point[1];
					s_l_ConfigData.CD_PartData.PRD_DropModeTable = (TC_INT)ProductionOrder::i_GetDropModeTable();
					s_l_ConfigData.CD_PartData.PRD_DropModeTurnOver = (TC_INT)ProductionOrder::i_GetDropModeTurnOver();
					s_l_ConfigData.CD_PartData.PRD_TakeModeLift = (TC_INT)ProductionOrder::i_GetTakeModeLift();
					s_l_ConfigData.CD_PartData.PRD_DropInBox = ProductionOrder::b_GetDropInBox();

					s_l_ConfigData.CD_PartData.PRD_PartOffsetThetaLiftDrop = ProductionOrder::GetPartOffsetThetaLiftDrop();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetXLiftDrop = ProductionOrder::GetPartOffsetXLiftDrop();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetYLiftDrop = ProductionOrder::GetPartOffsetYLiftDrop();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetZLayeringDrop = ProductionOrder::GetPartOffsetZLayeringDrop();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetZLayeringTake = ProductionOrder::GetPartOffsetZLayeringTake();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetZLiftDrop = ProductionOrder::GetPartOffsetZLiftDrop();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetZLiftTake = ProductionOrder::GetPartOffsetZLiftTake();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetZLiftBadTake = ProductionOrder::GetPartOffsetZLiftBadTake();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetZTurnOverDrop = ProductionOrder::GetPartOffsetZTurnOverDrop();
					s_l_ConfigData.CD_PartData.PRD_PartOffsetZCleaning = ProductionOrder::GetPartOffsetZCleaning();
					TUtilities::StringToCharArray(ProductionOrder::pS_GetVisionReferenceFileName(), s_l_ConfigData.CD_VisionRefFileName);

					WriteConfigData(&s_l_ConfigData);
					pT_RejectScreen->SetPlateData(&s_l_ConfigData.CD_PlateData);
				}
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Error on configuration file reading :" + pS_x_FileName + " with exception : " + e->Message, "TPearlingData::LoadFromFile");
		}

}
