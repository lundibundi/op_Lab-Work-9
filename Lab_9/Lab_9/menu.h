#pragma once
#ifndef MENU_H_
#define MENU_H_

#include "library.h"

namespace Menu {

	void ShowMainMenu();
	void MainMenuSwitch(char choice, ::Library::Unit **lib, size_t &size);
	
	void ShowMenuForNewUnit();
	void NewUnitSwitch(char choice, ::Library::Unit **lib, size_t &size);
	
	void ShowBookGenres();
	void ShowMagazineThemes();
	void ShowPaperGenres();
}

#endif // !MENU_H_
