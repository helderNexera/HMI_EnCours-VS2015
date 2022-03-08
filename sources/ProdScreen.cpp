#include "ProdScreen.h"

using namespace System::Globalization;

using namespace Projet1;

void ProdScreen::UpdateUI(void)
{
	unsigned long l_l_ProdQty,l_l_GoodQty,l_l_EstimatedTimeLeft, l_l_EstimatedPartTime, l_l_ProductionTime;
	TC_BOOL b_l_Status,b_l_InitDone, b_l_ReadyForChangeJob;
	//double d_l_CycleTime;
	//TimeSpan T_l_EndProdDuration;

	try
	{
		pT_RTPearlingScreen->UpdateUI();
		btnCloseOrder->Enabled = (ProductionOrder::b_OrderStarted());
		btnReject->Enabled = (ProductionOrder::b_OrderStarted());
		ReadTCData(s_ModeMask.MMM_Stop,b_l_Status);
		ReadTCData(b_MachineInitDone,b_l_InitDone);
		ReadTCData(b_ReadyForChangeJob, b_l_ReadyForChangeJob);
		btnNewOrder->Enabled = b_l_ReadyForChangeJob && !(ProductionOrder::b_OrderStarted());
		ReadTCData(s_ModeMask.MMM_Purge,b_l_Status);
		btnPurge->Enabled = (b_l_Status != 0);
		lblOrder->Text = ": " + ProductionOrder::pS_GetName();
		lblPart->Text = ": " + ProductionOrder::pS_GetReference();
		lblOrderQuantity->Text = ": " + ProductionOrder::i_GetQuantity();
		ReadTCData(s_ProdData.PL_ProdQty,l_l_ProdQty);
		lblProdQuantity->Text = ": " + l_l_ProdQty.ToString();
		ReadTCData(s_ProdData.PL_GoodQty,l_l_GoodQty);
		lblGoodQuantity->Text = ": " + l_l_GoodQty.ToString();
		lblRejectQuantity->Text = ": " + (l_l_ProdQty-l_l_GoodQty).ToString();
		if (l_l_ProdQty > 0)
			lblYield->Text = ": " + (l_l_GoodQty*100/l_l_ProdQty) + " %";
		else
			lblYield->Text = ": -- %";
		pT_NewOrderForm->UpdateUI();
		pT_RejectScreen->UpdateUI();
		ReadTCData(s_MachineOpt.MO_RTPearling, b_l_Status);
		// RT pearling option
		btnRTPearling->Visible = (b_l_Status != 0) || TUser::b_HasSystemLevel();
		if (ProductionOrder::b_OrderStarted())
		{
			ReadTCData(s_ProdData.PL_ProductionTime, l_l_ProductionTime);

			TimeSpan^ dtProdTime = TimeSpan::FromMilliseconds(l_l_ProductionTime);

			lblProdTime->Text = ": " + TUtilities::pS_FormatTimeSpan(dtProdTime);
			if (l_l_ProductionTime == 0)
			{
				lblStartProdDate->Text = ": ???";
			}
			else
			{
				if (m_l_LastProductionTime != l_l_ProductionTime)
				{
					m_l_LastProductionTime = l_l_ProductionTime;
					if (l_l_ProductionTime - m_l_LastWriteProductionTime > 10000)
					{
						m_l_LastWriteProductionTime = l_l_ProductionTime;
						TJobLogger::UpdateDuration(dtProdTime);
					}
					
				}
				else
				{
					m_l_LastProductionTime = l_l_ProductionTime;
					if (m_l_LastWriteProductionTime != l_l_ProductionTime)
					{
						m_l_LastWriteProductionTime = l_l_ProductionTime;
						TJobLogger::UpdateDuration(dtProdTime);
					}
				}
				if (String::IsNullOrEmpty(ProductionOrder::pS_GetStartDate()))
				{
					DateTime dtNow = DateTime::Now;
					DateTime dtStartProd = dtNow.AddMilliseconds(-((double)l_l_ProductionTime));
					String^ pS_l_StartDate = TUtilities::pS_FormatDateTime(dtStartProd);
					ProductionOrder::SetStartDate(pS_l_StartDate);
					TJobLogger::UpdateStartTime(dtStartProd);
				}
				lblStartProdDate->Text = ": " + ProductionOrder::pS_GetStartDate();
			}
			if (!String::IsNullOrEmpty(ProductionOrder::pS_GetEndDate()))
			{
				lblEndProdDate->Text = ": " + ProductionOrder::pS_GetEndDate();
			}
			else
			{
				ReadTCData(s_ProdData.PL_EstimatedTimeLeft, l_l_EstimatedTimeLeft);
				ReadTCData(s_ProdData.PL_EstimatedPartTime, l_l_EstimatedPartTime);
				if (l_l_EstimatedPartTime != 0)
				{
					DateTime dtNow = DateTime::Now;
					DateTime dtEndProd = dtNow.AddMilliseconds(l_l_EstimatedTimeLeft);
					lblEndProdDate->Text = ": " + TUtilities::pS_FormatDateTime(dtEndProd);
				}
				else
				{
					lblEndProdDate->Text = ": ???";
				}
			}
		}
		else
		{
			m_l_LastProductionTime = 0;
			m_l_LastWriteProductionTime = 0;
			lblStartProdDate->Text = ": ???";
			lblEndProdDate->Text = ": ???";
			lblProdTime->Text = ": ???";
		}
		// Check autosampling option
		ReadTCData(s_MachineOpt.MO_AutoSampling, b_l_Status);
		if (b_l_Status != 0)
			pT_AutoSamplingScreen->UpdateUI();
		else
			TUtilities::UpdateMonostableButton(GetTCData(s_ProductionCmd.PC_RequestSample), btnRequestSample);
	}
	catch (Exception^ )
	{
	}
}

void ProdScreen::Reload(void)
{
	b_ScreenReloaded = true;
}
