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
	public ref class VisionManualScreen : public System::Windows::Forms::Form
	{
	public:
		VisionManualScreen()
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::VisionManualScreen::OnUserLevelChanged);
		}
	private: MondemaComponents::Led^  ledSimulation;
	public:
	private: System::Windows::Forms::Label^  lblSimulation;
	private: MondemaComponents::Led^  ledValid;
	private: System::Windows::Forms::Label^  lblValid;
	private: System::Windows::Forms::Label^  lblTheta;
	private: System::Windows::Forms::Label^  lblY;
	private: System::Windows::Forms::Label^  lblX;
	private: System::Windows::Forms::Label^  lblValueTheta;
	private: System::Windows::Forms::Label^  lblValueY;
	private: System::Windows::Forms::Label^  lblValueX;
	private: MondemaComponents::Led^  ledPartPresent;
	private: System::Windows::Forms::Label^  lblPartPresent;
	private: System::Windows::Forms::Label^  lblValueScore;
	private: System::Windows::Forms::Label^  lblScore;
	private: System::Windows::Forms::GroupBox^  gbStatus;
	private: System::Windows::Forms::GroupBox^  gbResult;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  lblMoveVisionToLiftPos;
	private: System::Windows::Forms::Label^  lblMoveVisionToLift;
	private: System::Windows::Forms::TextBox^  tbPlatePos;
	private: System::Windows::Forms::Button^  btnMoveVisionToLift;
	private: System::Windows::Forms::Label^  lblMoveVisionToTable;
	private: System::Windows::Forms::Button^  btnMoveVisionToTable;
	private: System::Windows::Forms::CheckBox^  btnConfigMode;
	private:	bool bReloadParams;
			 // Our specific functions
	private:
	public:
		void UpdateUI(void);
		String^ FormatTime(TC_TIME stTime);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~VisionManualScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Button^  btnAnalyse;
	private: System::Windows::Forms::Button^  btnInit;
	private: MondemaComponents::Led^  ledReady;
	private: System::Windows::Forms::Label^  lblReady;
	private: System::Windows::Forms::Label^  lblConnected;
	private: MondemaComponents::Led^  ledConnected;
	private: System::Windows::Forms::Label^  lblAnalyseTime;
	private: System::Windows::Forms::Label^  lblInitTime;
	private: System::Windows::Forms::ComboBox^  cobModel;
	private: System::Windows::Forms::Label^  lblModel;
	private: System::Windows::Forms::Label^  lblRecipe;
	private: System::Windows::Forms::TextBox^  tbRecipe;
	private: System::Windows::Forms::CheckBox^  btnRun;
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
			this->btnConfigMode = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->lblMoveVisionToLiftPos = (gcnew System::Windows::Forms::Label());
			this->lblMoveVisionToLift = (gcnew System::Windows::Forms::Label());
			this->tbPlatePos = (gcnew System::Windows::Forms::TextBox());
			this->btnMoveVisionToLift = (gcnew System::Windows::Forms::Button());
			this->lblMoveVisionToTable = (gcnew System::Windows::Forms::Label());
			this->btnMoveVisionToTable = (gcnew System::Windows::Forms::Button());
			this->btnRun = (gcnew System::Windows::Forms::CheckBox());
			this->gbStatus = (gcnew System::Windows::Forms::GroupBox());
			this->lblConnected = (gcnew System::Windows::Forms::Label());
			this->ledConnected = (gcnew MondemaComponents::Led());
			this->lblReady = (gcnew System::Windows::Forms::Label());
			this->ledReady = (gcnew MondemaComponents::Led());
			this->ledSimulation = (gcnew MondemaComponents::Led());
			this->lblSimulation = (gcnew System::Windows::Forms::Label());
			this->gbResult = (gcnew System::Windows::Forms::GroupBox());
			this->lblPartPresent = (gcnew System::Windows::Forms::Label());
			this->lblX = (gcnew System::Windows::Forms::Label());
			this->lblY = (gcnew System::Windows::Forms::Label());
			this->lblValueScore = (gcnew System::Windows::Forms::Label());
			this->lblTheta = (gcnew System::Windows::Forms::Label());
			this->lblScore = (gcnew System::Windows::Forms::Label());
			this->lblValid = (gcnew System::Windows::Forms::Label());
			this->ledPartPresent = (gcnew MondemaComponents::Led());
			this->ledValid = (gcnew MondemaComponents::Led());
			this->lblValueX = (gcnew System::Windows::Forms::Label());
			this->lblValueTheta = (gcnew System::Windows::Forms::Label());
			this->lblValueY = (gcnew System::Windows::Forms::Label());
			this->lblRecipe = (gcnew System::Windows::Forms::Label());
			this->tbRecipe = (gcnew System::Windows::Forms::TextBox());
			this->lblModel = (gcnew System::Windows::Forms::Label());
			this->cobModel = (gcnew System::Windows::Forms::ComboBox());
			this->lblAnalyseTime = (gcnew System::Windows::Forms::Label());
			this->lblInitTime = (gcnew System::Windows::Forms::Label());
			this->btnAnalyse = (gcnew System::Windows::Forms::Button());
			this->btnInit = (gcnew System::Windows::Forms::Button());
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->gbStatus->SuspendLayout();
			this->gbResult->SuspendLayout();
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
			this->tabPage1->Controls->Add(this->btnConfigMode);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Controls->Add(this->btnRun);
			this->tabPage1->Controls->Add(this->gbStatus);
			this->tabPage1->Controls->Add(this->gbResult);
			this->tabPage1->Controls->Add(this->lblRecipe);
			this->tabPage1->Controls->Add(this->tbRecipe);
			this->tabPage1->Controls->Add(this->lblModel);
			this->tabPage1->Controls->Add(this->cobModel);
			this->tabPage1->Controls->Add(this->lblAnalyseTime);
			this->tabPage1->Controls->Add(this->lblInitTime);
			this->tabPage1->Controls->Add(this->btnAnalyse);
			this->tabPage1->Controls->Add(this->btnInit);
			this->tabPage1->Location = System::Drawing::Point(4, 49);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1570, 842);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// btnConfigMode
			// 
			this->btnConfigMode->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnConfigMode->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnConfigMode->Location = System::Drawing::Point(624, 207);
			this->btnConfigMode->Name = L"btnConfigMode";
			this->btnConfigMode->Size = System::Drawing::Size(173, 90);
			this->btnConfigMode->TabIndex = 154;
			this->btnConfigMode->Tag = L"2";
			this->btnConfigMode->Text = L"Configuration";
			this->btnConfigMode->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnConfigMode->UseVisualStyleBackColor = true;
			this->btnConfigMode->CheckedChanged += gcnew System::EventHandler(this, &VisionManualScreen::btnConfigMode_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->lblMoveVisionToLiftPos);
			this->groupBox1->Controls->Add(this->lblMoveVisionToLift);
			this->groupBox1->Controls->Add(this->tbPlatePos);
			this->groupBox1->Controls->Add(this->btnMoveVisionToLift);
			this->groupBox1->Controls->Add(this->lblMoveVisionToTable);
			this->groupBox1->Controls->Add(this->btnMoveVisionToTable);
			this->groupBox1->Location = System::Drawing::Point(624, 356);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(737, 330);
			this->groupBox1->TabIndex = 153;
			this->groupBox1->TabStop = false;
			this->groupBox1->Tag = L"1";
			this->groupBox1->Text = L" Positions";
			// 
			// lblMoveVisionToLiftPos
			// 
			this->lblMoveVisionToLiftPos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblMoveVisionToLiftPos->Location = System::Drawing::Point(95, 264);
			this->lblMoveVisionToLiftPos->Name = L"lblMoveVisionToLiftPos";
			this->lblMoveVisionToLiftPos->Size = System::Drawing::Size(462, 30);
			this->lblMoveVisionToLiftPos->TabIndex = 160;
			this->lblMoveVisionToLiftPos->Tag = L"1";
			this->lblMoveVisionToLiftPos->Text = L"Position sur le plateau";
			this->lblMoveVisionToLiftPos->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// lblMoveVisionToLift
			// 
			this->lblMoveVisionToLift->AutoSize = true;
			this->lblMoveVisionToLift->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveVisionToLift->Location = System::Drawing::Point(60, 189);
			this->lblMoveVisionToLift->Name = L"lblMoveVisionToLift";
			this->lblMoveVisionToLift->Size = System::Drawing::Size(387, 29);
			this->lblMoveVisionToLift->TabIndex = 156;
			this->lblMoveVisionToLift->Tag = L"1";
			this->lblMoveVisionToLift->Text = L"Déplacer la vision sur le plateau";
			// 
			// tbPlatePos
			// 
			this->tbPlatePos->Location = System::Drawing::Point(610, 260);
			this->tbPlatePos->MaxLength = 20;
			this->tbPlatePos->Name = L"tbPlatePos";
			this->tbPlatePos->Size = System::Drawing::Size(90, 35);
			this->tbPlatePos->TabIndex = 159;
			this->tbPlatePos->Tag = L"1";
			this->tbPlatePos->Text = L"1";
			this->tbPlatePos->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->tbPlatePos->Click += gcnew System::EventHandler(this, &VisionManualScreen::tbPlatePos_Click);
			// 
			// btnMoveVisionToLift
			// 
			this->btnMoveVisionToLift->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMoveVisionToLift->Location = System::Drawing::Point(610, 161);
			this->btnMoveVisionToLift->Name = L"btnMoveVisionToLift";
			this->btnMoveVisionToLift->Size = System::Drawing::Size(90, 90);
			this->btnMoveVisionToLift->TabIndex = 155;
			this->btnMoveVisionToLift->Tag = L"1";
			this->btnMoveVisionToLift->Text = L"Go";
			this->btnMoveVisionToLift->UseVisualStyleBackColor = true;
			this->btnMoveVisionToLift->Click += gcnew System::EventHandler(this, &VisionManualScreen::btnMoveVisionToLift_Click);
			// 
			// lblMoveVisionToTable
			// 
			this->lblMoveVisionToTable->AutoSize = true;
			this->lblMoveVisionToTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveVisionToTable->Location = System::Drawing::Point(60, 81);
			this->lblMoveVisionToTable->Name = L"lblMoveVisionToTable";
			this->lblMoveVisionToTable->Size = System::Drawing::Size(388, 29);
			this->lblMoveVisionToTable->TabIndex = 154;
			this->lblMoveVisionToTable->Tag = L"1";
			this->lblMoveVisionToTable->Text = L"Déplacer la vision sur le posage";
			// 
			// btnMoveVisionToTable
			// 
			this->btnMoveVisionToTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnMoveVisionToTable->Location = System::Drawing::Point(610, 53);
			this->btnMoveVisionToTable->Name = L"btnMoveVisionToTable";
			this->btnMoveVisionToTable->Size = System::Drawing::Size(90, 90);
			this->btnMoveVisionToTable->TabIndex = 153;
			this->btnMoveVisionToTable->Tag = L"1";
			this->btnMoveVisionToTable->Text = L"Go";
			this->btnMoveVisionToTable->UseVisualStyleBackColor = true;
			this->btnMoveVisionToTable->Click += gcnew System::EventHandler(this, &VisionManualScreen::btnMoveVisionToTable_Click);
			// 
			// btnRun
			// 
			this->btnRun->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRun->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRun->Location = System::Drawing::Point(12, 207);
			this->btnRun->Name = L"btnRun";
			this->btnRun->Size = System::Drawing::Size(173, 90);
			this->btnRun->TabIndex = 32;
			this->btnRun->Tag = L"2";
			this->btnRun->Text = L"Run";
			this->btnRun->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRun->UseVisualStyleBackColor = true;
			this->btnRun->Click += gcnew System::EventHandler(this, &VisionManualScreen::btnRun_Click);
			// 
			// gbStatus
			// 
			this->gbStatus->Controls->Add(this->lblConnected);
			this->gbStatus->Controls->Add(this->ledConnected);
			this->gbStatus->Controls->Add(this->lblReady);
			this->gbStatus->Controls->Add(this->ledReady);
			this->gbStatus->Controls->Add(this->ledSimulation);
			this->gbStatus->Controls->Add(this->lblSimulation);
			this->gbStatus->Location = System::Drawing::Point(624, 9);
			this->gbStatus->Name = L"gbStatus";
			this->gbStatus->Size = System::Drawing::Size(299, 150);
			this->gbStatus->TabIndex = 142;
			this->gbStatus->TabStop = false;
			this->gbStatus->Tag = L"1";
			this->gbStatus->Text = L"Status";
			// 
			// lblConnected
			// 
			this->lblConnected->AutoSize = true;
			this->lblConnected->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblConnected->Location = System::Drawing::Point(9, 33);
			this->lblConnected->Name = L"lblConnected";
			this->lblConnected->Size = System::Drawing::Size(139, 29);
			this->lblConnected->TabIndex = 117;
			this->lblConnected->Tag = L"1";
			this->lblConnected->Text = L"Connected";
			// 
			// ledConnected
			// 
			this->ledConnected->Location = System::Drawing::Point(245, 33);
			this->ledConnected->Margin = System::Windows::Forms::Padding(5);
			this->ledConnected->Name = L"ledConnected";
			this->ledConnected->Size = System::Drawing::Size(30, 30);
			this->ledConnected->TabIndex = 118;
			this->ledConnected->Tag = L"1";
			// 
			// lblReady
			// 
			this->lblReady->AutoSize = true;
			this->lblReady->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblReady->Location = System::Drawing::Point(9, 63);
			this->lblReady->Name = L"lblReady";
			this->lblReady->Size = System::Drawing::Size(87, 29);
			this->lblReady->TabIndex = 119;
			this->lblReady->Tag = L"1";
			this->lblReady->Text = L"Ready";
			// 
			// ledReady
			// 
			this->ledReady->Location = System::Drawing::Point(245, 63);
			this->ledReady->Margin = System::Windows::Forms::Padding(8);
			this->ledReady->Name = L"ledReady";
			this->ledReady->Size = System::Drawing::Size(30, 30);
			this->ledReady->TabIndex = 120;
			this->ledReady->Tag = L"1";
			// 
			// ledSimulation
			// 
			this->ledSimulation->Location = System::Drawing::Point(245, 93);
			this->ledSimulation->Margin = System::Windows::Forms::Padding(20, 18, 20, 18);
			this->ledSimulation->Name = L"ledSimulation";
			this->ledSimulation->Size = System::Drawing::Size(30, 30);
			this->ledSimulation->TabIndex = 128;
			this->ledSimulation->Tag = L"1";
			// 
			// lblSimulation
			// 
			this->lblSimulation->AutoSize = true;
			this->lblSimulation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSimulation->Location = System::Drawing::Point(9, 93);
			this->lblSimulation->Name = L"lblSimulation";
			this->lblSimulation->Size = System::Drawing::Size(136, 29);
			this->lblSimulation->TabIndex = 127;
			this->lblSimulation->Tag = L"1";
			this->lblSimulation->Text = L"Simulation";
			// 
			// gbResult
			// 
			this->gbResult->Controls->Add(this->lblPartPresent);
			this->gbResult->Controls->Add(this->lblX);
			this->gbResult->Controls->Add(this->lblY);
			this->gbResult->Controls->Add(this->lblValueScore);
			this->gbResult->Controls->Add(this->lblTheta);
			this->gbResult->Controls->Add(this->lblScore);
			this->gbResult->Controls->Add(this->lblValid);
			this->gbResult->Controls->Add(this->ledPartPresent);
			this->gbResult->Controls->Add(this->ledValid);
			this->gbResult->Controls->Add(this->lblValueX);
			this->gbResult->Controls->Add(this->lblValueTheta);
			this->gbResult->Controls->Add(this->lblValueY);
			this->gbResult->Location = System::Drawing::Point(932, 9);
			this->gbResult->Name = L"gbResult";
			this->gbResult->Size = System::Drawing::Size(336, 234);
			this->gbResult->TabIndex = 141;
			this->gbResult->TabStop = false;
			this->gbResult->Tag = L"1";
			this->gbResult->Text = L"Result";
			// 
			// lblPartPresent
			// 
			this->lblPartPresent->AutoSize = true;
			this->lblPartPresent->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPartPresent->Location = System::Drawing::Point(9, 33);
			this->lblPartPresent->Name = L"lblPartPresent";
			this->lblPartPresent->Size = System::Drawing::Size(150, 29);
			this->lblPartPresent->TabIndex = 137;
			this->lblPartPresent->Tag = L"1";
			this->lblPartPresent->Text = L"PartPresent";
			// 
			// lblX
			// 
			this->lblX->AutoSize = true;
			this->lblX->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblX->Location = System::Drawing::Point(9, 123);
			this->lblX->Name = L"lblX";
			this->lblX->Size = System::Drawing::Size(45, 29);
			this->lblX->TabIndex = 129;
			this->lblX->Tag = L"1";
			this->lblX->Text = L"X :";
			// 
			// lblY
			// 
			this->lblY->AutoSize = true;
			this->lblY->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblY->Location = System::Drawing::Point(9, 153);
			this->lblY->Name = L"lblY";
			this->lblY->Size = System::Drawing::Size(44, 29);
			this->lblY->TabIndex = 130;
			this->lblY->Tag = L"1";
			this->lblY->Text = L"Y :";
			// 
			// lblValueScore
			// 
			this->lblValueScore->AutoSize = true;
			this->lblValueScore->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblValueScore->Location = System::Drawing::Point(194, 93);
			this->lblValueScore->Name = L"lblValueScore";
			this->lblValueScore->Size = System::Drawing::Size(48, 29);
			this->lblValueScore->TabIndex = 140;
			this->lblValueScore->Tag = L"1";
			this->lblValueScore->Text = L"0.0";
			// 
			// lblTheta
			// 
			this->lblTheta->AutoSize = true;
			this->lblTheta->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTheta->Location = System::Drawing::Point(9, 183);
			this->lblTheta->Name = L"lblTheta";
			this->lblTheta->Size = System::Drawing::Size(94, 29);
			this->lblTheta->TabIndex = 131;
			this->lblTheta->Tag = L"1";
			this->lblTheta->Text = L"Theta :";
			// 
			// lblScore
			// 
			this->lblScore->AutoSize = true;
			this->lblScore->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblScore->Location = System::Drawing::Point(9, 93);
			this->lblScore->Name = L"lblScore";
			this->lblScore->Size = System::Drawing::Size(96, 29);
			this->lblScore->TabIndex = 139;
			this->lblScore->Tag = L"1";
			this->lblScore->Text = L"Score :";
			// 
			// lblValid
			// 
			this->lblValid->AutoSize = true;
			this->lblValid->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblValid->Location = System::Drawing::Point(9, 63);
			this->lblValid->Name = L"lblValid";
			this->lblValid->Size = System::Drawing::Size(72, 29);
			this->lblValid->TabIndex = 132;
			this->lblValid->Tag = L"1";
			this->lblValid->Text = L"Valid";
			// 
			// ledPartPresent
			// 
			this->ledPartPresent->Location = System::Drawing::Point(200, 33);
			this->ledPartPresent->Margin = System::Windows::Forms::Padding(56, 42, 56, 42);
			this->ledPartPresent->Name = L"ledPartPresent";
			this->ledPartPresent->Size = System::Drawing::Size(30, 30);
			this->ledPartPresent->TabIndex = 138;
			this->ledPartPresent->Tag = L"1";
			// 
			// ledValid
			// 
			this->ledValid->Location = System::Drawing::Point(200, 63);
			this->ledValid->Margin = System::Windows::Forms::Padding(33, 27, 33, 27);
			this->ledValid->Name = L"ledValid";
			this->ledValid->Size = System::Drawing::Size(30, 30);
			this->ledValid->TabIndex = 133;
			this->ledValid->Tag = L"1";
			// 
			// lblValueX
			// 
			this->lblValueX->AutoSize = true;
			this->lblValueX->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblValueX->Location = System::Drawing::Point(194, 123);
			this->lblValueX->Name = L"lblValueX";
			this->lblValueX->Size = System::Drawing::Size(48, 29);
			this->lblValueX->TabIndex = 134;
			this->lblValueX->Tag = L"1";
			this->lblValueX->Text = L"0.0";
			// 
			// lblValueTheta
			// 
			this->lblValueTheta->AutoSize = true;
			this->lblValueTheta->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblValueTheta->Location = System::Drawing::Point(194, 186);
			this->lblValueTheta->Name = L"lblValueTheta";
			this->lblValueTheta->Size = System::Drawing::Size(48, 29);
			this->lblValueTheta->TabIndex = 136;
			this->lblValueTheta->Tag = L"1";
			this->lblValueTheta->Text = L"0.0";
			// 
			// lblValueY
			// 
			this->lblValueY->AutoSize = true;
			this->lblValueY->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblValueY->Location = System::Drawing::Point(194, 156);
			this->lblValueY->Name = L"lblValueY";
			this->lblValueY->Size = System::Drawing::Size(48, 29);
			this->lblValueY->TabIndex = 135;
			this->lblValueY->Tag = L"1";
			this->lblValueY->Text = L"0.0";
			// 
			// lblRecipe
			// 
			this->lblRecipe->AutoSize = true;
			this->lblRecipe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRecipe->Location = System::Drawing::Point(12, 332);
			this->lblRecipe->Name = L"lblRecipe";
			this->lblRecipe->Size = System::Drawing::Size(96, 29);
			this->lblRecipe->TabIndex = 126;
			this->lblRecipe->Tag = L"2";
			this->lblRecipe->Text = L"Recipe";
			// 
			// tbRecipe
			// 
			this->tbRecipe->Location = System::Drawing::Point(188, 323);
			this->tbRecipe->MaxLength = 20;
			this->tbRecipe->Name = L"tbRecipe";
			this->tbRecipe->Size = System::Drawing::Size(287, 35);
			this->tbRecipe->TabIndex = 125;
			this->tbRecipe->Tag = L"2";
			this->tbRecipe->Click += gcnew System::EventHandler(this, &VisionManualScreen::tbRecipe_Click);
			// 
			// lblModel
			// 
			this->lblModel->AutoSize = true;
			this->lblModel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblModel->Location = System::Drawing::Point(12, 380);
			this->lblModel->Name = L"lblModel";
			this->lblModel->Size = System::Drawing::Size(86, 29);
			this->lblModel->TabIndex = 124;
			this->lblModel->Tag = L"2";
			this->lblModel->Text = L"Model";
			// 
			// cobModel
			// 
			this->cobModel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cobModel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cobModel->FormattingEnabled = true;
			this->cobModel->Location = System::Drawing::Point(188, 375);
			this->cobModel->Name = L"cobModel";
			this->cobModel->Size = System::Drawing::Size(180, 37);
			this->cobModel->TabIndex = 123;
			this->cobModel->Tag = L"2";
			this->cobModel->SelectedIndexChanged += gcnew System::EventHandler(this, &VisionManualScreen::cobModel_SelectedIndexChanged);
			// 
			// lblAnalyseTime
			// 
			this->lblAnalyseTime->AutoSize = true;
			this->lblAnalyseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAnalyseTime->Location = System::Drawing::Point(194, 137);
			this->lblAnalyseTime->Name = L"lblAnalyseTime";
			this->lblAnalyseTime->Size = System::Drawing::Size(111, 29);
			this->lblAnalyseTime->TabIndex = 122;
			this->lblAnalyseTime->Tag = L"1";
			this->lblAnalyseTime->Text = L"00:00:00";
			// 
			// lblInitTime
			// 
			this->lblInitTime->AutoSize = true;
			this->lblInitTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblInitTime->Location = System::Drawing::Point(194, 38);
			this->lblInitTime->Name = L"lblInitTime";
			this->lblInitTime->Size = System::Drawing::Size(111, 29);
			this->lblInitTime->TabIndex = 121;
			this->lblInitTime->Tag = L"1";
			this->lblInitTime->Text = L"00:00:00";
			// 
			// btnAnalyse
			// 
			this->btnAnalyse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAnalyse->Location = System::Drawing::Point(12, 108);
			this->btnAnalyse->Name = L"btnAnalyse";
			this->btnAnalyse->Size = System::Drawing::Size(173, 90);
			this->btnAnalyse->TabIndex = 109;
			this->btnAnalyse->Tag = L"1";
			this->btnAnalyse->Text = L"Analyse";
			this->btnAnalyse->UseVisualStyleBackColor = true;
			this->btnAnalyse->Click += gcnew System::EventHandler(this, &VisionManualScreen::btnAnalyse_Click);
			// 
			// btnInit
			// 
			this->btnInit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnInit->Location = System::Drawing::Point(12, 9);
			this->btnInit->Name = L"btnInit";
			this->btnInit->Size = System::Drawing::Size(173, 90);
			this->btnInit->TabIndex = 108;
			this->btnInit->Tag = L"1";
			this->btnInit->Text = L"Init";
			this->btnInit->UseVisualStyleBackColor = true;
			this->btnInit->Click += gcnew System::EventHandler(this, &VisionManualScreen::btnInit_Click);
			// 
			// VisionManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"VisionManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &VisionManualScreen::VisionManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->gbStatus->ResumeLayout(false);
			this->gbStatus->PerformLayout();
			this->gbResult->ResumeLayout(false);
			this->gbResult->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void ShowOsk_Click(System::Object^  sender, System::EventArgs^  e) {
		TUtilities::ShowOSK();
	}

	private: System::Void VisionManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			tabPage1->Text = TUtilities::pS_LoadString(TextIndex::Vision);
			btnAnalyse->Text = TUtilities::pS_LoadString(TextIndex::Analyse);
			btnInit->Text = TUtilities::pS_LoadString(TextIndex::Init);
			btnRun->Text = TUtilities::pS_LoadString(TextIndex::Run);
			lblConnected->Text = TUtilities::pS_LoadString(TextIndex::Connected);
			lblReady->Text = TUtilities::pS_LoadString(TextIndex::Ready);
			lblModel->Text = TUtilities::pS_LoadString(TextIndex::Model);
			lblRecipe->Text = TUtilities::pS_LoadString(TextIndex::Recipe);
			lblSimulation->Text = TUtilities::pS_LoadString(TextIndex::Simulation);
			lblValid->Text = TUtilities::pS_LoadString(TextIndex::Validate);
			lblPartPresent->Text = TUtilities::pS_LoadString(TextIndex::PartPresent);
			gbResult->Text = TUtilities::pS_LoadString(TextIndex::Result);
			gbStatus->Text = TUtilities::pS_LoadString(TextIndex::Status);
			lblMoveVisionToTable->Text = TUtilities::pS_LoadString(TextIndex::MoveVisionToTable);
			lblMoveVisionToLift->Text = TUtilities::pS_LoadString(TextIndex::MoveVisionToLift);
			lblMoveVisionToLiftPos->Text = TUtilities::pS_LoadString(TextIndex::MoveVisionToLiftPos);
			btnConfigMode->Text = TUtilities::pS_LoadString(TextIndex::ConfigMode);
			bReloadParams = true;
		 }
private: System::Void btnInit_Click(System::Object^  sender, System::EventArgs^  e) {
	char ac_l_RecipeName[255];
	
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Init));
	TUtilities::StringToCharArray(tbRecipe->Text, ac_l_RecipeName);

	cobModel->Items->Clear();
	WriteTCManData(s_VisionManual.MV_VisionRecipeName, ac_l_RecipeName);
	SetTCManData(s_VisionManual.MV_Init.MB_Activate);
}
private: System::Void btnAnalyse_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Analyse));
	SetTCManData(s_VisionManual.MV_Analyse.MB_Activate);
}
private: System::Void cobModel_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Model) + " [" + cobModel->SelectedIndex + "]");
	WriteTCManData(s_VisionManual.MV_UseModel, (TC_INT)cobModel->SelectedIndex);
}
private: System::Void tbRecipe_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

	openFileDialog1->InitialDirectory = "c:\\vision\\reference";
	openFileDialog1->Filter = "Vision recipe parameter|*.vrp";
	openFileDialog1->FilterIndex = 1;
	openFileDialog1->RestoreDirectory = true;
	openFileDialog1->CheckFileExists = true;
	openFileDialog1->FileName = tbRecipe->Text!="" ? tbRecipe->Text+".vrp" : "";

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		tbRecipe->Text = Path::GetFileNameWithoutExtension(openFileDialog1->SafeFileName);
	}
}
private: System::Void btnRun_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::Run) + L" " + TUtilities::pS_GetTextBool(btnRun->Checked));
	WriteTCManData(s_VisionManual.MV_Run, (TC_BOOL)btnRun->Checked);
}
		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
private: System::Void btnMoveVisionToLift_Click(System::Object^  sender, System::EventArgs^  e) {
	bool b_l_Exception = false;
	int i_l_PlatePos;

	try
	{
		i_l_PlatePos = Convert::ToInt16(tbPlatePos->Text);
		if (i_l_PlatePos < 1)
			b_l_Exception = true;
		else
		{
			TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::MoveVisionToLift) + L" pos. " + tbPlatePos->Text);
			WriteTCManData(s_LoaderManual.ML_MoveVision2LiftPos, (TC_INT)i_l_PlatePos);
			SetTCManData(s_LoaderManual.ML_MoveVision2Lift.MB_Activate);
		}
	}
	catch (Exception^)
	{
		b_l_Exception = true;
	}
	if (b_l_Exception)
	{
		MyMsgBox^ pT_l_ErrorOnPos = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::ErrorOnLiftPos) + L" <" + tbPlatePos->Text + L">", TUtilities::pS_LoadString(TextIndex::DataError), MessageBoxButtons::OK);
		pT_l_ErrorOnPos->ShowDialog();
	}
}
private: System::Void tbPlatePos_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblMoveVisionToLiftPos->Text, double::Parse(tbPlatePos->Text), 1, 70, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		tbPlatePos->Text = Keypad->Value.ToString("F0");
	}
}
private: System::Void btnMoveVisionToTable_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::MoveVisionToTable));
	SetTCManData(s_LoaderManual.ML_MoveVision2Table.MB_Activate);
}
private: System::Void btnConfigMode_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::ConfigMode) + L" " + TUtilities::pS_GetTextBool(btnConfigMode->Checked));
	WriteTCManData(s_VisionManual.MV_ConfigMode.MB_Activate, (TC_BOOL)btnConfigMode->Checked);
}
};
}