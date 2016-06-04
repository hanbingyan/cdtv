# cdtv
A new algorithm for image denoising


## 简介
本算法基于 Coordinate Descent , 求解 L0-TV 图像去噪模型。L0-TV 的论文见 

<https://ivul.kaust.edu.sa/Pages/Pub-LoTv-Image-Restoration.aspx>

代码使用的是 Matlab 和 C/C++ 混合编程的方法，并行版本使用的是 Pthreads ，当然也有纯 Matlab 版本的。目前只写了用于 512*512 黑白图片的代码。由于模型对于 RGB 三层有可分性，所以可以将代码分别作用到 RGB 三层，即得彩色图片的去噪结果。代码在 Ubuntu 14.04 bit 和 Matlab 2014a 的环境下编译通过。

## 使用

在 Matlab 下面输入：

mex pcdtv.c

即可得到非并行版本的链接库，使用 U=pcdtv(lambda,B) 即可运行程序，其中 B 是损坏的图片（程序目前只支持 512*512 大小的），建议先将 B 的取值都限制到0 到 1 的范围内，这时 lambda=5 较为合适， U 是结果 。

在 Matlab 下面输入：

mex mex_pcdtv2.c -lpthread 

可以得到使用两个线程的并行版本，语法 U=mex_pcdtv2(lambda,B);

纯 Matlab 代码是 cdtv.m  使用 [U,obj]=cdtv(B,lambda); 即可，相比之下速度较慢。obj 给出了目标函数值，一共计算了 100 个。

## 文件清单

* cdtv.m   : 单进程的 Matlab 版本代码；
* pcdtv.c  : 单进程的 C 与 Matlab 混合编程代码；
* mex_pcdtv2.c : 双进程的 C 与 Matlab 混合编程代码；
* util : 包含计算离散梯度的 difX.m difY.m , 给图片加噪声的 impulsenoise.m , 计算三种信噪比的 snr_l0.m 、snr_l1.m 、snr_l2.m 。






