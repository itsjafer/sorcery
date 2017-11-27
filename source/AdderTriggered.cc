#include "triggered.h"

using namespace std;

AdderTriggered::AdderTriggered(Event trigger, int attMod, int defMod, std::string target, std::string description):
        Triggered(trigger), attMod(attMod), defMod(defMod), target(target) {}