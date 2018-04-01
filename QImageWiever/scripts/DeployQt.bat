@echo off
color 02
echo.
echo Deploying program ...
echo.
C:\Qt\5.10.1\msvc2017_64\bin\windeployqt.exe %CD%\%~n1.exe
echo.
echo Deploying complete!
echo.
::pause
exit