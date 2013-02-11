Chapter 2 Notes
===============

Wow, I spent way too much time deciphering the mysteries of hi-dpi (aka
Retina) and multiple resolution support.

Here's the quick start guide. You want a directory tree like this:

    Resources/
      images/
        iphone/
          background.png
        iphone-hd/
          background.png
        ipad/
          background.png
        ipad-hd/
          background.png

Note and note well: the images all have the same name! In the Objective-C
cocos2d, you add `-hd` to a file name in the same way UIKit likes it when
you add `@2x` to a file name.

Since cocos2d-x is cross-platform and can potentially support many
resolutions, it works a little differently.

**Important note**: make sure you use a subdirectory inside `Resources`.
i.e. your path is `Resources/images/iphone/` and not just `Resources/iphone`.
I had some strange random image picking behavior when I set it up like that,
so you have been warned.

Then it's just a matter of setting the resource search path(s) correctly.
Check out AppDelegate.cpp for that.

