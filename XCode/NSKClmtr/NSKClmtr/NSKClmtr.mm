//
//  NSKClmtr.m
//  NSKClmtr
//
//  Created by LUHR JENSEN on 5/14/12.
//  Copyright 2012 Klein Instruments. All rights reserved.
//

#import "NSKClmtr.h"

SubClass::SubClass(NSKClmtr* _NSK)
{
    _NSKClmtr = _NSK;
}
void SubClass::printFlick(Flicker f)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    NSFlicker *flicker = [[NSFlicker alloc] initWithFlicker:f];
    [_NSKClmtr sendFlicker:flicker];
    
    [pool release];
}
void SubClass::printMeasure(Measurement m)
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    NSMeasurement *measure = [[NSMeasurement alloc] initWithMeasurement:m];
    [_NSKClmtr sendMeasure:measure];

    [pool release];

}
@implementation NSMeasurement

-(id)init{
    self = [super init];
    if(self){
        [self convertToC:Measurement()];
    }
    return self;
}

-(id)initWithMeasurement:(Measurement)measure{
    self = [super init];
    if(self){
        [self convertToC:Measurement()];
    }
    return self;
}
-(id)initwithXYZ:(double)_X Y:(double)_Y Z:(double)_Z{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromXYZ(_X, _Y, _Z)];
    }
    return self;
}
-(id)initWithXYZ:(double)_X Y:(double)_Y Z:(double)_Z gs:(gamutSpec)gs{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromXYZ(_X, _Y, _Z, gs)];
    }
    return self;
}
-(id)initwithxyY:(double)_x y:(double)_y Y:(double)_Y{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromxyY(_x, _y, _Y)];
    }
    return self;
}
-(id)initwithxyY:(double)_x y:(double)_y Y:(double)_Y gs:(gamutSpec)gs{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromxyY(_x, _y, _Y, gs)];
    }
    return self;
}
-(id)initwithuvprimeY:(double)_u u:(double)_v Y:(double)_Y{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromuvprimeY(_u, _v, _Y)];
    }
    return self;
}
-(id)initwithuvprimeY:(double)_u u:(double)_v Y:(double)_Y gs:(gamutSpec)gs{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromuvprimeY(_u, _v, _Y, gs)];
    }
    return self;
}
-(id)initwithTempduvY:(double)_temp duv:(double)_duv Y:(double)_Y{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromTempduvY(_temp, _duv, _Y)];
    }
    return self;
}
-(id)initWithTempduvY:(double)_temp duv:(double)_duv Y:(double)_Y gs:(gamutSpec)gs{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromTempduvY(_temp, _duv, _Y, gs)];
    }
    return self;
}
-(id)initWithRGB:(double)_red green:(double)_green blue:(double)_blue{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromRGB(_red, _green, _blue)];
    }
    return self;
}
-(id)initWithRGB:(double)_red green:(double)_green blue:(double)_blue gs:(gamutSpec)gs{
    self = [super init];
    if(self){
        [self convertToC:Measurement::fromRGB(_red, _green, _blue, gs)];
    }
    return self;
}
-(void)convertToC:(Measurement)measure{
    x = measure.x;
    y = measure.y;
    bigx = measure.bigx;
    bigy = measure.bigy;
    bigz = measure.bigz;
    bigxraw = measure.bigxraw;
    bigyraw = measure.bigyraw;
    bigzraw = measure.bigzraw;
    red = measure.red;
    green = measure.green;
    blue = measure.blue;
    u = measure.u;
    v = measure.v;
    nm = measure.nm;
    nmduv = measure.nmduv;
    L = measure.L;
    a = measure.a;
    b = measure.b;
    C = measure.C;
    h = measure.h;
    redrange = measure.redrange;
    greenrange = measure.greenrange;
    bluerange = measure.bluerange;
    temp = measure.temp;
    tempduv = measure.tempduv;
    errorcode = measure.errorcode;
    averagingby = measure.averagingby;
}

@end

@implementation NSFlicker
-(id)init{
    self = [super init];
    if(self){
        [self convertToC:Flicker()];
    }
    return self;
}
-(id)initWithFlicker:(Flicker) flicker{
    self = [super init];
    if(self){
        [self convertToC:flicker];
    }
    return self;
}
-(void)convertToC:(Flicker) flicker {
    [xyz initWithMeasurement:flicker.xyz];
    for(int i = 0; i < 3; ++i){
        for(int x = 0; x < 3; ++x){
            peakfrequency[i][x] = flicker.peakfrequency[i][x];
        }
    }
    for(int i = 0; i < 129; ++i){
        flickerDB[i] = flicker.flickerDB[i];
        flickerPercent[i] = flicker.flickerPercent[i];
    }
    errorcode = flicker.errorcode;
}
@end

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
-(WhiteSpec)getWhiteSpec{
    return _kclmtr->getWhiteSpec();
}
-(void)resetWhiteSpec{
    _kclmtr->resetWhiteSpec();
}

-(void)setWhiteSpec:(WhiteSpec)whiteSpec{
    _kclmtr->setWhiteSpec(whiteSpec);
}
-(NSArray*)getCalfileList{
    NSMutableArray *calListboo = [[NSMutableArray alloc] init];;
    const string* fileList = _kclmtr->getCalFileList();
    
    for(int i = 0; i < 97; ++i)
        [calListboo addObject:[NSString stringWithUTF8String:fileList[i].c_str()]];
    
    return calListboo;
}

-(void)setTempCalFile:(CorrectedCoefficient)matrix whitespec:(WhiteSpec)whitespec{
    _kclmtr->setTempCalFile(matrix, whitespec);
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
-(bool)getFFT_RollOff{
    return _kclmtr->getFFT_RollOff();
}
-(void)setFFT_RollOff:(bool)value{
    _kclmtr->setFFT_RollOff(value);
}
-(int)getFFT_Samples{
    return _kclmtr->getFFT_Samples();
}
-(void)setFFT_Samples:(int)value{
    _kclmtr->setFFT_Samples(value);
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
-(NSMeasurement*)getNextMeasurment:(int)n{
    return [[NSMeasurement alloc] initWithMeasurement:_kclmtr->getNextMeasurement(n)];
}
-(CorrectedCoefficient)getCofficintTestMatrix:(wrgb)Reference kclmtr:(wrgb)kclmtr{
    return _kclmtr->getCoefficientTestMatrix(Reference, kclmtr);
}
-(int)deleteCalFile:(int)calFileID{
    return _kclmtr->deleteCalFile(calFileID);
}
-(int)storeCalFile:(int)idNumber name:(NSString*)Name ref:(wrgb)Reference kclmtr:(wrgb)kclmtr whitespec:(WhiteSpec)whitespec{
    return _kclmtr->storeMatrices(idNumber, [Name UTF8String], Reference, kclmtr, whitespec);
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
-(NSFlicker*)getNextFlicker{
    return [[NSFlicker alloc] initWithFlicker:_kclmtr->getNextFlicker()];
}
-(void)stopFlickering{
    _kclmtr->stopFlicker();
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

-(void)sendMeasure:(NSMeasurement*)measurement
{
    [_target performSelector:printMeasure withObject:measurement];
}
-(void)sendFlicker:(NSFlicker*)flicker
{
    [_target performSelector:printFlicker withObject:flicker];
}
-(void)addTarget:(id)target action:(SEL)action forEvent:(bool)measure
{
    self->_target = target;
    if(measure)
        printMeasure = action;
    else
        printFlicker = action;
}

@end
