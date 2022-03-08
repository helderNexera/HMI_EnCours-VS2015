#include "LogScreen.h"

using namespace Projet1;

void LogScreen::OnLogUpdated(System::Object ^sender, System::EventArgs ^e)
{
	if (dgvLog->Rows[0] != nullptr)
		dgvLog->FirstDisplayedCell = dgvLog->Rows[0]->Cells[0];
}

void LogScreen::Reload(void)
{
	LogScreen_VisibleChanged(nullptr,nullptr);
}
