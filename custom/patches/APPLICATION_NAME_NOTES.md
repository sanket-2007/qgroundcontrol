# Application name change notes

Search the QGC source for the display name value:

```powershell
Ctrl + Shift + F -> QGroundControl
```

Change only display/app-name entries to:

```text
Protthapan Technologies
```

Do not blindly replace every `QGroundControl` string because many internal class names,
QML imports, folders, and C++ identifiers must remain unchanged.

Common places to check depending on QGC version:

- `CMakeLists.txt`
- `custom/CMakeLists.txt`
- deployment metadata files
- Windows installer metadata
- Android/iOS metadata if building mobile

If your QGC branch supports `CustomPlugin::appName()`, use the branding snippet.
If it does not, only modify the CMake/app metadata values.
