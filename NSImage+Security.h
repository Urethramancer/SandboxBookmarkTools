//
//  NSImage+Security.h
//  Copyright © 2013 Ronny Bangsund.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
// and associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
	NSURL *url = [[NSURL fileURLWithPath:path] restoreBookmark];
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
