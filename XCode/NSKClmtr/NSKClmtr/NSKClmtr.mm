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
@implementation NSKMatrix

-(id)initWithMatrix:(matrix)Matrix{
    self = [super init];
    if(self){
    for(int i = 0; i < 3; i++)
        for(int x = 0; x < 3; x++)
            v[i][x] = Matrix.v[i][x];
    }
    
    return self;
}

@end
@implementation NSMeasurement
-(id)initWithMeasurement:(Measurement)measurement
{
    self = [super init];
    if(self){
        x = measurement.x;
        y = measurement.y;
        l = measurement.l;
        bigx = measurement.bigx;
        bigy = measurement.bigy;
        bigz = measurement.bigz;
        bigxraw = measurement.bigxraw;
        bigyraw = measurement.bigyraw;
        bigzraw = measurement.bigzraw;
        r = measurement.r;
        g = measurement.g;
        b = measurement.b;
        u = measurement.u;
        v = measurement.v;
        nm = measurement.nm;
        du = measurement.du;
        //        L = measurement.L;
        //        A = measurement.A;
        //        B = measurement.B;
        redrange = [NSString stringWithUTF8String:measurement.redrange.c_str()];
        greenrange = [NSString stringWithUTF8String:measurement.greenrange.c_str()];
        bluerange = [NSString stringWithUTF8String:measurement.bluerange.c_str()];
        range = measurement.range;
        temp = measurement.temp;
        duv = measurement.duv;
        errorcode = measurement.errorcode;
        errorstring = [NSString stringWithUTF8String:measurement.errorstring.c_str()];
        averagingby = measurement.averagingby;
        readyflag = measurement.readyflag;
    }
    return self;
}
//-(void)release
//{
//    [redrange release];
//    [greenrange release];
//    [bluerange release];
//    [errorstring release];
//    
//    [super release];
//    //[super dealloc];
//}
@end

@implementation NSwrgb

-(id)initWithWRGB:(wrgb)WRGB
{
    self = [super init];
    if(self){
        for(int i=0; i<4; ++i)
            for(int j=0; j<3; ++j)
                v[i][j] = WRGB.v[i][j];
    }
    return self;
}
-(wrgb)getNwrgb;
{
    wrgb WRGB;
    
    for(int i=0; i<4; ++i)
        for(int j=0; j<3; ++j)
            WRGB.v[i][j] = v[i][j];
    
    return WRGB;
}

@end

@implementation NSBlackMatrix
-(id)initWithBlackMatrix:(BlackMatrix)black;
{
    self = [super init];
    if(self){
        for(int i = 0; i < 3; i++)
        {
            range1[i] = black.range1[i];
            range2[i] = black.range2[i];
            range3[i] = black.range3[i];
            range4[i] = black.range4[i];
            range5[i] = black.range5[i];
            range6[i] = black.range6[i];
        }
        Therm = black.Therm;
        errorcode = black.errorcode;
        errorstring = [NSString stringWithUTF8String:black.errorstring.c_str()];
    }
    return self;
}

@end

@implementation NSFlicker

-(id)initWithFlicker:(Flicker)flicker
{
    self = [super init];
    if(self){
        xyz = [[NSMeasurement alloc] initWithMeasurement:flicker.xyz];
    
        for(int i = 0; i < 3; i++)
        {
            for(int x = 0; x < 3; x++)
            {
                peakfrequency[i][x] = flicker.peakfrequency[i][x];
            }
        }
        for(int i = 0; i < 101; i++)
        {
            flickerDB[i] = flicker.flickerDB[i];
            flickerPercent[i] = flicker.flickerPercent[i];
        }
        errorcode = flicker.errorcode;
        errorstring = [NSString stringWithUTF8String:flicker.errorstring.c_str()];
        readyflag = flicker.readyflag;
    }
    return self;
}
@end

@implementation NSWhiteSpect

-(id)initWithWhite:(whitespect)White
{
    self = [super init];
    if(self)
    {
        x = White.x;
        y = White.y;
        z = White.z;
        xy = White.xy;
        l = White.l;
    }
    return self;
}
-(whitespect)getNwhitespect
{
    whitespect White;
    
    White.x = x;
    White.y = y;
    White.z = z;
    White.xy = xy;
    White.l = l;
    
    return White;
}

@end

@implementation NSCorrectedCoefficient

-(id)initWithCorrectedCoefficient:(CorrectedCoefficient) corrected;
{
    self = [super init];
    if(self){
    for(int i = 0; i < 3; i++)
        {
            for(int x = 0; x < 3; x++)
            {
                colorMatrix[i][x] = corrected.colorMatrix[i][x];
                rgbMatrix[i][x] = corrected.rgbMatrix[i][x];
            }
        }
    }
    return self;
}
-(CorrectedCoefficient)getNCorrectedCoefficient
{
    CorrectedCoefficient corrected;
    for(int i = 0; i < 3; i++)
    {
        for(int x = 0; x < 3; x++)
        {
            corrected.colorMatrix[i][x] = colorMatrix[i][x];
            corrected.rgbMatrix[i][x] = rgbMatrix[i][x];
        }
    }
    return corrected;
}
@end
@implementation NSColors

-(id)initwithColors:(Colors)colors{
    self = [super init];
    if(self){
        red = colors.red;
        green = colors.green;
        blue = colors.blue;
    }
    return self;
}
-(Colors)getNColor{
    Colors color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    
    return color;
}

@end
@implementation NSK10V

-(id)initWithK10V:(K10V)k10V{
    self = [super init];
    if(self)
    {
        _k10v = new K10V();
    }
    return self;
}
-(K10V)getNK10V{
    return *_k10v;
}
-(NSColors*)getColors{
    return [[NSColors alloc]initwithColors: _k10v->getColorField()];
}
-(void)setColors:(NSColors*)colors{
    _k10v->setColorField([colors getNColor]);
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
-(NSString*)getSN{
    return [NSString stringWithUTF8String:_kclmtr->getSN().c_str()];
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
-(void)setCalFileName:(NSString*)calFileName{
     _kclmtr->setCalFileName([calFileName UTF8String]);
}
-(int)getCalFileID{
    return _kclmtr->getCalFileID();
}
-(void)setCalFileID:(int)calFileID{
    _kclmtr->setCalFileID(calFileID);
}
-(NSMatrix*)getCalMatrix{
    return [[NSKMatrix alloc] initWithMatrix:_kclmtr->getcalMatrix()];
}
-(NSMatrix*)getRGBMatrix{
    return [[NSKMatrix alloc] initWithMatrix:_kclmtr->getRGBMatrix()];
}
-(NSWhiteSpect*) getWhiteSpect{
    return [[NSWhiteSpect alloc] initWithWhite:_kclmtr->getWhiteSpect()];
}
-(void)resetWhiteSpect{
    _kclmtr->resetWhiteSpect();
}

-(void)setWhiteSpect:(NSWhiteSpect*)whiteSpect{
    _kclmtr->setWhiteSpect([whiteSpect getNwhitespect]);
}
-(NSArray*)getCalfileList{
    NSMutableArray *calListboo = [[NSMutableArray alloc] init];;
    const string* fileList = _kclmtr->getCalFileList();
    
    for(int i = 0; i < 97; ++i)
        [calListboo addObject:[NSString stringWithUTF8String:fileList[i].c_str()]];
    
    return calListboo;
}
-(NSK10V*)getK10V{
    return [[NSKClmtr alloc] initWithK10V:_kclmtr->getVirtualK10()];
}
-(void)setK10V:(NSK10V*)value{
    _kclmtr->setVirtualK10([value getNK10V]);
}

-(void)setTempCalFile:(NSCorrectedCoefficient*)matrix whitespect:(NSWhiteSpect*)whitespect{
    _kclmtr->setTempCalFile([matrix getNCorrectedCoefficient],[whitespect getNwhitespect]);
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
    return _kclmtr->getFFT_RoolOff();
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
-(NSMeasurement*)getNextMeasurment{
    return [[NSMeasurement alloc] initWithMeasurement:_kclmtr->getNextMeasurement()];
}
-(NSCorrectedCoefficient*)getCofficintTestMatrix:(NSwrgb*)Reference kclmtr:(NSwrgb*)kclmtr{
    return [[NSCorrectedCoefficient alloc] initWithCorrectedCoefficient:_kclmtr->getCoefficientTestMatrix([Reference getNwrgb], [kclmtr getNwrgb])];
}
-(int)deleteCalFile:(int)calFileID{
    return _kclmtr->deleteCalFile(calFileID);
}
-(int)storeCalFile:(int)idNumber name:(NSString*)Name ref:(NSwrgb*)Reference kclmtr:(NSwrgb*)kclmtr whitespect:(NSWhiteSpect*)whitespect{
    return _kclmtr->storeMatrices(idNumber, [Name UTF8String], [Reference getNwrgb], [kclmtr getNwrgb], [whitespect getNwhitespect]);
}

//BlackCal - Cold
-(NSBlackMatrix*)captureBlackLevel{
    return [[NSBlackMatrix alloc] initWithBlackMatrix:_kclmtr->captureBlackLevel()];
}
-(NSBlackMatrix*)recallFlashMatrix{
    return [[NSBlackMatrix alloc] initWithBlackMatrix:_kclmtr->recallFlashMatrix()];
}

//BlackCal - hot
-(NSBlackMatrix*)recallRAMMatrix{
    return [[NSBlackMatrix alloc] initWithBlackMatrix:_kclmtr->recallRAMMatrix()];
}
-(NSBlackMatrix*)recallCoefficientMatrix{
    return [[NSBlackMatrix alloc] initWithBlackMatrix:_kclmtr->recallCoefficientMatrix()];
}

//FFT
-(bool)isFlickering{
    return _kclmtr->isFlickering();
}
-(NSString*)startFlicker:(bool)grabConstantly{
    return [NSString stringWithUTF8String:_kclmtr->startFlicker(grabConstantly).c_str()];
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
-(void)closePort:(bool)resetThePortName{
    _kclmtr->closePort(resetThePortName);
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
