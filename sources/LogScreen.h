#pragma once

#include "TLogger.h"
#include "TUtilities.h"

namespace Projet1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de LogScreen
	/// </summary>
	public ref class LogScreen : public System::Windows::Forms::Form
	{
	public:
		LogScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			AlarmAppTime->HeaderCell->Style->Alignment = DataGridViewContentAlignment::MiddleCenter;
			AlarmDisTime->HeaderCell->Style->Alignment = DataGridViewContentAlignment::MiddleCenter;
			AlarmUser->HeaderCell->Style->Alignment = DataGridViewContentAlignment::MiddleCenter;
			AlarmAppTime->DataPropertyName = "AppearanceTime";
			AlarmDisTime->DataPropertyName = "DisappearanceTime";
			AlarmUser->DataPropertyName = "UserName";
			AlarmMessage->DataPropertyName = "Message";
			dgvLog->AutoGenerateColumns = false;
			dgvLog->DataSource = TLogger::GetLog();
			
			TLogger::LogUpdated += gcnew System::EventHandler(this, &LogScreen::OnLogUpdated);
			OnLogUpdated(nullptr, EventArgs::Empty);
		}
	// Our specific functions
	public:
		void Reload(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~LogScreen()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::DataGridView^  dgvLog;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AlarmAppTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AlarmDisTime;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AlarmUser;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AlarmMessage;
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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->dgvLog = (gcnew System::Windows::Forms::DataGridView());
			this->AlarmAppTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->AlarmDisTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->AlarmUser = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->AlarmMessage = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvLog))->BeginInit();
			this->SuspendLayout();
			// 
			// dgvLog
			// 
			this->dgvLog->AllowUserToAddRows = false;
			this->dgvLog->AllowUserToDeleteRows = false;
			this->dgvLog->AllowUserToResizeColumns = false;
			this->dgvLog->AllowUserToResizeRows = false;
			this->dgvLog->BackgroundColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::LightGray;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::Color::LightGray;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvLog->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dgvLog->ColumnHeadersHeight = 60;
			this->dgvLog->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->dgvLog->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->AlarmAppTime,
					this->AlarmDisTime, this->AlarmUser, this->AlarmMessage
			});
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvLog->DefaultCellStyle = dataGridViewCellStyle6;
			this->dgvLog->EnableHeadersVisualStyles = false;
			this->dgvLog->Location = System::Drawing::Point(20, 20);
			this->dgvLog->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->dgvLog->MultiSelect = false;
			this->dgvLog->Name = L"dgvLog";
			this->dgvLog->ReadOnly = true;
			this->dgvLog->RowHeadersVisible = false;
			this->dgvLog->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dgvLog->RowTemplate->Height = 33;
			this->dgvLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dgvLog->ShowCellErrors = false;
			this->dgvLog->ShowCellToolTips = false;
			this->dgvLog->ShowEditingIcon = false;
			this->dgvLog->ShowRowErrors = false;
			this->dgvLog->Size = System::Drawing::Size(1538, 855);
			this->dgvLog->TabIndex = 1;
			this->dgvLog->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &LogScreen::dgvLog_CellContentClick);
			// 
			// AlarmAppTime
			// 
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->AlarmAppTime->DefaultCellStyle = dataGridViewCellStyle2;
			this->AlarmAppTime->HeaderText = L"";
			this->AlarmAppTime->Name = L"AlarmAppTime";
			this->AlarmAppTime->ReadOnly = true;
			this->AlarmAppTime->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->AlarmAppTime->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->AlarmAppTime->Width = 255;
			// 
			// AlarmDisTime
			// 
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->AlarmDisTime->DefaultCellStyle = dataGridViewCellStyle3;
			this->AlarmDisTime->HeaderText = L"";
			this->AlarmDisTime->Name = L"AlarmDisTime";
			this->AlarmDisTime->ReadOnly = true;
			this->AlarmDisTime->Width = 255;
			// 
			// AlarmUser
			// 
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->AlarmUser->DefaultCellStyle = dataGridViewCellStyle4;
			this->AlarmUser->HeaderText = L"";
			this->AlarmUser->Name = L"AlarmUser";
			this->AlarmUser->ReadOnly = true;
			this->AlarmUser->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->AlarmUser->Width = 225;
			// 
			// AlarmMessage
			// 
			this->AlarmMessage->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			this->AlarmMessage->DefaultCellStyle = dataGridViewCellStyle5;
			this->AlarmMessage->HeaderText = L"";
			this->AlarmMessage->Name = L"AlarmMessage";
			this->AlarmMessage->ReadOnly = true;
			this->AlarmMessage->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->AlarmMessage->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// LogScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->dgvLog);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"LogScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"LogScreen";
			this->VisibleChanged += gcnew System::EventHandler(this, &LogScreen::LogScreen_VisibleChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvLog))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void dgvLog_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 }
private: System::Void LogScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			AlarmAppTime->HeaderText = TUtilities::pS_LoadString(TextIndex::Apparition);
			AlarmDisTime->HeaderText = TUtilities::pS_LoadString(TextIndex::Disparition);
			AlarmUser->HeaderText = TUtilities::pS_LoadString(TextIndex::User);
			AlarmMessage->HeaderText = TUtilities::pS_LoadString(TextIndex::Message);
		 }
		 void OnLogUpdated(System::Object ^sender, System::EventArgs ^e);
};
}


