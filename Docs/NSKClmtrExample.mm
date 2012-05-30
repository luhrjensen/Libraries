//! [Header_measure]
@interface Sample_Continuously_MeasuringAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSWindow *window;
    NSKClmtr *kclmtr;
}

@property (assign) IBOutlet NSWindow *window;

-(void)printTheMeasurement:(NSMeasurement*)m;

@end
//! [Header_measure]
//! [Source_measure]
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    kclmtr = [[NSKClmtr alloc] init];
    //Setting up where to send Measurement
    [kclmtr addTarget:self action:@selector(printTheMeasurement:) forEvent:true];
}
-(void)printTheMeasurement:(NSMeasurement*)m
{
    //Send out the Measurement
}
@end
//! [Source_measure]
//! [Header_flicker]
@interface Sample_Continuously_MeasuringAppDelegate : NSObject <NSApplicationDelegate> {
@private
    NSWindow *window;
    NSKClmtr *kclmtr;
}

@property (assign) IBOutlet NSWindow *window;

-(void)printTheMeasurement:(NSMeasurement*)m;

@end
//! [Header_flicker]
//! [Source_flicker]
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    kclmtr = [[NSKClmtr alloc] init];
    //Setting up where to send Flicker
    [kclmtr addTarget:self action:@selector(printTheFlicker:) forEvent:false];
}
-(void)printTheFlicker:(NSFlicker*)f
{
    //Send out the Flicker
}
@end
//! [Source_flicker]