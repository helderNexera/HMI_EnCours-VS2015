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
	public ref class TurnOverManualScreen : public System::Windows::Forms::Form
	{
	public:
		TurnOverManualScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_Drive = gcnew DriveComponent(this->gbAxis);
			pT_Drive->UsePosition(0, "");
			pT_Drive->UsePosition(1, "");
			pT_Drive->SetDriveData(tabControl->TabPages[0]->Text, GetTCManualOffset(s_TurnOverManual.MTO_Axis), L"");
			pT_Drive->SetDrivePosData(0, GetTCManualOffset(s_TurnOverManual.MTO_AxisCWPos));
			pT_Drive->SetDrivePosData(1, GetTCManualOffset(s_TurnOverManual.MTO_AxisCCWPos));

			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::TurnOverManualScreen::OnUserLevelChanged);
		}
		// Our specific functions
	private:
		DriveComponent^ pT_Drive;
		DriveComponent^ pT_BufferDrive;
	private: System::Windows::Forms::CheckBox^  btnFixVacuum_OFF;
	private: System::Windows::Forms::CheckBox^  btnFixVacuum_ON;
	private: System::Windows::Forms::Label^  lblFixVacuum;
	private: System::Windows::Forms::CheckBox^  btnArmVacuum_OFF;
	private: System::Windows::Forms::CheckBox^  btnArmVacuum_ON;
	private: System::Windows::Forms::Label^  lblArmVacuum;
	private: System::Windows::Forms::CheckBox^  btnAspiration_OFF;
	private: System::Windows::Forms::CheckBox^  btnAspiration_ON;
	private: System::Windows::Forms::Label^  lblAspiration;
	private: System::Windows::Forms::CheckBox^  btnBlow_OFF;
	private: System::Windows::Forms::CheckBox^  btnBlow_ON;
	private: System::Windows::Forms::Label^  lblCleaningBlow;
	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~TurnOverManualScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tbTurnOver;
	private: System::Windows::Forms::GroupBox^  gbAxis;
	private: System::Windows::Forms::Label^  lblJack;
	private: System::Windows::Forms::CheckBox^  btnMoveArmDown;
	private: System::Windows::Forms::CheckBox^  btnMoveArmUp;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TurnOverManualScreen::typeid));
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tbTurnOver = (gcnew System::Windows::Forms::TabPage());
			this->btnBlow_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnBlow_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblCleaningBlow = (gcnew System::Windows::Forms::Label());
			this->btnAspiration_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnAspiration_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblAspiration = (gcnew System::Windows::Forms::Label());
			this->btnFixVacuum_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnFixVacuum_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblFixVacuum = (gcnew System::Windows::Forms::Label());
			this->btnArmVacuum_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnArmVacuum_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblArmVacuum = (gcnew System::Windows::Forms::Label());
			this->gbAxis = (gcnew System::Windows::Forms::GroupBox());
			this->lblJack = (gcnew System::Windows::Forms::Label());
			this->btnMoveArmDown = (gcnew System::Windows::Forms::CheckBox());
			this->btnMoveArmUp = (gcnew System::Windows::Forms::CheckBox());
			this->tabControl->SuspendLayout();
			this->tbTurnOver->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tbTurnOver);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tabControl->ItemSize = System::Drawing::Size(134, 45);
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1578, 895);
			this->tabControl->TabIndex = 0;
			// 
			// tbTurnOver
			// 
			this->tbTurnOver->Controls->Add(this->btnBlow_OFF);
			this->tbTurnOver->Controls->Add(this->btnBlow_ON);
			this->tbTurnOver->Controls->Add(this->lblCleaningBlow);
			this->tbTurnOver->Controls->Add(this->btnAspiration_OFF);
			this->tbTurnOver->Controls->Add(this->btnAspiration_ON);
			this->tbTurnOver->Controls->Add(this->lblAspiration);
			this->tbTurnOver->Controls->Add(this->btnFixVacuum_OFF);
			this->tbTurnOver->Controls->Add(this->btnFixVacuum_ON);
			this->tbTurnOver->Controls->Add(this->lblFixVacuum);
			this->tbTurnOver->Controls->Add(this->btnArmVacuum_OFF);
			this->tbTurnOver->Controls->Add(this->btnArmVacuum_ON);
			this->tbTurnOver->Controls->Add(this->lblArmVacuum);
			this->tbTurnOver->Controls->Add(this->gbAxis);
			this->tbTurnOver->Controls->Add(this->lblJack);
			this->tbTurnOver->Controls->Add(this->btnMoveArmDown);
			this->tbTurnOver->Controls->Add(this->btnMoveArmUp);
			this->tbTurnOver->Location = System::Drawing::Point(6, 51);
			this->tbTurnOver->Name = L"tbTurnOver";
			this->tbTurnOver->Padding = System::Windows::Forms::Padding(3);
			this->tbTurnOver->Size = System::Drawing::Size(1570, 857);
			this->tbTurnOver->TabIndex = 1;
			this->tbTurnOver->UseVisualStyleBackColor = true;
			// 
			// btnBlow_OFF
			// 
			this->btnBlow_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnBlow_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnBlow_OFF->Location = System::Drawing::Point(410, 504);
			this->btnBlow_OFF->Name = L"btnBlow_OFF";
			this->btnBlow_OFF->Size = System::Drawing::Size(90, 90);
			this->btnBlow_OFF->TabIndex = 120;
			this->btnBlow_OFF->Tag = L"1";
			this->btnBlow_OFF->Text = L"OFF";
			this->btnBlow_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnBlow_OFF->UseVisualStyleBackColor = true;
			this->btnBlow_OFF->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnBlow_OFF_Click);
			// 
			// btnBlow_ON
			// 
			this->btnBlow_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnBlow_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnBlow_ON->Location = System::Drawing::Point(311, 504);
			this->btnBlow_ON->Name = L"btnBlow_ON";
			this->btnBlow_ON->Size = System::Drawing::Size(90, 90);
			this->btnBlow_ON->TabIndex = 119;
			this->btnBlow_ON->Tag = L"1";
			this->btnBlow_ON->Text = L"ON";
			this->btnBlow_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnBlow_ON->UseVisualStyleBackColor = true;
			this->btnBlow_ON->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnBlow_ON_Click);
			// 
			// lblCleaningBlow
			// 
			this->lblCleaningBlow->AutoSize = true;
			this->lblCleaningBlow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCleaningBlow->Location = System::Drawing::Point(114, 536);
			this->lblCleaningBlow->Name = L"lblCleaningBlow";
			this->lblCleaningBlow->Size = System::Drawing::Size(176, 30);
			this->lblCleaningBlow->TabIndex = 118;
			this->lblCleaningBlow->Tag = L"1";
			this->lblCleaningBlow->Text = L"CleaningBlow";
			// 
			// btnAspiration_OFF
			// 
			this->btnAspiration_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAspiration_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAspiration_OFF->Location = System::Drawing::Point(410, 384);
			this->btnAspiration_OFF->Name = L"btnAspiration_OFF";
			this->btnAspiration_OFF->Size = System::Drawing::Size(90, 90);
			this->btnAspiration_OFF->TabIndex = 117;
			this->btnAspiration_OFF->Tag = L"1";
			this->btnAspiration_OFF->Text = L"OFF";
			this->btnAspiration_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAspiration_OFF->UseVisualStyleBackColor = true;
			this->btnAspiration_OFF->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnAspiration_OFF_Click);
			// 
			// btnAspiration_ON
			// 
			this->btnAspiration_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAspiration_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAspiration_ON->Location = System::Drawing::Point(311, 384);
			this->btnAspiration_ON->Name = L"btnAspiration_ON";
			this->btnAspiration_ON->Size = System::Drawing::Size(90, 90);
			this->btnAspiration_ON->TabIndex = 116;
			this->btnAspiration_ON->Tag = L"1";
			this->btnAspiration_ON->Text = L"ON";
			this->btnAspiration_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAspiration_ON->UseVisualStyleBackColor = true;
			this->btnAspiration_ON->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnAspiration_ON_Click);
			// 
			// lblAspiration
			// 
			this->lblAspiration->AutoSize = true;
			this->lblAspiration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAspiration->Location = System::Drawing::Point(114, 416);
			this->lblAspiration->Name = L"lblAspiration";
			this->lblAspiration->Size = System::Drawing::Size(135, 30);
			this->lblAspiration->TabIndex = 115;
			this->lblAspiration->Tag = L"1";
			this->lblAspiration->Text = L"Aspiration";
			// 
			// btnFixVacuum_OFF
			// 
			this->btnFixVacuum_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnFixVacuum_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnFixVacuum_OFF->Location = System::Drawing::Point(410, 267);
			this->btnFixVacuum_OFF->Name = L"btnFixVacuum_OFF";
			this->btnFixVacuum_OFF->Size = System::Drawing::Size(90, 90);
			this->btnFixVacuum_OFF->TabIndex = 62;
			this->btnFixVacuum_OFF->Tag = L"0";
			this->btnFixVacuum_OFF->Text = L"OFF";
			this->btnFixVacuum_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnFixVacuum_OFF->UseVisualStyleBackColor = true;
			this->btnFixVacuum_OFF->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnFixVacuum_OFF_Click);
			// 
			// btnFixVacuum_ON
			// 
			this->btnFixVacuum_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnFixVacuum_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnFixVacuum_ON->Location = System::Drawing::Point(311, 267);
			this->btnFixVacuum_ON->Name = L"btnFixVacuum_ON";
			this->btnFixVacuum_ON->Size = System::Drawing::Size(90, 90);
			this->btnFixVacuum_ON->TabIndex = 61;
			this->btnFixVacuum_ON->Tag = L"0";
			this->btnFixVacuum_ON->Text = L"ON";
			this->btnFixVacuum_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnFixVacuum_ON->UseVisualStyleBackColor = true;
			this->btnFixVacuum_ON->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnFixVacuum_ON_Click);
			// 
			// lblFixVacuum
			// 
			this->lblFixVacuum->AutoSize = true;
			this->lblFixVacuum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblFixVacuum->Location = System::Drawing::Point(114, 296);
			this->lblFixVacuum->Name = L"lblFixVacuum";
			this->lblFixVacuum->Size = System::Drawing::Size(146, 30);
			this->lblFixVacuum->TabIndex = 60;
			this->lblFixVacuum->Tag = L"0";
			this->lblFixVacuum->Text = L"FixVacuum";
			// 
			// btnArmVacuum_OFF
			// 
			this->btnArmVacuum_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnArmVacuum_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnArmVacuum_OFF->Location = System::Drawing::Point(410, 143);
			this->btnArmVacuum_OFF->Name = L"btnArmVacuum_OFF";
			this->btnArmVacuum_OFF->Size = System::Drawing::Size(90, 90);
			this->btnArmVacuum_OFF->TabIndex = 59;
			this->btnArmVacuum_OFF->Tag = L"0";
			this->btnArmVacuum_OFF->Text = L"OFF";
			this->btnArmVacuum_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnArmVacuum_OFF->UseVisualStyleBackColor = true;
			this->btnArmVacuum_OFF->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnArmVacuum_OFF_Click);
			// 
			// btnArmVacuum_ON
			// 
			this->btnArmVacuum_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnArmVacuum_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnArmVacuum_ON->Location = System::Drawing::Point(311, 143);
			this->btnArmVacuum_ON->Name = L"btnArmVacuum_ON";
			this->btnArmVacuum_ON->Size = System::Drawing::Size(90, 90);
			this->btnArmVacuum_ON->TabIndex = 58;
			this->btnArmVacuum_ON->Tag = L"0";
			this->btnArmVacuum_ON->Text = L"ON";
			this->btnArmVacuum_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnArmVacuum_ON->UseVisualStyleBackColor = true;
			this->btnArmVacuum_ON->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnArmVacuum_ON_Click);
			// 
			// lblArmVacuum
			// 
			this->lblArmVacuum->AutoSize = true;
			this->lblArmVacuum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblArmVacuum->Location = System::Drawing::Point(114, 171);
			this->lblArmVacuum->Name = L"lblArmVacuum";
			this->lblArmVacuum->Size = System::Drawing::Size(159, 30);
			this->lblArmVacuum->TabIndex = 57;
			this->lblArmVacuum->Tag = L"0";
			this->lblArmVacuum->Text = L"ArmVacuum";
			// 
			// gbAxis
			// 
			this->gbAxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbAxis->Location = System::Drawing::Point(762, 27);
			this->gbAxis->Name = L"gbAxis";
			this->gbAxis->Size = System::Drawing::Size(735, 375);
			this->gbAxis->TabIndex = 56;
			this->gbAxis->TabStop = false;
			this->gbAxis->Tag = L"2";
			// 
			// lblJack
			// 
			this->lblJack->AutoSize = true;
			this->lblJack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblJack->Location = System::Drawing::Point(114, 56);
			this->lblJack->Name = L"lblJack";
			this->lblJack->Size = System::Drawing::Size(69, 30);
			this->lblJack->TabIndex = 51;
			this->lblJack->Tag = L"1";
			this->lblJack->Text = L"Jack";
			// 
			// btnMoveArmDown
			// 
			this->btnMoveArmDown->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnMoveArmDown->BackColor = System::Drawing::Color::White;
			this->btnMoveArmDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMoveArmDown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnMoveArmDown.Image")));
			this->btnMoveArmDown->Location = System::Drawing::Point(410, 27);
			this->btnMoveArmDown->Name = L"btnMoveArmDown";
			this->btnMoveArmDown->Size = System::Drawing::Size(90, 90);
			this->btnMoveArmDown->TabIndex = 50;
			this->btnMoveArmDown->Tag = L"1";
			this->btnMoveArmDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnMoveArmDown->UseVisualStyleBackColor = false;
			this->btnMoveArmDown->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnMoveArmDown_Click);
			// 
			// btnMoveArmUp
			// 
			this->btnMoveArmUp->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnMoveArmUp->BackColor = System::Drawing::Color::White;
			this->btnMoveArmUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMoveArmUp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnMoveArmUp.Image")));
			this->btnMoveArmUp->Location = System::Drawing::Point(311, 27);
			this->btnMoveArmUp->Name = L"btnMoveArmUp";
			this->btnMoveArmUp->Size = System::Drawing::Size(90, 90);
			this->btnMoveArmUp->TabIndex = 49;
			this->btnMoveArmUp->Tag = L"1";
			this->btnMoveArmUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnMoveArmUp->UseVisualStyleBackColor = false;
			this->btnMoveArmUp->Click += gcnew System::EventHandler(this, &TurnOverManualScreen::btnMoveArmUp_Click);
			// 
			// TurnOverManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"TurnOverManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &TurnOverManualScreen::TurnOverManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tbTurnOver->ResumeLayout(false);
			this->tbTurnOver->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void btnMoveArmUp_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::MoveJackUp));
		SetTCManData(s_TurnOverManual.MTO_MoveJackUp.MB_Activate);
	}
	private: System::Void btnMoveArmDown_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::MoveJackDown));
		ClearTCManData(s_TurnOverManual.MTO_MoveJackUp.MB_Activate);
	}
	private: System::Void btnArmVacuum_ON_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::ArmVacuum) + " ON");
		SetTCManData(s_TurnOverManual.MTO_ArmVacuum.MB_Activate);
	}
	private: System::Void btnArmVacuum_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::ArmVacuum) + " OFF");
		ClearTCManData(s_TurnOverManual.MTO_ArmVacuum.MB_Activate);
	}
	private: System::Void btnFixVacuum_ON_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::FixVacuum) + " ON");
		SetTCManData(s_TurnOverManual.MTO_FixVacuum.MB_Activate);
	}
	private: System::Void btnFixVacuum_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::FixVacuum) + " OFF");
		ClearTCManData(s_TurnOverManual.MTO_FixVacuum.MB_Activate);
	}
	private: System::Void TurnOverManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
		gbAxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::Arm) + "  ";

		tabControl->TabPages[0]->Text = TUtilities::pS_LoadString(TextIndex::Turnover);

		lblFixVacuum->Text = TUtilities::pS_LoadString(TextIndex::FixVacuum);
		lblArmVacuum->Text = TUtilities::pS_LoadString(TextIndex::ArmVacuum);
		lblJack->Text = TUtilities::pS_LoadString(TextIndex::Jack);
		lblAspiration->Text = TUtilities::pS_LoadString(TextIndex::Aspiration);
		lblCleaningBlow->Text = TUtilities::pS_LoadString(TextIndex::Blowing);

		pT_Drive->ReloadComponent();
		pT_Drive->SetPositionName(0, TUtilities::pS_LoadString(TextIndex::Take));
		pT_Drive->SetPositionName(1, TUtilities::pS_LoadString(TextIndex::Drop));
		pT_Drive->SetDriveName(tabControl->TabPages[0]->Text, "");
	}
	private: System::Void btnAspiration_ON_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Aspiration) + "ON");
		SetTCManData(s_LoaderManual.ML_AspirationBrush.MB_Activate);
	}
	private: System::Void btnAspiration_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Aspiration) + "OFF");
		ClearTCManData(s_LoaderManual.ML_AspirationBrush.MB_Activate);
	}
	private: System::Void btnBlow_ON_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Blowing) + "ON");
		SetTCManData(s_TurnOverManual.MTO_ActivateCleaningBlow.MB_Activate);
	}
	private: System::Void btnBlow_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
		TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Blowing) + "OFF");
		ClearTCManData(s_TurnOverManual.MTO_ActivateCleaningBlow.MB_Activate);
	}
			 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
	};
}