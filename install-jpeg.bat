@echo off
cd /d %~dp0
mkdir jpeg-lib
cd jpeg-lib
echo Downloading libjpeg-turbo...
curl -L https://sourceforge.net/projects/libjpeg-turbo/files/3.0.0/libjpeg-turbo-3.0.0-gcc64.exe/download -o libjpeg.exe
echo Installing...
libjpeg.exe /S /D=%CD%
echo Installation complete!