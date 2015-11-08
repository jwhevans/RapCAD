#!/bin/bash
source config

Qt="qt-opensource-windows-x86-mingw492-5.5.1.exe"
QtSilent="QtSilentInstall.exe"
Zip="7z1509.exe"
Boost="boost_1_59_0.zip"
CMake="cmake-3.4.0-rc2-win32-x86.exe"
CGAL="CGAL-4.7-Setup.exe"
FlexBison="win_flex_bison-2.5.5.zip"

QtBin="c:\\Qt\\Qt5.5.1\\5.5\\mingw492_32\\bin"

./cmd.sh mklink /d c:\\shared \\\\vboxsvr\\shared
./cmd.sh copy c:\\shared\\$Qt c:\\
./cmd.sh c:\\shared\\$QtSilent c:\\$Qt
./cmd.sh del c:\\$Qt
./cmd.sh c:\\shared\\$Zip /S /D=c:\\7zip\\
./cmd.sh c:\\7zip\\7z.exe x -oc:\\ c:\\shared\\$Boost
cat << EOF > $SHAREDFOLDER/boost.bat
@echo off
call $QtBin\\qtenv2.bat
cd c:\\boost_1_59_0\\
call bootstrap.bat mingw
.\\b2 toolset=gcc variant=release --with-thread --with-system
EOF
./cmd.sh c:\\shared\\boost.bat
./cmd.sh c:\\shared\\$CMake /S /D=c:\\cmake\\
./cmd.sh c:\\shared\\$CGAL /S /D=c:\\CGAL-4.7\\
cat << EOF > $SHAREDFOLDER/cgal.bat
@echo off
call $QtBin\\qtenv2.bat
set PATH=%PATH%;"C:\\cmake\\bin"
set BOOST_ROOT=C:\\boost_1_59_0
cd "C:\\CGAL-4.7\\"
cmake -G"MinGW Makefiles" .
mingw32-make
EOF
./cmd.sh c:\\shared\\cgal.bat
./cmd.sh c:\\7zip\\7z.exe x -o$QtBin c:\\shared\\$FlexBison
./cmd.sh c:\\shared\\Git-2.6.2-32-bit.exe /SILENT /DIR=c:\\git
./cmd.sh msiexec /i c:\\shared\\python-2.7.10.msi /qn
./cmd.sh c:\\7zip\\7z.exe x -oc:\\ c:\\shared\\asciidoc-8.6.9.zip
./cmd.sh c:\\shared\\src-highlite-2.1.2.exe /SILENT /DIR=c:\\source-highlight
./cmd.sh move /Y c:\\source-highlight\\bin\\source-highlight.exe c:\\source-highlight\\bin\\source-highlight-exe.exe
cat << EOF > $SHAREDFOLDER/source-highlight.bat
@echo off
source-highlight-exe --data-dir "%~dp0\\..\\share\\source-highlight" %*
EOF
./cmd.sh copy c:\\shared\\source-highlight.bat c:\\source-highlight\\bin\\
./cmd.sh copy c:\\source-highlight\\share\\source-highlight\\lang.map c:\\shared\\
echo >> $SHAREDFOLDER\lang.map
echo "csharp = csharp.lang" >> $SHAREDFOLDER\lang.map
./cmd.sh copy c:\\shared\\lang.map c:\\source-highlight\\share\\source-highlight\\lang.map
./cmd.sh copy c:\\shared\\csharp.lang c:\\source-highlight\\share\\source-highlight\\
./cmd.sh c:\\git\\bin\\git.exe clone --depth 10 https://github.com/GilesBathgate/RapCAD.git c:\\rapcad
