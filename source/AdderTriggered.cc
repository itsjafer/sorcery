#include "triggered.h"

using namespace std;

AdderTriggered::AdderTriggered(Event trigger, int attMod, int defMod, string &target, string &description):
        Triggered(description, 0, 0, description, trigger), attMod(attMod), defMod(defMod), target(target) {}