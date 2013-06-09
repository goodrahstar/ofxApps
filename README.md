<b>openFrameworks apps from the [Perceptual Computing Lab](http://about.me/intelperceptual)</b><br/>
<b>Download the [Perceptual Computing SDK](http://software.intel.com/en-us/vcsource/tools/perceptual-computing-sdk)</b><br/>
<b>Download [openFrameworks](http://openframeworks.cc)</b><br/>
<br/>
Sync this repo into your <b>$(OFX_ROOT)/apps</b> folder so you end up with something like:<br/>
<b>of_v0.7.4_vs2010_release/apps/ofxApps</b><br/>
<br/>
Samples using the C-style interface (PXCUPipeline):
<ul>
<li><b>PXCU_Capture</b> - Video capture using the C-interface (pxcupipeline)</li>
<li><b>PXCU_Faces</b> - Face location and landmark tracking using the C-interface (pxcupipeline)</li>
<li><b>PXCU_Hands</b> - Hand and Fingertip using the C-interface (pxcupipeline)</li>
<li><b>PXCU_PointCloud (untested as of 06.09)</b> - Point cloud rendering using VBOs</li>
<ul>
<li>Requires <a href="https://github.com/rezaali/ofxUI">ofxUI</a> and ofxXmlSettings</li>
</ul>
</ul>
To use the C-style interface in an ofx project:
<ul>
<li>Add the directories <b>$(PCSDK_DIR)\include</b>, <b>$(PCSDK_DIR)\sample\common\include</b> and <b>$(PCSDK_DIR)\framework\common\pxcupipeline\include</b> to your include directories</li>
<li>Add the directories <b>$(PCSDK_DIR)\lib\win32</b> and <b>$(PCSDK_DIR)\framework\common\lib\win32</b> to your library directories</li>
<li>Include the <b>pxcupipeline.h</b> header</li>
<li>Add <b>pxcupipeline.cpp</b> to your project's source files, found in <b>$(PCSDK_DIR)\framework\common\pxcupipeline\src</b>
<li>Add the following .cpp files from <b>$(PCSDK_DIR)\sample\common\src</b> to your project:
<ul>
<li>util_capture.cpp</li>
<li>util_capture_file.cpp</li>
<li>util_captureimpl.cpp</li>
<li>util_pipeline_face.cpp</li>
<li>util_pipeline_gesture.cpp</li>
<li>util_pipeline_raw.cpp</li>
<li>util_pipeline_voice.cpp</li>
</ul>
<li>Add <b>libpxc_d.lib</b> and <b>ipppxcu_l.lib</b> as library inputs for Debug</li>
<li>Add <b>libpxc.lib</b> and <b>ipppxcu_l.lib</b> as library inputs for Release</li>
</ul>
Questions, Comments, Diatribes, or specific samples you'd like to see? Email [Seth](mailto:seth.gibson1@gmail.com)
