#pragma once

#include "TUtilities.h"

namespace Projet1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de MyMsgBox
	/// </summary>
	public ref class MyMsgBox : public System::Windows::Forms::Form
	{
	public: int iPressedButton;
	private:
		MessageBoxButtons e_CurrentMsgButton;
	public:
		MyMsgBox(String^ pS_x_Text,String^ pS_x_Title,MessageBoxButtons e_x_MsgButton)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			this->MsgBoxTitle->Text = pS_x_Title;
			this->MsgBoxText->Text = pS_x_Text;

			e_CurrentMsgButton = e_x_MsgButton;
			switch(e_x_MsgButton)
			{
				case MessageBoxButtons::AbortRetryIgnore:
					btnLeft->Text = TUtilities::pS_LoadString(TextIndex::Cancel);
					btnMiddle->Text = TUtilities::pS_LoadString(TextIndex::Retry);
					btnRight->Text = TUtilities::pS_LoadString(TextIndex::Ignore);
					break;
				case MessageBoxButtons::OK:
					btnLeft->Visible = false;
					btnMiddle->Text = "OK";
					btnRight->Visible = false;
					break;
				case MessageBoxButtons::OKCancel:
					btnLeft->Text = "OK";
					btnMiddle->Visible = false;
					btnRight->Text = TUtilities::pS_LoadString(TextIndex::Cancel);
					break;
				case MessageBoxButtons::RetryCancel:
					btnLeft->Text = TUtilities::pS_LoadString(TextIndex::Retry);
					btnMiddle->Visible = false;
					btnRight->Text = TUtilities::pS_LoadString(TextIndex::Cancel);
					break;
				case MessageBoxButtons::YesNo:
					btnLeft->Text = TUtilities::pS_LoadString(TextIndex::Yes);
					btnMiddle->Visible = false;
					btnRight->Text = TUtilities::pS_LoadString(TextIndex::No);
					break;
				case MessageBoxButtons::YesNoCancel:
					btnLeft->Text =  TUtilities::pS_LoadString(TextIndex::Yes);
					btnMiddle->Text =  TUtilities::pS_LoadString(TextIndex::No);
					btnRight->Text = TUtilities::pS_LoadString(TextIndex::Cancel);
					break;
			}
			iPressedButton = 0;
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MyMsgBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  MsgBoxText;
	private: System::Windows::Forms::Button^  btnRight;

	private: System::Windows::Forms::Button^  btnLeft;
	private: System::Windows::Forms::Button^  btnMiddle;
	private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape1;
	private: Microsoft::VisualBasic::PowerPacks::LineShape^  lineShape1;
	private: System::Windows::Forms::Label^  MsgBoxTitle;
	protected: 

	protected: 

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
			this->MsgBoxText = (gcnew System::Windows::Forms::Label());
			this->btnRight = (gcnew System::Windows::Forms::Button());
			this->btnLeft = (gcnew System::Windows::Forms::Button());
			this->btnMiddle = (gcnew System::Windows::Forms::Button());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->lineShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::LineShape());
			this->rectangleShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->MsgBoxTitle = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// MsgBoxText
			// 
			this->MsgBoxText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MsgBoxText->Location = System::Drawing::Point(18, 60);
			this->MsgBoxText->Name = L"MsgBoxText";
			this->MsgBoxText->Size = System::Drawing::Size(1158, 219);
			this->MsgBoxText->TabIndex = 8;
			this->MsgBoxText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->MsgBoxText->UseMnemonic = false;
			// 
			// btnRight
			// 
			this->btnRight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnRight->Location = System::Drawing::Point(803, 293);
			this->btnRight->Name = L"btnRight";
			this->btnRight->Size = System::Drawing::Size(225, 66);
			this->btnRight->TabIndex = 7;
			this->btnRight->UseVisualStyleBackColor = true;
			this->btnRight->Click += gcnew System::EventHandler(this, &MyMsgBox::btnRight_Click);
			// 
			// btnLeft
			// 
			this->btnLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnLeft->Location = System::Drawing::Point(153, 293);
			this->btnLeft->Name = L"btnLeft";
			this->btnLeft->Size = System::Drawing::Size(225, 66);
			this->btnLeft->TabIndex = 6;
			this->btnLeft->UseVisualStyleBackColor = true;
			this->btnLeft->Click += gcnew System::EventHandler(this, &MyMsgBox::btnLeft_Click);
			// 
			// btnMiddle
			// 
			this->btnMiddle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->btnMiddle->Location = System::Drawing::Point(473, 293);
			this->btnMiddle->Name = L"btnMiddle";
			this->btnMiddle->Size = System::Drawing::Size(225, 66);
			this->btnMiddle->TabIndex = 9;
			this->btnMiddle->UseVisualStyleBackColor = true;
			this->btnMiddle->Click += gcnew System::EventHandler(this, &MyMsgBox::btnMiddle_Click);
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(0, 0);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(2) {this->lineShape1, 
				this->rectangleShape1});
			this->shapeContainer1->Size = System::Drawing::Size(1194, 411);
			this->shapeContainer1->TabIndex = 11;
			this->shapeContainer1->TabStop = false;
			// 
			// lineShape1
			// 
			this->lineShape1->BorderColor = System::Drawing::Color::LightBlue;
			this->lineShape1->BorderWidth = 3;
			this->lineShape1->Name = L"lineShape1";
			this->lineShape1->X1 = 0;
			this->lineShape1->X2 = 1577;
			this->lineShape1->Y1 = 53;
			this->lineShape1->Y2 = 53;
			// 
			// rectangleShape1
			// 
			this->rectangleShape1->BorderColor = System::Drawing::Color::LightBlue;
			this->rectangleShape1->BorderWidth = 6;
			this->rectangleShape1->CornerRadius = 15;
			this->rectangleShape1->Location = System::Drawing::Point(3, 3);
			this->rectangleShape1->Name = L"rectangleShape1";
			this->rectangleShape1->Size = System::Drawing::Size(1188, 405);
			// 
			// MsgBoxTitle
			// 
			this->MsgBoxTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MsgBoxTitle->Location = System::Drawing::Point(18, 6);
			this->MsgBoxTitle->Name = L"MsgBoxTitle";
			this->MsgBoxTitle->Size = System::Drawing::Size(1158, 42);
			this->MsgBoxTitle->TabIndex = 12;
			this->MsgBoxTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->MsgBoxTitle->UseMnemonic = false;
			// 
			// MyMsgBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1194, 411);
			this->Controls->Add(this->MsgBoxTitle);
			this->Controls->Add(this->btnMiddle);
			this->Controls->Add(this->MsgBoxText);
			this->Controls->Add(this->btnRight);
			this->Controls->Add(this->btnLeft);
			this->Controls->Add(this->shapeContainer1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyMsgBox";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyMsgBox";
			this->TopMost = true;
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void btnLeft_Click(System::Object^  sender, System::EventArgs^  e) {
 			iPressedButton = 1;
			this->Close();
		 }
	private: System::Void btnMiddle_Click(System::Object^  sender, System::EventArgs^  e) {
			if (MessageBoxButtons::OK == e_CurrentMsgButton)
	 			iPressedButton = 1;
			else
	 			iPressedButton = 2;
			this->Close();
			 }
private: System::Void btnRight_Click(System::Object^  sender, System::EventArgs^  e) {
 			iPressedButton = 3;
			switch(e_CurrentMsgButton)
			{
				case MessageBoxButtons::OKCancel:
				case MessageBoxButtons::RetryCancel:
				case MessageBoxButtons::YesNo:
	 				iPressedButton = 2;
					break;
			}
			this->Close();
		 }
	};
}
