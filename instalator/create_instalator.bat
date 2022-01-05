rd /S /Q .\program
mkdir .\program
cd program
xcopy /s .\..\..\bin\release\NamesFinder.exe .
xcopy /e /i /y /s .\..\..\data .\data
c:\Qt\6.2.2\msvc2019_64\bin\windeployqt.exe NamesFinder.exe