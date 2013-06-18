//
//  NSKClmtr.h
//  NSKClmtr
//
//  Created by Klein Instruments on 5/14/12.
//  Copyright 2012 Klein Instruments. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "../../../kclmtr/KClmtr.h"

@class  NSKClmtr;
/** @cond */
class SubClass : public KClmtr {
public:
    SubClass(NSKClmtr* _NSK);
    void printMeasure(Measurement m);
    void printFlicker(Flicker f);
    NSKClmtr* _NSKClmtr;
};
/** @endcond */
/** @ingroup wrappers
 * 	@brief Wraps the Native object to work easly in XCode
 */
@interface NSKClmtr : NSObject {

@private
    SubClass* _kclmtr;
    id targetMeasure;
    id targetFlicker;
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
-(AvgMeasurement)getNextMeasurment:(int)n;
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
-(Flicker)getNextFlicker;
-(void)stopFlickering;

//Setup/closing
-(bool)connect;
-(bool)connect:(NSString*)portName;
-(void)closePort;
 
-(void)sendFlicker:(Flicker)flicker;
-(void)sendMeasure:(Measurement)measurement;
/** @brief Sets up where the measurement goes to
 *  @param target The object that needs to be sent to
 *  @param action The function that needs to be sent to
 *  @details Here is an example: 
 *  @details Header
 *  @snippet NSKClmtrExample.mm Header_flicker
 *  Source
 *  @snippet NSKClmtrExample.mm Source_flicker
 */
-(void)addTargetForMeasure:(id)target action:(SEL)action;
/** @brief Sets up where the flicker goes to
 *  @param target The object that needs to be sent to
 *  @param action The function that needs to be sent to
 *  @details Here is an example: 
 *  @details Header
 *  @snippet NSKClmtrExample.mm Header_measure
 *  Source
 *  @snippet NSKClmtrExample.mm Source_measure
 */
-(void)addTargetForFlicker:(id)target action:(SEL)action;

@end