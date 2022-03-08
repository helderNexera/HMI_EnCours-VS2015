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
	public ref class UtilitiesManualScreen : public System::Windows::Forms::Form
	{
	public:
		UtilitiesManualScreen()
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::UtilitiesManualScreen::OnUserLevelChanged);
		}
	private: System::Windows::Forms::Label^  lblPower;
	private: MondemaComponents::Led^  ledPower;
	private: System::Windows::Forms::CheckBox^  btnVacuum_OFF;
	private: System::Windows::Forms::CheckBox^  btnVacuum_ON;
	private: System::Windows::Forms::Label^  lblVacuum;
	private: System::Windows::Forms::CheckBox^  btnAspiration_OFF;
	private: System::Windows::Forms::CheckBox^  btnAspiration_ON;
	private: MondemaComponents::Led^  ledVacuum;
	private: MondemaComponents::Led^  ledAirPressure;
	private: System::Windows::Forms::Label^  lblVacuumOk;
	private: System::Windows::Forms::Label^  lblAirPressureOk;
	private: System::Windows::Forms::Label^  lbl48VOk;
	private: MondemaComponents::Led^  led48V;
	private: System::Windows::Forms::Label^  lbl24VOk;
	private: MondemaComponents::Led^  led24V;
	private: System::Windows::Forms::Label^  lblDriveOn;
	private: MondemaComponents::Led^  ledDrive;
	private: System::Windows::Forms::Button^  btnResetVacuumUseTime;
	private: System::Windows::Forms::TextBox^  tbVacuumUseTime;
	private: System::Windows::Forms::Button^  btnResetAspirationUseTime;
	private: System::Windows::Forms::TextBox^  tbAspirationUseTime;
	private: MondemaComponents::Led^  ledAspiration;
	private: System::Windows::Forms::Label^  lblAspirationOk;
	private: MondemaComponents::Led^  ledAspirationOn;
	private: System::Windows::Forms::Label^  lblAspirationIsOn;
	private: System::Windows::Forms::Label^  lblAspiration;
	public:

			 // Our specific functions
	private:
	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~UtilitiesManualScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
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
			this->ledAspirationOn = (gcnew MondemaComponents::Led());
			this->lblAspirationIsOn = (gcnew System::Windows::Forms::Label());
			this->ledAspiration = (gcnew MondemaComponents::Led());
			this->lblAspirationOk = (gcnew System::Windows::Forms::Label());
			this->btnResetVacuumUseTime = (gcnew System::Windows::Forms::Button());
			this->tbVacuumUseTime = (gcnew System::Windows::Forms::TextBox());
			this->btnResetAspirationUseTime = (gcnew System::Windows::Forms::Button());
			this->tbAspirationUseTime = (gcnew System::Windows::Forms::TextBox());
			this->ledVacuum = (gcnew MondemaComponents::Led());
			this->ledAirPressure = (gcnew MondemaComponents::Led());
			this->lblVacuumOk = (gcnew System::Windows::Forms::Label());
			this->lblAirPressureOk = (gcnew System::Windows::Forms::Label());
			this->lbl48VOk = (gcnew System::Windows::Forms::Label());
			this->led48V = (gcnew MondemaComponents::Led());
			this->lbl24VOk = (gcnew System::Windows::Forms::Label());
			this->led24V = (gcnew MondemaComponents::Led());
			this->lblDriveOn = (gcnew System::Windows::Forms::Label());
			this->ledDrive = (gcnew MondemaComponents::Led());
			this->btnVacuum_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnVacuum_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblVacuum = (gcnew System::Windows::Forms::Label());
			this->btnAspiration_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnAspiration_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblAspiration = (gcnew System::Windows::Forms::Label());
			this->lblPower = (gcnew System::Windows::Forms::Label());
			this->ledPower = (gcnew MondemaComponents::Led());
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
			this->tabPage1->Controls->Add(this->ledAspirationOn);
			this->tabPage1->Controls->Add(this->lblAspirationIsOn);
			this->tabPage1->Controls->Add(this->ledAspiration);
			this->tabPage1->Controls->Add(this->lblAspirationOk);
			this->tabPage1->Controls->Add(this->btnResetVacuumUseTime);
			this->tabPage1->Controls->Add(this->tbVacuumUseTime);
			this->tabPage1->Controls->Add(this->btnResetAspirationUseTime);
			this->tabPage1->Controls->Add(this->tbAspirationUseTime);
			this->tabPage1->Controls->Add(this->ledVacuum);
			this->tabPage1->Controls->Add(this->ledAirPressure);
			this->tabPage1->Controls->Add(this->lblVacuumOk);
			this->tabPage1->Controls->Add(this->lblAirPressureOk);
			this->tabPage1->Controls->Add(this->lbl48VOk);
			this->tabPage1->Controls->Add(this->led48V);
			this->tabPage1->Controls->Add(this->lbl24VOk);
			this->tabPage1->Controls->Add(this->led24V);
			this->tabPage1->Controls->Add(this->lblDriveOn);
			this->tabPage1->Controls->Add(this->ledDrive);
			this->tabPage1->Controls->Add(this->btnVacuum_OFF);
			this->tabPage1->Controls->Add(this->btnVacuum_ON);
			this->tabPage1->Controls->Add(this->lblVacuum);
			this->tabPage1->Controls->Add(this->btnAspiration_OFF);
			this->tabPage1->Controls->Add(this->btnAspiration_ON);
			this->tabPage1->Controls->Add(this->lblAspiration);
			this->tabPage1->Controls->Add(this->lblPower);
			this->tabPage1->Controls->Add(this->ledPower);
			this->tabPage1->Location = System::Drawing::Point(4, 49);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1570, 842);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// ledAspirationOn
			// 
			this->ledAspirationOn->Location = System::Drawing::Point(332, 572);
			this->ledAspirationOn->Margin = System::Windows::Forms::Padding(155, 99, 155, 99);
			this->ledAspirationOn->Name = L"ledAspirationOn";
			this->ledAspirationOn->Size = System::Drawing::Size(30, 30);
			this->ledAspirationOn->TabIndex = 141;
			this->ledAspirationOn->Tag = L"1";
			// 
			// lblAspirationIsOn
			// 
			this->lblAspirationIsOn->AutoSize = true;
			this->lblAspirationIsOn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAspirationIsOn->Location = System::Drawing::Point(38, 572);
			this->lblAspirationIsOn->Name = L"lblAspirationIsOn";
			this->lblAspirationIsOn->Size = System::Drawing::Size(176, 29);
			this->lblAspirationIsOn->TabIndex = 140;
			this->lblAspirationIsOn->Tag = L"1";
			this->lblAspirationIsOn->Text = L"Aspiration ON";
			// 
			// ledAspiration
			// 
			this->ledAspiration->Location = System::Drawing::Point(332, 527);
			this->ledAspiration->Margin = System::Windows::Forms::Padding(93, 65, 93, 65);
			this->ledAspiration->Name = L"ledAspiration";
			this->ledAspiration->Size = System::Drawing::Size(30, 30);
			this->ledAspiration->TabIndex = 139;
			this->ledAspiration->Tag = L"1";
			// 
			// lblAspirationOk
			// 
			this->lblAspirationOk->AutoSize = true;
			this->lblAspirationOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAspirationOk->Location = System::Drawing::Point(36, 527);
			this->lblAspirationOk->Name = L"lblAspirationOk";
			this->lblAspirationOk->Size = System::Drawing::Size(130, 29);
			this->lblAspirationOk->TabIndex = 138;
			this->lblAspirationOk->Tag = L"1";
			this->lblAspirationOk->Text = L"Aspiration";
			// 
			// btnResetVacuumUseTime
			// 
			this->btnResetVacuumUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnResetVacuumUseTime->Location = System::Drawing::Point(821, 128);
			this->btnResetVacuumUseTime->Name = L"btnResetVacuumUseTime";
			this->btnResetVacuumUseTime->Size = System::Drawing::Size(126, 39);
			this->btnResetVacuumUseTime->TabIndex = 137;
			this->btnResetVacuumUseTime->Tag = L"2";
			this->btnResetVacuumUseTime->Text = L"RESET";
			this->btnResetVacuumUseTime->UseVisualStyleBackColor = true;
			this->btnResetVacuumUseTime->Click += gcnew System::EventHandler(this, &UtilitiesManualScreen::btnResetVacuumUseTime_Click);
			// 
			// tbVacuumUseTime
			// 
			this->tbVacuumUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbVacuumUseTime->Location = System::Drawing::Point(618, 128);
			this->tbVacuumUseTime->Name = L"tbVacuumUseTime";
			this->tbVacuumUseTime->ReadOnly = true;
			this->tbVacuumUseTime->Size = System::Drawing::Size(162, 35);
			this->tbVacuumUseTime->TabIndex = 136;
			this->tbVacuumUseTime->Tag = L"1";
			this->tbVacuumUseTime->Text = L"0";
			this->tbVacuumUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// btnResetAspirationUseTime
			// 
			this->btnResetAspirationUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnResetAspirationUseTime->Location = System::Drawing::Point(821, 33);
			this->btnResetAspirationUseTime->Name = L"btnResetAspirationUseTime";
			this->btnResetAspirationUseTime->Size = System::Drawing::Size(126, 39);
			this->btnResetAspirationUseTime->TabIndex = 135;
			this->btnResetAspirationUseTime->Tag = L"2";
			this->btnResetAspirationUseTime->Text = L"RESET";
			this->btnResetAspirationUseTime->UseVisualStyleBackColor = true;
			this->btnResetAspirationUseTime->Click += gcnew System::EventHandler(this, &UtilitiesManualScreen::btnResetAspirationUseTime_Click);
			// 
			// tbAspirationUseTime
			// 
			this->tbAspirationUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbAspirationUseTime->Location = System::Drawing::Point(618, 33);
			this->tbAspirationUseTime->Name = L"tbAspirationUseTime";
			this->tbAspirationUseTime->ReadOnly = true;
			this->tbAspirationUseTime->Size = System::Drawing::Size(162, 35);
			this->tbAspirationUseTime->TabIndex = 133;
			this->tbAspirationUseTime->Tag = L"1";
			this->tbAspirationUseTime->Text = L"0";
			this->tbAspirationUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// ledVacuum
			// 
			this->ledVacuum->Location = System::Drawing::Point(332, 480);
			this->ledVacuum->Margin = System::Windows::Forms::Padding(56, 42, 56, 42);
			this->ledVacuum->Name = L"ledVacuum";
			this->ledVacuum->Size = System::Drawing::Size(30, 30);
			this->ledVacuum->TabIndex = 131;
			this->ledVacuum->Tag = L"1";
			// 
			// ledAirPressure
			// 
			this->ledAirPressure->Location = System::Drawing::Point(332, 435);
			this->ledAirPressure->Margin = System::Windows::Forms::Padding(33, 27, 33, 27);
			this->ledAirPressure->Name = L"ledAirPressure";
			this->ledAirPressure->Size = System::Drawing::Size(30, 30);
			this->ledAirPressure->TabIndex = 130;
			this->ledAirPressure->Tag = L"1";
			// 
			// lblVacuumOk
			// 
			this->lblVacuumOk->AutoSize = true;
			this->lblVacuumOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuumOk->Location = System::Drawing::Point(38, 480);
			this->lblVacuumOk->Name = L"lblVacuumOk";
			this->lblVacuumOk->Size = System::Drawing::Size(105, 29);
			this->lblVacuumOk->TabIndex = 129;
			this->lblVacuumOk->Tag = L"1";
			this->lblVacuumOk->Text = L"Vacuum";
			// 
			// lblAirPressureOk
			// 
			this->lblAirPressureOk->AutoSize = true;
			this->lblAirPressureOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAirPressureOk->Location = System::Drawing::Point(38, 435);
			this->lblAirPressureOk->Name = L"lblAirPressureOk";
			this->lblAirPressureOk->Size = System::Drawing::Size(157, 29);
			this->lblAirPressureOk->TabIndex = 128;
			this->lblAirPressureOk->Tag = L"1";
			this->lblAirPressureOk->Text = L"Air Pressure";
			// 
			// lbl48VOk
			// 
			this->lbl48VOk->AutoSize = true;
			this->lbl48VOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl48VOk->Location = System::Drawing::Point(38, 390);
			this->lbl48VOk->Name = L"lbl48VOk";
			this->lbl48VOk->Size = System::Drawing::Size(64, 29);
			this->lbl48VOk->TabIndex = 127;
			this->lbl48VOk->Tag = L"1";
			this->lbl48VOk->Text = L"48 V";
			// 
			// led48V
			// 
			this->led48V->Location = System::Drawing::Point(332, 390);
			this->led48V->Margin = System::Windows::Forms::Padding(20, 18, 20, 18);
			this->led48V->Name = L"led48V";
			this->led48V->Size = System::Drawing::Size(30, 30);
			this->led48V->TabIndex = 126;
			this->led48V->Tag = L"1";
			// 
			// lbl24VOk
			// 
			this->lbl24VOk->AutoSize = true;
			this->lbl24VOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl24VOk->Location = System::Drawing::Point(38, 345);
			this->lbl24VOk->Name = L"lbl24VOk";
			this->lbl24VOk->Size = System::Drawing::Size(64, 29);
			this->lbl24VOk->TabIndex = 125;
			this->lbl24VOk->Tag = L"1";
			this->lbl24VOk->Text = L"24 V";
			// 
			// led24V
			// 
			this->led24V->Location = System::Drawing::Point(332, 345);
			this->led24V->Margin = System::Windows::Forms::Padding(20, 18, 20, 18);
			this->led24V->Name = L"led24V";
			this->led24V->Size = System::Drawing::Size(30, 30);
			this->led24V->TabIndex = 124;
			this->led24V->Tag = L"1";
			// 
			// lblDriveOn
			// 
			this->lblDriveOn->AutoSize = true;
			this->lblDriveOn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDriveOn->Location = System::Drawing::Point(38, 300);
			this->lblDriveOn->Name = L"lblDriveOn";
			this->lblDriveOn->Size = System::Drawing::Size(108, 29);
			this->lblDriveOn->TabIndex = 123;
			this->lblDriveOn->Tag = L"1";
			this->lblDriveOn->Text = L"DriveOn";
			// 
			// ledDrive
			// 
			this->ledDrive->Location = System::Drawing::Point(332, 300);
			this->ledDrive->Margin = System::Windows::Forms::Padding(8);
			this->ledDrive->Name = L"ledDrive";
			this->ledDrive->Size = System::Drawing::Size(30, 30);
			this->ledDrive->TabIndex = 122;
			this->ledDrive->Tag = L"1";
			// 
			// btnVacuum_OFF
			// 
			this->btnVacuum_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum_OFF->Location = System::Drawing::Point(519, 108);
			this->btnVacuum_OFF->Name = L"btnVacuum_OFF";
			this->btnVacuum_OFF->Size = System::Drawing::Size(90, 90);
			this->btnVacuum_OFF->TabIndex = 121;
			this->btnVacuum_OFF->Tag = L"1";
			this->btnVacuum_OFF->Text = L"OFF";
			this->btnVacuum_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum_OFF->UseVisualStyleBackColor = true;
			this->btnVacuum_OFF->Click += gcnew System::EventHandler(this, &UtilitiesManualScreen::btnVacuum_OFF_Click);
			// 
			// btnVacuum_ON
			// 
			this->btnVacuum_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum_ON->Location = System::Drawing::Point(420, 108);
			this->btnVacuum_ON->Name = L"btnVacuum_ON";
			this->btnVacuum_ON->Size = System::Drawing::Size(90, 90);
			this->btnVacuum_ON->TabIndex = 120;
			this->btnVacuum_ON->Tag = L"1";
			this->btnVacuum_ON->Text = L"ON";
			this->btnVacuum_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum_ON->UseVisualStyleBackColor = true;
			this->btnVacuum_ON->Click += gcnew System::EventHandler(this, &UtilitiesManualScreen::btnVacuum_ON_Click);
			// 
			// lblVacuum
			// 
			this->lblVacuum->AutoSize = true;
			this->lblVacuum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuum->Location = System::Drawing::Point(38, 137);
			this->lblVacuum->Name = L"lblVacuum";
			this->lblVacuum->Size = System::Drawing::Size(105, 29);
			this->lblVacuum->TabIndex = 119;
			this->lblVacuum->Tag = L"1";
			this->lblVacuum->Text = L"Vacuum";
			// 
			// btnAspiration_OFF
			// 
			this->btnAspiration_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAspiration_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAspiration_OFF->Location = System::Drawing::Point(519, 9);
			this->btnAspiration_OFF->Name = L"btnAspiration_OFF";
			this->btnAspiration_OFF->Size = System::Drawing::Size(90, 90);
			this->btnAspiration_OFF->TabIndex = 118;
			this->btnAspiration_OFF->Tag = L"1";
			this->btnAspiration_OFF->Text = L"OFF";
			this->btnAspiration_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAspiration_OFF->UseVisualStyleBackColor = true;
			this->btnAspiration_OFF->Click += gcnew System::EventHandler(this, &UtilitiesManualScreen::btnAspiration_OFF_Click);
			// 
			// btnAspiration_ON
			// 
			this->btnAspiration_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAspiration_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAspiration_ON->Location = System::Drawing::Point(420, 9);
			this->btnAspiration_ON->Name = L"btnAspiration_ON";
			this->btnAspiration_ON->Size = System::Drawing::Size(90, 90);
			this->btnAspiration_ON->TabIndex = 117;
			this->btnAspiration_ON->Tag = L"1";
			this->btnAspiration_ON->Text = L"ON";
			this->btnAspiration_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAspiration_ON->UseVisualStyleBackColor = true;
			this->btnAspiration_ON->Click += gcnew System::EventHandler(this, &UtilitiesManualScreen::btnAspiration_ON_Click);
			// 
			// lblAspiration
			// 
			this->lblAspiration->AutoSize = true;
			this->lblAspiration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAspiration->Location = System::Drawing::Point(38, 38);
			this->lblAspiration->Name = L"lblAspiration";
			this->lblAspiration->Size = System::Drawing::Size(130, 29);
			this->lblAspiration->TabIndex = 116;
			this->lblAspiration->Tag = L"1";
			this->lblAspiration->Text = L"Aspiration";
			// 
			// lblPower
			// 
			this->lblPower->AutoSize = true;
			this->lblPower->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPower->Location = System::Drawing::Point(38, 256);
			this->lblPower->Name = L"lblPower";
			this->lblPower->Size = System::Drawing::Size(88, 29);
			this->lblPower->TabIndex = 113;
			this->lblPower->Tag = L"1";
			this->lblPower->Text = L"Power";
			// 
			// ledPower
			// 
			this->ledPower->Location = System::Drawing::Point(332, 255);
			this->ledPower->Margin = System::Windows::Forms::Padding(5);
			this->ledPower->Name = L"ledPower";
			this->ledPower->Size = System::Drawing::Size(30, 30);
			this->ledPower->TabIndex = 112;
			this->ledPower->Tag = L"1";
			// 
			// UtilitiesManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"UtilitiesManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &UtilitiesManualScreen::UtilitiesManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void ShowOsk_Click(System::Object^  sender, System::EventArgs^  e) {
		TUtilities::ShowOSK();
	}

	private: System::Void UtilitiesManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			tabPage1->Text = TUtilities::pS_LoadString(TextIndex::Utilities);
			lblAspiration->Text = TUtilities::pS_LoadString(TextIndex::Aspiration)+ " [h]";
			lblVacuum->Text = TUtilities::pS_LoadString(TextIndex::Vacuum)+ " [h]";
			lblAirPressureOk->Text = TUtilities::pS_LoadString(TextIndex::AirPressure) + " OK";
			lblVacuumOk->Text = TUtilities::pS_LoadString(TextIndex::Vacuum) + " OK";
			lblAspirationIsOn->Text = TUtilities::pS_LoadString(TextIndex::Aspiration) + " ON";
			lblAspirationOk->Text = TUtilities::pS_LoadString(TextIndex::Aspiration) + " OK";
		 }
private: System::Void btnAspiration_ON_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Aspiration) + "ON");
	SetTCManData(s_UtilitiesManual.MU_Aspiration.MB_Activate);
}
private: System::Void btnAspiration_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Aspiration) + "OFF");
	ClearTCManData(s_UtilitiesManual.MU_Aspiration.MB_Activate);

}
private: System::Void btnVacuum_ON_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Vacuum) + "ON");
	SetTCManData(s_UtilitiesManual.MU_Vacuum.MB_Activate);

}
private: System::Void btnVacuum_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Vacuum) + "OFF");
	ClearTCManData(s_UtilitiesManual.MU_Vacuum.MB_Activate);
}
private: System::Void btnResetAspirationUseTime_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::AspirationUseTime));
	SetTCManData(s_UtilitiesManual.MU_ResetAspirationUseTime.MB_Activate);
}
private: System::Void btnResetVacuumUseTime_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::VacuumUseTime));
	SetTCManData(s_UtilitiesManual.MU_ResetVacuumUseTime.MB_Activate);

}
		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
};
}