@echo off
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=2& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/win32-specific/gles/prebuilt/glew32.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=3& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=4& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/win32-specific/OggDecoder/prebuilt/libogg.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=5& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=6& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/win32-specific/OggDecoder/prebuilt/libvorbis.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=7& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=8& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/win32-specific/OggDecoder/prebuilt/libvorbisfile.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=9& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=10& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/win32-specific/MP3Decoder/prebuilt/libmpg123.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=11& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=12& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/win32-specific/OpenalSoft/prebuilt/OpenAL32.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=13& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=14& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/sqlite3/libraries/win32/sqlite3.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=15& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=16& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/win32-specific/zlib/prebuilt/zlib1.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=17& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=18& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/websockets/prebuilt/win32/websockets.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=19& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=20& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/curl/prebuilt/win32/libcurl.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=21& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=22& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/openssl/prebuilt/win32/libcrypto-1_1.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=23& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=24& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different D:/GameProject/MyGame/cocos2d/external/openssl/prebuilt/win32/libssl-1_1.dll D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=25& goto :ABORT)
cd /D D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=26& goto :ABORT)
"D:\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_directory D:/GameProject/MyGame/Resources D:/GameProject/MyGame/out/build/x64-Debug/bin/TemplateCpp/Debug || (set FAIL_LINE=27& goto :ABORT)
cd D:\GameProject\MyGame\out\build\x64-Debug || (set FAIL_LINE=28& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%