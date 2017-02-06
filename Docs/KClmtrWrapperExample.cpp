//! [measure]
public ref class Form1 : public System::Windows::Forms::Form {

	public:
		Form1(void){
			InitializeComponent();
			kClmtr = gcnew KClmtrWrapper::KClmtrWrap();
			//Connecting the Event
			kClmtr->measureEvent += gcnew System::EventHandler<MeasureEventArgs ^>(this, &Form1::printMeasurement);
		}

		private: KClmtrWrapper::KClmtrWrap^ kClmtr;

		public: System::Void printMeasurement(Object ^sender, MeasureEventArgs^ e) {
			if(this->TextX->InvokeRequired){
				// Form objects can't be updated from a different thread
				// This calls the function from the form's thread
				try{
					this->Invoke(gcnew System::EventHandler<MeasureEventArgs ^>(this, &Form1::printMeasurement), gcnew array<Object^> {this, e});
				}catch(...){
					// In case you closed the form before it could stop the measuring
				}
			}else{
				// If the code is 0 then there was no error
				if(xyL->getErrorCode() == 0){
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
			kClmtr->measureEvent += gcnew System::EventHandler<FlickerEventArgs^ >(this, &Form1::printFlicker);
		}

		private: KClmtrWrapper::KClmtrWrap^ kClmtr;

		public: System::Void printMeasurement(Object ^sender, FlickerEventArgs^ e) {
			if(this->TextX->InvokeRequired){
				// Form objects can't be updated from a different thread
				// This calls the function from the form's thread
				try{
					this->Invoke(gcnew System::EventHandler<FlickerEventArgs ^>(this, &Form1::printFlicker), gcnew array<Object^> {this, e});
				}catch(...){
					// In case you closed the form before it could stop the measuring
				}
				// If the code is 0 then there was no error, there are other errors that could be dropped, take a look at the examples
				if(flicker->getErrorCode() == 0){
					// Output
				}else{
					// There was an error
				}
			}
		}
	};
};
//! [flicker]
