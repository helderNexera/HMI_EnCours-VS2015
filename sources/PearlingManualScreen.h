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
	public ref class PearlingManualScreen : public System::Windows::Forms::Form
	{
	public:
		PearlingManualScreen(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			pT_XDrive = gcnew DriveComponent(this->gbXaxis);
			pT_XDrive->UsePosition(0,"");
			pT_XDrive->SetDriveData(tabControl->TabPages[0]->Text,GetTCManualOffset(s_PearlingManual.MP_Axis[0]));
			pT_XDrive->SetDrivePosData(0,GetTCManualOffset(s_PearlingManual.MP_AxisPos[0]));
			pT_YDrive = gcnew DriveComponent(this->gbYaxis);
			pT_YDrive->UsePosition(0,"");
			pT_YDrive->SetDriveData(tabControl->TabPages[0]->Text,GetTCManualOffset(s_PearlingManual.MP_Axis[1]));
			pT_YDrive->SetDrivePosData(0,GetTCManualOffset(s_PearlingManual.MP_AxisPos[1]));
			pT_Z1Drive = gcnew DriveComponent(this->gbZ1axis);
			pT_Z1Drive->UsePosition(0,"");
			pT_Z1Drive->SetDriveData(tabControl->TabPages[0]->Text,GetTCManualOffset(s_PearlingManual.MP_Axis[2]));
			pT_Z1Drive->SetDrivePosData(0,GetTCManualOffset(s_PearlingManual.MP_AxisPos[2]));
			pT_Z2Drive = gcnew DriveComponent(this->gbZ2axis);
			pT_Z2Drive->UsePosition(0,"");
			pT_Z2Drive->SetDriveData(tabControl->TabPages[0]->Text,GetTCManualOffset(s_PearlingManual.MP_Axis[3]));
			pT_Z2Drive->SetDrivePosData(0,GetTCManualOffset(s_PearlingManual.MP_AxisPos[3]));
			TUser::UserLevelChanged += gcnew TUser::UserLevelChangedEvent(this, &Projet1::PearlingManualScreen::OnUserLevelChanged);
		}

	public: 

			 // Our specific functions
	private:
	private:	bool bReloadParams;
		DriveComponent^ pT_XDrive;
		DriveComponent^ pT_YDrive;
		DriveComponent^ pT_Z1Drive;
		DriveComponent^ pT_Z2Drive;
		array<TC_LREAL>^		m_CalibrationLeftData = nullptr;
		array<TC_LREAL>^		m_CalibrationRightData = nullptr;

		enum class E_TableSide : TC_UINT
		{
			SideA = 0,
			SideB,
			None,
		};

		enum class E_Axis : TC_UINT
		{
			Z1 = 0,
			Z2,
			All,
		};

		ref class cbElement : IComboBoxAllowedItem
		{
		public:
			cbElement(PearlingManualScreen^ _Owner, String^ _Name, E_TableSide _eTableSide, E_Axis _eAxis, TC_UINT _Position)
			{
				m_Owner = _Owner;
				m_Name = _Name;
				m_eTableSide = _eTableSide;
				m_Position = _Position;
				m_Axis = _eAxis;
			}

			virtual String^ ToString() override
			{
				if (m_Axis == E_Axis::All)
					return m_Name + " ( " + E_Axis::Z1.ToString() + " " + E_Axis::Z2.ToString() + " )";
				else
					return m_Name + " ( " + m_Axis.ToString() + " )";
			}

		private:
			String^ m_Name;
			PearlingManualScreen^ m_Owner;
			E_TableSide m_eTableSide;
			TC_UINT m_Position;
			E_Axis m_Axis;

		public:
			property TC_UINT Position
			{
				TC_UINT get() { return m_Position; }
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
						case E_Axis::All:
							if ((!m_Owner->m_AxisZ1Safe) || (!m_Owner->m_AxisZ1Safe)) bRet = false;
							break;
					}
					return bRet;
				}
			}
		};

	private: E_TableSide m_eTableSide = E_TableSide::None;
	private: bool m_AxisZ1Safe;
private: System::Windows::Forms::TextBox^  tbRightHeightSensor;
private: System::Windows::Forms::TextBox^  tbLeftHeightSensor;
private: System::Windows::Forms::Label^  lblHeightSensor;
private: System::Windows::Forms::TextBox^  tbWeightSensor;
private: System::Windows::Forms::Label^  lblWeightSensor;
private: System::Windows::Forms::Label^  lblCurrentMotorMaxTh;
private: System::Windows::Forms::Label^  lblCurrentMotorMaxThreshold;
private: System::Windows::Forms::TextBox^  tbRightSpindlePearlsCounter;
private: System::Windows::Forms::TextBox^  tbLeftSpindlePearlsCounter;
private: System::Windows::Forms::Label^  lblSpindlePearlsCounter;
private: System::Windows::Forms::Label^  lblRightSpindle;

private: System::Windows::Forms::Label^  lblLeftSpindle;
private: System::Windows::Forms::Label^  lblRightSpindlePearling;

private: System::Windows::Forms::Label^  lblLeftSpindlePearling;
private: System::Windows::Forms::Label^  lblSharpenSpeedValue;
private: System::Windows::Forms::Label^  lblMinHoldLengthValue;
private: System::Windows::Forms::Label^  lblSharpenHeightValue;
private: System::Windows::Forms::Label^  lblNbOfFwBwSharpenValue;
private: System::Windows::Forms::Label^  lblNbOfFwBwBeforeTapeMoveValue;
private: System::Windows::Forms::Label^  lblRightSpindleManualSpeedValue;
private: System::Windows::Forms::Label^  lblLeftSpindleManualSpeedValue;
private: System::Windows::Forms::Label^  lblRightSpindleRatio;
private: System::Windows::Forms::Label^  lblLeftSpindleRatio;
private: System::Windows::Forms::Label^  lblRightCompenseWeight;
private: System::Windows::Forms::Label^  lblLeftCompenseWeight;




	private: bool m_AxisZ2Safe;
			 void SetUI(E_Axis eAxis);
	private: System::Windows::Forms::DataGridView^  dgvWeightTableRight;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chrLeft;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chrRight;
private: System::Windows::Forms::Label^  lblCurrentMotorWarnTh;

private: System::Windows::Forms::Label^  lblCurrentMotorMinTh;
private: System::Windows::Forms::Label^  lblCurrentMotorWarnThreshold;



private: System::Windows::Forms::Label^  lblCurrentMotorMinThreshold;


	private: System::Windows::Forms::CheckBox^  cbSimPearling;
	private: System::Windows::Forms::Label^  lblSimPearling;
	private: System::Windows::Forms::Label^  lblMotorStopTimeout;
	private: System::Windows::Forms::Label^  lblMotorStartTimeout;
	private: System::Windows::Forms::Label^  lblRightMotorStopTimeout;
	private: System::Windows::Forms::Label^  lblLeftMotorStopTimeout;
	private: System::Windows::Forms::Label^  lblRightMotorStartTimeout;
	private: System::Windows::Forms::Label^  lblLeftMotorStartTimeout;
	private: System::Windows::Forms::Label^  lblSpindleSharpenSpeed;
	private: System::Windows::Forms::Label^  lblSpindleSharpenSpeedValue;
	private: System::Windows::Forms::Label^  lblWeightToleranceValue;
	private: System::Windows::Forms::Label^  lblWeightTolerance;
	//private: System::Windows::Forms::TextBox^  tbMinHoldLength;
	private: System::Windows::Forms::Label^  lblMinHoldLength;
	private: System::Windows::Forms::CheckBox^  cbStopOnStickBreak;
	private: System::Windows::Forms::Label^  lblStopOnStickBreak;
	private: System::Windows::Forms::CheckBox^  cbStopOnVacuumLoss;
	private: System::Windows::Forms::Label^  lblStopOnVacuumLoss;
	private: System::Windows::Forms::CheckBox^  cbStopOnWeightOutOfTolerance;
	private: System::Windows::Forms::Label^  lblStopOnWeightOutOfTolerance;
	private: System::Windows::Forms::TabPage^  tabPageRecipe;
	private: System::Windows::Forms::Label^  tbRightCompensationStep;
	private: System::Windows::Forms::Label^  lblCompensationStep;
	private: System::Windows::Forms::TabPage^  tabPageCalibration;
	private: System::Windows::Forms::Button^  btnCalibrateLeftWeight;
	private: System::Windows::Forms::Label^  lblCalibrateLeftWeight;
	private: System::Windows::Forms::DataGridView^  dgvWeightTableLeft;
	private: System::Windows::Forms::GroupBox^  gbZ1axis;
	private: System::Windows::Forms::TabPage^  tabPageStick;
	private: System::Windows::Forms::GroupBox^  gbRightSpindle;
	private: System::Windows::Forms::Label^  lblRightMotor;
	private: System::Windows::Forms::CheckBox^  btnRightMotor_ON;
	private: System::Windows::Forms::CheckBox^  btnRightMotor_OFF;
	private: System::Windows::Forms::CheckBox^  btnRightBlowing_OFF;
	private: System::Windows::Forms::Label^  lblRightChuck;
	private: System::Windows::Forms::CheckBox^  btnRightBlowing_ON;
	private: System::Windows::Forms::CheckBox^  btnOpenRightChuck;
	private: System::Windows::Forms::Label^  lblRightBlowing;
	private: System::Windows::Forms::CheckBox^  btnCloseRightChuck;
	private: System::Windows::Forms::CheckBox^  btnRightEject_OFF;
	private: System::Windows::Forms::CheckBox^  btnRightEject_ON;
	private: System::Windows::Forms::Label^  lblRightEject;
	private: System::Windows::Forms::GroupBox^  gbLeftSpindle;
	private: System::Windows::Forms::Label^  lblLeftMotor;
	private: System::Windows::Forms::CheckBox^  btnLeftMotor_ON;
	private: System::Windows::Forms::CheckBox^  btnLeftMotor_OFF;
	private: System::Windows::Forms::CheckBox^  btnLeftBlowing_OFF;
	private: System::Windows::Forms::Label^  lblLeftChuck;
	private: System::Windows::Forms::CheckBox^  btnLeftBlowing_ON;
	private: System::Windows::Forms::CheckBox^  btnOpenLeftChuck;
	private: System::Windows::Forms::Label^  lblLeftBlowing;
	private: System::Windows::Forms::CheckBox^  btnCloseLeftChuck;
	private: System::Windows::Forms::CheckBox^  btnLeftEject_OFF;
	private: System::Windows::Forms::CheckBox^  btnLeftEject_ON;
	private: System::Windows::Forms::Label^  lblLeftEject;
	private: System::Windows::Forms::Button^  btnCalibrateRightWeight;
	private: System::Windows::Forms::Label^  lblCalibrateRightWeight;
	private: System::Windows::Forms::Label^  tbLeftCompensationStep;
	private: System::Windows::Forms::CheckBox^  cbRestartBeginOfArea;
	private: System::Windows::Forms::Label^  lblRestartBeginOfArea;
	private: System::Windows::Forms::TabPage^  tabPageSharpen;
	//private: System::Windows::Forms::TextBox^  tbSharpenSpeed;
	private: System::Windows::Forms::Label^  lblSharpenSpeed;
	//private: System::Windows::Forms::TextBox^  tbNbOfFwBwBeforeTapeMove;
	private: System::Windows::Forms::Label^  lblNbOfFwBwBeforeTapeMove;
	//private: System::Windows::Forms::TextBox^  tbNbOfFwBwSharpen;
	private: System::Windows::Forms::Label^  lblNbOfFwBwSharpen;
	//private: System::Windows::Forms::TextBox^  tbSharpenHeight;
	private: System::Windows::Forms::Label^  lblSharpenHeight;
	private: System::Windows::Forms::TabPage^  tabPagePearling;
	private: System::Windows::Forms::Button^  btnRAZRightMotorUseTime;
	private: System::Windows::Forms::TextBox^  tbRightMotorUseTime;
	//private: System::Windows::Forms::TextBox^  tbCompenseLeftWeight;
	private: System::Windows::Forms::Button^  btnRAZLeftMotorUseTime;
	private: System::Windows::Forms::TextBox^  tbLeftMotorUseTime;
	private: System::Windows::Forms::Label^  lblMotorUseTime;
	//private: System::Windows::Forms::TextBox^  tbCompenseRightWeight;
	private: System::Windows::Forms::Label^  lblCompenseWeight;
	private: System::Windows::Forms::TextBox^  tbRightMotorCurrent;
	private: System::Windows::Forms::TextBox^  tbRightMotorSpeed;
	private: System::Windows::Forms::TextBox^  tbLeftMotorCurrent;
	private: System::Windows::Forms::Label^  lblMotorCurrent;
	private: System::Windows::Forms::TextBox^  tbLeftMotorSpeed;
	private: System::Windows::Forms::Label^  lblMotorSpeed;
	private: System::Windows::Forms::Button^  btnSafe;
	private: MondemaComponents::ComboBoxAllowed^  cobCalibrationPosition;
	private: System::Windows::Forms::Button^  btnRAZRightSpindleUseTime;
	private: System::Windows::Forms::TextBox^  tbRightSpindleUseTime;
	private: System::Windows::Forms::Button^  btnRAZLeftSpindleUseTime;
	private: System::Windows::Forms::TextBox^  tbLeftSpindleUseTime;
	//private: System::Windows::Forms::TextBox^  tbLeftSpindleManualSpeed;
	//private: System::Windows::Forms::TextBox^  tbRightSpindleManualSpeed;
	private: System::Windows::Forms::Label^  lblSpindleManualSpeed;
	//private: System::Windows::Forms::TextBox^  tbLeftSpindleRatio;
	//private: System::Windows::Forms::TextBox^  tbRightSpindleRatio;
	private: System::Windows::Forms::Label^  lblSpindleRatio;
	private: System::Windows::Forms::Label^  lblSpindleUseTime;
	public:
		void UpdateUI(void);

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~PearlingManualScreen()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPageAxes;
	private: System::Windows::Forms::GroupBox^  gbXaxis;
	private: System::Windows::Forms::GroupBox^  gbZ2axis;
	private: System::Windows::Forms::GroupBox^  gbYaxis;
	private: System::Windows::Forms::Label^  lblRobotPosition;
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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPageAxes = (gcnew System::Windows::Forms::TabPage());
			this->btnSafe = (gcnew System::Windows::Forms::Button());
			this->cobCalibrationPosition = (gcnew MondemaComponents::ComboBoxAllowed());
			this->gbZ1axis = (gcnew System::Windows::Forms::GroupBox());
			this->lblRobotPosition = (gcnew System::Windows::Forms::Label());
			this->gbXaxis = (gcnew System::Windows::Forms::GroupBox());
			this->gbZ2axis = (gcnew System::Windows::Forms::GroupBox());
			this->gbYaxis = (gcnew System::Windows::Forms::GroupBox());
			this->tabPageStick = (gcnew System::Windows::Forms::TabPage());
			this->gbRightSpindle = (gcnew System::Windows::Forms::GroupBox());
			this->lblRightMotor = (gcnew System::Windows::Forms::Label());
			this->btnRightMotor_ON = (gcnew System::Windows::Forms::CheckBox());
			this->btnRightMotor_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnRightBlowing_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->lblRightChuck = (gcnew System::Windows::Forms::Label());
			this->btnRightBlowing_ON = (gcnew System::Windows::Forms::CheckBox());
			this->btnOpenRightChuck = (gcnew System::Windows::Forms::CheckBox());
			this->lblRightBlowing = (gcnew System::Windows::Forms::Label());
			this->btnCloseRightChuck = (gcnew System::Windows::Forms::CheckBox());
			this->btnRightEject_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnRightEject_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblRightEject = (gcnew System::Windows::Forms::Label());
			this->gbLeftSpindle = (gcnew System::Windows::Forms::GroupBox());
			this->lblLeftMotor = (gcnew System::Windows::Forms::Label());
			this->btnLeftMotor_ON = (gcnew System::Windows::Forms::CheckBox());
			this->btnLeftMotor_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnLeftBlowing_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->lblLeftChuck = (gcnew System::Windows::Forms::Label());
			this->btnLeftBlowing_ON = (gcnew System::Windows::Forms::CheckBox());
			this->btnOpenLeftChuck = (gcnew System::Windows::Forms::CheckBox());
			this->lblLeftBlowing = (gcnew System::Windows::Forms::Label());
			this->btnCloseLeftChuck = (gcnew System::Windows::Forms::CheckBox());
			this->btnLeftEject_OFF = (gcnew System::Windows::Forms::CheckBox());
			this->btnLeftEject_ON = (gcnew System::Windows::Forms::CheckBox());
			this->lblLeftEject = (gcnew System::Windows::Forms::Label());
			this->tabPageRecipe = (gcnew System::Windows::Forms::TabPage());
			this->lblRightSpindle = (gcnew System::Windows::Forms::Label());
			this->lblLeftSpindle = (gcnew System::Windows::Forms::Label());
			this->cbStopOnWeightOutOfTolerance = (gcnew System::Windows::Forms::CheckBox());
			this->lblStopOnWeightOutOfTolerance = (gcnew System::Windows::Forms::Label());
			this->cbStopOnStickBreak = (gcnew System::Windows::Forms::CheckBox());
			this->lblStopOnStickBreak = (gcnew System::Windows::Forms::Label());
			this->cbStopOnVacuumLoss = (gcnew System::Windows::Forms::CheckBox());
			this->lblStopOnVacuumLoss = (gcnew System::Windows::Forms::Label());
			this->lblWeightToleranceValue = (gcnew System::Windows::Forms::Label());
			this->lblWeightTolerance = (gcnew System::Windows::Forms::Label());
			this->cbSimPearling = (gcnew System::Windows::Forms::CheckBox());
			this->lblSimPearling = (gcnew System::Windows::Forms::Label());
			this->tbLeftCompensationStep = (gcnew System::Windows::Forms::Label());
			this->tbRightCompensationStep = (gcnew System::Windows::Forms::Label());
			this->lblCompensationStep = (gcnew System::Windows::Forms::Label());
			this->cbRestartBeginOfArea = (gcnew System::Windows::Forms::CheckBox());
			this->lblRestartBeginOfArea = (gcnew System::Windows::Forms::Label());
			this->tabPageSharpen = (gcnew System::Windows::Forms::TabPage());
			this->lblMinHoldLength = (gcnew System::Windows::Forms::Label());
			this->lblSpindleSharpenSpeed = (gcnew System::Windows::Forms::Label());
			this->lblMinHoldLengthValue = (gcnew System::Windows::Forms::Label());
			this->lblSharpenHeightValue = (gcnew System::Windows::Forms::Label());
			this->lblSharpenSpeedValue = (gcnew System::Windows::Forms::Label());
			this->lblNbOfFwBwSharpenValue = (gcnew System::Windows::Forms::Label());
			this->lblNbOfFwBwBeforeTapeMoveValue = (gcnew System::Windows::Forms::Label());
			this->lblSpindleSharpenSpeedValue = (gcnew System::Windows::Forms::Label());
			this->lblSharpenSpeed = (gcnew System::Windows::Forms::Label());
			this->lblNbOfFwBwBeforeTapeMove = (gcnew System::Windows::Forms::Label());
			this->lblNbOfFwBwSharpen = (gcnew System::Windows::Forms::Label());
			this->lblSharpenHeight = (gcnew System::Windows::Forms::Label());
			this->tabPagePearling = (gcnew System::Windows::Forms::TabPage());
			this->lblRightSpindlePearling = (gcnew System::Windows::Forms::Label());
			this->lblLeftSpindlePearling = (gcnew System::Windows::Forms::Label());
			this->tbRightSpindlePearlsCounter = (gcnew System::Windows::Forms::TextBox());
			this->tbLeftSpindlePearlsCounter = (gcnew System::Windows::Forms::TextBox());
			this->lblSpindlePearlsCounter = (gcnew System::Windows::Forms::Label());
			this->lblCurrentMotorMaxTh = (gcnew System::Windows::Forms::Label());
			this->lblCurrentMotorMaxThreshold = (gcnew System::Windows::Forms::Label());
			this->tbWeightSensor = (gcnew System::Windows::Forms::TextBox());
			this->lblWeightSensor = (gcnew System::Windows::Forms::Label());
			this->tbRightHeightSensor = (gcnew System::Windows::Forms::TextBox());
			this->tbLeftHeightSensor = (gcnew System::Windows::Forms::TextBox());
			this->lblHeightSensor = (gcnew System::Windows::Forms::Label());
			this->lblMotorStopTimeout = (gcnew System::Windows::Forms::Label());
			this->lblMotorStartTimeout = (gcnew System::Windows::Forms::Label());
			this->lblRightMotorStopTimeout = (gcnew System::Windows::Forms::Label());
			this->lblLeftMotorStopTimeout = (gcnew System::Windows::Forms::Label());
			this->lblRightSpindleRatio = (gcnew System::Windows::Forms::Label());
			this->lblRightCompenseWeight = (gcnew System::Windows::Forms::Label());
			this->lblRightSpindleManualSpeedValue = (gcnew System::Windows::Forms::Label());
			this->lblLeftSpindleRatio = (gcnew System::Windows::Forms::Label());
			this->lblLeftCompenseWeight = (gcnew System::Windows::Forms::Label());
			this->lblLeftSpindleManualSpeedValue = (gcnew System::Windows::Forms::Label());
			this->lblRightMotorStartTimeout = (gcnew System::Windows::Forms::Label());
			this->lblLeftMotorStartTimeout = (gcnew System::Windows::Forms::Label());
			this->lblCurrentMotorWarnTh = (gcnew System::Windows::Forms::Label());
			this->lblCurrentMotorMinTh = (gcnew System::Windows::Forms::Label());
			this->lblCurrentMotorWarnThreshold = (gcnew System::Windows::Forms::Label());
			this->lblCurrentMotorMinThreshold = (gcnew System::Windows::Forms::Label());
			this->lblSpindleManualSpeed = (gcnew System::Windows::Forms::Label());
			this->lblSpindleRatio = (gcnew System::Windows::Forms::Label());
			this->btnRAZRightSpindleUseTime = (gcnew System::Windows::Forms::Button());
			this->tbRightSpindleUseTime = (gcnew System::Windows::Forms::TextBox());
			this->btnRAZLeftSpindleUseTime = (gcnew System::Windows::Forms::Button());
			this->tbLeftSpindleUseTime = (gcnew System::Windows::Forms::TextBox());
			this->lblSpindleUseTime = (gcnew System::Windows::Forms::Label());
			this->btnRAZRightMotorUseTime = (gcnew System::Windows::Forms::Button());
			this->tbRightMotorUseTime = (gcnew System::Windows::Forms::TextBox());
			this->btnRAZLeftMotorUseTime = (gcnew System::Windows::Forms::Button());
			this->tbLeftMotorUseTime = (gcnew System::Windows::Forms::TextBox());
			this->lblMotorUseTime = (gcnew System::Windows::Forms::Label());
			this->lblCompenseWeight = (gcnew System::Windows::Forms::Label());
			this->tbRightMotorCurrent = (gcnew System::Windows::Forms::TextBox());
			this->tbRightMotorSpeed = (gcnew System::Windows::Forms::TextBox());
			this->tbLeftMotorCurrent = (gcnew System::Windows::Forms::TextBox());
			this->lblMotorCurrent = (gcnew System::Windows::Forms::Label());
			this->tbLeftMotorSpeed = (gcnew System::Windows::Forms::TextBox());
			this->lblMotorSpeed = (gcnew System::Windows::Forms::Label());
			this->tabPageCalibration = (gcnew System::Windows::Forms::TabPage());
			this->dgvWeightTableLeft = (gcnew System::Windows::Forms::DataGridView());
			this->dgvWeightTableRight = (gcnew System::Windows::Forms::DataGridView());
			this->chrRight = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chrLeft = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->btnCalibrateRightWeight = (gcnew System::Windows::Forms::Button());
			this->lblCalibrateRightWeight = (gcnew System::Windows::Forms::Label());
			this->btnCalibrateLeftWeight = (gcnew System::Windows::Forms::Button());
			this->lblCalibrateLeftWeight = (gcnew System::Windows::Forms::Label());
			this->tabControl->SuspendLayout();
			this->tabPageAxes->SuspendLayout();
			this->tabPageStick->SuspendLayout();
			this->gbRightSpindle->SuspendLayout();
			this->gbLeftSpindle->SuspendLayout();
			this->tabPageRecipe->SuspendLayout();
			this->tabPageSharpen->SuspendLayout();
			this->tabPagePearling->SuspendLayout();
			this->tabPageCalibration->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvWeightTableLeft))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvWeightTableRight))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrRight))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrLeft))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPageAxes);
			this->tabControl->Controls->Add(this->tabPageStick);
			this->tabControl->Controls->Add(this->tabPageRecipe);
			this->tabControl->Controls->Add(this->tabPageSharpen);
			this->tabControl->Controls->Add(this->tabPagePearling);
			this->tabControl->Controls->Add(this->tabPageCalibration);
			this->tabControl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tabControl->ItemSize = System::Drawing::Size(134, 45);
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1578, 895);
			this->tabControl->TabIndex = 2;
			this->tabControl->Tag = L"";
			// 
			// tabPageAxes
			// 
			this->tabPageAxes->Controls->Add(this->btnSafe);
			this->tabPageAxes->Controls->Add(this->cobCalibrationPosition);
			this->tabPageAxes->Controls->Add(this->gbZ1axis);
			this->tabPageAxes->Controls->Add(this->lblRobotPosition);
			this->tabPageAxes->Controls->Add(this->gbXaxis);
			this->tabPageAxes->Controls->Add(this->gbZ2axis);
			this->tabPageAxes->Controls->Add(this->gbYaxis);
			this->tabPageAxes->Location = System::Drawing::Point(4, 49);
			this->tabPageAxes->Name = L"tabPageAxes";
			this->tabPageAxes->Padding = System::Windows::Forms::Padding(3);
			this->tabPageAxes->Size = System::Drawing::Size(1570, 842);
			this->tabPageAxes->TabIndex = 0;
			this->tabPageAxes->Text = L"Axes";
			this->tabPageAxes->UseVisualStyleBackColor = true;
			// 
			// btnSafe
			// 
			this->btnSafe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSafe->Location = System::Drawing::Point(828, 27);
			this->btnSafe->Name = L"btnSafe";
			this->btnSafe->Size = System::Drawing::Size(90, 90);
			this->btnSafe->TabIndex = 136;
			this->btnSafe->Tag = L"0";
			this->btnSafe->Text = L"Safe";
			this->btnSafe->UseVisualStyleBackColor = true;
			this->btnSafe->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnSafe_Click);
			// 
			// cobCalibrationPosition
			// 
			this->cobCalibrationPosition->AllowResizeDropDown = false;
			this->cobCalibrationPosition->ControlSize = System::Drawing::Size(225, 225);
			this->cobCalibrationPosition->DropDownSizeMode = MondemaComponents::CustomComboBox::SizeMode::UseDropDownSize;
			this->cobCalibrationPosition->DropSize = System::Drawing::Size(182, 159);
			this->cobCalibrationPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->cobCalibrationPosition->FormattingEnabled = true;
			this->cobCalibrationPosition->Location = System::Drawing::Point(293, 51);
			this->cobCalibrationPosition->Name = L"cobCalibrationPosition";
			this->cobCalibrationPosition->Size = System::Drawing::Size(473, 37);
			this->cobCalibrationPosition->TabIndex = 134;
			this->cobCalibrationPosition->Tag = L"2";
			this->cobCalibrationPosition->SetItem += gcnew System::EventHandler<MondemaComponents::ItemEventArgs^ >(this, &PearlingManualScreen::cobCalibrationPosition_OnSetItem);
			this->cobCalibrationPosition->SelectedIndexChanged += gcnew System::EventHandler(this, &PearlingManualScreen::cobCalibrationPosition_SelectedIndexChanged);
			// 
			// gbZ1axis
			// 
			this->gbZ1axis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbZ1axis->Location = System::Drawing::Point(48, 458);
			this->gbZ1axis->Name = L"gbZ1axis";
			this->gbZ1axis->Size = System::Drawing::Size(728, 270);
			this->gbZ1axis->TabIndex = 133;
			this->gbZ1axis->TabStop = false;
			this->gbZ1axis->Tag = L"2";
			// 
			// lblRobotPosition
			// 
			this->lblRobotPosition->AutoSize = true;
			this->lblRobotPosition->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRobotPosition->Location = System::Drawing::Point(42, 56);
			this->lblRobotPosition->Name = L"lblRobotPosition";
			this->lblRobotPosition->Size = System::Drawing::Size(108, 29);
			this->lblRobotPosition->TabIndex = 96;
			this->lblRobotPosition->Tag = L"2";
			this->lblRobotPosition->Text = L"Position";
			// 
			// gbXaxis
			// 
			this->gbXaxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbXaxis->Location = System::Drawing::Point(48, 179);
			this->gbXaxis->Name = L"gbXaxis";
			this->gbXaxis->Size = System::Drawing::Size(728, 270);
			this->gbXaxis->TabIndex = 45;
			this->gbXaxis->TabStop = false;
			this->gbXaxis->Tag = L"2";
			// 
			// gbZ2axis
			// 
			this->gbZ2axis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbZ2axis->Location = System::Drawing::Point(788, 458);
			this->gbZ2axis->Name = L"gbZ2axis";
			this->gbZ2axis->Size = System::Drawing::Size(728, 270);
			this->gbZ2axis->TabIndex = 43;
			this->gbZ2axis->TabStop = false;
			this->gbZ2axis->Tag = L"2";
			// 
			// gbYaxis
			// 
			this->gbYaxis->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gbYaxis->Location = System::Drawing::Point(785, 179);
			this->gbYaxis->Name = L"gbYaxis";
			this->gbYaxis->Size = System::Drawing::Size(728, 270);
			this->gbYaxis->TabIndex = 42;
			this->gbYaxis->TabStop = false;
			this->gbYaxis->Tag = L"2";
			// 
			// tabPageStick
			// 
			this->tabPageStick->Controls->Add(this->gbRightSpindle);
			this->tabPageStick->Controls->Add(this->gbLeftSpindle);
			this->tabPageStick->Location = System::Drawing::Point(4, 49);
			this->tabPageStick->Name = L"tabPageStick";
			this->tabPageStick->Padding = System::Windows::Forms::Padding(3);
			this->tabPageStick->Size = System::Drawing::Size(1570, 842);
			this->tabPageStick->TabIndex = 3;
			this->tabPageStick->Text = L"Stick";
			this->tabPageStick->UseVisualStyleBackColor = true;
			// 
			// gbRightSpindle
			// 
			this->gbRightSpindle->Controls->Add(this->lblRightMotor);
			this->gbRightSpindle->Controls->Add(this->btnRightMotor_ON);
			this->gbRightSpindle->Controls->Add(this->btnRightMotor_OFF);
			this->gbRightSpindle->Controls->Add(this->btnRightBlowing_OFF);
			this->gbRightSpindle->Controls->Add(this->lblRightChuck);
			this->gbRightSpindle->Controls->Add(this->btnRightBlowing_ON);
			this->gbRightSpindle->Controls->Add(this->btnOpenRightChuck);
			this->gbRightSpindle->Controls->Add(this->lblRightBlowing);
			this->gbRightSpindle->Controls->Add(this->btnCloseRightChuck);
			this->gbRightSpindle->Controls->Add(this->btnRightEject_OFF);
			this->gbRightSpindle->Controls->Add(this->btnRightEject_ON);
			this->gbRightSpindle->Controls->Add(this->lblRightEject);
			this->gbRightSpindle->Location = System::Drawing::Point(791, 41);
			this->gbRightSpindle->Name = L"gbRightSpindle";
			this->gbRightSpindle->Size = System::Drawing::Size(690, 510);
			this->gbRightSpindle->TabIndex = 46;
			this->gbRightSpindle->TabStop = false;
			this->gbRightSpindle->Tag = L"1";
			// 
			// lblRightMotor
			// 
			this->lblRightMotor->AutoSize = true;
			this->lblRightMotor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRightMotor->Location = System::Drawing::Point(18, 66);
			this->lblRightMotor->Name = L"lblRightMotor";
			this->lblRightMotor->Size = System::Drawing::Size(0, 29);
			this->lblRightMotor->TabIndex = 30;
			this->lblRightMotor->Tag = L"1";
			// 
			// btnRightMotor_ON
			// 
			this->btnRightMotor_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRightMotor_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRightMotor_ON->Location = System::Drawing::Point(450, 38);
			this->btnRightMotor_ON->Name = L"btnRightMotor_ON";
			this->btnRightMotor_ON->Size = System::Drawing::Size(90, 90);
			this->btnRightMotor_ON->TabIndex = 31;
			this->btnRightMotor_ON->Tag = L"1";
			this->btnRightMotor_ON->Text = L"ON";
			this->btnRightMotor_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRightMotor_ON->UseVisualStyleBackColor = true;
			this->btnRightMotor_ON->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRightMotor_ON_Click);
			// 
			// btnRightMotor_OFF
			// 
			this->btnRightMotor_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRightMotor_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRightMotor_OFF->Location = System::Drawing::Point(555, 38);
			this->btnRightMotor_OFF->Name = L"btnRightMotor_OFF";
			this->btnRightMotor_OFF->Size = System::Drawing::Size(90, 90);
			this->btnRightMotor_OFF->TabIndex = 32;
			this->btnRightMotor_OFF->Tag = L"1";
			this->btnRightMotor_OFF->Text = L"OFF";
			this->btnRightMotor_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRightMotor_OFF->UseVisualStyleBackColor = true;
			this->btnRightMotor_OFF->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRightMotor_OFF_Click);
			// 
			// btnRightBlowing_OFF
			// 
			this->btnRightBlowing_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRightBlowing_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRightBlowing_OFF->Location = System::Drawing::Point(555, 398);
			this->btnRightBlowing_OFF->Name = L"btnRightBlowing_OFF";
			this->btnRightBlowing_OFF->Size = System::Drawing::Size(90, 90);
			this->btnRightBlowing_OFF->TabIndex = 41;
			this->btnRightBlowing_OFF->Tag = L"1";
			this->btnRightBlowing_OFF->Text = L"OFF";
			this->btnRightBlowing_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRightBlowing_OFF->UseVisualStyleBackColor = true;
			this->btnRightBlowing_OFF->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRightBlowing_OFF_Click);
			// 
			// lblRightChuck
			// 
			this->lblRightChuck->AutoSize = true;
			this->lblRightChuck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRightChuck->Location = System::Drawing::Point(18, 187);
			this->lblRightChuck->Name = L"lblRightChuck";
			this->lblRightChuck->Size = System::Drawing::Size(0, 29);
			this->lblRightChuck->TabIndex = 33;
			this->lblRightChuck->Tag = L"1";
			// 
			// btnRightBlowing_ON
			// 
			this->btnRightBlowing_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRightBlowing_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRightBlowing_ON->Location = System::Drawing::Point(450, 398);
			this->btnRightBlowing_ON->Name = L"btnRightBlowing_ON";
			this->btnRightBlowing_ON->Size = System::Drawing::Size(90, 90);
			this->btnRightBlowing_ON->TabIndex = 40;
			this->btnRightBlowing_ON->Tag = L"1";
			this->btnRightBlowing_ON->Text = L"ON";
			this->btnRightBlowing_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRightBlowing_ON->UseVisualStyleBackColor = true;
			this->btnRightBlowing_ON->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRightBlowing_ON_Click);
			// 
			// btnOpenRightChuck
			// 
			this->btnOpenRightChuck->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnOpenRightChuck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnOpenRightChuck->Location = System::Drawing::Point(450, 158);
			this->btnOpenRightChuck->Name = L"btnOpenRightChuck";
			this->btnOpenRightChuck->Size = System::Drawing::Size(90, 90);
			this->btnOpenRightChuck->TabIndex = 34;
			this->btnOpenRightChuck->Tag = L"1";
			this->btnOpenRightChuck->Text = L"ON";
			this->btnOpenRightChuck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnOpenRightChuck->UseVisualStyleBackColor = true;
			this->btnOpenRightChuck->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnOpenRightChuck_Click);
			// 
			// lblRightBlowing
			// 
			this->lblRightBlowing->AutoSize = true;
			this->lblRightBlowing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRightBlowing->Location = System::Drawing::Point(18, 426);
			this->lblRightBlowing->Name = L"lblRightBlowing";
			this->lblRightBlowing->Size = System::Drawing::Size(0, 29);
			this->lblRightBlowing->TabIndex = 39;
			this->lblRightBlowing->Tag = L"1";
			// 
			// btnCloseRightChuck
			// 
			this->btnCloseRightChuck->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnCloseRightChuck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCloseRightChuck->Location = System::Drawing::Point(555, 158);
			this->btnCloseRightChuck->Name = L"btnCloseRightChuck";
			this->btnCloseRightChuck->Size = System::Drawing::Size(90, 90);
			this->btnCloseRightChuck->TabIndex = 35;
			this->btnCloseRightChuck->Tag = L"1";
			this->btnCloseRightChuck->Text = L"OFF";
			this->btnCloseRightChuck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnCloseRightChuck->UseVisualStyleBackColor = true;
			this->btnCloseRightChuck->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnCloseRightChuck_Click);
			// 
			// btnRightEject_OFF
			// 
			this->btnRightEject_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRightEject_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRightEject_OFF->Location = System::Drawing::Point(555, 278);
			this->btnRightEject_OFF->Name = L"btnRightEject_OFF";
			this->btnRightEject_OFF->Size = System::Drawing::Size(90, 90);
			this->btnRightEject_OFF->TabIndex = 38;
			this->btnRightEject_OFF->Tag = L"1";
			this->btnRightEject_OFF->Text = L"OFF";
			this->btnRightEject_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRightEject_OFF->UseVisualStyleBackColor = true;
			this->btnRightEject_OFF->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRightEject_OFF_Click);
			// 
			// btnRightEject_ON
			// 
			this->btnRightEject_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnRightEject_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRightEject_ON->Location = System::Drawing::Point(450, 278);
			this->btnRightEject_ON->Name = L"btnRightEject_ON";
			this->btnRightEject_ON->Size = System::Drawing::Size(90, 90);
			this->btnRightEject_ON->TabIndex = 37;
			this->btnRightEject_ON->Tag = L"1";
			this->btnRightEject_ON->Text = L"ON";
			this->btnRightEject_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRightEject_ON->UseVisualStyleBackColor = true;
			this->btnRightEject_ON->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRightEject_ON_Click);
			// 
			// lblRightEject
			// 
			this->lblRightEject->AutoSize = true;
			this->lblRightEject->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRightEject->Location = System::Drawing::Point(18, 306);
			this->lblRightEject->Name = L"lblRightEject";
			this->lblRightEject->Size = System::Drawing::Size(0, 29);
			this->lblRightEject->TabIndex = 36;
			this->lblRightEject->Tag = L"1";
			// 
			// gbLeftSpindle
			// 
			this->gbLeftSpindle->Controls->Add(this->lblLeftMotor);
			this->gbLeftSpindle->Controls->Add(this->btnLeftMotor_ON);
			this->gbLeftSpindle->Controls->Add(this->btnLeftMotor_OFF);
			this->gbLeftSpindle->Controls->Add(this->btnLeftBlowing_OFF);
			this->gbLeftSpindle->Controls->Add(this->lblLeftChuck);
			this->gbLeftSpindle->Controls->Add(this->btnLeftBlowing_ON);
			this->gbLeftSpindle->Controls->Add(this->btnOpenLeftChuck);
			this->gbLeftSpindle->Controls->Add(this->lblLeftBlowing);
			this->gbLeftSpindle->Controls->Add(this->btnCloseLeftChuck);
			this->gbLeftSpindle->Controls->Add(this->btnLeftEject_OFF);
			this->gbLeftSpindle->Controls->Add(this->btnLeftEject_ON);
			this->gbLeftSpindle->Controls->Add(this->lblLeftEject);
			this->gbLeftSpindle->Location = System::Drawing::Point(23, 41);
			this->gbLeftSpindle->Name = L"gbLeftSpindle";
			this->gbLeftSpindle->Size = System::Drawing::Size(690, 510);
			this->gbLeftSpindle->TabIndex = 45;
			this->gbLeftSpindle->TabStop = false;
			this->gbLeftSpindle->Tag = L"1";
			// 
			// lblLeftMotor
			// 
			this->lblLeftMotor->AutoSize = true;
			this->lblLeftMotor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLeftMotor->Location = System::Drawing::Point(18, 66);
			this->lblLeftMotor->Name = L"lblLeftMotor";
			this->lblLeftMotor->Size = System::Drawing::Size(0, 29);
			this->lblLeftMotor->TabIndex = 30;
			this->lblLeftMotor->Tag = L"1";
			// 
			// btnLeftMotor_ON
			// 
			this->btnLeftMotor_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnLeftMotor_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLeftMotor_ON->Location = System::Drawing::Point(450, 38);
			this->btnLeftMotor_ON->Name = L"btnLeftMotor_ON";
			this->btnLeftMotor_ON->Size = System::Drawing::Size(90, 90);
			this->btnLeftMotor_ON->TabIndex = 31;
			this->btnLeftMotor_ON->Tag = L"1";
			this->btnLeftMotor_ON->Text = L"ON";
			this->btnLeftMotor_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLeftMotor_ON->UseVisualStyleBackColor = true;
			this->btnLeftMotor_ON->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnLeftMotor_ON_Click);
			// 
			// btnLeftMotor_OFF
			// 
			this->btnLeftMotor_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnLeftMotor_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLeftMotor_OFF->Location = System::Drawing::Point(555, 38);
			this->btnLeftMotor_OFF->Name = L"btnLeftMotor_OFF";
			this->btnLeftMotor_OFF->Size = System::Drawing::Size(90, 90);
			this->btnLeftMotor_OFF->TabIndex = 32;
			this->btnLeftMotor_OFF->Tag = L"1";
			this->btnLeftMotor_OFF->Text = L"OFF";
			this->btnLeftMotor_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLeftMotor_OFF->UseVisualStyleBackColor = true;
			this->btnLeftMotor_OFF->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnLeftMotor_OFF_Click);
			// 
			// btnLeftBlowing_OFF
			// 
			this->btnLeftBlowing_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnLeftBlowing_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLeftBlowing_OFF->Location = System::Drawing::Point(555, 398);
			this->btnLeftBlowing_OFF->Name = L"btnLeftBlowing_OFF";
			this->btnLeftBlowing_OFF->Size = System::Drawing::Size(90, 90);
			this->btnLeftBlowing_OFF->TabIndex = 41;
			this->btnLeftBlowing_OFF->Tag = L"1";
			this->btnLeftBlowing_OFF->Text = L"OFF";
			this->btnLeftBlowing_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLeftBlowing_OFF->UseVisualStyleBackColor = true;
			this->btnLeftBlowing_OFF->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnLeftBlowing_OFF_Click);
			// 
			// lblLeftChuck
			// 
			this->lblLeftChuck->AutoSize = true;
			this->lblLeftChuck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLeftChuck->Location = System::Drawing::Point(18, 186);
			this->lblLeftChuck->Name = L"lblLeftChuck";
			this->lblLeftChuck->Size = System::Drawing::Size(0, 29);
			this->lblLeftChuck->TabIndex = 33;
			this->lblLeftChuck->Tag = L"1";
			// 
			// btnLeftBlowing_ON
			// 
			this->btnLeftBlowing_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnLeftBlowing_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLeftBlowing_ON->Location = System::Drawing::Point(450, 398);
			this->btnLeftBlowing_ON->Name = L"btnLeftBlowing_ON";
			this->btnLeftBlowing_ON->Size = System::Drawing::Size(90, 90);
			this->btnLeftBlowing_ON->TabIndex = 40;
			this->btnLeftBlowing_ON->Tag = L"1";
			this->btnLeftBlowing_ON->Text = L"ON";
			this->btnLeftBlowing_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLeftBlowing_ON->UseVisualStyleBackColor = true;
			this->btnLeftBlowing_ON->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnLeftBlowing_ON_Click);
			// 
			// btnOpenLeftChuck
			// 
			this->btnOpenLeftChuck->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnOpenLeftChuck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnOpenLeftChuck->Location = System::Drawing::Point(450, 158);
			this->btnOpenLeftChuck->Name = L"btnOpenLeftChuck";
			this->btnOpenLeftChuck->Size = System::Drawing::Size(90, 90);
			this->btnOpenLeftChuck->TabIndex = 34;
			this->btnOpenLeftChuck->Tag = L"1";
			this->btnOpenLeftChuck->Text = L"ON";
			this->btnOpenLeftChuck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnOpenLeftChuck->UseVisualStyleBackColor = true;
			this->btnOpenLeftChuck->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnOpenLeftChuck_Click);
			// 
			// lblLeftBlowing
			// 
			this->lblLeftBlowing->AutoSize = true;
			this->lblLeftBlowing->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLeftBlowing->Location = System::Drawing::Point(18, 426);
			this->lblLeftBlowing->Name = L"lblLeftBlowing";
			this->lblLeftBlowing->Size = System::Drawing::Size(0, 29);
			this->lblLeftBlowing->TabIndex = 39;
			this->lblLeftBlowing->Tag = L"1";
			// 
			// btnCloseLeftChuck
			// 
			this->btnCloseLeftChuck->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnCloseLeftChuck->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCloseLeftChuck->Location = System::Drawing::Point(555, 158);
			this->btnCloseLeftChuck->Name = L"btnCloseLeftChuck";
			this->btnCloseLeftChuck->Size = System::Drawing::Size(90, 90);
			this->btnCloseLeftChuck->TabIndex = 35;
			this->btnCloseLeftChuck->Tag = L"1";
			this->btnCloseLeftChuck->Text = L"OFF";
			this->btnCloseLeftChuck->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnCloseLeftChuck->UseVisualStyleBackColor = true;
			this->btnCloseLeftChuck->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnCloseLeftChuck_Click);
			// 
			// btnLeftEject_OFF
			// 
			this->btnLeftEject_OFF->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnLeftEject_OFF->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLeftEject_OFF->Location = System::Drawing::Point(555, 278);
			this->btnLeftEject_OFF->Name = L"btnLeftEject_OFF";
			this->btnLeftEject_OFF->Size = System::Drawing::Size(90, 90);
			this->btnLeftEject_OFF->TabIndex = 38;
			this->btnLeftEject_OFF->Tag = L"1";
			this->btnLeftEject_OFF->Text = L"OFF";
			this->btnLeftEject_OFF->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLeftEject_OFF->UseVisualStyleBackColor = true;
			this->btnLeftEject_OFF->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnLeftEject_OFF_Click);
			// 
			// btnLeftEject_ON
			// 
			this->btnLeftEject_ON->Appearance = System::Windows::Forms::Appearance::Button;
			this->btnLeftEject_ON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLeftEject_ON->Location = System::Drawing::Point(450, 278);
			this->btnLeftEject_ON->Name = L"btnLeftEject_ON";
			this->btnLeftEject_ON->Size = System::Drawing::Size(90, 90);
			this->btnLeftEject_ON->TabIndex = 37;
			this->btnLeftEject_ON->Tag = L"1";
			this->btnLeftEject_ON->Text = L"ON";
			this->btnLeftEject_ON->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLeftEject_ON->UseVisualStyleBackColor = true;
			this->btnLeftEject_ON->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnLeftEject_ON_Click);
			// 
			// lblLeftEject
			// 
			this->lblLeftEject->AutoSize = true;
			this->lblLeftEject->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLeftEject->Location = System::Drawing::Point(18, 306);
			this->lblLeftEject->Name = L"lblLeftEject";
			this->lblLeftEject->Size = System::Drawing::Size(0, 29);
			this->lblLeftEject->TabIndex = 36;
			this->lblLeftEject->Tag = L"1";
			// 
			// tabPageRecipe
			// 
			this->tabPageRecipe->Controls->Add(this->lblRightSpindle);
			this->tabPageRecipe->Controls->Add(this->lblLeftSpindle);
			this->tabPageRecipe->Controls->Add(this->cbStopOnWeightOutOfTolerance);
			this->tabPageRecipe->Controls->Add(this->lblStopOnWeightOutOfTolerance);
			this->tabPageRecipe->Controls->Add(this->cbStopOnStickBreak);
			this->tabPageRecipe->Controls->Add(this->lblStopOnStickBreak);
			this->tabPageRecipe->Controls->Add(this->cbStopOnVacuumLoss);
			this->tabPageRecipe->Controls->Add(this->lblStopOnVacuumLoss);
			this->tabPageRecipe->Controls->Add(this->lblWeightToleranceValue);
			this->tabPageRecipe->Controls->Add(this->lblWeightTolerance);
			this->tabPageRecipe->Controls->Add(this->cbSimPearling);
			this->tabPageRecipe->Controls->Add(this->lblSimPearling);
			this->tabPageRecipe->Controls->Add(this->tbLeftCompensationStep);
			this->tabPageRecipe->Controls->Add(this->tbRightCompensationStep);
			this->tabPageRecipe->Controls->Add(this->lblCompensationStep);
			this->tabPageRecipe->Controls->Add(this->cbRestartBeginOfArea);
			this->tabPageRecipe->Controls->Add(this->lblRestartBeginOfArea);
			this->tabPageRecipe->Location = System::Drawing::Point(4, 49);
			this->tabPageRecipe->Name = L"tabPageRecipe";
			this->tabPageRecipe->Padding = System::Windows::Forms::Padding(3);
			this->tabPageRecipe->Size = System::Drawing::Size(1570, 842);
			this->tabPageRecipe->TabIndex = 1;
			this->tabPageRecipe->Text = L"Recipe";
			this->tabPageRecipe->UseVisualStyleBackColor = true;
			// 
			// lblRightSpindle
			// 
			this->lblRightSpindle->Location = System::Drawing::Point(686, 59);
			this->lblRightSpindle->Name = L"lblRightSpindle";
			this->lblRightSpindle->Size = System::Drawing::Size(162, 35);
			this->lblRightSpindle->TabIndex = 189;
			this->lblRightSpindle->Tag = L"1";
			this->lblRightSpindle->Text = L"RightSpindle";
			this->lblRightSpindle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLeftSpindle
			// 
			this->lblLeftSpindle->Location = System::Drawing::Point(515, 59);
			this->lblLeftSpindle->Name = L"lblLeftSpindle";
			this->lblLeftSpindle->Size = System::Drawing::Size(162, 35);
			this->lblLeftSpindle->TabIndex = 188;
			this->lblLeftSpindle->Tag = L"1";
			this->lblLeftSpindle->Text = L"LeftSpindle";
			this->lblLeftSpindle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// cbStopOnWeightOutOfTolerance
			// 
			this->cbStopOnWeightOutOfTolerance->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStopOnWeightOutOfTolerance->Checked = true;
			this->cbStopOnWeightOutOfTolerance->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbStopOnWeightOutOfTolerance->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->cbStopOnWeightOutOfTolerance->Location = System::Drawing::Point(67, 458);
			this->cbStopOnWeightOutOfTolerance->Margin = System::Windows::Forms::Padding(5);
			this->cbStopOnWeightOutOfTolerance->Name = L"cbStopOnWeightOutOfTolerance";
			this->cbStopOnWeightOutOfTolerance->Size = System::Drawing::Size(40, 40);
			this->cbStopOnWeightOutOfTolerance->TabIndex = 153;
			this->cbStopOnWeightOutOfTolerance->Tag = L"1";
			this->cbStopOnWeightOutOfTolerance->UseVisualStyleBackColor = true;
			this->cbStopOnWeightOutOfTolerance->CheckedChanged += gcnew System::EventHandler(this, &PearlingManualScreen::cbStopOnWeightOutOfTolerance_CheckedChanged);
			// 
			// lblStopOnWeightOutOfTolerance
			// 
			this->lblStopOnWeightOutOfTolerance->AutoSize = true;
			this->lblStopOnWeightOutOfTolerance->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblStopOnWeightOutOfTolerance->Location = System::Drawing::Point(117, 463);
			this->lblStopOnWeightOutOfTolerance->Name = L"lblStopOnWeightOutOfTolerance";
			this->lblStopOnWeightOutOfTolerance->Size = System::Drawing::Size(369, 29);
			this->lblStopOnWeightOutOfTolerance->TabIndex = 152;
			this->lblStopOnWeightOutOfTolerance->Tag = L"1";
			this->lblStopOnWeightOutOfTolerance->Text = L"StopOnWeightOutOfTolerance";
			// 
			// cbStopOnStickBreak
			// 
			this->cbStopOnStickBreak->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStopOnStickBreak->Checked = true;
			this->cbStopOnStickBreak->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbStopOnStickBreak->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbStopOnStickBreak->Location = System::Drawing::Point(67, 409);
			this->cbStopOnStickBreak->Margin = System::Windows::Forms::Padding(5);
			this->cbStopOnStickBreak->Name = L"cbStopOnStickBreak";
			this->cbStopOnStickBreak->Size = System::Drawing::Size(40, 40);
			this->cbStopOnStickBreak->TabIndex = 151;
			this->cbStopOnStickBreak->Tag = L"1";
			this->cbStopOnStickBreak->UseVisualStyleBackColor = true;
			this->cbStopOnStickBreak->CheckedChanged += gcnew System::EventHandler(this, &PearlingManualScreen::cbStopOnStickBreak_CheckedChanged);
			// 
			// lblStopOnStickBreak
			// 
			this->lblStopOnStickBreak->AutoSize = true;
			this->lblStopOnStickBreak->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStopOnStickBreak->Location = System::Drawing::Point(117, 414);
			this->lblStopOnStickBreak->Name = L"lblStopOnStickBreak";
			this->lblStopOnStickBreak->Size = System::Drawing::Size(226, 29);
			this->lblStopOnStickBreak->TabIndex = 150;
			this->lblStopOnStickBreak->Tag = L"1";
			this->lblStopOnStickBreak->Text = L"StopOnStickBreak";
			// 
			// cbStopOnVacuumLoss
			// 
			this->cbStopOnVacuumLoss->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStopOnVacuumLoss->Checked = true;
			this->cbStopOnVacuumLoss->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbStopOnVacuumLoss->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbStopOnVacuumLoss->Location = System::Drawing::Point(67, 505);
			this->cbStopOnVacuumLoss->Margin = System::Windows::Forms::Padding(5);
			this->cbStopOnVacuumLoss->Name = L"cbStopOnVacuumLoss";
			this->cbStopOnVacuumLoss->Size = System::Drawing::Size(40, 40);
			this->cbStopOnVacuumLoss->TabIndex = 149;
			this->cbStopOnVacuumLoss->Tag = L"10";
			this->cbStopOnVacuumLoss->UseVisualStyleBackColor = true;
			this->cbStopOnVacuumLoss->CheckedChanged += gcnew System::EventHandler(this, &PearlingManualScreen::cbStopOnVacuumLoss_CheckedChanged);
			// 
			// lblStopOnVacuumLoss
			// 
			this->lblStopOnVacuumLoss->AutoSize = true;
			this->lblStopOnVacuumLoss->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblStopOnVacuumLoss->Location = System::Drawing::Point(117, 510);
			this->lblStopOnVacuumLoss->Name = L"lblStopOnVacuumLoss";
			this->lblStopOnVacuumLoss->Size = System::Drawing::Size(248, 29);
			this->lblStopOnVacuumLoss->TabIndex = 148;
			this->lblStopOnVacuumLoss->Tag = L"10";
			this->lblStopOnVacuumLoss->Text = L"StopOnVacuumLoss";
			// 
			// lblWeightToleranceValue
			// 
			this->lblWeightToleranceValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblWeightToleranceValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblWeightToleranceValue->Location = System::Drawing::Point(600, 191);
			this->lblWeightToleranceValue->Name = L"lblWeightToleranceValue";
			this->lblWeightToleranceValue->Size = System::Drawing::Size(162, 39);
			this->lblWeightToleranceValue->TabIndex = 140;
			this->lblWeightToleranceValue->Tag = L"1";
			this->lblWeightToleranceValue->Text = L"0";
			this->lblWeightToleranceValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblWeightToleranceValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblWeightToleranceValue_Click);
			// 
			// lblWeightTolerance
			// 
			this->lblWeightTolerance->AutoSize = true;
			this->lblWeightTolerance->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblWeightTolerance->Location = System::Drawing::Point(59, 201);
			this->lblWeightTolerance->Name = L"lblWeightTolerance";
			this->lblWeightTolerance->Size = System::Drawing::Size(213, 29);
			this->lblWeightTolerance->TabIndex = 139;
			this->lblWeightTolerance->Tag = L"1";
			this->lblWeightTolerance->Text = L"WeightTolerance";
			this->lblWeightTolerance->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblWeightTolerance_Click);
			// 
			// cbSimPearling
			// 
			this->cbSimPearling->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbSimPearling->Checked = true;
			this->cbSimPearling->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbSimPearling->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbSimPearling->Location = System::Drawing::Point(67, 358);
			this->cbSimPearling->Margin = System::Windows::Forms::Padding(5);
			this->cbSimPearling->Name = L"cbSimPearling";
			this->cbSimPearling->Size = System::Drawing::Size(40, 40);
			this->cbSimPearling->TabIndex = 138;
			this->cbSimPearling->Tag = L"1";
			this->cbSimPearling->UseVisualStyleBackColor = true;
			this->cbSimPearling->CheckedChanged += gcnew System::EventHandler(this, &PearlingManualScreen::cbSimPearling_CheckedChanged);
			// 
			// lblSimPearling
			// 
			this->lblSimPearling->AutoSize = true;
			this->lblSimPearling->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSimPearling->Location = System::Drawing::Point(115, 363);
			this->lblSimPearling->Name = L"lblSimPearling";
			this->lblSimPearling->Size = System::Drawing::Size(233, 29);
			this->lblSimPearling->TabIndex = 137;
			this->lblSimPearling->Tag = L"1";
			this->lblSimPearling->Text = L"Simulation perlage";
			// 
			// tbLeftCompensationStep
			// 
			this->tbLeftCompensationStep->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tbLeftCompensationStep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tbLeftCompensationStep->Location = System::Drawing::Point(515, 95);
			this->tbLeftCompensationStep->Name = L"tbLeftCompensationStep";
			this->tbLeftCompensationStep->Size = System::Drawing::Size(162, 39);
			this->tbLeftCompensationStep->TabIndex = 116;
			this->tbLeftCompensationStep->Tag = L"1";
			this->tbLeftCompensationStep->Text = L"0.000";
			this->tbLeftCompensationStep->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->tbLeftCompensationStep->Click += gcnew System::EventHandler(this, &PearlingManualScreen::tbLeftCompensationStep_Click);
			// 
			// tbRightCompensationStep
			// 
			this->tbRightCompensationStep->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tbRightCompensationStep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tbRightCompensationStep->Location = System::Drawing::Point(686, 95);
			this->tbRightCompensationStep->Name = L"tbRightCompensationStep";
			this->tbRightCompensationStep->Size = System::Drawing::Size(162, 39);
			this->tbRightCompensationStep->TabIndex = 117;
			this->tbRightCompensationStep->Tag = L"1";
			this->tbRightCompensationStep->Text = L"0.000";
			this->tbRightCompensationStep->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->tbRightCompensationStep->Click += gcnew System::EventHandler(this, &PearlingManualScreen::tbRightCompensationStep_Click);
			// 
			// lblCompensationStep
			// 
			this->lblCompensationStep->AutoSize = true;
			this->lblCompensationStep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCompensationStep->Location = System::Drawing::Point(59, 104);
			this->lblCompensationStep->Name = L"lblCompensationStep";
			this->lblCompensationStep->Size = System::Drawing::Size(181, 29);
			this->lblCompensationStep->TabIndex = 118;
			this->lblCompensationStep->Tag = L"1";
			this->lblCompensationStep->Text = L"Compensation";
			// 
			// cbRestartBeginOfArea
			// 
			this->cbRestartBeginOfArea->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRestartBeginOfArea->Checked = true;
			this->cbRestartBeginOfArea->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbRestartBeginOfArea->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->cbRestartBeginOfArea->Location = System::Drawing::Point(67, 313);
			this->cbRestartBeginOfArea->Margin = System::Windows::Forms::Padding(5);
			this->cbRestartBeginOfArea->Name = L"cbRestartBeginOfArea";
			this->cbRestartBeginOfArea->Size = System::Drawing::Size(40, 40);
			this->cbRestartBeginOfArea->TabIndex = 96;
			this->cbRestartBeginOfArea->Tag = L"1";
			this->cbRestartBeginOfArea->UseVisualStyleBackColor = true;
			this->cbRestartBeginOfArea->CheckedChanged += gcnew System::EventHandler(this, &PearlingManualScreen::cbRestartBeginOfArea_CheckedChanged);
			// 
			// lblRestartBeginOfArea
			// 
			this->lblRestartBeginOfArea->AutoSize = true;
			this->lblRestartBeginOfArea->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRestartBeginOfArea->Location = System::Drawing::Point(115, 318);
			this->lblRestartBeginOfArea->Name = L"lblRestartBeginOfArea";
			this->lblRestartBeginOfArea->Size = System::Drawing::Size(241, 29);
			this->lblRestartBeginOfArea->TabIndex = 95;
			this->lblRestartBeginOfArea->Tag = L"1";
			this->lblRestartBeginOfArea->Text = L"Reprise debut zone";
			// 
			// tabPageSharpen
			// 
			this->tabPageSharpen->Controls->Add(this->lblMinHoldLength);
			this->tabPageSharpen->Controls->Add(this->lblSpindleSharpenSpeed);
			this->tabPageSharpen->Controls->Add(this->lblMinHoldLengthValue);
			this->tabPageSharpen->Controls->Add(this->lblSharpenHeightValue);
			this->tabPageSharpen->Controls->Add(this->lblSharpenSpeedValue);
			this->tabPageSharpen->Controls->Add(this->lblNbOfFwBwSharpenValue);
			this->tabPageSharpen->Controls->Add(this->lblNbOfFwBwBeforeTapeMoveValue);
			this->tabPageSharpen->Controls->Add(this->lblSpindleSharpenSpeedValue);
			this->tabPageSharpen->Controls->Add(this->lblSharpenSpeed);
			this->tabPageSharpen->Controls->Add(this->lblNbOfFwBwBeforeTapeMove);
			this->tabPageSharpen->Controls->Add(this->lblNbOfFwBwSharpen);
			this->tabPageSharpen->Controls->Add(this->lblSharpenHeight);
			this->tabPageSharpen->Location = System::Drawing::Point(4, 49);
			this->tabPageSharpen->Name = L"tabPageSharpen";
			this->tabPageSharpen->Size = System::Drawing::Size(1570, 842);
			this->tabPageSharpen->TabIndex = 4;
			this->tabPageSharpen->Text = L"Sharpen";
			this->tabPageSharpen->UseVisualStyleBackColor = true;
			// 
			// lblMinHoldLength
			// 
			this->lblMinHoldLength->AutoSize = true;
			this->lblMinHoldLength->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMinHoldLength->Location = System::Drawing::Point(55, 206);
			this->lblMinHoldLength->Name = L"lblMinHoldLength";
			this->lblMinHoldLength->Size = System::Drawing::Size(186, 29);
			this->lblMinHoldLength->TabIndex = 166;
			this->lblMinHoldLength->Tag = L"1";
			this->lblMinHoldLength->Text = L"MinHoldHeight";
			// 
			// lblSpindleSharpenSpeed
			// 
			this->lblSpindleSharpenSpeed->AutoSize = true;
			this->lblSpindleSharpenSpeed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblSpindleSharpenSpeed->Location = System::Drawing::Point(54, 303);
			this->lblSpindleSharpenSpeed->Name = L"lblSpindleSharpenSpeed";
			this->lblSpindleSharpenSpeed->Size = System::Drawing::Size(187, 29);
			this->lblSpindleSharpenSpeed->TabIndex = 165;
			this->lblSpindleSharpenSpeed->Tag = L"1";
			this->lblSpindleSharpenSpeed->Text = L"Spindle Speed";
			// 
			// lblMinHoldLengthValue
			// 
			this->lblMinHoldLengthValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblMinHoldLengthValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblMinHoldLengthValue->Location = System::Drawing::Point(692, 201);
			this->lblMinHoldLengthValue->Name = L"lblMinHoldLengthValue";
			this->lblMinHoldLengthValue->Size = System::Drawing::Size(162, 39);
			this->lblMinHoldLengthValue->TabIndex = 125;
			this->lblMinHoldLengthValue->Tag = L"1";
			this->lblMinHoldLengthValue->Text = L"0";
			this->lblMinHoldLengthValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblMinHoldLengthValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblMinHoldLengthValue_Click);
			// 
			// lblSharpenHeightValue
			// 
			this->lblSharpenHeightValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblSharpenHeightValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblSharpenHeightValue->Location = System::Drawing::Point(692, 152);
			this->lblSharpenHeightValue->Name = L"lblSharpenHeightValue";
			this->lblSharpenHeightValue->Size = System::Drawing::Size(162, 39);
			this->lblSharpenHeightValue->TabIndex = 125;
			this->lblSharpenHeightValue->Tag = L"1";
			this->lblSharpenHeightValue->Text = L"0";
			this->lblSharpenHeightValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblSharpenHeightValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblSharpenHeightValue_Click);
			// 
			// lblSharpenSpeedValue
			// 
			this->lblSharpenSpeedValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblSharpenSpeedValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblSharpenSpeedValue->Location = System::Drawing::Point(692, 249);
			this->lblSharpenSpeedValue->Name = L"lblSharpenSpeedValue";
			this->lblSharpenSpeedValue->Size = System::Drawing::Size(162, 39);
			this->lblSharpenSpeedValue->TabIndex = 125;
			this->lblSharpenSpeedValue->Tag = L"1";
			this->lblSharpenSpeedValue->Text = L"0";
			this->lblSharpenSpeedValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblSharpenSpeedValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblSharpenSpeedValue_Click);
			// 
			// lblNbOfFwBwSharpenValue
			// 
			this->lblNbOfFwBwSharpenValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblNbOfFwBwSharpenValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblNbOfFwBwSharpenValue->Location = System::Drawing::Point(692, 56);
			this->lblNbOfFwBwSharpenValue->Name = L"lblNbOfFwBwSharpenValue";
			this->lblNbOfFwBwSharpenValue->Size = System::Drawing::Size(162, 39);
			this->lblNbOfFwBwSharpenValue->TabIndex = 125;
			this->lblNbOfFwBwSharpenValue->Tag = L"1";
			this->lblNbOfFwBwSharpenValue->Text = L"0";
			this->lblNbOfFwBwSharpenValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblNbOfFwBwSharpenValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblNbOfFwBwSharpenValue_Click);
			// 
			// lblNbOfFwBwBeforeTapeMoveValue
			// 
			this->lblNbOfFwBwBeforeTapeMoveValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblNbOfFwBwBeforeTapeMoveValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblNbOfFwBwBeforeTapeMoveValue->Location = System::Drawing::Point(692, 104);
			this->lblNbOfFwBwBeforeTapeMoveValue->Name = L"lblNbOfFwBwBeforeTapeMoveValue";
			this->lblNbOfFwBwBeforeTapeMoveValue->Size = System::Drawing::Size(162, 39);
			this->lblNbOfFwBwBeforeTapeMoveValue->TabIndex = 125;
			this->lblNbOfFwBwBeforeTapeMoveValue->Tag = L"1";
			this->lblNbOfFwBwBeforeTapeMoveValue->Text = L"0";
			this->lblNbOfFwBwBeforeTapeMoveValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblNbOfFwBwBeforeTapeMoveValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblNbOfFwBwBeforeTapeMoveValue_Click);
			// 
			// lblSpindleSharpenSpeedValue
			// 
			this->lblSpindleSharpenSpeedValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblSpindleSharpenSpeedValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblSpindleSharpenSpeedValue->Location = System::Drawing::Point(692, 298);
			this->lblSpindleSharpenSpeedValue->Name = L"lblSpindleSharpenSpeedValue";
			this->lblSpindleSharpenSpeedValue->Size = System::Drawing::Size(162, 39);
			this->lblSpindleSharpenSpeedValue->TabIndex = 125;
			this->lblSpindleSharpenSpeedValue->Tag = L"1";
			this->lblSpindleSharpenSpeedValue->Text = L"0";
			this->lblSpindleSharpenSpeedValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblSpindleSharpenSpeedValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblSpindleSharpenSpeedValue_Click);
			// 
			// lblSharpenSpeed
			// 
			this->lblSharpenSpeed->AutoSize = true;
			this->lblSharpenSpeed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSharpenSpeed->Location = System::Drawing::Point(54, 254);
			this->lblSharpenSpeed->Name = L"lblSharpenSpeed";
			this->lblSharpenSpeed->Size = System::Drawing::Size(199, 29);
			this->lblSharpenSpeed->TabIndex = 124;
			this->lblSharpenSpeed->Tag = L"1";
			this->lblSharpenSpeed->Text = L"Vitesse affutage";
			// 
			// lblNbOfFwBwBeforeTapeMove
			// 
			this->lblNbOfFwBwBeforeTapeMove->AutoSize = true;
			this->lblNbOfFwBwBeforeTapeMove->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblNbOfFwBwBeforeTapeMove->Location = System::Drawing::Point(54, 109);
			this->lblNbOfFwBwBeforeTapeMove->Name = L"lblNbOfFwBwBeforeTapeMove";
			this->lblNbOfFwBwBeforeTapeMove->Size = System::Drawing::Size(358, 29);
			this->lblNbOfFwBwBeforeTapeMove->TabIndex = 122;
			this->lblNbOfFwBwBeforeTapeMove->Tag = L"1";
			this->lblNbOfFwBwBeforeTapeMove->Text = L"Nb BF av déplacement bande";
			// 
			// lblNbOfFwBwSharpen
			// 
			this->lblNbOfFwBwSharpen->AutoSize = true;
			this->lblNbOfFwBwSharpen->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblNbOfFwBwSharpen->Location = System::Drawing::Point(54, 61);
			this->lblNbOfFwBwSharpen->Name = L"lblNbOfFwBwSharpen";
			this->lblNbOfFwBwSharpen->Size = System::Drawing::Size(189, 29);
			this->lblNbOfFwBwSharpen->TabIndex = 120;
			this->lblNbOfFwBwSharpen->Tag = L"1";
			this->lblNbOfFwBwSharpen->Text = L"Nb BF Affutage";
			// 
			// lblSharpenHeight
			// 
			this->lblSharpenHeight->AutoSize = true;
			this->lblSharpenHeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSharpenHeight->Location = System::Drawing::Point(54, 157);
			this->lblSharpenHeight->Name = L"lblSharpenHeight";
			this->lblSharpenHeight->Size = System::Drawing::Size(204, 29);
			this->lblSharpenHeight->TabIndex = 118;
			this->lblSharpenHeight->Tag = L"1";
			this->lblSharpenHeight->Text = L"Hauteur affutage";
			// 
			// tabPagePearling
			// 
			this->tabPagePearling->Controls->Add(this->lblRightSpindlePearling);
			this->tabPagePearling->Controls->Add(this->lblLeftSpindlePearling);
			this->tabPagePearling->Controls->Add(this->tbRightSpindlePearlsCounter);
			this->tabPagePearling->Controls->Add(this->tbLeftSpindlePearlsCounter);
			this->tabPagePearling->Controls->Add(this->lblSpindlePearlsCounter);
			this->tabPagePearling->Controls->Add(this->lblCurrentMotorMaxTh);
			this->tabPagePearling->Controls->Add(this->lblCurrentMotorMaxThreshold);
			this->tabPagePearling->Controls->Add(this->tbWeightSensor);
			this->tabPagePearling->Controls->Add(this->lblWeightSensor);
			this->tabPagePearling->Controls->Add(this->tbRightHeightSensor);
			this->tabPagePearling->Controls->Add(this->tbLeftHeightSensor);
			this->tabPagePearling->Controls->Add(this->lblHeightSensor);
			this->tabPagePearling->Controls->Add(this->lblMotorStopTimeout);
			this->tabPagePearling->Controls->Add(this->lblMotorStartTimeout);
			this->tabPagePearling->Controls->Add(this->lblRightMotorStopTimeout);
			this->tabPagePearling->Controls->Add(this->lblLeftMotorStopTimeout);
			this->tabPagePearling->Controls->Add(this->lblRightSpindleRatio);
			this->tabPagePearling->Controls->Add(this->lblRightCompenseWeight);
			this->tabPagePearling->Controls->Add(this->lblRightSpindleManualSpeedValue);
			this->tabPagePearling->Controls->Add(this->lblLeftSpindleRatio);
			this->tabPagePearling->Controls->Add(this->lblLeftCompenseWeight);
			this->tabPagePearling->Controls->Add(this->lblLeftSpindleManualSpeedValue);
			this->tabPagePearling->Controls->Add(this->lblRightMotorStartTimeout);
			this->tabPagePearling->Controls->Add(this->lblLeftMotorStartTimeout);
			this->tabPagePearling->Controls->Add(this->lblCurrentMotorWarnTh);
			this->tabPagePearling->Controls->Add(this->lblCurrentMotorMinTh);
			this->tabPagePearling->Controls->Add(this->lblCurrentMotorWarnThreshold);
			this->tabPagePearling->Controls->Add(this->lblCurrentMotorMinThreshold);
			this->tabPagePearling->Controls->Add(this->lblSpindleManualSpeed);
			this->tabPagePearling->Controls->Add(this->lblSpindleRatio);
			this->tabPagePearling->Controls->Add(this->btnRAZRightSpindleUseTime);
			this->tabPagePearling->Controls->Add(this->tbRightSpindleUseTime);
			this->tabPagePearling->Controls->Add(this->btnRAZLeftSpindleUseTime);
			this->tabPagePearling->Controls->Add(this->tbLeftSpindleUseTime);
			this->tabPagePearling->Controls->Add(this->lblSpindleUseTime);
			this->tabPagePearling->Controls->Add(this->btnRAZRightMotorUseTime);
			this->tabPagePearling->Controls->Add(this->tbRightMotorUseTime);
			this->tabPagePearling->Controls->Add(this->btnRAZLeftMotorUseTime);
			this->tabPagePearling->Controls->Add(this->tbLeftMotorUseTime);
			this->tabPagePearling->Controls->Add(this->lblMotorUseTime);
			this->tabPagePearling->Controls->Add(this->lblCompenseWeight);
			this->tabPagePearling->Controls->Add(this->tbRightMotorCurrent);
			this->tabPagePearling->Controls->Add(this->tbRightMotorSpeed);
			this->tabPagePearling->Controls->Add(this->tbLeftMotorCurrent);
			this->tabPagePearling->Controls->Add(this->lblMotorCurrent);
			this->tabPagePearling->Controls->Add(this->tbLeftMotorSpeed);
			this->tabPagePearling->Controls->Add(this->lblMotorSpeed);
			this->tabPagePearling->Location = System::Drawing::Point(4, 49);
			this->tabPagePearling->Name = L"tabPagePearling";
			this->tabPagePearling->Size = System::Drawing::Size(1570, 842);
			this->tabPagePearling->TabIndex = 5;
			this->tabPagePearling->Text = L"Pearling";
			this->tabPagePearling->UseVisualStyleBackColor = true;
			// 
			// lblRightSpindlePearling
			// 
			this->lblRightSpindlePearling->Location = System::Drawing::Point(587, 15);
			this->lblRightSpindlePearling->Name = L"lblRightSpindlePearling";
			this->lblRightSpindlePearling->Size = System::Drawing::Size(162, 35);
			this->lblRightSpindlePearling->TabIndex = 192;
			this->lblRightSpindlePearling->Tag = L"1";
			this->lblRightSpindlePearling->Text = L"RightSpindle";
			this->lblRightSpindlePearling->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblLeftSpindlePearling
			// 
			this->lblLeftSpindlePearling->Location = System::Drawing::Point(416, 15);
			this->lblLeftSpindlePearling->Name = L"lblLeftSpindlePearling";
			this->lblLeftSpindlePearling->Size = System::Drawing::Size(162, 35);
			this->lblLeftSpindlePearling->TabIndex = 191;
			this->lblLeftSpindlePearling->Tag = L"1";
			this->lblLeftSpindlePearling->Text = L"LeftSpindle";
			this->lblLeftSpindlePearling->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tbRightSpindlePearlsCounter
			// 
			this->tbRightSpindlePearlsCounter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tbRightSpindlePearlsCounter->Location = System::Drawing::Point(586, 535);
			this->tbRightSpindlePearlsCounter->Name = L"tbRightSpindlePearlsCounter";
			this->tbRightSpindlePearlsCounter->ReadOnly = true;
			this->tbRightSpindlePearlsCounter->Size = System::Drawing::Size(162, 35);
			this->tbRightSpindlePearlsCounter->TabIndex = 190;
			this->tbRightSpindlePearlsCounter->Tag = L"1";
			this->tbRightSpindlePearlsCounter->Text = L"0";
			this->tbRightSpindlePearlsCounter->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tbLeftSpindlePearlsCounter
			// 
			this->tbLeftSpindlePearlsCounter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tbLeftSpindlePearlsCounter->Location = System::Drawing::Point(416, 535);
			this->tbLeftSpindlePearlsCounter->Name = L"tbLeftSpindlePearlsCounter";
			this->tbLeftSpindlePearlsCounter->ReadOnly = true;
			this->tbLeftSpindlePearlsCounter->Size = System::Drawing::Size(162, 35);
			this->tbLeftSpindlePearlsCounter->TabIndex = 188;
			this->tbLeftSpindlePearlsCounter->Tag = L"1";
			this->tbLeftSpindlePearlsCounter->Text = L"0";
			this->tbLeftSpindlePearlsCounter->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblSpindlePearlsCounter
			// 
			this->lblSpindlePearlsCounter->AutoSize = true;
			this->lblSpindlePearlsCounter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblSpindlePearlsCounter->Location = System::Drawing::Point(12, 539);
			this->lblSpindlePearlsCounter->Name = L"lblSpindlePearlsCounter";
			this->lblSpindlePearlsCounter->Size = System::Drawing::Size(270, 29);
			this->lblSpindlePearlsCounter->TabIndex = 189;
			this->lblSpindlePearlsCounter->Tag = L"1";
			this->lblSpindlePearlsCounter->Text = L"SpindlePearlsCounter";
			// 
			// lblCurrentMotorMaxTh
			// 
			this->lblCurrentMotorMaxTh->AutoSize = true;
			this->lblCurrentMotorMaxTh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCurrentMotorMaxTh->Location = System::Drawing::Point(798, 156);
			this->lblCurrentMotorMaxTh->Name = L"lblCurrentMotorMaxTh";
			this->lblCurrentMotorMaxTh->Size = System::Drawing::Size(244, 29);
			this->lblCurrentMotorMaxTh->TabIndex = 187;
			this->lblCurrentMotorMaxTh->Tag = L"2";
			this->lblCurrentMotorMaxTh->Text = L"CurrentMotorMaxTh";
			// 
			// lblCurrentMotorMaxThreshold
			// 
			this->lblCurrentMotorMaxThreshold->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblCurrentMotorMaxThreshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCurrentMotorMaxThreshold->Location = System::Drawing::Point(1291, 150);
			this->lblCurrentMotorMaxThreshold->Margin = System::Windows::Forms::Padding(3);
			this->lblCurrentMotorMaxThreshold->Name = L"lblCurrentMotorMaxThreshold";
			this->lblCurrentMotorMaxThreshold->Size = System::Drawing::Size(162, 39);
			this->lblCurrentMotorMaxThreshold->TabIndex = 186;
			this->lblCurrentMotorMaxThreshold->Tag = L"2";
			this->lblCurrentMotorMaxThreshold->Text = L"0";
			this->lblCurrentMotorMaxThreshold->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblCurrentMotorMaxThreshold->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblCurrentMotorMaxThreshold_Click);
			// 
			// tbWeightSensor
			// 
			this->tbWeightSensor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbWeightSensor->Location = System::Drawing::Point(1289, 459);
			this->tbWeightSensor->Name = L"tbWeightSensor";
			this->tbWeightSensor->ReadOnly = true;
			this->tbWeightSensor->Size = System::Drawing::Size(162, 35);
			this->tbWeightSensor->TabIndex = 184;
			this->tbWeightSensor->Tag = L"1";
			this->tbWeightSensor->Text = L"0";
			this->tbWeightSensor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblWeightSensor
			// 
			this->lblWeightSensor->AutoSize = true;
			this->lblWeightSensor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblWeightSensor->Location = System::Drawing::Point(798, 464);
			this->lblWeightSensor->Name = L"lblWeightSensor";
			this->lblWeightSensor->Size = System::Drawing::Size(180, 29);
			this->lblWeightSensor->TabIndex = 185;
			this->lblWeightSensor->Tag = L"1";
			this->lblWeightSensor->Text = L"Weight sensor";
			// 
			// tbRightHeightSensor
			// 
			this->tbRightHeightSensor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRightHeightSensor->Location = System::Drawing::Point(587, 461);
			this->tbRightHeightSensor->Name = L"tbRightHeightSensor";
			this->tbRightHeightSensor->ReadOnly = true;
			this->tbRightHeightSensor->Size = System::Drawing::Size(162, 35);
			this->tbRightHeightSensor->TabIndex = 183;
			this->tbRightHeightSensor->Tag = L"1";
			this->tbRightHeightSensor->Text = L"0";
			this->tbRightHeightSensor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tbLeftHeightSensor
			// 
			this->tbLeftHeightSensor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbLeftHeightSensor->Location = System::Drawing::Point(416, 461);
			this->tbLeftHeightSensor->Name = L"tbLeftHeightSensor";
			this->tbLeftHeightSensor->ReadOnly = true;
			this->tbLeftHeightSensor->Size = System::Drawing::Size(162, 35);
			this->tbLeftHeightSensor->TabIndex = 181;
			this->tbLeftHeightSensor->Tag = L"1";
			this->tbLeftHeightSensor->Text = L"0";
			this->tbLeftHeightSensor->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblHeightSensor
			// 
			this->lblHeightSensor->AutoSize = true;
			this->lblHeightSensor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblHeightSensor->Location = System::Drawing::Point(12, 465);
			this->lblHeightSensor->Name = L"lblHeightSensor";
			this->lblHeightSensor->Size = System::Drawing::Size(175, 29);
			this->lblHeightSensor->TabIndex = 182;
			this->lblHeightSensor->Tag = L"1";
			this->lblHeightSensor->Text = L"Height sensor";
			// 
			// lblMotorStopTimeout
			// 
			this->lblMotorStopTimeout->AutoSize = true;
			this->lblMotorStopTimeout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMotorStopTimeout->Location = System::Drawing::Point(12, 204);
			this->lblMotorStopTimeout->Name = L"lblMotorStopTimeout";
			this->lblMotorStopTimeout->Size = System::Drawing::Size(230, 29);
			this->lblMotorStopTimeout->TabIndex = 180;
			this->lblMotorStopTimeout->Tag = L"2";
			this->lblMotorStopTimeout->Text = L"MotorStopTimeout";
			// 
			// lblMotorStartTimeout
			// 
			this->lblMotorStartTimeout->AutoSize = true;
			this->lblMotorStartTimeout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMotorStartTimeout->Location = System::Drawing::Point(12, 156);
			this->lblMotorStartTimeout->Name = L"lblMotorStartTimeout";
			this->lblMotorStartTimeout->Size = System::Drawing::Size(230, 29);
			this->lblMotorStartTimeout->TabIndex = 179;
			this->lblMotorStartTimeout->Tag = L"2";
			this->lblMotorStartTimeout->Text = L"MotorStartTimeout";
			// 
			// lblRightMotorStopTimeout
			// 
			this->lblRightMotorStopTimeout->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblRightMotorStopTimeout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblRightMotorStopTimeout->Location = System::Drawing::Point(587, 200);
			this->lblRightMotorStopTimeout->Margin = System::Windows::Forms::Padding(3);
			this->lblRightMotorStopTimeout->Name = L"lblRightMotorStopTimeout";
			this->lblRightMotorStopTimeout->Size = System::Drawing::Size(162, 39);
			this->lblRightMotorStopTimeout->TabIndex = 178;
			this->lblRightMotorStopTimeout->Tag = L"2";
			this->lblRightMotorStopTimeout->Text = L"0";
			this->lblRightMotorStopTimeout->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblRightMotorStopTimeout->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblRightMotorStopTimeout_Click);
			// 
			// lblLeftMotorStopTimeout
			// 
			this->lblLeftMotorStopTimeout->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLeftMotorStopTimeout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLeftMotorStopTimeout->Location = System::Drawing::Point(416, 200);
			this->lblLeftMotorStopTimeout->Margin = System::Windows::Forms::Padding(3);
			this->lblLeftMotorStopTimeout->Name = L"lblLeftMotorStopTimeout";
			this->lblLeftMotorStopTimeout->Size = System::Drawing::Size(162, 39);
			this->lblLeftMotorStopTimeout->TabIndex = 177;
			this->lblLeftMotorStopTimeout->Tag = L"2";
			this->lblLeftMotorStopTimeout->Text = L"0";
			this->lblLeftMotorStopTimeout->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLeftMotorStopTimeout->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblLeftMotorStopTimeout_Click);
			// 
			// lblRightSpindleRatio
			// 
			this->lblRightSpindleRatio->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblRightSpindleRatio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblRightSpindleRatio->Location = System::Drawing::Point(587, 55);
			this->lblRightSpindleRatio->Margin = System::Windows::Forms::Padding(3);
			this->lblRightSpindleRatio->Name = L"lblRightSpindleRatio";
			this->lblRightSpindleRatio->Size = System::Drawing::Size(162, 39);
			this->lblRightSpindleRatio->TabIndex = 176;
			this->lblRightSpindleRatio->Tag = L"2";
			this->lblRightSpindleRatio->Text = L"0";
			this->lblRightSpindleRatio->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblRightSpindleRatio->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblRightSpindleRatio_Click);
			// 
			// lblRightCompenseWeight
			// 
			this->lblRightCompenseWeight->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblRightCompenseWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblRightCompenseWeight->Location = System::Drawing::Point(587, 252);
			this->lblRightCompenseWeight->Margin = System::Windows::Forms::Padding(3);
			this->lblRightCompenseWeight->Name = L"lblRightCompenseWeight";
			this->lblRightCompenseWeight->Size = System::Drawing::Size(162, 39);
			this->lblRightCompenseWeight->TabIndex = 176;
			this->lblRightCompenseWeight->Tag = L"2";
			this->lblRightCompenseWeight->Text = L"0";
			this->lblRightCompenseWeight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblRightCompenseWeight->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblRightCompenseWeight_Click);
			// 
			// lblRightSpindleManualSpeedValue
			// 
			this->lblRightSpindleManualSpeedValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblRightSpindleManualSpeedValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblRightSpindleManualSpeedValue->Location = System::Drawing::Point(587, 103);
			this->lblRightSpindleManualSpeedValue->Margin = System::Windows::Forms::Padding(3);
			this->lblRightSpindleManualSpeedValue->Name = L"lblRightSpindleManualSpeedValue";
			this->lblRightSpindleManualSpeedValue->Size = System::Drawing::Size(162, 39);
			this->lblRightSpindleManualSpeedValue->TabIndex = 176;
			this->lblRightSpindleManualSpeedValue->Tag = L"2";
			this->lblRightSpindleManualSpeedValue->Text = L"0";
			this->lblRightSpindleManualSpeedValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblRightSpindleManualSpeedValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblRightSpindleManualSpeedValue_Click);
			// 
			// lblLeftSpindleRatio
			// 
			this->lblLeftSpindleRatio->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLeftSpindleRatio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLeftSpindleRatio->Location = System::Drawing::Point(416, 55);
			this->lblLeftSpindleRatio->Margin = System::Windows::Forms::Padding(3);
			this->lblLeftSpindleRatio->Name = L"lblLeftSpindleRatio";
			this->lblLeftSpindleRatio->Size = System::Drawing::Size(162, 39);
			this->lblLeftSpindleRatio->TabIndex = 175;
			this->lblLeftSpindleRatio->Tag = L"2";
			this->lblLeftSpindleRatio->Text = L"0";
			this->lblLeftSpindleRatio->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLeftSpindleRatio->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblLeftSpindleRatio_Click);
			// 
			// lblLeftCompenseWeight
			// 
			this->lblLeftCompenseWeight->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLeftCompenseWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLeftCompenseWeight->Location = System::Drawing::Point(416, 252);
			this->lblLeftCompenseWeight->Margin = System::Windows::Forms::Padding(3);
			this->lblLeftCompenseWeight->Name = L"lblLeftCompenseWeight";
			this->lblLeftCompenseWeight->Size = System::Drawing::Size(162, 39);
			this->lblLeftCompenseWeight->TabIndex = 175;
			this->lblLeftCompenseWeight->Tag = L"2";
			this->lblLeftCompenseWeight->Text = L"0";
			this->lblLeftCompenseWeight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLeftCompenseWeight->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblLeftCompenseWeight_Click);
			// 
			// lblLeftSpindleManualSpeedValue
			// 
			this->lblLeftSpindleManualSpeedValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLeftSpindleManualSpeedValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLeftSpindleManualSpeedValue->Location = System::Drawing::Point(416, 103);
			this->lblLeftSpindleManualSpeedValue->Margin = System::Windows::Forms::Padding(3);
			this->lblLeftSpindleManualSpeedValue->Name = L"lblLeftSpindleManualSpeedValue";
			this->lblLeftSpindleManualSpeedValue->Size = System::Drawing::Size(162, 39);
			this->lblLeftSpindleManualSpeedValue->TabIndex = 175;
			this->lblLeftSpindleManualSpeedValue->Tag = L"2";
			this->lblLeftSpindleManualSpeedValue->Text = L"0";
			this->lblLeftSpindleManualSpeedValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLeftSpindleManualSpeedValue->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblLeftSpindleManualSpeedValue_Click);
			// 
			// lblRightMotorStartTimeout
			// 
			this->lblRightMotorStartTimeout->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblRightMotorStartTimeout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblRightMotorStartTimeout->Location = System::Drawing::Point(587, 151);
			this->lblRightMotorStartTimeout->Margin = System::Windows::Forms::Padding(3);
			this->lblRightMotorStartTimeout->Name = L"lblRightMotorStartTimeout";
			this->lblRightMotorStartTimeout->Size = System::Drawing::Size(162, 39);
			this->lblRightMotorStartTimeout->TabIndex = 176;
			this->lblRightMotorStartTimeout->Tag = L"2";
			this->lblRightMotorStartTimeout->Text = L"0";
			this->lblRightMotorStartTimeout->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblRightMotorStartTimeout->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblRightMotorStartTimeout_Click);
			// 
			// lblLeftMotorStartTimeout
			// 
			this->lblLeftMotorStartTimeout->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblLeftMotorStartTimeout->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblLeftMotorStartTimeout->Location = System::Drawing::Point(416, 151);
			this->lblLeftMotorStartTimeout->Margin = System::Windows::Forms::Padding(3);
			this->lblLeftMotorStartTimeout->Name = L"lblLeftMotorStartTimeout";
			this->lblLeftMotorStartTimeout->Size = System::Drawing::Size(162, 39);
			this->lblLeftMotorStartTimeout->TabIndex = 175;
			this->lblLeftMotorStartTimeout->Tag = L"2";
			this->lblLeftMotorStartTimeout->Text = L"0";
			this->lblLeftMotorStartTimeout->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblLeftMotorStartTimeout->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblLeftMotorStartTimeout_Click);
			// 
			// lblCurrentMotorWarnTh
			// 
			this->lblCurrentMotorWarnTh->AutoSize = true;
			this->lblCurrentMotorWarnTh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCurrentMotorWarnTh->Location = System::Drawing::Point(798, 108);
			this->lblCurrentMotorWarnTh->Name = L"lblCurrentMotorWarnTh";
			this->lblCurrentMotorWarnTh->Size = System::Drawing::Size(257, 29);
			this->lblCurrentMotorWarnTh->TabIndex = 174;
			this->lblCurrentMotorWarnTh->Tag = L"2";
			this->lblCurrentMotorWarnTh->Text = L"CurrentMotorWarnTh";
			// 
			// lblCurrentMotorMinTh
			// 
			this->lblCurrentMotorMinTh->AutoSize = true;
			this->lblCurrentMotorMinTh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCurrentMotorMinTh->Location = System::Drawing::Point(798, 60);
			this->lblCurrentMotorMinTh->Name = L"lblCurrentMotorMinTh";
			this->lblCurrentMotorMinTh->Size = System::Drawing::Size(239, 29);
			this->lblCurrentMotorMinTh->TabIndex = 173;
			this->lblCurrentMotorMinTh->Tag = L"2";
			this->lblCurrentMotorMinTh->Text = L"CurrentMotorMinTh";
			// 
			// lblCurrentMotorWarnThreshold
			// 
			this->lblCurrentMotorWarnThreshold->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblCurrentMotorWarnThreshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCurrentMotorWarnThreshold->Location = System::Drawing::Point(1291, 102);
			this->lblCurrentMotorWarnThreshold->Margin = System::Windows::Forms::Padding(3);
			this->lblCurrentMotorWarnThreshold->Name = L"lblCurrentMotorWarnThreshold";
			this->lblCurrentMotorWarnThreshold->Size = System::Drawing::Size(162, 39);
			this->lblCurrentMotorWarnThreshold->TabIndex = 171;
			this->lblCurrentMotorWarnThreshold->Tag = L"2";
			this->lblCurrentMotorWarnThreshold->Text = L"0";
			this->lblCurrentMotorWarnThreshold->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblCurrentMotorWarnThreshold->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblCurrentMotorWarnThreshold_Click);
			// 
			// lblCurrentMotorMinThreshold
			// 
			this->lblCurrentMotorMinThreshold->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblCurrentMotorMinThreshold->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCurrentMotorMinThreshold->Location = System::Drawing::Point(1291, 54);
			this->lblCurrentMotorMinThreshold->Margin = System::Windows::Forms::Padding(3);
			this->lblCurrentMotorMinThreshold->Name = L"lblCurrentMotorMinThreshold";
			this->lblCurrentMotorMinThreshold->Size = System::Drawing::Size(162, 39);
			this->lblCurrentMotorMinThreshold->TabIndex = 169;
			this->lblCurrentMotorMinThreshold->Tag = L"2";
			this->lblCurrentMotorMinThreshold->Text = L"0";
			this->lblCurrentMotorMinThreshold->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblCurrentMotorMinThreshold->Click += gcnew System::EventHandler(this, &PearlingManualScreen::lblCurrentMotorMinThreshold_Click);
			// 
			// lblSpindleManualSpeed
			// 
			this->lblSpindleManualSpeed->AutoSize = true;
			this->lblSpindleManualSpeed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSpindleManualSpeed->Location = System::Drawing::Point(12, 108);
			this->lblSpindleManualSpeed->Name = L"lblSpindleManualSpeed";
			this->lblSpindleManualSpeed->Size = System::Drawing::Size(278, 29);
			this->lblSpindleManualSpeed->TabIndex = 167;
			this->lblSpindleManualSpeed->Tag = L"2";
			this->lblSpindleManualSpeed->Text = L"Spindle Manual Speed";
			// 
			// lblSpindleRatio
			// 
			this->lblSpindleRatio->AutoSize = true;
			this->lblSpindleRatio->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSpindleRatio->Location = System::Drawing::Point(12, 60);
			this->lblSpindleRatio->Name = L"lblSpindleRatio";
			this->lblSpindleRatio->Size = System::Drawing::Size(171, 29);
			this->lblSpindleRatio->TabIndex = 164;
			this->lblSpindleRatio->Tag = L"2";
			this->lblSpindleRatio->Text = L"Spindle Ratio";
			// 
			// btnRAZRightSpindleUseTime
			// 
			this->btnRAZRightSpindleUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnRAZRightSpindleUseTime->Location = System::Drawing::Point(587, 752);
			this->btnRAZRightSpindleUseTime->Name = L"btnRAZRightSpindleUseTime";
			this->btnRAZRightSpindleUseTime->Size = System::Drawing::Size(162, 39);
			this->btnRAZRightSpindleUseTime->TabIndex = 162;
			this->btnRAZRightSpindleUseTime->Tag = L"1";
			this->btnRAZRightSpindleUseTime->Text = L"RESET";
			this->btnRAZRightSpindleUseTime->UseVisualStyleBackColor = true;
			this->btnRAZRightSpindleUseTime->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRAZRightSpindleUseTime_Click);
			// 
			// tbRightSpindleUseTime
			// 
			this->tbRightSpindleUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRightSpindleUseTime->Location = System::Drawing::Point(587, 711);
			this->tbRightSpindleUseTime->Name = L"tbRightSpindleUseTime";
			this->tbRightSpindleUseTime->ReadOnly = true;
			this->tbRightSpindleUseTime->Size = System::Drawing::Size(162, 35);
			this->tbRightSpindleUseTime->TabIndex = 161;
			this->tbRightSpindleUseTime->Tag = L"1";
			this->tbRightSpindleUseTime->Text = L"0";
			this->tbRightSpindleUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// btnRAZLeftSpindleUseTime
			// 
			this->btnRAZLeftSpindleUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnRAZLeftSpindleUseTime->Location = System::Drawing::Point(416, 752);
			this->btnRAZLeftSpindleUseTime->Name = L"btnRAZLeftSpindleUseTime";
			this->btnRAZLeftSpindleUseTime->Size = System::Drawing::Size(162, 39);
			this->btnRAZLeftSpindleUseTime->TabIndex = 160;
			this->btnRAZLeftSpindleUseTime->Tag = L"1";
			this->btnRAZLeftSpindleUseTime->Text = L"RESET";
			this->btnRAZLeftSpindleUseTime->UseVisualStyleBackColor = true;
			this->btnRAZLeftSpindleUseTime->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRAZLeftSpindleUseTime_Click);
			// 
			// tbLeftSpindleUseTime
			// 
			this->tbLeftSpindleUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbLeftSpindleUseTime->Location = System::Drawing::Point(416, 711);
			this->tbLeftSpindleUseTime->Name = L"tbLeftSpindleUseTime";
			this->tbLeftSpindleUseTime->ReadOnly = true;
			this->tbLeftSpindleUseTime->Size = System::Drawing::Size(162, 35);
			this->tbLeftSpindleUseTime->TabIndex = 158;
			this->tbLeftSpindleUseTime->Tag = L"1";
			this->tbLeftSpindleUseTime->Text = L"0";
			this->tbLeftSpindleUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblSpindleUseTime
			// 
			this->lblSpindleUseTime->AutoSize = true;
			this->lblSpindleUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSpindleUseTime->Location = System::Drawing::Point(12, 715);
			this->lblSpindleUseTime->Name = L"lblSpindleUseTime";
			this->lblSpindleUseTime->Size = System::Drawing::Size(209, 29);
			this->lblSpindleUseTime->TabIndex = 159;
			this->lblSpindleUseTime->Tag = L"1";
			this->lblSpindleUseTime->Text = L"SpindleUseTime";
			// 
			// btnRAZRightMotorUseTime
			// 
			this->btnRAZRightMotorUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnRAZRightMotorUseTime->Location = System::Drawing::Point(587, 653);
			this->btnRAZRightMotorUseTime->Name = L"btnRAZRightMotorUseTime";
			this->btnRAZRightMotorUseTime->Size = System::Drawing::Size(162, 39);
			this->btnRAZRightMotorUseTime->TabIndex = 157;
			this->btnRAZRightMotorUseTime->Tag = L"1";
			this->btnRAZRightMotorUseTime->Text = L"RESET";
			this->btnRAZRightMotorUseTime->UseVisualStyleBackColor = true;
			this->btnRAZRightMotorUseTime->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRAZRightMotorUseTime_Click);
			// 
			// tbRightMotorUseTime
			// 
			this->tbRightMotorUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRightMotorUseTime->Location = System::Drawing::Point(587, 612);
			this->tbRightMotorUseTime->Name = L"tbRightMotorUseTime";
			this->tbRightMotorUseTime->ReadOnly = true;
			this->tbRightMotorUseTime->Size = System::Drawing::Size(162, 35);
			this->tbRightMotorUseTime->TabIndex = 156;
			this->tbRightMotorUseTime->Tag = L"1";
			this->tbRightMotorUseTime->Text = L"0";
			this->tbRightMotorUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// btnRAZLeftMotorUseTime
			// 
			this->btnRAZLeftMotorUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnRAZLeftMotorUseTime->Location = System::Drawing::Point(416, 653);
			this->btnRAZLeftMotorUseTime->Name = L"btnRAZLeftMotorUseTime";
			this->btnRAZLeftMotorUseTime->Size = System::Drawing::Size(162, 39);
			this->btnRAZLeftMotorUseTime->TabIndex = 154;
			this->btnRAZLeftMotorUseTime->Tag = L"1";
			this->btnRAZLeftMotorUseTime->Text = L"RESET";
			this->btnRAZLeftMotorUseTime->UseVisualStyleBackColor = true;
			this->btnRAZLeftMotorUseTime->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnRAZLeftMotorUseTime_Click);
			// 
			// tbLeftMotorUseTime
			// 
			this->tbLeftMotorUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbLeftMotorUseTime->Location = System::Drawing::Point(416, 612);
			this->tbLeftMotorUseTime->Name = L"tbLeftMotorUseTime";
			this->tbLeftMotorUseTime->ReadOnly = true;
			this->tbLeftMotorUseTime->Size = System::Drawing::Size(162, 35);
			this->tbLeftMotorUseTime->TabIndex = 152;
			this->tbLeftMotorUseTime->Tag = L"1";
			this->tbLeftMotorUseTime->Text = L"0";
			this->tbLeftMotorUseTime->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblMotorUseTime
			// 
			this->lblMotorUseTime->AutoSize = true;
			this->lblMotorUseTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMotorUseTime->Location = System::Drawing::Point(12, 616);
			this->lblMotorUseTime->Name = L"lblMotorUseTime";
			this->lblMotorUseTime->Size = System::Drawing::Size(186, 29);
			this->lblMotorUseTime->TabIndex = 153;
			this->lblMotorUseTime->Tag = L"1";
			this->lblMotorUseTime->Text = L"MotorUseTime";
			// 
			// lblCompenseWeight
			// 
			this->lblCompenseWeight->AutoSize = true;
			this->lblCompenseWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCompenseWeight->Location = System::Drawing::Point(12, 257);
			this->lblCompenseWeight->Name = L"lblCompenseWeight";
			this->lblCompenseWeight->Size = System::Drawing::Size(220, 29);
			this->lblCompenseWeight->TabIndex = 151;
			this->lblCompenseWeight->Tag = L"2";
			this->lblCompenseWeight->Text = L"CompenseWeight";
			// 
			// tbRightMotorCurrent
			// 
			this->tbRightMotorCurrent->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRightMotorCurrent->Location = System::Drawing::Point(589, 343);
			this->tbRightMotorCurrent->Name = L"tbRightMotorCurrent";
			this->tbRightMotorCurrent->ReadOnly = true;
			this->tbRightMotorCurrent->Size = System::Drawing::Size(162, 35);
			this->tbRightMotorCurrent->TabIndex = 141;
			this->tbRightMotorCurrent->Tag = L"1";
			this->tbRightMotorCurrent->Text = L"0";
			this->tbRightMotorCurrent->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tbRightMotorSpeed
			// 
			this->tbRightMotorSpeed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbRightMotorSpeed->Location = System::Drawing::Point(589, 391);
			this->tbRightMotorSpeed->Name = L"tbRightMotorSpeed";
			this->tbRightMotorSpeed->ReadOnly = true;
			this->tbRightMotorSpeed->Size = System::Drawing::Size(162, 35);
			this->tbRightMotorSpeed->TabIndex = 140;
			this->tbRightMotorSpeed->Tag = L"1";
			this->tbRightMotorSpeed->Text = L"0";
			this->tbRightMotorSpeed->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tbLeftMotorCurrent
			// 
			this->tbLeftMotorCurrent->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbLeftMotorCurrent->Location = System::Drawing::Point(418, 343);
			this->tbLeftMotorCurrent->Name = L"tbLeftMotorCurrent";
			this->tbLeftMotorCurrent->ReadOnly = true;
			this->tbLeftMotorCurrent->Size = System::Drawing::Size(162, 35);
			this->tbLeftMotorCurrent->TabIndex = 138;
			this->tbLeftMotorCurrent->Tag = L"1";
			this->tbLeftMotorCurrent->Text = L"0";
			this->tbLeftMotorCurrent->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblMotorCurrent
			// 
			this->lblMotorCurrent->AutoSize = true;
			this->lblMotorCurrent->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMotorCurrent->Location = System::Drawing::Point(14, 347);
			this->lblMotorCurrent->Name = L"lblMotorCurrent";
			this->lblMotorCurrent->Size = System::Drawing::Size(173, 29);
			this->lblMotorCurrent->TabIndex = 139;
			this->lblMotorCurrent->Tag = L"1";
			this->lblMotorCurrent->Text = L"Motor Current";
			// 
			// tbLeftMotorSpeed
			// 
			this->tbLeftMotorSpeed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tbLeftMotorSpeed->Location = System::Drawing::Point(418, 391);
			this->tbLeftMotorSpeed->Name = L"tbLeftMotorSpeed";
			this->tbLeftMotorSpeed->ReadOnly = true;
			this->tbLeftMotorSpeed->Size = System::Drawing::Size(162, 35);
			this->tbLeftMotorSpeed->TabIndex = 136;
			this->tbLeftMotorSpeed->Tag = L"1";
			this->tbLeftMotorSpeed->Text = L"0";
			this->tbLeftMotorSpeed->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// lblMotorSpeed
			// 
			this->lblMotorSpeed->AutoSize = true;
			this->lblMotorSpeed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblMotorSpeed->Location = System::Drawing::Point(14, 395);
			this->lblMotorSpeed->Name = L"lblMotorSpeed";
			this->lblMotorSpeed->Size = System::Drawing::Size(157, 29);
			this->lblMotorSpeed->TabIndex = 137;
			this->lblMotorSpeed->Tag = L"1";
			this->lblMotorSpeed->Text = L"MotorSpeed";
			// 
			// tabPageCalibration
			// 
			this->tabPageCalibration->Controls->Add(this->dgvWeightTableLeft);
			this->tabPageCalibration->Controls->Add(this->dgvWeightTableRight);
			this->tabPageCalibration->Controls->Add(this->chrRight);
			this->tabPageCalibration->Controls->Add(this->chrLeft);
			this->tabPageCalibration->Controls->Add(this->btnCalibrateRightWeight);
			this->tabPageCalibration->Controls->Add(this->lblCalibrateRightWeight);
			this->tabPageCalibration->Controls->Add(this->btnCalibrateLeftWeight);
			this->tabPageCalibration->Controls->Add(this->lblCalibrateLeftWeight);
			this->tabPageCalibration->Location = System::Drawing::Point(4, 49);
			this->tabPageCalibration->Name = L"tabPageCalibration";
			this->tabPageCalibration->Padding = System::Windows::Forms::Padding(3);
			this->tabPageCalibration->Size = System::Drawing::Size(1570, 842);
			this->tabPageCalibration->TabIndex = 2;
			this->tabPageCalibration->Text = L"Calibration";
			this->tabPageCalibration->UseVisualStyleBackColor = true;
			// 
			// dgvWeightTableLeft
			// 
			this->dgvWeightTableLeft->AllowUserToAddRows = false;
			this->dgvWeightTableLeft->AllowUserToDeleteRows = false;
			this->dgvWeightTableLeft->AllowUserToResizeColumns = false;
			this->dgvWeightTableLeft->AllowUserToResizeRows = false;
			this->dgvWeightTableLeft->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgvWeightTableLeft->BackgroundColor = System::Drawing::Color::Gainsboro;
			this->dgvWeightTableLeft->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvWeightTableLeft->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dgvWeightTableLeft->ColumnHeadersHeight = 45;
			this->dgvWeightTableLeft->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvWeightTableLeft->DefaultCellStyle = dataGridViewCellStyle2;
			this->dgvWeightTableLeft->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->dgvWeightTableLeft->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->dgvWeightTableLeft->Location = System::Drawing::Point(5, 185);
			this->dgvWeightTableLeft->Margin = System::Windows::Forms::Padding(3, 3, 0, 3);
			this->dgvWeightTableLeft->MultiSelect = false;
			this->dgvWeightTableLeft->Name = L"dgvWeightTableLeft";
			this->dgvWeightTableLeft->ReadOnly = true;
			this->dgvWeightTableLeft->RowHeadersVisible = false;
			this->dgvWeightTableLeft->RowHeadersWidth = 75;
			this->dgvWeightTableLeft->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			dataGridViewCellStyle3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::Color::Black;
			this->dgvWeightTableLeft->RowsDefaultCellStyle = dataGridViewCellStyle3;
			this->dgvWeightTableLeft->RowTemplate->ReadOnly = true;
			this->dgvWeightTableLeft->RowTemplate->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvWeightTableLeft->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dgvWeightTableLeft->Size = System::Drawing::Size(305, 546);
			this->dgvWeightTableLeft->TabIndex = 124;
			this->dgvWeightTableLeft->TabStop = false;
			this->dgvWeightTableLeft->Tag = L"1";
			// 
			// dgvWeightTableRight
			// 
			this->dgvWeightTableRight->AllowUserToAddRows = false;
			this->dgvWeightTableRight->AllowUserToDeleteRows = false;
			this->dgvWeightTableRight->AllowUserToResizeColumns = false;
			this->dgvWeightTableRight->AllowUserToResizeRows = false;
			this->dgvWeightTableRight->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgvWeightTableRight->BackgroundColor = System::Drawing::Color::Gainsboro;
			this->dgvWeightTableRight->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvWeightTableRight->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle4;
			this->dgvWeightTableRight->ColumnHeadersHeight = 45;
			this->dgvWeightTableRight->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle5->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvWeightTableRight->DefaultCellStyle = dataGridViewCellStyle5;
			this->dgvWeightTableRight->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->dgvWeightTableRight->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->dgvWeightTableRight->Location = System::Drawing::Point(762, 185);
			this->dgvWeightTableRight->Margin = System::Windows::Forms::Padding(3, 3, 0, 3);
			this->dgvWeightTableRight->MultiSelect = false;
			this->dgvWeightTableRight->Name = L"dgvWeightTableRight";
			this->dgvWeightTableRight->ReadOnly = true;
			this->dgvWeightTableRight->RowHeadersVisible = false;
			this->dgvWeightTableRight->RowHeadersWidth = 75;
			this->dgvWeightTableRight->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			dataGridViewCellStyle6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::Color::Black;
			this->dgvWeightTableRight->RowsDefaultCellStyle = dataGridViewCellStyle6;
			this->dgvWeightTableRight->RowTemplate->ReadOnly = true;
			this->dgvWeightTableRight->RowTemplate->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvWeightTableRight->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dgvWeightTableRight->Size = System::Drawing::Size(305, 546);
			this->dgvWeightTableRight->TabIndex = 127;
			this->dgvWeightTableRight->TabStop = false;
			this->dgvWeightTableRight->Tag = L"1";
			// 
			// chrRight
			// 
			chartArea1->AxisX->Interval = 0.1;
			chartArea1->AxisX->Maximum = 0.4;
			chartArea1->AxisX->Minimum = 0.1;
			chartArea1->Name = L"chrAreaLeft";
			this->chrRight->ChartAreas->Add(chartArea1);
			this->chrRight->Location = System::Drawing::Point(1067, 185);
			this->chrRight->Margin = System::Windows::Forms::Padding(0, 3, 0, 3);
			this->chrRight->Name = L"chrRight";
			series1->ChartArea = L"chrAreaLeft";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::Color::Blue;
			series1->Name = L"Weight";
			series2->ChartArea = L"chrAreaLeft";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Color = System::Drawing::Color::Red;
			series2->Name = L"Calibration";
			this->chrRight->Series->Add(series1);
			this->chrRight->Series->Add(series2);
			this->chrRight->Size = System::Drawing::Size(449, 411);
			this->chrRight->TabIndex = 129;
			this->chrRight->Tag = L"1";
			this->chrRight->Text = L"chart1";
			// 
			// chrLeft
			// 
			chartArea2->AxisX->Interval = 0.1;
			chartArea2->AxisX->Maximum = 0.4;
			chartArea2->AxisX->Minimum = 0.1;
			chartArea2->Name = L"chrAreaLeft";
			this->chrLeft->ChartAreas->Add(chartArea2);
			this->chrLeft->Location = System::Drawing::Point(310, 185);
			this->chrLeft->Margin = System::Windows::Forms::Padding(0, 3, 0, 3);
			this->chrLeft->Name = L"chrLeft";
			series3->ChartArea = L"chrAreaLeft";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Color = System::Drawing::Color::Blue;
			series3->Name = L"Weight";
			series4->ChartArea = L"chrAreaLeft";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Red;
			series4->Name = L"Calibration";
			this->chrLeft->Series->Add(series3);
			this->chrLeft->Series->Add(series4);
			this->chrLeft->Size = System::Drawing::Size(449, 411);
			this->chrLeft->TabIndex = 128;
			this->chrLeft->Tag = L"1";
			this->chrLeft->Text = L"chart1";
			// 
			// btnCalibrateRightWeight
			// 
			this->btnCalibrateRightWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnCalibrateRightWeight->Location = System::Drawing::Point(1125, 67);
			this->btnCalibrateRightWeight->Name = L"btnCalibrateRightWeight";
			this->btnCalibrateRightWeight->Size = System::Drawing::Size(90, 90);
			this->btnCalibrateRightWeight->TabIndex = 126;
			this->btnCalibrateRightWeight->Tag = L"1";
			this->btnCalibrateRightWeight->Text = L"Go";
			this->btnCalibrateRightWeight->UseVisualStyleBackColor = true;
			this->btnCalibrateRightWeight->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnCalibrateRightWeight_Click);
			// 
			// lblCalibrateRightWeight
			// 
			this->lblCalibrateRightWeight->AutoSize = true;
			this->lblCalibrateRightWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCalibrateRightWeight->Location = System::Drawing::Point(769, 96);
			this->lblCalibrateRightWeight->Name = L"lblCalibrateRightWeight";
			this->lblCalibrateRightWeight->Size = System::Drawing::Size(261, 29);
			this->lblCalibrateRightWeight->TabIndex = 125;
			this->lblCalibrateRightWeight->Tag = L"1";
			this->lblCalibrateRightWeight->Text = L"CalibrateRightWeight";
			// 
			// btnCalibrateLeftWeight
			// 
			this->btnCalibrateLeftWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnCalibrateLeftWeight->Location = System::Drawing::Point(365, 67);
			this->btnCalibrateLeftWeight->Name = L"btnCalibrateLeftWeight";
			this->btnCalibrateLeftWeight->Size = System::Drawing::Size(90, 90);
			this->btnCalibrateLeftWeight->TabIndex = 121;
			this->btnCalibrateLeftWeight->Tag = L"1";
			this->btnCalibrateLeftWeight->Text = L"Go";
			this->btnCalibrateLeftWeight->UseVisualStyleBackColor = true;
			this->btnCalibrateLeftWeight->Click += gcnew System::EventHandler(this, &PearlingManualScreen::btnCalibrateLeftWeight_Click);
			// 
			// lblCalibrateLeftWeight
			// 
			this->lblCalibrateLeftWeight->AutoSize = true;
			this->lblCalibrateLeftWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lblCalibrateLeftWeight->Location = System::Drawing::Point(8, 97);
			this->lblCalibrateLeftWeight->Name = L"lblCalibrateLeftWeight";
			this->lblCalibrateLeftWeight->Size = System::Drawing::Size(243, 29);
			this->lblCalibrateLeftWeight->TabIndex = 120;
			this->lblCalibrateLeftWeight->Tag = L"1";
			this->lblCalibrateLeftWeight->Text = L"CalibrateLeftWeight";
			// 
			// PearlingManualScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(1578, 895);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(0, 100);
			this->Name = L"PearlingManualScreen";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Load += gcnew System::EventHandler(this, &PearlingManualScreen::PearlingManualScreen_Load);
			this->VisibleChanged += gcnew System::EventHandler(this, &PearlingManualScreen::PearlingManualScreen_VisibleChanged);
			this->tabControl->ResumeLayout(false);
			this->tabPageAxes->ResumeLayout(false);
			this->tabPageAxes->PerformLayout();
			this->tabPageStick->ResumeLayout(false);
			this->gbRightSpindle->ResumeLayout(false);
			this->gbRightSpindle->PerformLayout();
			this->gbLeftSpindle->ResumeLayout(false);
			this->gbLeftSpindle->PerformLayout();
			this->tabPageRecipe->ResumeLayout(false);
			this->tabPageRecipe->PerformLayout();
			this->tabPageSharpen->ResumeLayout(false);
			this->tabPageSharpen->PerformLayout();
			this->tabPagePearling->ResumeLayout(false);
			this->tabPagePearling->PerformLayout();
			this->tabPageCalibration->ResumeLayout(false);
			this->tabPageCalibration->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvWeightTableLeft))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvWeightTableRight))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrRight))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chrLeft))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void btnLeftMotor_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::StartMotor));
			SetTCManData(s_PearlingManual.MP_StartMotor[0].MB_Activate);
		 }
private: System::Void btnLeftMotor_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::StopMotor));
			ClearTCManData(s_PearlingManual.MP_StartMotor[0].MB_Activate);
		 }
private: System::Void btnOpenLeftChuck_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::OpenGripper));
			SetTCManData(s_PearlingManual.MP_OpenChuck[0].MB_Activate);
		 }
private: System::Void btnCloseLeftChuck_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::CloseGripper));
			ClearTCManData(s_PearlingManual.MP_OpenChuck[0].MB_Activate);
		 }
private: System::Void btnLeftEject_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::EjectStick));
			SetTCManData(s_PearlingManual.MP_EjectStick[0].MB_Activate);
		 }
private: System::Void btnLeftEject_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " +  TUtilities::pS_LoadString(TextIndex::CloseStickEjector));
			ClearTCManData(s_PearlingManual.MP_EjectStick[0].MB_Activate);
		 }
private: System::Void btnLeftBlowing_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " +  TUtilities::pS_LoadString(TextIndex::StartBlowing));
			SetTCManData(s_PearlingManual.MP_Blowing[0].MB_Activate);
		 }
private: System::Void btnLeftBlowing_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::StopBlowing));
			ClearTCManData(s_PearlingManual.MP_Blowing[0].MB_Activate);
		 }
private: System::Void btnRightMotor_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::StartMotor));
			SetTCManData(s_PearlingManual.MP_StartMotor[1].MB_Activate);
		 }
private: System::Void btnRightMotor_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::StopMotor));
			ClearTCManData(s_PearlingManual.MP_StartMotor[1].MB_Activate);
		 }
private: System::Void btnOpenRightChuck_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::OpenGripper));
			SetTCManData(s_PearlingManual.MP_OpenChuck[1].MB_Activate);
		 }
private: System::Void btnCloseRightChuck_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::CloseGripper));
			ClearTCManData(s_PearlingManual.MP_OpenChuck[1].MB_Activate);
		 }
private: System::Void btnRightEject_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::EjectStick));
			SetTCManData(s_PearlingManual.MP_EjectStick[1].MB_Activate);
		 }
private: System::Void btnRightEject_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " +  TUtilities::pS_LoadString(TextIndex::CloseStickEjector));
			ClearTCManData(s_PearlingManual.MP_EjectStick[1].MB_Activate);
		 }
private: System::Void btnRightBlowing_ON_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " +  TUtilities::pS_LoadString(TextIndex::StartBlowing));
			SetTCManData(s_PearlingManual.MP_Blowing[1].MB_Activate);
		 }
private: System::Void btnRightBlowing_OFF_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::StopBlowing));
			ClearTCManData(s_PearlingManual.MP_Blowing[1].MB_Activate);
		 }
private: System::Void PearlingManualScreen_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
			gbXaxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisX) + "  ";
			gbYaxis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisY) + "  ";
			gbZ1axis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisZ) + L"1  ";
			gbZ2axis->Text = L"  " + TUtilities::pS_LoadString(TextIndex::AxisZ) + L"2  ";

			tabPageAxes->Text = TUtilities::pS_LoadString(TextIndex::Robot);
			tabPageCalibration->Text = TUtilities::pS_LoadString(TextIndex::Calibration);
			tabPagePearling->Text = TUtilities::pS_LoadString(TextIndex::Pearling);
			tabPageRecipe->Text = TUtilities::pS_LoadString(TextIndex::Recipe);
			tabPageSharpen->Text = TUtilities::pS_LoadString(TextIndex::Sharpening);
			tabPageStick->Text = TUtilities::pS_LoadString(TextIndex::Stick);

			lblRobotPosition->Text = TUtilities::pS_LoadString(TextIndex::RobotPosition);
			gbLeftSpindle->Text = L"  " + TUtilities::pS_LoadString(TextIndex::LeftSpindle) + L"  ";
			gbRightSpindle->Text = L"  " + TUtilities::pS_LoadString(TextIndex::RightSpindle) + L"  ";
			lblLeftMotor->Text = TUtilities::pS_LoadString(TextIndex::Motor);
			lblRightMotor->Text = TUtilities::pS_LoadString(TextIndex::Motor);
			lblLeftChuck->Text = TUtilities::pS_LoadString(TextIndex::Chuck);
			lblRightChuck->Text = TUtilities::pS_LoadString(TextIndex::Chuck);
			lblLeftBlowing->Text = TUtilities::pS_LoadString(TextIndex::Blowing);
			lblRightBlowing->Text = TUtilities::pS_LoadString(TextIndex::Blowing);
			lblLeftEject->Text = TUtilities::pS_LoadString(TextIndex::Eject);
			lblRightEject->Text = TUtilities::pS_LoadString(TextIndex::Eject);
			lblCalibrateLeftWeight->Text = TUtilities::pS_LoadString(TextIndex::CalibrateLeftWeight);
			lblCalibrateRightWeight->Text = TUtilities::pS_LoadString(TextIndex::CalibrateRightWeight);
			lblLeftSpindle->Text = TUtilities::pS_LoadString(TextIndex::LeftSpindle);
			lblRightSpindle->Text = TUtilities::pS_LoadString(TextIndex::RightSpindle);
			lblLeftSpindlePearling->Text = TUtilities::pS_LoadString(TextIndex::LeftSpindle);
			lblRightSpindlePearling->Text = TUtilities::pS_LoadString(TextIndex::RightSpindle);

			pT_XDrive->ReloadComponent();
			pT_XDrive->SetPositionName(0,TUtilities::pS_LoadString(TextIndex::Position));
			pT_XDrive->SetDriveName(tabControl->TabPages[0]->Text + " X","");
			pT_YDrive->ReloadComponent();
			pT_YDrive->SetPositionName(0,TUtilities::pS_LoadString(TextIndex::Position));
			pT_YDrive->SetDriveName(tabControl->TabPages[0]->Text + " Y","");
			pT_Z1Drive->ReloadComponent();
			pT_Z1Drive->SetPositionName(0,TUtilities::pS_LoadString(TextIndex::Position));
			pT_Z1Drive->SetDriveName(tabControl->TabPages[0]->Text + " Z1","");
			pT_Z2Drive->ReloadComponent();
			pT_Z2Drive->SetPositionName(0,TUtilities::pS_LoadString(TextIndex::Position));
			pT_Z2Drive->SetDriveName(tabControl->TabPages[0]->Text + " Z2","");

			cobCalibrationPosition->Items->Clear();
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " A-B",E_TableSide::SideA, E_Axis::Z1, 0));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " A-B", E_TableSide::SideA, E_Axis::Z2, 1));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " C-D", E_TableSide::SideB, E_Axis::Z1, 2));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Table) + " C-D", E_TableSide::SideB, E_Axis::Z2, 3));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Barrel), E_TableSide::None, E_Axis::Z1,  4));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Barrel), E_TableSide::None, E_Axis::Z2, 5));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Reject), E_TableSide::None, E_Axis::Z1, 6));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Reject), E_TableSide::None, E_Axis::Z2, 7));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::Sharpening), E_TableSide::None, E_Axis::All, 8));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::CalibrateLeftWeight), E_TableSide::None, E_Axis::Z1, 9));
			cobCalibrationPosition->Items->Add(gcnew cbElement(this, TUtilities::pS_LoadString(TextIndex::CalibrateRightWeight), E_TableSide::None, E_Axis::Z2, 10));


			lblRestartBeginOfArea->Text = TUtilities::pS_LoadString(TextIndex::RestartBeginOfArea);
			lblCompenseWeight->Text = TUtilities::pS_LoadString(TextIndex::CompenseWeight) + " [g]";
			lblSharpenHeight->Text = TUtilities::pS_LoadString(TextIndex::SharpenHeight) + " [mm]";
			lblSharpenSpeed->Text = TUtilities::pS_LoadString(TextIndex::SharpenSpeed) + " [mm/s]";
			lblMinHoldLength->Text = TUtilities::pS_LoadString(TextIndex::MinHoldLength) + " [mm]";
			lblMotorSpeed->Text = TUtilities::pS_LoadString(TextIndex::MotorSpeed) + " [rpm]";
			lblMotorCurrent->Text = TUtilities::pS_LoadString(TextIndex::MotorCurrent) + " [mA]";
			lblMotorUseTime->Text = TUtilities::pS_LoadString(TextIndex::MotorUseTime) + " [h]";
			lblSpindleUseTime->Text = TUtilities::pS_LoadString(TextIndex::SpindleUseTime) + " [h]";
			lblSpindlePearlsCounter->Text = TUtilities::pS_LoadString(TextIndex::SpindlePearlsCounter) + " [-]";
			lblNbOfFwBwSharpen->Text = TUtilities::pS_LoadString(TextIndex::NbOfFwBwSharpen) + " [-]";
			lblNbOfFwBwBeforeTapeMove->Text = TUtilities::pS_LoadString(TextIndex::NbOfFwBwBeforeTapeMove) + " [-]";
			lblCompensationStep->Text = TUtilities::pS_LoadString(TextIndex::CompensationStep) + " [mm]";
			lblStopOnVacuumLoss->Text = TUtilities::pS_LoadString(TextIndex::StopOnVacuumLoss);
			lblStopOnStickBreak->Text = TUtilities::pS_LoadString(TextIndex::StopOnStickBreak);
			lblSpindleManualSpeed->Text = TUtilities::pS_LoadString(TextIndex::SpindleManualSpeed) + " [rpm]";
			lblSpindleRatio->Text = TUtilities::pS_LoadString(TextIndex::SpindleRatio) + " [-]";
			lblSpindleSharpenSpeed->Text = TUtilities::pS_LoadString(TextIndex::SpindleSpeed) + " [rpm]";
			lblWeightTolerance->Text = TUtilities::pS_LoadString(TextIndex::WeightTolerance) + " [g]";
			lblStopOnWeightOutOfTolerance->Text = TUtilities::pS_LoadString(TextIndex::StopOnWeightOutOfTolerance);
			lblHeightSensor->Text = TUtilities::pS_LoadString(TextIndex::HeightSensor) + " [-]";
			lblWeightSensor->Text = TUtilities::pS_LoadString(TextIndex::WeightSensor) + " [-]";
			lblMotorStopTimeout->Text = TUtilities::pS_LoadString(TextIndex::MotorStopTimeout) + " [ms]";
			lblMotorStartTimeout->Text = TUtilities::pS_LoadString(TextIndex::MotorStartTimeout) + " [ms]";
			bReloadParams = true;

			lblCurrentMotorMinTh->Text = TUtilities::pS_LoadString(TextIndex::CurrentMotorMinTh) + " [mA]";
			lblCurrentMotorWarnTh->Text = TUtilities::pS_LoadString(TextIndex::CurrentMotorWarnTh) + " [mA]";
			lblCurrentMotorMaxTh->Text = TUtilities::pS_LoadString(TextIndex::CurrentMotorMaxTh) + " [mA]";

		 }
/*private: System::Void tbMinHoldLength_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			if (e->KeyCode == Keys::Return)
			{
				double d_l_Data;

				if (Double::TryParse(tbMinHoldLength->Text,d_l_Data))
				{
					TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::MinHoldLength) + L" = " + tbMinHoldLength->Text);
					WriteTCData(s_StickDataShared.SDS_MinHoldLength,(TC_LREAL)d_l_Data);
				}
				else
					tbMinHoldLength->Text = L"0";
			}
			e->IsInputKey = true;
		 }*/
/*private: System::Void tbSharpenSpeed_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			if (e->KeyCode == Keys::Return)
			{
				double d_l_Data;

				if (Double::TryParse(tbSharpenSpeed->Text,d_l_Data))
				{
					TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SharpenSpeed) + L" = " + tbSharpenSpeed->Text);
					WriteTCData(s_StickDataShared.SDS_SharpenSpeed,(TC_LREAL)d_l_Data);
				}
				else
					tbSharpenSpeed->Text = L"0";
			}
			e->IsInputKey = true;
		 }*/
/*private: System::Void tbSharpenHeight_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			if (e->KeyCode == Keys::Return)
			{
				double d_l_Data;

				if (Double::TryParse(tbSharpenHeight->Text,d_l_Data))
				{
					TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SharpenHeight) + L" = " + tbSharpenHeight->Text);
					WriteTCData(s_StickDataShared.SDS_SharpenHeight,(TC_LREAL)d_l_Data);
				}
				else
					tbMinHoldLength->Text = L"0";
			}
			e->IsInputKey = true;
		 }*/
private: System::Void cbRestartBeginOfArea_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if (cbRestartBeginOfArea->Checked)
			{
				TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::RestartBeginOfArea) + L" = ON");
				SetTCData(s_StickDataShared.SDS_RestartBeginOfArea);
			}
			else
			{
				TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::RestartBeginOfArea) + L" = OFF");
				ClearTCData(s_StickDataShared.SDS_RestartBeginOfArea);
			}
		 }
private: System::Void ShowOsk_Click(System::Object^  sender, System::EventArgs^  e) {
			TUtilities::ShowOSK();
		 }
		 /*
private: System::Void tbCompenseRightWeight_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			if (e->KeyCode == Keys::Return)
			{
				int i_l_Data;

				if (Int32::TryParse(tbCompenseRightWeight->Text,i_l_Data))
				{
					TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::CompenseWeight) + L" = " + tbCompenseRightWeight->Text);
					WriteTCData(as_StickDataMMI[1].SD_CompenseWeight,(TC_INT)i_l_Data);
				}
				else
					tbCompenseRightWeight->Text = L"0";
			}
			e->IsInputKey = true;
		 }*/
/*private: System::Void tbNbOfFwBwSharpen_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			if (e->KeyCode == Keys::Return)
			{
				int i_l_Data;

				if (Int32::TryParse(tbNbOfFwBwSharpen->Text,i_l_Data))
				{
					TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::NbOfFwBwSharpen) + L" = " + tbNbOfFwBwSharpen->Text);
					WriteTCData(s_StickDataShared.SDS_NbOfFwBwSharpen, (TC_INT)i_l_Data);
				}
				else
					tbNbOfFwBwSharpen->Text = L"0";
			}
			e->IsInputKey = true;
		 }*/
/*private: System::Void tbNbOfFwBwBeforeTapeMove_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			if (e->KeyCode == Keys::Return)
			{
				int i_l_Data;

				if (Int32::TryParse(tbNbOfFwBwBeforeTapeMove->Text,i_l_Data))
				{
					TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::NbOfFwBwBeforeTapeMove) + L" = " + tbNbOfFwBwBeforeTapeMove->Text);
					WriteTCData(s_StickDataShared.SDS_NbOfFwBwBeforeTapeMove,(TC_INT)i_l_Data);
				}
				else
					tbNbOfFwBwBeforeTapeMove->Text = L"0";
			}
			e->IsInputKey = true;
		 }*/
private: System::Void tbRightCompensationStep_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(TUtilities::pS_LoadString(TextIndex::CompensationStep) + " " + TUtilities::pS_LoadString(TextIndex::Right), double::Parse(tbRightCompensationStep->Text), 0.0, 0.03, "F3");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::CompensationStep) + L" = " + Keypad->Value.ToString());
		WriteTCData(as_StickDataMMI[1].SD_MCRCorrectionStep, (TC_LREAL)Keypad->Value);
	}
}
private: System::Void cbStopOnVacuumLoss_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if (cbStopOnVacuumLoss->Checked)
			{
				TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::StopOnVacuumLoss) + L" = ON");
				SetTCData(s_StickDataShared.SDS_StopOnVacuumLoss);
			}
			else
			{
				TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::StopOnVacuumLoss) + L" = OFF");
				ClearTCData(s_StickDataShared.SDS_StopOnVacuumLoss);
			}
		 }
private: System::Void cbStopOnStickBreak_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if (cbStopOnStickBreak->Checked)
			{
				TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::StopOnStickBreak) + L" = ON");
				SetTCData(s_StickDataShared.SDS_StopOnStickBreak);
			}
			else
			{
				TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::StopOnStickBreak) + L" = OFF");
				ClearTCData(s_StickDataShared.SDS_StopOnStickBreak);
			}
		 }
private: System::Void btnCalibrateLeftWeight_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[3]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::CalibrateWeight));
			SetTCManData(s_PearlingManual.MP_CalibrateWeight[0].MB_Activate);
		 }
private: System::Void PearlingManualScreen_Load(System::Object^  sender, System::EventArgs^  e) {
			 dgvWeightTableLeft->ColumnCount = 2;
			 dgvWeightTableLeft->RowCount = 11;
			 dgvWeightTableLeft->Columns[0]->Name = "Z [mm]";
			 dgvWeightTableLeft->Columns[1]->Name = TUtilities::pS_LoadString(TextIndex::Weight) + " [g]";
			 dgvWeightTableLeft->Columns[1]->DefaultCellStyle->Format = "F1";
			 dgvWeightTableLeft->Rows->Clear();

			 dgvWeightTableRight->ColumnCount = 2;
			 dgvWeightTableRight->RowCount = 11;
			 dgvWeightTableRight->Columns[0]->Name = "Z [mm]";
			 dgvWeightTableRight->Columns[1]->Name = TUtilities::pS_LoadString(TextIndex::Weight) + " [g]";
			 dgvWeightTableRight->Columns[1]->DefaultCellStyle->Format = "F1";
			 dgvWeightTableRight->Rows->Clear();
		 }
private: System::Void btnRAZLeftMotorUseTime_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[2]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::MotorUseTime));
			SetTCManData(s_PearlingManual.MP_RAZMotorUseTime[0].MB_Activate);
		 }
private: System::Void btnRAZRightMotorUseTime_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[2]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::MotorUseTime));
			SetTCManData(s_PearlingManual.MP_RAZMotorUseTime[1].MB_Activate);
		 }
/*
private: System::Void tbCompenseLeftWeight_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
			if (e->KeyCode == Keys::Return)
			{
				int i_l_Data;

				if (Int32::TryParse(tbCompenseLeftWeight->Text,i_l_Data))
				{
					TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::CompenseWeight) + L" = " + tbCompenseLeftWeight->Text);
					WriteTCData(as_StickDataMMI[0].SD_CompenseWeight,(TC_INT)i_l_Data);
				}
				else
					tbCompenseLeftWeight->Text = L"0";
			}
			e->IsInputKey = true;
		 }*/


private: System::Void tbLeftCompensationStep_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(TUtilities::pS_LoadString(TextIndex::CompensationStep) + " " + TUtilities::pS_LoadString(TextIndex::Left), double::Parse(tbLeftCompensationStep->Text), 0.0, 0.03, "F3");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::CompensationStep) + L" = " + Keypad->Value.ToString());
		WriteTCData(as_StickDataMMI[0].SD_MCRCorrectionStep, (TC_LREAL)Keypad->Value);
	}
}

private: System::Void btnCalibrateRightWeight_Click(System::Object^  sender, System::EventArgs^  e) {
			TLogger::AddManualLog(tabControl->TabPages[3]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::CalibrateWeight));
			SetTCManData(s_PearlingManual.MP_CalibrateWeight[1].MB_Activate);
		 }
private: System::Void btnSafe_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(TUtilities::pS_LoadString(TextIndex::Pearling) + " : " + TUtilities::pS_LoadString(TextIndex::Safe));
	SetTCManData(s_PearlingManual.MP_Safe.MB_Activate);
}
private: System::Void btnRAZLeftSpindleUseTime_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[2]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::SpindleUseTime));
	SetTCManData(s_PearlingManual.MP_RAZSpindleUseTime[0].MB_Activate);
}
private: System::Void btnRAZRightSpindleUseTime_Click(System::Object^  sender, System::EventArgs^  e) {
	TLogger::AddManualLog(tabControl->TabPages[2]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::SpindleUseTime));
	SetTCManData(s_PearlingManual.MP_RAZSpindleUseTime[1].MB_Activate);
}
/*
private: System::Void tbLeftSpindleManualSpeed_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
	if (e->KeyCode == Keys::Return)
	{
		int i_l_Data;

		if (Int32::TryParse(tbLeftSpindleManualSpeed->Text, i_l_Data))
		{
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::SpindleManualSpeed) + L" = " + tbLeftSpindleManualSpeed->Text);
			WriteTCManData(s_PearlingManual.MP_SpindleSpeedSetpoint[0], (TC_INT)i_l_Data);
		}
		else
			tbLeftSpindleManualSpeed->Text = L"0";
	}
	e->IsInputKey = true;
}
private: System::Void tbRightSpindleManualSpeed_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
	if (e->KeyCode == Keys::Return)
	{
		int i_l_Data;

		if (Int32::TryParse(tbRightSpindleManualSpeed->Text, i_l_Data))
		{
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::SpindleManualSpeed) + L" = " + tbRightSpindleManualSpeed->Text);
			WriteTCManData(s_PearlingManual.MP_SpindleSpeedSetpoint[1], (TC_INT)i_l_Data);
		}
		else
			tbRightSpindleManualSpeed->Text = L"0";
	}
	e->IsInputKey = true;
}*/
/*private: System::Void tbLeftSpindleRatio_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
	if (e->KeyCode == Keys::Return)
	{
		double d_l_Data;

		if (Double::TryParse(tbLeftSpindleRatio->Text, d_l_Data))
		{
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Left) + " " + TUtilities::pS_LoadString(TextIndex::SpindleRatio) + L" = " + tbLeftSpindleRatio->Text);
			WriteTCData(as_StickDataMMI[0].SD_MCRRation, (TC_LREAL)d_l_Data);
		}
		else
			tbLeftSpindleRatio->Text = L"0";
	}
	e->IsInputKey = true;
}
private: System::Void tbRightSpindleRatio_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
	if (e->KeyCode == Keys::Return)
	{
		double d_l_Data;

		if (Double::TryParse(tbRightSpindleRatio->Text, d_l_Data))
		{
			TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::Right) + " " + TUtilities::pS_LoadString(TextIndex::SpindleRatio) + L" = " + tbRightSpindleRatio->Text);
			WriteTCData(as_StickDataMMI[1].SD_MCRRation, (TC_LREAL)d_l_Data);
		}
		else
			tbRightSpindleRatio->Text = L"0";
	}
	e->IsInputKey = true;
}*/

private: System::Void cobCalibrationPosition_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	cbElement^ oElement = (cbElement^)cobCalibrationPosition->SelectedItem;
	SetUI(oElement->Axis);
}
private: System::Void cobCalibrationPosition_OnSetItem(System::Object ^sender, MondemaComponents::ItemEventArgs ^e) {
	cbElement^ oElement = (cbElement^)e->Item;
	TLogger::AddManualLog(tabControl->TabPages[1]->Text + " : " + TUtilities::pS_LoadString(TextIndex::Position) + " : " + oElement->ToString());
	WriteTCManData(s_PearlingManual.MP_TeachPos, oElement->Position);
}
private: System::Void cbSimPearling_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (cbSimPearling->Checked)
	{
		TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : SimPearling = ON");
		SetTCData(b_SimPearling);
	}
	else
	{
		TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : SimPearling = OFF");
		ClearTCData(b_SimPearling);
	}
}

void OnUserLevelChanged(System::Object ^sender, UserLevelChangedEventArgs ^e);

private: System::Void lblLeftSpindleRatio_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblSpindleRatio->Text, double::Parse(lblLeftSpindleRatio->Text), 0.01, 10.0, "F2");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SpindleRatio) + L" Left = " + Keypad->Value.ToString());
		WriteTCData(as_StickDataMMI[0].SD_MCRRation, (TC_LREAL)(Keypad->Value));
	}
}
private: System::Void lblRightSpindleRatio_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblSpindleRatio->Text, double::Parse(lblRightSpindleRatio->Text), 0.01, 10.0, "F2");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SpindleRatio) + L" Right = " + Keypad->Value.ToString());
		WriteTCData(as_StickDataMMI[1].SD_MCRRation, (TC_LREAL)(Keypad->Value));
	}
}
private: System::Void lblLeftSpindleManualSpeedValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblSpindleManualSpeed->Text, double::Parse(lblLeftSpindleManualSpeedValue->Text), 1000.0, 6000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SpindleManualSpeed) + L" Left = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_SpindleSpeedSetpoint[0], (TC_INT)(Keypad->Value));
	}
}
private: System::Void lblRightSpindleManualSpeedValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblSpindleManualSpeed->Text, double::Parse(lblRightSpindleManualSpeedValue->Text), 1000.0, 6000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SpindleManualSpeed) + L" Right = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_SpindleSpeedSetpoint[1], (TC_INT)(Keypad->Value));
	}
}
private: System::Void lblLeftMotorStartTimeout_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblMotorStartTimeout->Text, double::Parse(lblLeftMotorStartTimeout->Text), 0.0, 5000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::MotorStartTimeout) + L" Left = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_MotorStartedTimeout[0], (TC_INT)(Keypad->Value));
	}
}
private: System::Void lblRightMotorStartTimeout_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblMotorStartTimeout->Text, double::Parse(lblRightMotorStartTimeout->Text), 0.0, 5000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::MotorStartTimeout) + L" Right = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_MotorStartedTimeout[1], (TC_INT)(Keypad->Value));
	}
}
private: System::Void lblLeftMotorStopTimeout_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblMotorStopTimeout->Text, double::Parse(lblLeftMotorStopTimeout->Text), 0.0, 5000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::MotorStopTimeout) + L" Left = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_MotorStoppedTimeout[0], (TC_INT)(Keypad->Value));
	}
}
private: System::Void lblRightMotorStopTimeout_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblMotorStopTimeout->Text, double::Parse(lblRightMotorStopTimeout->Text), 0.0, 5000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::MotorStopTimeout) + L" Right = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_MotorStoppedTimeout[1], (TC_INT)(Keypad->Value));
	}
}
private: System::Void lblLeftCompenseWeight_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblCompenseWeight->Text, double::Parse(lblLeftCompenseWeight->Text), -300.0, 300.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::CompenseWeight) + L" Left = " + Keypad->Value.ToString());
		WriteTCData(as_StickDataMMI[0].SD_CompenseWeight, (TC_INT)(Keypad->Value));
	}
}
private: System::Void lblRightCompenseWeight_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblCompenseWeight->Text, double::Parse(lblRightCompenseWeight->Text), -300.0, 300.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::CompenseWeight) + L" Right = " + Keypad->Value.ToString());
		WriteTCData(as_StickDataMMI[1].SD_CompenseWeight, (TC_INT)(Keypad->Value));
	}
}
private: System::Void lblNbOfFwBwSharpenValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblNbOfFwBwSharpen->Text, double::Parse(lblNbOfFwBwSharpenValue->Text), 1, 20, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::NbOfFwBwSharpen) + L" = " + Keypad->Value.ToString());
		WriteTCData(s_StickDataShared.SDS_NbOfFwBwSharpen, (TC_INT)Keypad->Value);
	}
}
private: System::Void lblNbOfFwBwBeforeTapeMoveValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblNbOfFwBwBeforeTapeMove->Text, double::Parse(lblNbOfFwBwBeforeTapeMoveValue->Text), 1, 10, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::NbOfFwBwBeforeTapeMove) + L" = " + Keypad->Value.ToString());
		WriteTCData(s_StickDataShared.SDS_NbOfFwBwBeforeTapeMove, (TC_INT)Keypad->Value);
	}
}
private: System::Void lblSharpenHeightValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblSharpenHeight->Text, double::Parse(lblSharpenHeightValue->Text), 0.05, 0.15, "F2");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SharpenHeight) + L" = " + Keypad->Value.ToString());
		WriteTCData(s_StickDataShared.SDS_SharpenHeight, (TC_LREAL)Keypad->Value);
	}
}
private: System::Void lblSharpenSpeedValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblSharpenSpeed->Text, double::Parse(lblSharpenSpeedValue->Text), 1.0, 50.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SharpenSpeed) + L" = " + Keypad->Value.ToString());
		WriteTCData(s_StickDataShared.SDS_SharpenSpeed, (TC_LREAL)Keypad->Value);
	}
}
private: System::Void lblSpindleSharpenSpeedValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblSpindleSharpenSpeed->Text, double::Parse(lblSpindleSharpenSpeedValue->Text), 1000.0, 6000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::SpindleSpeed) + L" = " + Keypad->Value.ToString());
		WriteTCData(s_StickDataShared.SDS_MCRSharpenSpeed, (TC_INT)Keypad->Value);
	}
}
private: System::Void lblMinHoldLengthValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblMinHoldLength->Text, double::Parse(lblMinHoldLengthValue->Text), 3.0, 15.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::MinHoldLength) + L" = " + Keypad->Value.ToString());
		WriteTCData(s_StickDataShared.SDS_MinHoldLength, (TC_LREAL)Keypad->Value);
	}
}
private: System::Void lblWeightToleranceValue_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblWeightTolerance->Text, double::Parse(lblWeightToleranceValue->Text), 10.0, 200.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::WeightTolerance) + L" = " + Keypad->Value.ToString());
		WriteTCData(s_StickDataShared.SDS_WeightTolerance, (TC_INT)Keypad->Value);
	}
}
private: System::Void cbStopOnWeightOutOfTolerance_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (cbStopOnWeightOutOfTolerance->Checked)
	{
		TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::StopOnWeightOutOfTolerance) + L" = ON");
		SetTCData(s_StickDataShared.SDS_StopOnWeightOutOfTolerance);
	}
	else
	{
		TLogger::AddManualLog(tabControl->TabPages[2]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::StopOnWeightOutOfTolerance) + L" = OFF");
		ClearTCData(s_StickDataShared.SDS_StopOnWeightOutOfTolerance);
	}

}
private: System::Void lblCurrentMotorMinThreshold_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblCurrentMotorMinThreshold->Text, double::Parse(lblCurrentMotorMinThreshold->Text), 1.0, 1000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::CurrentMotorMinTh) + L" = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_CurrentMotorMinTh, (TC_INT)Keypad->Value);
	}
}
private: System::Void lblCurrentMotorWarnThreshold_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblCurrentMotorWarnThreshold->Text, double::Parse(lblCurrentMotorWarnThreshold->Text), 1.0, 1000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::CurrentMotorWarnTh) + L" = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_CurrentMotorWarnTh, (TC_INT)Keypad->Value);
	}
}
private: System::Void lblCurrentMotorMaxThreshold_Click(System::Object^  sender, System::EventArgs^  e) {
	frmNumericKeypad^ Keypad = gcnew frmNumericKeypad(lblCurrentMotorMaxThreshold->Text, double::Parse(lblCurrentMotorMaxThreshold->Text), 1.0, 1000.0, "F0");
	if (Keypad->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
	{
		TLogger::AddManualLog(tabControl->TabPages[1]->Text + L" : " + TUtilities::pS_LoadString(TextIndex::CurrentMotorMaxTh) + L" = " + Keypad->Value.ToString());
		WriteTCManData(s_PearlingManual.MP_CurrentMotorMaxTh, (TC_INT)Keypad->Value);
	}
}
private: System::Void lblWeightTolerance_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
