//
//  NSKClmtr.h
//  NSKClmtr
//
//  Created by LUHR JENSEN on 5/14/12.
//  Copyright 2012 Klein Instruments. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "../../../kclmtr/KClmtr.h"

@class  NSKClmtr;

class SubClass : public KClmtr {
public:
    SubClass(NSKClmtr* _NSK);
    void printMeasure(Measurement m);
    void printFlick(Flicker f);
    NSKClmtr* _NSKClmtr;
};
@interface NSKMatrix : NSObject {
@public
    double v[3][3];
}
-(id)initWithMatrix:(matrix)Matrix;
@end
@interface NSMeasurement : NSObject {
@public
    double x;               //The x in the xyl
    double y;               //The y in the xyl
    double l;               //The l in the xyl
    double bigx;            //The x in the xyz
    double bigy;            //The y in the xyz
    double bigz;            //The z in the xyz
    double bigxraw;         //The xraw in the xyz
    double bigyraw;         //The yraw in the xyz
    double bigzraw;         //The zraw in the xyz
    double r;               //The r in the rgb
    double g;               //The g in the rgb
    double b;               //The b in the rgb
    double u;               //The u' in the u'v'y
    double v;               //The v' in the u'v'y
    double nm;              //The nm in the nmdu'v'Y
    double du;              //The duv' in the nmdu'v'Y
    //    double L;               //The L in L*A*B*
    //    double A;               //The A in L*A*B*
    //    double B;               //The B in L*A*B*
    NSString *redrange;		//The range which the KClmtr is in red
    NSString *greenrange;		//The range which the KClmtr is in green
    NSString *bluerange;		//The range which the KClmtr is in blue
    int range;              //The range which the KClmtr is in overall
    double temp;            //The temperature in K
    double duv;             //The distance off the curve
    int errorcode;          //The error code whenever you are getting data
    NSString *errorstring;	//The string
    int averagingby;        //How many measurements we are averaging by
    bool readyflag;         //Ready or not to grab it
}
-(id)initWithMeasurement:(Measurement) measure;
@end
@interface NSwrgb : NSObject
{
@public
    //white, red, green, blue
    //x, y, z
    double v[4][3];
}
-(id)initWithWRGB:(wrgb)WRGB;
-(wrgb)getNwrgb;
@end

@interface NSBlackMatrix : NSObject
{
@public
    double range1[3];
    double range2[3];
    double range3[3];
    double range4[3];
    double range5[3];
    double range6[3];
    double Therm;
    int errorcode;
    NSString *errorstring;
}
    
-(id)initWithBlackMatrix:(BlackMatrix)black;
@end

@interface NSCorrectedCoefficient : NSObject  
{
@public
    double colorMatrix[3][3];
    double rgbMatrix[3][3];
}
-(id)initWithCorrectedCoefficient:(CorrectedCoefficient)corrected;

-(CorrectedCoefficient)getNCorrectedCoefficient;

@end

@interface NSFlicker : NSObject
{
@public
    NSMeasurement *xyz;
    double peakfrequency[3][3];
    double flickerDB[101];
    double flickerPercent[101];
    int errorcode;
    NSString* errorstring;
    bool readyflag;
}
-(id)initWithFlicker:(Flicker)flicker;
@end

@interface NSColors : NSObject {
@public
    int red;
    int green;
    int blue;
}
-(id)initwithColors:(Colors)colors;
-(Colors)getNColor;
@end

@interface  NSWhiteSpect :  NSControl  {
@public
    double x;
    double y;
    double z;
    double xy;
    double l;
}
-(id)initWithWhite:(whitespect)White;
-(whitespect)getNwhitespect;
@end
@interface NSK10V : NSObject {
@private
    K10V* _k10v;
}
-(id)initWithK10V:(K10V)k10V;
-(K10V)getNK10V;
-(NSColors*)getColors;
-(void)setColors:(NSColors*)colors;
@end

@interface NSKClmtr : NSObject {

@private
    SubClass* _kclmtr;
    id _target;
    SEL printMeasure;
    SEL printFlicker;
}

//Properties
-(NSString*)getPort;
-(void)setPort:(NSString*)PortName;
-(NSString*)getSN;
-(NSString*)getModel;
-(bool)isPortOpen;

-(void)setAimingLights:(bool) onOff;

//Properties - CalFiles
-(NSString*)getCalfileName;
-(void)setCalFileName:(NSString*)calFileName;
-(int)getCalFileID;
-(void)setCalFileID:(int)calFileID;
-(NSMatrix*)getCalMatrix;
-(NSMatrix*)getRGBMatrix;
-(NSWhiteSpect*) getWhiteSpect;
-(void)resetWhiteSpect;

-(void)setWhiteSpect:(NSWhiteSpect*)whiteSpect;
-(NSString*)getCalfileList;
-(NSK10V*)getK10V;
-(void)setK10V:(NSK10V*)value;

-(void)setTempCalFile:(NSCorrectedCoefficient*)matrix whitespect:(NSWhiteSpect*)whitespect;

//Properties - FFT
-(bool)getFFT_Cosine;
-(void)setFFT_Cosine:(bool)value;
-(bool)getFFT_Smoothing;
-(void)setFFT_Smoothing:(bool)value;
-(bool)getFFT_RollOff;
-(void)setFFT_RollOff:(bool)value;
-(int)getFFT_Samples;
-(void)setFFT_Samples:(int)value;

//Measurements
-(bool)isMeasuring;
-(void)startMeasuring;
-(void)stopMeasuring;
-(NSMeasurement*)getNextMeasurment;
-(NSCorrectedCoefficient*)getCofficintTestMatrix:(NSwrgb*) Reference kclmtr:(NSwrgb*)kclmtr;
-(int)deleteCalFile:(int)calFileID;
-(int)storeCalFile:(int)idNumber name:(NSString*)Name ref:(NSwrgb*)Reference kclmtr:(NSwrgb*)kclmtr whitespect:(NSWhiteSpect*)whitespect;

//BlackCal - Cold
-(NSBlackMatrix*)captureBlackLevel;
-(NSBlackMatrix*)recallFlashMatrix;

//BlackCal - hot
-(NSBlackMatrix*)recallRAMMatrix;
-(NSBlackMatrix*)recallCoefficientMatrix;

//FFT
-(bool)isFlickering;
-(NSString*)startFlicker:(bool)grabConstantly;
-(NSFlicker*)getNextFlicker;
-(void)stopFlickering;

//Setup/closing
-(bool)connect;
-(bool)connect:(NSString*)portName;
-(void)closePort:(bool)resetThePortName;

//-(IBAction)printMeasure:(NSMeasurement*)measure;
//-(void)printFlicker:(NSFlicker*)flicker;
-(void)sendMeasure:(NSMeasurement*)measurement;
//-(void)sendFlicker:(NSFlicker*)flicker;
-(void)addTarget:(id)target action:(SEL)action forEvent:(bool)measure;

@end