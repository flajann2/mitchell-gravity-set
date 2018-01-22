#include "starconfig.hpp"

using namespace QtDataVisualization;

int main(int ac, char* av[]) {
  QApplication app(ac, av); 
  auto window = new StarConfig();
  
  window->init(); 
  return app.exec();
}
