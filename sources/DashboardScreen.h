#pragma once

#include "NewOrder.h"
#include "RejectScreen.h"
#include "RTPearlingScreen.h"
#include "TUtilities.h"
#include "Global.h"

namespace Projet1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de DashboardScreen
	/// </summary>
	public ref class DashboardScreen : public System::Windows::Forms::Form
	{
	public:
		DashboardScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::DashboardScreen::OnUserLevelChanged);
		}
	private: System::Windows::Forms::CheckBox^  btnPickPlace_OFF;
	public:
	private: System::Windows::Forms::CheckBox^  btnPickPlace_ON;
	private: System::Windows::Forms::Label^  lblPickPlace;
	private: System::Windows::Forms::Label^  lblModel;
	private: System::Windows::Forms::ComboBox^  cobModel;
	private: System::Windows::Forms::Button^  btnScanLift1;
	private: System::Windows::Forms::Button^  btnScanLift2;
	private: System::Windows::Forms::Button^  btnScanReject;
	private: System::Windows::Forms::GroupBox^  grbVision;
	private: System::Windows::Forms::Label^  lblMovePearling;
	private: System::Windows::Forms::Button^  btnMovePearling;
	private: System::Windows::Forms::Label^  lblMoveTable;
	private: System::Windows::Forms::Button^  btnMoveTable;
	private: System::Windows::Forms::Label^  lblMoveLiftLoader;
	private: System::Windows::Forms::Button^  btnMoveLiftLoader;
	private: System::Windows::Forms::Label^  lblRejectScanResult;
	private: System::Windows::Forms::Label^  lblLift2ScanResult;
	private: System::Windows::Forms::Label^  lblLift1ScanResult;


	private:
		bool b_ScreenReloaded;
	public: 
			 // Our specific functions
	public:
		void UpdateUI();
		void Reload(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~DashboardScreen()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
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
			this->btnPickPlace_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnPickPlace_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblPickPlace = (gcnew System::Windows::Forms::Label());
			this->lblModel = (gcnew System::Windows::Forms::Label());
			this->cobModel = (gcnew System::Windows::Forms::ComboBox());
			this->btnScanLift1 = (gcnew System::Windows::Forms::Button());
			this->btnScanLift2 = (gcnew System::Windows::Forms::Button());
			this->btnScanReject = (gcnew System::Windows::Forms::Button());
			this->grbVision = (gcnew System::Windows::Forms::GroupBox());
			this->lblMovePearling = (gcnew System::Windows::Forms::Label());
			this->btnMovePearling = (gcnew System::Windows::Forms::Button());
			this->lblMoveTable = (gcnew System::Windows::Forms::Label());
			this->btnMoveTable = (gcnew System::Windows::Forms::Button());
			this->lblMoveLiftLoader = (gcnew System::Windows::Forms::Label());
			this->btnMoveLiftLoader = (gcnew System::Windows::Forms::Button());
			this->lblLift1ScanResult = (gcnew System::Windows::Forms::Label());
			this->lblLift2ScanResult = (gcnew System::Windows::Forms::Label());
			this->lblRejectScanResult = (gcnew System::Windows::Forms::Label());
			this->grbVision->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnPickPlace_OFF
			// 
			this->btnPickPlace_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnPickPlace_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPickPlace_OFF->Location = System::Drawing::Point(1398, 18);
			this->btnPickPlace_OFF->Name = L"btnPickPlace_OFF";
			this->btnPickPlace_OFF->Size = System::Drawing::Size(90, 90);
			this->btnPickPlace_OFF->TabIndex = 117;
			this->btnPickPlace_OFF->Tag = L"2";
			this->btnPickPlace_OFF->Text = L"OFF";
			this->btnPickPlace_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnPickPlace_OFF->UseVisualStyleBackColor = true;
			this->btnPickPlace_OFF->Click += gcnew System::EventHandler(this, &DashboardScreen::btnPickPlace_OFF_Click);
			// 
			// btnPickPlace_ON
			// 
			this->btnPickPlace_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnPickPlace_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPickPlace_ON->Location = System::Drawing::Point(1299, 18);
			this->btnPickPlace_ON->Name = L"btnPickPlace_ON";
			this->btnPickPlace_ON->Size = System::Drawing::Size(90, 90);
			this->btnPickPlace_ON->TabIndex = 116;
			this->btnPickPlace_ON->Tag = L"2";
			this->btnPickPlace_ON->Text = L"ON";
			this->btnPickPlace_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnPickPlace_ON->UseVisualStyleBackColor = true;
			this->btnPickPlace_ON->Click += gcnew System::EventHandler(this, &DashboardScreen::btnPickPlace_ON_Click);
			// 
			// lblPickPlace
			// 
			this->lblPickPlace->AutoSize = true;
			this->lblPickPlace->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPickPlace->Location = System::Drawing::Point(972, 47);
			this->lblPickPlace->Name = L"lblPickPlace";
			this->lblPickPlace->Size = System::Drawing::Size(136, 30);
			this->lblPickPlace->TabIndex = 115;
			this->lblPickPlace->Tag = L"2";
			this->lblPickPlace->Text = L"Pick Place";
			// 
			// lblModel
			// 
			this->lblModel->AutoSize = true;
			this->lblModel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblModel->Location = System::Drawing::Point(9, 345);
			this->lblModel->Name = L"lblModel";
			this->lblModel->Size = System::Drawing::Size(86, 30);
			this->lblModel->TabIndex = 126;
			this->lblModel->Tag = L"1";
			this->lblModel->Text = L"Model";
			// 
			// cobModel
			// 
			this->cobModel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cobModel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cobModel->FormattingEnabled = true;
			this->cobModel->Location = System::Drawing::Point(104, 341);
			this->cobModel->Name = L"cobModel";
			this->cobModel->Size = System::Drawing::Size(180, 42);
			this->cobModel->TabIndex = 125;
			this->cobModel->Tag = L"1";
			this->cobModel->SelectedIndexChanged += gcnew System::EventHandler(this, &DashboardScreen::cobModel_SelectedIndexChanged);
			// 
			// btnScanLift1
			// 
			this->btnScanLift1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnScanLift1->Location = System::Drawing::Point(15, 38);
			this->btnScanLift1->Name = L"btnScanLift1";
			this->btnScanLift1->Size = System::Drawing::Size(141, 90);
			this->btnScanLift1->TabIndex = 127;
			this->btnScanLift1->Tag = L"1";
			this->btnScanLift1->Text = L"Lift 1";
			this->btnScanLift1->UseVisualStyleBackColor = true;
			this->btnScanLift1->Click += gcnew System::EventHandler(this, &DashboardScreen::btnScanLift1_Click);
			// 
			// btnScanLift2
			// 
			this->btnScanLift2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnScanLift2->Location = System::Drawing::Point(15, 137);
			this->btnScanLift2->Name = L"btnScanLift2";
			this->btnScanLift2->Size = System::Drawing::Size(141, 90);
			this->btnScanLift2->TabIndex = 128;
			this->btnScanLift2->Tag = L"1";
			this->btnScanLift2->Text = L"Lift 2";
			this->btnScanLift2->UseVisualStyleBackColor = true;
			this->btnScanLift2->Click += gcnew System::EventHandler(this, &DashboardScreen::btnScanLift2_Click);
			// 
			// btnScanReject
			// 
			this->btnScanReject->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnScanReject->Location = System::Drawing::Point(15, 236);
			this->btnScanReject->Name = L"btnScanReject";
			this->btnScanReject->Size = System::Drawing::Size(141, 90);
			this->btnScanReject->TabIndex = 129;
			this->btnScanReject->Tag = L"1";
			this->btnScanReject->Text = L"Reject";
			this->btnScanReject->UseVisualStyleBackColor = true;
			this->btnScanReject->Click += gcnew System::EventHandler(this, &DashboardScreen::btnScanReject_Click);
			// 
			// grbVision
			// 
			this->grbVision->Controls->Add(this->lblRejectScanResult);
			this->grbVision->Controls->Add(this->lblLift2ScanResult);
			this->grbVision->Controls->Add(this->lblLift1ScanResult);
			this->grbVision->Controls->Add(this->btnScanReject);
			this->grbVision->Controls->Add(this->lblModel);
			this->grbVision->Controls->Add(this->cobModel);
			this->grbVision->Controls->Add(this->btnScanLift1);
			this->grbVision->Controls->Add(this->btnScanLift2);
			this->grbVision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold));
			this->grbVision->Location = System::Drawing::Point(978, 117);
			this->grbVision->Name = L"grbVision";
			this->grbVision->Size = System::Drawing::Size(539, 423);
			this->grbVision->TabIndex = 130;
			this->grbVision->TabStop = false;
			this->grbVision->Tag = L"1";
			this->grbVision->Text = L"Scan Vision";
			// 
			// lblMovePearling
			// 
			this->lblMovePearling->AutoSize = true;
			this->lblMovePearling->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMovePearling->Location = System::Drawing::Point(56, 47);
			this->lblMovePearling->Name = L"lblMovePearling";
			this->lblMovePearling->Size = System::Drawing::Size(174, 30);
			this->lblMovePearling->TabIndex = 132;
			this->lblMovePearling->Tag = L"0";
			this->lblMovePearling->Text = L"MovePearling";
			// 
			// btnMovePearling
			// 
			this->btnMovePearling->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMovePearling->Location = System::Drawing::Point(438, 18);
			this->btnMovePearling->Name = L"btnMovePearling";
			this->btnMovePearling->Size = System::Drawing::Size(90, 90);
			this->btnMovePearling->TabIndex = 131;
			this->btnMovePearling->Tag = L"0";
			this->btnMovePearling->Text = L"Go";
			this->btnMovePearling->UseVisualStyleBackColor = true;
			this->btnMovePearling->Click += gcnew System::EventHandler(this, &DashboardScreen::btnMovePearling_Click);
			// 
			// lblMoveTable
			// 
			this->lblMoveTable->AutoSize = true;
			this->lblMoveTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveTable->Location = System::Drawing::Point(56, 146);
			this->lblMoveTable->Name = L"lblMoveTable";
			this->lblMoveTable->Size = System::Drawing::Size(143, 30);
			this->lblMoveTable->TabIndex = 134;
			this->lblMoveTable->Tag = L"0";
			this->lblMoveTable->Text = L"MoveTable";
			// 
			// btnMoveTable
			// 
			this->btnMoveTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMoveTable->Location = System::Drawing::Point(438, 117);
			this->btnMoveTable->Name = L"btnMoveTable";
			this->btnMoveTable->Size = System::Drawing::Size(90, 90);
			this->btnMoveTable->TabIndex = 133;
			this->btnMoveTable->Tag = L"0";
			this->btnMoveTable->Text = L"Go";
			this->btnMoveTable->UseVisualStyleBackColor = true;
			this->btnMoveTable->Click += gcnew System::EventHandler(this, &DashboardScreen::btnMoveTable_Click);
			// 
			// lblMoveLiftLoader
			// 
			this->lblMoveLiftLoader->AutoSize = true;
			this->lblMoveLiftLoader->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveLiftLoader->Location = System::Drawing::Point(56, 245);
			this->lblMoveLiftLoader->Name = L"lblMoveLiftLoader";
			this->lblMoveLiftLoader->Size = System::Drawing::Size(200, 30);
			this->lblMoveLiftLoader->TabIndex = 136;
			this->lblMoveLiftLoader->Tag = L"0";
			this->lblMoveLiftLoader->Text = L"MoveLiftLoader";
			// 
			// btnMoveLiftLoader
			// 
			this->btnMoveLiftLoader->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMoveLiftLoader->Location = System::Drawing::Point(438, 216);
			this->btnMoveLiftLoader->Name = L"btnMoveLiftLoader";
			this->btnMoveLiftLoader->Size = System::Drawing::Size(90, 90);
			this->btnMoveLiftLoader->TabIndex = 135;
			this->btnMoveLiftLoader->Tag = L"0";
			this->btnMoveLiftLoader->Text = L"Go";
			this->btnMoveLiftLoader->UseVisualStyleBackColor = true;
			this->btnMoveLiftLoader->Click += gcnew System::EventHandler(this, &DashboardScreen::btnMoveLiftLoader_Click);
			// 
			// lblLift1ScanResult
			// 
			this->lblLift1ScanResult->AutoSize = true;
			this->lblLift1ScanResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLift1ScanResult->Location = System::Drawing::Point(180, 66);
			this->lblLift1ScanResult->Name = L"lblLift1ScanResult";
			this->lblLift1ScanResult->Size = System::Drawing::Size(57, 30);
			this->lblLift1ScanResult->TabIndex = 133;
			this->lblLift1ScanResult->Tag = L"1";
			this->lblLift1ScanResult->Text = L"(-/-)";
			// 
			// lblLift2ScanResult
			// 
			this->lblLift2ScanResult->AutoSize = true;
			this->lblLift2ScanResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLift2ScanResult->Location = System::Drawing::Point(180, 165);
			this->lblLift2ScanResult->Name = L"lblLift2ScanResult";
			this->lblLift2ScanResult->Size = System::Drawing::Size(57, 30);
			this->lblLift2ScanResult->TabIndex = 134;
			this->lblLift2ScanResult->Tag = L"1";
			this->lblLift2ScanResult->Text = L"(-/-)";
			// 
			// lblRejectScanResult
			// 
			this->lblRejectScanResult->AutoSize = true;
			this->lblRejectScanResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRejectScanResult->Location = System::Drawing::Point(180, 264);
			this->lblRejectScanResult->Name = L"lblRejectScanResult";
			this->lblRejectScanResult->Size = System::Drawing::Size(57, 30);
			this->lblRejectScanResult->TabIndex = 135;
			this->lblRejectScanResult->Tag = L"1";
			this->lblRejectScanResult->Text = L"(-/-)";
			// 
			// DashboardScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->lblMoveLiftLoader);
			this->Controls->Add(this->btnMoveLiftLoader);
			this->Controls->Add(this->lblMoveTable);
			this->Controls->Add(this->btnMoveTable);
			this->Controls->Add(this->lblMovePearling);
			this->Controls->Add(this->btnMovePearling);
			this->Controls->Add(this->grbVision);
			this->Controls->Add(this->btnPickPlace_OFF);
			this->Controls->Add(this->btnPickPlace_ON);
			this->Controls->Add(this->lblPickPlace);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"DashboardScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Dashboard";
			this->Load += gcnew System::EventHandler(this, &DashboardScreen::ProdScreen_Load);
			this->VisibleChanged += gcnew System::EventHandler(this, &DashboardScreen::ProdScreen_VisibleChanged);
			this->grbVision->ResumeLayout(false);
			this->grbVision->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void ProdScreen_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void ProdScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			lblMoveLiftLoader->Text = TUtilities::pS_LoadString(TextIndex::MoveLiftLoader);
			lblMovePearling->Text = TUtilities::pS_LoadString(TextIndex::MovePearling);
			lblMoveTable->Text = TUtilities::pS_LoadString(TextIndex::MoveTable);
		 }
private: System::Void btnPickPlace_ON_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(this->Text + " : PickPlace OFF");
	SetTCData(s_DashboardCmd.DC_PickPlace);
}
private: System::Void btnPickPlace_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(this->Text + " : PickPlace ON");
	ClearTCData(s_DashboardCmd.DC_PickPlace);
}
private: System::Void btnScanLift1_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(this->Text + " : Scan Lift 1");
	SetTCData(s_DashboardCmd.DC_LoaderScanPlateLift1);
}
private: System::Void btnScanLift2_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(this->Text + " : Scan Lift 2");
	SetTCData(s_DashboardCmd.DC_LoaderScanPlateLift2);
}
private: System::Void btnScanReject_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(this->Text + " : Scan Reject");
	SetTCData(s_DashboardCmd.DC_LoaderScanPlateReject);
}
private: System::Void cobModel_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(this->Text + " : " + TUtilities::pS_LoadString(TextIndex::Model) + " [" + cobModel->SelectedIndex + "]");
	WriteTCData(s_DashboardCmd.DC_ScanModel, (TC_INT)cobModel->SelectedIndex);

}
	private: System::Void btnMovePearling_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(this->Text + " : " + TUtilities::pS_LoadString(TextIndex::MovePearling));
		SetTCData(s_DashboardCmd.DC_Pearling);
	}
private: System::Void btnMoveTable_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(this->Text + " : " + TUtilities::pS_LoadString(TextIndex::MoveTable));
	SetTCData(s_DashboardCmd.DC_TableTurn);
}
private: System::Void btnMoveLiftLoader_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(this->Text + " : " + TUtilities::pS_LoadString(TextIndex::MoveLiftLoader));
	SetTCData(s_DashboardCmd.DC_LoaderEndOfRecipe);
}
		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
};
}