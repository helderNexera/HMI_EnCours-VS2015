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
	public ref class CounterScreen : public System::Windows::Forms::Form
	{
	public:
		CounterScreen()
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::CounterScreen::OnUserLevelChanged);
		}
			 // Our specific functions
	public:
		void UpdateUI(void);
		void Reload(void) {}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~CounterScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TextBox^  tbRightSpindleUseTime;
	private: System::Windows::Forms::TextBox^  tbLeftSpindleUseTime;
	private: System::Windows::Forms::Label^  lblSpindleUseTime;
	private: System::Windows::Forms::TextBox^  tbRightMotorUseTime;
	private: System::Windows::Forms::Button^  btnResetMTBF;

	private: System::Windows::Forms::TextBox^  tbLeftMotorUseTime;
	private: System::Windows::Forms::Label^  lblMotorUseTime;
	private: System::Windows::Forms::TextBox^  tbPartProduced;

	private: System::Windows::Forms::Label^  lblPartProduced;
	private: System::Windows::Forms::TextBox^  tbVacuumUseTime;
	private: System::Windows::Forms::TextBox^  tbAspirationUseTime;
	private: System::Windows::Forms::Label^  lblVacuum;
	private: System::Windows::Forms::Label^  lblAspiration;
	private: System::Windows::Forms::TextBox^  tbMeanMTBF;
	private: System::Windows::Forms::Label^  lblMeanMTBF;
	private: System::Windows::Forms::TextBox^  tbInProdTime;
	private: System::Windows::Forms::Label^  lblInProdTime;
	private: System::Windows::Forms::TextBox^  tbMachineOnTime;
	private: System::Windows::Forms::Label^  lblMachineOnTime;
	private: System::Windows::Forms::Label^  lblRightSpindle;

	private: System::Windows::Forms::Label^  lblLeftSpindle;


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
			this->lblRightSpindle = (gcnew System::Windows::Forms::Label());
			this->lblLeftSpindle = (gcnew System::Windows::Forms::Label());
			this->tbInProdTime = (gcnew System::Windows::Forms::TextBox());
			this->lblInProdTime = (gcnew System::Windows::Forms::Label());
			this->tbMachineOnTime = (gcnew System::Windows::Forms::TextBox());
			this->lblMachineOnTime = (gcnew System::Windows::Forms::Label());
			this->tbMeanMTBF = (gcnew System::Windows::Forms::TextBox());
			this->lblMeanMTBF = (gcnew System::Windows::Forms::Label());
			this->tbPartProduced = (gcnew System::Windows::Forms::TextBox());
			this->lblPartProduced = (gcnew System::Windows::Forms::Label());
			this->tbVacuumUseTime = (gcnew System::Windows::Forms::TextBox());
			this->tbAspirationUseTime = (gcnew System::Windows::Forms::TextBox());
			this->lblVacuum = (gcnew System::Windows::Forms::Label());
			this->lblAspiration = (gcnew System::Windows::Forms::Label());
			this->tbRightSpindleUseTime = (gcnew System::Windows::Forms::TextBox());
			this->tbLeftSpindleUseTime = (gcnew System::Windows::Forms::TextBox());
			this->lblSpindleUseTime = (gcnew System::Windows::Forms::Label());
			this->tbRightMotorUseTime = (gcnew System::Windows::Forms::TextBox());
			this->btnResetMTBF = (gcnew System::Windows::Forms::Button());
			this->tbLeftMotorUseTime = (gcnew System::Windows::Forms::TextBox());
			this->lblMotorUseTime = (gcnew System::Windows::Forms::Label());
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
			this->tabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->lblRightSpindle);
			this->tabPage1->Controls->Add(this->lblLeftSpindle);
			this->tabPage1->Controls->Add(this->tbInProdTime);
			this->tabPage1->Controls->Add(this->lblInProdTime);
			this->tabPage1->Controls->Add(this->tbMachineOnTime);
			this->tabPage1->Controls->Add(this->lblMachineOnTime);
			this->tabPage1->Controls->Add(this->tbMeanMTBF);
			this->tabPage1->Controls->Add(this->lblMeanMTBF);
			this->tabPage1->Controls->Add(this->tbPartProduced);
			this->tabPage1->Controls->Add(this->lblPartProduced);
			this->tabPage1->Controls->Add(this->tbVacuumUseTime);
			this->tabPage1->Controls->Add(this->tbAspirationUseTime);
			this->tabPage1->Controls->Add(this->lblVacuum);
			this->tabPage1->Controls->Add(this->lblAspiration);
			this->tabPage1->Controls->Add(this->tbRightSpindleUseTime);
			this->tabPage1->Controls->Add(this->tbLeftSpindleUseTime);
			this->tabPage1->Controls->Add(this->lblSpindleUseTime);
			this->tabPage1->Controls->Add(this->tbRightMotorUseTime);
			this->tabPage1->Controls->Add(this->btnResetMTBF);
			this->tabPage1->Controls->Add(this->tbLeftMotorUseTime);
			this->tabPage1->Controls->Add(this->lblMotorUseTime);
			this->tabPage1->Location = System::Drawing::Point(4, 49);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1570, 842);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// lblRightSpindle
			// 
			this->lblRightSpindle->Location = System::Drawing::Point(558, 54);
			this->lblRightSpindle->Name = L"lblRightSpindle";
			this->lblRightSpindle->Size = System::Drawing::Size(162, 35);
			this->lblRightSpindle->TabIndex = 187;
			this->lblRightSpindle->Tag = L"1";
			this->lblRightSpindle->Text = L"RightSpindle";
			this->lblRightSpindle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLeftSpindle
			// 
			this->lblLeftSpindle->Location = System::Drawing::Point(387, 54);
			this->lblLeftSpindle->Name = L"lblLeftSpindle";
			this->lblLeftSpindle->Size = System::Drawing::Size(162, 35);
			this->lblLeftSpindle->TabIndex = 186;
			this->lblLeftSpindle->Tag = L"1";
			this->lblLeftSpindle->Text = L"LeftSpindle";
			this->lblLeftSpindle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tbInProdTime
			// 
			this->tbInProdTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbInProdTime->Location = System::Drawing::Point(476, 270);
			this->tbInProdTime->Name = L"tbInProdTime";
			this->tbInProdTime->ReadOnly = true;
			this->tbInProdTime->Size = System::Drawing::Size(162, 35);
			this->tbInProdTime->TabIndex = 184;
			this->tbInProdTime->Tag = L"1";
			this->tbInProdTime->Text = L"0";
			this->tbInProdTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblInProdTime
			// 
			this->lblInProdTime->AutoSize = true;
			this->lblInProdTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblInProdTime->Location = System::Drawing::Point(12, 274);
			this->lblInProdTime->Name = L"lblInProdTime";
			this->lblInProdTime->Size = System::Drawing::Size(150, 29);
			this->lblInProdTime->TabIndex = 185;
			this->lblInProdTime->Tag = L"1";
			this->lblInProdTime->Text = L"InProdTime";
			// 
			// tbMachineOnTime
			// 
			this->tbMachineOnTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbMachineOnTime->Location = System::Drawing::Point(476, 222);
			this->tbMachineOnTime->Name = L"tbMachineOnTime";
			this->tbMachineOnTime->ReadOnly = true;
			this->tbMachineOnTime->Size = System::Drawing::Size(162, 35);
			this->tbMachineOnTime->TabIndex = 182;
			this->tbMachineOnTime->Tag = L"1";
			this->tbMachineOnTime->Text = L"0";
			this->tbMachineOnTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblMachineOnTime
			// 
			this->lblMachineOnTime->AutoSize = true;
			this->lblMachineOnTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMachineOnTime->Location = System::Drawing::Point(12, 226);
			this->lblMachineOnTime->Name = L"lblMachineOnTime";
			this->lblMachineOnTime->Size = System::Drawing::Size(205, 29);
			this->lblMachineOnTime->TabIndex = 183;
			this->lblMachineOnTime->Tag = L"1";
			this->lblMachineOnTime->Text = L"MachineOnTime";
			// 
			// tbMeanMTBF
			// 
			this->tbMeanMTBF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbMeanMTBF->Location = System::Drawing::Point(476, 534);
			this->tbMeanMTBF->Name = L"tbMeanMTBF";
			this->tbMeanMTBF->ReadOnly = true;
			this->tbMeanMTBF->Size = System::Drawing::Size(162, 35);
			this->tbMeanMTBF->TabIndex = 181;
			this->tbMeanMTBF->Tag = L"1";
			this->tbMeanMTBF->Text = L"0";
			this->tbMeanMTBF->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblMeanMTBF
			// 
			this->lblMeanMTBF->AutoSize = true;
			this->lblMeanMTBF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMeanMTBF->Location = System::Drawing::Point(12, 537);
			this->lblMeanMTBF->Name = L"lblMeanMTBF";
			this->lblMeanMTBF->Size = System::Drawing::Size(148, 29);
			this->lblMeanMTBF->TabIndex = 180;
			this->lblMeanMTBF->Tag = L"1";
			this->lblMeanMTBF->Text = L"MeanMTBF";
			// 
			// tbPartProduced
			// 
			this->tbPartProduced->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbPartProduced->Location = System::Drawing::Point(476, 452);
			this->tbPartProduced->Name = L"tbPartProduced";
			this->tbPartProduced->ReadOnly = true;
			this->tbPartProduced->Size = System::Drawing::Size(162, 35);
			this->tbPartProduced->TabIndex = 179;
			this->tbPartProduced->Tag = L"1";
			this->tbPartProduced->Text = L"0";
			this->tbPartProduced->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblPartProduced
			// 
			this->lblPartProduced->AutoSize = true;
			this->lblPartProduced->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPartProduced->Location = System::Drawing::Point(12, 456);
			this->lblPartProduced->Name = L"lblPartProduced";
			this->lblPartProduced->Size = System::Drawing::Size(173, 29);
			this->lblPartProduced->TabIndex = 178;
			this->lblPartProduced->Tag = L"1";
			this->lblPartProduced->Text = L"PartProduced";
			// 
			// tbVacuumUseTime
			// 
			this->tbVacuumUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbVacuumUseTime->Location = System::Drawing::Point(476, 368);
			this->tbVacuumUseTime->Name = L"tbVacuumUseTime";
			this->tbVacuumUseTime->ReadOnly = true;
			this->tbVacuumUseTime->Size = System::Drawing::Size(162, 35);
			this->tbVacuumUseTime->TabIndex = 177;
			this->tbVacuumUseTime->Tag = L"1";
			this->tbVacuumUseTime->Text = L"0";
			this->tbVacuumUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tbAspirationUseTime
			// 
			this->tbAspirationUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbAspirationUseTime->Location = System::Drawing::Point(476, 320);
			this->tbAspirationUseTime->Name = L"tbAspirationUseTime";
			this->tbAspirationUseTime->ReadOnly = true;
			this->tbAspirationUseTime->Size = System::Drawing::Size(162, 35);
			this->tbAspirationUseTime->TabIndex = 176;
			this->tbAspirationUseTime->Tag = L"1";
			this->tbAspirationUseTime->Text = L"0";
			this->tbAspirationUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblVacuum
			// 
			this->lblVacuum->AutoSize = true;
			this->lblVacuum->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuum->Location = System::Drawing::Point(12, 372);
			this->lblVacuum->Name = L"lblVacuum";
			this->lblVacuum->Size = System::Drawing::Size(105, 29);
			this->lblVacuum->TabIndex = 173;
			this->lblVacuum->Tag = L"1";
			this->lblVacuum->Text = L"Vacuum";
			// 
			// lblAspiration
			// 
			this->lblAspiration->AutoSize = true;
			this->lblAspiration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAspiration->Location = System::Drawing::Point(12, 324);
			this->lblAspiration->Name = L"lblAspiration";
			this->lblAspiration->Size = System::Drawing::Size(130, 29);
			this->lblAspiration->TabIndex = 170;
			this->lblAspiration->Tag = L"1";
			this->lblAspiration->Text = L"Aspiration";
			// 
			// tbRightSpindleUseTime
			// 
			this->tbRightSpindleUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRightSpindleUseTime->Location = System::Drawing::Point(558, 140);
			this->tbRightSpindleUseTime->Name = L"tbRightSpindleUseTime";
			this->tbRightSpindleUseTime->ReadOnly = true;
			this->tbRightSpindleUseTime->Size = System::Drawing::Size(162, 35);
			this->tbRightSpindleUseTime->TabIndex = 169;
			this->tbRightSpindleUseTime->Tag = L"1";
			this->tbRightSpindleUseTime->Text = L"0";
			this->tbRightSpindleUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tbLeftSpindleUseTime
			// 
			this->tbLeftSpindleUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbLeftSpindleUseTime->Location = System::Drawing::Point(387, 140);
			this->tbLeftSpindleUseTime->Name = L"tbLeftSpindleUseTime";
			this->tbLeftSpindleUseTime->ReadOnly = true;
			this->tbLeftSpindleUseTime->Size = System::Drawing::Size(162, 35);
			this->tbLeftSpindleUseTime->TabIndex = 167;
			this->tbLeftSpindleUseTime->Tag = L"1";
			this->tbLeftSpindleUseTime->Text = L"0";
			this->tbLeftSpindleUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblSpindleUseTime
			// 
			this->lblSpindleUseTime->AutoSize = true;
			this->lblSpindleUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSpindleUseTime->Location = System::Drawing::Point(12, 145);
			this->lblSpindleUseTime->Name = L"lblSpindleUseTime";
			this->lblSpindleUseTime->Size = System::Drawing::Size(209, 29);
			this->lblSpindleUseTime->TabIndex = 168;
			this->lblSpindleUseTime->Tag = L"1";
			this->lblSpindleUseTime->Text = L"SpindleUseTime";
			// 
			// tbRightMotorUseTime
			// 
			this->tbRightMotorUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRightMotorUseTime->Location = System::Drawing::Point(558, 92);
			this->tbRightMotorUseTime->Name = L"tbRightMotorUseTime";
			this->tbRightMotorUseTime->ReadOnly = true;
			this->tbRightMotorUseTime->Size = System::Drawing::Size(162, 35);
			this->tbRightMotorUseTime->TabIndex = 165;
			this->tbRightMotorUseTime->Tag = L"1";
			this->tbRightMotorUseTime->Text = L"0";
			this->tbRightMotorUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// btnResetMTBF
			// 
			this->btnResetMTBF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnResetMTBF->Location = System::Drawing::Point(644, 534);
			this->btnResetMTBF->Name = L"btnResetMTBF";
			this->btnResetMTBF->Size = System::Drawing::Size(162, 35);
			this->btnResetMTBF->TabIndex = 164;
			this->btnResetMTBF->Tag = L"1";
			this->btnResetMTBF->Text = L"RESET";
			this->btnResetMTBF->UseVisualStyleBackColor = true;
			this->btnResetMTBF->Click += gcnew System::EventHandler(this, &CounterScreen::btnResetMTBF_Click);
			// 
			// tbLeftMotorUseTime
			// 
			this->tbLeftMotorUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbLeftMotorUseTime->Location = System::Drawing::Point(387, 92);
			this->tbLeftMotorUseTime->Name = L"tbLeftMotorUseTime";
			this->tbLeftMotorUseTime->ReadOnly = true;
			this->tbLeftMotorUseTime->Size = System::Drawing::Size(162, 35);
			this->tbLeftMotorUseTime->TabIndex = 162;
			this->tbLeftMotorUseTime->Tag = L"1";
			this->tbLeftMotorUseTime->Text = L"0";
			this->tbLeftMotorUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblMotorUseTime
			// 
			this->lblMotorUseTime->AutoSize = true;
			this->lblMotorUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMotorUseTime->Location = System::Drawing::Point(12, 97);
			this->lblMotorUseTime->Name = L"lblMotorUseTime";
			this->lblMotorUseTime->Size = System::Drawing::Size(186, 29);
			this->lblMotorUseTime->TabIndex = 163;
			this->lblMotorUseTime->Tag = L"1";
			this->lblMotorUseTime->Text = L"MotorUseTime";
			// 
			// CounterScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"CounterScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &CounterScreen::CounterScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void CounterScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			tabPage1->Text = TUtilities::pS_LoadString(TextIndex::Counter);
			lblMeanMTBF->Text = TUtilities::pS_LoadString(TextIndex::MTBF);
			lblMotorUseTime->Text = TUtilities::pS_LoadString(TextIndex::MotorUseTime) + " [h]";
			lblSpindleUseTime->Text = TUtilities::pS_LoadString(TextIndex::SpindleUseTime) + " [h]";
			lblAspiration->Text = TUtilities::pS_LoadString(TextIndex::Aspiration) + " [h]";
			lblVacuum->Text = TUtilities::pS_LoadString(TextIndex::Vacuum) + " [h]";
			lblPartProduced->Text = TUtilities::pS_LoadString(TextIndex::PartProduced) + " [-]";
			lblMachineOnTime->Text = TUtilities::pS_LoadString(TextIndex::MachineOnTime) + " [h]";
			lblInProdTime->Text = TUtilities::pS_LoadString(TextIndex::InProdTime) + " [h]";
			lblLeftSpindle->Text = TUtilities::pS_LoadString(TextIndex::LeftSpindle);
			lblRightSpindle->Text = TUtilities::pS_LoadString(TextIndex::RightSpindle);
	}
	void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
private: System::Void btnResetMTBF_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::MTBF));
	SetTCData(s_Counter.TC_ResetMTBF);
}
};
}


