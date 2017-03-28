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
using namespace KClmtrBase;
using namespace KClmtrNative;
class SubClass : public KClmtr {
public:
    SubClass(NSKClmtr* _NSK);
    void printMeasure(Measurement m);
    void printFlicker(Flicker f);
	void printCounts(Counts c);
    NSKClmtr* _NSKClmtr;
};
/** @endcond */
/** @ingroup wrappers
 *  @{
 */
/**
 * 	@brief Wraps the Native object to work easily in XCode
 */
@interface NSKClmtr : NSObject {

@private
    SubClass* _kclmtr;
    id targetMeasure;
    id targetFlicker;
	id targetCounts;
    SEL printMeasure;
    SEL printFlicker;
	SEL printCounts;
}

//Properties
-(NSString*)getPort;
-(void)setPort:(NSString*)PortName;
-(NSString*)getSerialNumber;
-(NSString*)getModel;
-(bool)isPortOpen;
-(void)setAimingLights:(bool) onOff;
-(void)setRange:(int) range;
-(int)getRange;
-(void)setZeroNoise:(bool)value;
-(bool)getZeroNoise;

//Properties - CalFiles
-(NSString*)getCalfileName;
-(int)getCalFileID;
-(void)setCalFileID:(int)calFileID;
-(Matrix<double>)getCalMatrix;
-(Matrix<double>)getRGBMatrix;
-(GamutSpec)getGamutSpec;
-(void)setGamutSpec:(GamutSpec)gamutSpec;
-(NSArray*)getCalfileList;
-(void)setTempCalFile:(CorrectedCoefficient)matrix;

//Properties - FFT
-(bool)getFFT_Cosine;
-(void)setFFT_Cosine:(bool)value;
-(bool)getFFT_Smoothing;
-(void)setFFT_Smoothing:(bool)value;
-(int)getFFT_Samples;
-(void)setFFT_Samples:(int)value;
-(bool)getFFT_PercentJEITA_Discount;
-(void)setFFT_PercentJEITA_Discount:(bool)onOff;
-(bool)getFFT_DBJEITA_Discount;
-(void) setFFT_DBJEITA_Discount:(bool)onOff;
-(PercentMode)getFFT_PercentMode;
-(void)setFFT_PercentMode:(PercentMode)mode;
-(DecibelMode)getFFT_DBMode;
-(void)setFFT_DBMode:(DecibelMode)onOff;
-(void)setFFT_numberOfPeaks:(int)numberOfPeaks;
-(int)getFFT_numberofPeaks;

//Measurements
-(bool)setMaxAverageCount:(int)maxAvg;
-(int)getMaxAverageCount;
-(SpeedMode)getMeasureSpeedMode;
-(void)setMeasureSpeedMode:(SpeedMode)s;
-(bool)isMeasuring;
-(void)startMeasuring;
-(void)stopMeasuring;
-(bool)getMeasurement:(out Measurement&) m;
-(Measurement)getNextMeasurment:(int)n;

//Counts
-(void)startMeasureCounts;
-(void)stopMeasureCounts;
-(bool)isMeasureCounts;
-(bool)getMeasureCounts:(out Counts&)c;
-(Counts)getNextMeasureCount;

//CalFiles
-(CorrectedCoefficient)getCofficintTestMatrix:(WRGB)Reference kclmtr:(WRGB)kclmtr;
-(int)deleteCalFile:(int)calFileID;
-(int)storeCalFile:(int)idNumber name:(NSString*)Name ref:(WRGB)Reference kclmtr:(WRGB)kclmtr;
-(int)storeCalFile:(int)idNumber name:(NSString*)Name correctionMatrix:(CorrectedCoefficient)correctionMatrix;


//BlackCal - Cold
-(BlackMatrix)captureBlackLevel;
-(BlackMatrix)getFlashMatrix;

//BlackCal - hot
-(BlackMatrix)getRAMMatrix;
-(BlackMatrix)getCoefficientMatrix;

//FFT
-(bool)isFlickering;
-(int)startFlicker;
-(Flicker)getNextFlicker;
-(void)stopFlickering;
-(bool)getFlicker:(out Flicker&)f;

//Setup/closing
-(bool)connect;
-(bool)connect:(NSString*)portName;
-(void)closePort;
 
+(bool)testConnection:(NSString*)portName model:(out NSString*)model SN:(out NSString*)SN;
 
-(void)sendFlicker:(Flicker)flicker;
-(void)sendMeasure:(Measurement)measurement;
-(void)sendCounts:(Counts)counts;
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
/** @brief Sets up where the Counts goes to
 *  @param target The object that needs to be sent to
 *  @param action The function that needs to be sent to
 *  @details Here is an example: 
 *  @details Header
 *  @snippet NSKClmtrExample.mm Header_measure
 *  Source
 *  @snippet NSKClmtrExample.mm Source_measure
 */
-(void)addTargetForCounts:(id)target action:(SEL)action;
@end
/** @} */