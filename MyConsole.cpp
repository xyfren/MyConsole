#include "CommandLine.h"

using namespace std;

int main()
{
    setlocale(0, "");
    string username = getUserName();
    string compname = getCompName();
    string id = username + "@" + compname;
    const char *title = id.c_str();
    wchar_t* wtitle = new wchar_t[strlen(title) + 1];
    mbstowcs_s(0, wtitle, strlen(title) + 1, title, _TRUNCATE);
    SetConsoleTitle(wtitle);
   


    CommandLine cmd(username,compname);
    return cmd.start();
}





