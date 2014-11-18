/* 
 Copyright (c) 2013 Alun Bestor and contributors. All rights reserved.
 This source file is released under the GNU General Public License 2.0. A full copy of this license
 can be found in this XCode project at Resources/English.lproj/BoxerHelp/pages/legalese.html, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */


//BXFrameRenderingView is a protocol for views that perform drawing of BXEmulator frames.
//It provides a consistent interface for BXDOSWindowController to communicate with
//different alternative view implementations.

#import <Cocoa/Cocoa.h>

typedef NS_ENUM(NSInteger, BXRenderingStyle) {
    BXRenderingStyleNormal,
    BXRenderingStyleSmoothed,
    BXRenderingStyleCRT,
    //---
    BXNumRenderingStyles
};


@class BXVideoFrame;

@protocol BXFrameRenderingView <NSObject>

//Return the current frame being rendered - i.e. the last frame that was passed
//to the view via updateWithFrame:. This property must be KVO-compliant.
@property (readonly, nonatomic) BXVideoFrame *currentFrame;

//Set/get the current rendering style of the view.
- (void) setRenderingStyle: (BXRenderingStyle)style;
- (BXRenderingStyle) renderingStyle;

//Whether this rendering view can render in the specified style.
- (BOOL) supportsRenderingStyle: (BXRenderingStyle)style;

//Returns whether the view should adjust its viewport to suit the aspect ratio
//of the current frame, or whether this will be done by adjusting the dimensions
//of the view itself.
- (void) setManagesViewport: (BOOL)managesViewport;
- (BOOL) managesViewport;

//Get/set the maximum size that the viewport is allowed to reach, beyond which it should remain
//the same size within the center of the view. Should only apply if managesViewport is YES.
- (NSSize) maxViewportSize;
- (void) setMaxViewportSize: (NSSize)size;

//Tells the view to render the specified frame next time it is redrawn.
//Typically the view should mark itself as needing display.
- (void) updateWithFrame: (BXVideoFrame *)frame;

//Reports the maximum displayable frame size (which may be limited by e.g. OpenGL
//maximum texture dimensions.) Frames larger than this will not be passed to updateWithFrame:.
- (NSSize) maxFrameSize;

//Reports where in the view the current frame will actually be rendered.
//This may be a portion of the total view size, when in fullscreen mode.
- (NSRect) viewportRect;


@optional
//Called to indicate to the rendering view that a view animation will be/has been
//applied to it. This permits the view to adjust its rendering context to suit
//the animation.
- (void) viewAnimationWillStart: (NSViewAnimation *)animation;
- (void) viewAnimationDidEnd: (NSViewAnimation *)animation;

//Called whenever the window changes color space or scaling factor.
- (void) windowDidChangeBackingProperties: (NSNotification *)notification;

@end
