# ofxModuleCanon

Module for [ofxModule](https://github.com/reddoLabs/ofxModule) that chromakeys an image using a manipulated version of [ofxChromakeyShader](https://github.com/musiko/ofxChromaKeyShader).

Compatible with openFrameworks 0.11.0+

Generate all project files using the openFrameworks Project Generator.

## Required Addons

* [ofxModule](https://github.com/reddoLabs/ofxModule)
* [ofxCv](https://github.com/brinoausrino/ofxCanon)
* ofxOpenCv

## Getting started

Have a look at the sample project to get started directly and have a small explanation here.

## Settings

The module can be configured in the settings.json, which is hard since you do not have a direct feedback.

Therefore it is better to use the `greenscreenSetup` example to configure the parameters.

## Communication

### Control the module

The module receives `ofTexture` messages, proceeds them and notifies them back. 

To change the background you have to send an `ofTexture` message to the address ´setBg´.

```cpp
shared_ptr<ofTexture> texture;
notifyEvent("setBg", texture);
```

### Get messages from the module

The proceeded picture arrives as `ofTexture` message.

```cpp
void Presenter::proceedModuleEvent(ModuleEvent& e) {
		
		// update the cam image 
		if (e.type == ModuleEvent::MODULE_EVENT_TEXTURE) {
			proceedTexture = e.texture;
		}
    }
```