
#include "cinder/app/cocoa/CinderViewMac.h"
#include "CreativeEngineApp.h"
#include "cinder/app/RendererGl.h"
#import <Cocoa/Cocoa.h>

@interface CreativeEngineDelegate : NSObject <NSApplicationDelegate>
{
	IBOutlet CinderViewMac	*cinderView;
	IBOutlet NSWindow		*window;
	IBOutlet NSColorWell	*colorWell;

	CreativeEngineApp		*mApp;
}

@property (assign) IBOutlet NSWindow *window;

- (IBAction)subdivisionSliderChanged:(id)sender;
- (IBAction)colorChanged:(id)sender;

@end
