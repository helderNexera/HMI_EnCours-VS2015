#pragma once

#include "global.h"
#include "TLogger.h"
#include "TUtilities.h"

namespace Projet1 {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Description résumée de AlarmScreen
	/// </summary>
	public ref class AlarmScreen : public System::Windows::Forms::Form
	{
	public:
		AlarmScreen(void)
		{
			pT_This = this;
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			// Load the alarms definition
			apS_AlarmText = TUtilities::LoadTranslation(C_APP_CONFIG_PATH + "alarms.csv");
			
			ab_AlarmWasOn = gcnew array<bool>(C_MAX_NB_OF_ERRORS);
			ab_AlarmIsOff = gcnew array<bool>(C_MAX_NB_OF_ERRORS);
			aT_AlarmAppearanceTime = gcnew array<DateTime>(C_MAX_NB_OF_ERRORS);
			ab_AlarmsStatus = gcnew array<bool>(C_MAX_NB_OF_ERRORS);

			AlarmTime->HeaderCell->Style->Alignment = DataGridViewContentAlignment::MiddleCenter;
			b_NoValidation = true;
		}
	// Our specific functions
	private:
		static AlarmScreen^ pT_This;
		int i_NbOfAlarms;
		Dictionary<String^, array<String^>^>^ apS_AlarmText;
		array<int>^ ai_AlarmID;
		array<bool>^ ab_AlarmWasOn;
		array<bool>^ ab_AlarmIsOff;
		array<DateTime>^ aT_AlarmAppearanceTime;
		array<bool>^ ab_AlarmsStatus;
		bool b_NoValidation;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AlarmTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AlarmMessage;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ForSorting;
			 static bool b_ForceRefresh;

		String^ pS_GetAlarm(int i_x_AlarmID);
	public:
		static String^ pS_GetLastAlarm(bool* pb_x_IsActive);
		void UpdateAlarmsTable(void);
		static void ResetAlarmList(void);
		void Reload(void);





	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~AlarmScreen()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;




	private: System::Windows::Forms::DataGridView^  dgvAlarmsList;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->dgvAlarmsList = (gcnew System::Windows::Forms::DataGridView());
			this->AlarmTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->AlarmMessage = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ForSorting = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvAlarmsList))->BeginInit();
			this->SuspendLayout();
			// 
			// dgvAlarmsList
			// 
			this->dgvAlarmsList->AllowUserToAddRows = false;
			this->dgvAlarmsList->AllowUserToDeleteRows = false;
			this->dgvAlarmsList->AllowUserToResizeColumns = false;
			this->dgvAlarmsList->AllowUserToResizeRows = false;
			this->dgvAlarmsList->BackgroundColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::LightGray;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::Color::LightGray;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvAlarmsList->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dgvAlarmsList->ColumnHeadersHeight = 60;
			this->dgvAlarmsList->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->dgvAlarmsList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->AlarmTime,
					this->AlarmMessage, this->ForSorting
			});
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvAlarmsList->DefaultCellStyle = dataGridViewCellStyle3;
			this->dgvAlarmsList->EnableHeadersVisualStyles = false;
			this->dgvAlarmsList->Location = System::Drawing::Point(20, 20);
			this->dgvAlarmsList->MultiSelect = false;
			this->dgvAlarmsList->Name = L"dgvAlarmsList";
			this->dgvAlarmsList->ReadOnly = true;
			this->dgvAlarmsList->RowHeadersVisible = false;
			this->dgvAlarmsList->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dgvAlarmsList->RowTemplate->Height = 33;
			this->dgvAlarmsList->ShowCellErrors = false;
			this->dgvAlarmsList->ShowCellToolTips = false;
			this->dgvAlarmsList->ShowEditingIcon = false;
			this->dgvAlarmsList->ShowRowErrors = false;
			this->dgvAlarmsList->Size = System::Drawing::Size(1538, 855);
			this->dgvAlarmsList->TabIndex = 0;
			// 
			// AlarmTime
			// 
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->AlarmTime->DefaultCellStyle = dataGridViewCellStyle2;
			this->AlarmTime->HeaderText = L"";
			this->AlarmTime->Name = L"AlarmTime";
			this->AlarmTime->ReadOnly = true;
			this->AlarmTime->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->AlarmTime->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::Programmatic;
			this->AlarmTime->Width = 300;
			// 
			// AlarmMessage
			// 
			this->AlarmMessage->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->AlarmMessage->HeaderText = L"";
			this->AlarmMessage->Name = L"AlarmMessage";
			this->AlarmMessage->ReadOnly = true;
			this->AlarmMessage->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			// 
			// ForSorting
			// 
			this->ForSorting->HeaderText = L"Column1";
			this->ForSorting->Name = L"ForSorting";
			this->ForSorting->ReadOnly = true;
			this->ForSorting->Visible = false;
			this->ForSorting->Width = 10;
			// 
			// AlarmScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->dgvAlarmsList);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"AlarmScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &AlarmScreen::AlarmScreen_VisibleChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvAlarmsList))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void AlarmScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
				// Reload language dependent texts
				this->AlarmTime->HeaderText = TUtilities::pS_LoadString(TextIndex::Apparition);
	 			this->AlarmMessage->HeaderText = TUtilities::pS_LoadString(TextIndex::Message);

			 }
};
}
