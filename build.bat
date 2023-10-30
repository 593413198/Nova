
cmake . -B build

"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" /p:Configuration=Release /m build\Game.vcxproj

.\build\Release\Game.exe
