# Xamarin Spectrum Analyser #

## Version 0.1 ##

### Summary ###

The Xamarin Spectrum Analyser is a small project that demonstrates how to bind C# managed code with the SuperpoweredSDK. It is not an attempt to provide a binding of the complete SDK, but rather demonstrates all of what you need to bind any of the SuperpoweredSDK class library to Xamarin. 

The single notable missing binding is the binding to SuperpoweredIOSAudioOutput. This is a complex binding that I did not need it for my initial implementation; I plan to build this later (or will happily accept contributions :-).

The X-Code and Xamarin projects give you everything you need to get up and going to extend the binding and enjoy the awesomeness of SuperpoweredSDK with cross-platform code!

### Contents: ###

* An XCode project that wraps up the SuperpoweredSDK and creates a satic library that can be called from C#.
* A Xamarin Solution that provides a bridge between the managed C# and the X-Code unmanaged codeand displays an audio spectrum os a standard-tuning guitar. Each red bar is the note C and represents a different octave.

### How do I get set up? ###

Building bindings is not for the faint hearted and what you have here is the result MANY hours of reading incomplete documentation and advanced concepts. Understanding how libraries, symbols, linking, and cross-language calling conventions work is really essential if you want to be productive. There are also a number of Unix utilities you need to use such as **lipo**, and **nm**.

For the basics you need to work thorugh the tutorial [Binding Objective-C](http://developer.xamarin.com/guides/ios/advanced_topics/binding_objective-c/). Note that the tutorial is out of date and does not work but if you get it working then you will be golden for everything else.

Another useful document to read is [Interop with Native Libraries](http://www.mono-project.com/docs/advanced/pinvoke/)
One key point that is easily missed is that the search path is **__Internal** if you statically link the library - so watch that one.

### Overview of the X-Code Project and Xamarin Solution and how it all works ###

#### X-Code ####

** Calling the C and C++ class library **

In order to bind to Superpowered you need to wrap up the C++ code in a way that enables it to be called from managed code. The information on how to do this is actually hard to find but basically there are two things working against you here:
C++ uses mangled names which means you need to create a map file to find the code you want to call.
You cannot create C++ objects from C#.
To work around this you reimplement each C++ method as a simple C function. The impact of this is that you need to pass object references into functions that need to call instance methods. For example, the following two functions are part of the reimplementation of the SuperpoweredBandpassFilterbank class:
Constructor: **extern "C" SuperpoweredBandpassFilterbank* SuperpoweredBandpassFilterbank_Create(int numBands, float frequencies[], float widths[], unsigned int samplerate);**
Instance method: **extern "C" void SuperpoweredBandpassFilterbank_SetSamplerate( SuperpoweredBandpassFilterbank *pObject, unsigned int sampleRate );**

There are two things going on here: 
1. extern "C" ensures that the function uses standard cdecl and does not mangle the function name.
2. The C++ object wrapper needs to pass the object reference in and out in order to construct the object and then call its methods.

**WARNING: IT IS CRITICAL THAT YOU DO NOT ALLOW AN EXCEPTION TO PASS FROM UNMANAGED CODE TO MANAGED CODE.** It is for this reason that the **catch(...)** is used and instead a diagnostic message is written to stderr. I think a good enhancement would be to add a result code to the C functions that can be tested in C# and then a call to get the error details.

** Calling Objective-C **

As I said, I have not bound SuperpoweredIOSAudioOutput yet - but have demonstrated what is required by binding to the SuperpoweredFrequencies demo. From an X-Code perspectiveyou do not need to do anything except make sure it is built into the library - the heavy lifting for this is done in C#.

The Xamarin utility Objective Sharpie is used t parse the Objective-C headers and create an ApiDefinition.cs and StructsAndEnums.cs class files. If you take the time to learn the notation I suggest writing them yourself.

Building the X-Code Project
To build the X-Code project you need to use the command line and run "make." This will create the libSuperpoweredXCodeWrapperSDK.a library that is needed for the Xaramin solution.

** Xamarin C# **

In the Xamarin Solution there are a couple of parts to the binding. To call the C or C++ code in SuperpoweredSDK you need to use pInvoke. To call Objective-C you need to use a C# binding. The solution therefore contains three projects.
	Project 1: SuperpoweredSDKXamarinWrapper - demonstrates how to wrap the C and C++ Superpowered library.
	Project 2: SuperpoweredSDKBinding - demonstrates how to bind to the SuperpoweredFrequencies demo in Objective-C (this is where the binding to SuperpoweredIOSAudioOutput will go).
	Project 3: XamarinSpectrumAnalyser - the project that demonstrates the implementation of the binding.

The code here is pretty self explanatory and the only thing worth noting is this is where we convert our "flattened" C++ code back into classes. Here I have basically reimplemented the original C++ interface in C# so you can use SuperpoweredBandpassFilterbank as per the current documentation.

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
The Xamarin solution depends upon **libSuperpoweredXCodeWrapperSDK.a** and **libSuperpoweredAudio.a.**

##### How to run tests #####
There are no tests written yet.

##### Deployment instructions #####
There are no special deployment instructions.

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

TBC

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Owner: Bryon Baker. Twiter: @bryonbakeraus

### Ongoing maintenance ###
There are no plans to maintain this repository. The project still serves as a useful tutorial for developers to work out how to integrate managed and unmanaged code as one of the major components have changed in how you use them.
If people would like to see this maintained against the l;atest releases of Xamarin, X Code, and SuperPowered then I would welcome pull requests.
I am very happy to field questions.