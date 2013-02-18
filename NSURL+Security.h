//
//  NSURL_Security.h
//  SerialFiller
//
//  Created by Ronny Bangsund on 2/18/13.
//  Copyright (c) 2013 Neural Short-Circuit. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface NSURL(Security)
+(void)bookmarkDataWithPath:(NSString *)path;
+(void)bookmarkDataWithPath:(NSString *)path isDirectory:(BOOL)dir;
+(NSURL *)restoreURLFromPath:(NSString *)path;
+(NSURL *)restoreURLFromPath:(NSString *)path isDirectory:(BOOL)dir;
-(NSData *)saveBookmark;
-(NSURL *)restoreBookmark;
-(void)removeBookmark;
@end

@implementation NSURL(Security)
// Fire & forget saving of a security bookmark directly from a path.
// Use this while looping through files dropped by the user.
+(void)bookmarkDataWithPath:(NSString *)path
{
	NSURL *url = [NSURL fileURLWithPath:path];
	[url saveBookmark];
}


// Or use this when looping through directories.
+(void)bookmarkDataWithPath:(NSString *)path isDirectory:(BOOL)dir
{
	NSURL *url = [NSURL fileURLWithPath:path isDirectory:dir];
	[url saveBookmark];
}


// Shortcut from path to restored bookmarked URL.
+(NSURL *)restoreURLFromPath:(NSString *)path
{
	return [[NSURL fileURLWithPath:path] restoreBookmark];
}


+(NSURL *)restoreURLFromPath:(NSString *)path isDirectory:(BOOL)dir
{
	return [[NSURL fileURLWithPath:path isDirectory:dir] restoreBookmark];
}


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
