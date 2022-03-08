#include <string.h>
#pragma once

#include <stdio.h>
#include <time.h>
#include "global.h"
#include "LoaderManualScreen.h"
#include "TableManualScreen.h"
#include "PearlingManualScreen.h"
#include "TurnOverManualScreen.h"
#include "BarrelManualScreen.h"
#include "SharpenManualScreen.h"
#include "LiftManualScreen.h"
#include "RejectManualScreen.h"
#include "VisionManualScreen.h"
#include "UtilitiesManualScreen.h"
#include "VacuumSettingsScreen.h"

#define ShowManualScreen(pT_ScreenToShow) \
	pT_LoaderManualForm->Hide();\
	pT_TableManualForm->Hide();\
	pT_PearlingManualForm->Hide();\
	pT_TurnOverManualForm->Hide();\
	pT_BarrelManualForm->Hide();\
	pT_SharpenManualForm->Hide();\
	pT_Lift1ManualForm->Hide();\
	pT_Lift2ManualForm->Hide();\
	pT_RejectManualForm->Hide();\
	pT_VisionManualForm->Hide();\
	pT_UtilitiesManualForm->Hide();\
	pT_VacuumSettingsForm->Hide();\
	pT_ScreenToShow->Show();

#define HideManualScreens() \
	pT_LoaderManualForm->Hide();\
	pT_TableManualForm->Hide();\
	pT_PearlingManualForm->Hide();\
	pT_TurnOverManualForm->Hide();\
	pT_BarrelManualForm->Hide();\
	pT_Lift1ManualForm->Hide();\
	pT_Lift2ManualForm->Hide();\
	pT_RejectManualForm->Hide();\
	pT_VisionManualForm->Hide();\
	pT_UtilitiesManualForm->Hide();\
	pT_VacuumSettingsForm->Hide();\
	pT_SharpenManualForm->Hide();

#define UpdateEnabled(Component,Enabled) {\
	if (Enabled) \
		Component->Visible = false;\
	else\
		Component->Visible = true;\
	}

namespace Projet1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MondemaComponents;

	/// <summary>
	/// Description résumée de MachineScreen
	/// </summary>
	public ref class MachineScreen : public System::Windows::Forms::Form
	{
	public:

		MachineScreen() : MachineScreen(nullptr)
		{
		}

		MachineScreen(Object^ pT_x_frmMain)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_frmMain = pT_x_frmMain;
			SetupModuleStatus(msLoader, offsetof(MACHINE_DATA, s_ModLoader));
			SetupModuleStatus(msTable, offsetof(MACHINE_DATA, s_ModTable));
			SetupModuleStatus(msPearling, offsetof(MACHINE_DATA, s_ModPearling));
			SetupModuleStatus(msTurnOver, offsetof(MACHINE_DATA, s_ModTurnOver));
			SetupModuleStatus(msBarrel, offsetof(MACHINE_DATA, s_ModBarrel));
			SetupModuleStatus(msSharpen, offsetof(MACHINE_DATA, s_ModSharpen));
			SetupModuleStatus(msLift1, offsetof(MACHINE_DATA, s_ModLift1));
			SetupModuleStatus(msLift2, offsetof(MACHINE_DATA, s_ModLift2));
			SetupModuleStatus(msReject, offsetof(MACHINE_DATA, s_ModReject));
			SetupModuleStatus(msVision, offsetof(MACHINE_DATA, s_ModVision));
			SetupModuleStatus(msUtilities, offsetof(MACHINE_DATA, s_ModUtilities));

			pT_LoaderManualForm = gcnew LoaderManualScreen();
			this->AddOwnedForm(pT_LoaderManualForm);
			pT_TableManualForm = gcnew TableManualScreen();
			this->AddOwnedForm(pT_TableManualForm);
			pT_PearlingManualForm = gcnew PearlingManualScreen();
			this->AddOwnedForm(pT_PearlingManualForm);
			pT_TurnOverManualForm = gcnew TurnOverManualScreen();
			this->AddOwnedForm(pT_TurnOverManualForm);
			pT_SharpenManualForm = gcnew SharpenManualScreen();
			this->AddOwnedForm(pT_SharpenManualForm);
			pT_BarrelManualForm = gcnew BarrelManualScreen();
			this->AddOwnedForm(pT_BarrelManualForm);
			pT_Lift1ManualForm = gcnew LiftManualScreen(true);
			this->AddOwnedForm(pT_Lift1ManualForm);
			pT_Lift2ManualForm = gcnew LiftManualScreen(false);
			this->AddOwnedForm(pT_Lift2ManualForm);
			pT_RejectManualForm = gcnew RejectManualScreen();
			this->AddOwnedForm(pT_RejectManualForm);
			pT_VisionManualForm = gcnew VisionManualScreen();
			this->AddOwnedForm(pT_VisionManualForm);
			pT_UtilitiesManualForm = gcnew UtilitiesManualScreen();
			this->AddOwnedForm(pT_UtilitiesManualForm);
			pT_VacuumSettingsForm = gcnew VacuumSettingsScreen();
			this->AddOwnedForm(pT_VacuumSettingsForm);
		
			b_ScreensCreated = true;

		}
	// Our specific functions
		void SetupModuleStatus(ModuleStatus^ ms, unsigned int Offset)
		{
			ms->Offset = Offset;
			ms->Debug->Click += gcnew System::EventHandler(this, &MachineScreen::OnDebugClick);
			ms->Step->Click += gcnew System::EventHandler(this, &MachineScreen::OnStepClick);
		}


	private:
		System::Void pnlCounter_Click(System::Object^  sender, System::EventArgs^  e);
		void UpdateStatus(ModuleStatus^ ms, Label^ lblStep, Label^ lblStatus);
		String^ GetStepStr(TC_INT eStep);
		bool b_ScreensCreated;
		LoaderManualScreen^ pT_LoaderManualForm;
		TableManualScreen^ pT_TableManualForm;
		PearlingManualScreen^ pT_PearlingManualForm;
		TurnOverManualScreen^ pT_TurnOverManualForm;
		BarrelManualScreen^ pT_BarrelManualForm;
		LiftManualScreen^ pT_Lift1ManualForm;
		VacuumSettingsScreen^ pT_VacuumSettingsForm;
		LiftManualScreen^ pT_Lift2ManualForm;
		RejectManualScreen^ pT_RejectManualForm;
		VisionManualScreen^ pT_VisionManualForm;
		UtilitiesManualScreen^ pT_UtilitiesManualForm;
		Object^ pT_frmMain;

	private: System::Windows::Forms::Panel^  pnlReject;

	private: System::Windows::Forms::Panel^  pnlLift1;

	private: System::Windows::Forms::Panel^  pnlLift2;

	private: System::Windows::Forms::Label^  lblStepLift1;
	private: System::Windows::Forms::Label^  lblLift1;
	private: System::Windows::Forms::Label^  lblStepReject;
	private: System::Windows::Forms::Label^  lblReject;
	private: System::Windows::Forms::Label^  lblStepLift2;
	private: System::Windows::Forms::Label^  lblLift2;
	private: System::Windows::Forms::Label^  lblStepVision;
	private: System::Windows::Forms::Label^  lblVision;
	private: System::Windows::Forms::Panel^  pnlVision;

	private: System::Windows::Forms::Label^  lblStepUtilities;
	private: System::Windows::Forms::Label^  lblUtilities;

	private: System::Windows::Forms::Panel^  pnlUtilities;
	private: System::Windows::Forms::PictureBox^  pbDoorsLoader2;

	private: System::Windows::Forms::PictureBox^  pbDoorsLoader1;


	private: System::Windows::Forms::PictureBox^  pbDoorsPearling2;

	private: System::Windows::Forms::PictureBox^  pbDoorsPearling1;

	private: System::Windows::Forms::PictureBox^  pbEmergency3;
	private: System::Windows::Forms::PictureBox^  pbEmergency2;
	private: System::Windows::Forms::PictureBox^  pbEmergency1;
	private: System::Windows::Forms::Label^  lblLift1Status;
	private: System::Windows::Forms::Label^  lblVisionStatus;
	private: System::Windows::Forms::Label^  lblLoaderStatus;
	private: System::Windows::Forms::Label^  lblTurnOverStatus;
	private: System::Windows::Forms::Label^  lblTableStatus;
	private: System::Windows::Forms::Label^  lblBarrelStatus;
	private: System::Windows::Forms::Label^  lblLift2Status;
	private: System::Windows::Forms::Label^  lblRejectStatus;
	private: System::Windows::Forms::Label^  lblSharpenStatus;
	private: System::Windows::Forms::Label^  lblPearlingStatus;
			 SharpenManualScreen^ pT_SharpenManualForm;
			 
	private: System::Windows::Forms::Label^  lblMMIVersion;
	private: System::Windows::Forms::Panel^  pnlPicture;

	private: System::Windows::Forms::Panel^  pnlLoader;
	private: System::Windows::Forms::Panel^  pnlSharpen;
	private: System::Windows::Forms::Panel^  pnlBarrel;
	private: System::Windows::Forms::Panel^  pnlPearling;
	private: System::Windows::Forms::Panel^  pnlTable;
	private: System::Windows::Forms::Panel^  pnlTurnOver;
	private: MondemaComponents::ModuleStatus^  msLoader;
	private: MondemaComponents::ModuleStatus^  msBarrel;
	private: MondemaComponents::ModuleStatus^  msPearling;
	private: MondemaComponents::ModuleStatus^  msTurnOver;
	private: MondemaComponents::ModuleStatus^  msTable;
	private: MondemaComponents::ModuleStatus^  msSharpen;
	private: MondemaComponents::ModuleStatus^  msVision;
	private: MondemaComponents::ModuleStatus^  msUtilities;
	private: MondemaComponents::ModuleStatus^  msReject;
	private: MondemaComponents::ModuleStatus^  msLift1;
	private: MondemaComponents::ModuleStatus^  msLift2;

	private: System::Windows::Forms::Label^  lblUtilitiesStatus;
	private: System::Windows::Forms::Label^  lblManagerRunStep;
private: System::Windows::Forms::CheckBox^  btnSavePersistent;
private: System::Windows::Forms::Panel^  pnlVacuum;
private: System::Windows::Forms::Panel^  pnlCounter;
private: System::Windows::Forms::Panel^  pnlImageTurnOver;



	private: System::Windows::Forms::Label^  lblAutomationVersion;

	public:
		void UpdateUI(void);
		void Reload(void);
		void MinimizeAll(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MachineScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lblLoader;
	private: System::Windows::Forms::Label^  lblPearling;
	private: System::Windows::Forms::Label^  lblSharpening;
	private: System::Windows::Forms::Label^  lblTurnover;
	private: System::Windows::Forms::Label^  lblStepPearling;
	private: System::Windows::Forms::Label^  lblStepSharpening;
	private: System::Windows::Forms::Label^  lblStepLoader;
	private: System::Windows::Forms::Label^  lblTable;
	private: System::Windows::Forms::Label^  lblStepTable;
	private: System::Windows::Forms::Label^  lblBarrel;
	private: System::Windows::Forms::Label^  lblStepBarrel;
	private: System::Windows::Forms::Label^  lblStepTurnover;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MachineScreen::typeid));
			this->lblStepPearling = (gcnew System::Windows::Forms::Label());
			this->lblPearling = (gcnew System::Windows::Forms::Label());
			this->lblStepSharpening = (gcnew System::Windows::Forms::Label());
			this->lblSharpening = (gcnew System::Windows::Forms::Label());
			this->lblTurnover = (gcnew System::Windows::Forms::Label());
			this->lblStepLoader = (gcnew System::Windows::Forms::Label());
			this->lblLoader = (gcnew System::Windows::Forms::Label());
			this->lblTable = (gcnew System::Windows::Forms::Label());
			this->lblStepTable = (gcnew System::Windows::Forms::Label());
			this->lblBarrel = (gcnew System::Windows::Forms::Label());
			this->lblStepBarrel = (gcnew System::Windows::Forms::Label());
			this->lblStepTurnover = (gcnew System::Windows::Forms::Label());
			this->lblMMIVersion = (gcnew System::Windows::Forms::Label());
			this->lblAutomationVersion = (gcnew System::Windows::Forms::Label());
			this->pnlPicture = (gcnew System::Windows::Forms::Panel());
			this->lblUtilitiesStatus = (gcnew System::Windows::Forms::Label());
			this->lblStepUtilities = (gcnew System::Windows::Forms::Label());
			this->lblLoaderStatus = (gcnew System::Windows::Forms::Label());
			this->lblVision = (gcnew System::Windows::Forms::Label());
			this->lblLift2 = (gcnew System::Windows::Forms::Label());
			this->lblPearlingStatus = (gcnew System::Windows::Forms::Label());
			this->lblVisionStatus = (gcnew System::Windows::Forms::Label());
			this->msSharpen = (gcnew MondemaComponents::ModuleStatus());
			this->lblStepVision = (gcnew System::Windows::Forms::Label());
			this->pnlImageTurnOver = (gcnew System::Windows::Forms::Panel());
			this->pnlCounter = (gcnew System::Windows::Forms::Panel());
			this->pnlVacuum = (gcnew System::Windows::Forms::Panel());
			this->btnSavePersistent = (gcnew System::Windows::Forms::CheckBox());
			this->pbEmergency1 = (gcnew System::Windows::Forms::PictureBox());
			this->msBarrel = (gcnew MondemaComponents::ModuleStatus());
			this->msTurnOver = (gcnew MondemaComponents::ModuleStatus());
			this->msReject = (gcnew MondemaComponents::ModuleStatus());
			this->msLift1 = (gcnew MondemaComponents::ModuleStatus());
			this->msLift2 = (gcnew MondemaComponents::ModuleStatus());
			this->msTable = (gcnew MondemaComponents::ModuleStatus());
			this->lblManagerRunStep = (gcnew System::Windows::Forms::Label());
			this->lblLift1Status = (gcnew System::Windows::Forms::Label());
			this->lblTurnOverStatus = (gcnew System::Windows::Forms::Label());
			this->lblTableStatus = (gcnew System::Windows::Forms::Label());
			this->lblBarrelStatus = (gcnew System::Windows::Forms::Label());
			this->lblLift2Status = (gcnew System::Windows::Forms::Label());
			this->lblRejectStatus = (gcnew System::Windows::Forms::Label());
			this->lblSharpenStatus = (gcnew System::Windows::Forms::Label());
			this->pbDoorsPearling2 = (gcnew System::Windows::Forms::PictureBox());
			this->pnlLoader = (gcnew System::Windows::Forms::Panel());
			this->msLoader = (gcnew MondemaComponents::ModuleStatus());
			this->pnlPearling = (gcnew System::Windows::Forms::Panel());
			this->msPearling = (gcnew MondemaComponents::ModuleStatus());
			this->pbDoorsLoader2 = (gcnew System::Windows::Forms::PictureBox());
			this->pbDoorsLoader1 = (gcnew System::Windows::Forms::PictureBox());
			this->pbDoorsPearling1 = (gcnew System::Windows::Forms::PictureBox());
			this->pbEmergency3 = (gcnew System::Windows::Forms::PictureBox());
			this->pbEmergency2 = (gcnew System::Windows::Forms::PictureBox());
			this->lblUtilities = (gcnew System::Windows::Forms::Label());
			this->pnlVision = (gcnew System::Windows::Forms::Panel());
			this->msVision = (gcnew MondemaComponents::ModuleStatus());
			this->lblStepLift1 = (gcnew System::Windows::Forms::Label());
			this->lblLift1 = (gcnew System::Windows::Forms::Label());
			this->lblStepReject = (gcnew System::Windows::Forms::Label());
			this->lblReject = (gcnew System::Windows::Forms::Label());
			this->lblStepLift2 = (gcnew System::Windows::Forms::Label());
			this->pnlReject = (gcnew System::Windows::Forms::Panel());
			this->pnlLift1 = (gcnew System::Windows::Forms::Panel());
			this->pnlLift2 = (gcnew System::Windows::Forms::Panel());
			this->pnlTurnOver = (gcnew System::Windows::Forms::Panel());
			this->pnlBarrel = (gcnew System::Windows::Forms::Panel());
			this->pnlTable = (gcnew System::Windows::Forms::Panel());
			this->pnlSharpen = (gcnew System::Windows::Forms::Panel());
			this->pnlUtilities = (gcnew System::Windows::Forms::Panel());
			this->msUtilities = (gcnew MondemaComponents::ModuleStatus());
			this->pnlPicture->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbEmergency1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDoorsPearling2))->BeginInit();
			this->pnlLoader->SuspendLayout();
			this->pnlPearling->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDoorsLoader2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDoorsLoader1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDoorsPearling1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbEmergency3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbEmergency2))->BeginInit();
			this->pnlVision->SuspendLayout();
			this->pnlUtilities->SuspendLayout();
			this->SuspendLayout();
			// 
			// lblStepPearling
			// 
			this->lblStepPearling->AutoSize = true;
			this->lblStepPearling->BackColor = System::Drawing::SystemColors::Control;
			this->lblStepPearling->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepPearling->ForeColor = System::Drawing::SystemColors::ControlText;
			this->lblStepPearling->Location = System::Drawing::Point(501, 95);
			this->lblStepPearling->Name = L"lblStepPearling";
			this->lblStepPearling->Size = System::Drawing::Size(100, 20);
			this->lblStepPearling->TabIndex = 5;
			this->lblStepPearling->Text = L"PearlingStep";
			this->lblStepPearling->Click += gcnew System::EventHandler(this, &MachineScreen::Pearling_Click);
			// 
			// lblPearling
			// 
			this->lblPearling->AutoSize = true;
			this->lblPearling->BackColor = System::Drawing::SystemColors::Control;
			this->lblPearling->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPearling->ForeColor = System::Drawing::SystemColors::ControlText;
			this->lblPearling->Location = System::Drawing::Point(501, 55);
			this->lblPearling->Name = L"lblPearling";
			this->lblPearling->Size = System::Drawing::Size(134, 37);
			this->lblPearling->TabIndex = 4;
			this->lblPearling->Text = L"Pearling";
			this->lblPearling->Click += gcnew System::EventHandler(this, &MachineScreen::Pearling_Click);
			// 
			// lblStepSharpening
			// 
			this->lblStepSharpening->AutoSize = true;
			this->lblStepSharpening->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepSharpening->Location = System::Drawing::Point(468, 331);
			this->lblStepSharpening->Name = L"lblStepSharpening";
			this->lblStepSharpening->Size = System::Drawing::Size(104, 20);
			this->lblStepSharpening->TabIndex = 6;
			this->lblStepSharpening->Text = L"SharpenStep";
			this->lblStepSharpening->Click += gcnew System::EventHandler(this, &MachineScreen::Sharpen_Click);
			// 
			// lblSharpening
			// 
			this->lblSharpening->AutoSize = true;
			this->lblSharpening->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSharpening->Location = System::Drawing::Point(468, 291);
			this->lblSharpening->Name = L"lblSharpening";
			this->lblSharpening->Size = System::Drawing::Size(138, 37);
			this->lblSharpening->TabIndex = 2;
			this->lblSharpening->Text = L"Sharpen";
			this->lblSharpening->Click += gcnew System::EventHandler(this, &MachineScreen::Sharpen_Click);
			// 
			// lblTurnover
			// 
			this->lblTurnover->AutoSize = true;
			this->lblTurnover->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTurnover->Location = System::Drawing::Point(864, 446);
			this->lblTurnover->Name = L"lblTurnover";
			this->lblTurnover->Size = System::Drawing::Size(152, 37);
			this->lblTurnover->TabIndex = 2;
			this->lblTurnover->Text = L"TurnOver";
			this->lblTurnover->Click += gcnew System::EventHandler(this, &MachineScreen::TurnOver_Click);
			// 
			// lblStepLoader
			// 
			this->lblStepLoader->AutoSize = true;
			this->lblStepLoader->BackColor = System::Drawing::SystemColors::Control;
			this->lblStepLoader->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepLoader->Location = System::Drawing::Point(1226, 118);
			this->lblStepLoader->Name = L"lblStepLoader";
			this->lblStepLoader->Size = System::Drawing::Size(93, 20);
			this->lblStepLoader->TabIndex = 6;
			this->lblStepLoader->Text = L"LoaderStep";
			this->lblStepLoader->Click += gcnew System::EventHandler(this, &MachineScreen::Loader_Click);
			// 
			// lblLoader
			// 
			this->lblLoader->AutoSize = true;
			this->lblLoader->BackColor = System::Drawing::SystemColors::Control;
			this->lblLoader->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLoader->Location = System::Drawing::Point(1224, 55);
			this->lblLoader->Name = L"lblLoader";
			this->lblLoader->Size = System::Drawing::Size(117, 37);
			this->lblLoader->TabIndex = 1;
			this->lblLoader->Text = L"Loader";
			this->lblLoader->Click += gcnew System::EventHandler(this, &MachineScreen::Loader_Click);
			// 
			// lblTable
			// 
			this->lblTable->AutoSize = true;
			this->lblTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTable->Location = System::Drawing::Point(431, 406);
			this->lblTable->Name = L"lblTable";
			this->lblTable->Size = System::Drawing::Size(97, 37);
			this->lblTable->TabIndex = 5;
			this->lblTable->Text = L"Table";
			this->lblTable->Click += gcnew System::EventHandler(this, &MachineScreen::Table_Click);
			// 
			// lblStepTable
			// 
			this->lblStepTable->AutoSize = true;
			this->lblStepTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepTable->Location = System::Drawing::Point(433, 446);
			this->lblStepTable->Name = L"lblStepTable";
			this->lblStepTable->Size = System::Drawing::Size(82, 20);
			this->lblStepTable->TabIndex = 6;
			this->lblStepTable->Text = L"TableStep";
			this->lblStepTable->Click += gcnew System::EventHandler(this, &MachineScreen::Table_Click);
			// 
			// lblBarrel
			// 
			this->lblBarrel->AutoSize = true;
			this->lblBarrel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBarrel->Location = System::Drawing::Point(871, 322);
			this->lblBarrel->Name = L"lblBarrel";
			this->lblBarrel->Size = System::Drawing::Size(99, 44);
			this->lblBarrel->TabIndex = 6;
			this->lblBarrel->Text = L"Barrel";
			this->lblBarrel->UseCompatibleTextRendering = true;
			this->lblBarrel->Click += gcnew System::EventHandler(this, &MachineScreen::Barrel_Click);
			// 
			// lblStepBarrel
			// 
			this->lblStepBarrel->AutoSize = true;
			this->lblStepBarrel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepBarrel->Location = System::Drawing::Point(870, 366);
			this->lblStepBarrel->Name = L"lblStepBarrel";
			this->lblStepBarrel->Size = System::Drawing::Size(85, 20);
			this->lblStepBarrel->TabIndex = 7;
			this->lblStepBarrel->Text = L"BarrelStep";
			this->lblStepBarrel->Click += gcnew System::EventHandler(this, &MachineScreen::Barrel_Click);
			// 
			// lblStepTurnover
			// 
			this->lblStepTurnover->AutoSize = true;
			this->lblStepTurnover->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepTurnover->Location = System::Drawing::Point(866, 485);
			this->lblStepTurnover->Name = L"lblStepTurnover";
			this->lblStepTurnover->Size = System::Drawing::Size(108, 20);
			this->lblStepTurnover->TabIndex = 7;
			this->lblStepTurnover->Text = L"TurnOverStep";
			this->lblStepTurnover->Click += gcnew System::EventHandler(this, &MachineScreen::TurnOver_Click);
			// 
			// lblMMIVersion
			// 
			this->lblMMIVersion->AutoSize = true;
			this->lblMMIVersion->BackColor = System::Drawing::Color::White;
			this->lblMMIVersion->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMMIVersion->Location = System::Drawing::Point(26, 770);
			this->lblMMIVersion->Name = L"lblMMIVersion";
			this->lblMMIVersion->Size = System::Drawing::Size(126, 25);
			this->lblMMIVersion->TabIndex = 34;
			this->lblMMIVersion->Text = L"MMIVersion";
			// 
			// lblAutomationVersion
			// 
			this->lblAutomationVersion->AutoSize = true;
			this->lblAutomationVersion->BackColor = System::Drawing::Color::White;
			this->lblAutomationVersion->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblAutomationVersion->Location = System::Drawing::Point(26, 821);
			this->lblAutomationVersion->Name = L"lblAutomationVersion";
			this->lblAutomationVersion->Size = System::Drawing::Size(193, 25);
			this->lblAutomationVersion->TabIndex = 35;
			this->lblAutomationVersion->Text = L"AutomationVersion";
			// 
			// pnlPicture
			// 
			this->pnlPicture->AutoSize = true;
			this->pnlPicture->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pnlPicture.BackgroundImage")));
			this->pnlPicture->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pnlPicture->Controls->Add(this->lblUtilitiesStatus);
			this->pnlPicture->Controls->Add(this->lblStepLoader);
			this->pnlPicture->Controls->Add(this->lblStepUtilities);
			this->pnlPicture->Controls->Add(this->lblStepPearling);
			this->pnlPicture->Controls->Add(this->lblLoader);
			this->pnlPicture->Controls->Add(this->lblLoaderStatus);
			this->pnlPicture->Controls->Add(this->lblVision);
			this->pnlPicture->Controls->Add(this->lblLift2);
			this->pnlPicture->Controls->Add(this->lblPearling);
			this->pnlPicture->Controls->Add(this->lblPearlingStatus);
			this->pnlPicture->Controls->Add(this->lblVisionStatus);
			this->pnlPicture->Controls->Add(this->msSharpen);
			this->pnlPicture->Controls->Add(this->lblStepVision);
			this->pnlPicture->Controls->Add(this->pnlImageTurnOver);
			this->pnlPicture->Controls->Add(this->lblAutomationVersion);
			this->pnlPicture->Controls->Add(this->lblStepSharpening);
			this->pnlPicture->Controls->Add(this->lblMMIVersion);
			this->pnlPicture->Controls->Add(this->lblSharpening);
			this->pnlPicture->Controls->Add(this->pnlCounter);
			this->pnlPicture->Controls->Add(this->lblStepBarrel);
			this->pnlPicture->Controls->Add(this->pnlVacuum);
			this->pnlPicture->Controls->Add(this->lblBarrel);
			this->pnlPicture->Controls->Add(this->btnSavePersistent);
			this->pnlPicture->Controls->Add(this->pbEmergency1);
			this->pnlPicture->Controls->Add(this->lblTurnover);
			this->pnlPicture->Controls->Add(this->msBarrel);
			this->pnlPicture->Controls->Add(this->msTurnOver);
			this->pnlPicture->Controls->Add(this->msReject);
			this->pnlPicture->Controls->Add(this->msLift1);
			this->pnlPicture->Controls->Add(this->msLift2);
			this->pnlPicture->Controls->Add(this->msTable);
			this->pnlPicture->Controls->Add(this->lblManagerRunStep);
			this->pnlPicture->Controls->Add(this->lblLift1Status);
			this->pnlPicture->Controls->Add(this->lblTurnOverStatus);
			this->pnlPicture->Controls->Add(this->lblTableStatus);
			this->pnlPicture->Controls->Add(this->lblBarrelStatus);
			this->pnlPicture->Controls->Add(this->lblLift2Status);
			this->pnlPicture->Controls->Add(this->lblRejectStatus);
			this->pnlPicture->Controls->Add(this->lblSharpenStatus);
			this->pnlPicture->Controls->Add(this->pbDoorsPearling2);
			this->pnlPicture->Controls->Add(this->lblStepTurnover);
			this->pnlPicture->Controls->Add(this->pnlLoader);
			this->pnlPicture->Controls->Add(this->pnlPearling);
			this->pnlPicture->Controls->Add(this->pbDoorsLoader2);
			this->pnlPicture->Controls->Add(this->pbDoorsLoader1);
			this->pnlPicture->Controls->Add(this->pbDoorsPearling1);
			this->pnlPicture->Controls->Add(this->lblTable);
			this->pnlPicture->Controls->Add(this->pbEmergency3);
			this->pnlPicture->Controls->Add(this->lblStepTable);
			this->pnlPicture->Controls->Add(this->pbEmergency2);
			this->pnlPicture->Controls->Add(this->lblUtilities);
			this->pnlPicture->Controls->Add(this->pnlVision);
			this->pnlPicture->Controls->Add(this->lblStepLift1);
			this->pnlPicture->Controls->Add(this->lblLift1);
			this->pnlPicture->Controls->Add(this->lblStepReject);
			this->pnlPicture->Controls->Add(this->lblReject);
			this->pnlPicture->Controls->Add(this->lblStepLift2);
			this->pnlPicture->Controls->Add(this->pnlReject);
			this->pnlPicture->Controls->Add(this->pnlLift1);
			this->pnlPicture->Controls->Add(this->pnlLift2);
			this->pnlPicture->Controls->Add(this->pnlTurnOver);
			this->pnlPicture->Controls->Add(this->pnlBarrel);
			this->pnlPicture->Controls->Add(this->pnlTable);
			this->pnlPicture->Controls->Add(this->pnlSharpen);
			this->pnlPicture->Controls->Add(this->pnlUtilities);
			this->pnlPicture->Location = System::Drawing::Point(19, 15);
			this->pnlPicture->Name = L"pnlPicture";
			this->pnlPicture->Size = System::Drawing::Size(1540, 865);
			this->pnlPicture->TabIndex = 36;
			// 
			// lblUtilitiesStatus
			// 
			this->lblUtilitiesStatus->AutoSize = true;
			this->lblUtilitiesStatus->BackColor = System::Drawing::SystemColors::Control;
			this->lblUtilitiesStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblUtilitiesStatus->Location = System::Drawing::Point(17, 118);
			this->lblUtilitiesStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblUtilitiesStatus->Name = L"lblUtilitiesStatus";
			this->lblUtilitiesStatus->Size = System::Drawing::Size(107, 20);
			this->lblUtilitiesStatus->TabIndex = 65;
			this->lblUtilitiesStatus->Text = L"UtilitiesStatus";
			this->lblUtilitiesStatus->Click += gcnew System::EventHandler(this, &MachineScreen::Utilities_Click);
			// 
			// lblStepUtilities
			// 
			this->lblStepUtilities->AutoSize = true;
			this->lblStepUtilities->BackColor = System::Drawing::SystemColors::Control;
			this->lblStepUtilities->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepUtilities->Location = System::Drawing::Point(17, 88);
			this->lblStepUtilities->Name = L"lblStepUtilities";
			this->lblStepUtilities->Size = System::Drawing::Size(94, 20);
			this->lblStepUtilities->TabIndex = 47;
			this->lblStepUtilities->Text = L"UtilitiesStep";
			this->lblStepUtilities->Click += gcnew System::EventHandler(this, &MachineScreen::Utilities_Click);
			// 
			// lblLoaderStatus
			// 
			this->lblLoaderStatus->AutoSize = true;
			this->lblLoaderStatus->BackColor = System::Drawing::SystemColors::Control;
			this->lblLoaderStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLoaderStatus->Location = System::Drawing::Point(1226, 138);
			this->lblLoaderStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblLoaderStatus->Name = L"lblLoaderStatus";
			this->lblLoaderStatus->Size = System::Drawing::Size(106, 20);
			this->lblLoaderStatus->TabIndex = 62;
			this->lblLoaderStatus->Text = L"LoaderStatus";
			this->lblLoaderStatus->Click += gcnew System::EventHandler(this, &MachineScreen::Loader_Click);
			// 
			// lblVision
			// 
			this->lblVision->AutoSize = true;
			this->lblVision->BackColor = System::Drawing::SystemColors::Control;
			this->lblVision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVision->Location = System::Drawing::Point(1350, 537);
			this->lblVision->Name = L"lblVision";
			this->lblVision->Size = System::Drawing::Size(105, 37);
			this->lblVision->TabIndex = 43;
			this->lblVision->Text = L"Vision";
			this->lblVision->Click += gcnew System::EventHandler(this, &MachineScreen::Vision_Click);
			// 
			// lblLift2
			// 
			this->lblLift2->AutoSize = true;
			this->lblLift2->BackColor = System::Drawing::SystemColors::Control;
			this->lblLift2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLift2->Location = System::Drawing::Point(732, 699);
			this->lblLift2->Name = L"lblLift2";
			this->lblLift2->Size = System::Drawing::Size(152, 37);
			this->lblLift2->TabIndex = 37;
			this->lblLift2->Text = L"Lift2(Out)";
			this->lblLift2->Click += gcnew System::EventHandler(this, &MachineScreen::Lift2_Click);
			// 
			// lblPearlingStatus
			// 
			this->lblPearlingStatus->AutoSize = true;
			this->lblPearlingStatus->BackColor = System::Drawing::SystemColors::Control;
			this->lblPearlingStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPearlingStatus->ForeColor = System::Drawing::SystemColors::ControlText;
			this->lblPearlingStatus->Location = System::Drawing::Point(501, 115);
			this->lblPearlingStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblPearlingStatus->Name = L"lblPearlingStatus";
			this->lblPearlingStatus->Size = System::Drawing::Size(113, 20);
			this->lblPearlingStatus->TabIndex = 37;
			this->lblPearlingStatus->Text = L"PearlingStatus";
			this->lblPearlingStatus->Click += gcnew System::EventHandler(this, &MachineScreen::Pearling_Click);
			// 
			// lblVisionStatus
			// 
			this->lblVisionStatus->AutoSize = true;
			this->lblVisionStatus->BackColor = System::Drawing::SystemColors::Control;
			this->lblVisionStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVisionStatus->Location = System::Drawing::Point(1353, 619);
			this->lblVisionStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblVisionStatus->Name = L"lblVisionStatus";
			this->lblVisionStatus->Size = System::Drawing::Size(99, 20);
			this->lblVisionStatus->TabIndex = 63;
			this->lblVisionStatus->Text = L"VisionStatus";
			this->lblVisionStatus->Click += gcnew System::EventHandler(this, &MachineScreen::Vision_Click);
			// 
			// msSharpen
			// 
			this->msSharpen->BackColor = System::Drawing::Color::Transparent;
			this->msSharpen->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msSharpen->Location = System::Drawing::Point(638, 266);
			this->msSharpen->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msSharpen->Name = L"msSharpen";
			this->msSharpen->Offset = static_cast<System::UInt32>(0);
			this->msSharpen->Size = System::Drawing::Size(65, 100);
			this->msSharpen->TabIndex = 6;
			this->msSharpen->Click += gcnew System::EventHandler(this, &MachineScreen::Sharpen_Click);
			// 
			// lblStepVision
			// 
			this->lblStepVision->AutoSize = true;
			this->lblStepVision->BackColor = System::Drawing::SystemColors::Control;
			this->lblStepVision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepVision->Location = System::Drawing::Point(1353, 596);
			this->lblStepVision->Name = L"lblStepVision";
			this->lblStepVision->Size = System::Drawing::Size(86, 20);
			this->lblStepVision->TabIndex = 44;
			this->lblStepVision->Text = L"VisionStep";
			this->lblStepVision->Click += gcnew System::EventHandler(this, &MachineScreen::Vision_Click);
			// 
			// pnlImageTurnOver
			// 
			this->pnlImageTurnOver->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pnlImageTurnOver.BackgroundImage")));
			this->pnlImageTurnOver->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pnlImageTurnOver->Location = System::Drawing::Point(753, 474);
			this->pnlImageTurnOver->Name = L"pnlImageTurnOver";
			this->pnlImageTurnOver->Size = System::Drawing::Size(105, 80);
			this->pnlImageTurnOver->TabIndex = 68;
			// 
			// pnlCounter
			// 
			this->pnlCounter->BackColor = System::Drawing::Color::Transparent;
			this->pnlCounter->Location = System::Drawing::Point(11, 218);
			this->pnlCounter->Name = L"pnlCounter";
			this->pnlCounter->Size = System::Drawing::Size(208, 203);
			this->pnlCounter->TabIndex = 67;
			this->pnlCounter->Click += gcnew System::EventHandler(this, &MachineScreen::pnlCounter_Click);
			// 
			// pnlVacuum
			// 
			this->pnlVacuum->BackColor = System::Drawing::Color::Transparent;
			this->pnlVacuum->Location = System::Drawing::Point(11, 425);
			this->pnlVacuum->Name = L"pnlVacuum";
			this->pnlVacuum->Size = System::Drawing::Size(208, 175);
			this->pnlVacuum->TabIndex = 49;
			this->pnlVacuum->Click += gcnew System::EventHandler(this, &MachineScreen::pnlVacuum_Click);
			// 
			// btnSavePersistent
			// 
			this->btnSavePersistent->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnSavePersistent->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSavePersistent->Location = System::Drawing::Point(19, 606);
			this->btnSavePersistent->Name = L"btnSavePersistent";
			this->btnSavePersistent->Size = System::Drawing::Size(200, 100);
			this->btnSavePersistent->TabIndex = 66;
			this->btnSavePersistent->Text = L"Save persistent";
			this->btnSavePersistent->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnSavePersistent->UseVisualStyleBackColor = true;
			this->btnSavePersistent->Click += gcnew System::EventHandler(this, &MachineScreen::btnSavePersistent_Click);
			// 
			// pbEmergency1
			// 
			this->pbEmergency1->BackColor = System::Drawing::Color::Transparent;
			this->pbEmergency1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbEmergency1.Image")));
			this->pbEmergency1->Location = System::Drawing::Point(353, 131);
			this->pbEmergency1->Name = L"pbEmergency1";
			this->pbEmergency1->Size = System::Drawing::Size(100, 100);
			this->pbEmergency1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbEmergency1->TabIndex = 49;
			this->pbEmergency1->TabStop = false;
			// 
			// msBarrel
			// 
			this->msBarrel->BackColor = System::Drawing::Color::Transparent;
			this->msBarrel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msBarrel->Location = System::Drawing::Point(765, 343);
			this->msBarrel->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msBarrel->Name = L"msBarrel";
			this->msBarrel->Offset = static_cast<System::UInt32>(0);
			this->msBarrel->Size = System::Drawing::Size(58, 112);
			this->msBarrel->TabIndex = 6;
			this->msBarrel->Click += gcnew System::EventHandler(this, &MachineScreen::Barrel_Click);
			// 
			// msTurnOver
			// 
			this->msTurnOver->BackColor = System::Drawing::Color::Transparent;
			this->msTurnOver->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msTurnOver->Location = System::Drawing::Point(879, 537);
			this->msTurnOver->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msTurnOver->Name = L"msTurnOver";
			this->msTurnOver->Offset = static_cast<System::UInt32>(0);
			this->msTurnOver->Size = System::Drawing::Size(72, 104);
			this->msTurnOver->TabIndex = 7;
			this->msTurnOver->Click += gcnew System::EventHandler(this, &MachineScreen::TurnOver_Click);
			// 
			// msReject
			// 
			this->msReject->BackColor = System::Drawing::Color::Transparent;
			this->msReject->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msReject->Location = System::Drawing::Point(573, 612);
			this->msReject->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msReject->Name = L"msReject";
			this->msReject->Offset = static_cast<System::UInt32>(0);
			this->msReject->Size = System::Drawing::Size(62, 94);
			this->msReject->TabIndex = 0;
			this->msReject->Click += gcnew System::EventHandler(this, &MachineScreen::Reject_Click);
			// 
			// msLift1
			// 
			this->msLift1->BackColor = System::Drawing::Color::Transparent;
			this->msLift1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msLift1->Location = System::Drawing::Point(652, 612);
			this->msLift1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msLift1->Name = L"msLift1";
			this->msLift1->Offset = static_cast<System::UInt32>(0);
			this->msLift1->Size = System::Drawing::Size(60, 97);
			this->msLift1->TabIndex = 0;
			this->msLift1->Click += gcnew System::EventHandler(this, &MachineScreen::Lift1_Click);
			// 
			// msLift2
			// 
			this->msLift2->BackColor = System::Drawing::Color::Transparent;
			this->msLift2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msLift2->Location = System::Drawing::Point(729, 612);
			this->msLift2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msLift2->Name = L"msLift2";
			this->msLift2->Offset = static_cast<System::UInt32>(0);
			this->msLift2->Size = System::Drawing::Size(71, 94);
			this->msLift2->TabIndex = 0;
			this->msLift2->Click += gcnew System::EventHandler(this, &MachineScreen::Lift2_Click);
			// 
			// msTable
			// 
			this->msTable->BackColor = System::Drawing::Color::Transparent;
			this->msTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msTable->Location = System::Drawing::Point(682, 406);
			this->msTable->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msTable->Name = L"msTable";
			this->msTable->Offset = static_cast<System::UInt32>(0);
			this->msTable->Size = System::Drawing::Size(68, 96);
			this->msTable->TabIndex = 7;
			this->msTable->Click += gcnew System::EventHandler(this, &MachineScreen::Table_Click);
			// 
			// lblManagerRunStep
			// 
			this->lblManagerRunStep->AutoSize = true;
			this->lblManagerRunStep->BackColor = System::Drawing::Color::White;
			this->lblManagerRunStep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblManagerRunStep->Location = System::Drawing::Point(26, 721);
			this->lblManagerRunStep->Name = L"lblManagerRunStep";
			this->lblManagerRunStep->Size = System::Drawing::Size(180, 25);
			this->lblManagerRunStep->TabIndex = 37;
			this->lblManagerRunStep->Text = L"ManagerRunStep";
			// 
			// lblLift1Status
			// 
			this->lblLift1Status->AutoSize = true;
			this->lblLift1Status->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLift1Status->Location = System::Drawing::Point(634, 830);
			this->lblLift1Status->Margin = System::Windows::Forms::Padding(3);
			this->lblLift1Status->Name = L"lblLift1Status";
			this->lblLift1Status->Size = System::Drawing::Size(87, 20);
			this->lblLift1Status->TabIndex = 64;
			this->lblLift1Status->Text = L"Lift1Status";
			this->lblLift1Status->Click += gcnew System::EventHandler(this, &MachineScreen::Lift1_Click);
			// 
			// lblTurnOverStatus
			// 
			this->lblTurnOverStatus->AutoSize = true;
			this->lblTurnOverStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTurnOverStatus->Location = System::Drawing::Point(866, 505);
			this->lblTurnOverStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblTurnOverStatus->Name = L"lblTurnOverStatus";
			this->lblTurnOverStatus->Size = System::Drawing::Size(121, 20);
			this->lblTurnOverStatus->TabIndex = 61;
			this->lblTurnOverStatus->Text = L"TurnOverStatus";
			this->lblTurnOverStatus->Click += gcnew System::EventHandler(this, &MachineScreen::TurnOver_Click);
			// 
			// lblTableStatus
			// 
			this->lblTableStatus->AutoSize = true;
			this->lblTableStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTableStatus->Location = System::Drawing::Point(433, 466);
			this->lblTableStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblTableStatus->Name = L"lblTableStatus";
			this->lblTableStatus->Size = System::Drawing::Size(95, 20);
			this->lblTableStatus->TabIndex = 60;
			this->lblTableStatus->Text = L"TableStatus";
			this->lblTableStatus->Click += gcnew System::EventHandler(this, &MachineScreen::Table_Click);
			// 
			// lblBarrelStatus
			// 
			this->lblBarrelStatus->AutoSize = true;
			this->lblBarrelStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBarrelStatus->Location = System::Drawing::Point(870, 386);
			this->lblBarrelStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblBarrelStatus->Name = L"lblBarrelStatus";
			this->lblBarrelStatus->Size = System::Drawing::Size(98, 20);
			this->lblBarrelStatus->TabIndex = 59;
			this->lblBarrelStatus->Text = L"BarrelStatus";
			this->lblBarrelStatus->Click += gcnew System::EventHandler(this, &MachineScreen::Barrel_Click);
			// 
			// lblLift2Status
			// 
			this->lblLift2Status->AutoSize = true;
			this->lblLift2Status->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLift2Status->Location = System::Drawing::Point(749, 832);
			this->lblLift2Status->Margin = System::Windows::Forms::Padding(3);
			this->lblLift2Status->Name = L"lblLift2Status";
			this->lblLift2Status->Size = System::Drawing::Size(87, 20);
			this->lblLift2Status->TabIndex = 58;
			this->lblLift2Status->Text = L"Lift2Status";
			this->lblLift2Status->Click += gcnew System::EventHandler(this, &MachineScreen::Lift2_Click);
			// 
			// lblRejectStatus
			// 
			this->lblRejectStatus->AutoSize = true;
			this->lblRejectStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRejectStatus->Location = System::Drawing::Point(469, 788);
			this->lblRejectStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblRejectStatus->Name = L"lblRejectStatus";
			this->lblRejectStatus->Size = System::Drawing::Size(102, 20);
			this->lblRejectStatus->TabIndex = 57;
			this->lblRejectStatus->Text = L"RejectStatus";
			this->lblRejectStatus->Click += gcnew System::EventHandler(this, &MachineScreen::Reject_Click);
			// 
			// lblSharpenStatus
			// 
			this->lblSharpenStatus->AutoSize = true;
			this->lblSharpenStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSharpenStatus->Location = System::Drawing::Point(469, 349);
			this->lblSharpenStatus->Margin = System::Windows::Forms::Padding(3);
			this->lblSharpenStatus->Name = L"lblSharpenStatus";
			this->lblSharpenStatus->Size = System::Drawing::Size(117, 20);
			this->lblSharpenStatus->TabIndex = 56;
			this->lblSharpenStatus->Text = L"SharpenStatus";
			this->lblSharpenStatus->Click += gcnew System::EventHandler(this, &MachineScreen::Sharpen_Click);
			// 
			// pbDoorsPearling2
			// 
			this->pbDoorsPearling2->BackColor = System::Drawing::Color::Transparent;
			this->pbDoorsPearling2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbDoorsPearling2.Image")));
			this->pbDoorsPearling2->Location = System::Drawing::Point(982, 25);
			this->pbDoorsPearling2->Name = L"pbDoorsPearling2";
			this->pbDoorsPearling2->Size = System::Drawing::Size(100, 100);
			this->pbDoorsPearling2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbDoorsPearling2->TabIndex = 53;
			this->pbDoorsPearling2->TabStop = false;
			// 
			// pnlLoader
			// 
			this->pnlLoader->BackColor = System::Drawing::Color::Transparent;
			this->pnlLoader->Controls->Add(this->msLoader);
			this->pnlLoader->Location = System::Drawing::Point(1037, 11);
			this->pnlLoader->Name = L"pnlLoader";
			this->pnlLoader->Size = System::Drawing::Size(474, 333);
			this->pnlLoader->TabIndex = 0;
			this->pnlLoader->Click += gcnew System::EventHandler(this, &MachineScreen::Loader_Click);
			// 
			// msLoader
			// 
			this->msLoader->BackColor = System::Drawing::Color::Transparent;
			this->msLoader->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msLoader->Location = System::Drawing::Point(346, 77);
			this->msLoader->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msLoader->Name = L"msLoader";
			this->msLoader->Offset = static_cast<System::UInt32>(0);
			this->msLoader->Size = System::Drawing::Size(65, 97);
			this->msLoader->TabIndex = 0;
			this->msLoader->Click += gcnew System::EventHandler(this, &MachineScreen::Loader_Click);
			// 
			// pnlPearling
			// 
			this->pnlPearling->BackColor = System::Drawing::Color::Transparent;
			this->pnlPearling->Controls->Add(this->msPearling);
			this->pnlPearling->ForeColor = System::Drawing::Color::Transparent;
			this->pnlPearling->Location = System::Drawing::Point(476, 42);
			this->pnlPearling->Name = L"pnlPearling";
			this->pnlPearling->Size = System::Drawing::Size(435, 218);
			this->pnlPearling->TabIndex = 4;
			this->pnlPearling->Click += gcnew System::EventHandler(this, &MachineScreen::Pearling_Click);
			// 
			// msPearling
			// 
			this->msPearling->BackColor = System::Drawing::Color::Transparent;
			this->msPearling->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msPearling->Location = System::Drawing::Point(331, 106);
			this->msPearling->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msPearling->Name = L"msPearling";
			this->msPearling->Offset = static_cast<System::UInt32>(0);
			this->msPearling->Size = System::Drawing::Size(62, 93);
			this->msPearling->TabIndex = 0;
			this->msPearling->Click += gcnew System::EventHandler(this, &MachineScreen::Pearling_Click);
			// 
			// pbDoorsLoader2
			// 
			this->pbDoorsLoader2->BackColor = System::Drawing::Color::Transparent;
			this->pbDoorsLoader2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbDoorsLoader2.Image")));
			this->pbDoorsLoader2->Location = System::Drawing::Point(982, 761);
			this->pbDoorsLoader2->Name = L"pbDoorsLoader2";
			this->pbDoorsLoader2->Size = System::Drawing::Size(100, 100);
			this->pbDoorsLoader2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbDoorsLoader2->TabIndex = 55;
			this->pbDoorsLoader2->TabStop = false;
			// 
			// pbDoorsLoader1
			// 
			this->pbDoorsLoader1->BackColor = System::Drawing::Color::Transparent;
			this->pbDoorsLoader1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbDoorsLoader1.Image")));
			this->pbDoorsLoader1->Location = System::Drawing::Point(348, 761);
			this->pbDoorsLoader1->Name = L"pbDoorsLoader1";
			this->pbDoorsLoader1->Size = System::Drawing::Size(100, 100);
			this->pbDoorsLoader1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbDoorsLoader1->TabIndex = 54;
			this->pbDoorsLoader1->TabStop = false;
			// 
			// pbDoorsPearling1
			// 
			this->pbDoorsPearling1->BackColor = System::Drawing::Color::Transparent;
			this->pbDoorsPearling1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbDoorsPearling1.Image")));
			this->pbDoorsPearling1->Location = System::Drawing::Point(353, 25);
			this->pbDoorsPearling1->Name = L"pbDoorsPearling1";
			this->pbDoorsPearling1->Size = System::Drawing::Size(100, 100);
			this->pbDoorsPearling1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbDoorsPearling1->TabIndex = 52;
			this->pbDoorsPearling1->TabStop = false;
			// 
			// pbEmergency3
			// 
			this->pbEmergency3->BackColor = System::Drawing::Color::Transparent;
			this->pbEmergency3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbEmergency3.Image")));
			this->pbEmergency3->Location = System::Drawing::Point(982, 655);
			this->pbEmergency3->Name = L"pbEmergency3";
			this->pbEmergency3->Size = System::Drawing::Size(100, 100);
			this->pbEmergency3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbEmergency3->TabIndex = 51;
			this->pbEmergency3->TabStop = false;
			// 
			// pbEmergency2
			// 
			this->pbEmergency2->BackColor = System::Drawing::Color::Transparent;
			this->pbEmergency2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbEmergency2.Image")));
			this->pbEmergency2->Location = System::Drawing::Point(349, 655);
			this->pbEmergency2->Name = L"pbEmergency2";
			this->pbEmergency2->Size = System::Drawing::Size(100, 100);
			this->pbEmergency2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbEmergency2->TabIndex = 50;
			this->pbEmergency2->TabStop = false;
			// 
			// lblUtilities
			// 
			this->lblUtilities->AutoSize = true;
			this->lblUtilities->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblUtilities->Location = System::Drawing::Point(14, 25);
			this->lblUtilities->Name = L"lblUtilities";
			this->lblUtilities->Size = System::Drawing::Size(119, 37);
			this->lblUtilities->TabIndex = 46;
			this->lblUtilities->Text = L"Utilities";
			this->lblUtilities->Click += gcnew System::EventHandler(this, &MachineScreen::Utilities_Click);
			// 
			// pnlVision
			// 
			this->pnlVision->BackColor = System::Drawing::Color::Transparent;
			this->pnlVision->Controls->Add(this->msVision);
			this->pnlVision->Location = System::Drawing::Point(1175, 485);
			this->pnlVision->Name = L"pnlVision";
			this->pnlVision->Size = System::Drawing::Size(336, 236);
			this->pnlVision->TabIndex = 1;
			this->pnlVision->Click += gcnew System::EventHandler(this, &MachineScreen::Vision_Click);
			// 
			// msVision
			// 
			this->msVision->BackColor = System::Drawing::Color::Transparent;
			this->msVision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msVision->Location = System::Drawing::Point(34, 50);
			this->msVision->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->msVision->Name = L"msVision";
			this->msVision->Offset = static_cast<System::UInt32>(0);
			this->msVision->Size = System::Drawing::Size(80, 109);
			this->msVision->TabIndex = 0;
			this->msVision->Click += gcnew System::EventHandler(this, &MachineScreen::Vision_Click);
			// 
			// lblStepLift1
			// 
			this->lblStepLift1->AutoSize = true;
			this->lblStepLift1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepLift1->Location = System::Drawing::Point(634, 810);
			this->lblStepLift1->Name = L"lblStepLift1";
			this->lblStepLift1->Size = System::Drawing::Size(74, 20);
			this->lblStepLift1->TabIndex = 42;
			this->lblStepLift1->Text = L"Lift1Step";
			this->lblStepLift1->Click += gcnew System::EventHandler(this, &MachineScreen::Lift1_Click);
			// 
			// lblLift1
			// 
			this->lblLift1->AutoSize = true;
			this->lblLift1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLift1->Location = System::Drawing::Point(631, 758);
			this->lblLift1->Name = L"lblLift1";
			this->lblLift1->Size = System::Drawing::Size(124, 37);
			this->lblLift1->TabIndex = 41;
			this->lblLift1->Text = L"Lift1(In)";
			this->lblLift1->Click += gcnew System::EventHandler(this, &MachineScreen::Lift1_Click);
			// 
			// lblStepReject
			// 
			this->lblStepReject->AutoSize = true;
			this->lblStepReject->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepReject->Location = System::Drawing::Point(469, 768);
			this->lblStepReject->Name = L"lblStepReject";
			this->lblStepReject->Size = System::Drawing::Size(89, 20);
			this->lblStepReject->TabIndex = 40;
			this->lblStepReject->Text = L"RejectStep";
			this->lblStepReject->Click += gcnew System::EventHandler(this, &MachineScreen::Reject_Click);
			// 
			// lblReject
			// 
			this->lblReject->AutoSize = true;
			this->lblReject->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblReject->Location = System::Drawing::Point(462, 716);
			this->lblReject->Name = L"lblReject";
			this->lblReject->Size = System::Drawing::Size(105, 37);
			this->lblReject->TabIndex = 39;
			this->lblReject->Text = L"Reject";
			this->lblReject->Click += gcnew System::EventHandler(this, &MachineScreen::Reject_Click);
			// 
			// lblStepLift2
			// 
			this->lblStepLift2->AutoSize = true;
			this->lblStepLift2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStepLift2->Location = System::Drawing::Point(749, 810);
			this->lblStepLift2->Name = L"lblStepLift2";
			this->lblStepLift2->Size = System::Drawing::Size(74, 20);
			this->lblStepLift2->TabIndex = 38;
			this->lblStepLift2->Text = L"Lift2Step";
			this->lblStepLift2->Click += gcnew System::EventHandler(this, &MachineScreen::Lift2_Click);
			// 
			// pnlReject
			// 
			this->pnlReject->BackColor = System::Drawing::Color::Transparent;
			this->pnlReject->Location = System::Drawing::Point(557, 587);
			this->pnlReject->Name = L"pnlReject";
			this->pnlReject->Size = System::Drawing::Size(68, 208);
			this->pnlReject->TabIndex = 9;
			this->pnlReject->Click += gcnew System::EventHandler(this, &MachineScreen::Reject_Click);
			// 
			// pnlLift1
			// 
			this->pnlLift1->BackColor = System::Drawing::Color::Transparent;
			this->pnlLift1->Location = System::Drawing::Point(641, 587);
			this->pnlLift1->Name = L"pnlLift1";
			this->pnlLift1->Size = System::Drawing::Size(66, 208);
			this->pnlLift1->TabIndex = 8;
			this->pnlLift1->Click += gcnew System::EventHandler(this, &MachineScreen::Lift1_Click);
			// 
			// pnlLift2
			// 
			this->pnlLift2->BackColor = System::Drawing::Color::Transparent;
			this->pnlLift2->Location = System::Drawing::Point(729, 587);
			this->pnlLift2->Name = L"pnlLift2";
			this->pnlLift2->Size = System::Drawing::Size(60, 208);
			this->pnlLift2->TabIndex = 7;
			this->pnlLift2->Click += gcnew System::EventHandler(this, &MachineScreen::Lift2_Click);
			// 
			// pnlTurnOver
			// 
			this->pnlTurnOver->BackColor = System::Drawing::Color::Transparent;
			this->pnlTurnOver->Location = System::Drawing::Point(752, 474);
			this->pnlTurnOver->Name = L"pnlTurnOver";
			this->pnlTurnOver->Size = System::Drawing::Size(199, 80);
			this->pnlTurnOver->TabIndex = 3;
			this->pnlTurnOver->Click += gcnew System::EventHandler(this, &MachineScreen::TurnOver_Click);
			// 
			// pnlBarrel
			// 
			this->pnlBarrel->BackColor = System::Drawing::Color::Transparent;
			this->pnlBarrel->Location = System::Drawing::Point(739, 332);
			this->pnlBarrel->Name = L"pnlBarrel";
			this->pnlBarrel->Size = System::Drawing::Size(229, 89);
			this->pnlBarrel->TabIndex = 2;
			this->pnlBarrel->Click += gcnew System::EventHandler(this, &MachineScreen::Barrel_Click);
			// 
			// pnlTable
			// 
			this->pnlTable->BackColor = System::Drawing::Color::Transparent;
			this->pnlTable->Location = System::Drawing::Point(537, 376);
			this->pnlTable->Name = L"pnlTable";
			this->pnlTable->Size = System::Drawing::Size(184, 178);
			this->pnlTable->TabIndex = 5;
			this->pnlTable->Click += gcnew System::EventHandler(this, &MachineScreen::Table_Click);
			// 
			// pnlSharpen
			// 
			this->pnlSharpen->BackColor = System::Drawing::Color::Transparent;
			this->pnlSharpen->Location = System::Drawing::Point(476, 291);
			this->pnlSharpen->Name = L"pnlSharpen";
			this->pnlSharpen->Size = System::Drawing::Size(227, 79);
			this->pnlSharpen->TabIndex = 1;
			this->pnlSharpen->Click += gcnew System::EventHandler(this, &MachineScreen::Sharpen_Click);
			// 
			// pnlUtilities
			// 
			this->pnlUtilities->BackColor = System::Drawing::Color::Transparent;
			this->pnlUtilities->Controls->Add(this->msUtilities);
			this->pnlUtilities->Location = System::Drawing::Point(12, 11);
			this->pnlUtilities->Name = L"pnlUtilities";
			this->pnlUtilities->Size = System::Drawing::Size(207, 187);
			this->pnlUtilities->TabIndex = 48;
			this->pnlUtilities->Click += gcnew System::EventHandler(this, &MachineScreen::Utilities_Click);
			// 
			// msUtilities
			// 
			this->msUtilities->BackColor = System::Drawing::Color::Transparent;
			this->msUtilities->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->msUtilities->Location = System::Drawing::Point(127, 44);
			this->msUtilities->Margin = System::Windows::Forms::Padding(6);
			this->msUtilities->Name = L"msUtilities";
			this->msUtilities->Offset = static_cast<System::UInt32>(0);
			this->msUtilities->Size = System::Drawing::Size(103, 135);
			this->msUtilities->TabIndex = 45;
			this->msUtilities->Click += gcnew System::EventHandler(this, &MachineScreen::Utilities_Click);
			// 
			// MachineScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->pnlPicture);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"MachineScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"MachineScreen";
			this->Load += gcnew System::EventHandler(this, &MachineScreen::MachineScreen_Load);
			this->VisibleChanged += gcnew System::EventHandler(this, &MachineScreen::MachineScreen_VisibleChanged);
			this->pnlPicture->ResumeLayout(false);
			this->pnlPicture->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbEmergency1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDoorsPearling2))->EndInit();
			this->pnlLoader->ResumeLayout(false);
			this->pnlPearling->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDoorsLoader2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDoorsLoader1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDoorsPearling1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbEmergency3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbEmergency2))->EndInit();
			this->pnlVision->ResumeLayout(false);
			this->pnlUtilities->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void MachineScreen_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Loader_Click(System::Object^  sender, System::EventArgs^  e) {
			if (pnlLoader->Enabled)
			{
				ShowManualScreen(pT_LoaderManualForm);
			}
		 }

private: System::Void btnFreeLift_Click(System::Object^  sender, System::EventArgs^  e) {
			int i_l_LiftNb = TUtilities::i_GetValueFromTag(((System::Windows::Forms::Button^)sender)->Tag);
			TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::FreeLiftNb) + " " + i_l_LiftNb);
			SetTCData(s_OperatorRequest.OR_FreeLift[i_l_LiftNb]);
		 }
private: System::Void Barrel_Click(System::Object^  sender, System::EventArgs^  e) {
			if (pnlBarrel->Enabled)
			{
				ShowManualScreen(pT_BarrelManualForm);
			}
		 }
private: System::Void Sharpen_Click(System::Object^  sender, System::EventArgs^  e) {
			if (pnlSharpen->Enabled)
			{
				ShowManualScreen(pT_SharpenManualForm);
			}
		 }
private: System::Void Pearling_Click(System::Object^  sender, System::EventArgs^  e) {
			if (pnlPearling->Enabled)
			{
				ShowManualScreen(pT_PearlingManualForm);
			}
		 }
private: System::Void Table_Click(System::Object^  sender, System::EventArgs^  e) {
			if (pnlTable->Enabled)
			{
				ShowManualScreen(pT_TableManualForm);
			}
		 }
private: System::Void TurnOver_Click(System::Object^  sender, System::EventArgs^  e) {
			if (pnlTurnOver->Enabled)
			{
				ShowManualScreen(pT_TurnOverManualForm);
			}
		 }

private: System::Void Lift1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pnlLift1->Enabled)
	{
		ShowManualScreen(pT_Lift1ManualForm);
	}
}
private: System::Void Lift2_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pnlLift2->Enabled)
	{
		ShowManualScreen(pT_Lift2ManualForm);
	}
}
private: System::Void Reject_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pnlReject->Enabled)
	{
		ShowManualScreen(pT_RejectManualForm);
	}
}

private: System::Void Vision_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pnlVision->Enabled)
	{
		ShowManualScreen(pT_VisionManualForm);
	}
}

private: System::Void Utilities_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pnlUtilities->Enabled)
	{
		ShowManualScreen(pT_UtilitiesManualForm);
	}
}

private: System::Void MachineScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {

			lblPearling->Text = TUtilities::pS_LoadString(TextIndex::Pearling);
			lblTable->Text = TUtilities::pS_LoadString(TextIndex::Table);
			lblSharpening->Text = TUtilities::pS_LoadString(TextIndex::Sharpening);
			lblBarrel->Text = TUtilities::pS_LoadString(TextIndex::Barrel);
			lblTurnover->Text = TUtilities::pS_LoadString(TextIndex::Turnover);
			lblLoader->Text = TUtilities::pS_LoadString(TextIndex::Loader);
			lblLift1->Text = TUtilities::pS_LoadString(TextIndex::LeftLift);
			lblLift2->Text = TUtilities::pS_LoadString(TextIndex::RightLift);
			lblReject->Text = TUtilities::pS_LoadString(TextIndex::Reject);
			lblVision->Text = TUtilities::pS_LoadString(TextIndex::Vision);
			lblUtilities->Text = TUtilities::pS_LoadString(TextIndex::Utilities);

			lblStepPearling->Text = TUtilities::pS_LoadString(TextIndex::Step) +" :";
			lblStepTable->Text = TUtilities::pS_LoadString(TextIndex::Step) +" :";
			lblStepSharpening->Text = TUtilities::pS_LoadString(TextIndex::Step) +" :";
			lblStepBarrel->Text = TUtilities::pS_LoadString(TextIndex::Step) +" :";
			lblStepTurnover->Text = TUtilities::pS_LoadString(TextIndex::Step) +" :";
			lblStepLoader->Text = TUtilities::pS_LoadString(TextIndex::Step) +" :";
			lblStepLift1->Text = TUtilities::pS_LoadString(TextIndex::Loader);
			lblStepLift2->Text = TUtilities::pS_LoadString(TextIndex::Loader);
			lblStepReject->Text = TUtilities::pS_LoadString(TextIndex::Loader);
		 }
private: void OnDebugClick(System::Object ^sender, System::EventArgs ^e) {
			ModuleStatus^ ms = (ModuleStatus^)sender;

			TTwincatInterface::GetTCVarAccess()->SetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_StepMode), (TC_BOOL)(ms->Debug->Checked));
		 }
 private: void OnStepClick(System::Object ^sender, System::EventArgs ^e) {
				ModuleStatus^ ms = (ModuleStatus^)sender;
				TTwincatInterface::GetTCVarAccess()->SetData(DVT_Global, ms->Offset + offsetof(MODULE_DATA, MD_WaitStep), (TC_BOOL)(false));
		 }
private: System::Void btnSavePersistent_Click(System::Object^  sender, System::EventArgs^  e) {
	SetTCData(b_SavePersistent);
}
private: System::Void pnlVacuum_Click(System::Object^  sender, System::EventArgs^  e) {
	if (pnlVacuum->Enabled)
	{
		ShowManualScreen(pT_VacuumSettingsForm);
	}
}
};
}



