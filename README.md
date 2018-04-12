# UnrealThumbnailGenerator

I created this tool because our team needed it to quickly make some thumbnails semi-automatic, instead of posing camera, taking a picture, cropping, re-importing and adjusting settings for every item in our games. I don't intend to give support on this asset if something breaks in a future version other than that if I would personally need the update for our projects. I will however check out community pull requests in case someone wants to PR the fixes or updates.

The tool is primarily designed for our needs but should fit people's need in general. I've added Static Mesh, Skeletal Mesh, animations and materials.

**IMPORTANT - Read before use**  
If you install this plugin into your project, make sure you go to project settings and put the setting "Custom Depth-Stencil Pass" to "Enabled With Stencil". If you don't like this option, you can turn it off when you are not using the creator. However, for the transparency to work, that has to be enabled for the duration of the usage.

**How it works:**  
You open the thumbnail generator and are started out with a scene and options panel on the left, on the options panel you can click buttons and also setup settings for the scene and screenshots.
Once you click on create screenshot it'll create a screenshot every 0.03s, once that all is done it'll go over all created screenshots and reimport them as UTexture2D into the engine and saved into the content browser.

**Binaries Downloads - for those who don't want to compile it themselves**  
4.18 -> https://drive.google.com/open?id=1D2wWOf1OO7Z1HgDnPVrSc83vH8oVQSGP  
4.19 -> https://drive.google.com/open?id=1zL1vahdDB-3GRyvB-WXrekFm8METUqJl

**How to install**  
Locate the .uproject file of your project. Once in that folder create a new folder and call it "Plugins", then create a new folder called "UnrealThumbnailCreator" inside that folder. Then go into that folder and drop the contens of the zip file into it. Then just launch the project. It's possible you need to enable the plugin inside the Plugins window of the editor. Don't forget to turn on the "Enabled with Stencil" as described above.

**Tips**    
Don't use the generator for objects that are relatively differently sized, it will use the same view rotation and view location for every shot taken, so you can bulk this with items of relatively the same size. (Chairs, Tables, Swords, bows, staffs, handguns, etc.)

**Exported**  
Images are exported as Texture2D's into the content browser under ThumbnailExports and are prefixed with Thumb_

![](https://i.imgur.com/q82lJjJ.png)

**Example of the UI**
![](https://i.imgur.com/zraPCAR.png)
![](https://i.imgur.com/NCVYqtw.png)
