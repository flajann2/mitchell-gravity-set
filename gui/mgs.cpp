#include "mgs.h"
#include "starconfig.h"

using namespace QtDataVisualization;
using namespace mgs;

int main(int ac, char* av[]) {
  QApplication app(ac, av); 
  auto window = new StarConfig();
  
  window->init(); 
  return app.exec();
}
