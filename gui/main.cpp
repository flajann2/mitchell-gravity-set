#include "mgs.h"
#include "star_config.h"

using namespace QtDataVisualization;
using namespace mgs;

int main(int ac, char* av[]) {
  QApplication app(ac, av); 
  auto window = new StarConfig();
  
  window->init(); 
  return app.exec();
}
