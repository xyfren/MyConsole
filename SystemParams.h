#pragma once
#include <iostream>
#include <lmcons.h>

namespace Color {
	const std::string RESET = "\033[0m";
	const std::string BLACK = "\033[30m";
	const std::string RED = "\033[31m";
	const std::string GREEN = "\033[32m";
	const std::string YELLOW = "\033[33m";
	const std::string BLUE = "\033[34m";
	const std::string MAGENTA = "\033[35m";
	const std::string CYAN = "\033[36m";
	const std::string WHITE = "\033[37m";

	// Жирный текст
	const std::string BOLD = "\033[1m";
	const std::string BOLD_RED = "\033[1;31m";
	const std::string BOLD_GREEN = "\033[1;32m";
	const std::string BOLD_YELLOW = "\033[1;33m";

	// Фон
	const std::string BG_RED = "\033[41m";
	const std::string BG_GREEN = "\033[42m";
	const std::string BG_BLUE = "\033[44m";
}
inline std::string getUserName() {
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;

	if (GetUserNameA(username, &username_len)) {
		//std::cout << "Имя пользователя: " << username << std::endl;
	}
	else {
		std::cout << "Ошибка получения имени пользователя" << std::endl;
	}
	return username;
}
inline std::string getCompName() {
	char comp_name[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(comp_name);

	if (GetComputerNameA(comp_name, &size)) {
		//std::cout << "Имя компьютера: " << comp_name << std::endl;
		
	}
	else {
		std::cout << "Ошибка получения имени компьютера: "
			<< GetLastError() << std::endl;
	}
	return comp_name;
}


