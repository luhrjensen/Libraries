#include "KClmtr.h"
#include <stdio.h>
/**
  * @cond REMOVE
  */
class foobar : public KClmtr
{
public:
	foobar(){}
	~foobar(){}
	int i;
	void printMeasure(Measurement foobar)
	{
		i++;
		if(i < 100)
		{
			if(foobar.errorcode == 0)
				printf("x: %f y: %f Y: %f - %i\n", foobar.x, foobar.y, foobar.l, i);
			else{
				printf("ERROR: %s\n", foobar.errorstring.substr(2).c_str());
				i = 101;
			}
		}
	}
};

int main()
{
	printf("Hello World\n");

	foobar* Foobar = new foobar();

	Foobar->setKPort("/dev/ttyUSB0");
	Foobar->KHookUp();
	if(Foobar->isPortOpen() ==  true)
	{
		printf("Open\n");
		printf("SN: '%s'\n", Foobar->getSN().c_str());
		printf("Model: '%s'\n", Foobar->getModel().c_str());
		//printf("CaliFile: '%s'\n", Foobar->getCalFileList().c_str());
		Foobar->startMeasuring();
	}
	else
		printf("Not Open\n");


	while(Foobar->i < 100);
	printf("done Measuring\n");
	Foobar->stopMeasuring();
	Foobar->closePort(true);
	return 0;
}

/**
  * @endcond
  */