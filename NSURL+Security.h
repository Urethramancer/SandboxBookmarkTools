//
//  NSURL_Security.h
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

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface NSURL(Security)
-(NSData *)saveBookmark;
-(NSURL *)restoreBookmark;
-(void)removeBookmark;
@end

@implementation NSURL(Security)
// Save a security bookmark for the URL to the standard user defaults.
// The key is the path of the file (not a formatted URL).
-(NSData *)saveBookmark
{
	NSError *error = nil;
	NSData *bookmark = nil;
	bookmark = [self bookmarkDataWithOptions:NSURLBookmarkCreationWithSecurityScope includingResourceValuesForKeys:nil relativeToURL:nil error:&error];
	if(error)
	{
		[NSApp presentError:error];
		return nil;
	}
	[[NSUserDefaults standardUserDefaults] setObject:bookmark forKey:[self path]];
	return bookmark;
}


// Retrieve a security bookmark for the URL from the standard user defaults.
-(NSURL *)restoreBookmark
{
	NSError *error;
	BOOL stale;
	NSData *bookmark;
	NSURL *url;

	bookmark = [[NSUserDefaults standardUserDefaults] objectForKey:[self path]];
	url = [NSURL URLByResolvingBookmarkData:bookmark options:NSURLBookmarkResolutionWithSecurityScope relativeToURL:nil bookmarkDataIsStale:&stale error:&error];
	// We don't need stale keys hanging around in the user defaults
	if(stale || error)
	{
		[self removeBookmark];
		if(error) [NSApp presentError:error];
		return nil;
	}
	return url;
}


-(void)removeBookmark
{
	[[NSUserDefaults standardUserDefaults] removeObjectForKey:[self path]];
}
@end
