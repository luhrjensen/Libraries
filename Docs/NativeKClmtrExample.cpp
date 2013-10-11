//! [measure]
class subClass : public KClmtr
{
public:
	void printMeasure(Measurement measure)
	{
		if(measure.errorcode == 0){
			// output
		}else{
			// ERROR
		}
	}
};
//! [measure]
//! [flicker]
class subClass : public KClmtr
{
public:
	void printFlicker(Flicker flicker)
	{
		if(flicker.errorcode == 0){
			// output
		}else{
			// ERROR
		}
	}
};
//! [flicker]