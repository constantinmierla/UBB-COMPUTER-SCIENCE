#include "carRepo.h"
#include "carService.h"
#include "carValidator.h"
#include "CarGUI.h"

int main(int argc, char* argv[])
{
	testValidateCar();
	testDomain();
	testRepo();
	testService();

	CarRepo repo;
	CarRepo washrepo;
	CarService service{ repo, washrepo };
	populateCarList(service);
	QApplication app(argc, argv);
	CarGUI gui{ service };
	gui.show();
	return app.exec();

}

