#pragma once

#include "TUtilities.h"
#include "MyMsgBox.h"

namespace Projet1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de UserManager
	/// </summary>
	public ref class UserManager : public System::Windows::Forms::Form
	{
	public:
		UserManager(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~UserManager()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnClose;
	private: System::Windows::Forms::Label^  lblPassword;
	private: System::Windows::Forms::Label^  lblName;
	private: System::Windows::Forms::TextBox^  tbName;
	private: System::Windows::Forms::Button^  btnAddUser;
	private: System::Windows::Forms::CheckBox^  cbMaintenance;
	private: System::Windows::Forms::MaskedTextBox^  tbPassword;
	private: System::Windows::Forms::CheckBox^  cbManager;
	private: System::Windows::Forms::Button^  btnDeleteUser;
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
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->lblPassword = (gcnew System::Windows::Forms::Label());
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->tbName = (gcnew System::Windows::Forms::TextBox());
			this->btnAddUser = (gcnew System::Windows::Forms::Button());
			this->cbMaintenance = (gcnew System::Windows::Forms::CheckBox());
			this->tbPassword = (gcnew System::Windows::Forms::MaskedTextBox());
			this->cbManager = (gcnew System::Windows::Forms::CheckBox());
			this->btnDeleteUser = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnClose
			// 
			this->btnClose->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->btnClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnClose->Location = System::Drawing::Point(30, 435);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(225, 66);
			this->btnClose->TabIndex = 3;
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &UserManager::btnClose_Click);
			// 
			// lblPassword
			// 
			this->lblPassword->AutoSize = true;
			this->lblPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblPassword->Location = System::Drawing::Point(90, 152);
			this->lblPassword->Name = L"lblPassword";
			this->lblPassword->Size = System::Drawing::Size(200, 36);
			this->lblPassword->TabIndex = 20;
			this->lblPassword->Text = L"";
			// 
			// lblName
			// 
			this->lblName->AutoSize = true;
			this->lblName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblName->Location = System::Drawing::Point(90, 71);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(92, 36);
			this->lblName->TabIndex = 18;
			this->lblName->Text = L"";
			// 
			// tbName
			// 
			this->tbName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->tbName->Location = System::Drawing::Point(299, 66);
			this->tbName->Name = L"tbName";
			this->tbName->Size = System::Drawing::Size(315, 44);
			this->tbName->TabIndex = 0;
			this->tbName->Click += gcnew System::EventHandler(this, &UserManager::tbName_Click);
			// 
			// btnAddUser
			// 
			this->btnAddUser->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->btnAddUser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnAddUser->Location = System::Drawing::Point(498, 435);
			this->btnAddUser->Name = L"btnAddUser";
			this->btnAddUser->Size = System::Drawing::Size(225, 66);
			this->btnAddUser->TabIndex = 4;
			this->btnAddUser->Text = L"";
			this->btnAddUser->UseVisualStyleBackColor = true;
			this->btnAddUser->Click += gcnew System::EventHandler(this, &UserManager::btnAddUser_Click);
			// 
			// cbMaintenance
			// 
			this->cbMaintenance->AutoSize = true;
			this->cbMaintenance->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cbMaintenance->Location = System::Drawing::Point(96, 252);
			this->cbMaintenance->Name = L"cbMaintenance";
			this->cbMaintenance->Size = System::Drawing::Size(393, 42);
			this->cbMaintenance->TabIndex = 2;
			this->cbMaintenance->Text = L"";
			this->cbMaintenance->UseVisualStyleBackColor = true;
			this->cbMaintenance->CheckedChanged += gcnew System::EventHandler(this, &UserManager::cbMaintenance_CheckedChanged);
			// 
			// tbPassword
			// 
			this->tbPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->tbPassword->Location = System::Drawing::Point(299, 147);
			this->tbPassword->Name = L"tbPassword";
			this->tbPassword->Size = System::Drawing::Size(315, 44);
			this->tbPassword->TabIndex = 1;
			this->tbPassword->UseSystemPasswordChar = true;
			this->tbPassword->Click += gcnew System::EventHandler(this, &UserManager::tbName_Click);
			// 
			// cbManager
			// 
			this->cbManager->AutoSize = true;
			this->cbManager->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cbManager->Location = System::Drawing::Point(96, 329);
			this->cbManager->Name = L"cbManager";
			this->cbManager->Size = System::Drawing::Size(342, 42);
			this->cbManager->TabIndex = 21;
			this->cbManager->Text = L"";
			this->cbManager->UseVisualStyleBackColor = true;
			this->cbManager->CheckedChanged += gcnew System::EventHandler(this, &UserManager::cbManager_CheckedChanged);
			// 
			// btnDeleteUser
			// 
			this->btnDeleteUser->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->btnDeleteUser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnDeleteUser->Location = System::Drawing::Point(264, 435);
			this->btnDeleteUser->Name = L"btnDeleteUser";
			this->btnDeleteUser->Size = System::Drawing::Size(225, 66);
			this->btnDeleteUser->TabIndex = 22;
			this->btnDeleteUser->Text = L"";
			this->btnDeleteUser->UseVisualStyleBackColor = true;
			this->btnDeleteUser->Click += gcnew System::EventHandler(this, &UserManager::btnDeleteUser_Click);
			// 
			// UserManager
			// 
			this->AcceptButton = this->btnAddUser;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(747, 537);
			this->Controls->Add(this->btnDeleteUser);
			this->Controls->Add(this->cbManager);
			this->Controls->Add(this->tbPassword);
			this->Controls->Add(this->cbMaintenance);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->lblPassword);
			this->Controls->Add(this->lblName);
			this->Controls->Add(this->tbName);
			this->Controls->Add(this->btnAddUser);
			this->Name = L"UserManager";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"";
			this->VisibleChanged += gcnew System::EventHandler(this, &UserManager::UserManager_VisibleChanged);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
private: System::Void btnAddUser_Click(System::Object^  sender, System::EventArgs^  e) {
			bool b_l_CanAddIt = true;

			// Check if a valid name was entered
			if (0 == String::Compare(tbName->Text,""))
			{
				MyMsgBox^ pT_l_EmptyName = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::NeedValidName) + L" !",TUtilities::pS_LoadString(TextIndex::DataError),MessageBoxButtons::OK);
				pT_l_EmptyName->ShowDialog();
				b_l_CanAddIt = false;
			}
			// Or we try to change system password without the rights
			else if (!TUser::b_HasSystemLevel() && (0 == String::Compare(tbName->Text,"nexera")))
			{	
				MyMsgBox^ pT_l_EmptyName = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::CantModifyUser) + L" !",TUtilities::pS_LoadString(TextIndex::DataError),MessageBoxButtons::OK);
				pT_l_EmptyName->ShowDialog();
				b_l_CanAddIt = false;
			}
			// Check if this user is already existing
			else if (TUtilities::b_UserExists(tbName->Text))
			{
				MyMsgBox^ pT_l_ValidateChange = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::SureToModifyUser) + L" ?",TUtilities::pS_LoadString(TextIndex::ValidateReq),MessageBoxButtons::YesNo);
				pT_l_ValidateChange->ShowDialog();
				if (2 == pT_l_ValidateChange->iPressedButton)
					b_l_CanAddIt = false;
			}
			if (b_l_CanAddIt)
			{
				 // Check if the user has a password in maintenance
				 if ((cbMaintenance->Checked || cbManager->Checked) && (0 == String::Compare(tbPassword->Text,"")))
				 {
					MyMsgBox^ pT_l_PasswordMissing = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::NeedPW4MaintUser),TUtilities::pS_LoadString(TextIndex::DataError),MessageBoxButtons::OK);
					pT_l_PasswordMissing->ShowDialog();
					b_l_CanAddIt = false;
				 }
			}
			if (b_l_CanAddIt)
			{
				enum UserLevel e_l_NewUserLevel = UL_Operator;

				if (cbManager->Checked)
					e_l_NewUserLevel = UL_Manager;
				if (cbMaintenance->Checked)
					e_l_NewUserLevel = UL_Maintenance;
				TUtilities::CreateUser(tbName->Text,tbPassword->Text,e_l_NewUserLevel);
				MyMsgBox^ pT_l_NewUser = gcnew MyMsgBox(tbName->Text + " " + TUtilities::pS_LoadString(TextIndex::CanLogNow),TUtilities::pS_LoadString(TextIndex::UserCreated),MessageBoxButtons::OK);
				pT_l_NewUser->ShowDialog();
				tbName->Text = "";
				tbPassword->Text = "";
				cbManager->Checked = false;
				cbMaintenance->Checked = false;
			}
		}
private: System::Void tbName_Click(System::Object^  sender, System::EventArgs^  e) {
			TUtilities::ShowOSK();
		}
private: System::Void cbManager_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (cbManager->Checked)
				 cbMaintenance->Checked = false;
		 }
private: System::Void cbMaintenance_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (cbMaintenance->Checked)
				 cbManager->Checked = false;
		 }
private: System::Void btnDeleteUser_Click(System::Object^  sender, System::EventArgs^  e) {
			if (TUtilities::b_UserExists(tbName->Text))
			{
				MyMsgBox^ pT_l_ValidateChange = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::Sure2DeleteUser),TUtilities::pS_LoadString(TextIndex::ConfirmReq),MessageBoxButtons::YesNo);
				pT_l_ValidateChange->ShowDialog();
				if (1 == pT_l_ValidateChange->iPressedButton)
				{
					TUtilities::DeleteUser(tbName->Text);
					tbName->Text = "";
				}
			}
			else
			{
				MyMsgBox^ pT_l_NoUser = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::UserNotExisting),TUtilities::pS_LoadString(TextIndex::DeleteError),MessageBoxButtons::OK);
				pT_l_NoUser->ShowDialog();
			}
		 }
private: System::Void UserManager_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			btnClose->Text = TUtilities::pS_LoadString(TextIndex::Exit);
			lblPassword->Text = TUtilities::pS_LoadString(TextIndex::Password) + L" :";
			lblName->Text = TUtilities::pS_LoadString(TextIndex::Name) + L" :";
			btnAddUser->Text = TUtilities::pS_LoadString(TextIndex::Add);
			cbMaintenance->Text = TUtilities::pS_LoadString(TextIndex::HasMaintenanceRights);
			cbManager->Text = TUtilities::pS_LoadString(TextIndex::HasManagerRights);
			btnDeleteUser->Text = TUtilities::pS_LoadString(TextIndex::Delete);
			Text = TUtilities::pS_LoadString(TextIndex::UserManager);
		 }
};
}
