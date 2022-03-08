#pragma once

#include "TTwincatInterface.h"
#include "MyMsgBox.h"
#include "global.h"
#include "TUtilities.h"
#include "AlarmScreen.h"
#include "TLogger.h"
#include "TJobLogger.h"

namespace Projet1 {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de LotScreen
	/// </summary>
	public ref class RejectScreen : public System::Windows::Forms::Form
	{
	public:
		RejectScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			m_oRejectedParts = gcnew Dictionary<String^, List<PartData^>^>();
			m_aPlatePosition = gcnew array<Position^>(0);
			m_sSelectedPlate = "";
			m_iSelectedPlatePos = -1;
			d_PosDiameter = 0;
			m_dBaseResolution = ((double)pbPlate->Width / m_dBaseSizeInMm) * 25.4;
			m_iPosPlate = pnlPlate->Left;
			m_iPosInformation = pnlInformation->Left;
			TJobLogger::UpdateRejectPart += gcnew EventUpdateRejectPart(this, &Projet1::RejectScreen::OnUpdateRejectPart);
		}
	// Our specific functions
	private:
		ref struct Position
		{
			double x;
			double y;
		};
		array<Position^>^ m_aPlatePosition;
		String^ m_sSelectedPlate;
		int m_iSelectedPlatePos;
		initonly int m_iPosInformation;
		initonly int m_iPosPlate;
		Dictionary<String^, List<PartData^>^>^ m_oRejectedParts;
		const double m_dBaseSizeInMm = 136;
		const double d_ZoomRatio = 1.0;
		initonly double m_dBaseResolution;
			 double d_PosDiameter;
		double PixelToMm(double dValue, double dResolution);
		double MmToPixel(double dValue, double dResolution);
		void OnUpdateRejectPart(int);
		void UpdatePlateList();
	public:
		void UpdateUI(void);
		void SetPlateData(TC_PLATE_DATA* ps_x_PlateData);
		void DrawPlate();

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~RejectScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	protected: 
	private: System::Windows::Forms::Label^  lblRejectReason;
	private: System::Windows::Forms::Label^  lblRejectReasonText;
	private: System::Windows::Forms::Label^  lblSelectedPosition;
	private: System::Windows::Forms::Label^  lblRejectPlate;
	private: System::Windows::Forms::Label^  lblInformations;
	private: System::Windows::Forms::Button^  btnClose;
	private: System::Windows::Forms::Label^  lblLastAlarm;
	private: System::Windows::Forms::ListBox^  lbPlateNb;
	private: MondemaComponents::BorderPanel^  pnlPlate;
	private: MondemaComponents::BorderPanel^  pnlInformation;
	private: MondemaComponents::RoundedBorderPanel^  roundedBorderPanel1;
	private: System::Windows::Forms::PictureBox^  pbPlate;
	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblRejectPlate = (gcnew System::Windows::Forms::Label());
			this->lblInformations = (gcnew System::Windows::Forms::Label());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->lblLastAlarm = (gcnew System::Windows::Forms::Label());
			this->lbPlateNb = (gcnew System::Windows::Forms::ListBox());
			this->pnlPlate = (gcnew MondemaComponents::BorderPanel());
			this->pnlInformation = (gcnew MondemaComponents::BorderPanel());
			this->lblSelectedPosition = (gcnew System::Windows::Forms::Label());
			this->lblRejectReasonText = (gcnew System::Windows::Forms::Label());
			this->lblRejectReason = (gcnew System::Windows::Forms::Label());
			this->pbPlate = (gcnew System::Windows::Forms::PictureBox());
			this->roundedBorderPanel1 = (gcnew MondemaComponents::RoundedBorderPanel());
			this->pnlPlate->SuspendLayout();
			this->pnlInformation->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPlate))->BeginInit();
			this->SuspendLayout();
			// 
			// lblRejectPlate
			// 
			this->lblRejectPlate->AutoEllipsis = true;
			this->lblRejectPlate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRejectPlate->Location = System::Drawing::Point(17, 8);
			this->lblRejectPlate->Name = L"lblRejectPlate";
			this->lblRejectPlate->Size = System::Drawing::Size(402, 60);
			this->lblRejectPlate->TabIndex = 2;
			this->lblRejectPlate->Text = L"Palette";
			this->lblRejectPlate->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblInformations
			// 
			this->lblInformations->AutoEllipsis = true;
			this->lblInformations->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblInformations->Location = System::Drawing::Point(17, 8);
			this->lblInformations->Name = L"lblInformations";
			this->lblInformations->Size = System::Drawing::Size(981, 60);
			this->lblInformations->TabIndex = 3;
			this->lblInformations->Text = L"Information";
			this->lblInformations->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnClose
			// 
			this->btnClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClose->Location = System::Drawing::Point(1660, 40);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(225, 66);
			this->btnClose->TabIndex = 5;
			this->btnClose->Text = L"Quitter";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &RejectScreen::btnClose_Click);
			// 
			// lblLastAlarm
			// 
			this->lblLastAlarm->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLastAlarm->ForeColor = System::Drawing::Color::Red;
			this->lblLastAlarm->Location = System::Drawing::Point(20, 1002);
			this->lblLastAlarm->Name = L"lblLastAlarm";
			this->lblLastAlarm->Size = System::Drawing::Size(1538, 68);
			this->lblLastAlarm->TabIndex = 26;
			this->lblLastAlarm->Text = L"...";
			this->lblLastAlarm->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lbPlateNb
			// 
			this->lbPlateNb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbPlateNb->FormattingEnabled = true;
			this->lbPlateNb->ItemHeight = 29;
			this->lbPlateNb->Location = System::Drawing::Point(23, 146);
			this->lbPlateNb->Name = L"lbPlateNb";
			this->lbPlateNb->ScrollAlwaysVisible = true;
			this->lbPlateNb->Size = System::Drawing::Size(396, 729);
			this->lbPlateNb->TabIndex = 27;
			this->lbPlateNb->SelectedIndexChanged += gcnew System::EventHandler(this, &RejectScreen::lbPlateNb_SelectedIndexChanged);
			// 
			// pnlPlate
			// 
			this->pnlPlate->BorderSize = 3;
			this->pnlPlate->Controls->Add(this->lbPlateNb);
			this->pnlPlate->Controls->Add(this->lblRejectPlate);
			this->pnlPlate->DisplayBorder = true;
			this->pnlPlate->Location = System::Drawing::Point(36, 30);
			this->pnlPlate->Name = L"pnlPlate";
			this->pnlPlate->Size = System::Drawing::Size(435, 924);
			this->pnlPlate->TabIndex = 40;
			// 
			// pnlInformation
			// 
			this->pnlInformation->BorderSize = 3;
			this->pnlInformation->Controls->Add(this->lblSelectedPosition);
			this->pnlInformation->Controls->Add(this->lblRejectReasonText);
			this->pnlInformation->Controls->Add(this->lblInformations);
			this->pnlInformation->Controls->Add(this->lblRejectReason);
			this->pnlInformation->Controls->Add(this->pbPlate);
			this->pnlInformation->DisplayBorder = true;
			this->pnlInformation->Location = System::Drawing::Point(500, 30);
			this->pnlInformation->Name = L"pnlInformation";
			this->pnlInformation->Size = System::Drawing::Size(1005, 924);
			this->pnlInformation->TabIndex = 41;
			// 
			// lblSelectedPosition
			// 
			this->lblSelectedPosition->AutoSize = true;
			this->lblSelectedPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblSelectedPosition->Location = System::Drawing::Point(539, 92);
			this->lblSelectedPosition->Name = L"lblSelectedPosition";
			this->lblSelectedPosition->Size = System::Drawing::Size(100, 29);
			this->lblSelectedPosition->TabIndex = 118;
			this->lblSelectedPosition->Text = L"Position";
			// 
			// lblRejectReasonText
			// 
			this->lblRejectReasonText->BackColor = System::Drawing::SystemColors::Control;
			this->lblRejectReasonText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblRejectReasonText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblRejectReasonText->Location = System::Drawing::Point(545, 183);
			this->lblRejectReasonText->Name = L"lblRejectReasonText";
			this->lblRejectReasonText->Size = System::Drawing::Size(429, 276);
			this->lblRejectReasonText->TabIndex = 117;
			this->lblRejectReasonText->Tag = L"";
			this->lblRejectReasonText->Text = L"-";
			// 
			// lblRejectReason
			// 
			this->lblRejectReason->AutoSize = true;
			this->lblRejectReason->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRejectReason->Location = System::Drawing::Point(539, 153);
			this->lblRejectReason->Name = L"lblRejectReason";
			this->lblRejectReason->Size = System::Drawing::Size(165, 29);
			this->lblRejectReason->TabIndex = 1;
			this->lblRejectReason->Text = L"RejectReason";
			// 
			// pbPlate
			// 
			this->pbPlate->Location = System::Drawing::Point(23, 92);
			this->pbPlate->Name = L"pbPlate";
			this->pbPlate->Size = System::Drawing::Size(479, 810);
			this->pbPlate->TabIndex = 0;
			this->pbPlate->TabStop = false;
			this->pbPlate->Click += gcnew System::EventHandler(this, &RejectScreen::pbPlate_Click);
			// 
			// roundedBorderPanel1
			// 
			this->roundedBorderPanel1->BorderCornerRadius = 18;
			this->roundedBorderPanel1->DisplayBorder = true;
			this->roundedBorderPanel1->Location = System::Drawing::Point(1, 995);
			this->roundedBorderPanel1->Name = L"roundedBorderPanel1";
			this->roundedBorderPanel1->Size = System::Drawing::Size(1578, 84);
			this->roundedBorderPanel1->TabIndex = 42;
			// 
			// RejectScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1920, 1080);
			this->Controls->Add(this->lblLastAlarm);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->pnlPlate);
			this->Controls->Add(this->pnlInformation);
			this->Controls->Add(this->roundedBorderPanel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"RejectScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LotScreen";
			this->VisibleChanged += gcnew System::EventHandler(this, &RejectScreen::RejectScreen_VisibleChanged);
			this->pnlPlate->ResumeLayout(false);
			this->pnlInformation->ResumeLayout(false);
			this->pnlInformation->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbPlate))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {
				this->Close();
		 }

private: System::Void RejectScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
		lblInformations->Text = TUtilities::pS_LoadString(TextIndex::Informations);
		lblRejectPlate->Text = TUtilities::pS_LoadString(TextIndex::Plate);
		lblRejectReason->Text = TUtilities::pS_LoadString(TextIndex::RejectReason);
		if (this->Visible)
		{
			System::Diagnostics::Debug::Print("Update Plate and parts");
			m_oRejectedParts = TJobLogger::GetRejectedParts(m_sSelectedPlate);
			m_iSelectedPlatePos = -1;
			UpdatePlateList();
			DrawPlate();
		}
	 }
private: System::Void lbPlateNb_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (lbPlateNb->SelectedIndex == -1)
		{
			m_sSelectedPlate = "";
		}
		else
		{
			m_sSelectedPlate = lbPlateNb->SelectedItem->ToString();
		}
		m_iSelectedPlatePos = -1;
		DrawPlate();
	}

	 
private: System::Void pbPlate_Click(System::Object^  sender, System::EventArgs^  e) {
	
	int X = pbPlate->PointToClient(Cursor->Position).X;
	int Y = pbPlate->PointToClient(Cursor->Position).Y;
	double dPosX = PixelToMm(X, m_dBaseResolution * d_ZoomRatio);
	double dPosY = PixelToMm(Y, m_dBaseResolution * d_ZoomRatio);
	System::Diagnostics::Debug::Print("X : " + dPosX.ToString("F2") + " Y : " + dPosY.ToString("F2"));

	m_iSelectedPlatePos = -1;
	for (int i = 0; i < m_aPlatePosition->Length; i++)
	{
		if ((Math::Pow((dPosX - m_aPlatePosition[i]->x), 2) + Math::Pow((dPosY - m_aPlatePosition[i]->y), 2)) < Math::Pow(d_PosDiameter / 2, 2))
		{
			m_iSelectedPlatePos = i;
		}
	}
	DrawPlate();
}
};
}
