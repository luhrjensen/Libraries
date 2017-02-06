//! [Header_measure]
private slots:
    void on_Measure(QMeasurement measurement);
//! [Header_measure]

//! [Source_measure]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    //Registring QMeasurement
    qRegisterMetaType<QMeasurement>("QMeasurement");
    kclmtr = new QKClmtr();
    //Creating the measured between flickered to on_Measure
    connect(kclmtr, SIGNAL(measured(QMeasurement)), this, SLOT(on_Measure(QMeasurement)));
    ui->setupUi(this);
}
void MainWindow::on_Measure(QMeasurement measurement){
	// If the code is 0 then there was no error, there are other errors that could be dropped, take a look at the examples
    if(measurement.getErrorCode() == 0){
        //Output the measurement
    }else{
        //ERROR
	}
}
//! [Source_measure]

//! [Header_flicker]
private slots:
    void on_flicker(QFlicker flicker);
//! [Header_flicker]

//! [Source_flicker]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    //Registring QFlicker
    qRegisterMetaType<QFlicker>("QFlicker");
    kclmtr = new QKClmtr();
    //Creating the connection between flickered to on_flicker
    connect(kclmtr, SIGNAL(flickered(QFlicker)), this, SLOT(on_flicker(QFlicker)));
    ui->setupUi(this);
}

void MainWindow::on_flicker(QFlicker flicker){
	// If the code is 0 then there was no error, there are other errors that could be dropped, take a look at the examples
    if(flicker.getErrorCode() == 0){
        //Output the measurement
    }else{
        //ERROR
	}
}
//! [Source_flicker]