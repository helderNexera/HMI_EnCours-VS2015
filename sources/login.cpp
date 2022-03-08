#include "login.h"

using namespace Projet1;

bool login::bMyLogin(int i_x_LanguageNb) 
{
	TUser::SetName(tbName->Text);
	// We need a valid name
	if (tbName->Text == "")
	{
		MyMsgBox^ pT_l_LoginError = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::NoNameError),TUtilities::pS_LoadString(TextIndex::LoginError),MessageBoxButtons::OK);
		pT_l_LoginError->ShowDialog();
		return false;
	}
	if (TUtilities::b_CheckPassword(tbName->Text,tbPassword->Text))
	{
		// This is an operator
		TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::NewLoginMode) + " : " + TUtilities::pS_LoadString(TextIndex::Operator));
		TUser::SetLevel(UL_Operator);
	}
	else if (TUtilities::b_CheckPassword(tbName->Text + "0",tbPassword->Text))
	{
		// This is maintenance
		TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::NewLoginMode) + " : " + TUtilities::pS_LoadString(TextIndex::Maintenance));
		TUser::SetLevel(UL_Maintenance);
	}
	else if (TUtilities::b_CheckPassword(tbName->Text + "1",tbPassword->Text))
	{
		// This is manager
		TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::NewLoginMode) + " : " + TUtilities::pS_LoadString(TextIndex::Manager));
		TUser::SetLevel(UL_Manager);
	}
	else
	{
		// This user/password is bad
		MyMsgBox^ pT_l_LoginError = gcnew MyMsgBox(TUtilities::pS_LoadString(TextIndex::PasswordError),TUtilities::pS_LoadString(TextIndex::LoginError),MessageBoxButtons::OK);
		pT_l_LoginError->ShowDialog();
		return false;
	}
	if (tbName->Text == "nexera")
	{
		TLogger::AddLog(TUtilities::pS_LoadString(TextIndex::NewLoginMode) + " : " + TUtilities::pS_LoadString(TextIndex::System));
		TUser::SetLevel(UL_System);
	}
	// Memorize language
	RegistryKey^ pT_l_LanguageKey = Registry::LocalMachine->CreateSubKey("Software")->CreateSubKey("Nexera")->CreateSubKey(C_REG_BASE_KEY);
	i_g_LanguageNb = i_x_LanguageNb;
	pT_l_LanguageKey->SetValue("DefaultLanguage", i_g_LanguageNb );
	pT_l_LanguageKey->Close();
	return true;
}
