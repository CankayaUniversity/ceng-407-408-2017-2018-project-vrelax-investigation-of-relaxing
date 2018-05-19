# VRelax Investigation of Relaxing Computer Engineering Project

* Görkem Narinoğlu 201411041
* Umut Efiloğlu 201311016

##### Advisor: Dr. Faris Serdar Taşel
##### Co-Advisor: Assist. Prof. Dr. Murat YILMAZ

# Installation & Compilation Guide
This guide will describe how to install and compile VRelax from the release builds. Make sure to grab the latest build.

### Prerequisites
* Unreal Engine 4.18.3 should be installed to run and compile the project. Newer versions will work however older versions won't open the project correctly.
* Project uses AutoTerrainCover and Victory Plugins so they should be installed and added to the projects "Plugins" folder.
* Project use many materials both from the UE marketplace and from the web. The material and texture packages below should be obtained from the web if any package/material/texture not found errors occur when compiling.   
_- Animation Starter Pack_     
_- Beach Summer Pack_   
_- BeachShader_   
_- EssentialTreeKit_   
_- GTFreeMaterials_   
_- LowPolyForest_   
_- KiteDemo_   
_- Showcase_Assets_   
_- Starter Content_   
* Visual Studio 2017 should be installed to compile the project. Older versions won't compile the project.
* GSL Libraries should be installed to compile/run the project. You can download GSL from [this link](https://www.bruot.org/hp/media/files/libraries/gsl_2_2_msvc2017_64.zip).

### Compile & Run From Editor
* Copy the source files with a base folder to Unreal Engine default projects folder. (Optional)
* Open the VRELAX_IoR.uproject file.
* Run the the application from blue play button.
* You can change the play settings like Standalone Game or New Window (Optional)   

**Note:** Sometimes Editor doesn't sync with Visual Studio solution so if any error occurs please refer compile/run from VS 2017 section below.

### Compile & Run From Visual Studio 2017
* Open VRELAX_IoR.sln file.
* Go to Configuration Properties -> VC++ Directories -> Additional Include directories. Add GSL/include folder that you have downloaded.
* Go to Configuration Properties -> VC++ Directories -> Additional Library directories. Add GSL/lib folder that you have downloaded.
* Compile and run the project with green start button named "Local Windows Debugger".

## Installation

* Download project files named "VRELAX_IoR_V1.0.0-alpha.rar" from [here](https://github.com/CankayaUniversity/ceng-407-408-project-vrelax-investigation-of-relaxing/releases).
* Extract the files.
* Run the VRELAX_IoR.exe to run the application.   

**Note:** If any Prerequisites error occurs try running UE4PrereqSetup_x64.exe file first located in \Engine\Extras\Redist\en-us
