# PCSDK openFrameworks Examples

openFrameworks example apps from the [Perceptual Computing Lab](http://about.me/intelperceptual)

## Prerequisites
	
- Download & install the [Perceptual Computing SDK](http://software.intel.com/en-us/vcsource/tools/perceptual-computing-sdk)
- Download & Install [openFrameworks](http://openframeworks.cc)

## Installation

Sync this repo into your **$(OFX_ROOT)/apps** folder so you end up with something like:

	of_v0.8.0_vs_release/apps/ofxApps

Samples using the C-style interface (PXCUPipeline):

- **PXCU_Capture** - Video capture (RGB, depth, blobs, ir)
- **PXCU_Faces** - Face location and landmark tracking
- **PXCU_Hands** - Hand and Fingertip detection
- **PXCU_PointCloud (untested as of 06.09)** - Point cloud rendering using VBOs
	- Requires [ofxUI](https://github.com/rezaali/ofxUI) and ofxXmlSettings
- **PXCU_Voice** - Speech Recognition example for Dictation and Command&Control modes
	- This example uses the C++ UtilPipeline as opposed to C PXCUPipeline

## C-Style Interface

- Add the directories `$(PCSDK_DIR)\include`, `$(PCSDK_DIR)\sample\common\include` and `$(PCSDK_DIR)\framework\common\pxcupipeline\include` to your include directories

- Add the directories `$(PCSDK_DIR)\lib\win32` and `$(PCSDK_DIR)\framework\common\lib\win32` to your library directories

- Include the `pxcupipeline.h` header
in `$(PCSDK_DIR)\fra
- Add `pxcupipeline.cpp` to your project's source files, found mework\common\pxcupipeline\src`

- Add the following .cpp files from `$(PCSDK_DIR)\sample\common\src` to your project:

	- `util_capture.cpp`
	- `util_capture_file.cpp`
	- `util_captureimpl.cpp`
	- `util_pipeline_face.cpp`
	- `util_pipeline_gesture.cpp`
	- `util_pipeline_raw.cpp`
	- `util_pipeline_voice.cpp`

- Add `libpxc_d.lib` and `ipppxcu_l.lib` as library inputs for Debug

- Add `libpxc.lib` and `ipppxcu_l.lib` as library inputs for Release

## Blame

Questions, Comments, Diatribes, or specific samples you'd like to see? Email [Seth](mailto:seth.gibson1@gmail.com)