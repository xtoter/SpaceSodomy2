#include <iostream>
#include "Control.h"

using namespace std;

int main() {
	Control control("localhost", 8002);
	control.get_files_list();
	control.get_file("well.rep", "19.04.2021_21.40.rep");
	Sleep(1000000);
}