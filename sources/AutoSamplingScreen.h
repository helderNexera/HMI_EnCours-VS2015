#pragma once

#include "TTwincatInterface.h"
#include "MyMsgBox.h"
#include "global.h"
#include "TUtilities.h"
#include "AlarmScreen.h"
#include "TLogger.h"
#include "DriveComponent.h"

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
	public ref class AutoSamplingScreen : public System::Windows::Forms::Form
	{
	public:
		AutoSamplingScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//

			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::AutoSamplingScreen::OnUserLevelChanged);
		}



	public:

	public: 



	public: 
	public: 

			 // Our specific functions
	private:


		 DriveComponent^ pT_DriveTable;
	private: System::Windows::Forms::CheckBox^  cbEnableAS;
	private: System::Windows::Forms::Label^  lblEnableAS;
	private: System::Windows::Forms::TextBox^  tbASPeriod;
	private: System::Windows::Forms::Label^  lblASPeriod;
	private: System::Windows::Forms::TextBox^  tbASSize;
	private: System::Windows::Forms::Label^  lblASSize;
	private: System::Windows::Forms::Button^  btnRequestSample;
	private: System::Windows::Forms::Label^  lblASPeriodCounter;
	private: System::Windows::Forms::Label^  lblASBatchCounter;

			 DriveComponent^ pT_DriveBrush;

	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~AutoSamplingScreen()
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
			this->cbEnableAS = (gcnew System::Windows::Forms::CheckBox());
			this->lblEnableAS = (gcnew System::Windows::Forms::Label());
			this->tbASPeriod = (gcnew System::Windows::Forms::TextBox());
			this->lblASPeriod = (gcnew System::Windows::Forms::Label());
			this->tbASSize = (gcnew System::Windows::Forms::TextBox());
			this->lblASSize = (gcnew System::Windows::Forms::Label());
			this->btnRequestSample = (gcnew System::Windows::Forms::Button());
			this->lblASPeriodCounter = (gcnew System::Windows::Forms::Label());
			this->lblASBatchCounter = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// cbEnableAS
			// 
			this->cbEnableAS->AutoSize = true;
			this->cbEnableAS->Checked = true;
			this->cbEnableAS->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbEnableAS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbEnableAS->Location = System::Drawing::Point(447, 38);
			this->cbEnableAS->Name = L"cbEnableAS";
			this->cbEnableAS->Size = System::Drawing::Size(15, 14);
			this->cbEnableAS->TabIndex = 98;
			this->cbEnableAS->Tag = L"1";
			this->cbEnableAS->UseVisualStyleBackColor = true;
			// 
			// lblEnableAS
			// 
			this->lblEnableAS->AutoSize = true;
			this->lblEnableAS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblEnableAS->Location = System::Drawing::Point(42, 36);
			this->lblEnableAS->Name = L"lblEnableAS";
			this->lblEnableAS->Size = System::Drawing::Size(128, 29);
			this->lblEnableAS->TabIndex = 97;
			this->lblEnableAS->Tag = L"1";
			this->lblEnableAS->Text = L"EnableAS";
			// 
			// tbASPeriod
			// 
			this->tbASPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbASPeriod->Location = System::Drawing::Point(447, 126);
			this->tbASPeriod->Name = L"tbASPeriod";
			this->tbASPeriod->Size = System::Drawing::Size(162, 35);
			this->tbASPeriod->TabIndex = 119;
			this->tbASPeriod->Tag = L"1";
			this->tbASPeriod->Text = L"100";
			this->tbASPeriod->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->tbASPeriod->Click += gcnew System::EventHandler(this, &AutoSamplingScreen::ShowOsk_Click);
			this->tbASPeriod->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &AutoSamplingScreen::tbASPeriod_PreviewKeyDown);
			// 
			// lblASPeriod
			// 
			this->lblASPeriod->AutoSize = true;
			this->lblASPeriod->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblASPeriod->Location = System::Drawing::Point(42, 126);
			this->lblASPeriod->Name = L"lblASPeriod";
			this->lblASPeriod->Size = System::Drawing::Size(124, 29);
			this->lblASPeriod->TabIndex = 120;
			this->lblASPeriod->Tag = L"1";
			this->lblASPeriod->Text = L"ASPeriod";
			// 
			// tbASSize
			// 
			this->tbASSize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbASSize->Location = System::Drawing::Point(447, 192);
			this->tbASSize->Name = L"tbASSize";
			this->tbASSize->Size = System::Drawing::Size(162, 35);
			this->tbASSize->TabIndex = 121;
			this->tbASSize->Tag = L"1";
			this->tbASSize->Text = L"1";
			this->tbASSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->tbASSize->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &AutoSamplingScreen::tbASSize_PreviewKeyDown);
			// 
			// lblASSize
			// 
			this->lblASSize->AutoSize = true;
			this->lblASSize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblASSize->Location = System::Drawing::Point(42, 192);
			this->lblASSize->Name = L"lblASSize";
			this->lblASSize->Size = System::Drawing::Size(97, 29);
			this->lblASSize->TabIndex = 122;
			this->lblASSize->Tag = L"1";
			this->lblASSize->Text = L"ASSize";
			// 
			// btnRequestSample
			// 
			this->btnRequestSample->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnRequestSample->Location = System::Drawing::Point(511, 16);
			this->btnRequestSample->Name = L"btnRequestSample";
			this->btnRequestSample->Size = System::Drawing::Size(225, 66);
			this->btnRequestSample->TabIndex = 123;
			this->btnRequestSample->UseVisualStyleBackColor = true;
			// 
			// lblASPeriodCounter
			// 
			this->lblASPeriodCounter->AutoSize = true;
			this->lblASPeriodCounter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblASPeriodCounter->Location = System::Drawing::Point(618, 131);
			this->lblASPeriodCounter->Name = L"lblASPeriodCounter";
			this->lblASPeriodCounter->Size = System::Drawing::Size(27, 29);
			this->lblASPeriodCounter->TabIndex = 124;
			this->lblASPeriodCounter->Tag = L"1";
			this->lblASPeriodCounter->Text = L"0";
			// 
			// lblASBatchCounter
			// 
			this->lblASBatchCounter->AutoSize = true;
			this->lblASBatchCounter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblASBatchCounter->Location = System::Drawing::Point(618, 195);
			this->lblASBatchCounter->Name = L"lblASBatchCounter";
			this->lblASBatchCounter->Size = System::Drawing::Size(27, 29);
			this->lblASBatchCounter->TabIndex = 125;
			this->lblASBatchCounter->Tag = L"1";
			this->lblASBatchCounter->Text = L"0";
			// 
			// AutoSamplingScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->lblASBatchCounter);
			this->Controls->Add(this->lblASPeriodCounter);
			this->Controls->Add(this->btnRequestSample);
			this->Controls->Add(this->tbASSize);
			this->Controls->Add(this->lblASSize);
			this->Controls->Add(this->tbASPeriod);
			this->Controls->Add(this->lblASPeriod);
			this->Controls->Add(this->cbEnableAS);
			this->Controls->Add(this->lblEnableAS);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"AutoSamplingScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &AutoSamplingScreen::AutoSamplingScreen_VisibleChanged);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);

private: System::Void AutoSamplingScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			lblEnableAS->Text = TUtilities::pS_LoadString(TextIndex::EnableAS);
			lblASPeriod->Text = TUtilities::pS_LoadString(TextIndex::ASPeriod);
			lblASSize->Text = TUtilities::pS_LoadString(TextIndex::ASSIze);
			btnRequestSample->Text = TUtilities::pS_LoadString(TextIndex::Sample);

		}
private: System::Void tbASPeriod_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
	if (e->KeyCode == Keys::Return)
	{
		int i_l_Data;

		if (Int32::TryParse(tbASPeriod->Text, i_l_Data))
		{
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::ASPeriod) + L" = " + tbASPeriod->Text);
			WriteTCData(s_ProductionCmd.PC_AutoSampling.AS_Period, (TC_INT)i_l_Data);
		}
		else
			tbASPeriod->Text = L"0";
	}
	e->IsInputKey = true;
}
private: System::Void ShowOsk_Click(System::Object^  sender, System::EventArgs^  e) {
	TUtilities::ShowOSK();
}

private: System::Void tbASSize_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
	if (e->KeyCode == Keys::Return)
	{
		int i_l_Data;

		if (Int32::TryParse(tbASSize->Text, i_l_Data))
		{
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::ASPeriod) + L" = " + tbASSize->Text);
			WriteTCData(s_ProductionCmd.PC_AutoSampling.AS_BatchSize, (TC_INT)i_l_Data);
		}
		else
			tbASSize->Text = L"0";
	}
	e->IsInputKey = true;
}
};
}
