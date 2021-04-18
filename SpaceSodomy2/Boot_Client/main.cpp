#include <iostream>
#include "Control.h"

using namespace std;

int main() {
	Control control("localhost", 8001);
	control.get_replays();
}