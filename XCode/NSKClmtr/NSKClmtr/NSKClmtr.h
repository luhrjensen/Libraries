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
@interface NSMeasurement : NSObject {
@public
    double x;
    double y;
    double bigx;
    double bigy;
    double bigz;
    double bigxraw;
    double bigyraw;
    double bigzraw;
    double red;
    double green;
    double blue;
    double u;
    double v;
    double nm;
    double nmduv;
    double L;
    double a;
    double b;
    double C;
    double h;
    Measurement::MeasurmentRange redrange;
    Measurement::MeasurmentRange greenrange;
    Measurement::MeasurmentRange bluerange;
    double temp;
    double tempduv;
    int errorcode;
    int averagingby;
}
    
-(id)initWithMeasurement:(Measurement) measure;   
-(id)initwithXYZ:(double)_X Y:(double)_Y Z:(double)_Z;
-(id)initWithXYZ:(double)_X Y:(double)_Y Z:(double)_Z gs:(gamutSpec)gs;
-(id)initwithxyY:(double)_x y:(double)_y Y:(double)_Y;
-(id)initwithxyY:(double)_x y:(double)_y Y:(double)_Y gs:(gamutSpec)gs;
-(id)initwithuvprimeY:(double)_u u:(double)_v Y:(double)_Y;
-(id)initwithuvprimeY:(double)_u u:(double)_v Y:(double)_Y gs:(gamutSpec)gs;
-(id)initwithTempduvY:(double)_temp duv:(double)_duv Y:(double)_Y;
-(id)initWithTempduvY:(double)_temp duv:(double)_duv Y:(double)_Y gs:(gamutSpec)gs;
-(id)initWithRGB:(double)_red green:(double)_green blue:(double)_blue;
-(id)initWithRGB:(double)_red green:(double)_green blue:(double)_blue gs:(gamutSpec)gs;


-(void)convertToC:(Measurement) measure;

@end

@interface NSFlicker : NSObject {
@public
    NSMeasurement *xyz;
    double peakfrequency[3][3];
    double flickerDB[129];
    double flickerPercent[129];
    int errorcode;
}

-(id)initWithFlicker:(Flicker) flicker;

-(void)convertToC:(Flicker) flicker;
    
@end
/** @ingroup wrappers
 * 	@brief Wraps the Native object to work easly in XCode
 */
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
-(NSString*)getSerialNumber;
-(NSString*)getModel;
-(bool)isPortOpen;

-(void)setAimingLights:(bool) onOff;

//Properties - CalFiles
-(NSString*)getCalfileName;
-(int)getCalFileID;
-(void)setCalFileID:(int)calFileID;
-(matrix)getCalMatrix;
-(matrix)getRGBMatrix;
-(WhiteSpec)getWhiteSpec;
-(void)resetWhiteSpec;

-(void)setWhiteSpec:(WhiteSpec)whiteSpec;
-(NSArray*)getCalfileList;
-(void)setTempCalFile:(CorrectedCoefficient)matrix whitespec:(WhiteSpec)whitespec;

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
-(NSMeasurement*)getNextMeasurment:(int)n;
-(CorrectedCoefficient)getCofficintTestMatrix:(wrgb) Reference kclmtr:(wrgb)kclmtr;
-(int)deleteCalFile:(int)calFileID;
-(int)storeCalFile:(int)idNumber name:(NSString*)Name ref:(wrgb)Reference kclmtr:(wrgb)kclmtr whitespec:(WhiteSpec)whitespec;

//BlackCal - Cold
-(BlackMatrix)captureBlackLevel;
-(BlackMatrix)getFlashMatrix;

//BlackCal - hot
-(BlackMatrix)getRAMMatrix;
-(BlackMatrix)getCoefficientMatrix;

//FFT
-(bool)isFlickering;
-(int)startFlicker:(bool)grabConstantly;
-(NSFlicker*)getNextFlicker;
-(void)stopFlickering;

//Setup/closing
-(bool)connect;
-(bool)connect:(NSString*)portName;
-(void)closePort;
 
/** @brief Sends out flicker
 *  @details You must setup the target where the flicker needs to go to.
 *  @details Here is an example: 
 *  @details Header
 *  @snippet NSKClmtrExample.mm Header_flicker
 *   Source
 *  @snippet NSKClmtrExample.mm Source_flicker
 */
-(void)sendFlicker:(NSFlicker*)flicker;
/** @brief Sends out measurement
 *  @details You must setup the target where the measure needs to go to.
 *  @details Here is an example: 
 *  @details Header
 *  @snippet NSKClmtrExample.mm Header_measure
 *   Source
 *  @snippet NSKClmtrExample.mm Source_measure
 */
-(void)sendMeasure:(NSMeasurement*)measurement;
/** @brief Sets up where the measurement/flicker goes to
 *  @param target The object that needs to be sent to
 *  @param action The function that needs to be sent to
 *  @param measure If it's for measruement = TRUE, if it's for flicker = False
 */
-(void)addTarget:(id)target action:(SEL)action forEvent:(bool)measure;

@end