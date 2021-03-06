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
	public ref class BarrelManualScreen : public System::Windows::Forms::Form
	{
	public:
		BarrelManualScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_Drive = gcnew DriveComponent(this->gbAxis);
			pT_Drive->UsePosition(0,TUtilities::pS_LoadString(TextIndex::Take));
			pT_Drive->UsePosition(1, TUtilities::pS_LoadString(TextIndex::StickCheck));
			pT_Drive->SetDriveData(TUtilities::pS_LoadString(TextIndex::Rotation),GetTCManualOffset(s_BarrelManual.MB_Axis),L"");
			pT_Drive->SetDrivePosData(0,GetTCManualOffset(s_BarrelManual.MB_AxisTakenPos));
			pT_Drive->SetDrivePosData(1, GetTCManualOffset(s_BarrelManual.MB_AxisCheckPos));
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::BarrelManualScreen::OnUserLevelChanged);
		}
	private: System::Windows::Forms::CheckBox^  btnIndexDown;
	private: System::Windows::Forms::CheckBox^  btnIndexUp;
	private: System::Windows::Forms::Label^  lblIndex;
	private: System::Windows::Forms::Button^  btnTakenMove1Step;
	private: System::Windows::Forms::Button^  btnCheckMove1Step;
	private: System::Windows::Forms::Label^  lblMove1Step;
	private: System::Windows::Forms::Button^  btnTakenMoveSectionD;
	private: System::Windows::Forms::Label^  lblMoveSectionD;
	private: System::Windows::Forms::Button^  btnTakenMoveSectionC;
	private: System::Windows::Forms::Label^  lblMoveSectionC;
	private: System::Windows::Forms::Button^  btnTakenMoveSectionB;
	private: System::Windows::Forms::Label^  lblMoveSectionB;
	private: System::Windows::Forms::Button^  btnTakenMoveSectionA;
	private: System::Windows::Forms::Label^  lblMoveSectionA;
	private: System::Windows::Forms::Label^  lblPresence;
	private: System::Windows::Forms::Label^  lblPosition;
	private: System::Windows::Forms::Button^  btnCheckMoveSectionA;
	private: System::Windows::Forms::Button^  btnCheckMoveSectionB;
	private: System::Windows::Forms::Button^  btnCheckMoveSectionC;
	private: System::Windows::Forms::Button^  btnCheckMoveSectionD;
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
		~BarrelManualScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::ImageList^  SensorImages;
	private: System::Windows::Forms::CheckBox^  btnJackDown;
	private: System::Windows::Forms::CheckBox^  btnJackUp;
	private: Led^  osStickPresent;
	private: System::Windows::Forms::Label^  lblJack;
	private: System::Windows::Forms::GroupBox^  gbAxis;
	private: System::ComponentModel::IContainer^  components;
	protected: 
	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BarrelManualScreen::typeid));
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->lblPresence = (gcnew System::Windows::Forms::Label());
			this->lblPosition = (gcnew System::Windows::Forms::Label());
			this->btnTakenMoveSectionD = (gcnew System::Windows::Forms::Button());
			this->lblMoveSectionD = (gcnew System::Windows::Forms::Label());
			this->btnTakenMoveSectionC = (gcnew System::Windows::Forms::Button());
			this->lblMoveSectionC = (gcnew System::Windows::Forms::Label());
			this->btnTakenMoveSectionB = (gcnew System::Windows::Forms::Button());
			this->lblMoveSectionB = (gcnew System::Windows::Forms::Label());
			this->btnTakenMoveSectionA = (gcnew System::Windows::Forms::Button());
			this->lblMoveSectionA = (gcnew System::Windows::Forms::Label());
			this->btnTakenMove1Step = (gcnew System::Windows::Forms::Button());
			this->btnCheckMove1Step = (gcnew System::Windows::Forms::Button());
			this->lblMove1Step = (gcnew System::Windows::Forms::Label());
			this->btnIndexDown = (gcnew System::Windows::Forms::CheckBox());
			this->btnIndexUp = (gcnew System::Windows::Forms::CheckBox());
			this->lblIndex = (gcnew System::Windows::Forms::Label());
			this->gbAxis = (gcnew System::Windows::Forms::GroupBox());
			this->btnJackDown = (gcnew System::Windows::Forms::CheckBox());
			this->btnJackUp = (gcnew System::Windows::Forms::CheckBox());
			this->osStickPresent = (gcnew MondemaComponents::Led());
			this->lblJack = (gcnew System::Windows::Forms::Label());
			this->btnCheckMoveSectionA = (gcnew System::Windows::Forms::Button());
			this->btnCheckMoveSectionB = (gcnew System::Windows::Forms::Button());
			this->btnCheckMoveSectionC = (gcnew System::Windows::Forms::Button());
			this->btnCheckMoveSectionD = (gcnew System::Windows::Forms::Button());
			this->SensorImages = (gcnew System::Windows::Forms::ImageList(this->components));
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tabControl->ItemSize = System::Drawing::Size(135, 45);
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1578, 895);
			this->tabControl->TabIndex = 2;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::Color::White;
			this->tabPage1->Controls->Add(this->lblPresence);
			this->tabPage1->Controls->Add(this->lblPosition);
			this->tabPage1->Controls->Add(this->btnTakenMoveSectionD);
			this->tabPage1->Controls->Add(this->lblMoveSectionD);
			this->tabPage1->Controls->Add(this->btnTakenMoveSectionC);
			this->tabPage1->Controls->Add(this->lblMoveSectionC);
			this->tabPage1->Controls->Add(this->btnTakenMoveSectionB);
			this->tabPage1->Controls->Add(this->lblMoveSectionB);
			this->tabPage1->Controls->Add(this->btnTakenMoveSectionA);
			this->tabPage1->Controls->Add(this->lblMoveSectionA);
			this->tabPage1->Controls->Add(this->btnTakenMove1Step);
			this->tabPage1->Controls->Add(this->btnCheckMove1Step);
			this->tabPage1->Controls->Add(this->lblMove1Step);
			this->tabPage1->Controls->Add(this->btnIndexDown);
			this->tabPage1->Controls->Add(this->btnIndexUp);
			this->tabPage1->Controls->Add(this->lblIndex);
			this->tabPage1->Controls->Add(this->gbAxis);
			this->tabPage1->Controls->Add(this->btnJackDown);
			this->tabPage1->Controls->Add(this->btnJackUp);
			this->tabPage1->Controls->Add(this->osStickPresent);
			this->tabPage1->Controls->Add(this->lblJack);
			this->tabPage1->Controls->Add(this->btnCheckMoveSectionA);
			this->tabPage1->Controls->Add(this->btnCheckMoveSectionB);
			this->tabPage1->Controls->Add(this->btnCheckMoveSectionC);
			this->tabPage1->Controls->Add(this->btnCheckMoveSectionD);
			this->tabPage1->Location = System::Drawing::Point(4, 49);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1570, 842);
			this->tabPage1->TabIndex = 0;
			// 
			// lblPresence
			// 
			this->lblPresence->AutoSize = true;
			this->lblPresence->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPresence->Location = System::Drawing::Point(760, 29);
			this->lblPresence->Name = L"lblPresence";
			this->lblPresence->Size = System::Drawing::Size(124, 29);
			this->lblPresence->TabIndex = 115;
			this->lblPresence->Tag = L"1";
			this->lblPresence->Text = L"Présence";
			// 
			// lblPosition
			// 
			this->lblPosition->AutoSize = true;
			this->lblPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPosition->Location = System::Drawing::Point(760, 89);
			this->lblPosition->Name = L"lblPosition";
			this->lblPosition->Size = System::Drawing::Size(108, 29);
			this->lblPosition->TabIndex = 115;
			this->lblPosition->Tag = L"1";
			this->lblPosition->Text = L"Position";
			// 
			// btnTakenMoveSectionD
			// 
			this->btnTakenMoveSectionD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnTakenMoveSectionD->Location = System::Drawing::Point(365, 620);
			this->btnTakenMoveSectionD->Name = L"btnTakenMoveSectionD";
			this->btnTakenMoveSectionD->Size = System::Drawing::Size(120, 90);
			this->btnTakenMoveSectionD->TabIndex = 114;
			this->btnTakenMoveSectionD->Tag = L"1";
			this->btnTakenMoveSectionD->Text = L"GO";
			this->btnTakenMoveSectionD->UseVisualStyleBackColor = true;
			this->btnTakenMoveSectionD->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnTakenMoveSectionD_Click);
			// 
			// lblMoveSectionD
			// 
			this->lblMoveSectionD->AutoSize = true;
			this->lblMoveSectionD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveSectionD->Location = System::Drawing::Point(95, 648);
			this->lblMoveSectionD->Name = L"lblMoveSectionD";
			this->lblMoveSectionD->Size = System::Drawing::Size(0, 29);
			this->lblMoveSectionD->TabIndex = 113;
			this->lblMoveSectionD->Tag = L"1";
			// 
			// btnTakenMoveSectionC
			// 
			this->btnTakenMoveSectionC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnTakenMoveSectionC->Location = System::Drawing::Point(365, 521);
			this->btnTakenMoveSectionC->Name = L"btnTakenMoveSectionC";
			this->btnTakenMoveSectionC->Size = System::Drawing::Size(120, 90);
			this->btnTakenMoveSectionC->TabIndex = 112;
			this->btnTakenMoveSectionC->Tag = L"1";
			this->btnTakenMoveSectionC->Text = L"GO";
			this->btnTakenMoveSectionC->UseVisualStyleBackColor = true;
			this->btnTakenMoveSectionC->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnTakenMoveSectionC_Click);
			// 
			// lblMoveSectionC
			// 
			this->lblMoveSectionC->AutoSize = true;
			this->lblMoveSectionC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveSectionC->Location = System::Drawing::Point(95, 549);
			this->lblMoveSectionC->Name = L"lblMoveSectionC";
			this->lblMoveSectionC->Size = System::Drawing::Size(0, 29);
			this->lblMoveSectionC->TabIndex = 111;
			this->lblMoveSectionC->Tag = L"1";
			// 
			// btnTakenMoveSectionB
			// 
			this->btnTakenMoveSectionB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnTakenMoveSectionB->Location = System::Drawing::Point(365, 422);
			this->btnTakenMoveSectionB->Name = L"btnTakenMoveSectionB";
			this->btnTakenMoveSectionB->Size = System::Drawing::Size(120, 90);
			this->btnTakenMoveSectionB->TabIndex = 110;
			this->btnTakenMoveSectionB->Tag = L"1";
			this->btnTakenMoveSectionB->Text = L"GO";
			this->btnTakenMoveSectionB->UseVisualStyleBackColor = true;
			this->btnTakenMoveSectionB->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnTakenMoveSectionB_Click);
			// 
			// lblMoveSectionB
			// 
			this->lblMoveSectionB->AutoSize = true;
			this->lblMoveSectionB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveSectionB->Location = System::Drawing::Point(95, 450);
			this->lblMoveSectionB->Name = L"lblMoveSectionB";
			this->lblMoveSectionB->Size = System::Drawing::Size(0, 29);
			this->lblMoveSectionB->TabIndex = 109;
			this->lblMoveSectionB->Tag = L"1";
			// 
			// btnTakenMoveSectionA
			// 
			this->btnTakenMoveSectionA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnTakenMoveSectionA->Location = System::Drawing::Point(365, 323);
			this->btnTakenMoveSectionA->Name = L"btnTakenMoveSectionA";
			this->btnTakenMoveSectionA->Size = System::Drawing::Size(120, 90);
			this->btnTakenMoveSectionA->TabIndex = 108;
			this->btnTakenMoveSectionA->Tag = L"1";
			this->btnTakenMoveSectionA->Text = L"GO";
			this->btnTakenMoveSectionA->UseVisualStyleBackColor = true;
			this->btnTakenMoveSectionA->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnTakenMoveSectionA_Click);
			// 
			// lblMoveSectionA
			// 
			this->lblMoveSectionA->AutoSize = true;
			this->lblMoveSectionA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveSectionA->Location = System::Drawing::Point(95, 351);
			this->lblMoveSectionA->Name = L"lblMoveSectionA";
			this->lblMoveSectionA->Size = System::Drawing::Size(0, 29);
			this->lblMoveSectionA->TabIndex = 107;
			this->lblMoveSectionA->Tag = L"1";
			// 
			// btnTakenMove1Step
			// 
			this->btnTakenMove1Step->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnTakenMove1Step->Location = System::Drawing::Point(365, 224);
			this->btnTakenMove1Step->Name = L"btnTakenMove1Step";
			this->btnTakenMove1Step->Size = System::Drawing::Size(120, 90);
			this->btnTakenMove1Step->TabIndex = 106;
			this->btnTakenMove1Step->Tag = L"1";
			this->btnTakenMove1Step->Text = L"GO";
			this->btnTakenMove1Step->UseVisualStyleBackColor = true;
			this->btnTakenMove1Step->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnTakenMove1Step_Click);
			// 
			// btnCheckMove1Step
			// 
			this->btnCheckMove1Step->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCheckMove1Step->Location = System::Drawing::Point(500, 224);
			this->btnCheckMove1Step->Name = L"btnCheckMove1Step";
			this->btnCheckMove1Step->Size = System::Drawing::Size(180, 90);
			this->btnCheckMove1Step->TabIndex = 106;
			this->btnCheckMove1Step->Tag = L"1";
			this->btnCheckMove1Step->Text = L"GO";
			this->btnCheckMove1Step->UseVisualStyleBackColor = true;
			this->btnCheckMove1Step->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnCheckMove1Step_Click);
			// 
			// lblMove1Step
			// 
			this->lblMove1Step->AutoSize = true;
			this->lblMove1Step->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMove1Step->Location = System::Drawing::Point(95, 252);
			this->lblMove1Step->Name = L"lblMove1Step";
			this->lblMove1Step->Size = System::Drawing::Size(0, 29);
			this->lblMove1Step->TabIndex = 105;
			this->lblMove1Step->Tag = L"1";
			// 
			// btnIndexDown
			// 
			this->btnIndexDown->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnIndexDown->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnIndexDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnIndexDown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnIndexDown.Image")));
			this->btnIndexDown->Location = System::Drawing::Point(464, 126);
			this->btnIndexDown->Name = L"btnIndexDown";
			this->btnIndexDown->Size = System::Drawing::Size(90, 90);
			this->btnIndexDown->TabIndex = 99;
			this->btnIndexDown->Tag = L"1";
			this->btnIndexDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnIndexDown->UseVisualStyleBackColor = false;
			this->btnIndexDown->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnIndexDown_Click);
			// 
			// btnIndexUp
			// 
			this->btnIndexUp->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnIndexUp->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnIndexUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnIndexUp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnIndexUp.Image")));
			this->btnIndexUp->Location = System::Drawing::Point(365, 126);
			this->btnIndexUp->Name = L"btnIndexUp";
			this->btnIndexUp->Size = System::Drawing::Size(90, 90);
			this->btnIndexUp->TabIndex = 98;
			this->btnIndexUp->Tag = L"1";
			this->btnIndexUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnIndexUp->UseVisualStyleBackColor = false;
			this->btnIndexUp->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnIndexUp_Click);
			// 
			// lblIndex
			// 
			this->lblIndex->AutoSize = true;
			this->lblIndex->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblIndex->Location = System::Drawing::Point(95, 164);
			this->lblIndex->Name = L"lblIndex";
			this->lblIndex->Size = System::Drawing::Size(0, 29);
			this->lblIndex->TabIndex = 97;
			this->lblIndex->Tag = L"1";
			// 
			// gbAxis
			// 
			this->gbAxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbAxis->Location = System::Drawing::Point(765, 224);
			this->gbAxis->Name = L"gbAxis";
			this->gbAxis->Size = System::Drawing::Size(728, 375);
			this->gbAxis->TabIndex = 96;
			this->gbAxis->TabStop = false;
			this->gbAxis->Tag = L"2";
			// 
			// btnJackDown
			// 
			this->btnJackDown->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnJackDown->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnJackDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnJackDown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnJackDown.Image")));
			this->btnJackDown->Location = System::Drawing::Point(464, 29);
			this->btnJackDown->Name = L"btnJackDown";
			this->btnJackDown->Size = System::Drawing::Size(90, 90);
			this->btnJackDown->TabIndex = 65;
			this->btnJackDown->Tag = L"1";
			this->btnJackDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnJackDown->UseVisualStyleBackColor = false;
			this->btnJackDown->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnJackDown_Click);
			// 
			// btnJackUp
			// 
			this->btnJackUp->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnJackUp->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnJackUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnJackUp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnJackUp.Image")));
			this->btnJackUp->Location = System::Drawing::Point(365, 29);
			this->btnJackUp->Name = L"btnJackUp";
			this->btnJackUp->Size = System::Drawing::Size(90, 90);
			this->btnJackUp->TabIndex = 64;
			this->btnJackUp->Tag = L"1";
			this->btnJackUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnJackUp->UseVisualStyleBackColor = false;
			this->btnJackUp->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnJackUp_Click);
			// 
			// osStickPresent
			// 
			this->osStickPresent->Location = System::Drawing::Point(1084, 29);
			this->osStickPresent->Name = L"osStickPresent";
			this->osStickPresent->Size = System::Drawing::Size(30, 30);
			this->osStickPresent->TabIndex = 116;
			this->osStickPresent->Tag = L"1";
			// 
			// lblJack
			// 
			this->lblJack->AutoSize = true;
			this->lblJack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblJack->Location = System::Drawing::Point(95, 66);
			this->lblJack->Name = L"lblJack";
			this->lblJack->Size = System::Drawing::Size(0, 29);
			this->lblJack->TabIndex = 63;
			this->lblJack->Tag = L"1";
			// 
			// btnCheckMoveSectionA
			// 
			this->btnCheckMoveSectionA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCheckMoveSectionA->Location = System::Drawing::Point(500, 323);
			this->btnCheckMoveSectionA->Name = L"btnCheckMoveSectionA";
			this->btnCheckMoveSectionA->Size = System::Drawing::Size(180, 90);
			this->btnCheckMoveSectionA->TabIndex = 108;
			this->btnCheckMoveSectionA->Tag = L"1";
			this->btnCheckMoveSectionA->Text = L"GO";
			this->btnCheckMoveSectionA->UseVisualStyleBackColor = true;
			this->btnCheckMoveSectionA->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnCheckMoveSectionA_Click);
			// 
			// btnCheckMoveSectionB
			// 
			this->btnCheckMoveSectionB->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCheckMoveSectionB->Location = System::Drawing::Point(500, 422);
			this->btnCheckMoveSectionB->Name = L"btnCheckMoveSectionB";
			this->btnCheckMoveSectionB->Size = System::Drawing::Size(180, 90);
			this->btnCheckMoveSectionB->TabIndex = 108;
			this->btnCheckMoveSectionB->Tag = L"1";
			this->btnCheckMoveSectionB->Text = L"GO";
			this->btnCheckMoveSectionB->UseVisualStyleBackColor = true;
			this->btnCheckMoveSectionB->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnCheckMoveSectionB_Click);
			// 
			// btnCheckMoveSectionC
			// 
			this->btnCheckMoveSectionC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnCheckMoveSectionC->Location = System::Drawing::Point(500, 521);
			this->btnCheckMoveSectionC->Name = L"btnCheckMoveSectionC";
			this->btnCheckMoveSectionC->Size = System::Drawing::Size(180, 90);
			this->btnCheckMoveSectionC->TabIndex = 108;
			this->btnCheckMoveSectionC->Tag = L"1";
			this->btnCheckMoveSectionC->Text = L"GO";
			this->btnCheckMoveSectionC->UseVisualStyleBackColor = true;
			this->btnCheckMoveSectionC->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnCheckMoveSectionC_Click);
			// 
			// btnCheckMoveSectionD
			// 
			this->btnCheckMoveSectionD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCheckMoveSectionD->Location = System::Drawing::Point(500, 620);
			this->btnCheckMoveSectionD->Name = L"btnCheckMoveSectionD";
			this->btnCheckMoveSectionD->Size = System::Drawing::Size(180, 90);
			this->btnCheckMoveSectionD->TabIndex = 108;
			this->btnCheckMoveSectionD->Tag = L"1";
			this->btnCheckMoveSectionD->Text = L"GO";
			this->btnCheckMoveSectionD->UseVisualStyleBackColor = true;
			this->btnCheckMoveSectionD->Click += gcnew System::EventHandler(this, &BarrelManualScreen::btnCheckMoveSectionD_Click);
			// 
			// SensorImages
			// 
			this->SensorImages->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"SensorImages.ImageStream")));
			this->SensorImages->TransparentColor = System::Drawing::Color::Transparent;
			this->SensorImages->Images->SetKeyName(0, L"GreenLed.jpg");
			this->SensorImages->Images->SetKeyName(1, L"RedLed.jpg");
			// 
			// BarrelManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"BarrelManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &BarrelManualScreen::BarrelManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void btnJackUp_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveJackUp));
			SetTCManData(s_BarrelManual.MB_MoveJackUp.MB_Activate);
		 }
private: System::Void btnJackDown_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveJackDown));
			ClearTCManData(s_BarrelManual.MB_MoveJackUp.MB_Activate);
		 }
private: System::Void BarrelManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			this->tabPage1->Text = TUtilities::pS_LoadString(TextIndex::Barrel);
			this->gbAxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::Axis) + L"  ";
			this->lblPresence->Text = TUtilities::pS_LoadString(TextIndex::StickCheck);
			this->lblPosition->Text = "";
			this->lblJack->Text = TUtilities::pS_LoadString(TextIndex::Jack);
			this->lblIndex->Text = TUtilities::pS_LoadString(TextIndex::Indexing);
			this->lblMove1Step->Text = TUtilities::pS_LoadString(TextIndex::Move1Step);
			this->lblMoveSectionA->Text = TUtilities::pS_LoadString(TextIndex::MoveSectionA);
			this->lblMoveSectionB->Text = TUtilities::pS_LoadString(TextIndex::MoveSectionB);
			this->lblMoveSectionC->Text = TUtilities::pS_LoadString(TextIndex::MoveSectionC);
			this->lblMoveSectionD->Text = TUtilities::pS_LoadString(TextIndex::MoveSectionD);

			this->btnTakenMove1Step->Text = TUtilities::pS_LoadString(TextIndex::Take);
			this->btnTakenMoveSectionA->Text = TUtilities::pS_LoadString(TextIndex::Take);
			this->btnTakenMoveSectionB->Text = TUtilities::pS_LoadString(TextIndex::Take);
			this->btnTakenMoveSectionC->Text = TUtilities::pS_LoadString(TextIndex::Take);
			this->btnTakenMoveSectionD->Text = TUtilities::pS_LoadString(TextIndex::Take);

			this->btnCheckMove1Step->Text = TUtilities::pS_LoadString(TextIndex::StickCheck);
			this->btnCheckMoveSectionA->Text = TUtilities::pS_LoadString(TextIndex::StickCheck);
			this->btnCheckMoveSectionB->Text = TUtilities::pS_LoadString(TextIndex::StickCheck);
			this->btnCheckMoveSectionC->Text = TUtilities::pS_LoadString(TextIndex::StickCheck);
			this->btnCheckMoveSectionD->Text = TUtilities::pS_LoadString(TextIndex::StickCheck);

			pT_Drive->ReloadComponent();
			pT_Drive->SetPositionName(0,TUtilities::pS_LoadString(TextIndex::Take));
			pT_Drive->SetPositionName(1, TUtilities::pS_LoadString(TextIndex::StickCheck));
			pT_Drive->SetDriveName(TUtilities::pS_LoadString(TextIndex::Rotation),L"");
		 }
private: System::Void btnIndexDown_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::Indexing) + " 0");
			ClearTCManData(s_BarrelManual.MB_IndexUp.MB_Activate);
		 }
private: System::Void btnIndexUp_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::Indexing) + " 1");
			SetTCManData(s_BarrelManual.MB_IndexUp.MB_Activate);
		 }
private: System::Void btnTakenMove1Step_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::Move1Step));
			SetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_Move1Step.MB_Activate);
		 }
private: System::Void btnCheckMove1Step_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::Move1Step));
	SetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_Move1Step.MB_Activate);
}
private: System::Void btnTakenMoveSectionA_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveSectionA));
	SetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_MoveSectionA.MB_Activate);
}
private: System::Void btnTakenMoveSectionB_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveSectionB));
	SetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_MoveSectionB.MB_Activate);
}
private: System::Void btnTakenMoveSectionC_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveSectionC));
	SetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_MoveSectionC.MB_Activate);
}
private: System::Void btnTakenMoveSectionD_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveSectionD));
	SetTCManData(s_BarrelManual.MB_MoveTaken.MBAP_MoveSectionD.MB_Activate);
}

private: System::Void btnCheckMoveSectionA_Click(System::Object^  sender, System::EventArgs^  e) {
	 TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveSectionA));
	 SetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_MoveSectionA.MB_Activate);
}
private: System::Void btnCheckMoveSectionB_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveSectionB));
	SetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_MoveSectionB.MB_Activate);
}
private: System::Void btnCheckMoveSectionC_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveSectionC));
	SetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_MoveSectionC.MB_Activate);
}
private: System::Void btnCheckMoveSectionD_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Barrel) + L" : " + TUtilities::pS_LoadString(TextIndex::MoveSectionD));
	SetTCManData(s_BarrelManual.MB_MoveCheck.MBAP_MoveSectionD.MB_Activate);
}


		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
};
}


