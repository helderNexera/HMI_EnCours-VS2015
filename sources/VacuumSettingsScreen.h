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
	public ref class VacuumSettingsScreen : public System::Windows::Forms::Form
	{
	public:
		VacuumSettingsScreen()
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::VacuumSettingsScreen::OnUserLevelChanged);
			lblTableBlowing->Offset = GetTCManualOffset(s_VacuumSettings.VSM_Table.VS_Blowing);
			lblTableWaitVacuumOk->Offset = GetTCManualOffset(s_VacuumSettings.VSM_Table.VS_WaitWhenVacuumOk);
			lblTableErrorDelay->Offset = GetTCManualOffset(s_VacuumSettings.VSM_Table.VS_ErrorDelay);
			lblTablePartialTakeTime->Offset = GetTCManualOffset(s_VacuumSettings.VSM_TablePartialDelay);

			lblLoaderHeadBlowing->Offset = GetTCManualOffset(s_VacuumSettings.VSM_LoaderHead.VS_Blowing);
			lblLoaderHeadWaitVacuumOk->Offset = GetTCManualOffset(s_VacuumSettings.VSM_LoaderHead.VS_WaitWhenVacuumOk);
			lblLoaderHeadErrorDelay->Offset = GetTCManualOffset(s_VacuumSettings.VSM_LoaderHead.VS_ErrorDelay);

			lblLoaderPlateBlowing->Offset = GetTCManualOffset(s_VacuumSettings.VSM_LoaderPlate.VS_Blowing);
			lblLoaderPlateWaitVacuumOk->Offset = GetTCManualOffset(s_VacuumSettings.VSM_LoaderPlate.VS_WaitWhenVacuumOk);
			lblLoaderPlateErrorDelay->Offset = GetTCManualOffset(s_VacuumSettings.VSM_LoaderPlate.VS_ErrorDelay);

			lblTurnOverBlowing->Offset = GetTCManualOffset(s_VacuumSettings.VSM_TurnOver.VS_Blowing);
			lblTurnOverWaitVacuumOk->Offset = GetTCManualOffset(s_VacuumSettings.VSM_TurnOver.VS_WaitWhenVacuumOk);
			lblTurnOverErrorDelay->Offset = GetTCManualOffset(s_VacuumSettings.VSM_TurnOver.VS_ErrorDelay);
		}
			 // Our specific functions
	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~VacuumSettingsScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  lblBlowing;
	private: MondemaComponents::LabelOffset^  lblTableBlowing;
	private: System::Windows::Forms::Label^  lblErrorDelay;
	private: System::Windows::Forms::Label^  lblWaitVacuumOk;
	private: System::Windows::Forms::Label^  lblTable;
	private: System::Windows::Forms::Label^  lblLoaderHead;
	private: System::Windows::Forms::Label^  lblLoaderPlate;
	private: System::Windows::Forms::Label^  lblTurnOver;
	private: MondemaComponents::LabelOffset^  lblTablePartialTakeTime;
	private: MondemaComponents::LabelOffset^  lblLoaderHeadBlowing;
	private: MondemaComponents::LabelOffset^  lblLoaderPlateBlowing;
	private: MondemaComponents::LabelOffset^  lblTurnOverBlowing;
	private: MondemaComponents::LabelOffset^  lblTableWaitVacuumOk;
	private: MondemaComponents::LabelOffset^  lblLoaderHeadWaitVacuumOk;

	private: MondemaComponents::LabelOffset^  lblLoaderPlateWaitVacuumOk;
	private: MondemaComponents::LabelOffset^  lblTurnOverWaitVacuumOk;
	private: MondemaComponents::LabelOffset^  lblTableErrorDelay;
	private: MondemaComponents::LabelOffset^  lblLoaderHeadErrorDelay;
	private: MondemaComponents::LabelOffset^  lblLoaderPlateErrorDelay;
	private: MondemaComponents::LabelOffset^  lblTurnOverErrorDelay;
	private: System::Windows::Forms::Label^  lblPartialTakeTime;
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
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->lblTablePartialTakeTime = (gcnew MondemaComponents::LabelOffset());
			this->lblTableBlowing = (gcnew MondemaComponents::LabelOffset());
			this->lblBlowing = (gcnew System::Windows::Forms::Label());
			this->lblTable = (gcnew System::Windows::Forms::Label());
			this->lblLoaderHead = (gcnew System::Windows::Forms::Label());
			this->lblLoaderPlate = (gcnew System::Windows::Forms::Label());
			this->lblTurnOver = (gcnew System::Windows::Forms::Label());
			this->lblWaitVacuumOk = (gcnew System::Windows::Forms::Label());
			this->lblErrorDelay = (gcnew System::Windows::Forms::Label());
			this->lblLoaderHeadBlowing = (gcnew MondemaComponents::LabelOffset());
			this->lblLoaderPlateBlowing = (gcnew MondemaComponents::LabelOffset());
			this->lblTurnOverBlowing = (gcnew MondemaComponents::LabelOffset());
			this->lblTableWaitVacuumOk = (gcnew MondemaComponents::LabelOffset());
			this->lblLoaderHeadWaitVacuumOk = (gcnew MondemaComponents::LabelOffset());
			this->lblLoaderPlateWaitVacuumOk = (gcnew MondemaComponents::LabelOffset());
			this->lblTurnOverWaitVacuumOk = (gcnew MondemaComponents::LabelOffset());
			this->lblTableErrorDelay = (gcnew MondemaComponents::LabelOffset());
			this->lblLoaderHeadErrorDelay = (gcnew MondemaComponents::LabelOffset());
			this->lblLoaderPlateErrorDelay = (gcnew MondemaComponents::LabelOffset());
			this->lblTurnOverErrorDelay = (gcnew MondemaComponents::LabelOffset());
			this->lblPartialTakeTime = (gcnew System::Windows::Forms::Label());
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
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
			this->tabPage1->Controls->Add(this->tableLayoutPanel1);
			this->tabPage1->Location = System::Drawing::Point(4, 49);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1570, 842);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 5;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				30.76923F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				17.30769F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				17.30769F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				17.30769F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				17.30769F)));
			this->tableLayoutPanel1->Controls->Add(this->lblTablePartialTakeTime, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->lblTableBlowing, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblBlowing, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblTable, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->lblLoaderHead, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->lblLoaderPlate, 3, 0);
			this->tableLayoutPanel1->Controls->Add(this->lblTurnOver, 4, 0);
			this->tableLayoutPanel1->Controls->Add(this->lblWaitVacuumOk, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblErrorDelay, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->lblLoaderHeadBlowing, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblLoaderPlateBlowing, 3, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblTurnOverBlowing, 4, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblTableWaitVacuumOk, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblLoaderHeadWaitVacuumOk, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblLoaderPlateWaitVacuumOk, 3, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblTurnOverWaitVacuumOk, 4, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblTableErrorDelay, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->lblLoaderHeadErrorDelay, 2, 3);
			this->tableLayoutPanel1->Controls->Add(this->lblLoaderPlateErrorDelay, 3, 3);
			this->tableLayoutPanel1->Controls->Add(this->lblTurnOverErrorDelay, 4, 3);
			this->tableLayoutPanel1->Controls->Add(this->lblPartialTakeTime, 0, 4);
			this->tableLayoutPanel1->Location = System::Drawing::Point(6, 6);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1511, 300);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// lblTablePartialTakeTime
			// 
			this->lblTablePartialTakeTime->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTablePartialTakeTime->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblTablePartialTakeTime->EditText = L"";
			this->lblTablePartialTakeTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTablePartialTakeTime->Location = System::Drawing::Point(469, 245);
			this->lblTablePartialTakeTime->Margin = System::Windows::Forms::Padding(5);
			this->lblTablePartialTakeTime->Name = L"lblTablePartialTakeTime";
			this->lblTablePartialTakeTime->Offset = static_cast<System::UInt32>(0);
			this->lblTablePartialTakeTime->Size = System::Drawing::Size(251, 50);
			this->lblTablePartialTakeTime->TabIndex = 136;
			this->lblTablePartialTakeTime->Tag = L"1";
			this->lblTablePartialTakeTime->Text = L"0";
			this->lblTablePartialTakeTime->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblTablePartialTakeTime->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblTableBlowing
			// 
			this->lblTableBlowing->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTableBlowing->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblTableBlowing->EditText = L"";
			this->lblTableBlowing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTableBlowing->Location = System::Drawing::Point(469, 65);
			this->lblTableBlowing->Margin = System::Windows::Forms::Padding(5);
			this->lblTableBlowing->Name = L"lblTableBlowing";
			this->lblTableBlowing->Offset = static_cast<System::UInt32>(0);
			this->lblTableBlowing->Size = System::Drawing::Size(251, 50);
			this->lblTableBlowing->TabIndex = 117;
			this->lblTableBlowing->Tag = L"1";
			this->lblTableBlowing->Text = L"0";
			this->lblTableBlowing->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblTableBlowing->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblBlowing
			// 
			this->lblBlowing->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblBlowing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBlowing->Location = System::Drawing::Point(3, 63);
			this->lblBlowing->Margin = System::Windows::Forms::Padding(3);
			this->lblBlowing->Name = L"lblBlowing";
			this->lblBlowing->Size = System::Drawing::Size(458, 54);
			this->lblBlowing->TabIndex = 116;
			this->lblBlowing->Tag = L"1";
			this->lblBlowing->Text = L"Blowing";
			this->lblBlowing->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblTable
			// 
			this->lblTable->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTable->Location = System::Drawing::Point(467, 3);
			this->lblTable->Margin = System::Windows::Forms::Padding(3);
			this->lblTable->Name = L"lblTable";
			this->lblTable->Size = System::Drawing::Size(255, 54);
			this->lblTable->TabIndex = 120;
			this->lblTable->Tag = L"1";
			this->lblTable->Text = L"Table";
			this->lblTable->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLoaderHead
			// 
			this->lblLoaderHead->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLoaderHead->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLoaderHead->Location = System::Drawing::Point(728, 3);
			this->lblLoaderHead->Margin = System::Windows::Forms::Padding(3);
			this->lblLoaderHead->Name = L"lblLoaderHead";
			this->lblLoaderHead->Size = System::Drawing::Size(255, 54);
			this->lblLoaderHead->TabIndex = 121;
			this->lblLoaderHead->Tag = L"1";
			this->lblLoaderHead->Text = L"LoaderHead";
			this->lblLoaderHead->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLoaderPlate
			// 
			this->lblLoaderPlate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLoaderPlate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLoaderPlate->Location = System::Drawing::Point(989, 3);
			this->lblLoaderPlate->Margin = System::Windows::Forms::Padding(3);
			this->lblLoaderPlate->Name = L"lblLoaderPlate";
			this->lblLoaderPlate->Size = System::Drawing::Size(255, 54);
			this->lblLoaderPlate->TabIndex = 122;
			this->lblLoaderPlate->Tag = L"1";
			this->lblLoaderPlate->Text = L"LoaderPlate";
			this->lblLoaderPlate->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblTurnOver
			// 
			this->lblTurnOver->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTurnOver->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTurnOver->Location = System::Drawing::Point(1250, 3);
			this->lblTurnOver->Margin = System::Windows::Forms::Padding(3);
			this->lblTurnOver->Name = L"lblTurnOver";
			this->lblTurnOver->Size = System::Drawing::Size(258, 54);
			this->lblTurnOver->TabIndex = 123;
			this->lblTurnOver->Tag = L"1";
			this->lblTurnOver->Text = L"TurnOver";
			this->lblTurnOver->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblWaitVacuumOk
			// 
			this->lblWaitVacuumOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblWaitVacuumOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblWaitVacuumOk->Location = System::Drawing::Point(3, 123);
			this->lblWaitVacuumOk->Margin = System::Windows::Forms::Padding(3);
			this->lblWaitVacuumOk->Name = L"lblWaitVacuumOk";
			this->lblWaitVacuumOk->Size = System::Drawing::Size(458, 54);
			this->lblWaitVacuumOk->TabIndex = 119;
			this->lblWaitVacuumOk->Tag = L"1";
			this->lblWaitVacuumOk->Text = L"WaitVacuumOk";
			this->lblWaitVacuumOk->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblErrorDelay
			// 
			this->lblErrorDelay->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblErrorDelay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblErrorDelay->Location = System::Drawing::Point(3, 183);
			this->lblErrorDelay->Margin = System::Windows::Forms::Padding(3);
			this->lblErrorDelay->Name = L"lblErrorDelay";
			this->lblErrorDelay->Size = System::Drawing::Size(458, 54);
			this->lblErrorDelay->TabIndex = 118;
			this->lblErrorDelay->Tag = L"1";
			this->lblErrorDelay->Text = L"ErrorDelay";
			this->lblErrorDelay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLoaderHeadBlowing
			// 
			this->lblLoaderHeadBlowing->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLoaderHeadBlowing->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLoaderHeadBlowing->EditText = L"";
			this->lblLoaderHeadBlowing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLoaderHeadBlowing->Location = System::Drawing::Point(730, 65);
			this->lblLoaderHeadBlowing->Margin = System::Windows::Forms::Padding(5);
			this->lblLoaderHeadBlowing->Name = L"lblLoaderHeadBlowing";
			this->lblLoaderHeadBlowing->Offset = static_cast<System::UInt32>(0);
			this->lblLoaderHeadBlowing->Size = System::Drawing::Size(251, 50);
			this->lblLoaderHeadBlowing->TabIndex = 124;
			this->lblLoaderHeadBlowing->Tag = L"1";
			this->lblLoaderHeadBlowing->Text = L"0";
			this->lblLoaderHeadBlowing->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLoaderHeadBlowing->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblLoaderPlateBlowing
			// 
			this->lblLoaderPlateBlowing->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLoaderPlateBlowing->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLoaderPlateBlowing->EditText = L"";
			this->lblLoaderPlateBlowing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLoaderPlateBlowing->Location = System::Drawing::Point(991, 65);
			this->lblLoaderPlateBlowing->Margin = System::Windows::Forms::Padding(5);
			this->lblLoaderPlateBlowing->Name = L"lblLoaderPlateBlowing";
			this->lblLoaderPlateBlowing->Offset = static_cast<System::UInt32>(0);
			this->lblLoaderPlateBlowing->Size = System::Drawing::Size(251, 50);
			this->lblLoaderPlateBlowing->TabIndex = 125;
			this->lblLoaderPlateBlowing->Tag = L"1";
			this->lblLoaderPlateBlowing->Text = L"0";
			this->lblLoaderPlateBlowing->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLoaderPlateBlowing->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblTurnOverBlowing
			// 
			this->lblTurnOverBlowing->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTurnOverBlowing->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblTurnOverBlowing->EditText = L"";
			this->lblTurnOverBlowing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTurnOverBlowing->Location = System::Drawing::Point(1252, 65);
			this->lblTurnOverBlowing->Margin = System::Windows::Forms::Padding(5);
			this->lblTurnOverBlowing->Name = L"lblTurnOverBlowing";
			this->lblTurnOverBlowing->Offset = static_cast<System::UInt32>(0);
			this->lblTurnOverBlowing->Size = System::Drawing::Size(254, 50);
			this->lblTurnOverBlowing->TabIndex = 126;
			this->lblTurnOverBlowing->Tag = L"1";
			this->lblTurnOverBlowing->Text = L"0";
			this->lblTurnOverBlowing->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblTurnOverBlowing->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblTableWaitVacuumOk
			// 
			this->lblTableWaitVacuumOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTableWaitVacuumOk->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblTableWaitVacuumOk->EditText = L"";
			this->lblTableWaitVacuumOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTableWaitVacuumOk->Location = System::Drawing::Point(469, 125);
			this->lblTableWaitVacuumOk->Margin = System::Windows::Forms::Padding(5);
			this->lblTableWaitVacuumOk->Name = L"lblTableWaitVacuumOk";
			this->lblTableWaitVacuumOk->Offset = static_cast<System::UInt32>(0);
			this->lblTableWaitVacuumOk->Size = System::Drawing::Size(251, 50);
			this->lblTableWaitVacuumOk->TabIndex = 127;
			this->lblTableWaitVacuumOk->Tag = L"1";
			this->lblTableWaitVacuumOk->Text = L"0";
			this->lblTableWaitVacuumOk->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblTableWaitVacuumOk->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblLoaderHeadWaitVacuumOk
			// 
			this->lblLoaderHeadWaitVacuumOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLoaderHeadWaitVacuumOk->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLoaderHeadWaitVacuumOk->EditText = L"";
			this->lblLoaderHeadWaitVacuumOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLoaderHeadWaitVacuumOk->Location = System::Drawing::Point(730, 125);
			this->lblLoaderHeadWaitVacuumOk->Margin = System::Windows::Forms::Padding(5);
			this->lblLoaderHeadWaitVacuumOk->Name = L"lblLoaderHeadWaitVacuumOk";
			this->lblLoaderHeadWaitVacuumOk->Offset = static_cast<System::UInt32>(0);
			this->lblLoaderHeadWaitVacuumOk->Size = System::Drawing::Size(251, 50);
			this->lblLoaderHeadWaitVacuumOk->TabIndex = 128;
			this->lblLoaderHeadWaitVacuumOk->Tag = L"1";
			this->lblLoaderHeadWaitVacuumOk->Text = L"0";
			this->lblLoaderHeadWaitVacuumOk->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLoaderHeadWaitVacuumOk->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblLoaderPlateWaitVacuumOk
			// 
			this->lblLoaderPlateWaitVacuumOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLoaderPlateWaitVacuumOk->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLoaderPlateWaitVacuumOk->EditText = L"";
			this->lblLoaderPlateWaitVacuumOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLoaderPlateWaitVacuumOk->Location = System::Drawing::Point(991, 125);
			this->lblLoaderPlateWaitVacuumOk->Margin = System::Windows::Forms::Padding(5);
			this->lblLoaderPlateWaitVacuumOk->Name = L"lblLoaderPlateWaitVacuumOk";
			this->lblLoaderPlateWaitVacuumOk->Offset = static_cast<System::UInt32>(0);
			this->lblLoaderPlateWaitVacuumOk->Size = System::Drawing::Size(251, 50);
			this->lblLoaderPlateWaitVacuumOk->TabIndex = 129;
			this->lblLoaderPlateWaitVacuumOk->Tag = L"1";
			this->lblLoaderPlateWaitVacuumOk->Text = L"0";
			this->lblLoaderPlateWaitVacuumOk->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLoaderPlateWaitVacuumOk->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblTurnOverWaitVacuumOk
			// 
			this->lblTurnOverWaitVacuumOk->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTurnOverWaitVacuumOk->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblTurnOverWaitVacuumOk->EditText = L"";
			this->lblTurnOverWaitVacuumOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTurnOverWaitVacuumOk->Location = System::Drawing::Point(1252, 125);
			this->lblTurnOverWaitVacuumOk->Margin = System::Windows::Forms::Padding(5);
			this->lblTurnOverWaitVacuumOk->Name = L"lblTurnOverWaitVacuumOk";
			this->lblTurnOverWaitVacuumOk->Offset = static_cast<System::UInt32>(0);
			this->lblTurnOverWaitVacuumOk->Size = System::Drawing::Size(254, 50);
			this->lblTurnOverWaitVacuumOk->TabIndex = 130;
			this->lblTurnOverWaitVacuumOk->Tag = L"1";
			this->lblTurnOverWaitVacuumOk->Text = L"0";
			this->lblTurnOverWaitVacuumOk->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblTurnOverWaitVacuumOk->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblTableErrorDelay
			// 
			this->lblTableErrorDelay->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTableErrorDelay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblTableErrorDelay->EditText = L"";
			this->lblTableErrorDelay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTableErrorDelay->Location = System::Drawing::Point(469, 185);
			this->lblTableErrorDelay->Margin = System::Windows::Forms::Padding(5);
			this->lblTableErrorDelay->Name = L"lblTableErrorDelay";
			this->lblTableErrorDelay->Offset = static_cast<System::UInt32>(0);
			this->lblTableErrorDelay->Size = System::Drawing::Size(251, 50);
			this->lblTableErrorDelay->TabIndex = 131;
			this->lblTableErrorDelay->Tag = L"1";
			this->lblTableErrorDelay->Text = L"0";
			this->lblTableErrorDelay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblTableErrorDelay->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblLoaderHeadErrorDelay
			// 
			this->lblLoaderHeadErrorDelay->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLoaderHeadErrorDelay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLoaderHeadErrorDelay->EditText = L"";
			this->lblLoaderHeadErrorDelay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLoaderHeadErrorDelay->Location = System::Drawing::Point(730, 185);
			this->lblLoaderHeadErrorDelay->Margin = System::Windows::Forms::Padding(5);
			this->lblLoaderHeadErrorDelay->Name = L"lblLoaderHeadErrorDelay";
			this->lblLoaderHeadErrorDelay->Offset = static_cast<System::UInt32>(0);
			this->lblLoaderHeadErrorDelay->Size = System::Drawing::Size(251, 50);
			this->lblLoaderHeadErrorDelay->TabIndex = 132;
			this->lblLoaderHeadErrorDelay->Tag = L"1";
			this->lblLoaderHeadErrorDelay->Text = L"0";
			this->lblLoaderHeadErrorDelay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLoaderHeadErrorDelay->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblLoaderPlateErrorDelay
			// 
			this->lblLoaderPlateErrorDelay->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLoaderPlateErrorDelay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLoaderPlateErrorDelay->EditText = L"";
			this->lblLoaderPlateErrorDelay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLoaderPlateErrorDelay->Location = System::Drawing::Point(991, 185);
			this->lblLoaderPlateErrorDelay->Margin = System::Windows::Forms::Padding(5);
			this->lblLoaderPlateErrorDelay->Name = L"lblLoaderPlateErrorDelay";
			this->lblLoaderPlateErrorDelay->Offset = static_cast<System::UInt32>(0);
			this->lblLoaderPlateErrorDelay->Size = System::Drawing::Size(251, 50);
			this->lblLoaderPlateErrorDelay->TabIndex = 133;
			this->lblLoaderPlateErrorDelay->Tag = L"1";
			this->lblLoaderPlateErrorDelay->Text = L"0";
			this->lblLoaderPlateErrorDelay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLoaderPlateErrorDelay->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblTurnOverErrorDelay
			// 
			this->lblTurnOverErrorDelay->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTurnOverErrorDelay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblTurnOverErrorDelay->EditText = L"";
			this->lblTurnOverErrorDelay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblTurnOverErrorDelay->Location = System::Drawing::Point(1252, 185);
			this->lblTurnOverErrorDelay->Margin = System::Windows::Forms::Padding(5);
			this->lblTurnOverErrorDelay->Name = L"lblTurnOverErrorDelay";
			this->lblTurnOverErrorDelay->Offset = static_cast<System::UInt32>(0);
			this->lblTurnOverErrorDelay->Size = System::Drawing::Size(254, 50);
			this->lblTurnOverErrorDelay->TabIndex = 134;
			this->lblTurnOverErrorDelay->Tag = L"1";
			this->lblTurnOverErrorDelay->Text = L"0";
			this->lblTurnOverErrorDelay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblTurnOverErrorDelay->Click += gcnew System::EventHandler(this, &VacuumSettingsScreen::lbl_Click);
			// 
			// lblPartialTakeTime
			// 
			this->lblPartialTakeTime->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblPartialTakeTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPartialTakeTime->Location = System::Drawing::Point(3, 243);
			this->lblPartialTakeTime->Margin = System::Windows::Forms::Padding(3);
			this->lblPartialTakeTime->Name = L"lblPartialTakeTime";
			this->lblPartialTakeTime->Size = System::Drawing::Size(458, 54);
			this->lblPartialTakeTime->TabIndex = 135;
			this->lblPartialTakeTime->Tag = L"1";
			this->lblPartialTakeTime->Text = L"PartialTakeTime";
			this->lblPartialTakeTime->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// VacuumSettingsScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"VacuumSettingsScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &VacuumSettingsScreen::VacuumSettingsScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void VacuumSettingsScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			tabPage1->Text = TUtilities::pS_LoadString(TextIndex::Vacuum);
			lblTable->Text = TUtilities::pS_LoadString(TextIndex::Table);
			lblLoaderHead->Text = TUtilities::pS_LoadString(TextIndex::LoaderHead);
			lblLoaderPlate->Text = TUtilities::pS_LoadString(TextIndex::LoaderPlate);
			lblTurnOver->Text = TUtilities::pS_LoadString(TextIndex::Turnover);
			lblBlowing->Text = TUtilities::pS_LoadString(TextIndex::Blowing) + " [ms]";
			lblWaitVacuumOk->Text = TUtilities::pS_LoadString(TextIndex::WaitVacuumOk) + " [ms]";
			lblErrorDelay->Text = TUtilities::pS_LoadString(TextIndex::VacuumErrorDelay) + " [ms]";
			lblPartialTakeTime->Text = TUtilities::pS_LoadString(TextIndex::PartialTakeTime) + " [ms]";

			lblTableBlowing->EditText = lblBlowing->Text + " (" + lblTable->Text + ")";
			lblTableWaitVacuumOk->EditText = lblWaitVacuumOk->Text + " (" + lblTable->Text + ")";
			lblTableErrorDelay->EditText = lblErrorDelay->Text + " (" + lblTable->Text + ")";
			lblTablePartialTakeTime->EditText = lblPartialTakeTime->Text + " (" + lblTable->Text + ")";

			lblLoaderHeadBlowing->EditText = lblBlowing->Text + " (" + lblLoaderHead->Text + ")";
			lblLoaderHeadWaitVacuumOk->EditText = lblWaitVacuumOk->Text + " (" + lblLoaderHead->Text + ")";
			lblLoaderHeadErrorDelay->EditText = lblErrorDelay->Text + " (" + lblLoaderHead->Text + ")";

			lblLoaderPlateBlowing->EditText = lblBlowing->Text + " (" + lblLoaderPlate->Text + ")";
			lblLoaderPlateWaitVacuumOk->EditText = lblWaitVacuumOk->Text + " (" + lblLoaderPlate->Text + ")";
			lblLoaderPlateErrorDelay->EditText = lblErrorDelay->Text + " (" + lblLoaderPlate->Text + ")";

			lblTurnOverBlowing->EditText = lblBlowing->Text + " (" + lblTurnOver->Text + ")";
			lblTurnOverWaitVacuumOk->EditText = lblWaitVacuumOk->Text + " (" + lblTurnOver->Text + ")";
			lblTurnOverErrorDelay->EditText = lblErrorDelay->Text + " (" + lblTurnOver->Text + ")";
		 }
	void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
private: System::Void lbl_Click(System::Object^  sender, System::EventArgs^  e) {
	LabelOffset^ lbl = (LabelOffset^)sender;
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lbl->EditText, double::Parse(lbl->Text), 0, 5000, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(lbl->EditText + L" : = " + Keypad->Value.ToString());
		WriteTCManOffsetData(lbl->Offset, (TC_INT)Keypad->Value);
	}
}
};
}


