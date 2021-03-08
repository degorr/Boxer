//
//  BBAppDelegate.h
//  Boxer Bundler
//
//  Created by Alun Bestor on 15/08/2012.
//  Copyright (c) 2012 Alun Bestor. All rights reserved.
//

#import <Cocoa/Cocoa.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark -
#pragma mark Constants

extern NSString * const kBBRowIndexSetDropType;
extern NSString * const kUTTypeGamebox;
extern NSErrorDomain const kBBValidationErrorDomain;

NS_ERROR_ENUM(kBBValidationErrorDomain) {
    kBBValidationValueMissing,
    kBBValidationInvalidValue,
    kBBValidationUnsupportedApplication
};

typedef NS_ENUM(NSInteger, BXGameIdentifierType) {
	kBXGameIdentifierUserSpecified	= 0,	//!< Manually specified type.
	kBXGameIdentifierUUID			= 1,	//!< Standard UUID. Generated for empty gameboxes.
	kBXGameIdentifierEXEDigest		= 2,	//!< SHA1 digest of each EXE file in the gamebox.
	kBXGameIdentifierReverseDNS		= 3,	//!< Reverse-DNS (net.washboardabs.boxer)-style identifer.
};



#pragma mark -
#pragma mark Interface


@class BBIconDropzone;
@interface BBAppDelegate : NSObject <NSApplicationDelegate, NSTableViewDataSource, NSWindowDelegate>

#pragma mark -
#pragma mark Properties

@property (weak) IBOutlet NSWindow *window;
@property (weak) IBOutlet BBIconDropzone *iconDropzone;

@property (strong, nonatomic) NSURL *gameboxURL;
@property (strong, nonatomic, nullable) NSURL *appIconURL;
@property (copy, nonatomic) NSString *appName;
@property (copy, nonatomic) NSString *appBundleIdentifier;
@property (copy, nonatomic) NSString *appVersion;

@property (copy, nonatomic, nullable) NSString *organizationName;
@property (copy, nonatomic, nullable) NSString *organizationURL;

@property (nonatomic) BOOL showsLaunchPanelAlways;
@property (nonatomic) BOOL showsHotkeyWarning;
@property (nonatomic) BOOL showsAspectCorrectionToggle;
@property (nonatomic) BOOL ctrlClickEnabled;
@property (nonatomic) BOOL seamlessMouseEnabled;

@property (readonly, getter=isUnbranded) BOOL unbranded;

/// Will be @c YES while app generation is in progress. Disables the UI.
@property (readonly, getter=isBusy) BOOL busy;

/// A version of the app name suitable for use as a filename.
/// This replaces or removes restricted characters like :, / and \.
@property (readonly, nonatomic) NSString *sanitisedAppName;

/// Whether the launch panel is available for this gamebox:
/// will be @c NO if the gamebox has only one launch option.
/// Used for selectively disabling launch-related options.
@property (readonly, nonatomic) BOOL launchPanelAvailable;

/// An editable array of help links.
@property (strong, nonatomic) NSMutableArray<NSMutableDictionary*> *helpLinks;


#pragma mark -
#pragma mark Actions

/// Create a bundle.
- (IBAction) exportApp: (nullable id)sender;

- (IBAction) chooseIconURL: (nullable id)sender;

- (IBAction) importSettingsFromExistingApp: (nullable id)sender;


#pragma mark -
#pragma mark Helper class methods

/// Given a filename, returns a name suitable for inclusion in a bundle identifier.
+ (NSString *) bundleIdentifierFragmentFromString: (NSString *)inString;

/// Given the URL of a gamebox, returns an array of launch options found inside that gamebox.
+ (NSArray<NSDictionary<NSString*,id>*> *) launchersForGameboxAtURL: (NSURL *)gameboxURL;

@end

NS_ASSUME_NONNULL_END
