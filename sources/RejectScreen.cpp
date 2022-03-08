#include "RejectScreen.h"

using namespace Projet1;
using namespace System::Collections::Generic;

void RejectScreen::UpdateUI(void)
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

void RejectScreen::OnUpdateRejectPart(int iPos)
{
	m_oRejectedParts = TJobLogger::GetRejectedParts(m_sSelectedPlate);
	UpdatePlateList();
	m_iSelectedPlatePos = iPos;
	DrawPlate();
}

void RejectScreen::UpdatePlateList()
{
	int i = 0;
	int iSelectedPlate = -1;
	lbPlateNb->Items->Clear();
	for each(KeyValuePair<String^, List<PartData^>^>^ kvp in m_oRejectedParts)
	{
		lbPlateNb->Items->Add(kvp->Key);
		if (kvp->Key == m_sSelectedPlate) iSelectedPlate = i;
		i++;
	}
	lbPlateNb->SelectedIndex = iSelectedPlate;
	bool bVisible = false;
	if (lbPlateNb->Items->Count > 1) bVisible = true;
	if ((lbPlateNb->Items->Count == 1) && (lbPlateNb->Items[0]->ToString() != "")) bVisible = true;
	if (bVisible)
	{
		pnlPlate->Visible = true;
		pnlPlate->Left = m_iPosPlate;
		pnlInformation->Left = m_iPosInformation;
	}
	else
	{
		pnlPlate->Visible = false;
		pnlInformation->Left = (this->Width - pnlInformation->Width) / 2;
	}
}


void RejectScreen::SetPlateData(TC_PLATE_DATA* ps_x_PlateData)
{
	d_PosDiameter = 5;
	m_aPlatePosition = gcnew array<Position^>(ps_x_PlateData->PD_NbPartOnPlate);
	for (int i = 0; i < m_aPlatePosition->Length; i++)
	{
		m_aPlatePosition[i] = gcnew Position();
		m_aPlatePosition[i]->x = ps_x_PlateData->PD_PartOnPlate[i].PXY_X;
		m_aPlatePosition[i]->y = ps_x_PlateData->PD_PartOnPlate[i].PXY_Y;
	}
	if (m_aPlatePosition->Length >= 2)
	{
		d_PosDiameter = Math::Abs(m_aPlatePosition[0]->x - m_aPlatePosition[1]->x) - PixelToMm(2, m_dBaseResolution * d_ZoomRatio);
		if (d_PosDiameter < 5) d_PosDiameter = 5;
	}
	m_sSelectedPlate = "";
	m_iSelectedPlatePos = -1;
	DrawPlate();
}

void RejectScreen::DrawPlate()
{
	System::Diagnostics::Debug::Print("Draw Plate");

	Bitmap^ po_OutImage = gcnew Bitmap(pbPlate->Width, pbPlate->Height);
	Graphics^ pT_l_Graphics = Graphics::FromImage(po_OutImage);
	SolidBrush^ PosBrush = gcnew SolidBrush(Color::FromArgb(255, 255, 0, 0));
	double d_l_PosDiameterPx = MmToPixel(d_PosDiameter, m_dBaseResolution * d_ZoomRatio);

	List<PartData^>^ lsParts = nullptr;
	lsParts = m_oRejectedParts->ContainsKey(m_sSelectedPlate) ? m_oRejectedParts[m_sSelectedPlate] : nullptr;

	Dictionary<int, PartData^>^ oParts = gcnew Dictionary<int, PartData^>();
	if (lsParts != nullptr)
	{
		for each (PartData^ oPart in lsParts)
		{
			oParts->Add(oPart->iPlateOutPos, oPart);
		}
	}

	pT_l_Graphics->FillRectangle(Brushes::White, 0, 0, pbPlate->Width, pbPlate->Height);
	lblRejectReasonText->Text = "";
	lblSelectedPosition->Text = TUtilities::pS_LoadString(TextIndex::Position);
	for (int i = 0; i < m_aPlatePosition->Length; i++)
	{
		int i_l_Xpos = (int)MmToPixel(m_aPlatePosition[i]->x - d_PosDiameter / 2.0, m_dBaseResolution * d_ZoomRatio);
		int i_l_Ypos = (int)MmToPixel(m_aPlatePosition[i]->y - d_PosDiameter / 2.0, m_dBaseResolution * d_ZoomRatio);
		PartData^ oPart = nullptr;
		if (oParts->ContainsKey(i)) oPart = oParts[i];
		if (oPart == nullptr)
		{
			PosBrush->Color = Color::LightGray;
		}
		else if (oPart->bSample)
		{
			PosBrush->Color = Color::Lime;
		}
		else
		{
			PosBrush->Color = Color::Red;
		}
		if (i == m_iSelectedPlatePos)
		{
			lblSelectedPosition->Text = TUtilities::pS_LoadString(TextIndex::Position) + " " + (i + 1).ToString();
			PosBrush->Color = Color::FromArgb(255, 255 - PosBrush->Color.R, 255 - PosBrush->Color.G, 255 - PosBrush->Color.B);
			if (oPart != nullptr)
			{
				if (oPart->bSample)
					lblRejectReasonText->Text = "échantillon";
				else
					lblRejectReasonText->Text = String::Join(Environment::NewLine,oPart->RejectReason);
			}
		}
		pT_l_Graphics->FillEllipse(PosBrush, i_l_Xpos, i_l_Ypos, (int)d_l_PosDiameterPx, (int)d_l_PosDiameterPx);
		pT_l_Graphics->DrawEllipse(Pens::Black, i_l_Xpos, i_l_Ypos, (int)d_l_PosDiameterPx, (int)d_l_PosDiameterPx);
		StringFormat^ sFormat = gcnew StringFormat();
		sFormat->Alignment = StringAlignment::Center;
		sFormat->LineAlignment = StringAlignment::Center;
		float txtOffset = (float)(d_l_PosDiameterPx / 2.0);
		System::Drawing::Font^ sFont = gcnew System::Drawing::Font(L"Microsoft Sans Serif", (float)(d_l_PosDiameterPx / 3.0), System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel, static_cast<System::Byte>(0));
		pT_l_Graphics->DrawString((i+1).ToString(), sFont, Brushes::Black, (float)i_l_Xpos + txtOffset, (float)i_l_Ypos + txtOffset, sFormat);

	}
	pbPlate->BackgroundImage = po_OutImage;
	
}

double RejectScreen::PixelToMm(double dValue, double dResolution)
{
	return dValue / (dResolution / 25.4);
}

double RejectScreen::MmToPixel(double dValue, double dResolution)
{
	return (dResolution / 25.4) * dValue;
}

