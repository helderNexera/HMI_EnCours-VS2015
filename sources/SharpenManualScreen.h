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
	using namespace MondemaComponents;

	/// <summary>
	/// Description résumée de LotScreen
	/// </summary>
	public ref class SharpenManualScreen : public System::Windows::Forms::Form
	{
	public:
		SharpenManualScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_Drive = gcnew DriveComponent(this->gbAxis);
			pT_Drive->SetDriveData(TUtilities::pS_LoadString(TextIndex::Rotation), GetTCManualOffset(s_SharpenManual.MS_Axis), L"");
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::SharpenManualScreen::OnUserLevelChanged);
		}

	private:	bool bReloadParams;
	private: System::Windows::Forms::Label^  lblTapePresent;
	private: MondemaComponents::Led^  ledTapeNotEmpty;
	private: System::Windows::Forms::Label^  lblStep;
	private: System::Windows::Forms::Label^  lblStepValue;

	public:

			 // Our specific functions
	private:
		DriveComponent^ pT_Drive;
	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~SharpenManualScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::CheckBox^  btnAspiration_OFF;
	private: System::Windows::Forms::CheckBox^  btnAspiration_ON;
	private: System::Windows::Forms::Label^  lblAspiration;
	private: System::Windows::Forms::GroupBox^  gbAxis;
	private: System::Windows::Forms::Label^  lblNextStep;
	private: System::Windows::Forms::Button^  btnMove2NextStep;
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
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->lblStepValue = (gcnew System::Windows::Forms::Label());
			this->lblStep = (gcnew System::Windows::Forms::Label());
			this->lblTapePresent = (gcnew System::Windows::Forms::Label());
			this->ledTapeNotEmpty = (gcnew MondemaComponents::Led());
			this->btnAspiration_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnAspiration_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblAspiration = (gcnew System::Windows::Forms::Label());
			this->lblNextStep = (gcnew System::Windows::Forms::Label());
			this->btnMove2NextStep = (gcnew System::Windows::Forms::Button());
			this->gbAxis = (gcnew System::Windows::Forms::GroupBox());
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tabControl->ItemSize = System::Drawing::Size(134, 45);
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1578, 895);
			this->tabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->lblStepValue);
			this->tabPage1->Controls->Add(this->lblStep);
			this->tabPage1->Controls->Add(this->lblTapePresent);
			this->tabPage1->Controls->Add(this->ledTapeNotEmpty);
			this->tabPage1->Controls->Add(this->btnAspiration_OFF);
			this->tabPage1->Controls->Add(this->btnAspiration_ON);
			this->tabPage1->Controls->Add(this->lblAspiration);
			this->tabPage1->Controls->Add(this->lblNextStep);
			this->tabPage1->Controls->Add(this->btnMove2NextStep);
			this->tabPage1->Controls->Add(this->gbAxis);
			this->tabPage1->Location = System::Drawing::Point(4, 49);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1570, 842);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// lblStepValue
			// 
			this->lblStepValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblStepValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblStepValue->Location = System::Drawing::Point(1035, 131);
			this->lblStepValue->Name = L"lblStepValue";
			this->lblStepValue->Size = System::Drawing::Size(162, 39);
			this->lblStepValue->TabIndex = 116;
			this->lblStepValue->Tag = L"1";
			this->lblStepValue->Text = L"0.00";
			this->lblStepValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblStepValue->Click += gcnew System::EventHandler(this, &SharpenManualScreen::tbStep_Click);
			// 
			// lblStep
			// 
			this->lblStep->AutoSize = true;
			this->lblStep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStep->Location = System::Drawing::Point(796, 131);
			this->lblStep->Name = L"lblStep";
			this->lblStep->Size = System::Drawing::Size(67, 29);
			this->lblStep->TabIndex = 115;
			this->lblStep->Tag = L"1";
			this->lblStep->Text = L"Step";
			// 
			// lblTapePresent
			// 
			this->lblTapePresent->AutoSize = true;
			this->lblTapePresent->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTapePresent->Location = System::Drawing::Point(796, 74);
			this->lblTapePresent->Name = L"lblTapePresent";
			this->lblTapePresent->Size = System::Drawing::Size(171, 29);
			this->lblTapePresent->TabIndex = 113;
			this->lblTapePresent->Tag = L"1";
			this->lblTapePresent->Text = L"Tape Present";
			// 
			// ledTapeNotEmpty
			// 
			this->ledTapeNotEmpty->Location = System::Drawing::Point(1088, 66);
			this->ledTapeNotEmpty->Margin = System::Windows::Forms::Padding(5);
			this->ledTapeNotEmpty->Name = L"ledTapeNotEmpty";
			this->ledTapeNotEmpty->Size = System::Drawing::Size(45, 45);
			this->ledTapeNotEmpty->TabIndex = 112;
			this->ledTapeNotEmpty->Tag = L"1";
			// 
			// btnAspiration_OFF
			// 
			this->btnAspiration_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAspiration_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAspiration_OFF->Location = System::Drawing::Point(528, 198);
			this->btnAspiration_OFF->Name = L"btnAspiration_OFF";
			this->btnAspiration_OFF->Size = System::Drawing::Size(90, 90);
			this->btnAspiration_OFF->TabIndex = 111;
			this->btnAspiration_OFF->Tag = L"1";
			this->btnAspiration_OFF->Text = L"OFF";
			this->btnAspiration_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAspiration_OFF->UseVisualStyleBackColor = true;
			this->btnAspiration_OFF->Click += gcnew System::EventHandler(this, &SharpenManualScreen::btnAspiration_OFF_Click);
			// 
			// btnAspiration_ON
			// 
			this->btnAspiration_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAspiration_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAspiration_ON->Location = System::Drawing::Point(429, 198);
			this->btnAspiration_ON->Name = L"btnAspiration_ON";
			this->btnAspiration_ON->Size = System::Drawing::Size(90, 90);
			this->btnAspiration_ON->TabIndex = 110;
			this->btnAspiration_ON->Tag = L"1";
			this->btnAspiration_ON->Text = L"ON";
			this->btnAspiration_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAspiration_ON->UseVisualStyleBackColor = true;
			this->btnAspiration_ON->Click += gcnew System::EventHandler(this, &SharpenManualScreen::btnAspiration_ON_Click);
			// 
			// lblAspiration
			// 
			this->lblAspiration->AutoSize = true;
			this->lblAspiration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAspiration->Location = System::Drawing::Point(47, 227);
			this->lblAspiration->Name = L"lblAspiration";
			this->lblAspiration->Size = System::Drawing::Size(0, 29);
			this->lblAspiration->TabIndex = 109;
			this->lblAspiration->Tag = L"1";
			// 
			// lblNextStep
			// 
			this->lblNextStep->AutoSize = true;
			this->lblNextStep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblNextStep->Location = System::Drawing::Point(47, 102);
			this->lblNextStep->Name = L"lblNextStep";
			this->lblNextStep->Size = System::Drawing::Size(0, 29);
			this->lblNextStep->TabIndex = 10;
			this->lblNextStep->Tag = L"1";
			// 
			// btnMove2NextStep
			// 
			this->btnMove2NextStep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMove2NextStep->Location = System::Drawing::Point(429, 74);
			this->btnMove2NextStep->Name = L"btnMove2NextStep";
			this->btnMove2NextStep->Size = System::Drawing::Size(90, 90);
			this->btnMove2NextStep->TabIndex = 2;
			this->btnMove2NextStep->Tag = L"1";
			this->btnMove2NextStep->Text = L"Go";
			this->btnMove2NextStep->UseVisualStyleBackColor = true;
			this->btnMove2NextStep->Click += gcnew System::EventHandler(this, &SharpenManualScreen::btnMove2NextStep_Click);
			// 
			// gbAxis
			// 
			this->gbAxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbAxis->Location = System::Drawing::Point(52, 323);
			this->gbAxis->Name = L"gbAxis";
			this->gbAxis->Size = System::Drawing::Size(728, 375);
			this->gbAxis->TabIndex = 96;
			this->gbAxis->TabStop = false;
			this->gbAxis->Tag = L"2";
			// 
			// SharpenManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"SharpenManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &SharpenManualScreen::SharpenManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void ShowOsk_Click(System::Object^  sender, System::EventArgs^  e) {
		TUtilities::ShowOSK();
	}

private: System::Void btnMove2NextStep_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::NextStep));
			SetTCManData(s_SharpenManual.MS_Move2NextPos.MB_Activate);
		 }
private: System::Void btnAspiration_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Aspiration) + "ON");
			SetTCManData(s_PearlingManual.MP_ActivateAspirationSharpen.MB_Activate);
		 }
private: System::Void btnAspiration_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Aspiration) + "OFF");
			ClearTCManData(s_PearlingManual.MP_ActivateAspirationSharpen.MB_Activate);
		 }
private: System::Void SharpenManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			tabPage1->Text = TUtilities::pS_LoadString(TextIndex::Sharpening);
			lblAspiration->Text = TUtilities::pS_LoadString(TextIndex::Aspiration);
			lblNextStep->Text = TUtilities::pS_LoadString(TextIndex::NextStep);
			lblStep->Text = TUtilities::pS_LoadString(TextIndex::Step) + " [mm]";
			lblTapePresent->Text = TUtilities::pS_LoadString(TextIndex::TapePresent);

			gbAxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::Axis) + L"  ";

			pT_Drive->ReloadComponent();
			pT_Drive->SetDriveName(TUtilities::pS_LoadString(TextIndex::Rotation), L"");
			bReloadParams = true;
		 }
private: System::Void tbStep_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblStep->Text, double::Parse(lblStepValue->Text), 1.0, 15.0,"F1");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabPage1->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Step) + L" = " + Keypad->Value.ToString());
		WriteTCManData(s_SharpenManual.MS_Step, (TC_LREAL)Keypad->Value);
	}
}
		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
};
}