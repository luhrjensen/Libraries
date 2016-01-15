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
-(matrix)getCalMatrix{
    return _kclmtr->getCalMatrix();
}
-(matrix)getRGBMatrix{
    return _kclmtr->getRGBMatrix();
}
-(gamutSpec)getGamutSpec{
    return _kclmtr->getGamutSpec();
}
-(void)setGamutSpec:(gamutSpec)gamutSpec{
    _kclmtr->setGamutSpec(gamutSpec);
}
-(NSArray*)getCalfileList{
    NSMutableArray *calListboo = [[NSMutableArray alloc] init];;
    const string* fileList = _kclmtr->getCalFileList();
    
    for(int i = 0; i < 97; ++i)
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
-(bool)getFFT_PercentJEITA_Discount() {
	return _kclmtrgetFFT_PercentJEITA_Discount();
}
-(void)setFFT_PercentJEITA_Discount(bool onOff) {
	_kclmtr->setFFT_PercentJEITA_Discount(onOff);
}
-(bool)getFFT_DBJEITA_Discount() {
	return _kclmtr->getFFT_DBJEITA_Discount();
}
-(void) setFFT_DBJEITA_Discount(bool onOff) {
	_kclmtr->setFFT_DBJEITA_Discount(onOff);
}
-(FlickerSetting::percentMode) getFFT_PercentMode() {
	return _kclmtr->getFFT_PercentMode;
}
-(void)setFFT_PercentMode(FlickerSetting::percentMode mode) {
	_kclmtr->setFFT_PercentMode(mode);
}
-(FlickerSetting::decibelMode)getFFT_DBMode() {
	return _kclmtr->getFFT_DBMode();
}
-(void) setFFT_DBMode(FlickerSetting::decibelMode onOff) {
	_kclmtr->setFFT_DBMode(onOff);
}

//Measurements
-(bool)isMeasuring{
    return _kclmtr->isMeasuring();
}
-(void)startMeasuring{
    _kclmtr->startMeasuring();
}
-(void)stopMeasuring{
    _kclmtr->stopMeasuring();
}
-(AvgMeasurement)getNextMeasurment:(int)n{
    return _kclmtr->getNextMeasurement(n);
}
-(CorrectedCoefficient)getCofficintTestMatrix:(wrgb)Reference kclmtr:(wrgb)kclmtr{
    return _kclmtr->getCoefficientTestMatrix(Reference, kclmtr);
}
-(int)deleteCalFile:(int)calFileID{
    return _kclmtr->deleteCalFile(calFileID);
}
-(int)storeCalFile:(int)idNumber name:(NSString*)Name ref:(wrgb)Reference kclmtr:(wrgb)kclmtr {
    return _kclmtr->storeMatrices(idNumber, [Name UTF8String], Reference, kclmtr);
}
-(bool)getMeasurement:(Measurement&) m; {
	return _kclmtr->getMeasurement(m);
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
-(int)startFlicker:(bool)grabConstantly{
    return _kclmtr->startFlicker(grabConstantly);
}
-(Flicker)getNextFlicker{
    return _kclmtr->getNextFlicker();
}
-(void)stopFlickering{
    _kclmtr->stopFlicker();
}
-(bool)getFlicker:(Flicker&) f {
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

-(void)sendMeasure:(Measurement)measurement
{
    [targetMeasure performSelector:printMeasure withObject:[NSValue value:new Measurement(measurement) withObjCType:@encode(Measurement)]] ;
}
-(void)sendFlicker:(Flicker)flicker
{
    [targetFlicker performSelector:printFlicker withObject:[NSValue value:new Flicker(flicker) withObjCType:@encode(Flicker)]];
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

@end
