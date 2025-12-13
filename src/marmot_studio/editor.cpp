#include "editor.h"

using namespace marmot::studio;

void Editor::display() {
    _menu->display();
    _main_panel->display();
}
