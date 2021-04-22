#include <iostream>
#include "Control.h"

using namespace std;

int main() {
	Control control("localhost", 8002);
	while (1) {
		control.get_replays();
	}
}