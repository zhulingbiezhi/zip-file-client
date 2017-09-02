@echo off
echo.[Translate zh_CN] ......
lupdate -no-obsolete -pro html5Player.pro -ts html5Player_zh_CN.ts
lrelease html5Player_zh_CN.ts

echo.[Copy Files] ......
copy html5Player_zh_CN.qm ..\..\players /B /Y


echo.[Delete Files] ......
	del html5Player_zh_CN.qm
pause