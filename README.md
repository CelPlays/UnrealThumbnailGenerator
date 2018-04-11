# UnrealThumbnailGenerator

I created this tool because our team needed it to quickly make some thumbnails semi-automatic, instead of posing camera, taking a picture, cropping, re-importing and adjusting settings for every item in our games. I don't intend to give support on this asset if something breaks in a future version other than that if I would personally need the update for our projects. I will however check out community pull requests in case someone wants to PR the fixes or updates.

The tool is primarily desgined for our needs but should fit people's need in general. I've added Static Mesh, Skeletal Mesh, animations and materials.

**How it works:**  
You open the thumbnail generator and are started out with a scene and options panel on the left, on the left you can click buttons and also setup settings for the scene and screenshots.
Once you click on create screenshot it'll create a screenshot every 0.03s, once that all is done it'll go over all created screenshots and reimport them as UTexture2D into the engine and saved into the content browser.

**Tips**  
Don't use the generator for objects of relatively different sized objects, it will use the same view rotation and view location for every shot taken, so you can bulk this with items of relatively the same size. (Chairs, Tables, Swords, bows, staffs, handguns, etc.)

**Exported**
Images are exported as Texture2D's into the content browser under ThumbnailExports and are prefixed with Thumb_

![](https://i.imgur.com/q82lJjJ.png)

**Example of the UI**
![](https://i.imgur.com/zraPCAR.png)
![](https://i.imgur.com/NCVYqtw.png)
