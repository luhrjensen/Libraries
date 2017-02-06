//! [measure]
class subClass : public KClmtr
{
public:
	void printMeasure(Measurement measure)
	{
		if(measure.getErrorCode() == 0){
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
		// If the code is 0 then there was no error, there are other errors that could be dropped, take a look at the examples
		if(flicker.getErrorCode() == 0){
			// output
		}else{
			// ERROR
		}
	}
};
//! [flicker]