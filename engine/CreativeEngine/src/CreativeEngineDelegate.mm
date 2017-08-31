#include "cinder/Cinder.h"
#include "cinder/Rand.h"
#import "CreativeEngineDelegate.h"
#import "CinderImGui.h"

@implementation CreativeEngineDelegate

@synthesize window;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	cinder::app::AppBase::Settings settings;
    auto openGLOptions = cinder::app::RendererGl::Options();
    openGLOptions.msaa(16);
    
    
	cinder::app::RendererRef renderer( new cinder::app::RendererGl(openGLOptions) );
	CreativeEngineApp::initialize(&settings, renderer);

	mApp = new CreativeEngineApp;
	mApp->setupCinderView( cinderView );
	mApp->launch();

	[window setAcceptsMouseMovedEvents:YES];

	colorWell.color = [NSColor colorWithCalibratedRed:mApp->mColor.r green:mApp->mColor.g blue:mApp->mColor.b alpha:1.0f];
}

- (IBAction)subdivisionSliderChanged:(id)sender
{
	mApp->mRadius = [sender intValue];
}

- (IBAction)colorChanged:(id)sender
{
	NSColor *color = [sender color];
	mApp->mColor = ci::Colorf( [color redComponent], [color greenComponent], [color blueComponent] );
}

@end
