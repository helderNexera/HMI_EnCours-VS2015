#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;
using namespace MondemaComponents;

#include "TTwincatInterface.h"
#include "TUtilities.h"
#include "MyMsgBox.h"
#include "TLogger.h"

namespace Projet1 {

	/// <summary>
	/// Description résumée de DriveComponent
	/// </summary>
	public ref class DriveComponent :  public System::ComponentModel::Component
	{
	private:
		String^ s_ComponentName;
		TC_MAN_DRIVE* pT_TCDrive;
		System::Windows::Forms::GroupBox ^pT_MyContainer;
		size_t DriveDataOffset;
		array<size_t>^ a_PositionDataOffset;
		array<size_t>^ a_CobDataOffset;
		bool b_UseSpecificButton;
	public:
		DriveComponent(System::Windows::Forms::GroupBox ^pT_x_Container)
		{
			/// <summary>
			/// Requis pour la prise en charge du Concepteur de composition de classes Windows.Forms
			/// </summary>

			s_ComponentName = gcnew String(L"");

			a_PositionDataOffset = gcnew array<size_t>(4);
			a_CobDataOffset = gcnew array<size_t>(4);
			a_lblPosName = gcnew array<System::Windows::Forms::Label ^>(4);
			a_cobAxisListPos = gcnew array<System::Windows::Forms::ComboBox ^>(4);
			a_lblAxisPos = gcnew array<System::Windows::Forms::Label ^>(4);
			a_btnAxisTeachPos = gcnew array<System::Windows::Forms::Button ^>(4);
			a_btnAxisMove2Pos = gcnew array<System::Windows::Forms::Button ^>(4);

			pT_MyContainer = pT_x_Container;
			InitializeComponent();


			this->btnaxisJogP->Tag = "1";
			this->btnaxisJogN->Tag = "1";
			for (int i = 0; i<4; i++)
			{
				this->a_cobAxisListPos[i]->Tag = "10";
				this->a_lblPosName[i]->Tag = "10";
				this->a_lblAxisPos[i]->Tag = "10";
				this->a_btnAxisMove2Pos[i]->Tag = "10";
				this->a_btnAxisTeachPos[i]->Tag = "10";
			}
			this->tbaxisJogStep->Tag = "1";
			this->btnAxisServo->Tag = "1";
			this->btnAxisHome->Tag = "2";
			this->btnAxisSpecific->Tag = "10";
			this->lblAxisCurrentPos->Tag = "1";
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::DriveComponent::OnUserLevelChanged);
		}

		void SetDriveData(String^ s_x_ComponentName, size_t x_DriveDataOffset)
		{
			SetDriveData(s_x_ComponentName, x_DriveDataOffset, "");
		}

		void SetDriveData(String^ s_x_ComponentName,size_t x_DriveDataOffset,String^ s_x_SpecificButton)
		{
			s_ComponentName = s_x_ComponentName;
			DriveDataOffset = x_DriveDataOffset;
			if (s_x_SpecificButton != L"")
			{
				b_UseSpecificButton = true;
				btnAxisSpecific->Text = s_x_SpecificButton;
				btnAxisSpecific->Tag = "1";
			}
			else
			{
				btnAxisSpecific->Tag = "10";
				b_UseSpecificButton = false;
			}
		}
		void UsePosition(int i_x_Position,String^ s_x_PostionName);
		void UsePosition(int i_x_Position,String^ s_x_PostionName,int i_x_MinValue,int i_x_MaxValue);
		void SetDrivePosData(int i_x_Position,size_t x_PositionDataOffset)
		{
			a_PositionDataOffset[i_x_Position] = x_PositionDataOffset;
		}
		void SetDrivePosData(int i_x_Position,size_t x_PositionDataOffset,size_t x_CobDataOffset)
		{
			a_PositionDataOffset[i_x_Position] = x_PositionDataOffset;
			a_CobDataOffset[i_x_Position] = x_CobDataOffset;
		}
		void UpdateUI(void);
		void ReloadComponent(void);
		void SetPositionName(int i_x_Position,String^ pS_x_PositionName);
		void SetDriveName(String^ pS_x_DriveName,String^ pS_x_SpecificName);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~DriveComponent()
		{
		}
	private:
		System::Windows::Forms::Button^  btnaxisJogP;
		System::Windows::Forms::Button^  btnaxisJogN;
		array<System::Windows::Forms::Label ^> ^a_lblPosName;
		array<System::Windows::Forms::ComboBox ^> ^a_cobAxisListPos;
		array<System::Windows::Forms::Label ^> ^a_lblAxisPos;
		array<System::Windows::Forms::Button ^> ^a_btnAxisTeachPos;
		array<System::Windows::Forms::Button ^> ^a_btnAxisMove2Pos;
		System::Windows::Forms::Label^  tbaxisJogStep;
		System::Windows::Forms::CheckBox^  btnAxisSpecific;
		System::Windows::Forms::CheckBox^  btnAxisServo;
		System::Windows::Forms::CheckBox^  btnAxisHome;
		System::Windows::Forms::Label^  lblAxisCurrentPos;
	private:

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			int i = 0;

			this->btnaxisJogP = (gcnew System::Windows::Forms::Button());
			this->btnaxisJogN = (gcnew System::Windows::Forms::Button());
			for (i=0;i<4;i++)
			{
				this->a_lblPosName[i] = gcnew System::Windows::Forms::Label();
				this->a_cobAxisListPos[i] = gcnew System::Windows::Forms::ComboBox();
				this->a_lblAxisPos[i] = gcnew System::Windows::Forms::Label();
				this->a_btnAxisMove2Pos[i] = gcnew System::Windows::Forms::Button();
				this->a_btnAxisTeachPos[i] = gcnew System::Windows::Forms::Button();
			}
			this->tbaxisJogStep = (gcnew System::Windows::Forms::Label());
			this->btnAxisServo = (gcnew System::Windows::Forms::CheckBox());
			this->btnAxisHome = (gcnew System::Windows::Forms::CheckBox());
			this->btnAxisSpecific = (gcnew System::Windows::Forms::CheckBox());
			this->lblAxisCurrentPos = (gcnew System::Windows::Forms::Label());

			// 
			// btnaxisJogP
			// 
			this->btnaxisJogP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnaxisJogP->Location = System::Drawing::Point(510, 48);
			this->btnaxisJogP->Name = L"btnaxisJogP";
			this->btnaxisJogP->Size = System::Drawing::Size(90, 90);
			this->btnaxisJogP->TabIndex = 38;
			this->btnaxisJogP->Text = L">>";
			this->btnaxisJogP->UseVisualStyleBackColor = true;
			this->btnaxisJogP->Click += gcnew System::EventHandler(this, &DriveComponent::btnaxisJogP_Click);
			pT_MyContainer->Controls->Add(this->btnaxisJogP);
			// 
			// btnaxisJogN
			// 
			this->btnaxisJogN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnaxisJogN->Location = System::Drawing::Point(260, 48);
			this->btnaxisJogN->Name = L"btnaxisJogN";
			this->btnaxisJogN->Size = System::Drawing::Size(90, 90);
			this->btnaxisJogN->TabIndex = 37;
			this->btnaxisJogN->Text = L"<<";
			this->btnaxisJogN->UseVisualStyleBackColor = true;
			this->btnaxisJogN->Click += gcnew System::EventHandler(this, &DriveComponent::btnaxisJogN_Click);
			pT_MyContainer->Controls->Add(this->btnaxisJogN);
			// 
			// btnYAxisMove2Pos
			// 
			for (i=0;i<4;i++)
			{
				this->a_btnAxisMove2Pos[i]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(0)));
				this->a_btnAxisMove2Pos[i]->Location = System::Drawing::Point(563, 164+(i*104));
				this->a_btnAxisMove2Pos[i]->Name = L"btnAxisMove2Pos"+i;
				this->a_btnAxisMove2Pos[i]->Size = System::Drawing::Size(143, 90);
				this->a_btnAxisMove2Pos[i]->TabIndex = 36;
				this->a_btnAxisMove2Pos[i]->Text = L"";
				this->a_btnAxisMove2Pos[i]->UseVisualStyleBackColor = true;
				this->a_btnAxisMove2Pos[i]->TabStop = false;
				this->a_btnAxisMove2Pos[i]->TabIndex = i;
				this->a_btnAxisMove2Pos[i]->Visible = false;
				this->a_btnAxisMove2Pos[i]->Click += gcnew System::EventHandler(this, &DriveComponent::btnAxisMove2Pos_Click);
				pT_MyContainer->Controls->Add(this->a_btnAxisMove2Pos[i]);
			}
			// 
			// btnYAxisTeachPos
			// 
			for (i=0;i<4;i++)
			{
				this->a_btnAxisTeachPos[i]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(0)));
				this->a_btnAxisTeachPos[i]->Location = System::Drawing::Point(411, 164+(i*104));
				this->a_btnAxisTeachPos[i]->Name = L"btnAxisTeachPos"+i;
				this->a_btnAxisTeachPos[i]->Size = System::Drawing::Size(143, 90);
				this->a_btnAxisTeachPos[i]->TabIndex = 34;
				this->a_btnAxisTeachPos[i]->Text = L"";
				this->a_btnAxisTeachPos[i]->UseVisualStyleBackColor = true;
				this->a_btnAxisTeachPos[i]->TabStop = false;
				this->a_btnAxisTeachPos[i]->TabIndex = i;
				this->a_btnAxisTeachPos[i]->Visible = false;
				this->a_btnAxisTeachPos[i]->Click += gcnew System::EventHandler(this, &DriveComponent::btnAxisTeachPos_Click);
				pT_MyContainer->Controls->Add(this->a_btnAxisTeachPos[i]);
			}
			// 
			// lblAxisPos
			// 
			for (i=0;i<4;i++)
			{
				this->a_lblAxisPos[i]->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				this->a_lblAxisPos[i]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(0)));
				this->a_lblAxisPos[i]->Location = System::Drawing::Point(260, 186+(i*104));
				this->a_lblAxisPos[i]->Name = L"lblAxisPos"+i;
				this->a_lblAxisPos[i]->Size = System::Drawing::Size(143, 39);
				this->a_lblAxisPos[i]->TabIndex = 29;
				this->a_lblAxisPos[i]->Text = L"0";
				this->a_lblAxisPos[i]->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				this->a_lblAxisPos[i]->Visible = false;
				this->a_lblAxisPos[i]->BackColor = SystemColors::Control;
				pT_MyContainer->Controls->Add(this->a_lblAxisPos[i]);
			}
			// 
			// a_lblPosName
			// 
			for (i=0;i<4;i++)
			{
				this->a_lblPosName[i]->AutoSize = true;
				this->a_lblPosName[i]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(0)));
				this->a_lblPosName[i]->Location = System::Drawing::Point(44, 192+(i*104));
				this->a_lblPosName[i]->Name = L"lblPosName"+i;
				this->a_lblPosName[i]->Size = System::Drawing::Size(74, 30);
				this->a_lblPosName[i]->TabIndex = 28;
				this->a_lblPosName[i]->Text = L"";
				this->a_lblPosName[i]->Visible = false;
				pT_MyContainer->Controls->Add(this->a_lblPosName[i]);
			}
			// 
			// cobHolderNumber
			// 
			for (i=0;i<4;i++)
			{
				this->a_cobAxisListPos[i]->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				this->a_cobAxisListPos[i]->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					static_cast<System::Byte>(0)));
				this->a_cobAxisListPos[i]->FormattingEnabled = true;
				this->a_cobAxisListPos[i]->Location = System::Drawing::Point(143, 186+(i*104));
				this->a_cobAxisListPos[i]->Name = L"cobAxisListPos"+i;
				this->a_cobAxisListPos[i]->Size = System::Drawing::Size(93, 42);
				this->a_cobAxisListPos[i]->TabIndex = 27;
				this->a_cobAxisListPos[i]->TabStop = false;
				this->a_cobAxisListPos[i]->TabIndex = i;
				this->a_cobAxisListPos[i]->Visible = false;
				this->a_cobAxisListPos[i]->SelectedIndexChanged += gcnew System::EventHandler(this, &DriveComponent::cobAxisListPos_SelectedIndexChanged);
				pT_MyContainer->Controls->Add(this->a_cobAxisListPos[i]);
			}
			// 
			// tbaxisJogStep
			// 
			this->tbaxisJogStep->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tbaxisJogStep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tbaxisJogStep->Location = System::Drawing::Point(611, 71);
			this->tbaxisJogStep->Name = L"tbaxisJogStep";
			this->tbaxisJogStep->Size = System::Drawing::Size(95, 42);
			this->tbaxisJogStep->TabIndex = 33;
			this->tbaxisJogStep->Text = L"0";
			this->tbaxisJogStep->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;;
			this->tbaxisJogStep->Click += gcnew System::EventHandler(this, &DriveComponent::tbAxisJogStep_Click);
			pT_MyContainer->Controls->Add(this->tbaxisJogStep);
			// 
			// btnAxisServo
			// 
			this->btnAxisServo->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAxisServo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnAxisServo->Location = System::Drawing::Point(135, 50);
			this->btnAxisServo->Name = L"btnAxisServo";
			this->btnAxisServo->Size = System::Drawing::Size(113, 90);
			this->btnAxisServo->TabIndex = 32;
			this->btnAxisServo->Text = L"";
			this->btnAxisServo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAxisServo->UseVisualStyleBackColor = true;
			this->btnAxisServo->Click += gcnew System::EventHandler(this, &DriveComponent::btnAxisServo_Click);
			pT_MyContainer->Controls->Add(this->btnAxisServo);
			// 
			// btnAxisHome
			// 
			this->btnAxisHome->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAxisHome->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnAxisHome->Location = System::Drawing::Point(15, 50);
			this->btnAxisHome->Name = L"btnAxisHome";
			this->btnAxisHome->Size = System::Drawing::Size(113, 90);
			this->btnAxisHome->TabIndex = 32;
			this->btnAxisHome->Text = L"";
			this->btnAxisHome->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAxisHome->UseVisualStyleBackColor = true;
			this->btnAxisHome->Click += gcnew System::EventHandler(this, &DriveComponent::btnAxisHome_Click);
			pT_MyContainer->Controls->Add(this->btnAxisHome);
			// 
			// btnAxisSpecific
			// 
			this->btnAxisSpecific->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnAxisSpecific->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnAxisSpecific->Location = System::Drawing::Point(15, 50);
			this->btnAxisSpecific->Name = L"btnAxisSpecific";
			this->btnAxisSpecific->Size = System::Drawing::Size(113, 90);
			this->btnAxisSpecific->TabIndex = 32;
			this->btnAxisSpecific->Text = L"";
			this->btnAxisSpecific->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAxisSpecific->UseVisualStyleBackColor = true;
			this->btnAxisSpecific->Visible = false;
			this->btnAxisSpecific->Click += gcnew System::EventHandler(this, &DriveComponent::btnAxisSpecific_Click);
			pT_MyContainer->Controls->Add(this->btnAxisSpecific);
			// 
			// lblAxisCurrentPos
			// 
			this->lblAxisCurrentPos->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblAxisCurrentPos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblAxisCurrentPos->Location = System::Drawing::Point(359, 72);
			this->lblAxisCurrentPos->Name = L"lblAxisCurrentPos";
			this->lblAxisCurrentPos->Size = System::Drawing::Size(143, 39);
			this->lblAxisCurrentPos->TabIndex = 22;
			this->lblAxisCurrentPos->Text = L"";
			this->lblAxisCurrentPos->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblAxisCurrentPos->BackColor = SystemColors::Control;
			pT_MyContainer->Controls->Add(this->lblAxisCurrentPos);

		}
#pragma endregion
private: System::Void btnaxisJogP_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(s_ComponentName + L" : Jog +" + tbaxisJogStep->Text);
			SetTCManOffsetData(DriveDataOffset+offsetof(TC_MAN_DRIVE,MD_MoveFw.MB_Activate));
		 }
private: System::Void btnaxisJogN_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(s_ComponentName + L" : Jog -" + tbaxisJogStep->Text);
			SetTCManOffsetData(DriveDataOffset+offsetof(TC_MAN_DRIVE,MD_MoveBw.MB_Activate));
		 }
private: System::Void tbAxisJogStep_Click(System::Object^  sender, System::EventArgs^  e) {
			frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(TUtilities::pS_LoadString(TextIndex::JogStep) + " : " + this->pT_MyContainer->Text, double::Parse(tbaxisJogStep->Text));
			if (Keypad->ShowDialog(this->pT_MyContainer) == System::Windows::Forms::DialogResult::OK)
			{
				TLogger::AddManualLog(s_ComponentName + L" : " + TUtilities::pS_LoadString(TextIndex::JogStep) + L" = " + Keypad->Value.ToString());
				WriteTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_JogStep), (TC_LREAL)Keypad->Value);
			}
		 }

private: System::Void btnAxisServo_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(s_ComponentName + L" : " + TUtilities::pS_LoadString(TextIndex::Servo) + L" " + TUtilities::pS_GetTextBool(btnAxisServo->Checked));
			WriteTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE,MD_ServoON.MB_Activate),(TC_BOOL)btnAxisServo->Checked);
		 }		 
private: System::Void btnAxisHome_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(s_ComponentName + L" : " + TUtilities::pS_LoadString(TextIndex::Home) + L" " + TUtilities::pS_GetTextBool(btnAxisHome->Checked));
	WriteTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE, MD_Home.MB_Activate), (TC_BOOL)btnAxisHome->Checked);
}
private: System::Void btnAxisSpecific_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(s_ComponentName + L" : " + TUtilities::pS_LoadString(TextIndex::Specific) + L" " + TUtilities::pS_GetTextBool(btnAxisSpecific->Checked));
			WriteTCManOffsetData(DriveDataOffset + offsetof(TC_MAN_DRIVE,MD_Specific.MB_Activate),(TC_BOOL)btnAxisSpecific->Checked);
		 }
private: System::Void btnAxisMove2Pos_Click(System::Object^  sender, System::EventArgs^  e) {
			int i_l_PosNb = ((System::Windows::Forms::Button ^)sender)->TabIndex;
			TLogger::AddManualLog(s_ComponentName + L" : " + TUtilities::pS_LoadString(TextIndex::MoveToPos) + L" " + a_lblPosName[i_l_PosNb]->Text);
			SetTCManOffsetData(a_PositionDataOffset[i_l_PosNb] + offsetof(TC_MAN_DRIVE_POS,MDP_MoveToTeach.MB_Activate));
		 }
private: System::Void btnAxisTeachPos_Click(System::Object^  sender, System::EventArgs^  e) {
			int i_l_PosNb = ((System::Windows::Forms::Button ^)sender)->TabIndex;
			MyMsgBox^ pT_l_ValidateChange = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::PosTeachReq) + L" <" + a_lblPosName[i_l_PosNb]->Text + L"> ?",TUtilities::pS_LoadString(TextIndex::ValidateReq),MessageBoxButtons::YesNo);
			pT_l_ValidateChange->ShowDialog();
			if (1 == pT_l_ValidateChange->iPressedButton)
			{
				TLogger::AddManualLog(s_ComponentName + L" : " + TUtilities::pS_LoadString(TextIndex::Position) + L" " + a_lblPosName[i_l_PosNb]->Text + L" : " + a_lblAxisPos[i_l_PosNb]->Text + " --> " + lblAxisCurrentPos->Text);
				SetTCManOffsetData(a_PositionDataOffset[i_l_PosNb] + offsetof(TC_MAN_DRIVE_POS,MDP_Teach));
			}
		 }
private: System::Void cobAxisListPos_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			int i_l_CobNb = ((System::Windows::Forms::ComboBox ^)sender)->TabIndex;
			TLogger::AddManualLog(s_ComponentName + TUtilities::pS_LoadString(TextIndex::Position) + a_lblPosName[i_l_CobNb]->Text );
			WriteTCManOffsetData(a_CobDataOffset[i_l_CobNb],(TC_INT)a_cobAxisListPos[i_l_CobNb]->SelectedIndex);
		 }
		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
};
}