#pragma once

#include "TTwincatInterface.h"
#include "MyMsgBox.h"
#include "global.h"
#include "TUtilities.h"
#include "AlarmScreen.h"
#include "TLogger.h"
#include "TJobLogger.h"
#include "RejectScreen.h"
#include <memory.h>

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
	public ref class NewOrder : public System::Windows::Forms::Form
	{
	public:
		NewOrder(RejectScreen^ pT_x_RejectScreen)
		{
			Dictionary<String^, array<String^>^>^ apS_l_CheckListText;
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_RejectScreen = pT_x_RejectScreen;
			try
			{
				clsCheckList->Items->Clear();
				clsCheckList->Visible = true;
				apS_l_CheckListText = TUtilities::LoadTranslation(C_APP_CONFIG_PATH + "CheckList.csv");
				//array<String^>^ aList = File::ReadAllLines(C_APP_CONFIG_PATH + "CheckList.txt");
				if (apS_l_CheckListText->Count > 0)
				{
					for each (KeyValuePair<String^, array<String^>^> item in apS_l_CheckListText)
					{
						clsCheckList->Items->Add(item.Value[i_g_LanguageNb]);
					}
					btnValidate->Enabled = false;
				}
				
				/*if (apS_l_CheckListText[i_g_LanguageNb]->Length > 0)
				{
					clsCheckList->Items->AddRange(aList);
					btnValidate->Enabled = false;
				}*/
				else
				{
					clsCheckList->Visible = false;
					btnValidate->Enabled = true;
				}
			}
			catch (...)
			{
				clsCheckList->Items->Clear();
				clsCheckList->Visible = false;
				btnValidate->Enabled = true;
			}

		}
	private: MondemaComponents::CheckedListBoxHeightItem^  clsCheckList;
	private: System::Windows::Forms::Button^  btnValidateConfig;
	private: System::Windows::Forms::Label^  lblBottomRightWeight;
	private: System::Windows::Forms::Label^  lblBottomLeftWeight;
	private: System::Windows::Forms::Label^  lblBottomWeight;
	public:
		// Our specific functions
	private:
		RejectScreen^ pT_RejectScreen;

		void ClearUI(void);
		void LoadConfiguration(String^ pS_x_FileName);

		String^ FormatWeight(TC_PEARLING_DATA_HEAD *stPearlingData)
		{
			if (stPearlingData == nullptr)
			{
				return "-";
			}
			TC_INT iWeight = stPearlingData->PDH_Weight;
			TC_INT iDispersion = stPearlingData->PDH_DispersionZ;

			if (iWeight == 0)
				return "-";
			if (iDispersion == 0)
				return iWeight.ToString() + " [g]";
			else
				return iWeight.ToString() + " [g] ± " + iDispersion.ToString() + " %";
		}

		String^ FormatStick(String^ sText)
		{
			if (String::IsNullOrEmpty(sText)) return "-";
			return sText;
		}

		String^ FormatDiameter(String^ sText)
		{
			if (String::IsNullOrEmpty(sText)) return "-";
			double dDiameter = Convert::ToDouble(sText);
			return dDiameter.ToString("F1");
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

		Bitmap^ TransformImage(PictureBox ^ pbImage, String^ sData)
		{
			Image^ po_Image = Base64StringToImage(sData);
			if (po_Image == nullptr)
			{
				return nullptr;
			}
			try
			{
				const double m_dBaseSizeInMm = 35;
				const double d_ZoomRatio = 1.0;
				Bitmap^ po_OutImage = gcnew Bitmap(pbImage->Width, pbImage->Height);
				Graphics^ pT_l_Graphics = Graphics::FromImage(po_OutImage);
				double m_dBaseResolution = ((double)po_OutImage->Height / m_dBaseSizeInMm) * 25.4;

				double dSrcSizeX = PixelToMm(po_Image->Width, po_Image->HorizontalResolution);
				double dSrcSizeY = PixelToMm(po_Image->Height, po_Image->VerticalResolution);
				double dDstSizeX = PixelToMm(po_OutImage->Width, m_dBaseResolution * d_ZoomRatio);
				double dDstSizeY = PixelToMm(po_OutImage->Height, m_dBaseResolution * d_ZoomRatio);
				double dSrcPosX = 0;
				double dSrcPosY = 0;
				double dDesPosX = 0;
				double dDesPosY = 0;

				if (dSrcSizeX > dDstSizeX)
				{
					dSrcPosX = (dSrcSizeX - dDstSizeX) / 2;
					dSrcSizeX = dDstSizeX;
				}
				else if (dDstSizeX > dSrcSizeX)
				{
					dDesPosX = (dDstSizeX - dSrcSizeX) / 2;
					dDstSizeX = dSrcSizeX;
				}
				if (dSrcSizeY > dDstSizeY)
				{
					dSrcPosY = (dSrcSizeY - dDstSizeY) / 2;
					dSrcSizeY = dDstSizeY;
				}
				else if (dDstSizeY > dSrcSizeY)
				{
					dDesPosY = (dDstSizeY - dSrcSizeY) / 2;
					dDstSizeY = dSrcSizeY;
				}
				pT_l_Graphics->FillRectangle(Brushes::White, 0, 0, po_OutImage->Width, po_OutImage->Height);

				Rectangle rDes((int)MmToPixel(dDesPosX, m_dBaseResolution * d_ZoomRatio), (int)MmToPixel(dDesPosY, m_dBaseResolution * d_ZoomRatio), (int)MmToPixel(dDstSizeX, m_dBaseResolution * d_ZoomRatio), (int)MmToPixel(dDstSizeY, m_dBaseResolution * d_ZoomRatio));
				Rectangle rSrc((int)MmToPixel(dSrcPosX, po_Image->HorizontalResolution), (int)MmToPixel(dSrcPosY, po_Image->VerticalResolution), (int)MmToPixel(dSrcSizeX, po_Image->HorizontalResolution), (int)MmToPixel(dSrcSizeY, po_Image->VerticalResolution));
				pT_l_Graphics->DrawImage(po_Image, rDes, rSrc, GraphicsUnit::Pixel);
				return po_OutImage;
			}
			catch (...)
			{
				return nullptr;
			}
		}

		double PixelToMm(double dValue, double dResolution)
		{
			return dValue / (dResolution / 25.4);
		}

		double MmToPixel(double dValue, double dResolution)
		{
			return (dResolution / 25.4) * dValue;
		}
	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~NewOrder()
		{

			if (components)
			{
				delete components;
			}
		}
	protected: 
	private: System::Windows::Forms::Label^  lblNewOrder;
	private: System::Windows::Forms::Label^  lblInformations;
	private: System::Windows::Forms::Button^  btnValidate;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  lblOrderN;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  lblPartN;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  lblQtyN;
	private: System::Windows::Forms::TextBox^  tbOrder;
	private: System::Windows::Forms::MaskedTextBox^  tbQuantity;
	private: System::Windows::Forms::Label^  lblPart;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape3;
	private: System::Windows::Forms::Label^  lblLastAlarm;
	private: System::Windows::Forms::Label^  lblConfigN;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  tbConfiguration;
	private: System::Windows::Forms::Button^  btnSelectCggFile;
	private: System::Windows::Forms::Label^  lblLeftStick;
	private: System::Windows::Forms::Label^  lblRightStick;
	private: System::Windows::Forms::Label^  lblLeftDiameter;
	private: System::Windows::Forms::Label^  lblRightDiameter;
	private: System::Windows::Forms::Label^  lblTopLeftWeight;
	private: System::Windows::Forms::Label^  lblTopRightWeight;
	private: MondemaComponents::BorderPanel^  borderPanel1;
	private: MondemaComponents::BorderPanel^  borderPanel2;
	private: MondemaComponents::RoundedBorderPanel^  roundedBorderPanel1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;


	private: System::Windows::Forms::Label^  lblRight;
	private: System::Windows::Forms::Label^  lblLeft;
	private: System::Windows::Forms::Label^  lblTopWeight;
	private: System::Windows::Forms::Label^  lblDiameter;
	private: System::Windows::Forms::Label^  lblStick;

	private: System::Windows::Forms::PictureBox^  pbSous;
	private: System::Windows::Forms::PictureBox^  pbSus;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(NewOrder::typeid));
			this->lblInformations = (gcnew System::Windows::Forms::Label());
			this->btnValidate = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->lblLastAlarm = (gcnew System::Windows::Forms::Label());
			this->borderPanel1 = (gcnew MondemaComponents::BorderPanel());
			this->btnValidateConfig = (gcnew System::Windows::Forms::Button());
			this->clsCheckList = (gcnew MondemaComponents::CheckedListBoxHeightItem());
			this->btnSelectCggFile = (gcnew System::Windows::Forms::Button());
			this->lblNewOrder = (gcnew System::Windows::Forms::Label());
			this->tbConfiguration = (gcnew System::Windows::Forms::TextBox());
			this->tbOrder = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->lblOrderN = (gcnew System::Windows::Forms::Label());
			this->lblConfigN = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tbQuantity = (gcnew System::Windows::Forms::MaskedTextBox());
			this->lblPart = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lblQtyN = (gcnew System::Windows::Forms::Label());
			this->lblPartN = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->borderPanel2 = (gcnew MondemaComponents::BorderPanel());
			this->pbSous = (gcnew System::Windows::Forms::PictureBox());
			this->pbSus = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->lblTopWeight = (gcnew System::Windows::Forms::Label());
			this->lblDiameter = (gcnew System::Windows::Forms::Label());
			this->lblStick = (gcnew System::Windows::Forms::Label());
			this->lblRight = (gcnew System::Windows::Forms::Label());
			this->lblTopRightWeight = (gcnew System::Windows::Forms::Label());
			this->lblLeftDiameter = (gcnew System::Windows::Forms::Label());
			this->lblTopLeftWeight = (gcnew System::Windows::Forms::Label());
			this->lblLeftStick = (gcnew System::Windows::Forms::Label());
			this->lblRightStick = (gcnew System::Windows::Forms::Label());
			this->lblRightDiameter = (gcnew System::Windows::Forms::Label());
			this->lblLeft = (gcnew System::Windows::Forms::Label());
			this->roundedBorderPanel1 = (gcnew MondemaComponents::RoundedBorderPanel());
			this->lblBottomRightWeight = (gcnew System::Windows::Forms::Label());
			this->lblBottomLeftWeight = (gcnew System::Windows::Forms::Label());
			this->lblBottomWeight = (gcnew System::Windows::Forms::Label());
			this->borderPanel1->SuspendLayout();
			this->borderPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSous))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSus))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// lblInformations
			// 
			this->lblInformations->AutoEllipsis = true;
			this->lblInformations->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblInformations->Location = System::Drawing::Point(791, 38);
			this->lblInformations->Name = L"lblInformations";
			this->lblInformations->Size = System::Drawing::Size(708, 60);
			this->lblInformations->TabIndex = 3;
			this->lblInformations->Text = L"Information";
			this->lblInformations->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnValidate
			// 
			this->btnValidate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnValidate->Location = System::Drawing::Point(1660, 40);
			this->btnValidate->Name = L"btnValidate";
			this->btnValidate->Size = System::Drawing::Size(225, 66);
			this->btnValidate->TabIndex = 4;
			this->btnValidate->Text = L"Validate";
			this->btnValidate->UseVisualStyleBackColor = true;
			this->btnValidate->Click += gcnew System::EventHandler(this, &NewOrder::btnValidate_Click);
			// 
			// btnCancel
			// 
			this->btnCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCancel->Location = System::Drawing::Point(1660, 105);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(225, 66);
			this->btnCancel->TabIndex = 5;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Click += gcnew System::EventHandler(this, &NewOrder::btnCancel_Click);
			// 
			// lblLastAlarm
			// 
			this->lblLastAlarm->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLastAlarm->ForeColor = System::Drawing::Color::Red;
			this->lblLastAlarm->Location = System::Drawing::Point(20, 1002);
			this->lblLastAlarm->Name = L"lblLastAlarm";
			this->lblLastAlarm->Size = System::Drawing::Size(1872, 70);
			this->lblLastAlarm->TabIndex = 26;
			this->lblLastAlarm->Text = L"...";
			this->lblLastAlarm->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// borderPanel1
			// 
			this->borderPanel1->BorderSize = 3;
			this->borderPanel1->Controls->Add(this->btnValidateConfig);
			this->borderPanel1->Controls->Add(this->clsCheckList);
			this->borderPanel1->Controls->Add(this->btnSelectCggFile);
			this->borderPanel1->Controls->Add(this->lblNewOrder);
			this->borderPanel1->Controls->Add(this->tbConfiguration);
			this->borderPanel1->Controls->Add(this->tbOrder);
			this->borderPanel1->Controls->Add(this->label15);
			this->borderPanel1->Controls->Add(this->lblOrderN);
			this->borderPanel1->Controls->Add(this->lblConfigN);
			this->borderPanel1->Controls->Add(this->label10);
			this->borderPanel1->Controls->Add(this->tbQuantity);
			this->borderPanel1->Controls->Add(this->lblPart);
			this->borderPanel1->Controls->Add(this->label4);
			this->borderPanel1->Controls->Add(this->lblQtyN);
			this->borderPanel1->Controls->Add(this->lblPartN);
			this->borderPanel1->Controls->Add(this->label6);
			this->borderPanel1->DisplayBorder = true;
			this->borderPanel1->Location = System::Drawing::Point(36, 30);
			this->borderPanel1->Name = L"borderPanel1";
			this->borderPanel1->Size = System::Drawing::Size(723, 924);
			this->borderPanel1->TabIndex = 56;
			// 
			// btnValidateConfig
			// 
			this->btnValidateConfig->BackColor = System::Drawing::SystemColors::Window;
			this->btnValidateConfig->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->btnValidateConfig->FlatAppearance->BorderSize = 0;
			this->btnValidateConfig->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnValidateConfig->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnValidateConfig.Image")));
			this->btnValidateConfig->Location = System::Drawing::Point(542, 320);
			this->btnValidateConfig->Name = L"btnValidateConfig";
			this->btnValidateConfig->Size = System::Drawing::Size(72, 66);
			this->btnValidateConfig->TabIndex = 48;
			this->btnValidateConfig->UseVisualStyleBackColor = false;
			this->btnValidateConfig->Click += gcnew System::EventHandler(this, &NewOrder::btnValidateConfig_Click);
			// 
			// clsCheckList
			// 
			this->clsCheckList->CheckOnClick = true;
			this->clsCheckList->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->clsCheckList->FormattingEnabled = true;
			this->clsCheckList->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"test", L"test" });
			this->clsCheckList->ItemSize = 40;
			this->clsCheckList->Location = System::Drawing::Point(84, 414);
			this->clsCheckList->Name = L"clsCheckList";
			this->clsCheckList->Size = System::Drawing::Size(555, 404);
			this->clsCheckList->TabIndex = 47;
			this->clsCheckList->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &NewOrder::clsCheckList_ItemCheck);
			// 
			// btnSelectCggFile
			// 
			this->btnSelectCggFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSelectCggFile->Location = System::Drawing::Point(623, 320);
			this->btnSelectCggFile->Name = L"btnSelectCggFile";
			this->btnSelectCggFile->Size = System::Drawing::Size(72, 66);
			this->btnSelectCggFile->TabIndex = 46;
			this->btnSelectCggFile->Text = L"...";
			this->btnSelectCggFile->UseVisualStyleBackColor = true;
			this->btnSelectCggFile->Click += gcnew System::EventHandler(this, &NewOrder::btnSelectCggFile_Click);
			// 
			// lblNewOrder
			// 
			this->lblNewOrder->AutoEllipsis = true;
			this->lblNewOrder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblNewOrder->Location = System::Drawing::Point(5, 5);
			this->lblNewOrder->Margin = System::Windows::Forms::Padding(3);
			this->lblNewOrder->Name = L"lblNewOrder";
			this->lblNewOrder->Size = System::Drawing::Size(714, 60);
			this->lblNewOrder->TabIndex = 2;
			this->lblNewOrder->Text = L"NewOrder";
			this->lblNewOrder->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tbConfiguration
			// 
			this->tbConfiguration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbConfiguration->Location = System::Drawing::Point(84, 335);
			this->tbConfiguration->Name = L"tbConfiguration";
			this->tbConfiguration->Size = System::Drawing::Size(449, 35);
			this->tbConfiguration->TabIndex = 45;
			// 
			// tbOrder
			// 
			this->tbOrder->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbOrder->Location = System::Drawing::Point(339, 77);
			this->tbOrder->Name = L"tbOrder";
			this->tbOrder->Size = System::Drawing::Size(300, 35);
			this->tbOrder->TabIndex = 19;
			this->tbOrder->Click += gcnew System::EventHandler(this, &NewOrder::tbLotName_Click);
			// 
			// label15
			// 
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(234, 273);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(30, 30);
			this->label15->TabIndex = 44;
			this->label15->Text = L":";
			// 
			// lblOrderN
			// 
			this->lblOrderN->AutoSize = true;
			this->lblOrderN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblOrderN->Location = System::Drawing::Point(78, 86);
			this->lblOrderN->Name = L"lblOrderN";
			this->lblOrderN->Size = System::Drawing::Size(94, 29);
			this->lblOrderN->TabIndex = 13;
			this->lblOrderN->Text = L"OrderN";
			// 
			// lblConfigN
			// 
			this->lblConfigN->AutoSize = true;
			this->lblConfigN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblConfigN->Location = System::Drawing::Point(78, 273);
			this->lblConfigN->Name = L"lblConfigN";
			this->lblConfigN->Size = System::Drawing::Size(101, 29);
			this->lblConfigN->TabIndex = 43;
			this->lblConfigN->Text = L"ConfigN";
			// 
			// label10
			// 
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(234, 86);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(30, 30);
			this->label10->TabIndex = 14;
			this->label10->Text = L":";
			// 
			// tbQuantity
			// 
			this->tbQuantity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbQuantity->Location = System::Drawing::Point(339, 146);
			this->tbQuantity->Name = L"tbQuantity";
			this->tbQuantity->Size = System::Drawing::Size(129, 35);
			this->tbQuantity->TabIndex = 21;
			this->tbQuantity->Click += gcnew System::EventHandler(this, &NewOrder::tbLotName_Click);
			// 
			// lblPart
			// 
			this->lblPart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPart->Location = System::Drawing::Point(341, 215);
			this->lblPart->Name = L"lblPart";
			this->lblPart->Size = System::Drawing::Size(299, 42);
			this->lblPart->TabIndex = 22;
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(234, 215);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(30, 30);
			this->label4->TabIndex = 16;
			this->label4->Text = L":";
			// 
			// lblQtyN
			// 
			this->lblQtyN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblQtyN->Location = System::Drawing::Point(78, 155);
			this->lblQtyN->Name = L"lblQtyN";
			this->lblQtyN->Size = System::Drawing::Size(150, 30);
			this->lblQtyN->TabIndex = 17;
			this->lblQtyN->Text = L"QtyN";
			// 
			// lblPartN
			// 
			this->lblPartN->AutoSize = true;
			this->lblPartN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPartN->Location = System::Drawing::Point(78, 215);
			this->lblPartN->Name = L"lblPartN";
			this->lblPartN->Size = System::Drawing::Size(74, 29);
			this->lblPartN->TabIndex = 15;
			this->lblPartN->Text = L"PartN";
			// 
			// label6
			// 
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(234, 155);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(30, 30);
			this->label6->TabIndex = 18;
			this->label6->Text = L":";
			// 
			// borderPanel2
			// 
			this->borderPanel2->BorderSize = 3;
			this->borderPanel2->Controls->Add(this->pbSous);
			this->borderPanel2->Controls->Add(this->pbSus);
			this->borderPanel2->Controls->Add(this->tableLayoutPanel1);
			this->borderPanel2->DisplayBorder = true;
			this->borderPanel2->Location = System::Drawing::Point(783, 30);
			this->borderPanel2->Name = L"borderPanel2";
			this->borderPanel2->Size = System::Drawing::Size(723, 924);
			this->borderPanel2->TabIndex = 57;
			// 
			// pbSous
			// 
			this->pbSous->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pbSous->Location = System::Drawing::Point(366, 414);
			this->pbSous->Margin = System::Windows::Forms::Padding(0, 0, 3, 0);
			this->pbSous->Name = L"pbSous";
			this->pbSous->Size = System::Drawing::Size(353, 353);
			this->pbSous->TabIndex = 30;
			this->pbSous->TabStop = false;
			this->pbSous->Visible = false;
			// 
			// pbSus
			// 
			this->pbSus->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pbSus->Location = System::Drawing::Point(5, 414);
			this->pbSus->Margin = System::Windows::Forms::Padding(3, 0, 0, 0);
			this->pbSus->Name = L"pbSus";
			this->pbSus->Size = System::Drawing::Size(353, 353);
			this->pbSus->TabIndex = 29;
			this->pbSus->TabStop = false;
			this->pbSus->Visible = false;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33334F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33334F)));
			this->tableLayoutPanel1->Controls->Add(this->lblTopWeight, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->lblDiameter, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblStick, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblRight, 2, 0);
			this->tableLayoutPanel1->Controls->Add(this->lblBottomRightWeight, 2, 4);
			this->tableLayoutPanel1->Controls->Add(this->lblBottomLeftWeight, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->lblTopRightWeight, 2, 3);
			this->tableLayoutPanel1->Controls->Add(this->lblLeftDiameter, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblTopLeftWeight, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->lblLeftStick, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblRightStick, 2, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblRightDiameter, 2, 2);
			this->tableLayoutPanel1->Controls->Add(this->lblLeft, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->lblBottomWeight, 0, 4);
			this->tableLayoutPanel1->Location = System::Drawing::Point(14, 77);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(701, 189);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// lblTopWeight
			// 
			this->lblTopWeight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTopWeight->AutoSize = true;
			this->lblTopWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTopWeight->Location = System::Drawing::Point(4, 112);
			this->lblTopWeight->Name = L"lblTopWeight";
			this->lblTopWeight->Size = System::Drawing::Size(226, 36);
			this->lblTopWeight->TabIndex = 52;
			this->lblTopWeight->Text = L"TopWeight";
			this->lblTopWeight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblDiameter
			// 
			this->lblDiameter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblDiameter->AutoSize = true;
			this->lblDiameter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDiameter->Location = System::Drawing::Point(4, 75);
			this->lblDiameter->Name = L"lblDiameter";
			this->lblDiameter->Size = System::Drawing::Size(226, 36);
			this->lblDiameter->TabIndex = 51;
			this->lblDiameter->Text = L"Diameter";
			this->lblDiameter->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblStick
			// 
			this->lblStick->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblStick->AutoSize = true;
			this->lblStick->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStick->Location = System::Drawing::Point(4, 38);
			this->lblStick->Name = L"lblStick";
			this->lblStick->Size = System::Drawing::Size(226, 36);
			this->lblStick->TabIndex = 50;
			this->lblStick->Text = L"Stick";
			this->lblStick->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblRight
			// 
			this->lblRight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblRight->AutoSize = true;
			this->lblRight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRight->Location = System::Drawing::Point(470, 1);
			this->lblRight->Name = L"lblRight";
			this->lblRight->Size = System::Drawing::Size(227, 36);
			this->lblRight->TabIndex = 56;
			this->lblRight->Text = L"Right";
			this->lblRight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblTopRightWeight
			// 
			this->lblTopRightWeight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTopRightWeight->AutoSize = true;
			this->lblTopRightWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTopRightWeight->Location = System::Drawing::Point(470, 112);
			this->lblTopRightWeight->Name = L"lblTopRightWeight";
			this->lblTopRightWeight->Size = System::Drawing::Size(227, 36);
			this->lblTopRightWeight->TabIndex = 54;
			this->lblTopRightWeight->Text = L"-";
			this->lblTopRightWeight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLeftDiameter
			// 
			this->lblLeftDiameter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLeftDiameter->AutoSize = true;
			this->lblLeftDiameter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLeftDiameter->Location = System::Drawing::Point(237, 75);
			this->lblLeftDiameter->Name = L"lblLeftDiameter";
			this->lblLeftDiameter->Size = System::Drawing::Size(226, 36);
			this->lblLeftDiameter->TabIndex = 51;
			this->lblLeftDiameter->Text = L"-";
			this->lblLeftDiameter->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblTopLeftWeight
			// 
			this->lblTopLeftWeight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblTopLeftWeight->AutoSize = true;
			this->lblTopLeftWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTopLeftWeight->Location = System::Drawing::Point(237, 112);
			this->lblTopLeftWeight->Name = L"lblTopLeftWeight";
			this->lblTopLeftWeight->Size = System::Drawing::Size(226, 36);
			this->lblTopLeftWeight->TabIndex = 53;
			this->lblTopLeftWeight->Text = L"-";
			this->lblTopLeftWeight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLeftStick
			// 
			this->lblLeftStick->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLeftStick->AutoSize = true;
			this->lblLeftStick->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLeftStick->Location = System::Drawing::Point(237, 38);
			this->lblLeftStick->Name = L"lblLeftStick";
			this->lblLeftStick->Size = System::Drawing::Size(226, 36);
			this->lblLeftStick->TabIndex = 49;
			this->lblLeftStick->Text = L"-";
			this->lblLeftStick->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblRightStick
			// 
			this->lblRightStick->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblRightStick->AutoSize = true;
			this->lblRightStick->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRightStick->Location = System::Drawing::Point(470, 38);
			this->lblRightStick->Name = L"lblRightStick";
			this->lblRightStick->Size = System::Drawing::Size(227, 36);
			this->lblRightStick->TabIndex = 50;
			this->lblRightStick->Text = L"-";
			this->lblRightStick->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblRightDiameter
			// 
			this->lblRightDiameter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblRightDiameter->AutoSize = true;
			this->lblRightDiameter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRightDiameter->Location = System::Drawing::Point(470, 75);
			this->lblRightDiameter->Name = L"lblRightDiameter";
			this->lblRightDiameter->Size = System::Drawing::Size(227, 36);
			this->lblRightDiameter->TabIndex = 52;
			this->lblRightDiameter->Text = L"-";
			this->lblRightDiameter->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLeft
			// 
			this->lblLeft->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblLeft->AutoSize = true;
			this->lblLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLeft->Location = System::Drawing::Point(237, 1);
			this->lblLeft->Name = L"lblLeft";
			this->lblLeft->Size = System::Drawing::Size(226, 36);
			this->lblLeft->TabIndex = 55;
			this->lblLeft->Text = L"Left";
			this->lblLeft->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// roundedBorderPanel1
			// 
			this->roundedBorderPanel1->BorderCornerRadius = 12;
			this->roundedBorderPanel1->DisplayBorder = true;
			this->roundedBorderPanel1->Location = System::Drawing::Point(4, 995);
			this->roundedBorderPanel1->Name = L"roundedBorderPanel1";
			this->roundedBorderPanel1->Size = System::Drawing::Size(1912, 85);
			this->roundedBorderPanel1->TabIndex = 59;
			// 
			// lblBottomRightWeight
			// 
			this->lblBottomRightWeight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblBottomRightWeight->AutoSize = true;
			this->lblBottomRightWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblBottomRightWeight->Location = System::Drawing::Point(470, 149);
			this->lblBottomRightWeight->Name = L"lblBottomRightWeight";
			this->lblBottomRightWeight->Size = System::Drawing::Size(227, 39);
			this->lblBottomRightWeight->TabIndex = 54;
			this->lblBottomRightWeight->Text = L"-";
			this->lblBottomRightWeight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblBottomLeftWeight
			// 
			this->lblBottomLeftWeight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblBottomLeftWeight->AutoSize = true;
			this->lblBottomLeftWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblBottomLeftWeight->Location = System::Drawing::Point(237, 149);
			this->lblBottomLeftWeight->Name = L"lblBottomLeftWeight";
			this->lblBottomLeftWeight->Size = System::Drawing::Size(226, 39);
			this->lblBottomLeftWeight->TabIndex = 54;
			this->lblBottomLeftWeight->Text = L"-";
			this->lblBottomLeftWeight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblBottomWeight
			// 
			this->lblBottomWeight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblBottomWeight->AutoSize = true;
			this->lblBottomWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBottomWeight->Location = System::Drawing::Point(4, 149);
			this->lblBottomWeight->Name = L"lblBottomWeight";
			this->lblBottomWeight->Size = System::Drawing::Size(226, 39);
			this->lblBottomWeight->TabIndex = 57;
			this->lblBottomWeight->Text = L"BottomWeight";
			this->lblBottomWeight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// NewOrder
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1920, 1080);
			this->Controls->Add(this->lblLastAlarm);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnValidate);
			this->Controls->Add(this->lblInformations);
			this->Controls->Add(this->borderPanel1);
			this->Controls->Add(this->borderPanel2);
			this->Controls->Add(this->roundedBorderPanel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"NewOrder";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LotScreen";
			this->Load += gcnew System::EventHandler(this, &NewOrder::NewLot_Load);
			this->VisibleChanged += gcnew System::EventHandler(this, &NewOrder::NewOrder_VisibleChanged);
			this->borderPanel1->ResumeLayout(false);
			this->borderPanel1->PerformLayout();
			this->borderPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSous))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSus))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e) {
				TC_BOOL b_l_Status;

				ReadTCData(s_ModeMask.MMM_Stop,b_l_Status);
				if (b_l_Status)
				{
					TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::StopMachine));
					SetTCData(s_ModeReq.MMM_Stop);
				}
				ClearUI();
				pT_RejectScreen->DrawPlate();
				this->Close();
			 }
private: System::Void cbCheckList_Click(System::Object^  sender, System::EventArgs^  e) {
			 bool b_l_CanValidate = true;

			 // Loop through checkboxes to define if we can validate the holders change
			 for each (Control^ ctrl in this->Controls)
			 {
				if (ctrl->Name->StartsWith("cbCheckList"))
				{
					CheckBox^ chkBox = dynamic_cast<CheckBox^>(ctrl);
					if (chkBox != nullptr)
					{
						if (!chkBox->Checked)
							b_l_CanValidate = false;
					}
				}
			}
			btnValidate->Enabled = b_l_CanValidate;
		 }
private: System::Void NewLot_Load(System::Object^  sender, System::EventArgs^  e) {
			//String^ pS_l_CompleteFileName;
			//String^ pS_l_FileNameWithExt;
			// Get caliber list
			lblPart->Text = "";
			//lblPart->Items->Clear();
			//array<String^>^dirs = Directory::GetFiles(C_APP_REFERENCES_PATH, "*.xml");
			//Collections::IEnumerator^ myEnum = dirs->GetEnumerator();
			//while (myEnum->MoveNext())
			//{
			//	pS_l_CompleteFileName = myEnum->Current->ToString();
			//	pS_l_FileNameWithExt = pS_l_CompleteFileName->Substring(pS_l_CompleteFileName->LastIndexOf("\\") + 1);
			//	lblPart->Items->Add(pS_l_FileNameWithExt->Substring(0,pS_l_FileNameWithExt->LastIndexOf(".")));
			//}
		 }
private: System::Void btnValidate_Click(System::Object^  sender, System::EventArgs^  e) {
			MyMsgBox^ pT_l_ErrorMsg;
			enum JobFileCheckResult e_l_CheckFileResult;
			unsigned long n_l_GoodQty,n_l_TotalQty;
			TimeSpan^ n_o_Duration = TimeSpan::Zero;
			String^ pS_l_StartDate = gcnew String("");
			String^ pS_l_EndDate = gcnew String("");
			int i_l_Qty;

			try
			{
				// Check if a configuration file was given
				if (0 == String::Compare(tbConfiguration->Text,""))
				 {
					pT_l_ErrorMsg = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::NeedConfigFile),TUtilities::pS_LoadString(TextIndex::ValidationError),MessageBoxButtons::OK);
					pT_l_ErrorMsg->ShowDialog();
				 }
				// Check if lot configuration is OK
				 if (0 == String::Compare(tbOrder->Text,""))
				 {
					 pT_l_ErrorMsg = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::IntroduceValidOrder),TUtilities::pS_LoadString(TextIndex::ValidationError),MessageBoxButtons::OK);
					 pT_l_ErrorMsg->ShowDialog();
				 }
				 else if (0 == String::Compare(lblPart->Text,""))
				 {
					pT_l_ErrorMsg = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::IntroduceValidPart),TUtilities::pS_LoadString(TextIndex::ValidationError),MessageBoxButtons::OK);
					pT_l_ErrorMsg->ShowDialog();
				 }
				 else if (!Int32::TryParse(tbQuantity->Text,i_l_Qty))
				 {
					pT_l_ErrorMsg = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::IntroduceValidQuantity),TUtilities::pS_LoadString(TextIndex::ValidationError),MessageBoxButtons::OK);
					pT_l_ErrorMsg->ShowDialog();
				 }
				 else
				 {
					// Check if the order is already started
					e_l_CheckFileResult = TJobLogger::e_GetJobLogData(tbOrder->Text,lblPart->Text,i_l_Qty,&n_l_GoodQty,&n_l_TotalQty,pS_l_StartDate, pS_l_EndDate, n_o_Duration);
					if (JFCR_BadData == e_l_CheckFileResult)
					{
						pT_l_ErrorMsg = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::OrderAlreadyUsed),TUtilities::pS_LoadString(TextIndex::ValidationError),MessageBoxButtons::OK);
						pT_l_ErrorMsg->ShowDialog();
					}
					else
					{
						if (JFCR_OK == e_l_CheckFileResult)
						{
							// Update quantities based on file log
							WriteTCData(s_ProdData.PL_ProdQty,n_l_TotalQty);
							WriteTCData(s_ProdData.PL_GoodQty,n_l_GoodQty);
							String^ pS_l_LogString = String::Format(TUtilities::pS_LoadString(TextIndex::ReopenOrder),tbOrder->Text,n_l_TotalQty.ToString(),tbQuantity->Text,lblPart->Text);
							TLogger::AddLog(pS_l_LogString);
							ProductionOrder::SetName(tbOrder->Text);
							ProductionOrder::SetQuantity(i_l_Qty);
							ProductionOrder::SetStartDate(pS_l_StartDate);
							ProductionOrder::SetEndDate(pS_l_EndDate);
							WriteTCData(s_ProdData.PL_LotQty,(TC_DWORD)i_l_Qty);
							WriteTCData(dw_StartJobElapsedTime, (TC_DWORD)(n_o_Duration->TotalMilliseconds));
							TJobLogger::CreateLog();
						}
						else
						{
							String^ pS_l_LogString = String::Format(TUtilities::pS_LoadString(TextIndex::CreateOrder),tbOrder->Text,tbQuantity->Text,lblPart->Text);
							TLogger::AddLog(pS_l_LogString);
							ProductionOrder::SetName(tbOrder->Text);
							ProductionOrder::SetReference(lblPart->Text);
							ProductionOrder::SetQuantity(i_l_Qty);
							WriteTCData(s_ProdData.PL_LotQty,(TC_DWORD)i_l_Qty);
							WriteTCData(s_ProdData.PL_ProdQty,(TC_DWORD)0);
							WriteTCData(s_ProdData.PL_GoodQty,(TC_DWORD)0);
							WriteTCData(dw_StartJobElapsedTime, (TC_DWORD)0);
							ProductionOrder::SetStartDate("");
							ProductionOrder::SetEndDate("");
							TJobLogger::CreateLog();
						}
						
						// Set new job is active
						SetTCData(b_NewJob);
						btnCancel_Click(sender,e);
						ClearUI();
						pT_RejectScreen->DrawPlate();
						this->Close();
					}
				}
			}
			catch (Exception^)
			{
				pT_l_ErrorMsg = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::EnterValidData),TUtilities::pS_LoadString(TextIndex::ValidationError),MessageBoxButtons::OK);
				pT_l_ErrorMsg->ShowDialog();
			}
		 }
private: System::Void tbLotName_Click(System::Object^  sender, System::EventArgs^  e) {
			 TUtilities::ShowOSK();
		 }
private: System::Void NewOrder_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			lblNewOrder->Text = TUtilities::pS_LoadString(TextIndex::NewOrder);
			lblInformations->Text = TUtilities::pS_LoadString(TextIndex::Informations);
			btnValidate->Text = TUtilities::pS_LoadString(TextIndex::Validate);
			btnCancel->Text = TUtilities::pS_LoadString(TextIndex::Cancel);
			lblOrderN->Text = TUtilities::pS_LoadString(TextIndex::Order);
			lblPartN->Text = TUtilities::pS_LoadString(TextIndex::Part);
			lblQtyN->Text = TUtilities::pS_LoadString(TextIndex::Quantity);
			lblConfigN->Text = TUtilities::pS_LoadString(TextIndex::Config);
			lblLeft->Text = TUtilities::pS_LoadString(TextIndex::Left);
			lblRight->Text = TUtilities::pS_LoadString(TextIndex::Right);
			lblDiameter->Text = TUtilities::pS_LoadString(TextIndex::Diameter);
			lblStick->Text = TUtilities::pS_LoadString(TextIndex::Stick);
			lblTopWeight->Text = TUtilities::pS_LoadString(TextIndex::TopWeight);
			lblBottomWeight->Text = TUtilities::pS_LoadString(TextIndex::BottomWeight);

		 }
private: System::Void cbNoWearStick_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

		 }

private: Image^ Base64StringToImage(String^ sData)
		 {
			 if (String::IsNullOrEmpty(sData)) return nullptr;
			 try
			 {
				 array<Byte>^ aData = Convert::FromBase64String(sData);
				 MemoryStream^ ms = gcnew MemoryStream(aData);
				 Image^ returnImage = Image::FromStream(ms);
				 return returnImage;
			 }
			 catch (...)
			 {
				 return nullptr;
			 }
		 }
private: System::Void btnSelectCggFile_Click(System::Object^  sender, System::EventArgs^  e) {

			// First open dialog box to select the config file

			OpenFileDialog^ pT_l_GetFile2Load = gcnew OpenFileDialog;
			pT_l_GetFile2Load->InitialDirectory = C_APP_REFERENCES_PATH;
			pT_l_GetFile2Load->InitialDirectory = pT_l_GetFile2Load->InitialDirectory->Substring(0, pT_l_GetFile2Load->InitialDirectory->Length - 1);
			pT_l_GetFile2Load->Filter = TUtilities::pS_LoadString(TextIndex::ConfigFiles) + " (*.cfgc)|*.cfgc";
			pT_l_GetFile2Load->FilterIndex = 1;
			pT_l_GetFile2Load->CheckFileExists = true;
			pT_l_GetFile2Load->RestoreDirectory = true;

			if (pT_l_GetFile2Load->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				LoadConfiguration(pT_l_GetFile2Load->FileName);
		 }

private: System::Void clsCheckList_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e) {
	bool bEnable = true;
	
	for (int i = 0; i < clsCheckList->Items->Count; i++)
	{
		if (i == e->Index)
		{
			if (e->NewValue != CheckState::Checked)
			{
				bEnable = false;
				break;

			}
		}
		else if (!clsCheckList->GetItemChecked(i))
		{
			bEnable = false;
			break;
		}
	}
	btnValidate->Enabled = bEnable;
}
private: System::Void btnValidateConfig_Click(System::Object^  sender, System::EventArgs^  e) {
	if ("" != tbConfiguration->Text)
		LoadConfiguration(C_APP_REFERENCES_PATH + tbConfiguration->Text);

}
};
}
