Sandbox Bookmark Tools
======================

A few categories to help with sandbox file access in OS X 10.7.3 and later.

NSURL+Security.h
================
Methods to save and restore security bookmarks for URLs. It's simple to use:
```smalltalk
[url saveBookmark];
```
or
```smalltalk
NSURL *newurl = [url restoreBookmark];
```
If there are any errors, it will call NSApp's presentError: method with the error message.
If this is undesired, just remove that line.

restoreBookmark will also remove any stale bookmarks automatically. To do this yourself:
```smalltalk
[url removeBookmark];
```

Then there are the even lazier shortcuts:
```smalltalk
[NSURL bookmarkDataWithPath:@/Users/me/Pictures/w00t.png"];
```
For directories:
```smalltalk
[NSURL bookmarkDataWithPath:@/Users/me/wherever/" isDirectory:YES];
```

And to restore from just a string:
```smalltalk
NSURL *url = [NSURL restoreURLFromPath:@/Users/me/Pictures/w00t.png"];
```
And for directories:
```smalltalk
NSURL *url = [NSURL restoreURLFromPath:@/Users/me/wherever/" isDirectory:YES];
```

NSImage+Security
================
Just one method to directly load an image previously bookmarked with the NSURL categories above.
It will use the access methods from OS X 10.7.3 if available, but will also work on 10.7.2 and earlier.

Example:
```smalltalk
NSImage *image = [NSImage initWithSecureContentsOfFile:@"/Users/me/Pictures/w00t.png"];
```

All these categories have only been used with ARC programs. I don't care about anything old and stale :)

Licence
=======
The code is licensed under the MIT licence. Go nuts with it. Or don't.
