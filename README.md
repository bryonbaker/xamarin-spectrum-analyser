# Xamarin Spectrum Analyser #

## Version 0.1 ##

### Summary ###

This repository provides a managed-code C# wrapper for the SuperpoweredSDK library and reimplements the SuperpoweredFrequencies demo in C#

### Contents: ###

* An XCode project that wraps up the SuperpoweredSDK so that it can be called from C#.
* A C# project that wraps and reimplements existing SuperpoweredSDK classes.
* A C# project that displays the audio spectrum. Each red bar is the note C and represents a different octave.

* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

#### Summary of set up ###

#### Building the XCode Library ####

Building the XCode library needs to be done form the command line with the makefile.

*make* clean will clean the project

*make* will make the project

It will generate a libSuperpoweredSDK.a library that needs to be copied to the Xamarin project, and two C# source code files:
* APIDefinition.cs
* StructsAndEnums.cs
These files can be ignored because I have modified them and they exist in the Xamarin project already.
NOTE: There is a problem with the latest XCode version and Sharpie will generate errors. These can be ignored because we are not using these generated source files anymore.


##### Objective Sharpie ####

The -sdk switch needs to match the sdk build Base SDK value in XCode under: *Build Settings > Architectures > Base SDK*.

##### Linker configuration #####

Build Options Configuration

Set the following options in the Project's *iOS Build* settings page:

* Linker Options: *Don't Link*
* Additional Options:

	-cxx -gcc_flags "-L${ProjectDir} -lSuperpoweredAudio -force_load ${ProjectDir}/libSuperpoweredAudio.a -lSuperpoweredXCodeWrapperSDK -force_load ${ProjectDir}/libSuperpoweredXCodeWrapperSDK.a" -gcc_flags "-Wl,-map,${ProjectDir}/output.map"

NOTE: Make sure you set the options for both *iPhone* and *iPhone Simulator*.

##### Dependencies ####

##### How to run tests #####

##### Deployment instructions #####
## LICENSE

SuperpoweredSDK is copyrighted by Superpowered Inc. License terms and conditions are detailed here:
http://superpowered.com/license/

All SuperpoweredSDK wrappers and bindings are copyrighted by Bryon Baker (c)2015 and are licensed under the the MIT License terms and conditions described below:

The MIT License (MIT)

Copyright (c) 2015 Bryon Baker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Owner: Bryon Baker
* Others: tbd