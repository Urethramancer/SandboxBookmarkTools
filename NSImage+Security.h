//
//  NSImage_Security.h
//  SerialFiller
//
//  Created by Ronny Bangsund on 2/18/13.
//  Copyright (c) 2013 Neural Short-Circuit. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "NSURL+Security.h"


@interface NSImage(Security)
+initWithSecureContentsOfFile:(NSString *)path;
@end

@implementation NSImage(Security)
// Load an image previously bookmarked via the NSURL security category.
+initWithSecureContentsOfFile:(NSString *)path
{
	NSURL *url = [NSURL restoreURLFromPath:path];
	if(!url) return nil;
	
	// Check for selectors not available in OS X 10.7.3 or earlier
	// before proceeding to start access. Bookmarks in general will
	// work without them on 10.7.0 to 10.7.2, and security sandboxing
	// is ignored on 10.6.8.
	if([url respondsToSelector:@selector(startAccessingSecurityScopedResource)]) [url startAccessingSecurityScopedResource];
	NSImage *image = [[NSImage alloc] initWithContentsOfFile:[url path]];
	if([url respondsToSelector:@selector(stopAccessingSecurityScopedResource)]) [url stopAccessingSecurityScopedResource];
	return image;
}
@end
