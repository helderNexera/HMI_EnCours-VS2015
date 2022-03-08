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
	public ref class RejectManualScreen : public System::Windows::Forms::Form
	{
	public:
		RejectManualScreen()
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::RejectManualScreen::OnUserLevelChanged);
		}

	private: System::Windows::Forms::Label^  lblDrawerInPos;
	private: MondemaComponents::Led^  ledDrawerInPos;
	private: System::Windows::Forms::Label^  lblPlateInPos;
	private: MondemaComponents::Led^  ledPlateInPos;
	public:

			 // Our specific functions
	private:
	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~RejectManualScreen()
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
			this->lblPlateInPos = (gcnew System::Windows::Forms::Label());
			this->ledPlateInPos = (gcnew MondemaComponents::Led());
			this->lblDrawerInPos = (gcnew System::Windows::Forms::Label());
			this->ledDrawerInPos = (gcnew MondemaComponents::Led());
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
			this->tabPage1->Controls->Add(this->lblPlateInPos);
			this->tabPage1->Controls->Add(this->ledPlateInPos);
			this->tabPage1->Controls->Add(this->lblDrawerInPos);
			this->tabPage1->Controls->Add(this->ledDrawerInPos);
			this->tabPage1->Location = System::Drawing::Point(6, 51);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1570, 857);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// lblPlateInPos
			// 
			this->lblPlateInPos->AutoSize = true;
			this->lblPlateInPos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPlateInPos->Location = System::Drawing::Point(9, 54);
			this->lblPlateInPos->Name = L"lblPlateInPos";
			this->lblPlateInPos->Size = System::Drawing::Size(144, 30);
			this->lblPlateInPos->TabIndex = 115;
			this->lblPlateInPos->Tag = L"1";
			this->lblPlateInPos->Text = L"PlateInPos";
			// 
			// ledPlateInPos
			// 
			this->ledPlateInPos->Location = System::Drawing::Point(323, 54);
			this->ledPlateInPos->Margin = System::Windows::Forms::Padding(8);
			this->ledPlateInPos->Name = L"ledPlateInPos";
			this->ledPlateInPos->Size = System::Drawing::Size(45, 45);
			this->ledPlateInPos->TabIndex = 114;
			this->ledPlateInPos->Tag = L"1";
			// 
			// lblDrawerInPos
			// 
			this->lblDrawerInPos->AutoSize = true;
			this->lblDrawerInPos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDrawerInPos->Location = System::Drawing::Point(9, 5);
			this->lblDrawerInPos->Name = L"lblDrawerInPos";
			this->lblDrawerInPos->Size = System::Drawing::Size(168, 30);
			this->lblDrawerInPos->TabIndex = 113;
			this->lblDrawerInPos->Tag = L"1";
			this->lblDrawerInPos->Text = L"DrawerInPos";
			// 
			// ledDrawerInPos
			// 
			this->ledDrawerInPos->Location = System::Drawing::Point(323, 5);
			this->ledDrawerInPos->Margin = System::Windows::Forms::Padding(5);
			this->ledDrawerInPos->Name = L"ledDrawerInPos";
			this->ledDrawerInPos->Size = System::Drawing::Size(45, 45);
			this->ledDrawerInPos->TabIndex = 112;
			this->ledDrawerInPos->Tag = L"1";
			// 
			// RejectManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"RejectManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &RejectManualScreen::RejectManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void ShowOsk_Click(System::Object^  sender, System::EventArgs^  e) {
		TUtilities::ShowOSK();
	}

	private: System::Void RejectManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			tabPage1->Text = TUtilities::pS_LoadString(TextIndex::Reject);
			lblDrawerInPos->Text = TUtilities::pS_LoadString(TextIndex::DrawerInPos);
			lblPlateInPos->Text = TUtilities::pS_LoadString(TextIndex::PlateInPos);
		 }
			 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
};
}


