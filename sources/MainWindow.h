#pragma once

#include "TTwincatInterface.h"
#include "MyMsgBox.h"
#include "global.h"
#include "login.h"
#include "UserManager.h"
#include "ProdScreen.h"
#include "RejectScreen.h"
#include "AlarmScreen.h"
#include "LogScreen.h"
#include "MachineScreen.h"
#include "DashboardScreen.h"
#include "CounterScreen.h"
#include "TJobLogger.h"

#define ShowScreen(pT_ScreenToShow) \
	pT_ProdScreen->Hide();\
	pT_AlarmScreen->Hide();\
	pT_LogScreen->Hide();\
	pT_MachineScreen->Hide();\
	pT_DashboardScreen->Hide();\
	pT_CounterScreen->Hide();\
	pT_ScreenToShow->Reload();\
	pT_ScreenToShow->Show();

#define HideAllScreen() \
	pT_ProdScreen->Hide();\
	pT_AlarmScreen->Hide();\
	pT_LogScreen->Hide();\
	pT_DashboardScreen->Hide();\
	pT_CounterScreen->Hide();\
	pT_MachineScreen->Hide();

enum Screens {e_NoScreen,e_ProdScreen,e_AlarmScreen,e_LogScreen,e_MachineScreen,e_BaseMachineScreen, e_DashboardScreen, e_CounterScreen};

namespace Projet1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		MainForm(String^ CommandLine)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			apT_ExportFile = gcnew array<StreamWriter^>(2);
			at_LastLog = gcnew array<DateTime>(2);
			apT_ExportFile[0] = nullptr;
			apT_ExportFile[1] = nullptr;
			b_NeedCleanup = true;
			b_ScreensLoaded = false;
			eMachineMode = MM_Stopped;
			eLastMachineMode = eMachineMode;
			worker = gcnew System::ComponentModel::BackgroundWorker();
			pTTwincatInterface = gcnew TTwincatInterface(C_AUTOMATION_VAR,C_MANUAL_VAR,C_CONFIG_VAR,CommandLine);
			if (pTTwincatInterface->IsConnected())
			{
				pTTwincatInterface->SetThisPtr(pTTwincatInterface);
			}
			else
			{
				MyMsgBox^ pT_l_CheckAutomation = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::UnableToConnectToAutomation),TUtilities::pS_LoadString(TextIndex::ConnectionError),MessageBoxButtons::OK);
				 pT_l_CheckAutomation->ShowDialog();
				 Application::Exit();
			}
			this->timer1->Enabled = true;
			worker->WorkerSupportsCancellation = true;
			worker->WorkerReportsProgress = true;
			worker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Projet1::MainForm::OnDoWork);
			worker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Projet1::MainForm::OnProgressChanged);
			worker->RunWorkerAsync();
		}
	private: System::Windows::Forms::Button^  btnStop;
	private: System::Windows::Forms::Button^  btnLockDoor;
	private: System::Windows::Forms::Button^  btnMinimize;

	private: System::Windows::Forms::Button^  btnPause;

	public: 

	public: 
		// Our specific functions
	System::Void SetCounterScreen() {
		e_NewScreen = e_CounterScreen;
	}
	private:
		bool b_ScreensLoaded;
		MachineModes eMachineMode;
		MachineModes eLastMachineMode;
		bool b_NeedCleanup;
		DateTime t_LastCleanUp;
		array<DateTime>^ at_LastLog;
		array<StreamWriter^>^ apT_ExportFile;
	private: System::Windows::Forms::Button^  btnDashboard;

			 TTwincatInterface^ pTTwincatInterface;
		void UpdateUI(void);
		void UpdateLoginData(void);
		void LogProbing();
		void CleanUpLogProbing();
		void MainForm::LoadScreen(enum Screens e_x_NewScreen);
	public:

	private: System::Windows::Forms::Button^  btnStart;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  btnReset;
	private: System::Windows::Forms::Button^  btnExit;
	private: System::Windows::Forms::Button^  btnManual;
	private: System::Windows::Forms::Button^  btnInit;
	private: System::Windows::Forms::Button^  btnUnlockDoor;


	private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Button^  btnUsers;

	private: System::Windows::Forms::Button^  btnLogout;
	private: System::Windows::Forms::Button^  btnlog;
	private: System::Windows::Forms::Button^  btnMachine;
	private: System::Windows::Forms::Button^  btnProduction;
	private: System::Windows::Forms::Button^  btnAlarms;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Label^  lblStatus;

	private: System::Windows::Forms::Label^  lblMachine;

	private: System::Windows::Forms::Label^  lblStatusN;
	private: System::Windows::Forms::Label^  lblMachineN;




	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Label^  lblTime;
	private: System::Windows::Forms::Label^  lblTeam;
	private: System::Windows::Forms::Label^  lblDate;
	private: System::Windows::Forms::Label^  lblUser;
	private: System::Windows::Forms::Label^  lblTimeN;

	private: System::Windows::Forms::Label^  lblTeamN;
	private: System::Windows::Forms::Label^  lblDateN;


	private: System::Windows::Forms::Label^  lblUserN;


	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::Label^  lblPart;

	private: System::Windows::Forms::Label^  lblOrder;
	private: System::Windows::Forms::Label^  lblPartN;



	private: System::Windows::Forms::Label^  lblOrderN;

	private: System::Windows::Forms::Label^  lblLastAlarm;



	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::BackgroundWorker^ worker;
	

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MainForm()
		{
			if (worker->IsBusy)
			{
				worker->CancelAsync();
			}
			if (components)
			{
				delete components;
			}
		}

	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		ProdScreen^ pT_ProdScreen;
		AlarmScreen^ pT_AlarmScreen;
		LogScreen^ pT_LogScreen;
		MachineScreen^ pT_MachineScreen;
		DashboardScreen^ pT_DashboardScreen;
		CounterScreen^ pT_CounterScreen;
		enum Screens e_CurrentScreen;
		static enum Screens e_NewScreen;
	/// </summary>


#pragma region Windows Form Designer generated codeMYForm
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btnDashboard = (gcnew System::Windows::Forms::Button());
			this->btnPause = (gcnew System::Windows::Forms::Button());
			this->btnMinimize = (gcnew System::Windows::Forms::Button());
			this->btnLockDoor = (gcnew System::Windows::Forms::Button());
			this->btnStop = (gcnew System::Windows::Forms::Button());
			this->btnReset = (gcnew System::Windows::Forms::Button());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->btnManual = (gcnew System::Windows::Forms::Button());
			this->btnInit = (gcnew System::Windows::Forms::Button());
			this->btnUnlockDoor = (gcnew System::Windows::Forms::Button());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->btnUsers = (gcnew System::Windows::Forms::Button());
			this->btnLogout = (gcnew System::Windows::Forms::Button());
			this->btnlog = (gcnew System::Windows::Forms::Button());
			this->btnMachine = (gcnew System::Windows::Forms::Button());
			this->btnProduction = (gcnew System::Windows::Forms::Button());
			this->btnAlarms = (gcnew System::Windows::Forms::Button());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->lblMachine = (gcnew System::Windows::Forms::Label());
			this->lblStatusN = (gcnew System::Windows::Forms::Label());
			this->lblMachineN = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->lblTime = (gcnew System::Windows::Forms::Label());
			this->lblTeam = (gcnew System::Windows::Forms::Label());
			this->lblDate = (gcnew System::Windows::Forms::Label());
			this->lblUser = (gcnew System::Windows::Forms::Label());
			this->lblTimeN = (gcnew System::Windows::Forms::Label());
			this->lblTeamN = (gcnew System::Windows::Forms::Label());
			this->lblDateN = (gcnew System::Windows::Forms::Label());
			this->lblUserN = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->lblPart = (gcnew System::Windows::Forms::Label());
			this->lblOrder = (gcnew System::Windows::Forms::Label());
			this->lblPartN = (gcnew System::Windows::Forms::Label());
			this->lblOrderN = (gcnew System::Windows::Forms::Label());
			this->lblLastAlarm = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel5->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnStart
			// 
			this->btnStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnStart->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnStart.Image")));
			this->btnStart->Location = System::Drawing::Point(170, 12);
			this->btnStart->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(122, 75);
			this->btnStart->TabIndex = 1;
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MainForm::btnStart_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->btnDashboard);
			this->panel1->Controls->Add(this->btnPause);
			this->panel1->Controls->Add(this->btnMinimize);
			this->panel1->Controls->Add(this->btnLockDoor);
			this->panel1->Controls->Add(this->btnStop);
			this->panel1->Controls->Add(this->btnReset);
			this->panel1->Controls->Add(this->btnExit);
			this->panel1->Controls->Add(this->btnManual);
			this->panel1->Controls->Add(this->btnInit);
			this->panel1->Controls->Add(this->btnUnlockDoor);
			this->panel1->Controls->Add(this->btnStart);
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1920, 100);
			this->panel1->TabIndex = 2;
			// 
			// btnDashboard
			// 
			this->btnDashboard->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDashboard->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnDashboard.Image")));
			this->btnDashboard->Location = System::Drawing::Point(770, 12);
			this->btnDashboard->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnDashboard->Name = L"btnDashboard";
			this->btnDashboard->Size = System::Drawing::Size(122, 75);
			this->btnDashboard->TabIndex = 11;
			this->btnDashboard->UseVisualStyleBackColor = true;
			this->btnDashboard->Click += gcnew System::EventHandler(this, &MainForm::btnDashboard_Click);
			// 
			// btnPause
			// 
			this->btnPause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPause->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnPause.Image")));
			this->btnPause->Location = System::Drawing::Point(320, 12);
			this->btnPause->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnPause->Name = L"btnPause";
			this->btnPause->Size = System::Drawing::Size(122, 75);
			this->btnPause->TabIndex = 10;
			this->btnPause->UseVisualStyleBackColor = true;
			this->btnPause->Click += gcnew System::EventHandler(this, &MainForm::btnPause_Click);
			// 
			// btnMinimize
			// 
			this->btnMinimize->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->btnMinimize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMinimize->Location = System::Drawing::Point(1222, 12);
			this->btnMinimize->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnMinimize->Name = L"btnMinimize";
			this->btnMinimize->Size = System::Drawing::Size(154, 75);
			this->btnMinimize->TabIndex = 9;
			this->btnMinimize->Text = L"Réduire";
			this->btnMinimize->UseVisualStyleBackColor = true;
			this->btnMinimize->Click += gcnew System::EventHandler(this, &MainForm::btnMinimize_Click);
			// 
			// btnLockDoor
			// 
			this->btnLockDoor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLockDoor->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnLockDoor.Image")));
			this->btnLockDoor->Location = System::Drawing::Point(920, 12);
			this->btnLockDoor->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnLockDoor->Name = L"btnLockDoor";
			this->btnLockDoor->Size = System::Drawing::Size(122, 75);
			this->btnLockDoor->TabIndex = 7;
			this->btnLockDoor->UseVisualStyleBackColor = true;
			this->btnLockDoor->Click += gcnew System::EventHandler(this, &MainForm::btnLockDoor_Click);
			// 
			// btnStop
			// 
			this->btnStop->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btnStop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnStop->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnStop.Image")));
			this->btnStop->Location = System::Drawing::Point(20, 12);
			this->btnStop->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnStop->Name = L"btnStop";
			this->btnStop->Size = System::Drawing::Size(122, 75);
			this->btnStop->TabIndex = 6;
			this->btnStop->UseVisualStyleBackColor = true;
			this->btnStop->Click += gcnew System::EventHandler(this, &MainForm::btnStop_Click);
			// 
			// btnReset
			// 
			this->btnReset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnReset->Location = System::Drawing::Point(1402, 12);
			this->btnReset->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnReset->Name = L"btnReset";
			this->btnReset->Size = System::Drawing::Size(250, 75);
			this->btnReset->TabIndex = 5;
			this->btnReset->UseVisualStyleBackColor = true;
			this->btnReset->Click += gcnew System::EventHandler(this, &MainForm::btnReset_Click);
			// 
			// btnExit
			// 
			this->btnExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnExit->Location = System::Drawing::Point(1658, 12);
			this->btnExit->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(250, 75);
			this->btnExit->TabIndex = 3;
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);
			// 
			// btnManual
			// 
			this->btnManual->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnManual->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnManual.Image")));
			this->btnManual->Location = System::Drawing::Point(620, 12);
			this->btnManual->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnManual->Name = L"btnManual";
			this->btnManual->Size = System::Drawing::Size(122, 75);
			this->btnManual->TabIndex = 4;
			this->btnManual->UseVisualStyleBackColor = true;
			this->btnManual->Click += gcnew System::EventHandler(this, &MainForm::btnManual_Click);
			// 
			// btnInit
			// 
			this->btnInit->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btnInit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnInit->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnInit.Image")));
			this->btnInit->Location = System::Drawing::Point(470, 12);
			this->btnInit->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnInit->Name = L"btnInit";
			this->btnInit->Size = System::Drawing::Size(122, 75);
			this->btnInit->TabIndex = 3;
			this->btnInit->UseVisualStyleBackColor = true;
			this->btnInit->Click += gcnew System::EventHandler(this, &MainForm::btnInit_Click);
			// 
			// btnUnlockDoor
			// 
			this->btnUnlockDoor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnUnlockDoor->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnUnlockDoor.Image")));
			this->btnUnlockDoor->Location = System::Drawing::Point(1070, 12);
			this->btnUnlockDoor->Margin = System::Windows::Forms::Padding(3, 8, 3, 3);
			this->btnUnlockDoor->Name = L"btnUnlockDoor";
			this->btnUnlockDoor->Size = System::Drawing::Size(122, 75);
			this->btnUnlockDoor->TabIndex = 2;
			this->btnUnlockDoor->UseVisualStyleBackColor = true;
			this->btnUnlockDoor->Click += gcnew System::EventHandler(this, &MainForm::btnUnlockDoor_Click);
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(0, 0);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(1) { this->rectangleShape1 });
			this->shapeContainer1->Size = System::Drawing::Size(1920, 1080);
			this->shapeContainer1->TabIndex = 3;
			this->shapeContainer1->TabStop = false;
			// 
			// rectangleShape1
			// 
			this->rectangleShape1->CornerRadius = 6;
			this->rectangleShape1->Location = System::Drawing::Point(1, 995);
			this->rectangleShape1->Name = L"rectangleShape1";
			this->rectangleShape1->SelectionColor = System::Drawing::Color::GreenYellow;
			this->rectangleShape1->Size = System::Drawing::Size(1578, 84);
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->btnUsers);
			this->panel2->Controls->Add(this->btnLogout);
			this->panel2->Controls->Add(this->btnlog);
			this->panel2->Controls->Add(this->btnMachine);
			this->panel2->Controls->Add(this->btnProduction);
			this->panel2->Controls->Add(this->btnAlarms);
			this->panel2->Location = System::Drawing::Point(1582, 595);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(338, 485);
			this->panel2->TabIndex = 4;
			// 
			// btnUsers
			// 
			this->btnUsers->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnUsers->Location = System::Drawing::Point(4, 325);
			this->btnUsers->Name = L"btnUsers";
			this->btnUsers->Size = System::Drawing::Size(330, 75);
			this->btnUsers->TabIndex = 5;
			this->btnUsers->UseVisualStyleBackColor = true;
			this->btnUsers->Click += gcnew System::EventHandler(this, &MainForm::btnUser_Click);
			// 
			// btnLogout
			// 
			this->btnLogout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLogout->Location = System::Drawing::Point(4, 405);
			this->btnLogout->Name = L"btnLogout";
			this->btnLogout->Size = System::Drawing::Size(330, 75);
			this->btnLogout->TabIndex = 3;
			this->btnLogout->UseVisualStyleBackColor = true;
			this->btnLogout->Click += gcnew System::EventHandler(this, &MainForm::btnLogout_Click);
			// 
			// btnlog
			// 
			this->btnlog->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnlog->Location = System::Drawing::Point(4, 245);
			this->btnlog->Name = L"btnlog";
			this->btnlog->Size = System::Drawing::Size(330, 75);
			this->btnlog->TabIndex = 4;
			this->btnlog->UseVisualStyleBackColor = true;
			this->btnlog->Click += gcnew System::EventHandler(this, &MainForm::btnlog_Click);
			// 
			// btnMachine
			// 
			this->btnMachine->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMachine->Location = System::Drawing::Point(4, 165);
			this->btnMachine->Name = L"btnMachine";
			this->btnMachine->Size = System::Drawing::Size(330, 75);
			this->btnMachine->TabIndex = 3;
			this->btnMachine->UseVisualStyleBackColor = true;
			this->btnMachine->Click += gcnew System::EventHandler(this, &MainForm::btnMachine_Click);
			// 
			// btnProduction
			// 
			this->btnProduction->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnProduction->Location = System::Drawing::Point(4, 85);
			this->btnProduction->Name = L"btnProduction";
			this->btnProduction->Size = System::Drawing::Size(330, 75);
			this->btnProduction->TabIndex = 2;
			this->btnProduction->UseVisualStyleBackColor = true;
			this->btnProduction->Click += gcnew System::EventHandler(this, &MainForm::btnProduction_Click);
			// 
			// btnAlarms
			// 
			this->btnAlarms->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAlarms->Location = System::Drawing::Point(4, 5);
			this->btnAlarms->Name = L"btnAlarms";
			this->btnAlarms->Size = System::Drawing::Size(330, 75);
			this->btnAlarms->TabIndex = 1;
			this->btnAlarms->UseVisualStyleBackColor = true;
			this->btnAlarms->Click += gcnew System::EventHandler(this, &MainForm::btnAlarms_Click);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::SystemColors::Control;
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->lblStatus);
			this->panel3->Controls->Add(this->lblMachine);
			this->panel3->Controls->Add(this->lblStatusN);
			this->panel3->Controls->Add(this->lblMachineN);
			this->panel3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel3->Location = System::Drawing::Point(1579, 110);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(338, 110);
			this->panel3->TabIndex = 6;
			// 
			// lblStatus
			// 
			this->lblStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStatus->Location = System::Drawing::Point(162, 50);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(171, 49);
			this->lblStatus->TabIndex = 3;
			this->lblStatus->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblMachine
			// 
			this->lblMachine->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMachine->Location = System::Drawing::Point(162, 1);
			this->lblMachine->Name = L"lblMachine";
			this->lblMachine->Size = System::Drawing::Size(171, 49);
			this->lblMachine->TabIndex = 2;
			this->lblMachine->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblStatusN
			// 
			this->lblStatusN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStatusN->Location = System::Drawing::Point(10, 50);
			this->lblStatusN->Name = L"lblStatusN";
			this->lblStatusN->Size = System::Drawing::Size(146, 49);
			this->lblStatusN->TabIndex = 1;
			this->lblStatusN->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblMachineN
			// 
			this->lblMachineN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMachineN->Location = System::Drawing::Point(10, 1);
			this->lblMachineN->Name = L"lblMachineN";
			this->lblMachineN->Size = System::Drawing::Size(146, 49);
			this->lblMachineN->TabIndex = 0;
			this->lblMachineN->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// panel4
			// 
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel4->Controls->Add(this->lblTime);
			this->panel4->Controls->Add(this->lblTeam);
			this->panel4->Controls->Add(this->lblDate);
			this->panel4->Controls->Add(this->lblUser);
			this->panel4->Controls->Add(this->lblTimeN);
			this->panel4->Controls->Add(this->lblTeamN);
			this->panel4->Controls->Add(this->lblDateN);
			this->panel4->Controls->Add(this->lblUserN);
			this->panel4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel4->Location = System::Drawing::Point(1579, 235);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(338, 220);
			this->panel4->TabIndex = 7;
			// 
			// lblTime
			// 
			this->lblTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTime->Location = System::Drawing::Point(162, 150);
			this->lblTime->Name = L"lblTime";
			this->lblTime->Size = System::Drawing::Size(171, 49);
			this->lblTime->TabIndex = 11;
			this->lblTime->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblTeam
			// 
			this->lblTeam->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTeam->Location = System::Drawing::Point(162, 50);
			this->lblTeam->Name = L"lblTeam";
			this->lblTeam->Size = System::Drawing::Size(171, 49);
			this->lblTeam->TabIndex = 3;
			this->lblTeam->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->lblTeam->Visible = false;
			// 
			// lblDate
			// 
			this->lblDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDate->Location = System::Drawing::Point(162, 101);
			this->lblDate->Name = L"lblDate";
			this->lblDate->Size = System::Drawing::Size(171, 49);
			this->lblDate->TabIndex = 10;
			this->lblDate->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblUser
			// 
			this->lblUser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblUser->Location = System::Drawing::Point(162, 1);
			this->lblUser->Name = L"lblUser";
			this->lblUser->Size = System::Drawing::Size(171, 49);
			this->lblUser->TabIndex = 2;
			this->lblUser->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblTimeN
			// 
			this->lblTimeN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTimeN->Location = System::Drawing::Point(10, 150);
			this->lblTimeN->Name = L"lblTimeN";
			this->lblTimeN->Size = System::Drawing::Size(146, 49);
			this->lblTimeN->TabIndex = 9;
			this->lblTimeN->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblTeamN
			// 
			this->lblTeamN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTeamN->Location = System::Drawing::Point(10, 50);
			this->lblTeamN->Name = L"lblTeamN";
			this->lblTeamN->Size = System::Drawing::Size(146, 49);
			this->lblTeamN->TabIndex = 1;
			this->lblTeamN->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->lblTeamN->Visible = false;
			// 
			// lblDateN
			// 
			this->lblDateN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDateN->Location = System::Drawing::Point(10, 101);
			this->lblDateN->Name = L"lblDateN";
			this->lblDateN->Size = System::Drawing::Size(146, 49);
			this->lblDateN->TabIndex = 8;
			this->lblDateN->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblUserN
			// 
			this->lblUserN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblUserN->Location = System::Drawing::Point(10, 1);
			this->lblUserN->Name = L"lblUserN";
			this->lblUserN->Size = System::Drawing::Size(146, 49);
			this->lblUserN->TabIndex = 0;
			this->lblUserN->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// panel5
			// 
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel5->Controls->Add(this->lblPart);
			this->panel5->Controls->Add(this->lblOrder);
			this->panel5->Controls->Add(this->lblPartN);
			this->panel5->Controls->Add(this->lblOrderN);
			this->panel5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->panel5->Location = System::Drawing::Point(1582, 470);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(338, 110);
			this->panel5->TabIndex = 8;
			this->panel5->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::panel5_Paint);
			// 
			// lblPart
			// 
			this->lblPart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPart->Location = System::Drawing::Point(162, 50);
			this->lblPart->Name = L"lblPart";
			this->lblPart->Size = System::Drawing::Size(171, 49);
			this->lblPart->TabIndex = 3;
			this->lblPart->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblOrder
			// 
			this->lblOrder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOrder->Location = System::Drawing::Point(162, 1);
			this->lblOrder->Name = L"lblOrder";
			this->lblOrder->Size = System::Drawing::Size(171, 49);
			this->lblOrder->TabIndex = 2;
			this->lblOrder->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblPartN
			// 
			this->lblPartN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPartN->Location = System::Drawing::Point(10, 50);
			this->lblPartN->Name = L"lblPartN";
			this->lblPartN->Size = System::Drawing::Size(143, 49);
			this->lblPartN->TabIndex = 1;
			this->lblPartN->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblOrderN
			// 
			this->lblOrderN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOrderN->Location = System::Drawing::Point(10, 1);
			this->lblOrderN->Name = L"lblOrderN";
			this->lblOrderN->Size = System::Drawing::Size(143, 49);
			this->lblOrderN->TabIndex = 0;
			this->lblOrderN->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblLastAlarm
			// 
			this->lblLastAlarm->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLastAlarm->ForeColor = System::Drawing::Color::Red;
			this->lblLastAlarm->Location = System::Drawing::Point(20, 1002);
			this->lblLastAlarm->Name = L"lblLastAlarm";
			this->lblLastAlarm->Size = System::Drawing::Size(1538, 68);
			this->lblLastAlarm->TabIndex = 9;
			this->lblLastAlarm->Text = L"...";
			this->lblLastAlarm->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1920, 1080);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->lblLastAlarm);
			this->Controls->Add(this->panel5);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->shapeContainer1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->VisibleChanged += gcnew System::EventHandler(this, &MainForm::MainForm_VisibleChanged);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnExit_Click(System::Object^  sender, System::EventArgs^  e) {
				 MyMsgBox^ pT_l_ValidateExit = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::SureToExitApplication)+ " ?",TUtilities::pS_LoadString(TextIndex::ValidateReq),MessageBoxButtons::YesNo);
			pT_l_ValidateExit->ShowDialog();
			if (1 == pT_l_ValidateExit->iPressedButton)
			{
				TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::ExitApp));
				Application::Exit();
			}
		}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			if (!TTwincatInterface::GetTCVarAccess()->IsConnected())
				 Application::Exit();
			else
			{
				TTwincatInterface::GetTCVarAccess()->bReadAllData();
				UpdateUI();
			}
		}
private: System::Void btnStart_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::StartMachine));
			SetTCData(s_ModeReq.MMM_Run);
		}
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
			// Prevent screen loading
 			e_NewScreen = e_NoScreen;
			e_CurrentScreen = e_NoScreen;
			// Create the embedded screens
	 		pT_ProdScreen = gcnew ProdScreen();
			this->AddOwnedForm(pT_ProdScreen);
	 		pT_AlarmScreen = gcnew AlarmScreen();
			this->AddOwnedForm(pT_AlarmScreen);
	 		pT_LogScreen = gcnew LogScreen();
			this->AddOwnedForm(pT_LogScreen);
	 		pT_MachineScreen = gcnew MachineScreen(this);
			this->AddOwnedForm(pT_MachineScreen);
			pT_DashboardScreen = gcnew DashboardScreen();
			this->AddOwnedForm(pT_DashboardScreen);
			pT_CounterScreen = gcnew CounterScreen();
			this->AddOwnedForm(pT_CounterScreen);

			// And update UI for login data
			UpdateLoginData();
			TUser::SetLevel(TUser::GetLevel());//Force refresh of user level access
			b_ScreensLoaded = true;

		}
private: System::Void btnLogout_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddLog(TUser::pS_GetName()  + " " + TUtilities::pS_LoadString(TextIndex::HasUnlogged));
			TUser::Clear();
			HideAllScreen();
			// Display the login box
			login^ pT_l_LoginForm = gcnew login();
			pT_l_LoginForm->ShowDialog();
			// And update UI for login data
			UpdateLoginData();
			MainForm_VisibleChanged(nullptr,nullptr);
		}
private: System::Void btnStop_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::StopMachine));
			SetTCData(s_ModeReq.MMM_Stop);
		}
private: System::Void btnInit_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::InitMachine));
			SetTCData(s_ModeReq.MMM_Init);
		}
private: System::Void btnManual_Click(System::Object^  sender, System::EventArgs^  e) {
			if (eMachineMode == MM_Manual)
			{
				e_NewScreen = e_BaseMachineScreen;
			}
			else
			{
				TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::MachineInManual));
				SetTCData(s_ModeReq.MMM_Manual);
			}
		}
private: System::Void btnReset_Click(System::Object^  sender, System::EventArgs^  e) {
			SetTCData(b_ResetErrors);
			pT_AlarmScreen->ResetAlarmList();
		}
private: System::Void btnUser_Click(System::Object^  sender, System::EventArgs^  e) {
			 UserManager^ pT_l_UserManagerForm = gcnew UserManager();
			 pT_l_UserManagerForm->ShowDialog();
		 }
private: System::Void btnProduction_Click(System::Object^  sender, System::EventArgs^  e) {
			e_NewScreen = e_ProdScreen;
		 }
private: System::Void btnAlarms_Click(System::Object^  sender, System::EventArgs^  e) {
			e_NewScreen = e_AlarmScreen;
		 }
private: System::Void btnMachine_Click(System::Object^  sender, System::EventArgs^  e) {
			e_NewScreen = e_BaseMachineScreen;
		 }
private: System::Void btnlog_Click(System::Object^  sender, System::EventArgs^  e) {
			e_NewScreen = e_LogScreen;
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			System::Diagnostics::Process ^proc = gcnew System::Diagnostics::Process();
			proc->StartInfo->FileName = "osk.exe";
			proc->Start() ;
			proc->Close();
		 }
private: System::Void MainForm_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void btnLockDoor_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::DoorsLocked));
			SetTCData(s_MachineSafety.MM_LockDoor);
		 }
private: System::Void btnUnlockDoor_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::DoorsUnlocked));
			SetTCData(s_MachineSafety.MM_UnlockDoor);
		 }
private: System::Void MainForm_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			//btnStart->Text = TUtilities::pS_LoadString(TextIndex::Start);
			//btnStop->Text = TUtilities::pS_LoadString(TextIndex::Stop);
			//btnPause->Text = TUtilities::pS_LoadString(TextIndex::Pause);
			//btnInit->Text = TUtilities::pS_LoadString(TextIndex::Init);
			//btnManual->Text = TUtilities::pS_LoadString(TextIndex::Manual);
			btnReset->Text = TUtilities::pS_LoadString(TextIndex::Reset);
			btnExit->Text = TUtilities::pS_LoadString(TextIndex::Exit);
			//btnLockDoor->Text = TUtilities::pS_LoadString(TextIndex::Lock);
			//btnUnlockDoor->Text = TUtilities::pS_LoadString(TextIndex::Unlock);

			btnUsers->Text = TUtilities::pS_LoadString(TextIndex::Users);
			btnLogout->Text = TUtilities::pS_LoadString(TextIndex::Logout);
			btnlog->Text = TUtilities::pS_LoadString(TextIndex::LogBook);
			btnMachine->Text = TUtilities::pS_LoadString(TextIndex::Machine);
			btnProduction->Text = TUtilities::pS_LoadString(TextIndex::Production);
			btnAlarms->Text = TUtilities::pS_LoadString(TextIndex::Alarms);
			lblMachine->Text = ":  " + TUtilities::pS_LoadString(TextIndex::MachineName);
			lblStatusN->Text = TUtilities::pS_LoadString(TextIndex::Status);
			lblMachineN->Text = TUtilities::pS_LoadString(TextIndex::Machine);
			lblTimeN->Text = TUtilities::pS_LoadString(TextIndex::Time);
			lblTeamN->Text = TUtilities::pS_LoadString(TextIndex::Team);
			lblDateN->Text = TUtilities::pS_LoadString(TextIndex::Date);
			lblUserN->Text = TUtilities::pS_LoadString(TextIndex::User);
			lblPartN->Text = TUtilities::pS_LoadString(TextIndex::Part);
			lblOrderN->Text = TUtilities::pS_LoadString(TextIndex::Order);
			btnMinimize->Text = TUtilities::pS_LoadString(TextIndex::Minimize);

		 }
private: System::Void btnMinimize_Click(System::Object^  sender, System::EventArgs^  e) {
			 pT_MachineScreen->MinimizeAll();
			 WindowState = FormWindowState::Minimized;
		 }
private: System::Void btnPause_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::Pause));
			SetTCData(s_ModeReq.MMM_Pause);
		 }

	private: System::Void OnDoWork(System::Object ^sender, System::ComponentModel::DoWorkEventArgs ^e)
	{
		BackgroundWorker^ worker = (BackgroundWorker^)sender;

			while (true)
			{
				if (worker->CancellationPending == true)
				{
					e->Cancel = true;
					break;
				}
				else
				{
					System::Threading::Thread::Sleep(2000);
					if (TUser::b_HasSystemLevel()) worker->ReportProgress(true);
				}
			}
		}

		private: System::Void OnProgressChanged(System::Object ^sender, System::ComponentModel::ProgressChangedEventArgs ^e)
		 {
			bool bIsMondemaLoginAllowed = e->ProgressPercentage ? true : false;
			if ((TUser::b_HasSystemLevel()) && (!bIsMondemaLoginAllowed))
			{
				btnLogout_Click(btnLogout, EventArgs::Empty);
			}
		 }

private: System::Void btnDashboard_Click(System::Object^  sender, System::EventArgs^  e) {
	if (eMachineMode == MM_Dashboard)
	{
		e_NewScreen = e_DashboardScreen;
	}
	else
	{
		TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::MachineInDashboard));
		SetTCData(s_ModeReq.MMM_Dashboard);
	}
}
private: System::Void panel5_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
};

}





