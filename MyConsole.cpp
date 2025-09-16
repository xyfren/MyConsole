#include "CommandLine.h"

using namespace std;

int main(int argc,char *argv[])
{
    setlocale(0, "");
   
    CommandLine cmd(argc,argv);
    
    return cmd.start();
}





