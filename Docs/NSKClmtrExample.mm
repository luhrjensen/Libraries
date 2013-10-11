//! [Header_measure]
@interface Sample_Continuously_MeasuringAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSKClmtr *kclmtr;
}
-(void)printTheMeasurement:(id)m;

@end
//! [Header_measure]
//! [Source_measure]
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    kclmtr = [[NSKClmtr alloc] init];
    //Setting up where to send Measurement
    [kclmtr addTargetForMeasure:self action:@selector(printTheMeasurement:)];
}
- (void)printTheMeasurement:(id)m
{
    Measurement measure;
    [m getValue:&measure];
	if(measure.errorcode == 0){
		// output
	}else{
		// ERROR
	}
}
@end
//! [Source_measure]
//! [Header_flicker]
@interface Sample_Continuously_MeasuringAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSKClmtr *kclmtr;
}

-(void)printTheMeasurement:(id)m;

@end
//! [Header_flicker]
//! [Source_flicker]
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    kclmtr = [[NSKClmtr alloc] init];
    //Setting up where to send Flicker
    [kclmtr addTargetForFlicker:self action:@selector(printTheFlicker:)];
}
- (void)printTheFlicker:(id)f
{
    Flicker flicker;
    [f getValue:&flicker];
	if(flicker.errorcode == 0){
		// output
	}else{
		// ERROR
	}
}
@end
//! [Source_flicker]