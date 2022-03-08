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
	public ref class LoaderManualScreen : public System::Windows::Forms::Form
	{
	public:
		LoaderManualScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			
			pT_RobotXDrive = gcnew DriveComponent(this->gbRobotXaxis);
			pT_RobotXDrive->UsePosition(0, L"");
			pT_RobotXDrive->SetDriveData(tabRobot->Text, GetTCManualOffset(s_LoaderManual.ML_Axis[0]), L"");
			pT_RobotXDrive->SetDrivePosData(0, GetTCManualOffset(s_LoaderManual.ML_AxisRobotPos[0]));
			pT_RobotYDrive = gcnew DriveComponent(this->gbRobotYaxis);
			pT_RobotYDrive->UsePosition(0, L"");
			pT_RobotYDrive->SetDriveData(tabRobot->Text, GetTCManualOffset(s_LoaderManual.ML_Axis[1]), L"");
			pT_RobotYDrive->SetDrivePosData(0, GetTCManualOffset(s_LoaderManual.ML_AxisRobotPos[1]));
			pT_RobotZ1Drive = gcnew DriveComponent(this->gbRobotZ1axis);
			pT_RobotZ1Drive->UsePosition(0, L"");
			pT_RobotZ1Drive->SetDriveData(tabRobot->Text, GetTCManualOffset(s_LoaderManual.ML_Axis[2]), "");
			pT_RobotZ1Drive->SetDrivePosData(0, GetTCManualOffset(s_LoaderManual.ML_AxisRobotPos[2]));
			pT_RobotZ2Drive = gcnew DriveComponent(this->gbRobotZ2axis);
			pT_RobotZ2Drive->UsePosition(0, L"");
			pT_RobotZ2Drive->SetDriveData(tabRobot->Text, GetTCManualOffset(s_LoaderManual.ML_Axis[3]), "");
			pT_RobotZ2Drive->SetDrivePosData(0, GetTCManualOffset(s_LoaderManual.ML_AxisRobotPos[3]));
			pT_RobotThetaDrive = gcnew DriveComponent(this->gbRobotThetaaxis);
			pT_RobotThetaDrive->UsePosition(0, L"");
			pT_RobotThetaDrive->SetDriveData(tabRobot->Text, GetTCManualOffset(s_LoaderManual.ML_Axis[4]), L"");
			pT_RobotThetaDrive->SetDrivePosData(0, GetTCManualOffset(s_LoaderManual.ML_AxisRobotPos[4]));


			cobRobotPosition->Sorted = true;
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::LoaderManualScreen::OnUserLevelChanged);

			lblVacuumThresholdHead1->Offset = GetTCManualOffset(s_LoaderManual.MT_VacuumThreshold[0]);
			lblVacuumThresholdHead2->Offset = GetTCManualOffset(s_LoaderManual.MT_VacuumThreshold[1]);
		}
			 // Our specific functions
	private:
		enum class E_Position : TC_UINT
		{
			Reject=0,
			Lift1,
			Lift2,
			TableSideALayering1,
			TableSideBLayering1,
			CleanBrush,
			TurnOverFix,
			TurnOverArm,
			TableSideALayering2,
			TableSideBLayering2,
			BulkBox,
			RejectBulkBox,
		};


		enum class E_Axis : TC_UINT
		{
			Z1 = 0,
			Z2,
			Plate,
			Vision,
			ZSensor,
		};

		enum class E_AllowedAxis : TC_UINT
		{
			None = 0xFFFE,
			All = 0xFFFF,
			Z1= (TC_UINT)E_Axis::Z1,
			Z2 = (TC_UINT)E_Axis::Z2,
			Plate = (TC_UINT)E_Axis::Plate,
			Vision = (TC_UINT)E_Axis::Vision,
			ZSensor = (TC_UINT)E_Axis::ZSensor,
		};

		enum class E_TableSide : TC_UINT
		{
			SideA = 0,
			SideB,
			None,
		};

		DriveComponent^ pT_RobotXDrive;
		DriveComponent^ pT_RobotYDrive;
		DriveComponent^ pT_RobotZ1Drive;
		DriveComponent^ pT_RobotZ2Drive;
		DriveComponent^ pT_RobotThetaDrive;
	private: System::Windows::Forms::Button^  btnZSensorTeach;
	private: System::Windows::Forms::Label^  lblValueSensorCorrection;

	private: System::Windows::Forms::Button^  btnVisionCalibration;
	private: System::Windows::Forms::CheckBox^  cbDisableVision;
	private: System::Windows::Forms::Label^  lblDisableVision;
	private: MondemaComponents::LabelOffset^  lblVacuumThresholdHead2;

	private: MondemaComponents::LabelOffset^  lblVacuumThresholdHead1;

	private: System::Windows::Forms::TextBox^  tbVacuumHead2;

	private: System::Windows::Forms::TextBox^  tbVacuumHead1;
private: System::Windows::Forms::Label^  lblRateOfFlow2;

private: System::Windows::Forms::Label^  lblRateOfFlow1;
private: System::Windows::Forms::Label^  lblSpeedModeSlow;

private: System::Windows::Forms::CheckBox^  cbSpeedModeSlow;








		bool bReloadParams;


		void SetUI(E_Axis eAxis);

		ref class cbElement : IComboBoxAllowedItem
		{
			public: 
				cbElement(LoaderManualScreen^ _Owner,String^ _Name, E_Position _ePosition, E_Axis _eAxis, E_TableSide _eTableSide)
				{
					m_Owner = _Owner;
					m_Name = _Name;
					m_Position = _ePosition;
					m_eTableSide = _eTableSide;
					m_Axis = _eAxis;
					setModeText();
				}

				virtual String^ ToString() override
				{
					return m_Name + " ( "+ m_UIModeText +" )";
				}
			
		private:
			E_Position m_Position;
			E_Axis m_Axis;
			E_TableSide m_eTableSide;
			String^ m_Name;
			String^ m_UIModeText;
			LoaderManualScreen^ m_Owner;

			void setModeText()
			{
				switch (m_Axis)
				{
					case E_Axis::Z1:
					case E_Axis::Z2:
						m_UIModeText = m_Axis.ToString();
						break;
					case E_Axis::Plate:
						m_UIModeText = TUtilities::pS_LoadString(TextIndex::Plate);
						break;
					case E_Axis::Vision:
						m_UIModeText = TUtilities::pS_LoadString(TextIndex::Vision);
						break;
					case E_Axis::ZSensor:
						m_UIModeText = TUtilities::pS_LoadString(TextIndex::ZSensor);
						break;
				}
			}
		public:
			property TC_UINT Position
			{
				TC_UINT get() { return (TC_UINT)m_Position | ((TC_UINT)m_Axis << 4); }
			}

		public:
			property E_Axis Axis
			{
				E_Axis get() { return m_Axis; }
			}

			property bool Selectable
			{
				virtual bool get()
				{
					bool bRet = true;

					// Disable turnover position if not present
					if (!b_g_UseTurnover)
					{
						switch (m_Position)
						{
							case E_Position::CleanBrush:
							case E_Position::TurnOverFix:
							case E_Position::TurnOverArm:
								bRet = false;
								break;
						}
					}

					if (m_eTableSide != E_TableSide::None)
					{
						if (m_eTableSide != m_Owner->m_eTableSide) bRet = false;
					}
					

					switch (m_Axis)
					{
						case E_Axis::Z1:
							if (!m_Owner->m_AxisZ2Safe) bRet = false;
							break;
						case E_Axis::Z2:
							if (!m_Owner->m_AxisZ1Safe) bRet = false;
							break;
						case E_Axis::Plate:
							if ((!m_Owner->m_AxisZ1Safe) || (!m_Owner->m_AxisZ2Safe)) bRet = false;
							break;
						case E_Axis::Vision:
							if ((!m_Owner->m_AxisZ1Safe) || (!m_Owner->m_AxisZ2Safe)) bRet = false;
							break;
						case E_Axis::ZSensor:
							if ((!m_Owner->m_AxisZ1Safe) || (!m_Owner->m_AxisZ2Safe)) bRet = false;
							break;
					}
					return bRet;

				}
			}
		};

		private: E_TableSide m_eTableSide = E_TableSide::None;
		private: bool m_AxisZ1Safe;
		private: bool m_AxisZ2Safe;
	private: System::Windows::Forms::Button^  btnRobotSafe;

	private: System::Windows::Forms::Label^  lblValueSensorMeasure;
	private: System::Windows::Forms::Label^  lblSensorMeasure;
	private: System::Windows::Forms::CheckBox^  btnHead2VacuumOFF;
	private: System::Windows::Forms::CheckBox^  btnHead2VacuumON;
	private: System::Windows::Forms::Label^  lblVacuumHead2;

	private: System::Windows::Forms::GroupBox^  gbRobotThetaaxis;
	private: System::Windows::Forms::GroupBox^  gbRobotXaxis;
	private: System::Windows::Forms::GroupBox^  gbRobotYaxis;
	private: System::Windows::Forms::Label^  lblRobotPosition;
	private: MondemaComponents::ComboBoxAllowed^  cobRobotPosition;
	private: System::Windows::Forms::GroupBox^  gbRobotZ1axis;
	private: System::Windows::Forms::GroupBox^  gbRobotZ2axis;
	private: System::Windows::Forms::CheckBox^  btnVacuumPlate_OFF;
	private: System::Windows::Forms::CheckBox^  btnVacuumPlate_ON;
	private: System::Windows::Forms::Label^  lblVacuumPlate;
private: System::Windows::Forms::CheckBox^  btnMovePlateTakerDown;


	private: System::Windows::Forms::CheckBox^  btnMovePlateTakerUp;
	private: System::Windows::Forms::Label^  lblJack;
	private: System::Windows::Forms::Label^  lblSensorCorrection;
	public:
		void UpdateUI(void);
	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~LoaderManualScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabRobot;
	private: System::Windows::Forms::TabPage^  tabOther;
	private: System::Windows::Forms::CheckBox^  btnHead1VacuumOFF;
	private: System::Windows::Forms::CheckBox^  btnHead1VacuumON;
	private: System::Windows::Forms::Label^  lblVacuumHead1;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LoaderManualScreen::typeid));
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabRobot = (gcnew System::Windows::Forms::TabPage());
			this->btnVisionCalibration = (gcnew System::Windows::Forms::Button());
			this->btnRobotSafe = (gcnew System::Windows::Forms::Button());
			this->gbRobotThetaaxis = (gcnew System::Windows::Forms::GroupBox());
			this->gbRobotXaxis = (gcnew System::Windows::Forms::GroupBox());
			this->gbRobotYaxis = (gcnew System::Windows::Forms::GroupBox());
			this->lblRobotPosition = (gcnew System::Windows::Forms::Label());
			this->cobRobotPosition = (gcnew MondemaComponents::ComboBoxAllowed());
			this->gbRobotZ1axis = (gcnew System::Windows::Forms::GroupBox());
			this->gbRobotZ2axis = (gcnew System::Windows::Forms::GroupBox());
			this->tabOther = (gcnew System::Windows::Forms::TabPage());
			this->lblSpeedModeSlow = (gcnew System::Windows::Forms::Label());
			this->cbSpeedModeSlow = (gcnew System::Windows::Forms::CheckBox());
			this->lblRateOfFlow2 = (gcnew System::Windows::Forms::Label());
			this->lblRateOfFlow1 = (gcnew System::Windows::Forms::Label());
			this->lblVacuumThresholdHead2 = (gcnew MondemaComponents::LabelOffset());
			this->lblVacuumThresholdHead1 = (gcnew MondemaComponents::LabelOffset());
			this->tbVacuumHead2 = (gcnew System::Windows::Forms::TextBox());
			this->tbVacuumHead1 = (gcnew System::Windows::Forms::TextBox());
			this->cbDisableVision = (gcnew System::Windows::Forms::CheckBox());
			this->lblDisableVision = (gcnew System::Windows::Forms::Label());
			this->lblValueSensorCorrection = (gcnew System::Windows::Forms::Label());
			this->btnZSensorTeach = (gcnew System::Windows::Forms::Button());
			this->lblValueSensorMeasure = (gcnew System::Windows::Forms::Label());
			this->lblSensorMeasure = (gcnew System::Windows::Forms::Label());
			this->lblSensorCorrection = (gcnew System::Windows::Forms::Label());
			this->btnVacuumPlate_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnVacuumPlate_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblVacuumPlate = (gcnew System::Windows::Forms::Label());
			this->btnMovePlateTakerDown = (gcnew System::Windows::Forms::CheckBox());
			this->btnMovePlateTakerUp = (gcnew System::Windows::Forms::CheckBox());
			this->lblJack = (gcnew System::Windows::Forms::Label());
			this->btnHead2VacuumOFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnHead2VacuumON = (gcnew System::Windows::Forms::CheckBox());
			this->lblVacuumHead2 = (gcnew System::Windows::Forms::Label());
			this->btnHead1VacuumOFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnHead1VacuumON = (gcnew System::Windows::Forms::CheckBox());
			this->lblVacuumHead1 = (gcnew System::Windows::Forms::Label());
			this->tabControl->SuspendLayout();
			this->tabRobot->SuspendLayout();
			this->tabOther->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabRobot);
			this->tabControl->Controls->Add(this->tabOther);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tabControl->ItemSize = System::Drawing::Size(134, 45);
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Margin = System::Windows::Forms::Padding(2);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1578, 873);
			this->tabControl->TabIndex = 2;
			// 
			// tabRobot
			// 
			this->tabRobot->Controls->Add(this->btnVisionCalibration);
			this->tabRobot->Controls->Add(this->btnRobotSafe);
			this->tabRobot->Controls->Add(this->gbRobotThetaaxis);
			this->tabRobot->Controls->Add(this->gbRobotXaxis);
			this->tabRobot->Controls->Add(this->gbRobotYaxis);
			this->tabRobot->Controls->Add(this->lblRobotPosition);
			this->tabRobot->Controls->Add(this->cobRobotPosition);
			this->tabRobot->Controls->Add(this->gbRobotZ1axis);
			this->tabRobot->Controls->Add(this->gbRobotZ2axis);
			this->tabRobot->Location = System::Drawing::Point(4, 49);
			this->tabRobot->Margin = System::Windows::Forms::Padding(2);
			this->tabRobot->Name = L"tabRobot";
			this->tabRobot->Padding = System::Windows::Forms::Padding(2);
			this->tabRobot->Size = System::Drawing::Size(1570, 820);
			this->tabRobot->TabIndex = 0;
			this->tabRobot->Text = L"Robot";
			this->tabRobot->UseVisualStyleBackColor = true;
			// 
			// btnVisionCalibration
			// 
			this->btnVisionCalibration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVisionCalibration->Location = System::Drawing::Point(1413, 44);
			this->btnVisionCalibration->Margin = System::Windows::Forms::Padding(2);
			this->btnVisionCalibration->Name = L"btnVisionCalibration";
			this->btnVisionCalibration->Size = System::Drawing::Size(90, 90);
			this->btnVisionCalibration->TabIndex = 121;
			this->btnVisionCalibration->Tag = L"2";
			this->btnVisionCalibration->Text = L"Vision";
			this->btnVisionCalibration->UseVisualStyleBackColor = true;
			this->btnVisionCalibration->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnVisionCalibration_Click);
			// 
			// btnRobotSafe
			// 
			this->btnRobotSafe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRobotSafe->Location = System::Drawing::Point(834, 44);
			this->btnRobotSafe->Margin = System::Windows::Forms::Padding(2);
			this->btnRobotSafe->Name = L"btnRobotSafe";
			this->btnRobotSafe->Size = System::Drawing::Size(90, 90);
			this->btnRobotSafe->TabIndex = 120;
			this->btnRobotSafe->Tag = L"0";
			this->btnRobotSafe->Text = L"Safe";
			this->btnRobotSafe->UseVisualStyleBackColor = true;
			this->btnRobotSafe->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnSafe_Click);
			// 
			// gbRobotThetaaxis
			// 
			this->gbRobotThetaaxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbRobotThetaaxis->Location = System::Drawing::Point(776, 389);
			this->gbRobotThetaaxis->Margin = System::Windows::Forms::Padding(2);
			this->gbRobotThetaaxis->Name = L"gbRobotThetaaxis";
			this->gbRobotThetaaxis->Padding = System::Windows::Forms::Padding(2);
			this->gbRobotThetaaxis->Size = System::Drawing::Size(728, 263);
			this->gbRobotThetaaxis->TabIndex = 118;
			this->gbRobotThetaaxis->TabStop = false;
			this->gbRobotThetaaxis->Tag = L"2";
			// 
			// gbRobotXaxis
			// 
			this->gbRobotXaxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbRobotXaxis->Location = System::Drawing::Point(23, 134);
			this->gbRobotXaxis->Margin = System::Windows::Forms::Padding(2);
			this->gbRobotXaxis->Name = L"gbRobotXaxis";
			this->gbRobotXaxis->Padding = System::Windows::Forms::Padding(2);
			this->gbRobotXaxis->Size = System::Drawing::Size(728, 270);
			this->gbRobotXaxis->TabIndex = 116;
			this->gbRobotXaxis->TabStop = false;
			this->gbRobotXaxis->Tag = L"2";
			// 
			// gbRobotYaxis
			// 
			this->gbRobotYaxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbRobotYaxis->Location = System::Drawing::Point(776, 134);
			this->gbRobotYaxis->Margin = System::Windows::Forms::Padding(2);
			this->gbRobotYaxis->Name = L"gbRobotYaxis";
			this->gbRobotYaxis->Padding = System::Windows::Forms::Padding(2);
			this->gbRobotYaxis->Size = System::Drawing::Size(728, 270);
			this->gbRobotYaxis->TabIndex = 117;
			this->gbRobotYaxis->TabStop = false;
			this->gbRobotYaxis->Tag = L"2";
			// 
			// lblRobotPosition
			// 
			this->lblRobotPosition->AutoSize = true;
			this->lblRobotPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRobotPosition->Location = System::Drawing::Point(48, 72);
			this->lblRobotPosition->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblRobotPosition->Name = L"lblRobotPosition";
			this->lblRobotPosition->Size = System::Drawing::Size(108, 29);
			this->lblRobotPosition->TabIndex = 115;
			this->lblRobotPosition->Tag = L"2";
			this->lblRobotPosition->Text = L"Position";
			// 
			// cobRobotPosition
			// 
			this->cobRobotPosition->AllowResizeDropDown = false;
			this->cobRobotPosition->ControlSize = System::Drawing::Size(225, 225);
			this->cobRobotPosition->DropDownSizeMode = MondemaComponents::CustomComboBox::SizeMode::UseDropDownSize;
			this->cobRobotPosition->DropSize = System::Drawing::Size(182, 159);
			this->cobRobotPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cobRobotPosition->FormattingEnabled = true;
			this->cobRobotPosition->Location = System::Drawing::Point(299, 68);
			this->cobRobotPosition->Margin = System::Windows::Forms::Padding(2);
			this->cobRobotPosition->Name = L"cobRobotPosition";
			this->cobRobotPosition->Size = System::Drawing::Size(473, 37);
			this->cobRobotPosition->TabIndex = 114;
			this->cobRobotPosition->Tag = L"2";
			this->cobRobotPosition->SetItem += gcnew System::EventHandler<MondemaComponents::ItemEventArgs^ >(this, &LoaderManualScreen::cobRobotPosition_OnSetItem);
			this->cobRobotPosition->SelectedIndexChanged += gcnew System::EventHandler(this, &LoaderManualScreen::cobRobotPosition_SelectedIndexChanged);
			// 
			// gbRobotZ1axis
			// 
			this->gbRobotZ1axis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbRobotZ1axis->Location = System::Drawing::Point(23, 398);
			this->gbRobotZ1axis->Margin = System::Windows::Forms::Padding(2);
			this->gbRobotZ1axis->Name = L"gbRobotZ1axis";
			this->gbRobotZ1axis->Padding = System::Windows::Forms::Padding(2);
			this->gbRobotZ1axis->Size = System::Drawing::Size(728, 270);
			this->gbRobotZ1axis->TabIndex = 113;
			this->gbRobotZ1axis->TabStop = false;
			this->gbRobotZ1axis->Tag = L"2";
			// 
			// gbRobotZ2axis
			// 
			this->gbRobotZ2axis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbRobotZ2axis->Location = System::Drawing::Point(23, 398);
			this->gbRobotZ2axis->Margin = System::Windows::Forms::Padding(2);
			this->gbRobotZ2axis->Name = L"gbRobotZ2axis";
			this->gbRobotZ2axis->Padding = System::Windows::Forms::Padding(2);
			this->gbRobotZ2axis->Size = System::Drawing::Size(728, 270);
			this->gbRobotZ2axis->TabIndex = 113;
			this->gbRobotZ2axis->TabStop = false;
			this->gbRobotZ2axis->Tag = L"2";
			// 
			// tabOther
			// 
			this->tabOther->Controls->Add(this->lblSpeedModeSlow);
			this->tabOther->Controls->Add(this->cbSpeedModeSlow);
			this->tabOther->Controls->Add(this->lblRateOfFlow2);
			this->tabOther->Controls->Add(this->lblRateOfFlow1);
			this->tabOther->Controls->Add(this->lblVacuumThresholdHead2);
			this->tabOther->Controls->Add(this->lblVacuumThresholdHead1);
			this->tabOther->Controls->Add(this->tbVacuumHead2);
			this->tabOther->Controls->Add(this->tbVacuumHead1);
			this->tabOther->Controls->Add(this->cbDisableVision);
			this->tabOther->Controls->Add(this->lblDisableVision);
			this->tabOther->Controls->Add(this->lblValueSensorCorrection);
			this->tabOther->Controls->Add(this->btnZSensorTeach);
			this->tabOther->Controls->Add(this->lblValueSensorMeasure);
			this->tabOther->Controls->Add(this->lblSensorMeasure);
			this->tabOther->Controls->Add(this->lblSensorCorrection);
			this->tabOther->Controls->Add(this->btnVacuumPlate_OFF);
			this->tabOther->Controls->Add(this->btnVacuumPlate_ON);
			this->tabOther->Controls->Add(this->lblVacuumPlate);
			this->tabOther->Controls->Add(this->btnMovePlateTakerDown);
			this->tabOther->Controls->Add(this->btnMovePlateTakerUp);
			this->tabOther->Controls->Add(this->lblJack);
			this->tabOther->Controls->Add(this->btnHead2VacuumOFF);
			this->tabOther->Controls->Add(this->btnHead2VacuumON);
			this->tabOther->Controls->Add(this->lblVacuumHead2);
			this->tabOther->Controls->Add(this->btnHead1VacuumOFF);
			this->tabOther->Controls->Add(this->btnHead1VacuumON);
			this->tabOther->Controls->Add(this->lblVacuumHead1);
			this->tabOther->Location = System::Drawing::Point(4, 49);
			this->tabOther->Margin = System::Windows::Forms::Padding(2);
			this->tabOther->Name = L"tabOther";
			this->tabOther->Padding = System::Windows::Forms::Padding(2);
			this->tabOther->Size = System::Drawing::Size(1570, 820);
			this->tabOther->TabIndex = 1;
			this->tabOther->Text = L"Other";
			this->tabOther->UseVisualStyleBackColor = true;
			// 
			// lblSpeedModeSlow
			// 
			this->lblSpeedModeSlow->AutoSize = true;
			this->lblSpeedModeSlow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSpeedModeSlow->Location = System::Drawing::Point(72, 665);
			this->lblSpeedModeSlow->Name = L"lblSpeedModeSlow";
			this->lblSpeedModeSlow->Size = System::Drawing::Size(228, 29);
			this->lblSpeedModeSlow->TabIndex = 154;
			this->lblSpeedModeSlow->Tag = L"1";
			this->lblSpeedModeSlow->Text = L"Speed Mode Slow";
			// 
			// cbSpeedModeSlow
			// 
			this->cbSpeedModeSlow->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbSpeedModeSlow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbSpeedModeSlow->Location = System::Drawing::Point(15, 655);
			this->cbSpeedModeSlow->Margin = System::Windows::Forms::Padding(5);
			this->cbSpeedModeSlow->Name = L"cbSpeedModeSlow";
			this->cbSpeedModeSlow->Size = System::Drawing::Size(50, 50);
			this->cbSpeedModeSlow->TabIndex = 153;
			this->cbSpeedModeSlow->Tag = L"1";
			this->cbSpeedModeSlow->UseVisualStyleBackColor = true;
			this->cbSpeedModeSlow->CheckedChanged += gcnew System::EventHandler(this, &LoaderManualScreen::cbSpeedModeSlow_CheckedChanged);
			// 
			// lblRateOfFlow2
			// 
			this->lblRateOfFlow2->AutoSize = true;
			this->lblRateOfFlow2->Location = System::Drawing::Point(900, 143);
			this->lblRateOfFlow2->Name = L"lblRateOfFlow2";
			this->lblRateOfFlow2->Size = System::Drawing::Size(86, 29);
			this->lblRateOfFlow2->TabIndex = 152;
			this->lblRateOfFlow2->Tag = L"1";
			this->lblRateOfFlow2->Text = L"[l/min]";
			// 
			// lblRateOfFlow1
			// 
			this->lblRateOfFlow1->AutoSize = true;
			this->lblRateOfFlow1->Location = System::Drawing::Point(900, 44);
			this->lblRateOfFlow1->Name = L"lblRateOfFlow1";
			this->lblRateOfFlow1->Size = System::Drawing::Size(86, 29);
			this->lblRateOfFlow1->TabIndex = 152;
			this->lblRateOfFlow1->Tag = L"1";
			this->lblRateOfFlow1->Text = L"[l/min]";
			// 
			// lblVacuumThresholdHead2
			// 
			this->lblVacuumThresholdHead2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblVacuumThresholdHead2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblVacuumThresholdHead2->EditText = L"";
			this->lblVacuumThresholdHead2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblVacuumThresholdHead2->Location = System::Drawing::Point(680, 135);
			this->lblVacuumThresholdHead2->Margin = System::Windows::Forms::Padding(5);
			this->lblVacuumThresholdHead2->Name = L"lblVacuumThresholdHead2";
			this->lblVacuumThresholdHead2->Offset = static_cast<System::UInt32>(0);
			this->lblVacuumThresholdHead2->Size = System::Drawing::Size(212, 45);
			this->lblVacuumThresholdHead2->TabIndex = 151;
			this->lblVacuumThresholdHead2->Tag = L"1";
			this->lblVacuumThresholdHead2->Text = L"0";
			this->lblVacuumThresholdHead2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblVacuumThresholdHead2->Click += gcnew System::EventHandler(this, &LoaderManualScreen::lblVacuumThresholdHead_Click);
			// 
			// lblVacuumThresholdHead1
			// 
			this->lblVacuumThresholdHead1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblVacuumThresholdHead1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblVacuumThresholdHead1->EditText = L"";
			this->lblVacuumThresholdHead1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblVacuumThresholdHead1->Location = System::Drawing::Point(680, 36);
			this->lblVacuumThresholdHead1->Margin = System::Windows::Forms::Padding(5);
			this->lblVacuumThresholdHead1->Name = L"lblVacuumThresholdHead1";
			this->lblVacuumThresholdHead1->Offset = static_cast<System::UInt32>(0);
			this->lblVacuumThresholdHead1->Size = System::Drawing::Size(212, 45);
			this->lblVacuumThresholdHead1->TabIndex = 150;
			this->lblVacuumThresholdHead1->Tag = L"1";
			this->lblVacuumThresholdHead1->Text = L"0";
			this->lblVacuumThresholdHead1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblVacuumThresholdHead1->Click += gcnew System::EventHandler(this, &LoaderManualScreen::lblVacuumThresholdHead_Click);
			// 
			// tbVacuumHead2
			// 
			this->tbVacuumHead2->Location = System::Drawing::Point(506, 138);
			this->tbVacuumHead2->Name = L"tbVacuumHead2";
			this->tbVacuumHead2->ReadOnly = true;
			this->tbVacuumHead2->Size = System::Drawing::Size(162, 35);
			this->tbVacuumHead2->TabIndex = 149;
			this->tbVacuumHead2->Tag = L"1";
			this->tbVacuumHead2->Text = L"0.00";
			this->tbVacuumHead2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// tbVacuumHead1
			// 
			this->tbVacuumHead1->Location = System::Drawing::Point(506, 39);
			this->tbVacuumHead1->Name = L"tbVacuumHead1";
			this->tbVacuumHead1->ReadOnly = true;
			this->tbVacuumHead1->Size = System::Drawing::Size(162, 35);
			this->tbVacuumHead1->TabIndex = 148;
			this->tbVacuumHead1->Tag = L"1";
			this->tbVacuumHead1->Text = L"0.00";
			this->tbVacuumHead1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// cbDisableVision
			// 
			this->cbDisableVision->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbDisableVision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbDisableVision->Location = System::Drawing::Point(15, 568);
			this->cbDisableVision->Margin = System::Windows::Forms::Padding(5);
			this->cbDisableVision->Name = L"cbDisableVision";
			this->cbDisableVision->Size = System::Drawing::Size(50, 50);
			this->cbDisableVision->TabIndex = 147;
			this->cbDisableVision->Tag = L"1";
			this->cbDisableVision->UseVisualStyleBackColor = true;
			this->cbDisableVision->CheckedChanged += gcnew System::EventHandler(this, &LoaderManualScreen::cbDisableVision_CheckedChanged);
			// 
			// lblDisableVision
			// 
			this->lblDisableVision->AutoSize = true;
			this->lblDisableVision->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDisableVision->Location = System::Drawing::Point(72, 578);
			this->lblDisableVision->Name = L"lblDisableVision";
			this->lblDisableVision->Size = System::Drawing::Size(239, 29);
			this->lblDisableVision->TabIndex = 146;
			this->lblDisableVision->Tag = L"1";
			this->lblDisableVision->Text = L"Désactiver la vision";
			// 
			// lblValueSensorCorrection
			// 
			this->lblValueSensorCorrection->AutoSize = true;
			this->lblValueSensorCorrection->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblValueSensorCorrection->Location = System::Drawing::Point(368, 496);
			this->lblValueSensorCorrection->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblValueSensorCorrection->Name = L"lblValueSensorCorrection";
			this->lblValueSensorCorrection->Size = System::Drawing::Size(48, 29);
			this->lblValueSensorCorrection->TabIndex = 145;
			this->lblValueSensorCorrection->Tag = L"2";
			this->lblValueSensorCorrection->Text = L"0.0";
			// 
			// btnZSensorTeach
			// 
			this->btnZSensorTeach->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnZSensorTeach->Location = System::Drawing::Point(437, 435);
			this->btnZSensorTeach->Margin = System::Windows::Forms::Padding(2);
			this->btnZSensorTeach->Name = L"btnZSensorTeach";
			this->btnZSensorTeach->Size = System::Drawing::Size(143, 90);
			this->btnZSensorTeach->TabIndex = 144;
			this->btnZSensorTeach->Tag = L"2";
			this->btnZSensorTeach->Text = L"Teach";
			this->btnZSensorTeach->UseVisualStyleBackColor = true;
			this->btnZSensorTeach->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnZSensorTeach_Click);
			// 
			// lblValueSensorMeasure
			// 
			this->lblValueSensorMeasure->AutoSize = true;
			this->lblValueSensorMeasure->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblValueSensorMeasure->Location = System::Drawing::Point(370, 435);
			this->lblValueSensorMeasure->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblValueSensorMeasure->Name = L"lblValueSensorMeasure";
			this->lblValueSensorMeasure->Size = System::Drawing::Size(48, 29);
			this->lblValueSensorMeasure->TabIndex = 142;
			this->lblValueSensorMeasure->Tag = L"1";
			this->lblValueSensorMeasure->Text = L"0.0";
			// 
			// lblSensorMeasure
			// 
			this->lblSensorMeasure->AutoSize = true;
			this->lblSensorMeasure->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSensorMeasure->Location = System::Drawing::Point(12, 435);
			this->lblSensorMeasure->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblSensorMeasure->Name = L"lblSensorMeasure";
			this->lblSensorMeasure->Size = System::Drawing::Size(114, 29);
			this->lblSensorMeasure->TabIndex = 141;
			this->lblSensorMeasure->Tag = L"1";
			this->lblSensorMeasure->Text = L"Measure";
			// 
			// lblSensorCorrection
			// 
			this->lblSensorCorrection->AutoSize = true;
			this->lblSensorCorrection->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSensorCorrection->Location = System::Drawing::Point(10, 496);
			this->lblSensorCorrection->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblSensorCorrection->Name = L"lblSensorCorrection";
			this->lblSensorCorrection->Size = System::Drawing::Size(218, 29);
			this->lblSensorCorrection->TabIndex = 118;
			this->lblSensorCorrection->Tag = L"2";
			this->lblSensorCorrection->Text = L"SensorCorrection";
			// 
			// btnVacuumPlate_OFF
			// 
			this->btnVacuumPlate_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuumPlate_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuumPlate_OFF->Location = System::Drawing::Point(350, 209);
			this->btnVacuumPlate_OFF->Margin = System::Windows::Forms::Padding(2);
			this->btnVacuumPlate_OFF->Name = L"btnVacuumPlate_OFF";
			this->btnVacuumPlate_OFF->Size = System::Drawing::Size(90, 90);
			this->btnVacuumPlate_OFF->TabIndex = 117;
			this->btnVacuumPlate_OFF->Tag = L"0";
			this->btnVacuumPlate_OFF->Text = L"OFF";
			this->btnVacuumPlate_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuumPlate_OFF->UseVisualStyleBackColor = true;
			this->btnVacuumPlate_OFF->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnVacuumPlate_OFF_Click);
			// 
			// btnVacuumPlate_ON
			// 
			this->btnVacuumPlate_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnVacuumPlate_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVacuumPlate_ON->Location = System::Drawing::Point(251, 209);
			this->btnVacuumPlate_ON->Margin = System::Windows::Forms::Padding(2);
			this->btnVacuumPlate_ON->Name = L"btnVacuumPlate_ON";
			this->btnVacuumPlate_ON->Size = System::Drawing::Size(90, 90);
			this->btnVacuumPlate_ON->TabIndex = 116;
			this->btnVacuumPlate_ON->Tag = L"0";
			this->btnVacuumPlate_ON->Text = L"ON";
			this->btnVacuumPlate_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnVacuumPlate_ON->UseVisualStyleBackColor = true;
			this->btnVacuumPlate_ON->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnVacuumPlate_ON_Click);
			// 
			// lblVacuumPlate
			// 
			this->lblVacuumPlate->AutoSize = true;
			this->lblVacuumPlate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuumPlate->Location = System::Drawing::Point(12, 237);
			this->lblVacuumPlate->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblVacuumPlate->Name = L"lblVacuumPlate";
			this->lblVacuumPlate->Size = System::Drawing::Size(165, 29);
			this->lblVacuumPlate->TabIndex = 115;
			this->lblVacuumPlate->Tag = L"0";
			this->lblVacuumPlate->Text = L"VacuumPlate";
			// 
			// btnMovePlateTakerDown
			// 
			this->btnMovePlateTakerDown->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnMovePlateTakerDown->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnMovePlateTakerDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMovePlateTakerDown->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnMovePlateTakerDown.Image")));
			this->btnMovePlateTakerDown->Location = System::Drawing::Point(350, 308);
			this->btnMovePlateTakerDown->Margin = System::Windows::Forms::Padding(2);
			this->btnMovePlateTakerDown->Name = L"btnMovePlateTakerDown";
			this->btnMovePlateTakerDown->Size = System::Drawing::Size(90, 90);
			this->btnMovePlateTakerDown->TabIndex = 114;
			this->btnMovePlateTakerDown->Tag = L"1";
			this->btnMovePlateTakerDown->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnMovePlateTakerDown->UseVisualStyleBackColor = false;
			this->btnMovePlateTakerDown->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnMovePlateTakerDown_Click);
			// 
			// btnMovePlateTakerUp
			// 
			this->btnMovePlateTakerUp->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnMovePlateTakerUp->BackColor = System::Drawing::SystemColors::ControlLight;
			this->btnMovePlateTakerUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnMovePlateTakerUp->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnMovePlateTakerUp.Image")));
			this->btnMovePlateTakerUp->Location = System::Drawing::Point(251, 308);
			this->btnMovePlateTakerUp->Margin = System::Windows::Forms::Padding(2);
			this->btnMovePlateTakerUp->Name = L"btnMovePlateTakerUp";
			this->btnMovePlateTakerUp->Size = System::Drawing::Size(90, 90);
			this->btnMovePlateTakerUp->TabIndex = 113;
			this->btnMovePlateTakerUp->Tag = L"1";
			this->btnMovePlateTakerUp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnMovePlateTakerUp->UseVisualStyleBackColor = false;
			this->btnMovePlateTakerUp->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnMovePlateTakerUp_Click);
			// 
			// lblJack
			// 
			this->lblJack->AutoSize = true;
			this->lblJack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblJack->Location = System::Drawing::Point(12, 345);
			this->lblJack->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblJack->Name = L"lblJack";
			this->lblJack->Size = System::Drawing::Size(132, 29);
			this->lblJack->TabIndex = 112;
			this->lblJack->Tag = L"1";
			this->lblJack->Text = L"TakePlate";
			// 
			// btnHead2VacuumOFF
			// 
			this->btnHead2VacuumOFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnHead2VacuumOFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnHead2VacuumOFF->Location = System::Drawing::Point(350, 110);
			this->btnHead2VacuumOFF->Margin = System::Windows::Forms::Padding(2);
			this->btnHead2VacuumOFF->Name = L"btnHead2VacuumOFF";
			this->btnHead2VacuumOFF->Size = System::Drawing::Size(90, 90);
			this->btnHead2VacuumOFF->TabIndex = 111;
			this->btnHead2VacuumOFF->Tag = L"0";
			this->btnHead2VacuumOFF->Text = L"OFF";
			this->btnHead2VacuumOFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnHead2VacuumOFF->UseVisualStyleBackColor = true;
			this->btnHead2VacuumOFF->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnHead2VacuumOFF_Click);
			// 
			// btnHead2VacuumON
			// 
			this->btnHead2VacuumON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnHead2VacuumON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnHead2VacuumON->Location = System::Drawing::Point(251, 110);
			this->btnHead2VacuumON->Margin = System::Windows::Forms::Padding(2);
			this->btnHead2VacuumON->Name = L"btnHead2VacuumON";
			this->btnHead2VacuumON->Size = System::Drawing::Size(90, 90);
			this->btnHead2VacuumON->TabIndex = 110;
			this->btnHead2VacuumON->Tag = L"0";
			this->btnHead2VacuumON->Text = L"ON";
			this->btnHead2VacuumON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnHead2VacuumON->UseVisualStyleBackColor = true;
			this->btnHead2VacuumON->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnHead2VacuumON_Click);
			// 
			// lblVacuumHead2
			// 
			this->lblVacuumHead2->AutoSize = true;
			this->lblVacuumHead2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuumHead2->Location = System::Drawing::Point(12, 138);
			this->lblVacuumHead2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblVacuumHead2->Name = L"lblVacuumHead2";
			this->lblVacuumHead2->Size = System::Drawing::Size(181, 29);
			this->lblVacuumHead2->TabIndex = 109;
			this->lblVacuumHead2->Tag = L"0";
			this->lblVacuumHead2->Text = L"VacuumHead2";
			// 
			// btnHead1VacuumOFF
			// 
			this->btnHead1VacuumOFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnHead1VacuumOFF->BackColor = System::Drawing::Color::Transparent;
			this->btnHead1VacuumOFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnHead1VacuumOFF->Location = System::Drawing::Point(350, 11);
			this->btnHead1VacuumOFF->Margin = System::Windows::Forms::Padding(2);
			this->btnHead1VacuumOFF->Name = L"btnHead1VacuumOFF";
			this->btnHead1VacuumOFF->Size = System::Drawing::Size(90, 90);
			this->btnHead1VacuumOFF->TabIndex = 88;
			this->btnHead1VacuumOFF->Tag = L"0";
			this->btnHead1VacuumOFF->Text = L"OFF";
			this->btnHead1VacuumOFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnHead1VacuumOFF->UseVisualStyleBackColor = false;
			this->btnHead1VacuumOFF->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnHead1VacuumOFF_Click);
			// 
			// btnHead1VacuumON
			// 
			this->btnHead1VacuumON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnHead1VacuumON->BackColor = System::Drawing::Color::Transparent;
			this->btnHead1VacuumON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnHead1VacuumON->Location = System::Drawing::Point(251, 11);
			this->btnHead1VacuumON->Margin = System::Windows::Forms::Padding(2);
			this->btnHead1VacuumON->Name = L"btnHead1VacuumON";
			this->btnHead1VacuumON->Size = System::Drawing::Size(90, 90);
			this->btnHead1VacuumON->TabIndex = 87;
			this->btnHead1VacuumON->Tag = L"0";
			this->btnHead1VacuumON->Text = L"ON";
			this->btnHead1VacuumON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnHead1VacuumON->UseVisualStyleBackColor = false;
			this->btnHead1VacuumON->Click += gcnew System::EventHandler(this, &LoaderManualScreen::btnHead1VacuumON_Click);
			// 
			// lblVacuumHead1
			// 
			this->lblVacuumHead1->AutoSize = true;
			this->lblVacuumHead1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblVacuumHead1->Location = System::Drawing::Point(12, 39);
			this->lblVacuumHead1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblVacuumHead1->Name = L"lblVacuumHead1";
			this->lblVacuumHead1->Size = System::Drawing::Size(181, 29);
			this->lblVacuumHead1->TabIndex = 86;
			this->lblVacuumHead1->Tag = L"0";
			this->lblVacuumHead1->Text = L"VacuumHead1";
			// 
			// LoaderManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"LoaderManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"LoaderManualScreen";
			this->VisibleChanged += gcnew System::EventHandler(this, &LoaderManualScreen::LoaderManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabRobot->ResumeLayout(false);
			this->tabRobot->PerformLayout();
			this->tabOther->ResumeLayout(false);
			this->tabOther->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void btnHead1VacuumON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabOther->Text + " : " + TUtilities::pS_LoadString(TextIndex::Vacuum) + "1 ON");
			SetTCManData(s_LoaderManual.ML_Head1Vacuum.MB_Activate);
		 }
private: System::Void btnHead1VacuumOFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabOther->Text + " : " + TUtilities::pS_LoadString(TextIndex::Vacuum) + "1 OFF");
			ClearTCManData(s_LoaderManual.ML_Head1Vacuum.MB_Activate);
		 }
private: System::Void cobRobotPosition_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			cbElement^ oElement = (cbElement^)cobRobotPosition->SelectedItem;
			SetUI(oElement->Axis);
		 }
private: System::Void cobRobotPosition_OnSetItem(System::Object ^sender, MondemaComponents::ItemEventArgs ^e) {
			cbElement^ oElement = (cbElement^)e->Item;
			TLogger::AddManualLog(tabRobot->Text + " : " + TUtilities::pS_LoadString(TextIndex::Position) + " : " + oElement->ToString());
			WriteTCManData(s_LoaderManual.ML_RobotPos, oElement->Position);
			SetUI(oElement->Axis);
		}
private: System::Void btnMovePlateTakerUp_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabOther->Text + " : " + TUtilities::pS_LoadString(TextIndex::MovePlateJackUp));
			ClearTCManData(s_LoaderManual.ML_MovePlateTakerDown.MB_Activate);
		 }
private: System::Void btnMovePlateTakerDown_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabOther->Text + " : " + TUtilities::pS_LoadString(TextIndex::MovePlateJackDown));
			SetTCManData(s_LoaderManual.ML_MovePlateTakerDown.MB_Activate);
		 }
private: System::Void btnVacuumPlate_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabOther->Text + " : " + TUtilities::pS_LoadString(TextIndex::EnableVacuum));
			SetTCManData(s_LoaderManual.ML_PlateVacuum.MB_Activate);
		 }
private: System::Void btnVacuumPlate_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabOther->Text + " : " + TUtilities::pS_LoadString(TextIndex::DisableVacuum));
			ClearTCManData(s_LoaderManual.ML_PlateVacuum.MB_Activate);
		 }
private: System::Void LoaderManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			gbRobotXaxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisX) + L"  ";
			gbRobotYaxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisY) + L"  ";
			gbRobotZ1axis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisZ) + L"1  ";
			gbRobotZ2axis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisZ) + L"2  ";
			gbRobotThetaaxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisTheta) + L"  ";

			lblSensorCorrection->Text = TUtilities::pS_LoadString(TextIndex::SensorCorrection) + " [mm]";
			lblJack->Text = TUtilities::pS_LoadString(TextIndex::PlateJack);
			lblVacuumHead1->Text = TUtilities::pS_LoadString(TextIndex::VacuumHead1);
			lblVacuumHead2->Text = TUtilities::pS_LoadString(TextIndex::VacuumHead2);
			lblVacuumPlate->Text = TUtilities::pS_LoadString(TextIndex::VacuumPlate);
			lblRobotPosition->Text = TUtilities::pS_LoadString(TextIndex::RobotPosition);
			btnVisionCalibration->Text = TUtilities::pS_LoadString(TextIndex::Vision);

			tabRobot->Text = TUtilities::pS_LoadString(TextIndex::Robot);
			tabOther->Text = TUtilities::pS_LoadString(TextIndex::Other);

			btnRobotSafe->Text = TUtilities::pS_LoadString(TextIndex::Safe);
			lblSensorMeasure->Text = TUtilities::pS_LoadString(TextIndex::SensorMeasure) + " [mm]";
			lblDisableVision->Text = TUtilities::pS_LoadString(TextIndex::DisableVision);
			lblSpeedModeSlow->Text = TUtilities::pS_LoadString(TextIndex::SpeedModeSlow);

			cobRobotPosition->Items->Clear();
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Reject), E_Position::Reject, E_Axis::Z1,E_TableSide::None));
			cobRobotPosition->Items->Add(gcnew cbElement(this,TUtilities::pS_LoadString(TextIndex::LeftLift), E_Position::Lift1, E_Axis::Z1, E_TableSide::None));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::RightLift), E_Position::Lift2, E_Axis::Z1, E_TableSide::None));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " Pos A", E_Position::TableSideALayering1, E_Axis::Z1, E_TableSide::SideA));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " Pos B", E_Position::TableSideALayering2, E_Axis::Z1, E_TableSide::SideA));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " Pos C", E_Position::TableSideBLayering1, E_Axis::Z1, E_TableSide::SideB));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " Pos D", E_Position::TableSideBLayering2, E_Axis::Z1, E_TableSide::SideB));

			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::TurnOverClean), E_Position::CleanBrush, E_Axis::Z1, E_TableSide::None));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::TurnOverFix), E_Position::TurnOverFix, E_Axis::Z1, E_TableSide::None));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::TurnOverArm), E_Position::TurnOverArm, E_Axis::Z1, E_TableSide::None));

			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " Pos A", E_Position::TableSideALayering1, E_Axis::Z2, E_TableSide::SideA));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " Pos A", E_Position::TableSideALayering1, E_Axis::Vision, E_TableSide::SideA));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " Pos A", E_Position::TableSideALayering1, E_Axis::ZSensor, E_TableSide::SideA));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::LeftLift), E_Position::Lift1, E_Axis::Plate, E_TableSide::None));

			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::BulkBox), E_Position::BulkBox, E_Axis::Z1, E_TableSide::None));
			cobRobotPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::RejectBulkBox), E_Position::RejectBulkBox, E_Axis::Z1, E_TableSide::None));

			pT_RobotXDrive->ReloadComponent();
			pT_RobotXDrive->SetPositionName(0, TUtilities::pS_LoadString(TextIndex::Position));
			pT_RobotXDrive->SetDriveName(tabRobot->Text + L" X", "");
			pT_RobotYDrive->ReloadComponent();
			pT_RobotYDrive->SetPositionName(0, TUtilities::pS_LoadString(TextIndex::Position));
			pT_RobotYDrive->SetDriveName(tabRobot->Text + L" Y", "");
			pT_RobotZ1Drive->ReloadComponent();
			pT_RobotZ1Drive->SetPositionName(0, TUtilities::pS_LoadString(TextIndex::Position));
			pT_RobotZ1Drive->SetDriveName(tabRobot->Text + L" Z1", "");
			pT_RobotZ2Drive->ReloadComponent();
			pT_RobotZ2Drive->SetPositionName(0, TUtilities::pS_LoadString(TextIndex::Position));
			pT_RobotZ2Drive->SetDriveName(tabRobot->Text + L" Z2", "");
			pT_RobotThetaDrive->ReloadComponent();
			pT_RobotThetaDrive->SetPositionName(0, TUtilities::pS_LoadString(TextIndex::Position));
			pT_RobotThetaDrive->SetDriveName(tabRobot->Text + " Theta", "");
			btnZSensorTeach->Text = TUtilities::pS_LoadString(TextIndex::Teach);
			bReloadParams = true;
		 }
private: System::Void btnHead2VacuumON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Loader) + " : " + TUtilities::pS_LoadString(TextIndex::Vacuum) + "2 ON");
			SetTCManData(s_LoaderManual.ML_Head2Vacuum.MB_Activate);
		 }
private: System::Void btnHead2VacuumOFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Loader) + " : " + TUtilities::pS_LoadString(TextIndex::Vacuum) + "2 OFF");
			ClearTCManData(s_LoaderManual.ML_Head2Vacuum.MB_Activate);
		 }
private: System::Void tbSensorAdjust_Click(System::Object^  sender, System::EventArgs^  e) {
			TUtilities::ShowOSK();
		 }
private: System::Void btnSafe_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Loader) + " : " + TUtilities::pS_LoadString(TextIndex::Safe));
	SetTCManData(s_LoaderManual.ML_Safe.MB_Activate);
}
private: System::Void btnZSensorTeach_Click(System::Object^  sender, System::EventArgs^  e) {
	MyMsgBox^ pT_l_ValidateChange = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::PosTeachReq) + L" <" + TUtilities::pS_LoadString(TextIndex::SensorCorrection) + L"> ?", TUtilities::pS_LoadString(TextIndex::ValidateReq), MessageBoxButtons::YesNo);
	pT_l_ValidateChange->ShowDialog();
	if (1 == pT_l_ValidateChange->iPressedButton)
	{
		TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Position) + L" " + TUtilities::pS_LoadString(TextIndex::SensorCorrection));
		SetTCManData(s_LoaderManual.ML_ZSensorTeach.MB_Activate);
	}
}
private: System::Void btnVisionCalibration_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Loader) + " : " + TUtilities::pS_LoadString(TextIndex::Vision));
	SetTCManData(s_LoaderManual.ML_VisionCalibration.MB_Activate);
}
		 void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);
	private: System::Void cbDisableVision_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (cbDisableVision->Checked)
		{
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::DisableVision) + L" = ON");
			SetTCData(s_MachineOpt.MO_DisableVision);
		}
		else
		{
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::DisableVision) + L" = OFF");
			ClearTCData(s_MachineOpt.MO_DisableVision);
		}
	}
private: System::Void lblVacuumThresholdHead_Click(System::Object^  sender, System::EventArgs^  e) {
	LabelOffset^ lbl = (LabelOffset^)sender;
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lbl->EditText, double::Parse(lbl->Text), 0, 9, "F2");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(lbl->EditText + L" : = " + Keypad->Value.ToString());
		WriteTCManOffsetData(lbl->Offset, (TC_LREAL)Keypad->Value);
	}
}
private: System::Void cbSpeedModeSlow_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (cbSpeedModeSlow->Checked)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SpeedModeSlow) + L" = ON");
		SetTCData(s_MachineOpt.MO_SpeedModeSlow);
	}
	else
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SpeedModeSlow) + L" = OFF");
		ClearTCData(s_MachineOpt.MO_SpeedModeSlow);
	}
}
};
}
