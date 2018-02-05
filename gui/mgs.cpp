#include "mgs.h"
#include "starconfig.h"

using namespace QtDataVisualization;
//using namespace mgs::gui;

int main(int ac, char* av[]) {
  QApplication app(ac, av); 
  auto window = new mgs::gui::StarConfig();
  
  window->init(); 
  return app.exec();
}
