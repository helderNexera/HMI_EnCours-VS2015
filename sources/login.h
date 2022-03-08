#pragma once

#include "TTwincatInterface.h"
#include "MyMsgBox.h"
#include "global.h"
#include "TUtilities.h"
#include "TLogger.h"

namespace Projet1 {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de login
	/// </summary>
	public ref class login : public System::Windows::Forms::Form
	{
	public:
		login(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			if (!System::Diagnostics::Debugger::IsAttached)
				this->TopMost = true;
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnLoginDE;
	protected:

	protected:
	private: System::Windows::Forms::Button^  btnLoginFR;

	protected:

	protected:

	protected:

		bool bMyLogin(int i_x_LanguageNb);
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::TextBox^  tbName;
	private: System::Windows::Forms::Label^  lblName;
	private: System::Windows::Forms::Label^  lblPassword;
	private: System::Windows::Forms::Label^  lblTeam;
	private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape1;
	private: System::Windows::Forms::Button^  btnExit;
	private: System::Windows::Forms::MaskedTextBox^  tbPassword;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Label^  lblLanguage;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(login::typeid));
			this->btnLoginFR = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->tbName = (gcnew System::Windows::Forms::TextBox());
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->lblPassword = (gcnew System::Windows::Forms::Label());
			this->lblTeam = (gcnew System::Windows::Forms::Label());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->tbPassword = (gcnew System::Windows::Forms::MaskedTextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->lblLanguage = (gcnew System::Windows::Forms::Label());
			this->btnLoginDE = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// btnLoginFR
			// 
			this->btnLoginFR->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->btnLoginFR->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLoginFR->Location = System::Drawing::Point(926, 406);
			this->btnLoginFR->Name = L"btnLoginFR";
			this->btnLoginFR->Size = System::Drawing::Size(225, 66);
			this->btnLoginFR->TabIndex = 4;
			this->btnLoginFR->UseVisualStyleBackColor = true;
			this->btnLoginFR->Click += gcnew System::EventHandler(this, &login::btnLoginFR_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(600, 600);
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// tbName
			// 
			this->tbName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbName->Location = System::Drawing::Point(824, 167);
			this->tbName->Name = L"tbName";
			this->tbName->Size = System::Drawing::Size(315, 38);
			this->tbName->TabIndex = 0;
			this->tbName->Click += gcnew System::EventHandler(this, &login::tbName_Click);
			// 
			// lblName
			// 
			this->lblName->AutoSize = true;
			this->lblName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblName->Location = System::Drawing::Point(635, 170);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(0, 31);
			this->lblName->TabIndex = 9;
			// 
			// lblPassword
			// 
			this->lblPassword->AutoSize = true;
			this->lblPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPassword->Location = System::Drawing::Point(635, 224);
			this->lblPassword->Name = L"lblPassword";
			this->lblPassword->Size = System::Drawing::Size(0, 31);
			this->lblPassword->TabIndex = 11;
			// 
			// lblTeam
			// 
			this->lblTeam->AutoSize = true;
			this->lblTeam->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTeam->Location = System::Drawing::Point(435, 250);
			this->lblTeam->Name = L"lblTeam";
			this->lblTeam->Size = System::Drawing::Size(0, 31);
			this->lblTeam->TabIndex = 13;
			this->lblTeam->Visible = false;
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(0, 0);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(1) { this->rectangleShape1 });
			this->shapeContainer1->Size = System::Drawing::Size(1194, 632);
			this->shapeContainer1->TabIndex = 14;
			this->shapeContainer1->TabStop = false;
			// 
			// rectangleShape1
			// 
			this->rectangleShape1->BorderColor = System::Drawing::Color::LightBlue;
			this->rectangleShape1->BorderWidth = 4;
			this->rectangleShape1->CornerRadius = 10;
			this->rectangleShape1->Location = System::Drawing::Point(2, 2);
			this->rectangleShape1->Name = L"rectangleShape1";
			this->rectangleShape1->Size = System::Drawing::Size(1188, 626);
			// 
			// btnExit
			// 
			this->btnExit->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->btnExit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnExit->Location = System::Drawing::Point(792, 522);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(225, 66);
			this->btnExit->TabIndex = 3;
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &login::btnExit_Click);
			// 
			// tbPassword
			// 
			this->tbPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbPassword->Location = System::Drawing::Point(824, 221);
			this->tbPassword->Name = L"tbPassword";
			this->tbPassword->Size = System::Drawing::Size(315, 38);
			this->tbPassword->TabIndex = 1;
			this->tbPassword->UseSystemPasswordChar = true;
			this->tbPassword->Click += gcnew System::EventHandler(this, &login::tbName_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pictureBox2->Location = System::Drawing::Point(759, 30);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(312, 83);
			this->pictureBox2->TabIndex = 16;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &login::pictureBox2_Click);
			// 
			// lblLanguage
			// 
			this->lblLanguage->AutoSize = true;
			this->lblLanguage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLanguage->Location = System::Drawing::Point(435, 310);
			this->lblLanguage->Name = L"lblLanguage";
			this->lblLanguage->Size = System::Drawing::Size(0, 31);
			this->lblLanguage->TabIndex = 17;
			this->lblLanguage->Visible = false;
			// 
			// btnLoginDE
			// 
			this->btnLoginDE->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->btnLoginDE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLoginDE->Location = System::Drawing::Point(660, 406);
			this->btnLoginDE->Name = L"btnLoginDE";
			this->btnLoginDE->Size = System::Drawing::Size(225, 66);
			this->btnLoginDE->TabIndex = 18;
			this->btnLoginDE->UseVisualStyleBackColor = true;
			this->btnLoginDE->Click += gcnew System::EventHandler(this, &login::btnLoginDE_Click);
			// 
			// login
			// 
			this->AcceptButton = this->btnLoginFR;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1194, 632);
			this->Controls->Add(this->btnLoginDE);
			this->Controls->Add(this->lblLanguage);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->tbPassword);
			this->Controls->Add(this->btnExit);
			this->Controls->Add(this->lblTeam);
			this->Controls->Add(this->lblPassword);
			this->Controls->Add(this->lblName);
			this->Controls->Add(this->tbName);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->btnLoginFR);
			this->Controls->Add(this->shapeContainer1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"login";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Login";
			this->Load += gcnew System::EventHandler(this, &login::login_Load);
			this->VisibleChanged += gcnew System::EventHandler(this, &login::login_VisibleChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

private: System::Void btnExit_Click(System::Object^  sender, System::EventArgs^  e) {
			MyMsgBox^ pT_l_ValidateExit = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::SureToExitApplication) + " ?", TUtilities::pS_LoadString(TextIndex::ValidateReq),MessageBoxButtons::YesNo);
			pT_l_ValidateExit->ShowDialog();
			if (1 == pT_l_ValidateExit->iPressedButton)
			{
				TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::ExitApp));
				Application::Exit();
			}
		 }
private: System::Void tbName_Click(System::Object^  sender, System::EventArgs^  e) {
			TUtilities::ShowOSK();
		 }
private: System::Void login_Load(System::Object^  sender, System::EventArgs^  e) {
			// Check if we can exit the application
			btnExit->Enabled = !(ProductionOrder::b_OrderStarted());
		 }
private: System::Void login_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			btnLoginFR->Text = TUtilities::pS_LoadString(TextIndex::Login) + " FR";
			btnLoginDE->Text = TUtilities::pS_LoadString(TextIndex::Login) + " DE";
			lblName->Text = TUtilities::pS_LoadString(TextIndex::Name) + " :";
			lblPassword->Text = TUtilities::pS_LoadString(TextIndex::Password) + " :";
			btnExit->Text = TUtilities::pS_LoadString(TextIndex::Exit);

		 }
private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			// Recreate nexera access
			TUtilities::CreateUser("nexera","ascii",UL_System);
		 }

private: System::Void btnLoginDE_Click(System::Object^  sender, System::EventArgs^  e) {
	if (bMyLogin(1))
		this->Close();
}
private: System::Void btnLoginFR_Click(System::Object^  sender, System::EventArgs^  e) {
	if (bMyLogin(0))
		this->Close();
}
};
}
