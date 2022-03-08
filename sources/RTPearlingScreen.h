#pragma once

#include "TTwincatInterface.h"
#include "MyMsgBox.h"
#include "global.h"
#include "TUtilities.h"
#include "AlarmScreen.h"
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
	/// Description résumée de LotScreen
	/// </summary>
	public ref class RTPearlingScreen : public System::Windows::Forms::Form
	{
	public:
		RTPearlingScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			ai_d_MaxValue = gcnew array<double, 2>(2, 2);
			ab_Export = gcnew array<bool,2>(2,2);
			ab_Exporting = gcnew array<bool,2>(2,2);
			apT_ExportFile = gcnew array<StreamWriter^,2>(2,2);
			b_ReloadData = false;
			b_NeedCleanup = true;
			for (int i=0;i<2;i++)
			{
				for (int j=0;j<2;j++)
				{
					ai_d_MaxValue[i, j] = 0;
					ab_Export[i,j] = true;
					//ab_Export[i,j] = false;
					ab_Exporting[i,j] = false;
				}
			}
			apT_FaceBaseName = gcnew array<String^,2>(2,2);
			apT_FaceBaseName[0,0] = "TL";
			apT_FaceBaseName[0,1] = "BL";
			apT_FaceBaseName[1,0] = "TR";
			apT_FaceBaseName[1,1] = "BR";

			pbTLGraph->Visible = false;
			pbBLGraph->Visible = false;
			pbTRGraph->Visible = false;
			pbBRGraph->Visible = false;

			chrTLGraph->Series[0]->Points->Clear();
			chrTRGraph->Series[0]->Points->Clear();
			chrBLGraph->Series[0]->Points->Clear();
			chrBRGraph->Series[0]->Points->Clear();
		}
	// Our specific functions
	private:
		array<double, 2>^ ai_d_MaxValue;
		array<bool,2>^ ab_Export;
		array<bool,2>^ ab_Exporting;
		bool b_ReloadData;
		array<StreamWriter^,2>^ apT_ExportFile;
		array<String^,2>^ apT_FaceBaseName;
		bool b_NeedCleanup;
		DateTime t_LastCleanUp;

	private: System::Windows::Forms::PictureBox^  pbBLGraph;

	private: System::Windows::Forms::Label^  lblBLPearlNb;
	private: System::Windows::Forms::Label^  lblBLCorrection_um;
	private: System::Windows::Forms::Panel^  pnlCorrectionColor;
	private: System::Windows::Forms::Label^  lblTRPearlNb;
	private: System::Windows::Forms::PictureBox^  pbTRGraph;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  lblBRPearlNb;
	private: System::Windows::Forms::PictureBox^  pbBRGraph;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  lblTLPearlNb;
	private: System::Windows::Forms::PictureBox^  pbTLGraph;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Panel^  panel6;
	private: System::Windows::Forms::Label^  lblBRCorrection_um;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Label^  lblTRCorrection_um;
	private: System::Windows::Forms::Panel^  panel9;
	private: System::Windows::Forms::Label^  lblTLCorrection_um;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape10;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Button^  btnTLExport;
	private: System::Windows::Forms::Button^  btnTRExport;
	private: System::Windows::Forms::Button^  btnBLExport;
	private: System::Windows::Forms::Button^  btnBRExport;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chrTLGraph;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chrTRGraph;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chrBLGraph;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chrBRGraph;


	public:
		void UpdateUI(void);
	private:	void CleanUpExport();

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~RTPearlingScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape1;
	private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
	private: System::Windows::Forms::Button^  btnClose;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape3;
	private: System::Windows::Forms::Label^  lblLastAlarm;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape5;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape4;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape2;
	private: System::Windows::Forms::Label^  lblBottomLeft;
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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				0));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint2 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(1,
				20));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint3 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(2,
				-5));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint4 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(3,
				-10));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint5 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(50,
				0));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint6 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				0));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint7 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(1,
				20));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint8 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(2,
				-5));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint9 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(3,
				-10));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint10 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(50,
				0));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint11 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				0));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint12 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(1,
				20));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint13 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(2,
				-5));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint14 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(3,
				-10));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint15 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(50,
				0));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint16 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				0));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint17 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(1,
				20));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint18 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(2,
				-5));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint19 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(3,
				-10));
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint20 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(50,
				0));
			this->rectangleShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape10 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape5 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape4 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape2 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape3 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->lblLastAlarm = (gcnew System::Windows::Forms::Label());
			this->lblBottomLeft = (gcnew System::Windows::Forms::Label());
			this->pbBLGraph = (gcnew System::Windows::Forms::PictureBox());
			this->lblBLPearlNb = (gcnew System::Windows::Forms::Label());
			this->lblBLCorrection_um = (gcnew System::Windows::Forms::Label());
			this->pnlCorrectionColor = (gcnew System::Windows::Forms::Panel());
			this->lblTRPearlNb = (gcnew System::Windows::Forms::Label());
			this->pbTRGraph = (gcnew System::Windows::Forms::PictureBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->lblBRPearlNb = (gcnew System::Windows::Forms::Label());
			this->pbBRGraph = (gcnew System::Windows::Forms::PictureBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->lblTLPearlNb = (gcnew System::Windows::Forms::Label());
			this->pbTLGraph = (gcnew System::Windows::Forms::PictureBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->lblBRCorrection_um = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->lblTRCorrection_um = (gcnew System::Windows::Forms::Label());
			this->panel9 = (gcnew System::Windows::Forms::Panel());
			this->lblTLCorrection_um = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->btnTLExport = (gcnew System::Windows::Forms::Button());
			this->btnTRExport = (gcnew System::Windows::Forms::Button());
			this->btnBLExport = (gcnew System::Windows::Forms::Button());
			this->btnBRExport = (gcnew System::Windows::Forms::Button());
			this->chrTLGraph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chrTRGraph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chrBLGraph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chrBRGraph = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBLGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbTRGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBRGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbTLGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrTLGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrTRGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrBLGraph))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrBRGraph))->BeginInit();
			this->SuspendLayout();
			// 
			// rectangleShape1
			// 
			this->rectangleShape1->BorderWidth = 3;
			this->rectangleShape1->Location = System::Drawing::Point(38, 150);
			this->rectangleShape1->Name = L"rectangleShape1";
			this->rectangleShape1->Size = System::Drawing::Size(713, 415);
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(0, 0);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(6) {
				this->rectangleShape10,
					this->rectangleShape5, this->rectangleShape4, this->rectangleShape2, this->rectangleShape3, this->rectangleShape1
			});
			this->shapeContainer1->Size = System::Drawing::Size(1920, 1080);
			this->shapeContainer1->TabIndex = 0;
			this->shapeContainer1->TabStop = false;
			// 
			// rectangleShape10
			// 
			this->rectangleShape10->BorderWidth = 3;
			this->rectangleShape10->Location = System::Drawing::Point(39, 23);
			this->rectangleShape10->Name = L"rectangleShape10";
			this->rectangleShape10->Size = System::Drawing::Size(1218, 84);
			// 
			// rectangleShape5
			// 
			this->rectangleShape5->BorderWidth = 3;
			this->rectangleShape5->Location = System::Drawing::Point(788, 575);
			this->rectangleShape5->Name = L"rectangleShape5";
			this->rectangleShape5->Size = System::Drawing::Size(713, 415);
			// 
			// rectangleShape4
			// 
			this->rectangleShape4->BorderWidth = 3;
			this->rectangleShape4->Location = System::Drawing::Point(38, 575);
			this->rectangleShape4->Name = L"rectangleShape4";
			this->rectangleShape4->Size = System::Drawing::Size(713, 415);
			// 
			// rectangleShape2
			// 
			this->rectangleShape2->BorderWidth = 3;
			this->rectangleShape2->Location = System::Drawing::Point(788, 150);
			this->rectangleShape2->Name = L"rectangleShape2";
			this->rectangleShape2->Size = System::Drawing::Size(713, 415);
			// 
			// rectangleShape3
			// 
			this->rectangleShape3->CornerRadius = 6;
			this->rectangleShape3->Location = System::Drawing::Point(1, 995);
			this->rectangleShape3->Name = L"rectangleShape3";
			this->rectangleShape3->SelectionColor = System::Drawing::Color::GreenYellow;
			this->rectangleShape3->Size = System::Drawing::Size(1578, 84);
			// 
			// btnClose
			// 
			this->btnClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClose->Location = System::Drawing::Point(1658, 12);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(225, 66);
			this->btnClose->TabIndex = 5;
			this->btnClose->Text = L"Quitter";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &RTPearlingScreen::btnClose_Click);
			// 
			// lblLastAlarm
			// 
			this->lblLastAlarm->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLastAlarm->ForeColor = System::Drawing::Color::Red;
			this->lblLastAlarm->Location = System::Drawing::Point(20, 1002);
			this->lblLastAlarm->Name = L"lblLastAlarm";
			this->lblLastAlarm->Size = System::Drawing::Size(1538, 68);
			this->lblLastAlarm->TabIndex = 26;
			this->lblLastAlarm->Text = L"...";
			this->lblLastAlarm->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblBottomLeft
			// 
			this->lblBottomLeft->AutoEllipsis = true;
			this->lblBottomLeft->AutoSize = true;
			this->lblBottomLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBottomLeft->Location = System::Drawing::Point(53, 583);
			this->lblBottomLeft->Name = L"lblBottomLeft";
			this->lblBottomLeft->Size = System::Drawing::Size(316, 31);
			this->lblBottomLeft->TabIndex = 28;
			this->lblBottomLeft->Text = L"Broche gauche - SOUS";
			this->lblBottomLeft->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pbBLGraph
			// 
			this->pbBLGraph->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pbBLGraph->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pbBLGraph->Location = System::Drawing::Point(59, 694);
			this->pbBLGraph->Name = L"pbBLGraph";
			this->pbBLGraph->Size = System::Drawing::Size(675, 280);
			this->pbBLGraph->TabIndex = 52;
			this->pbBLGraph->TabStop = false;
			// 
			// lblBLPearlNb
			// 
			this->lblBLPearlNb->AutoSize = true;
			this->lblBLPearlNb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBLPearlNb->Location = System::Drawing::Point(548, 587);
			this->lblBLPearlNb->Name = L"lblBLPearlNb";
			this->lblBLPearlNb->Size = System::Drawing::Size(110, 29);
			this->lblBLPearlNb->TabIndex = 59;
			this->lblBLPearlNb->Text = L"Perle n° :";
			// 
			// lblBLCorrection_um
			// 
			this->lblBLCorrection_um->AutoSize = true;
			this->lblBLCorrection_um->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBLCorrection_um->Location = System::Drawing::Point(423, 643);
			this->lblBLCorrection_um->Name = L"lblBLCorrection_um";
			this->lblBLCorrection_um->Size = System::Drawing::Size(234, 29);
			this->lblBLCorrection_um->TabIndex = 64;
			this->lblBLCorrection_um->Text = L"Compensation [um] :";
			// 
			// pnlCorrectionColor
			// 
			this->pnlCorrectionColor->BackColor = System::Drawing::Color::MediumOrchid;
			this->pnlCorrectionColor->Location = System::Drawing::Point(393, 649);
			this->pnlCorrectionColor->Name = L"pnlCorrectionColor";
			this->pnlCorrectionColor->Size = System::Drawing::Size(24, 24);
			this->pnlCorrectionColor->TabIndex = 57;
			// 
			// lblTRPearlNb
			// 
			this->lblTRPearlNb->AutoSize = true;
			this->lblTRPearlNb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTRPearlNb->Location = System::Drawing::Point(1298, 162);
			this->lblTRPearlNb->Name = L"lblTRPearlNb";
			this->lblTRPearlNb->Size = System::Drawing::Size(110, 29);
			this->lblTRPearlNb->TabIndex = 75;
			this->lblTRPearlNb->Text = L"Perle n° :";
			// 
			// pbTRGraph
			// 
			this->pbTRGraph->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pbTRGraph->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pbTRGraph->Location = System::Drawing::Point(809, 269);
			this->pbTRGraph->Name = L"pbTRGraph";
			this->pbTRGraph->Size = System::Drawing::Size(675, 280);
			this->pbTRGraph->TabIndex = 73;
			this->pbTRGraph->TabStop = false;
			// 
			// label9
			// 
			this->label9->AutoEllipsis = true;
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(803, 158);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(273, 31);
			this->label9->TabIndex = 72;
			this->label9->Text = L"Broche droite - SUS";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblBRPearlNb
			// 
			this->lblBRPearlNb->AutoSize = true;
			this->lblBRPearlNb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBRPearlNb->Location = System::Drawing::Point(1298, 587);
			this->lblBRPearlNb->Name = L"lblBRPearlNb";
			this->lblBRPearlNb->Size = System::Drawing::Size(110, 29);
			this->lblBRPearlNb->TabIndex = 79;
			this->lblBRPearlNb->Text = L"Perle n° :";
			// 
			// pbBRGraph
			// 
			this->pbBRGraph->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pbBRGraph->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pbBRGraph->Location = System::Drawing::Point(809, 694);
			this->pbBRGraph->Name = L"pbBRGraph";
			this->pbBRGraph->Size = System::Drawing::Size(675, 280);
			this->pbBRGraph->TabIndex = 77;
			this->pbBRGraph->TabStop = false;
			// 
			// label12
			// 
			this->label12->AutoEllipsis = true;
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(803, 583);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(295, 31);
			this->label12->TabIndex = 76;
			this->label12->Text = L"Broche droite - SOUS";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblTLPearlNb
			// 
			this->lblTLPearlNb->AutoSize = true;
			this->lblTLPearlNb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTLPearlNb->Location = System::Drawing::Point(548, 162);
			this->lblTLPearlNb->Name = L"lblTLPearlNb";
			this->lblTLPearlNb->Size = System::Drawing::Size(110, 29);
			this->lblTLPearlNb->TabIndex = 83;
			this->lblTLPearlNb->Text = L"Perle n° :";
			// 
			// pbTLGraph
			// 
			this->pbTLGraph->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->pbTLGraph->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pbTLGraph->Location = System::Drawing::Point(59, 269);
			this->pbTLGraph->Name = L"pbTLGraph";
			this->pbTLGraph->Size = System::Drawing::Size(675, 280);
			this->pbTLGraph->TabIndex = 81;
			this->pbTLGraph->TabStop = false;
			// 
			// label15
			// 
			this->label15->AutoEllipsis = true;
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(53, 158);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(294, 31);
			this->label15->TabIndex = 80;
			this->label15->Text = L"Broche gauche - SUS";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// panel6
			// 
			this->panel6->BackColor = System::Drawing::Color::MediumOrchid;
			this->panel6->Location = System::Drawing::Point(1143, 647);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(24, 24);
			this->panel6->TabIndex = 84;
			// 
			// lblBRCorrection_um
			// 
			this->lblBRCorrection_um->AutoSize = true;
			this->lblBRCorrection_um->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblBRCorrection_um->Location = System::Drawing::Point(1173, 643);
			this->lblBRCorrection_um->Name = L"lblBRCorrection_um";
			this->lblBRCorrection_um->Size = System::Drawing::Size(234, 29);
			this->lblBRCorrection_um->TabIndex = 90;
			this->lblBRCorrection_um->Text = L"Compensation [um] :";
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::MediumOrchid;
			this->panel3->Location = System::Drawing::Point(1143, 222);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(24, 24);
			this->panel3->TabIndex = 98;
			// 
			// lblTRCorrection_um
			// 
			this->lblTRCorrection_um->AutoSize = true;
			this->lblTRCorrection_um->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTRCorrection_um->Location = System::Drawing::Point(1173, 218);
			this->lblTRCorrection_um->Name = L"lblTRCorrection_um";
			this->lblTRCorrection_um->Size = System::Drawing::Size(234, 29);
			this->lblTRCorrection_um->TabIndex = 104;
			this->lblTRCorrection_um->Text = L"Compensation [um] :";
			// 
			// panel9
			// 
			this->panel9->BackColor = System::Drawing::Color::MediumOrchid;
			this->panel9->Location = System::Drawing::Point(393, 221);
			this->panel9->Name = L"panel9";
			this->panel9->Size = System::Drawing::Size(24, 24);
			this->panel9->TabIndex = 112;
			// 
			// lblTLCorrection_um
			// 
			this->lblTLCorrection_um->AutoSize = true;
			this->lblTLCorrection_um->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTLCorrection_um->Location = System::Drawing::Point(423, 216);
			this->lblTLCorrection_um->Name = L"lblTLCorrection_um";
			this->lblTLCorrection_um->Size = System::Drawing::Size(234, 29);
			this->lblTLCorrection_um->TabIndex = 118;
			this->lblTLCorrection_um->Text = L"Compensation [um] :";
			// 
			// label26
			// 
			this->label26->AutoEllipsis = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 27, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->Location = System::Drawing::Point(51, 38);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(1206, 60);
			this->label26->TabIndex = 134;
			this->label26->Text = L"Visualisation des paramètres de perlage sensitif";
			this->label26->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnTLExport
			// 
			this->btnTLExport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnTLExport->Location = System::Drawing::Point(59, 207);
			this->btnTLExport->Name = L"btnTLExport";
			this->btnTLExport->Size = System::Drawing::Size(225, 50);
			this->btnTLExport->TabIndex = 135;
			this->btnTLExport->Text = L"Exporter";
			this->btnTLExport->UseVisualStyleBackColor = true;
			this->btnTLExport->Visible = false;
			this->btnTLExport->Click += gcnew System::EventHandler(this, &RTPearlingScreen::btnTLExport_Click);
			// 
			// btnTRExport
			// 
			this->btnTRExport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnTRExport->Location = System::Drawing::Point(809, 207);
			this->btnTRExport->Name = L"btnTRExport";
			this->btnTRExport->Size = System::Drawing::Size(225, 50);
			this->btnTRExport->TabIndex = 136;
			this->btnTRExport->Text = L"Exporter";
			this->btnTRExport->UseVisualStyleBackColor = true;
			this->btnTRExport->Visible = false;
			this->btnTRExport->Click += gcnew System::EventHandler(this, &RTPearlingScreen::btnTRExport_Click);
			// 
			// btnBLExport
			// 
			this->btnBLExport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnBLExport->Location = System::Drawing::Point(59, 632);
			this->btnBLExport->Name = L"btnBLExport";
			this->btnBLExport->Size = System::Drawing::Size(225, 50);
			this->btnBLExport->TabIndex = 137;
			this->btnBLExport->Text = L"Exporter";
			this->btnBLExport->UseVisualStyleBackColor = true;
			this->btnBLExport->Visible = false;
			this->btnBLExport->Click += gcnew System::EventHandler(this, &RTPearlingScreen::btnBLExport_Click);
			// 
			// btnBRExport
			// 
			this->btnBRExport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnBRExport->Location = System::Drawing::Point(809, 632);
			this->btnBRExport->Name = L"btnBRExport";
			this->btnBRExport->Size = System::Drawing::Size(225, 50);
			this->btnBRExport->TabIndex = 138;
			this->btnBRExport->Text = L"Exporter";
			this->btnBRExport->UseVisualStyleBackColor = true;
			this->btnBRExport->Visible = false;
			this->btnBRExport->Click += gcnew System::EventHandler(this, &RTPearlingScreen::btnBRExport_Click);
			// 
			// chrTLGraph
			// 
			chartArea1->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisY->Interval = 25;
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->LogarithmBase = 2;
			chartArea1->AxisY->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisY->Maximum = 50;
			chartArea1->AxisY->Minimum = -50;
			chartArea1->Name = L"chaTLGraph";
			this->chrTLGraph->ChartAreas->Add(chartArea1);
			this->chrTLGraph->Location = System::Drawing::Point(59, 269);
			this->chrTLGraph->Name = L"chrTLGraph";
			series1->ChartArea = L"chaTLGraph";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Name = L"Series1";
			series1->Points->Add(dataPoint1);
			series1->Points->Add(dataPoint2);
			series1->Points->Add(dataPoint3);
			series1->Points->Add(dataPoint4);
			series1->Points->Add(dataPoint5);
			this->chrTLGraph->Series->Add(series1);
			this->chrTLGraph->Size = System::Drawing::Size(675, 280);
			this->chrTLGraph->TabIndex = 139;
			this->chrTLGraph->Text = L"chart1";
			// 
			// chrTRGraph
			// 
			chartArea2->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea2->AxisX->Minimum = 0;
			chartArea2->AxisY->Interval = 25;
			chartArea2->AxisY->IsStartedFromZero = false;
			chartArea2->AxisY->LogarithmBase = 2;
			chartArea2->AxisY->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea2->AxisY->Maximum = 50;
			chartArea2->AxisY->Minimum = -50;
			chartArea2->Name = L"chaTRGraph";
			this->chrTRGraph->ChartAreas->Add(chartArea2);
			this->chrTRGraph->Location = System::Drawing::Point(809, 269);
			this->chrTRGraph->Name = L"chrTRGraph";
			series2->ChartArea = L"chaTRGraph";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Name = L"Series1";
			series2->Points->Add(dataPoint6);
			series2->Points->Add(dataPoint7);
			series2->Points->Add(dataPoint8);
			series2->Points->Add(dataPoint9);
			series2->Points->Add(dataPoint10);
			this->chrTRGraph->Series->Add(series2);
			this->chrTRGraph->Size = System::Drawing::Size(675, 280);
			this->chrTRGraph->TabIndex = 140;
			this->chrTRGraph->Text = L"chart1";
			// 
			// chrBLGraph
			// 
			chartArea3->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea3->AxisX->Minimum = 0;
			chartArea3->AxisY->Interval = 25;
			chartArea3->AxisY->IsStartedFromZero = false;
			chartArea3->AxisY->LogarithmBase = 2;
			chartArea3->AxisY->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea3->AxisY->Maximum = 50;
			chartArea3->AxisY->Minimum = -50;
			chartArea3->Name = L"chaBLGraph";
			this->chrBLGraph->ChartAreas->Add(chartArea3);
			this->chrBLGraph->Location = System::Drawing::Point(59, 694);
			this->chrBLGraph->Name = L"chrBLGraph";
			series3->ChartArea = L"chaBLGraph";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Name = L"Series1";
			series3->Points->Add(dataPoint11);
			series3->Points->Add(dataPoint12);
			series3->Points->Add(dataPoint13);
			series3->Points->Add(dataPoint14);
			series3->Points->Add(dataPoint15);
			this->chrBLGraph->Series->Add(series3);
			this->chrBLGraph->Size = System::Drawing::Size(675, 280);
			this->chrBLGraph->TabIndex = 141;
			this->chrBLGraph->Text = L"chart1";
			// 
			// chrBRGraph
			// 
			chartArea4->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea4->AxisX->Minimum = 0;
			chartArea4->AxisY->Interval = 25;
			chartArea4->AxisY->IsStartedFromZero = false;
			chartArea4->AxisY->LogarithmBase = 2;
			chartArea4->AxisY->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea4->AxisY->Maximum = 50;
			chartArea4->AxisY->Minimum = -50;
			chartArea4->Name = L"chaBRGraph";
			this->chrBRGraph->ChartAreas->Add(chartArea4);
			this->chrBRGraph->Location = System::Drawing::Point(809, 694);
			this->chrBRGraph->Name = L"chrBRGraph";
			series4->ChartArea = L"chaBRGraph";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Name = L"Series1";
			series4->Points->Add(dataPoint16);
			series4->Points->Add(dataPoint17);
			series4->Points->Add(dataPoint18);
			series4->Points->Add(dataPoint19);
			series4->Points->Add(dataPoint20);
			this->chrBRGraph->Series->Add(series4);
			this->chrBRGraph->Size = System::Drawing::Size(675, 280);
			this->chrBRGraph->TabIndex = 142;
			this->chrBRGraph->Text = L"chart1";
			// 
			// RTPearlingScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1920, 1080);
			this->Controls->Add(this->chrBRGraph);
			this->Controls->Add(this->chrBLGraph);
			this->Controls->Add(this->chrTRGraph);
			this->Controls->Add(this->chrTLGraph);
			this->Controls->Add(this->btnBRExport);
			this->Controls->Add(this->btnBLExport);
			this->Controls->Add(this->btnTRExport);
			this->Controls->Add(this->btnTLExport);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->panel9);
			this->Controls->Add(this->lblTLCorrection_um);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->lblTRCorrection_um);
			this->Controls->Add(this->panel6);
			this->Controls->Add(this->lblBRCorrection_um);
			this->Controls->Add(this->lblTLPearlNb);
			this->Controls->Add(this->pbTLGraph);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->lblBRPearlNb);
			this->Controls->Add(this->pbBRGraph);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->lblTRPearlNb);
			this->Controls->Add(this->pbTRGraph);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->pnlCorrectionColor);
			this->Controls->Add(this->lblBLCorrection_um);
			this->Controls->Add(this->lblBLPearlNb);
			this->Controls->Add(this->pbBLGraph);
			this->Controls->Add(this->lblBottomLeft);
			this->Controls->Add(this->lblLastAlarm);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->shapeContainer1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"RTPearlingScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LotScreen";
			this->VisibleChanged += gcnew System::EventHandler(this, &RTPearlingScreen::RTPearlingScreen_VisibleChanged);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBLGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbTRGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBRGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbTLGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrTLGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrTRGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrBLGraph))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrBRGraph))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {
				this->Close();
		 }

private: System::Void RTPearlingScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			 b_ReloadData = true;
		 }
private: System::Void btnBRExport_Click(System::Object^  sender, System::EventArgs^  e) {
			 ab_Export[1,1] = true;
			 ab_Exporting[1,1] = false;
		 }
private: System::Void btnTRExport_Click(System::Object^  sender, System::EventArgs^  e) {
			 ab_Export[1,0] = true;
			 ab_Exporting[1,0] = false;
		 }
private: System::Void btnBLExport_Click(System::Object^  sender, System::EventArgs^  e) {
			 ab_Export[0,1] = true;
			 ab_Exporting[0,1] = false;
		 }
private: System::Void btnTLExport_Click(System::Object^  sender, System::EventArgs^  e) {
			 ab_Export[0,0] = true;
			 ab_Exporting[0,0] = false;
		 }
};
}
