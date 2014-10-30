//! [measure]
public ref class Form1 : public System::Windows::Forms::Form {

	public:
		Form1(void){
			InitializeComponent();
			kClmtr = gcnew KClmtrWrapper::KClmtrWrap();
			//Connecting the Event
			kClmtr->measureEvent += gcnew KClmtrWrapper::KClmtrWrap::MeasureEventHandler(this, &Form1::printMeasurement);
		}
		
		private: KClmtrWrapper::KClmtrWrap^ kClmtr;

		public: System::Void printMeasurement(KClmtrWrapper::wMeasurement^ xyL) {
			if(this->TextX->InvokeRequired){
				// Form objects can't be updated from a different thread
				// This calls the function from the form's thread
				try{
					printMeasurementDelegate^ d = gcnew printMeasurementDelegate(this, &Form1::printMeasurement);
					this->Invoke(d, gcnew array<Object^> { xyL });
				}catch(...){
					// In case you closed the form before it could stop the measuring
				}
			}else{
				// If the code is 0 then there was no error
				if(xyL->errorcode == 0){
					// Output
				}else{
					// There was an error
				}
			}
		}
	};
};
//! [measure]
//! [flicker]
public ref class Form1 : public System::Windows::Forms::Form {

	public:
		Form1(void){
			InitializeComponent();
			kClmtr = gcnew KClmtrWrapper::KClmtrWrap();
			//Connecting the Event
			kClmtr->measureEvent += gcnew KClmtrWrapper::KClmtrWrap::FlickerEventHandler(this, &Form1::printFlicker);
		}
		
		private: KClmtrWrapper::KClmtrWrap^ kClmtr;

		public: System::Void printMeasurement(KClmtrWrapper::wFlicker^ flicker) {
			if(this->TextX->InvokeRequired){
				// Form objects can't be updated from a different thread
				// This calls the function from the form's thread
				try{
					printMeasurementDelegate^ d = gcnew printMeasurementDelegate(this, &Form1::printFlicker);
					this->Invoke(d, gcnew array<Object^> { flicker });
				}catch(...){
					// In case you closed the form before it could stop the measuring
				}
				// If the code is 0 then there was no error, there are other errors that could be dropped, take a look at the examples
				if(flicker->errorcode == 0){
					// Output
				}else{
					// There was an error
				}
			}
		}
	};
};
//! [flicker]