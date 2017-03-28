//
//  NSKClmtr.m
//  NSKClmtr
//
//  Created by Klein Instruments on 5/14/12.
//  Copyright 2012 Klein Instruments. All rights reserved.
//

#import "NSKClmtr.h"

SubClass::SubClass(NSKClmtr* _NSK)
{
    _NSKClmtr = _NSK;
}
void SubClass::printFlicker(Flicker f)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    [_NSKClmtr sendFlicker:f];
    
    [pool release];
}
void SubClass::printMeasure(Measurement m)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    [_NSKClmtr sendMeasure:m];

    [pool release];

}
void SubClass::printCounts(Counts c)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    [_NSKClmtr sendCounts:c];

    [pool release];

}

@implementation NSKClmtr

- (id)init
{
    self = [super init];
    if (self) {
        _kclmtr = new SubClass(self);
    }
    
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

-(NSString*) getPort{
    return [NSString stringWithUTF8String:_kclmtr->getPort().c_str()];
}
-(void) setPort:(NSString *)PortName 
{
    _kclmtr->setPort([PortName UTF8String]);
}
-(NSString*)getSerialNumber{
    return [NSString stringWithUTF8String:_kclmtr->getSerialNumber().c_str()];
}
-(NSString*)getModel{
    return [NSString stringWithUTF8String:_kclmtr->getModel().c_str()];
}
-(bool)isPortOpen{
    return _kclmtr->isPortOpen();
}

-(void)setAimingLights:(bool) onOff{
    _kclmtr->setAimingLights(onOff);
}
-(int)getRange{
	return _kclmtr->getRange();
}
-(void)setRange:(int) range{
	_kclmtr->setRange(range);
}
-(void)setZeroNoise:(bool)value {
    _kclmtr->setZeroNoise(value);
}
-(bool)getZeroNoise {
    return _kclmtr->getZeroNoise();
}
//Properties - CalFiles
-(NSString*)getCalfileName{
    return [NSString stringWithUTF8String:_kclmtr->getCalFileName().c_str()];
}
-(int)getCalFileID{
    return _kclmtr->getCalFileID();
}
-(void)setCalFileID:(int)calFileID{
    _kclmtr->setCalFileID(calFileID);
}
-(Matrix<double>)getCalMatrix{
    return _kclmtr->getCalMatrix();
}
-(Matrix<double>)getRGBMatrix{
    return _kclmtr->getRGBMatrix();
}
-(GamutSpec)getGamutSpec{
    return _kclmtr->getGamutSpec();
}
-(void)setGamutSpec:(GamutSpec)gamutSpec{
    _kclmtr->setGamutSpec(gamutSpec);
}
-(NSArray*)getCalfileList{
    NSMutableArray *calListboo = [[NSMutableArray alloc] init];;
    vector<string> fileList = _kclmtr->getCalFileList();
    
    for(size_t i = 0; i < fileList.size(); ++i)
        [calListboo addObject:[NSString stringWithUTF8String:fileList[i].c_str()]];
    
    return calListboo;
}

-(void)setTempCalFile:(CorrectedCoefficient)matrix {
    _kclmtr->setTempCalFile(matrix);
}

//Properties - FFT
-(bool)getFFT_Cosine{
    return _kclmtr->getFFT_Cosine();
}
-(void)setFFT_Cosine:(bool)value{
    _kclmtr->setFFT_Cosine(value);
}
-(bool)getFFT_Smoothing{
    return _kclmtr->getFFT_Smoothing();
}
-(void)setFFT_Smoothing:(bool)value{
    _kclmtr->setFFT_Smoothing(value);
}
-(int)getFFT_Samples{
    return _kclmtr->getFFT_Samples();
}
-(void)setFFT_Samples:(int)value{
    _kclmtr->setFFT_Samples(value);
}
-(bool)getFFT_PercentJEITA_Discount{
	return _kclmtr->getFFT_PercentJEITA_Discount();
}
-(void)setFFT_PercentJEITA_Discount:(bool)onOff{
	_kclmtr->setFFT_PercentJEITA_Discount(onOff);
}
-(bool)getFFT_DBJEITA_Discount{
	return _kclmtr->getFFT_DBJEITA_Discount();
}
-(void) setFFT_DBJEITA_Discount:(bool)onOff{
	_kclmtr->setFFT_DBJEITA_Discount(onOff);
}
-(PercentMode)getFFT_PercentMode{
	return _kclmtr->getFFT_PercentMode();
}
-(void)setFFT_PercentMode:(PercentMode)mode{
	_kclmtr->setFFT_PercentMode(mode);
}
-(DecibelMode)getFFT_DBMode{
	return _kclmtr->getFFT_DBMode();
}
-(void) setFFT_DBMode:(DecibelMode)onOff {
	_kclmtr->setFFT_DBMode(onOff);
}
-(void)setFFT_numberOfPeaks:(int)numberOfPeaks{
	_kclmtr->setFFT_numberOfPeaks(numberOfPeaks);
}
-(int)getFFT_numberofPeaks{
	return _kclmtr->getFFT_numberOfPeaks();
}
//Measurements
-(bool)setMaxAverageCount:(int)maxAvg{
	return _kclmtr->setMaxAverageCount(maxAvg);
}
-(int)getMaxAverageCount {
	return _kclmtr->getMaxAverageCount();
}
-(SpeedMode)getMeasureSpeedMode {
	return _kclmtr->getMeasureSpeedMode();
}
-(void)setMeasureSpeedMode:(SpeedMode)s{
	_kclmtr->setMeasureSpeedMode(s);
}
-(bool)isMeasuring{
    return _kclmtr->isMeasuring();
}
-(void)startMeasuring{
    _kclmtr->startMeasuring();
}
-(void)stopMeasuring{
    _kclmtr->stopMeasuring();
}
-(Measurement)getNextMeasurment:(int)n{
    return _kclmtr->getNextMeasurement(n);
}
-(bool)getMeasurement:(out Measurement&) m; {
	return _kclmtr->getMeasurement(m);
}

//Counts
-(void)startMeasureCounts{
	_kclmtr->startMeasureCounts();
}
-(void)stopMeasureCounts{
	_kclmtr->stopMeasureCounts();
}
-(bool)isMeasureCounts{
	return _kclmtr->isMeasureCounts();
}
-(bool)getMeasureCounts:(out Counts&)c{
	return _kclmtr->getMeasureCounts(c);
}
-(Counts)getNextMeasureCount{
	return _kclmtr->getNextMeasureCount();
}

//CalFiles
-(CorrectedCoefficient)getCofficintTestMatrix:(WRGB)Reference kclmtr:(WRGB)kclmtr{
    return _kclmtr->getCoefficientTestMatrix(Reference, kclmtr);
}
-(int)deleteCalFile:(int)calFileID{
    return _kclmtr->deleteCalFile(calFileID);
}
-(int)storeCalFile:(int)idNumber name:(NSString*)Name ref:(WRGB)Reference kclmtr:(WRGB)kclmtr {
    return _kclmtr->storeMatrices(idNumber, [Name UTF8String], Reference, kclmtr);
}
-(int)storeCalFile:(int)idNumber name:(NSString*)Name correctionMatrix:(CorrectedCoefficient)correctionMatrix {
	return _kclmtr->storeMatrices(idNumber, [Name UTF8String], correctionMatrix);
}

//BlackCal - Cold
-(BlackMatrix)captureBlackLevel{
    return _kclmtr->captureBlackLevel();
}
-(BlackMatrix)getFlashMatrix{
    return _kclmtr->getFlashMatrix();
}

//BlackCal - hot
-(BlackMatrix)getRAMMatrix{
    return _kclmtr->getRAMMatrix();
}
-(BlackMatrix)getCoefficientMatrix{
    return _kclmtr->getCoefficientMatrix();
}

//FFT
-(bool)isFlickering{
    return _kclmtr->isFlickering();
}
-(int)startFlicker{
    return _kclmtr->startFlicker();
}
-(Flicker)getNextFlicker{
    return _kclmtr->getNextFlicker();
}
-(void)stopFlickering{
    _kclmtr->stopFlicker();
}
-(bool)getFlicker:(out Flicker&) f {
	return _kclmtr->getFlicker(f);
}

//Setup/closing
-(bool)connect{
    return _kclmtr->connect();
}
-(bool)connect:(NSString*)portName{
    return _kclmtr->connect([portName UTF8String]);
}
-(void)closePort{
    _kclmtr->closePort();
}
+(bool)testConnection:(NSString*)portName model:(out NSString*)model SN:(out NSString*)SN{
	string _model, _SN;
	bool test = KClmtr::testConnection([portName UTF8String], _model, _SN);
	
	model = [NSString stringWithUTF8String:_model.c_str()];
	SN = [NSString stringWithUTF8String:_SN.c_str()];
	
	return test;
}


-(void)sendMeasure:(Measurement)measurement
{
    [targetMeasure performSelector:printMeasure withObject:[NSValue value:new Measurement(measurement) withObjCType:@encode(Measurement)]] ;
}
-(void)sendFlicker:(Flicker)flicker
{
    [targetFlicker performSelector:printFlicker withObject:[NSValue value:new Flicker(flicker) withObjCType:@encode(Flicker)]];
}
-(void)sendCounts:(Counts)counts
{
    [targetCounts performSelector:printCounts withObject:[NSValue value:new Counts(counts) withObjCType:@encode(Counts)]];
}
-(void)addTargetForMeasure:(id)target action:(SEL)action
{
    targetMeasure = target;
    printMeasure = action;
}
-(void)addTargetForFlicker:(id)target action:(SEL)action
{
    targetFlicker = target;
    printFlicker = action;
}
-(void)addTargetForCounts:(id)target action:(SEL)action
{
    targetCounts = target;
    printCounts = action;
}

@end
