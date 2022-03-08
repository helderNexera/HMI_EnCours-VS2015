#pragma once

#include "NewOrder.h"
#include "RejectScreen.h"
#include "RTPearlingScreen.h"
#include "AutoSamplingScreen.h"
#include "TUtilities.h"
#include "Global.h"

namespace Projet1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de ProdScreen
	/// </summary>
	public ref class ProdScreen : public System::Windows::Forms::Form
	{
	public:
		ProdScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_RejectScreen = gcnew RejectScreen();
			pT_NewOrderForm = gcnew NewOrder(pT_RejectScreen);
			pT_RTPearlingScreen = gcnew RTPearlingScreen();
			pT_AutoSamplingScreen = gcnew AutoSamplingScreen();
			m_l_LastProductionTime = 0;
			m_l_LastWriteProductionTime = 0;

		}
	private: System::Windows::Forms::Button^  btnPurge;
	private: System::Windows::Forms::Label^  lblYield;
	private: System::Windows::Forms::Label^  lblYieldN;
	private: System::Windows::Forms::Label^  lblGoodQuantity;
	private: System::Windows::Forms::Label^  lblGoodQuantityN;
	private: System::Windows::Forms::Label^  lblRejectQuantity;
	private: System::Windows::Forms::Label^  lblRejectQuantityN;
	private: System::Windows::Forms::GroupBox^  gbProdDateN;
	private: System::Windows::Forms::Label^  lblStartProdDate;
	private: System::Windows::Forms::Label^  lblStartProdDateN;
	private: System::Windows::Forms::Label^  lblEndProdDate;
	private: System::Windows::Forms::Label^  lblEndProdDateN;
	private: System::Windows::Forms::Button^  btnReject;

			 // Our specific functions
	private:
		NewOrder^ pT_NewOrderForm;
		RejectScreen^ pT_RejectScreen;
		RTPearlingScreen^ pT_RTPearlingScreen;
		AutoSamplingScreen^ pT_AutoSamplingScreen;
		unsigned long m_l_LastProductionTime;
		unsigned long m_l_LastWriteProductionTime;
	private: System::Windows::Forms::Button^  btnRTPearling;
	private: System::Windows::Forms::Button^  btnRequestSample;
	private: System::Windows::Forms::PictureBox^  pbSous;
	private: System::Windows::Forms::PictureBox^  pbSus;
	private: MondemaComponents::BorderPanel^  borderPanel1;
	private: MondemaComponents::BorderPanel^  borderPanel2;
	private: System::Windows::Forms::Label^  lblProdTime;
	private: System::Windows::Forms::Label^  lblProdTimeN;
			 bool b_ScreenReloaded;
	public:
		void UpdateUI(void);
		void Reload(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~ProdScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	protected: 
	private: System::Windows::Forms::Label^  lblCurrentOrder;
	private: System::Windows::Forms::Button^  btnCloseOrder;
	private: System::Windows::Forms::Button^  btnNewOrder;
	private: System::Windows::Forms::Label^  lblProductivity;
	private: System::Windows::Forms::Label^  lblOrderN;
	private: System::Windows::Forms::Label^  lblPartN;
	private: System::Windows::Forms::Label^  lblOrderQuantityN;
	private: System::Windows::Forms::Label^  lblProdQuantityN;
	private: System::Windows::Forms::Label^  lblOrder;
	private: System::Windows::Forms::Label^  lblPart;
	private: System::Windows::Forms::Label^  lblOrderQuantity;
	private: System::Windows::Forms::Label^  lblProdQuantity;
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
			this->lblCurrentOrder = (gcnew System::Windows::Forms::Label());
			this->btnCloseOrder = (gcnew System::Windows::Forms::Button());
			this->btnNewOrder = (gcnew System::Windows::Forms::Button());
			this->lblProductivity = (gcnew System::Windows::Forms::Label());
			this->lblOrderN = (gcnew System::Windows::Forms::Label());
			this->lblPartN = (gcnew System::Windows::Forms::Label());
			this->lblOrderQuantityN = (gcnew System::Windows::Forms::Label());
			this->lblProdQuantityN = (gcnew System::Windows::Forms::Label());
			this->lblOrder = (gcnew System::Windows::Forms::Label());
			this->lblPart = (gcnew System::Windows::Forms::Label());
			this->lblOrderQuantity = (gcnew System::Windows::Forms::Label());
			this->lblProdQuantity = (gcnew System::Windows::Forms::Label());
			this->btnPurge = (gcnew System::Windows::Forms::Button());
			this->lblYield = (gcnew System::Windows::Forms::Label());
			this->lblYieldN = (gcnew System::Windows::Forms::Label());
			this->lblGoodQuantity = (gcnew System::Windows::Forms::Label());
			this->lblGoodQuantityN = (gcnew System::Windows::Forms::Label());
			this->lblRejectQuantity = (gcnew System::Windows::Forms::Label());
			this->lblRejectQuantityN = (gcnew System::Windows::Forms::Label());
			this->gbProdDateN = (gcnew System::Windows::Forms::GroupBox());
			this->lblProdTime = (gcnew System::Windows::Forms::Label());
			this->lblProdTimeN = (gcnew System::Windows::Forms::Label());
			this->lblEndProdDate = (gcnew System::Windows::Forms::Label());
			this->lblEndProdDateN = (gcnew System::Windows::Forms::Label());
			this->lblStartProdDate = (gcnew System::Windows::Forms::Label());
			this->lblStartProdDateN = (gcnew System::Windows::Forms::Label());
			this->btnReject = (gcnew System::Windows::Forms::Button());
			this->btnRTPearling = (gcnew System::Windows::Forms::Button());
			this->btnRequestSample = (gcnew System::Windows::Forms::Button());
			this->pbSous = (gcnew System::Windows::Forms::PictureBox());
			this->pbSus = (gcnew System::Windows::Forms::PictureBox());
			this->borderPanel1 = (gcnew MondemaComponents::BorderPanel());
			this->borderPanel2 = (gcnew MondemaComponents::BorderPanel());
			this->gbProdDateN->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSous))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSus))->BeginInit();
			this->borderPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// lblCurrentOrder
			// 
			this->lblCurrentOrder->AutoEllipsis = true;
			this->lblCurrentOrder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCurrentOrder->Location = System::Drawing::Point(38, 38);
			this->lblCurrentOrder->Name = L"lblCurrentOrder";
			this->lblCurrentOrder->Size = System::Drawing::Size(708, 60);
			this->lblCurrentOrder->TabIndex = 1;
			this->lblCurrentOrder->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnCloseOrder
			// 
			this->btnCloseOrder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCloseOrder->Location = System::Drawing::Point(30, 696);
			this->btnCloseOrder->Name = L"btnCloseOrder";
			this->btnCloseOrder->Size = System::Drawing::Size(225, 66);
			this->btnCloseOrder->TabIndex = 2;
			this->btnCloseOrder->UseVisualStyleBackColor = true;
			this->btnCloseOrder->Click += gcnew System::EventHandler(this, &ProdScreen::btnCloseLot_Click);
			// 
			// btnNewOrder
			// 
			this->btnNewOrder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnNewOrder->Location = System::Drawing::Point(530, 696);
			this->btnNewOrder->Name = L"btnNewOrder";
			this->btnNewOrder->Size = System::Drawing::Size(225, 66);
			this->btnNewOrder->TabIndex = 3;
			this->btnNewOrder->UseVisualStyleBackColor = true;
			this->btnNewOrder->Click += gcnew System::EventHandler(this, &ProdScreen::btnNewLot_Click);
			// 
			// lblProductivity
			// 
			this->lblProductivity->AutoEllipsis = true;
			this->lblProductivity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblProductivity->Location = System::Drawing::Point(800, 38);
			this->lblProductivity->Name = L"lblProductivity";
			this->lblProductivity->Size = System::Drawing::Size(693, 60);
			this->lblProductivity->TabIndex = 4;
			this->lblProductivity->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblOrderN
			// 
			this->lblOrderN->AutoSize = true;
			this->lblOrderN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOrderN->Location = System::Drawing::Point(120, 171);
			this->lblOrderN->Name = L"lblOrderN";
			this->lblOrderN->Size = System::Drawing::Size(50, 29);
			this->lblOrderN->TabIndex = 5;
			this->lblOrderN->Text = L"ON";
			// 
			// lblPartN
			// 
			this->lblPartN->AutoSize = true;
			this->lblPartN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPartN->Location = System::Drawing::Point(120, 225);
			this->lblPartN->Name = L"lblPartN";
			this->lblPartN->Size = System::Drawing::Size(47, 29);
			this->lblPartN->TabIndex = 6;
			this->lblPartN->Text = L"PN";
			// 
			// lblOrderQuantityN
			// 
			this->lblOrderQuantityN->AutoSize = true;
			this->lblOrderQuantityN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOrderQuantityN->Location = System::Drawing::Point(120, 282);
			this->lblOrderQuantityN->Name = L"lblOrderQuantityN";
			this->lblOrderQuantityN->Size = System::Drawing::Size(69, 29);
			this->lblOrderQuantityN->TabIndex = 7;
			this->lblOrderQuantityN->Text = L"OQN";
			// 
			// lblProdQuantityN
			// 
			this->lblProdQuantityN->AutoSize = true;
			this->lblProdQuantityN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblProdQuantityN->Location = System::Drawing::Point(120, 339);
			this->lblProdQuantityN->Name = L"lblProdQuantityN";
			this->lblProdQuantityN->Size = System::Drawing::Size(66, 29);
			this->lblProdQuantityN->TabIndex = 8;
			this->lblProdQuantityN->Text = L"PQN";
			// 
			// lblOrder
			// 
			this->lblOrder->AutoSize = true;
			this->lblOrder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOrder->Location = System::Drawing::Point(429, 171);
			this->lblOrder->Name = L"lblOrder";
			this->lblOrder->Size = System::Drawing::Size(32, 29);
			this->lblOrder->TabIndex = 12;
			this->lblOrder->Text = L"O";
			// 
			// lblPart
			// 
			this->lblPart->AutoSize = true;
			this->lblPart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPart->Location = System::Drawing::Point(429, 225);
			this->lblPart->Name = L"lblPart";
			this->lblPart->Size = System::Drawing::Size(29, 29);
			this->lblPart->TabIndex = 13;
			this->lblPart->Text = L"P";
			// 
			// lblOrderQuantity
			// 
			this->lblOrderQuantity->AutoSize = true;
			this->lblOrderQuantity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOrderQuantity->Location = System::Drawing::Point(429, 282);
			this->lblOrderQuantity->Name = L"lblOrderQuantity";
			this->lblOrderQuantity->Size = System::Drawing::Size(51, 29);
			this->lblOrderQuantity->TabIndex = 14;
			this->lblOrderQuantity->Text = L"OQ";
			// 
			// lblProdQuantity
			// 
			this->lblProdQuantity->AutoSize = true;
			this->lblProdQuantity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblProdQuantity->Location = System::Drawing::Point(429, 339);
			this->lblProdQuantity->Name = L"lblProdQuantity";
			this->lblProdQuantity->Size = System::Drawing::Size(48, 29);
			this->lblProdQuantity->TabIndex = 15;
			this->lblProdQuantity->Text = L"PQ";
			// 
			// btnPurge
			// 
			this->btnPurge->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPurge->Location = System::Drawing::Point(264, 696);
			this->btnPurge->Name = L"btnPurge";
			this->btnPurge->Size = System::Drawing::Size(225, 66);
			this->btnPurge->TabIndex = 23;
			this->btnPurge->UseVisualStyleBackColor = true;
			this->btnPurge->Click += gcnew System::EventHandler(this, &ProdScreen::btnPurge_Click);
			// 
			// lblYield
			// 
			this->lblYield->AutoSize = true;
			this->lblYield->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblYield->Location = System::Drawing::Point(411, 245);
			this->lblYield->Name = L"lblYield";
			this->lblYield->Size = System::Drawing::Size(25, 29);
			this->lblYield->TabIndex = 25;
			this->lblYield->Text = L": ";
			// 
			// lblYieldN
			// 
			this->lblYieldN->AutoSize = true;
			this->lblYieldN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblYieldN->Location = System::Drawing::Point(96, 245);
			this->lblYieldN->Name = L"lblYieldN";
			this->lblYieldN->Size = System::Drawing::Size(69, 29);
			this->lblYieldN->TabIndex = 24;
			this->lblYieldN->Text = L"Yield";
			// 
			// lblGoodQuantity
			// 
			this->lblGoodQuantity->AutoSize = true;
			this->lblGoodQuantity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblGoodQuantity->Location = System::Drawing::Point(411, 95);
			this->lblGoodQuantity->Name = L"lblGoodQuantity";
			this->lblGoodQuantity->Size = System::Drawing::Size(19, 29);
			this->lblGoodQuantity->TabIndex = 27;
			this->lblGoodQuantity->Text = L":";
			this->lblGoodQuantity->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblGoodQuantityN
			// 
			this->lblGoodQuantityN->AutoSize = true;
			this->lblGoodQuantityN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblGoodQuantityN->Location = System::Drawing::Point(96, 95);
			this->lblGoodQuantityN->Name = L"lblGoodQuantityN";
			this->lblGoodQuantityN->Size = System::Drawing::Size(68, 29);
			this->lblGoodQuantityN->TabIndex = 26;
			this->lblGoodQuantityN->Text = L"GQN";
			// 
			// lblRejectQuantity
			// 
			this->lblRejectQuantity->AutoSize = true;
			this->lblRejectQuantity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRejectQuantity->Location = System::Drawing::Point(411, 170);
			this->lblRejectQuantity->Name = L"lblRejectQuantity";
			this->lblRejectQuantity->Size = System::Drawing::Size(19, 29);
			this->lblRejectQuantity->TabIndex = 29;
			this->lblRejectQuantity->Text = L":";
			this->lblRejectQuantity->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblRejectQuantityN
			// 
			this->lblRejectQuantityN->AutoSize = true;
			this->lblRejectQuantityN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRejectQuantityN->Location = System::Drawing::Point(96, 170);
			this->lblRejectQuantityN->Name = L"lblRejectQuantityN";
			this->lblRejectQuantityN->Size = System::Drawing::Size(67, 29);
			this->lblRejectQuantityN->TabIndex = 28;
			this->lblRejectQuantityN->Text = L"RQN";
			// 
			// gbProdDateN
			// 
			this->gbProdDateN->Controls->Add(this->lblProdTime);
			this->gbProdDateN->Controls->Add(this->lblProdTimeN);
			this->gbProdDateN->Controls->Add(this->lblEndProdDate);
			this->gbProdDateN->Controls->Add(this->lblEndProdDateN);
			this->gbProdDateN->Controls->Add(this->lblStartProdDate);
			this->gbProdDateN->Controls->Add(this->lblStartProdDateN);
			this->gbProdDateN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbProdDateN->Location = System::Drawing::Point(65, 414);
			this->gbProdDateN->Name = L"gbProdDateN";
			this->gbProdDateN->Size = System::Drawing::Size(656, 243);
			this->gbProdDateN->TabIndex = 32;
			this->gbProdDateN->TabStop = false;
			this->gbProdDateN->Text = L"  HP  ";
			// 
			// lblProdTime
			// 
			this->lblProdTime->AutoSize = true;
			this->lblProdTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblProdTime->Location = System::Drawing::Point(371, 194);
			this->lblProdTime->Name = L"lblProdTime";
			this->lblProdTime->Size = System::Drawing::Size(45, 29);
			this->lblProdTime->TabIndex = 37;
			this->lblProdTime->Text = L"PT";
			// 
			// lblProdTimeN
			// 
			this->lblProdTimeN->AutoSize = true;
			this->lblProdTimeN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblProdTimeN->Location = System::Drawing::Point(56, 194);
			this->lblProdTimeN->Name = L"lblProdTimeN";
			this->lblProdTimeN->Size = System::Drawing::Size(63, 29);
			this->lblProdTimeN->TabIndex = 36;
			this->lblProdTimeN->Text = L"PTN";
			// 
			// lblEndProdDate
			// 
			this->lblEndProdDate->AutoSize = true;
			this->lblEndProdDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblEndProdDate->Location = System::Drawing::Point(371, 137);
			this->lblEndProdDate->Name = L"lblEndProdDate";
			this->lblEndProdDate->Size = System::Drawing::Size(45, 29);
			this->lblEndProdDate->TabIndex = 35;
			this->lblEndProdDate->Text = L"EP";
			// 
			// lblEndProdDateN
			// 
			this->lblEndProdDateN->AutoSize = true;
			this->lblEndProdDateN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblEndProdDateN->Location = System::Drawing::Point(56, 137);
			this->lblEndProdDateN->Name = L"lblEndProdDateN";
			this->lblEndProdDateN->Size = System::Drawing::Size(63, 29);
			this->lblEndProdDateN->TabIndex = 34;
			this->lblEndProdDateN->Text = L"EPN";
			// 
			// lblStartProdDate
			// 
			this->lblStartProdDate->AutoSize = true;
			this->lblStartProdDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStartProdDate->Location = System::Drawing::Point(371, 74);
			this->lblStartProdDate->Name = L"lblStartProdDate";
			this->lblStartProdDate->Size = System::Drawing::Size(45, 29);
			this->lblStartProdDate->TabIndex = 33;
			this->lblStartProdDate->Text = L"SP";
			// 
			// lblStartProdDateN
			// 
			this->lblStartProdDateN->AutoSize = true;
			this->lblStartProdDateN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStartProdDateN->Location = System::Drawing::Point(56, 74);
			this->lblStartProdDateN->Name = L"lblStartProdDateN";
			this->lblStartProdDateN->Size = System::Drawing::Size(63, 29);
			this->lblStartProdDateN->TabIndex = 32;
			this->lblStartProdDateN->Text = L"SPN";
			// 
			// btnReject
			// 
			this->btnReject->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnReject->Location = System::Drawing::Point(1283, 696);
			this->btnReject->Name = L"btnReject";
			this->btnReject->Size = System::Drawing::Size(225, 66);
			this->btnReject->TabIndex = 33;
			this->btnReject->UseVisualStyleBackColor = true;
			this->btnReject->Click += gcnew System::EventHandler(this, &ProdScreen::btnReject_Click);
			// 
			// btnRTPearling
			// 
			this->btnRTPearling->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRTPearling->Location = System::Drawing::Point(783, 696);
			this->btnRTPearling->Name = L"btnRTPearling";
			this->btnRTPearling->Size = System::Drawing::Size(225, 66);
			this->btnRTPearling->TabIndex = 34;
			this->btnRTPearling->UseVisualStyleBackColor = true;
			this->btnRTPearling->Click += gcnew System::EventHandler(this, &ProdScreen::btnRTPearling_Click);
			// 
			// btnRequestSample
			// 
			this->btnRequestSample->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRequestSample->Location = System::Drawing::Point(1032, 696);
			this->btnRequestSample->Name = L"btnRequestSample";
			this->btnRequestSample->Size = System::Drawing::Size(225, 66);
			this->btnRequestSample->TabIndex = 35;
			this->btnRequestSample->UseVisualStyleBackColor = true;
			this->btnRequestSample->Click += gcnew System::EventHandler(this, &ProdScreen::btnRequestSample_Click);
			// 
			// pbSous
			// 
			this->pbSous->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pbSous->Location = System::Drawing::Point(366, 297);
			this->pbSous->Margin = System::Windows::Forms::Padding(0, 0, 3, 0);
			this->pbSous->Name = L"pbSous";
			this->pbSous->Size = System::Drawing::Size(353, 353);
			this->pbSous->TabIndex = 37;
			this->pbSous->TabStop = false;
			this->pbSous->Visible = false;
			// 
			// pbSus
			// 
			this->pbSus->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pbSus->Location = System::Drawing::Point(5, 297);
			this->pbSus->Margin = System::Windows::Forms::Padding(3, 0, 0, 0);
			this->pbSus->Name = L"pbSus";
			this->pbSus->Size = System::Drawing::Size(353, 353);
			this->pbSus->TabIndex = 36;
			this->pbSus->TabStop = false;
			this->pbSus->Visible = false;
			// 
			// borderPanel1
			// 
			this->borderPanel1->BorderSize = 3;
			this->borderPanel1->Controls->Add(this->pbSus);
			this->borderPanel1->Controls->Add(this->pbSous);
			this->borderPanel1->Controls->Add(this->lblGoodQuantityN);
			this->borderPanel1->Controls->Add(this->lblYieldN);
			this->borderPanel1->Controls->Add(this->lblRejectQuantity);
			this->borderPanel1->Controls->Add(this->lblYield);
			this->borderPanel1->Controls->Add(this->lblRejectQuantityN);
			this->borderPanel1->Controls->Add(this->lblGoodQuantity);
			this->borderPanel1->DisplayBorder = true;
			this->borderPanel1->Location = System::Drawing::Point(783, 30);
			this->borderPanel1->Name = L"borderPanel1";
			this->borderPanel1->Size = System::Drawing::Size(723, 654);
			this->borderPanel1->TabIndex = 38;
			// 
			// borderPanel2
			// 
			this->borderPanel2->BorderSize = 3;
			this->borderPanel2->DisplayBorder = true;
			this->borderPanel2->Location = System::Drawing::Point(30, 30);
			this->borderPanel2->Name = L"borderPanel2";
			this->borderPanel2->Size = System::Drawing::Size(723, 654);
			this->borderPanel2->TabIndex = 39;
			// 
			// ProdScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->btnRequestSample);
			this->Controls->Add(this->btnRTPearling);
			this->Controls->Add(this->btnReject);
			this->Controls->Add(this->gbProdDateN);
			this->Controls->Add(this->btnPurge);
			this->Controls->Add(this->lblProdQuantity);
			this->Controls->Add(this->lblOrderQuantity);
			this->Controls->Add(this->lblPart);
			this->Controls->Add(this->lblOrder);
			this->Controls->Add(this->lblProdQuantityN);
			this->Controls->Add(this->lblOrderQuantityN);
			this->Controls->Add(this->lblPartN);
			this->Controls->Add(this->lblOrderN);
			this->Controls->Add(this->lblProductivity);
			this->Controls->Add(this->btnNewOrder);
			this->Controls->Add(this->btnCloseOrder);
			this->Controls->Add(this->lblCurrentOrder);
			this->Controls->Add(this->borderPanel1);
			this->Controls->Add(this->borderPanel2);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"ProdScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Load += gcnew System::EventHandler(this, &ProdScreen::ProdScreen_Load);
			this->VisibleChanged += gcnew System::EventHandler(this, &ProdScreen::ProdScreen_VisibleChanged);
			this->gbProdDateN->ResumeLayout(false);
			this->gbProdDateN->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSous))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSus))->EndInit();
			this->borderPanel1->ResumeLayout(false);
			this->borderPanel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnNewLot_Click(System::Object^  sender, System::EventArgs^  e) {
			pT_NewOrderForm->ShowDialog();
			SetImage(pbSus, ProductionOrder::GetPartImage(0));
			SetImage(pbSous, ProductionOrder::GetPartImage(1));
		}

		void SetImage(PictureBox ^ pbImage, Bitmap^ pData)
		{
			if (pData == nullptr)
			{
				pbImage->Visible = false;
				return;
			}
			pbImage->BackgroundImage = pData;
			pbImage->Visible = true;
		}

private: System::Void btnCloseLot_Click(System::Object^  sender, System::EventArgs^  e) {
			MyMsgBox^ pT_l_ValidateClose = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::SureToCloseOrder),TUtilities::pS_LoadString(TextIndex::ValidateReq),MessageBoxButtons::YesNo);
			pT_l_ValidateClose->ShowDialog();
			if (1 == pT_l_ValidateClose->iPressedButton)
			{
				String^ pS_l_LogString = String::Format(TUtilities::pS_LoadString(TextIndex::CloseOrder) + " {0}",ProductionOrder::pS_GetName());
				TLogger::AddLog(pS_l_LogString);
				TJobLogger::CloseLog();
				ProductionOrder::CloseOrder();
				SetTCData(b_CloseJob);
			}
		}
private: System::Void ProdScreen_Load(System::Object^  sender, System::EventArgs^  e) {
			 btnCloseOrder->Enabled = (ProductionOrder::b_OrderStarted());
			 btnNewOrder->Enabled = !(ProductionOrder::b_OrderStarted());
		 }
private: System::Void btnPurge_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::Purge));
			SetTCData(s_ModeReq.MMM_Purge);
		 }
private: System::Void ProdScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			lblCurrentOrder->Text = TUtilities::pS_LoadString(TextIndex::CurrentOrder);
			btnCloseOrder->Text = TUtilities::pS_LoadString(TextIndex::CloseOrder);
			btnNewOrder->Text = TUtilities::pS_LoadString(TextIndex::NewOrder);
			btnReject->Text = TUtilities::pS_LoadString(TextIndex::Reject);
			btnRTPearling->Text = TUtilities::pS_LoadString(TextIndex::RTPearling);
			lblProductivity->Text = TUtilities::pS_LoadString(TextIndex::Productivity);
			lblOrderN->Text = TUtilities::pS_LoadString(TextIndex::Order);
			lblPartN->Text = TUtilities::pS_LoadString(TextIndex::Part);
			lblOrderQuantityN->Text = TUtilities::pS_LoadString(TextIndex::OrderQuantity);
			lblProdQuantityN->Text = TUtilities::pS_LoadString(TextIndex::ProdQuantity);
			lblGoodQuantityN->Text = TUtilities::pS_LoadString(TextIndex::GoodQuantity);
			lblRejectQuantityN->Text = TUtilities::pS_LoadString(TextIndex::RejectQuantity);
			lblYieldN->Text = TUtilities::pS_LoadString(TextIndex::Yield);
			btnPurge->Text = TUtilities::pS_LoadString(TextIndex::Purge);
			gbProdDateN->Text = "  " + TUtilities::pS_LoadString(TextIndex::ProdDate) + "  ";
			lblStartProdDateN->Text = TUtilities::pS_LoadString(TextIndex::Beginning);
			lblEndProdDateN->Text = TUtilities::pS_LoadString(TextIndex::End);
			btnRequestSample->Text = TUtilities::pS_LoadString(TextIndex::Sample);
			lblProdTimeN->Text = TUtilities::pS_LoadString(TextIndex::Time);
		 }
private: System::Void btnReject_Click(System::Object^  sender, System::EventArgs^  e) {
			pT_RejectScreen->ShowDialog();
		 }
private: System::Void btnRTPearling_Click(System::Object^  sender, System::EventArgs^  e) {
			pT_RTPearlingScreen->ShowDialog();
		 }
private: System::Void btnRequestSample_Click(System::Object^  sender, System::EventArgs^  e) {
	TC_BOOL b_l_Status;
		
	ReadTCData(s_MachineOpt.MO_AutoSampling, b_l_Status);
	if (b_l_Status != 0)
	{
		pT_AutoSamplingScreen->ShowDialog();
	}
	else
	{
		TLogger::AddManualLog(this->Text + " : " + TUtilities::pS_LoadString(TextIndex::Sample));
		SetTCData(s_ProductionCmd.PC_RequestSample);
	}
}
};
}
