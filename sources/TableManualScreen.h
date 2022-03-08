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
	public ref class TableManualScreen : public System::Windows::Forms::Form
	{
	public:
		TableManualScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_DriveTable = gcnew DriveComponent(this->gbAxisTable);
			pT_DriveTable->UsePosition(0,"");
			pT_DriveTable->UsePosition(1,"");
			pT_DriveTable->SetDriveData(tabControl->TabPages[0]->Text,GetTCManualOffset(s_TableManual.MT_AxisTable),"");
			pT_DriveTable->SetDrivePosData(0,GetTCManualOffset(s_TableManual.MT_AxisTableLoading12Pos));
			pT_DriveTable->SetDrivePosData(1,GetTCManualOffset(s_TableManual.MT_AxisTableLoading34Pos));

			pT_DriveBrush = gcnew DriveComponent(this->gbAxisBrush);
			pT_DriveBrush->UsePosition(0, "");
			pT_DriveBrush->UsePosition(1, "");
			pT_DriveBrush->UsePosition(2, "");
			pT_DriveBrush->UsePosition(3, "");
			pT_DriveBrush->SetDriveData(tabControl->TabPages[1]->Text, GetTCManualOffset(s_TableManual.MT_AxisBrush), "");
			pT_DriveBrush->SetDrivePosData(0, GetTCManualOffset(s_TableManual.MT_AxisBrushParkPos[0]));
			pT_DriveBrush->SetDrivePosData(1, GetTCManualOffset(s_TableManual.MT_AxisBrushParkPos[1]));
			pT_DriveBrush->SetDrivePosData(2, GetTCManualOffset(s_TableManual.MT_AxisBrushWorkPos[0]));
			pT_DriveBrush->SetDrivePosData(3, GetTCManualOffset(s_TableManual.MT_AxisBrushWorkPos[1]));

			lblVacuumThreshold1->Offset = GetTCManualOffset(s_TableManual.MT_VacuumThreshold[0]);
			lblVacuumThreshold2->Offset = GetTCManualOffset(s_TableManual.MT_VacuumThreshold[1]);
			lblVacuumThreshold3->Offset = GetTCManualOffset(s_TableManual.MT_VacuumThreshold[2]);
			lblVacuumThreshold4->Offset = GetTCManualOffset(s_TableManual.MT_VacuumThreshold[3]);

			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::TableManualScreen::OnUserLevelChanged);
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::GroupBox^  gbAxisTable;
	public: 

			 // Our specific functions
	private:
		 DriveComponent^ pT_DriveTable;
		 DriveComponent^ pT_DriveBrush;
	private: System::Windows::Forms::CheckBox^  btnAspirationDown;
	private: System::Windows::Forms::CheckBox^  btnAspirationUp;
	private: System::Windows::Forms::Label^  lblAspirationRoom;
	private: System::Windows::Forms::CheckBox^  btnIndexMoveDown;
	private: System::Windows::Forms::CheckBox^  btnIndexMoveUp;
	private: System::Windows::Forms::Label^  lblIndexing;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::CheckBox^  btnVacuum1_OFF;
	private: System::Windows::Forms::CheckBox^  btnVacuum1_ON;
	private: System::Windows::Forms::Label^  lblVacuumPos1;
	private: System::Windows::Forms::CheckBox^  btnVacuum2_OFF;
	private: System::Windows::Forms::CheckBox^  btnVacuum2_ON;
	private: System::Windows::Forms::Label^  lblVacuumPos2;
	private: System::Windows::Forms::CheckBox^  btnVacuum3_OFF;
	private: System::Windows::Forms::CheckBox^  btnVacuum3_ON;
	private: System::Windows::Forms::Label^  lblVacuumPos3;
	private: System::Windows::Forms::CheckBox^  btnVacuum4_OFF;
	private: System::Windows::Forms::CheckBox^  btnVacuum4_ON;
	private: System::Windows::Forms::Label^  lblVacuumPos4;
	private: System::Windows::Forms::TextBox^  tbVacuum4;
	private: System::Windows::Forms::TextBox^  tbVacuum3;
	private: System::Windows::Forms::TextBox^  tbVacuum2;
	private: System::Windows::Forms::TextBox^  tbVacuum1;
	private: System::Windows::Forms::CheckBox^  btnPearling1Aspiration_OFF;
	private: System::Windows::Forms::CheckBox^  btnPearling1Aspiration_ON;
	private: System::Windows::Forms::Label^  lblPearling1Aspiration;
	private: System::Windows::Forms::CheckBox^  btnBrushAspiration_OFF;
	private: System::Windows::Forms::CheckBox^  btnBrushAspiration_ON;
	private: System::Windows::Forms::Label^  lblBrushAspiration;
	private: System::Windows::Forms::CheckBox^  btnPearling2Aspiration_OFF;
	private: System::Windows::Forms::CheckBox^  btnPearling2Aspiration_ON;
	private: System::Windows::Forms::Label^  lblPearling2Aspiration;
	private: MondemaComponents::LabelOffset^  lblVacuumThreshold4;
	private: MondemaComponents::LabelOffset^  lblVacuumThreshold3;
	private: MondemaComponents::LabelOffset^  lblVacuumThreshold2;
	private: MondemaComponents::LabelOffset^  lblVacuumThreshold1;
	private: System::Windows::Forms::CheckBox^  cbDisableCleanAfterPearl;
	private: System::Windows::Forms::Label^  lblDisableCleanAfterPearl;
	private: System::Windows::Forms::CheckBox^  btnCleanBrushDown;
	private: System::Windows::Forms::CheckBox^  btnCleanBrushUp;
	private: System::Windows::Forms::Label^  lblCleanBrush;
	private: System::Windows::Forms::Label^  lblRateOfFlow2;
	private: System::Windows::Forms::Label^  lblRateOfFlow4;


	private: System::Windows::Forms::Label^  lblRateOfFlow1;
	private: System::Windows::Forms::Label^  lblRateOfFlow3;


	private: System::Windows::Forms::GroupBox^  gbAxisBrush;
	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~TableManualScreen()
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TableManualScreen::typeid));
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->btnCleanBrushDown = (gcnew System::Windows::Forms::CheckBox());
			this->btnCleanBrushUp = (gcnew System::Windows::Forms::CheckBox());
			this->lblCleanBrush = (gcnew System::Windows::Forms::Label());
			this->btnPearling2Aspiration_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnPearling2Aspiration_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblPearling2Aspiration = (gcnew System::Windows::Forms::Label());
			this->btnPearling1Aspiration_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnPearling1Aspiration_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblPearling1Aspiration = (gcnew System::Windows::Forms::Label());
			this->btnAspirationDown = (gcnew System::Windows::Forms::CheckBox());
			this->btnAspirationUp = (gcnew System::Windows::Forms::CheckBox());
			this->lblAspirationRoom = (gcnew System::Windows::Forms::Label());
			this->btnIndexMoveDown = (gcnew System::Windows::Forms::CheckBox());
			this->btnIndexMoveUp = (gcnew System::Windows::Forms::CheckBox());
			this->lblIndexing = (gcnew System::Windows::Forms::Label());
			this->gbAxisTable = (gcnew System::Windows::Forms::GroupBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->lblDisableCleanAfterPearl = (gcnew System::Windows::Forms::Label());
			this->cbDisableCleanAfterPearl = (gcnew System::Windows::Forms::CheckBox());
			this->btnBrushAspiration_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnBrushAspiration_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblBrushAspiration = (gcnew System::Windows::Forms::Label());
			this->gbAxisBrush = (gcnew System::Windows::Forms::GroupBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->lblRateOfFlow2 = (gcnew System::Windows::Forms::Label());
			this->lblRateOfFlow4 = (gcnew System::Windows::Forms::Label());
			this->lblRateOfFlow1 = (gcnew System::Windows::Forms::Label());
			this->lblRateOfFlow3 = (gcnew System::Windows::Forms::Label());
			this->lblVacuumThreshold4 = (gcnew MondemaComponents::LabelOffset());
			this->lblVacuumThreshold3 = (gcnew MondemaComponents::LabelOffset());
			this->lblVacuumThreshold2 = (gcnew MondemaComponents::LabelOffset());
			this->lblVacuumThreshold1 = (gcnew MondemaComponents::LabelOffset());
			this->tbVacuum4 = (gcnew System::Windows::Forms::TextBox());
			this->tbVacuum3 = (gcnew System::Windows::Forms::TextBox());
			this->tbVacuum2 = (gcnew System::Windows::Forms::TextBox());
			this->tbVacuum1 = (gcnew System::Windows::Forms::TextBox());
			this->btnVacuum1_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnVacuum1_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblVacuumPos1 = (gcnew System::Windows::Forms::Label());
			this->btnVacuum2_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnVacuum2_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblVacuumPos2 = (gcnew System::Windows::Forms::Label());
			this->btnVacuum3_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnVacuum3_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblVacuumPos3 = (gcnew System::Windows::Forms::Label());
			this->btnVacuum4_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnVacuum4_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblVacuumPos4 = (gcnew System::Windows::Forms::Label());
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Controls->Add(this->tabPage3);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tabControl->ItemSize = System::Drawing::Size(134, 45);
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1578, 895);
			this->tabControl->TabIndex = 24;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->btnCleanBrushDown);
			this->tabPage1->Controls->Add(this->btnCleanBrushUp);
			this->tabPage1->Controls->Add(this->lblCleanBrush);
			this->tabPage1->Controls->Add(this->btnPearling2Aspiration_OFF);
			this->tabPage1->Controls->Add(this->btnPearling2Aspiration_ON);
			this->tabPage1->Controls->Add(this->lblPearling2Aspiration);
			this->tabPage1->Controls->Add(this->btnPearling1Aspiration_OFF);
			this->tabPage1->Controls->Add(this->btnPearling1Aspiration_ON);
			this->tabPage1->Controls->Add(this->lblPearling1Aspiration);
			this->tabPage1->Controls->Add(this->btnAspirationDown);
			this->tabPage1->Controls->Add(this->btnAspirationUp);
			this->tabPage1->Controls->Add(this->lblAspirationRoom);
			this->tabPage1->Controls->Add(this->btnIndexMoveDown);
			this->tabPage1->Controls->Add(this->btnIndexMoveUp);
			this->tabPage1->Controls->Add(this->lblIndexing);
			this->tabPage1->Controls->Add(this->gbAxisTable);
			this->tabPage1->Location = System::Drawing::Point(4, 49);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(1570, 842);
			this->tabPage1->TabIndex = 1;
			this->tabPage1->Text = L"Table";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// btnCleanBrushDown
			// 
			this->btnCleanBrushDown->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnCleanBrushDown->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnCleanBrushDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCleanBrushDown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnCleanBrushDown.Image")));
			this->btnCleanBrushDown->Location = System::Drawing::Point(473, 460);
			this->btnCleanBrushDown->Name = L"btnCleanBrushDown";
			this->btnCleanBrushDown->Size = System::Drawing::Size(90, 90);
			this->btnCleanBrushDown->TabIndex = 120;
			this->btnCleanBrushDown->Tag = L"1";
			this->btnCleanBrushDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnCleanBrushDown->UseVisualStyleBackColor = false;
			this->btnCleanBrushDown->CheckedChanged += gcnew System::EventHandler(this, &TableManualScreen::btnCleanBrushDown_CheckedChanged);
			// 
			// btnCleanBrushUp
			// 
			this->btnCleanBrushUp->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnCleanBrushUp->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnCleanBrushUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCleanBrushUp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnCleanBrushUp.Image")));
			this->btnCleanBrushUp->Location = System::Drawing::Point(374, 460);
			this->btnCleanBrushUp->Name = L"btnCleanBrushUp";
			this->btnCleanBrushUp->Size = System::Drawing::Size(90, 90);
			this->btnCleanBrushUp->TabIndex = 119;
			this->btnCleanBrushUp->Tag = L"1";
			this->btnCleanBrushUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnCleanBrushUp->UseVisualStyleBackColor = false;
			this->btnCleanBrushUp->CheckedChanged += gcnew System::EventHandler(this, &TableManualScreen::btnCleanBrushUp_CheckedChanged);
			// 
			// lblCleanBrush
			// 
			this->lblCleanBrush->AutoSize = true;
			this->lblCleanBrush->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCleanBrush->Location = System::Drawing::Point(47, 498);
			this->lblCleanBrush->Name = L"lblCleanBrush";
			this->lblCleanBrush->Size = System::Drawing::Size(95, 29);
			this->lblCleanBrush->TabIndex = 118;
			this->lblCleanBrush->Tag = L"1";
			this->lblCleanBrush->Text = L"Brosse";
			// 
			// btnPearling2Aspiration_OFF
			// 
			this->btnPearling2Aspiration_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnPearling2Aspiration_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnPearling2Aspiration_OFF->Location = System::Drawing::Point(473, 354);
			this->btnPearling2Aspiration_OFF->Name = L"btnPearling2Aspiration_OFF";
			this->btnPearling2Aspiration_OFF->Size = System::Drawing::Size(90, 90);
			this->btnPearling2Aspiration_OFF->TabIndex = 117;
			this->btnPearling2Aspiration_OFF->Tag = L"1";
			this->btnPearling2Aspiration_OFF->Text = L"OFF";
			this->btnPearling2Aspiration_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnPearling2Aspiration_OFF->UseVisualStyleBackColor = true;
			this->btnPearling2Aspiration_OFF->Click += gcnew System::EventHandler(this, &TableManualScreen::btnPearling2Aspiration_OFF_Click);
			// 
			// btnPearling2Aspiration_ON
			// 
			this->btnPearling2Aspiration_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnPearling2Aspiration_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnPearling2Aspiration_ON->Location = System::Drawing::Point(374, 354);
			this->btnPearling2Aspiration_ON->Name = L"btnPearling2Aspiration_ON";
			this->btnPearling2Aspiration_ON->Size = System::Drawing::Size(90, 90);
			this->btnPearling2Aspiration_ON->TabIndex = 116;
			this->btnPearling2Aspiration_ON->Tag = L"1";
			this->btnPearling2Aspiration_ON->Text = L"ON";
			this->btnPearling2Aspiration_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnPearling2Aspiration_ON->UseVisualStyleBackColor = true;
			this->btnPearling2Aspiration_ON->Click += gcnew System::EventHandler(this, &TableManualScreen::btnPearling2Aspiration_ON_Click);
			// 
			// lblPearling2Aspiration
			// 
			this->lblPearling2Aspiration->AutoSize = true;
			this->lblPearling2Aspiration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblPearling2Aspiration->Location = System::Drawing::Point(47, 383);
			this->lblPearling2Aspiration->Name = L"lblPearling2Aspiration";
			this->lblPearling2Aspiration->Size = System::Drawing::Size(256, 29);
			this->lblPearling2Aspiration->TabIndex = 115;
			this->lblPearling2Aspiration->Tag = L"1";
			this->lblPearling2Aspiration->Text = L"Aspiration Pearling 2";
			// 
			// btnPearling1Aspiration_OFF
			// 
			this->btnPearling1Aspiration_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnPearling1Aspiration_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnPearling1Aspiration_OFF->Location = System::Drawing::Point(473, 255);
			this->btnPearling1Aspiration_OFF->Name = L"btnPearling1Aspiration_OFF";
			this->btnPearling1Aspiration_OFF->Size = System::Drawing::Size(90, 90);
			this->btnPearling1Aspiration_OFF->TabIndex = 114;
			this->btnPearling1Aspiration_OFF->Tag = L"1";
			this->btnPearling1Aspiration_OFF->Text = L"OFF";
			this->btnPearling1Aspiration_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnPearling1Aspiration_OFF->UseVisualStyleBackColor = true;
			this->btnPearling1Aspiration_OFF->Click += gcnew System::EventHandler(this, &TableManualScreen::btnPearling1Aspiration_OFF_Click);
			// 
			// btnPearling1Aspiration_ON
			// 
			this->btnPearling1Aspiration_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnPearling1Aspiration_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnPearling1Aspiration_ON->Location = System::Drawing::Point(374, 255);
			this->btnPearling1Aspiration_ON->Name = L"btnPearling1Aspiration_ON";
			this->btnPearling1Aspiration_ON->Size = System::Drawing::Size(90, 90);
			this->btnPearling1Aspiration_ON->TabIndex = 113;
			this->btnPearling1Aspiration_ON->Tag = L"1";
			this->btnPearling1Aspiration_ON->Text = L"ON";
			this->btnPearling1Aspiration_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnPearling1Aspiration_ON->UseVisualStyleBackColor = true;
			this->btnPearling1Aspiration_ON->Click += gcnew System::EventHandler(this, &TableManualScreen::btnPearling1Aspiration_ON_Click);
			// 
			// lblPearling1Aspiration
			// 
			this->lblPearling1Aspiration->AutoSize = true;
			this->lblPearling1Aspiration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblPearling1Aspiration->Location = System::Drawing::Point(47, 284);
			this->lblPearling1Aspiration->Name = L"lblPearling1Aspiration";
			this->lblPearling1Aspiration->Size = System::Drawing::Size(256, 29);
			this->lblPearling1Aspiration->TabIndex = 112;
			this->lblPearling1Aspiration->Tag = L"1";
			this->lblPearling1Aspiration->Text = L"Aspiration Pearling 1";
			// 
			// btnAspirationDown
			// 
			this->btnAspirationDown->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAspirationDown->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnAspirationDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAspirationDown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAspirationDown.Image")));
			this->btnAspirationDown->Location = System::Drawing::Point(473, 156);
			this->btnAspirationDown->Name = L"btnAspirationDown";
			this->btnAspirationDown->Size = System::Drawing::Size(90, 90);
			this->btnAspirationDown->TabIndex = 80;
			this->btnAspirationDown->Tag = L"1";
			this->btnAspirationDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAspirationDown->UseVisualStyleBackColor = false;
			this->btnAspirationDown->Click += gcnew System::EventHandler(this, &TableManualScreen::btnAspirationDown_Click);
			// 
			// btnAspirationUp
			// 
			this->btnAspirationUp->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAspirationUp->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnAspirationUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAspirationUp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAspirationUp.Image")));
			this->btnAspirationUp->Location = System::Drawing::Point(374, 156);
			this->btnAspirationUp->Name = L"btnAspirationUp";
			this->btnAspirationUp->Size = System::Drawing::Size(90, 90);
			this->btnAspirationUp->TabIndex = 79;
			this->btnAspirationUp->Tag = L"1";
			this->btnAspirationUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAspirationUp->UseVisualStyleBackColor = false;
			this->btnAspirationUp->Click += gcnew System::EventHandler(this, &TableManualScreen::btnAspirationUp_Click);
			// 
			// lblAspirationRoom
			// 
			this->lblAspirationRoom->AutoSize = true;
			this->lblAspirationRoom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAspirationRoom->Location = System::Drawing::Point(47, 194);
			this->lblAspirationRoom->Name = L"lblAspirationRoom";
			this->lblAspirationRoom->Size = System::Drawing::Size(130, 29);
			this->lblAspirationRoom->TabIndex = 78;
			this->lblAspirationRoom->Tag = L"1";
			this->lblAspirationRoom->Text = L"Aspiration";
			// 
			// btnIndexMoveDown
			// 
			this->btnIndexMoveDown->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnIndexMoveDown->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnIndexMoveDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnIndexMoveDown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnIndexMoveDown.Image")));
			this->btnIndexMoveDown->Location = System::Drawing::Point(473, 57);
			this->btnIndexMoveDown->Name = L"btnIndexMoveDown";
			this->btnIndexMoveDown->Size = System::Drawing::Size(90, 90);
			this->btnIndexMoveDown->TabIndex = 75;
			this->btnIndexMoveDown->Tag = L"1";
			this->btnIndexMoveDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnIndexMoveDown->UseVisualStyleBackColor = false;
			this->btnIndexMoveDown->Click += gcnew System::EventHandler(this, &TableManualScreen::btnIndexMoveDown_Click);
			// 
			// btnIndexMoveUp
			// 
			this->btnIndexMoveUp->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnIndexMoveUp->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnIndexMoveUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnIndexMoveUp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnIndexMoveUp.Image")));
			this->btnIndexMoveUp->Location = System::Drawing::Point(374, 57);
			this->btnIndexMoveUp->Name = L"btnIndexMoveUp";
			this->btnIndexMoveUp->Size = System::Drawing::Size(90, 90);
			this->btnIndexMoveUp->TabIndex = 74;
			this->btnIndexMoveUp->Tag = L"1";
			this->btnIndexMoveUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnIndexMoveUp->UseVisualStyleBackColor = false;
			this->btnIndexMoveUp->Click += gcnew System::EventHandler(this, &TableManualScreen::btnIndexMoveUp_Click);
			// 
			// lblIndexing
			// 
			this->lblIndexing->AutoSize = true;
			this->lblIndexing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblIndexing->Location = System::Drawing::Point(47, 95);
			this->lblIndexing->Name = L"lblIndexing";
			this->lblIndexing->Size = System::Drawing::Size(76, 29);
			this->lblIndexing->TabIndex = 72;
			this->lblIndexing->Tag = L"1";
			this->lblIndexing->Text = L"Index";
			// 
			// gbAxisTable
			// 
			this->gbAxisTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbAxisTable->Location = System::Drawing::Point(764, 5);
			this->gbAxisTable->Name = L"gbAxisTable";
			this->gbAxisTable->Size = System::Drawing::Size(728, 375);
			this->gbAxisTable->TabIndex = 41;
			this->gbAxisTable->TabStop = false;
			this->gbAxisTable->Tag = L"2";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->lblDisableCleanAfterPearl);
			this->tabPage2->Controls->Add(this->cbDisableCleanAfterPearl);
			this->tabPage2->Controls->Add(this->btnBrushAspiration_OFF);
			this->tabPage2->Controls->Add(this->btnBrushAspiration_ON);
			this->tabPage2->Controls->Add(this->lblBrushAspiration);
			this->tabPage2->Controls->Add(this->gbAxisBrush);
			this->tabPage2->Location = System::Drawing::Point(4, 49);
			this->tabPage2->Margin = System::Windows::Forms::Padding(5);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1570, 842);
			this->tabPage2->TabIndex = 2;
			this->tabPage2->Text = L"Brush";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// lblDisableCleanAfterPearl
			// 
			this->lblDisableCleanAfterPearl->AutoSize = true;
			this->lblDisableCleanAfterPearl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblDisableCleanAfterPearl->Location = System::Drawing::Point(82, 162);
			this->lblDisableCleanAfterPearl->Name = L"lblDisableCleanAfterPearl";
			this->lblDisableCleanAfterPearl->Size = System::Drawing::Size(422, 29);
			this->lblDisableCleanAfterPearl->TabIndex = 115;
			this->lblDisableCleanAfterPearl->Tag = L"1";
			this->lblDisableCleanAfterPearl->Text = L"Désactiver brossage aprés perlage";
			// 
			// cbDisableCleanAfterPearl
			// 
			this->cbDisableCleanAfterPearl->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbDisableCleanAfterPearl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->cbDisableCleanAfterPearl->Location = System::Drawing::Point(28, 152);
			this->cbDisableCleanAfterPearl->Margin = System::Windows::Forms::Padding(5);
			this->cbDisableCleanAfterPearl->Name = L"cbDisableCleanAfterPearl";
			this->cbDisableCleanAfterPearl->Size = System::Drawing::Size(46, 50);
			this->cbDisableCleanAfterPearl->TabIndex = 116;
			this->cbDisableCleanAfterPearl->Tag = L"1";
			this->cbDisableCleanAfterPearl->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbDisableCleanAfterPearl->UseVisualStyleBackColor = true;
			this->cbDisableCleanAfterPearl->CheckedChanged += gcnew System::EventHandler(this, &TableManualScreen::cbDisableCleanAfterPearl_CheckedChanged);
			// 
			// btnBrushAspiration_OFF
			// 
			this->btnBrushAspiration_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnBrushAspiration_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnBrushAspiration_OFF->Location = System::Drawing::Point(513, 9);
			this->btnBrushAspiration_OFF->Name = L"btnBrushAspiration_OFF";
			this->btnBrushAspiration_OFF->Size = System::Drawing::Size(90, 90);
			this->btnBrushAspiration_OFF->TabIndex = 114;
			this->btnBrushAspiration_OFF->Tag = L"1";
			this->btnBrushAspiration_OFF->Text = L"OFF";
			this->btnBrushAspiration_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnBrushAspiration_OFF->UseVisualStyleBackColor = true;
			this->btnBrushAspiration_OFF->Click += gcnew System::EventHandler(this, &TableManualScreen::btnBrushAspiration_OFF_Click);
			// 
			// btnBrushAspiration_ON
			// 
			this->btnBrushAspiration_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnBrushAspiration_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnBrushAspiration_ON->Location = System::Drawing::Point(414, 9);
			this->btnBrushAspiration_ON->Name = L"btnBrushAspiration_ON";
			this->btnBrushAspiration_ON->Size = System::Drawing::Size(90, 90);
			this->btnBrushAspiration_ON->TabIndex = 113;
			this->btnBrushAspiration_ON->Tag = L"1";
			this->btnBrushAspiration_ON->Text = L"ON";
			this->btnBrushAspiration_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnBrushAspiration_ON->UseVisualStyleBackColor = true;
			this->btnBrushAspiration_ON->Click += gcnew System::EventHandler(this, &TableManualScreen::btnBrushAspiration_ON_Click);
			// 
			// lblBrushAspiration
			// 
			this->lblBrushAspiration->AutoSize = true;
			this->lblBrushAspiration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBrushAspiration->Location = System::Drawing::Point(32, 38);
			this->lblBrushAspiration->Name = L"lblBrushAspiration";
			this->lblBrushAspiration->Size = System::Drawing::Size(204, 29);
			this->lblBrushAspiration->TabIndex = 112;
			this->lblBrushAspiration->Tag = L"1";
			this->lblBrushAspiration->Text = L"Aspiration Brush";
			// 
			// gbAxisBrush
			// 
			this->gbAxisBrush->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbAxisBrush->Location = System::Drawing::Point(764, 5);
			this->gbAxisBrush->Name = L"gbAxisBrush";
			this->gbAxisBrush->Size = System::Drawing::Size(728, 600);
			this->gbAxisBrush->TabIndex = 90;
			this->gbAxisBrush->TabStop = false;
			this->gbAxisBrush->Tag = L"2";
			this->gbAxisBrush->Enter += gcnew System::EventHandler(this, &TableManualScreen::gbAxisBrush_Enter);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->lblRateOfFlow2);
			this->tabPage3->Controls->Add(this->lblRateOfFlow4);
			this->tabPage3->Controls->Add(this->lblRateOfFlow1);
			this->tabPage3->Controls->Add(this->lblRateOfFlow3);
			this->tabPage3->Controls->Add(this->lblVacuumThreshold4);
			this->tabPage3->Controls->Add(this->lblVacuumThreshold3);
			this->tabPage3->Controls->Add(this->lblVacuumThreshold2);
			this->tabPage3->Controls->Add(this->lblVacuumThreshold1);
			this->tabPage3->Controls->Add(this->tbVacuum4);
			this->tabPage3->Controls->Add(this->tbVacuum3);
			this->tabPage3->Controls->Add(this->tbVacuum2);
			this->tabPage3->Controls->Add(this->tbVacuum1);
			this->tabPage3->Controls->Add(this->btnVacuum1_OFF);
			this->tabPage3->Controls->Add(this->btnVacuum1_ON);
			this->tabPage3->Controls->Add(this->lblVacuumPos1);
			this->tabPage3->Controls->Add(this->btnVacuum2_OFF);
			this->tabPage3->Controls->Add(this->btnVacuum2_ON);
			this->tabPage3->Controls->Add(this->lblVacuumPos2);
			this->tabPage3->Controls->Add(this->btnVacuum3_OFF);
			this->tabPage3->Controls->Add(this->btnVacuum3_ON);
			this->tabPage3->Controls->Add(this->lblVacuumPos3);
			this->tabPage3->Controls->Add(this->btnVacuum4_OFF);
			this->tabPage3->Controls->Add(this->btnVacuum4_ON);
			this->tabPage3->Controls->Add(this->lblVacuumPos4);
			this->tabPage3->Location = System::Drawing::Point(4, 49);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(1570, 842);
			this->tabPage3->TabIndex = 3;
			this->tabPage3->Text = L"Vacuum";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// lblRateOfFlow2
			// 
			this->lblRateOfFlow2->AutoSize = true;
			this->lblRateOfFlow2->Location = System::Drawing::Point(960, 160);
			this->lblRateOfFlow2->Name = L"lblRateOfFlow2";
			this->lblRateOfFlow2->Size = System::Drawing::Size(86, 29);
			this->lblRateOfFlow2->TabIndex = 153;
			this->lblRateOfFlow2->Tag = L"1";
			this->lblRateOfFlow2->Text = L"[l/min]";
			// 
			// lblRateOfFlow4
			// 
			this->lblRateOfFlow4->AutoSize = true;
			this->lblRateOfFlow4->Location = System::Drawing::Point(960, 381);
			this->lblRateOfFlow4->Name = L"lblRateOfFlow4";
			this->lblRateOfFlow4->Size = System::Drawing::Size(86, 29);
			this->lblRateOfFlow4->TabIndex = 153;
			this->lblRateOfFlow4->Tag = L"1";
			this->lblRateOfFlow4->Text = L"[l/min]";
			// 
			// lblRateOfFlow1
			// 
			this->lblRateOfFlow1->AutoSize = true;
			this->lblRateOfFlow1->Location = System::Drawing::Point(960, 47);
			this->lblRateOfFlow1->Name = L"lblRateOfFlow1";
			this->lblRateOfFlow1->Size = System::Drawing::Size(86, 29);
			this->lblRateOfFlow1->TabIndex = 154;
			this->lblRateOfFlow1->Tag = L"1";
			this->lblRateOfFlow1->Text = L"[l/min]";
			// 
			// lblRateOfFlow3
			// 
			this->lblRateOfFlow3->AutoSize = true;
			this->lblRateOfFlow3->Location = System::Drawing::Point(960, 273);
			this->lblRateOfFlow3->Name = L"lblRateOfFlow3";
			this->lblRateOfFlow3->Size = System::Drawing::Size(86, 29);
			this->lblRateOfFlow3->TabIndex = 154;
			this->lblRateOfFlow3->Tag = L"1";
			this->lblRateOfFlow3->Text = L"[l/min]";
			// 
			// lblVacuumThreshold4
			// 
			this->lblVacuumThreshold4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblVacuumThreshold4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblVacuumThreshold4->EditText = L"";
			this->lblVacuumThreshold4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblVacuumThreshold4->Location = System::Drawing::Point(740, 375);
			this->lblVacuumThreshold4->Margin = System::Windows::Forms::Padding(5);
			this->lblVacuumThreshold4->Name = L"lblVacuumThreshold4";
			this->lblVacuumThreshold4->Offset = static_cast<System::UInt32>(0);
			this->lblVacuumThreshold4->Size = System::Drawing::Size(212, 45);
			this->lblVacuumThreshold4->TabIndex = 122;
			this->lblVacuumThreshold4->Tag = L"1";
			this->lblVacuumThreshold4->Text = L"0";
			this->lblVacuumThreshold4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblVacuumThreshold4->Click += gcnew System::EventHandler(this, &TableManualScreen::lblVacuumThreshold_Click);
			// 
			// lblVacuumThreshold3
			// 
			this->lblVacuumThreshold3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblVacuumThreshold3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblVacuumThreshold3->EditText = L"";
			this->lblVacuumThreshold3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblVacuumThreshold3->Location = System::Drawing::Point(740, 267);
			this->lblVacuumThreshold3->Margin = System::Windows::Forms::Padding(5);
			this->lblVacuumThreshold3->Name = L"lblVacuumThreshold3";
			this->lblVacuumThreshold3->Offset = static_cast<System::UInt32>(0);
			this->lblVacuumThreshold3->Size = System::Drawing::Size(212, 45);
			this->lblVacuumThreshold3->TabIndex = 121;
			this->lblVacuumThreshold3->Tag = L"1";
			this->lblVacuumThreshold3->Text = L"0";
			this->lblVacuumThreshold3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblVacuumThreshold3->Click += gcnew System::EventHandler(this, &TableManualScreen::lblVacuumThreshold_Click);
			// 
			// lblVacuumThreshold2
			// 
			this->lblVacuumThreshold2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblVacuumThreshold2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblVacuumThreshold2->EditText = L"";
			this->lblVacuumThreshold2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblVacuumThreshold2->Location = System::Drawing::Point(740, 156);
			this->lblVacuumThreshold2->Margin = System::Windows::Forms::Padding(5);
			this->lblVacuumThreshold2->Name = L"lblVacuumThreshold2";
			this->lblVacuumThreshold2->Offset = static_cast<System::UInt32>(0);
			this->lblVacuumThreshold2->Size = System::Drawing::Size(212, 45);
			this->lblVacuumThreshold2->TabIndex = 120;
			this->lblVacuumThreshold2->Tag = L"1";
			this->lblVacuumThreshold2->Text = L"0";
			this->lblVacuumThreshold2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblVacuumThreshold2->Click += gcnew System::EventHandler(this, &TableManualScreen::lblVacuumThreshold_Click);
			// 
			// lblVacuumThreshold1
			// 
			this->lblVacuumThreshold1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblVacuumThreshold1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblVacuumThreshold1->EditText = L"";
			this->lblVacuumThreshold1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblVacuumThreshold1->Location = System::Drawing::Point(740, 41);
			this->lblVacuumThreshold1->Margin = System::Windows::Forms::Padding(5);
			this->lblVacuumThreshold1->Name = L"lblVacuumThreshold1";
			this->lblVacuumThreshold1->Offset = static_cast<System::UInt32>(0);
			this->lblVacuumThreshold1->Size = System::Drawing::Size(212, 45);
			this->lblVacuumThreshold1->TabIndex = 119;
			this->lblVacuumThreshold1->Tag = L"1";
			this->lblVacuumThreshold1->Text = L"0";
			this->lblVacuumThreshold1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblVacuumThreshold1->Click += gcnew System::EventHandler(this, &TableManualScreen::lblVacuumThreshold_Click);
			// 
			// tbVacuum4
			// 
			this->tbVacuum4->Location = System::Drawing::Point(566, 378);
			this->tbVacuum4->Name = L"tbVacuum4";
			this->tbVacuum4->ReadOnly = true;
			this->tbVacuum4->Size = System::Drawing::Size(162, 35);
			this->tbVacuum4->TabIndex = 118;
			this->tbVacuum4->Tag = L"1";
			this->tbVacuum4->Text = L"0.00";
			this->tbVacuum4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tbVacuum3
			// 
			this->tbVacuum3->Location = System::Drawing::Point(566, 270);
			this->tbVacuum3->Name = L"tbVacuum3";
			this->tbVacuum3->ReadOnly = true;
			this->tbVacuum3->Size = System::Drawing::Size(162, 35);
			this->tbVacuum3->TabIndex = 117;
			this->tbVacuum3->Tag = L"1";
			this->tbVacuum3->Text = L"0.00";
			this->tbVacuum3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tbVacuum2
			// 
			this->tbVacuum2->Location = System::Drawing::Point(566, 159);
			this->tbVacuum2->Name = L"tbVacuum2";
			this->tbVacuum2->ReadOnly = true;
			this->tbVacuum2->Size = System::Drawing::Size(162, 35);
			this->tbVacuum2->TabIndex = 116;
			this->tbVacuum2->Tag = L"1";
			this->tbVacuum2->Text = L"0.00";
			this->tbVacuum2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tbVacuum1
			// 
			this->tbVacuum1->Location = System::Drawing::Point(566, 44);
			this->tbVacuum1->Name = L"tbVacuum1";
			this->tbVacuum1->ReadOnly = true;
			this->tbVacuum1->Size = System::Drawing::Size(162, 35);
			this->tbVacuum1->TabIndex = 115;
			this->tbVacuum1->Tag = L"1";
			this->tbVacuum1->Text = L"0.00";
			this->tbVacuum1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnVacuum1_OFF
			// 
			this->btnVacuum1_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum1_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum1_OFF->Location = System::Drawing::Point(467, 20);
			this->btnVacuum1_OFF->Name = L"btnVacuum1_OFF";
			this->btnVacuum1_OFF->Size = System::Drawing::Size(90, 90);
			this->btnVacuum1_OFF->TabIndex = 83;
			this->btnVacuum1_OFF->Tag = L"0";
			this->btnVacuum1_OFF->Text = L"OFF";
			this->btnVacuum1_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum1_OFF->UseVisualStyleBackColor = true;
			this->btnVacuum1_OFF->Click += gcnew System::EventHandler(this, &TableManualScreen::btnVacuum1_OFF_Click);
			// 
			// btnVacuum1_ON
			// 
			this->btnVacuum1_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum1_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum1_ON->Location = System::Drawing::Point(368, 20);
			this->btnVacuum1_ON->Name = L"btnVacuum1_ON";
			this->btnVacuum1_ON->Size = System::Drawing::Size(90, 90);
			this->btnVacuum1_ON->TabIndex = 82;
			this->btnVacuum1_ON->Tag = L"0";
			this->btnVacuum1_ON->Text = L"ON";
			this->btnVacuum1_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum1_ON->UseVisualStyleBackColor = true;
			this->btnVacuum1_ON->Click += gcnew System::EventHandler(this, &TableManualScreen::btnVacuum1_ON_Click);
			// 
			// lblVacuumPos1
			// 
			this->lblVacuumPos1->AutoSize = true;
			this->lblVacuumPos1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuumPos1->Location = System::Drawing::Point(41, 48);
			this->lblVacuumPos1->Name = L"lblVacuumPos1";
			this->lblVacuumPos1->Size = System::Drawing::Size(0, 29);
			this->lblVacuumPos1->TabIndex = 81;
			this->lblVacuumPos1->Tag = L"0";
			// 
			// btnVacuum2_OFF
			// 
			this->btnVacuum2_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum2_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum2_OFF->Location = System::Drawing::Point(467, 135);
			this->btnVacuum2_OFF->Name = L"btnVacuum2_OFF";
			this->btnVacuum2_OFF->Size = System::Drawing::Size(90, 90);
			this->btnVacuum2_OFF->TabIndex = 80;
			this->btnVacuum2_OFF->Tag = L"0";
			this->btnVacuum2_OFF->Text = L"OFF";
			this->btnVacuum2_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum2_OFF->UseVisualStyleBackColor = true;
			this->btnVacuum2_OFF->Click += gcnew System::EventHandler(this, &TableManualScreen::btnVacuum2_OFF_Click);
			// 
			// btnVacuum2_ON
			// 
			this->btnVacuum2_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum2_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum2_ON->Location = System::Drawing::Point(368, 135);
			this->btnVacuum2_ON->Name = L"btnVacuum2_ON";
			this->btnVacuum2_ON->Size = System::Drawing::Size(90, 90);
			this->btnVacuum2_ON->TabIndex = 79;
			this->btnVacuum2_ON->Tag = L"0";
			this->btnVacuum2_ON->Text = L"ON";
			this->btnVacuum2_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum2_ON->UseVisualStyleBackColor = true;
			this->btnVacuum2_ON->Click += gcnew System::EventHandler(this, &TableManualScreen::btnVacuum2_ON_Click);
			// 
			// lblVacuumPos2
			// 
			this->lblVacuumPos2->AutoSize = true;
			this->lblVacuumPos2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuumPos2->Location = System::Drawing::Point(41, 164);
			this->lblVacuumPos2->Name = L"lblVacuumPos2";
			this->lblVacuumPos2->Size = System::Drawing::Size(0, 29);
			this->lblVacuumPos2->TabIndex = 78;
			this->lblVacuumPos2->Tag = L"0";
			// 
			// btnVacuum3_OFF
			// 
			this->btnVacuum3_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum3_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum3_OFF->Location = System::Drawing::Point(467, 246);
			this->btnVacuum3_OFF->Name = L"btnVacuum3_OFF";
			this->btnVacuum3_OFF->Size = System::Drawing::Size(90, 90);
			this->btnVacuum3_OFF->TabIndex = 77;
			this->btnVacuum3_OFF->Tag = L"0";
			this->btnVacuum3_OFF->Text = L"OFF";
			this->btnVacuum3_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum3_OFF->UseVisualStyleBackColor = true;
			this->btnVacuum3_OFF->Click += gcnew System::EventHandler(this, &TableManualScreen::btnVacuum3_OFF_Click);
			// 
			// btnVacuum3_ON
			// 
			this->btnVacuum3_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum3_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum3_ON->Location = System::Drawing::Point(368, 246);
			this->btnVacuum3_ON->Name = L"btnVacuum3_ON";
			this->btnVacuum3_ON->Size = System::Drawing::Size(90, 90);
			this->btnVacuum3_ON->TabIndex = 76;
			this->btnVacuum3_ON->Tag = L"0";
			this->btnVacuum3_ON->Text = L"ON";
			this->btnVacuum3_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum3_ON->UseVisualStyleBackColor = true;
			this->btnVacuum3_ON->Click += gcnew System::EventHandler(this, &TableManualScreen::btnVacuum3_ON_Click);
			// 
			// lblVacuumPos3
			// 
			this->lblVacuumPos3->AutoSize = true;
			this->lblVacuumPos3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuumPos3->Location = System::Drawing::Point(41, 275);
			this->lblVacuumPos3->Name = L"lblVacuumPos3";
			this->lblVacuumPos3->Size = System::Drawing::Size(0, 29);
			this->lblVacuumPos3->TabIndex = 75;
			this->lblVacuumPos3->Tag = L"0";
			// 
			// btnVacuum4_OFF
			// 
			this->btnVacuum4_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum4_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum4_OFF->Location = System::Drawing::Point(467, 354);
			this->btnVacuum4_OFF->Name = L"btnVacuum4_OFF";
			this->btnVacuum4_OFF->Size = System::Drawing::Size(90, 90);
			this->btnVacuum4_OFF->TabIndex = 74;
			this->btnVacuum4_OFF->Tag = L"0";
			this->btnVacuum4_OFF->Text = L"OFF";
			this->btnVacuum4_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum4_OFF->UseVisualStyleBackColor = true;
			this->btnVacuum4_OFF->Click += gcnew System::EventHandler(this, &TableManualScreen::btnVacuum4_OFF_Click);
			// 
			// btnVacuum4_ON
			// 
			this->btnVacuum4_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuum4_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuum4_ON->Location = System::Drawing::Point(368, 354);
			this->btnVacuum4_ON->Name = L"btnVacuum4_ON";
			this->btnVacuum4_ON->Size = System::Drawing::Size(90, 90);
			this->btnVacuum4_ON->TabIndex = 73;
			this->btnVacuum4_ON->Tag = L"0";
			this->btnVacuum4_ON->Text = L"ON";
			this->btnVacuum4_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuum4_ON->UseVisualStyleBackColor = true;
			this->btnVacuum4_ON->Click += gcnew System::EventHandler(this, &TableManualScreen::btnVacuum4_ON_Click);
			// 
			// lblVacuumPos4
			// 
			this->lblVacuumPos4->AutoSize = true;
			this->lblVacuumPos4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuumPos4->Location = System::Drawing::Point(41, 383);
			this->lblVacuumPos4->Name = L"lblVacuumPos4";
			this->lblVacuumPos4->Size = System::Drawing::Size(0, 29);
			this->lblVacuumPos4->TabIndex = 72;
			this->lblVacuumPos4->Tag = L"0";
			// 
			// TableManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"TableManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &TableManualScreen::TableManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void btnIndexMoveDown_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Indexing) + " OFF");
			ClearTCManData(s_TableManual.MT_IndexTable.MB_Activate);
		 }
private: System::Void btnIndexMoveUp_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Indexing) + "ON");
			SetTCManData(s_TableManual.MT_IndexTable.MB_Activate);
		 }
private: System::Void btnAspirationUp_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::OpenAspirationRoom));
			ClearTCManData(s_TableManual.MT_AspirationDown.MB_Activate);
		 }
private: System::Void btnAspirationDown_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::CloseAspirationRoom));
			SetTCManData(s_TableManual.MT_AspirationDown.MB_Activate);
		 }
private: System::Void btnVacuum1_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::EnableVacuum) + " 1");
			SetTCManData(s_TableManual.MT_VacuumPos1.MB_Activate);
		 }
private: System::Void btnVacuum1_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::DisableVacuum) + " 1");
			ClearTCManData(s_TableManual.MT_VacuumPos1.MB_Activate);
		 }
private: System::Void btnVacuum2_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::EnableVacuum) + " 2");
			SetTCManData(s_TableManual.MT_VacuumPos2.MB_Activate);
		 }
private: System::Void btnVacuum2_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::DisableVacuum) + " 2");
			ClearTCManData(s_TableManual.MT_VacuumPos2.MB_Activate);
		 }
private: System::Void btnVacuum3_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::EnableVacuum) + " 3");
			SetTCManData(s_TableManual.MT_VacuumPos3.MB_Activate);
		 }
private: System::Void btnVacuum3_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::DisableVacuum) + " 3");
			ClearTCManData(s_TableManual.MT_VacuumPos3.MB_Activate);
		 }
private: System::Void btnVacuum4_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::EnableVacuum) + " 4");
			SetTCManData(s_TableManual.MT_VacuumPos4.MB_Activate);
		 }
private: System::Void btnVacuum4_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::DisableVacuum) + " 4");
			ClearTCManData(s_TableManual.MT_VacuumPos4.MB_Activate);
		 }
private: System::Void TableManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			gbAxisTable->Text = L"  " + TUtilities::pS_LoadString(TextIndex::Axis) + "  ";

			tabControl->TabPages[0]->Text = TUtilities::pS_LoadString(TextIndex::Table);
			tabControl->TabPages[1]->Text = TUtilities::pS_LoadString(TextIndex::Brush);
			tabControl->TabPages[2]->Text = TUtilities::pS_LoadString(TextIndex::Vacuum);

			lblAspirationRoom->Text = TUtilities::pS_LoadString(TextIndex::AspirationRoom);
			lblIndexing->Text = TUtilities::pS_LoadString(TextIndex::Indexing);
			lblVacuumPos1->Text = TUtilities::pS_LoadString(TextIndex::VacuumPosition) + " A";
			lblVacuumPos2->Text = TUtilities::pS_LoadString(TextIndex::VacuumPosition) + " B";
			lblVacuumPos3->Text = TUtilities::pS_LoadString(TextIndex::VacuumPosition) + " C";
			lblVacuumPos4->Text = TUtilities::pS_LoadString(TextIndex::VacuumPosition) + " D";
			lblCleanBrush->Text = TUtilities::pS_LoadString(TextIndex::Brush);

			lblVacuumThreshold1->EditText = TUtilities::pS_LoadString(TextIndex::VacuumPosition) + " A";
			lblVacuumThreshold2->EditText = TUtilities::pS_LoadString(TextIndex::VacuumPosition) + " B";
			lblVacuumThreshold3->EditText = TUtilities::pS_LoadString(TextIndex::VacuumPosition) + " C";
			lblVacuumThreshold4->EditText = TUtilities::pS_LoadString(TextIndex::VacuumPosition) + " D";

			lblBrushAspiration->Text = TUtilities::pS_LoadString(TextIndex::Aspiration);
			lblPearling1Aspiration->Text = TUtilities::pS_LoadString(TextIndex::AspirationPearling1);
			lblPearling2Aspiration->Text = TUtilities::pS_LoadString(TextIndex::AspirationPearling2);
			lblDisableCleanAfterPearl->Text = TUtilities::pS_LoadString(TextIndex::DisableCleanAfterPearling);

			pT_DriveTable->ReloadComponent();
			pT_DriveTable->SetPositionName(0,TUtilities::pS_LoadString(TextIndex::Loader));
			pT_DriveTable->SetPositionName(1,TUtilities::pS_LoadString(TextIndex::Pearling));
			pT_DriveTable->SetDriveName(tabControl->TabPages[0]->Text,"");
		 
			pT_DriveBrush->ReloadComponent();
			pT_DriveBrush->SetPositionName(0, TUtilities::pS_LoadString(TextIndex::Park) + " 1");
			pT_DriveBrush->SetPositionName(1, TUtilities::pS_LoadString(TextIndex::Park) + " 2");
			pT_DriveBrush->SetPositionName(2, TUtilities::pS_LoadString(TextIndex::Work) + " 1");
			pT_DriveBrush->SetPositionName(3, TUtilities::pS_LoadString(TextIndex::Work) + " 2");
			pT_DriveBrush->SetDriveName(tabControl->TabPages[0]->Text, "");
		}
private: System::Void btnPearling1Aspiration_ON_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::AspirationPearling1) + "ON");
	SetTCManData(s_PearlingManual.MP_ActivateAspirationTable[0].MB_Activate);
}
private: System::Void btnPearling1Aspiration_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::AspirationPearling1) + "OFF");
	ClearTCManData(s_PearlingManual.MP_ActivateAspirationTable[0].MB_Activate);
}
private: System::Void btnPearling2Aspiration_ON_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::AspirationPearling2) + "ON");
	SetTCManData(s_PearlingManual.MP_ActivateAspirationTable[1].MB_Activate);
}
private: System::Void btnPearling2Aspiration_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::AspirationPearling2) + "OFF");
	ClearTCManData(s_PearlingManual.MP_ActivateAspirationTable[1].MB_Activate);
}
private: System::Void btnBrushAspiration_ON_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Aspiration) + "ON");
	SetTCManData(s_TableManual.MT_AspirationBrush.MB_Activate);
}
private: System::Void btnBrushAspiration_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Aspiration) + "OFF");
	ClearTCManData(s_TableManual.MT_AspirationBrush.MB_Activate);
}
		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
private: System::Void lblVacuumThreshold_Click(System::Object^  sender, System::EventArgs^  e) {
	LabelOffset^ lbl = (LabelOffset^)sender;
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lbl->EditText, double::Parse(lbl->Text), 0, 9, "F2");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(lbl->EditText + L" : = " + Keypad->Value.ToString());
		WriteTCManOffsetData(lbl->Offset, (TC_LREAL)Keypad->Value);
	}
}
private: System::Void cbDisableCleanAfterPearl_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (cbDisableCleanAfterPearl->Checked)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::DisableCleanAfterPearling) + L" = ON");
		SetTCData(s_MachineOpt.MO_DisableCleanAfterPearling);
	}
	else
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::DisableCleanAfterPearling) + L" = OFF");
		ClearTCData(s_MachineOpt.MO_DisableCleanAfterPearling);
	}
}
private: System::Void btnCleanBrushUp_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Brush) + "UP");
	ClearTCManData(s_TableManual.MT_CleanBrushDown.MB_Activate);
}
private: System::Void btnCleanBrushDown_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[0]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Brush) + "DOWN");
	SetTCManData(s_TableManual.MT_CleanBrushDown.MB_Activate);
}
private: System::Void gbAxisBrush_Enter(System::Object^  sender, System::EventArgs^  e) {
}
};
}
