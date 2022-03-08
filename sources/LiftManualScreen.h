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
	public ref class LiftManualScreen : public System::Windows::Forms::Form
	{
	public:
		LiftManualScreen(void) : LiftManualScreen(false)
		{
		}

		LiftManualScreen(bool IsGiver)
		{
			m_bIsGiver = IsGiver;
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_Drive = gcnew DriveComponent(this->gbAxis);

			pT_Drive->UsePosition(0, TUtilities::pS_LoadString(TextIndex::Loader));
			pT_Drive->UsePosition(1, TUtilities::pS_LoadString(TextIndex::Empty));
			pT_Drive->UsePosition(2, TUtilities::pS_LoadString(TextIndex::Full));
			pT_Drive->UsePosition(3, TUtilities::pS_LoadString(TextIndex::Plate));
			if (m_bIsGiver)
			{
				pT_Drive->SetDrivePosData(0, GetTCManualOffset(s_Lift1Manual.ML_AxisLoadPos));
				pT_Drive->SetDrivePosData(1, GetTCManualOffset(s_Lift1Manual.ML_AxisEmptyPos));
				pT_Drive->SetDrivePosData(2, GetTCManualOffset(s_Lift1Manual.ML_AxisFullPos));
				pT_Drive->SetDrivePosData(3, GetTCManualOffset(s_Lift1Manual.ML_AxisZOffset));
				pT_Drive->SetDriveData(TUtilities::pS_LoadString(TextIndex::LeftLift), GetTCManualOffset(s_Lift1Manual.ML_Axis), L"");
			}
			else
			{
				pT_Drive->SetDrivePosData(0, GetTCManualOffset(s_Lift2Manual.ML_AxisLoadPos));
				pT_Drive->SetDrivePosData(1, GetTCManualOffset(s_Lift2Manual.ML_AxisEmptyPos));
				pT_Drive->SetDrivePosData(2, GetTCManualOffset(s_Lift2Manual.ML_AxisFullPos));
				pT_Drive->SetDrivePosData(3, GetTCManualOffset(s_Lift2Manual.ML_AxisZOffset));
				pT_Drive->SetDriveData(TUtilities::pS_LoadString(TextIndex::RightLift), GetTCManualOffset(s_Lift2Manual.ML_Axis), L"");
			}
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::LiftManualScreen::OnUserLevelChanged);
		}

	private:	bool bReloadParams;
	private:	bool m_bIsGiver;
	private: System::Windows::Forms::Label^  lblDrawerInPos;
	private: MondemaComponents::Led^  ledDrawerInPos;
	private: System::Windows::Forms::Label^  lblPlateInPos;
	private: MondemaComponents::Led^  ledPlateInPos;

	private: System::Windows::Forms::Label^  lblValuePlatePos;
	private: System::Windows::Forms::Label^  lblPlatePos;
	private: System::Windows::Forms::Label^  lblMoveToPlateVision;
	private: System::Windows::Forms::Button^  btnMoveToPlateVision;
	private: System::Windows::Forms::Label^  lblLockPlate;
	private: System::Windows::Forms::Label^  lblLockDrawer;







	private: System::Windows::Forms::CheckBox^  btnLockPlate;
	private: System::Windows::Forms::CheckBox^  btnUnlockPlate;
	private: System::Windows::Forms::CheckBox^  btnUnlockDrawer;



	private: System::Windows::Forms::CheckBox^  btnLockDrawer;

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
		~LiftManualScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::GroupBox^  gbAxis;
	private: System::Windows::Forms::Label^  lblMoveToPlate;
	private: System::Windows::Forms::Button^  btnMoveToPlate;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LiftManualScreen::typeid));
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->btnLockPlate = (gcnew System::Windows::Forms::CheckBox());
			this->btnUnlockPlate = (gcnew System::Windows::Forms::CheckBox());
			this->lblLockPlate = (gcnew System::Windows::Forms::Label());
			this->btnUnlockDrawer = (gcnew System::Windows::Forms::CheckBox());
			this->btnLockDrawer = (gcnew System::Windows::Forms::CheckBox());
			this->lblLockDrawer = (gcnew System::Windows::Forms::Label());
			this->lblMoveToPlateVision = (gcnew System::Windows::Forms::Label());
			this->btnMoveToPlateVision = (gcnew System::Windows::Forms::Button());
			this->lblValuePlatePos = (gcnew System::Windows::Forms::Label());
			this->lblPlatePos = (gcnew System::Windows::Forms::Label());
			this->lblPlateInPos = (gcnew System::Windows::Forms::Label());
			this->ledPlateInPos = (gcnew MondemaComponents::Led());
			this->lblDrawerInPos = (gcnew System::Windows::Forms::Label());
			this->ledDrawerInPos = (gcnew MondemaComponents::Led());
			this->lblMoveToPlate = (gcnew System::Windows::Forms::Label());
			this->btnMoveToPlate = (gcnew System::Windows::Forms::Button());
			this->gbAxis = (gcnew System::Windows::Forms::GroupBox());
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
			this->tabPage1->Controls->Add(this->btnLockPlate);
			this->tabPage1->Controls->Add(this->btnUnlockPlate);
			this->tabPage1->Controls->Add(this->lblLockPlate);
			this->tabPage1->Controls->Add(this->btnUnlockDrawer);
			this->tabPage1->Controls->Add(this->btnLockDrawer);
			this->tabPage1->Controls->Add(this->lblLockDrawer);
			this->tabPage1->Controls->Add(this->lblMoveToPlateVision);
			this->tabPage1->Controls->Add(this->btnMoveToPlateVision);
			this->tabPage1->Controls->Add(this->lblValuePlatePos);
			this->tabPage1->Controls->Add(this->lblPlatePos);
			this->tabPage1->Controls->Add(this->lblPlateInPos);
			this->tabPage1->Controls->Add(this->ledPlateInPos);
			this->tabPage1->Controls->Add(this->lblDrawerInPos);
			this->tabPage1->Controls->Add(this->ledDrawerInPos);
			this->tabPage1->Controls->Add(this->lblMoveToPlate);
			this->tabPage1->Controls->Add(this->btnMoveToPlate);
			this->tabPage1->Controls->Add(this->gbAxis);
			this->tabPage1->Location = System::Drawing::Point(4, 49);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1570, 842);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// btnLockPlate
			// 
			this->btnLockPlate->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnLockPlate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLockPlate->Location = System::Drawing::Point(413, 626);
			this->btnLockPlate->Name = L"btnLockPlate";
			this->btnLockPlate->Size = System::Drawing::Size(90, 90);
			this->btnLockPlate->TabIndex = 155;
			this->btnLockPlate->Tag = L"1";
			this->btnLockPlate->Text = L"ON";
			this->btnLockPlate->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLockPlate->UseVisualStyleBackColor = true;
			this->btnLockPlate->Click += gcnew System::EventHandler(this, &LiftManualScreen::btnLockPlate_Click);
			// 
			// btnUnlockPlate
			// 
			this->btnUnlockPlate->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnUnlockPlate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnUnlockPlate->Location = System::Drawing::Point(518, 626);
			this->btnUnlockPlate->Name = L"btnUnlockPlate";
			this->btnUnlockPlate->Size = System::Drawing::Size(90, 90);
			this->btnUnlockPlate->TabIndex = 156;
			this->btnUnlockPlate->Tag = L"1";
			this->btnUnlockPlate->Text = L"OFF";
			this->btnUnlockPlate->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnUnlockPlate->UseVisualStyleBackColor = true;
			this->btnUnlockPlate->Click += gcnew System::EventHandler(this, &LiftManualScreen::btnUnlockPlate_Click);
			// 
			// lblLockPlate
			// 
			this->lblLockPlate->AutoSize = true;
			this->lblLockPlate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLockPlate->Location = System::Drawing::Point(47, 655);
			this->lblLockPlate->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblLockPlate->Name = L"lblLockPlate";
			this->lblLockPlate->Size = System::Drawing::Size(128, 29);
			this->lblLockPlate->TabIndex = 152;
			this->lblLockPlate->Tag = L"1";
			this->lblLockPlate->Text = L"LockPlate";
			// 
			// btnUnlockDrawer
			// 
			this->btnUnlockDrawer->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnUnlockDrawer->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnUnlockDrawer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnUnlockDrawer->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnUnlockDrawer.Image")));
			this->btnUnlockDrawer->Location = System::Drawing::Point(518, 516);
			this->btnUnlockDrawer->Margin = System::Windows::Forms::Padding(2);
			this->btnUnlockDrawer->Name = L"btnUnlockDrawer";
			this->btnUnlockDrawer->Size = System::Drawing::Size(90, 90);
			this->btnUnlockDrawer->TabIndex = 151;
			this->btnUnlockDrawer->Tag = L"1";
			this->btnUnlockDrawer->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnUnlockDrawer->UseVisualStyleBackColor = false;
			this->btnUnlockDrawer->Click += gcnew System::EventHandler(this, &LiftManualScreen::btnUnlockDrawer_Click);
			// 
			// btnLockDrawer
			// 
			this->btnLockDrawer->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnLockDrawer->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnLockDrawer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLockDrawer->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnLockDrawer.Image")));
			this->btnLockDrawer->Location = System::Drawing::Point(413, 516);
			this->btnLockDrawer->Margin = System::Windows::Forms::Padding(2);
			this->btnLockDrawer->Name = L"btnLockDrawer";
			this->btnLockDrawer->Size = System::Drawing::Size(90, 90);
			this->btnLockDrawer->TabIndex = 150;
			this->btnLockDrawer->Tag = L"1";
			this->btnLockDrawer->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLockDrawer->UseVisualStyleBackColor = false;
			this->btnLockDrawer->Click += gcnew System::EventHandler(this, &LiftManualScreen::btnLockDrawer_Click);
			// 
			// lblLockDrawer
			// 
			this->lblLockDrawer->AutoSize = true;
			this->lblLockDrawer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLockDrawer->Location = System::Drawing::Point(47, 552);
			this->lblLockDrawer->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblLockDrawer->Name = L"lblLockDrawer";
			this->lblLockDrawer->Size = System::Drawing::Size(152, 29);
			this->lblLockDrawer->TabIndex = 149;
			this->lblLockDrawer->Tag = L"1";
			this->lblLockDrawer->Text = L"LockDrawer";
			// 
			// lblMoveToPlateVision
			// 
			this->lblMoveToPlateVision->AutoSize = true;
			this->lblMoveToPlateVision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveToPlateVision->Location = System::Drawing::Point(47, 210);
			this->lblMoveToPlateVision->Name = L"lblMoveToPlateVision";
			this->lblMoveToPlateVision->Size = System::Drawing::Size(240, 29);
			this->lblMoveToPlateVision->TabIndex = 148;
			this->lblMoveToPlateVision->Tag = L"2";
			this->lblMoveToPlateVision->Text = L"MoveToPlateVision";
			// 
			// btnMoveToPlateVision
			// 
			this->btnMoveToPlateVision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMoveToPlateVision->Location = System::Drawing::Point(518, 182);
			this->btnMoveToPlateVision->Name = L"btnMoveToPlateVision";
			this->btnMoveToPlateVision->Size = System::Drawing::Size(90, 90);
			this->btnMoveToPlateVision->TabIndex = 147;
			this->btnMoveToPlateVision->Tag = L"2";
			this->btnMoveToPlateVision->Text = L"Go";
			this->btnMoveToPlateVision->UseVisualStyleBackColor = true;
			this->btnMoveToPlateVision->Click += gcnew System::EventHandler(this, &LiftManualScreen::btnMoveToPlateVision_Click);
			// 
			// lblValuePlatePos
			// 
			this->lblValuePlatePos->AutoSize = true;
			this->lblValuePlatePos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblValuePlatePos->Location = System::Drawing::Point(408, 308);
			this->lblValuePlatePos->Name = L"lblValuePlatePos";
			this->lblValuePlatePos->Size = System::Drawing::Size(48, 29);
			this->lblValuePlatePos->TabIndex = 145;
			this->lblValuePlatePos->Tag = L"1";
			this->lblValuePlatePos->Text = L"0.0";
			// 
			// lblPlatePos
			// 
			this->lblPlatePos->AutoSize = true;
			this->lblPlatePos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPlatePos->Location = System::Drawing::Point(47, 308);
			this->lblPlatePos->Name = L"lblPlatePos";
			this->lblPlatePos->Size = System::Drawing::Size(168, 29);
			this->lblPlatePos->TabIndex = 144;
			this->lblPlatePos->Tag = L"1";
			this->lblPlatePos->Text = L"PlatePosition";
			// 
			// lblPlateInPos
			// 
			this->lblPlateInPos->AutoSize = true;
			this->lblPlateInPos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPlateInPos->Location = System::Drawing::Point(47, 408);
			this->lblPlateInPos->Name = L"lblPlateInPos";
			this->lblPlateInPos->Size = System::Drawing::Size(139, 29);
			this->lblPlateInPos->TabIndex = 115;
			this->lblPlateInPos->Tag = L"1";
			this->lblPlateInPos->Text = L"PlateInPos";
			// 
			// ledPlateInPos
			// 
			this->ledPlateInPos->Location = System::Drawing::Point(411, 402);
			this->ledPlateInPos->Margin = System::Windows::Forms::Padding(8, 9, 8, 9);
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
			this->lblDrawerInPos->Location = System::Drawing::Point(47, 358);
			this->lblDrawerInPos->Name = L"lblDrawerInPos";
			this->lblDrawerInPos->Size = System::Drawing::Size(163, 29);
			this->lblDrawerInPos->TabIndex = 113;
			this->lblDrawerInPos->Tag = L"1";
			this->lblDrawerInPos->Text = L"DrawerInPos";
			// 
			// ledDrawerInPos
			// 
			this->ledDrawerInPos->Location = System::Drawing::Point(411, 350);
			this->ledDrawerInPos->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->ledDrawerInPos->Name = L"ledDrawerInPos";
			this->ledDrawerInPos->Size = System::Drawing::Size(45, 45);
			this->ledDrawerInPos->TabIndex = 112;
			this->ledDrawerInPos->Tag = L"1";
			// 
			// lblMoveToPlate
			// 
			this->lblMoveToPlate->AutoSize = true;
			this->lblMoveToPlate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMoveToPlate->Location = System::Drawing::Point(47, 102);
			this->lblMoveToPlate->Name = L"lblMoveToPlate";
			this->lblMoveToPlate->Size = System::Drawing::Size(168, 29);
			this->lblMoveToPlate->TabIndex = 10;
			this->lblMoveToPlate->Tag = L"1";
			this->lblMoveToPlate->Text = L"MoveToPlate";
			// 
			// btnMoveToPlate
			// 
			this->btnMoveToPlate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMoveToPlate->Location = System::Drawing::Point(518, 74);
			this->btnMoveToPlate->Name = L"btnMoveToPlate";
			this->btnMoveToPlate->Size = System::Drawing::Size(90, 90);
			this->btnMoveToPlate->TabIndex = 2;
			this->btnMoveToPlate->Tag = L"1";
			this->btnMoveToPlate->Text = L"Go";
			this->btnMoveToPlate->UseVisualStyleBackColor = true;
			this->btnMoveToPlate->Click += gcnew System::EventHandler(this, &LiftManualScreen::btnMoveToPlate_Click);
			// 
			// gbAxis
			// 
			this->gbAxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbAxis->Location = System::Drawing::Point(771, 24);
			this->gbAxis->Name = L"gbAxis";
			this->gbAxis->Size = System::Drawing::Size(728, 600);
			this->gbAxis->TabIndex = 96;
			this->gbAxis->TabStop = false;
			this->gbAxis->Tag = L"2";
			// 
			// LiftManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"LiftManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->VisibleChanged += gcnew System::EventHandler(this, &LiftManualScreen::LiftManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void ShowOsk_Click(System::Object^  sender, System::EventArgs^  e) {
		TUtilities::ShowOSK();
	}

private: System::Void btnMoveToPlate_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::NextStep));
			if (m_bIsGiver)
				SetTCManData(s_Lift1Manual.ML_MoveToPlate.MB_Activate);
			else
				SetTCManData(s_Lift2Manual.ML_MoveToPlate.MB_Activate);
		 }
	private: System::Void LiftManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			pT_Drive->ReloadComponent();
			if (m_bIsGiver)
			{
				tabPage1->Text = TUtilities::pS_LoadString(TextIndex::LeftLift);
				pT_Drive->SetDriveName(TUtilities::pS_LoadString(TextIndex::LeftLift), L"");
			}
			else
			{
				tabPage1->Text = TUtilities::pS_LoadString(TextIndex::RightLift);
				pT_Drive->SetDriveName(TUtilities::pS_LoadString(TextIndex::RightLift), L"");
			}
			lblDrawerInPos->Text = TUtilities::pS_LoadString(TextIndex::DrawerInPos);
			lblMoveToPlate->Text = TUtilities::pS_LoadString(TextIndex::MoveToPlate);
			lblPlateInPos->Text = TUtilities::pS_LoadString(TextIndex::PlateInPos);
			lblMoveToPlateVision->Text = TUtilities::pS_LoadString(TextIndex::MoveToPlateVision);
			lblPlatePos->Text = TUtilities::pS_LoadString(TextIndex::PlatePosition) + " [mm]";
			lblLockPlate->Text = TUtilities::pS_LoadString(TextIndex::LockPlate);
			lblLockDrawer->Text = TUtilities::pS_LoadString(TextIndex::LockDrawer);

			gbAxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::Axis) + L"  ";
			bReloadParams = true;
		 }
private: System::Void btnMoveToPlateVision_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::NextStep));
	if (m_bIsGiver)
		SetTCManData(s_Lift1Manual.ML_MoveToPlateVision.MB_Activate);
	else
		SetTCManData(s_Lift2Manual.ML_MoveToPlateVision.MB_Activate);
}
		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
private: System::Void btnLockPlate_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::LockPlate) + "ON");
	if (m_bIsGiver)
		SetTCManData(s_Lift1Manual.ML_LockPlate.MB_Activate);
	else
		SetTCManData(s_Lift2Manual.ML_LockPlate.MB_Activate);
}
private: System::Void btnUnlockPlate_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::LockPlate) + "OFF");
	if (m_bIsGiver)
		ClearTCManData(s_Lift1Manual.ML_LockPlate.MB_Activate);
	else
		ClearTCManData(s_Lift2Manual.ML_LockPlate.MB_Activate);
}
private: System::Void btnLockDrawer_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::LockDrawer) + "ON");
	if (m_bIsGiver)
		SetTCManData(s_Lift1Manual.ML_LockDrawer.MB_Activate);
	else
		SetTCManData(s_Lift2Manual.ML_LockDrawer.MB_Activate);
}
private: System::Void btnUnlockDrawer_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabPage1->Text + " : " + TUtilities::pS_LoadString(TextIndex::LockDrawer) + "OFF");
	if (m_bIsGiver)
		ClearTCManData(s_Lift1Manual.ML_LockDrawer.MB_Activate);
	else
		ClearTCManData(s_Lift2Manual.ML_LockDrawer.MB_Activate);
}
};
}

