# YDColorizer

YDWE的颜色插件代码

本代码是visual studio 2017 RC写的，语言是c++，环境是win7 64位 SP1 旗舰版，使用win10的SDK（好像是版本号比较高的SDK）。

先生成lualib，debug模式生成lualib就用debug的模式生成lua。

生成lua子项目时注意改变生成路径，否则会生成到D盘。复制XXXX.DLl这个文件同样覆盖YDWE目录的某同名的DLL。

在lua里有一个XXXX.lua，这个文件覆盖YDWE目录的同样名字的lua。

覆盖路径自己搜索。

有一个debug_test模式，不可以直接启动调试，先用dll覆盖YDWE目录下的DLL后，然后打开YDWE，待启动后（只有图片是第一段，不可以调试，当显示图片和“功能异常YD的WE”时候即可），然后可以设置断点调试。其实就是附加进程，YDWE有两段，第一段是引导，并没有启动DLL，只有第二段才启动了dll，所以通常的方法无法调试DLL。
