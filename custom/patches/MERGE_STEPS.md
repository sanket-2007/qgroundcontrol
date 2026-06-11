# Protthapan Technologies QGC Custom Build - Merge Steps

These files are ready to paste into your QGroundControl `custom` folder.
The logo was extracted from the provided Protthapan product catalog.

## 1. Correct folder

After copying, your structure should be:

```text
qgroundcontrol/
  custom/
    custom.qrc
    res/Images/protthapan-logo-catalog.png
    res/Images/protthapan-logo-catalog-transparent.png
    res/Images/protthapan-logo-toolbar.png
    res/Images/splash.png
    src/FlyViewCustomLayer.qml
    src/ProtthapanSettings.qml
    src/ProtthapanMapToolbarOverlay.qml
    src/CustomPlugin_paletteOverride_snippet.cc
    src/CustomPlugin_branding_snippet.cc
```

Do not create `qgroundcontrol/custom/custom/`.

## 2. Merge theme colors

Open:

```text
custom/src/CustomPlugin_paletteOverride_snippet.cc
```

Copy the function body into:

```text
custom/src/CustomPlugin.cc
```

Search for:

```cpp
paletteOverride
```

If it already exists, replace only its body. Do not create a duplicate function.

## 3. Merge logo/branding

Open:

```text
custom/src/CustomPlugin_branding_snippet.cc
```

Copy/replace the functions in:

```text
custom/src/CustomPlugin.cc
```

Main functions:

```cpp
brandImageIndoor()
brandImageOutdoor()
```

Only add `appName()` / `companyName()` if your QGC branch already supports those methods.
Otherwise, change the application name in CMake/app metadata.

## 4. Application name

Set display name to:

```text
Protthapan Technologies
```

Use VS Code search:

```text
Ctrl + Shift + F -> QGroundControl
```

Change only display/app-name entries. Do not blindly replace all internal `QGroundControl` text.

## 5. Fly View overlay

`FlyViewCustomLayer.qml` is included. If your custom-example already has one,
replace it with the included file.

This creates a futuristic tactical map overlay with:

- Protthapan logo at top
- map operations panel
- radar-style map-lock indicator
- dark green/cyan military-style UI

## 6. Splash/logo files

Images are already registered in `custom.qrc`:

- `protthapan-logo-catalog.png`
- `protthapan-logo-catalog-transparent.png`
- `protthapan-logo-toolbar.png`
- `splash.png`
- `app-icon.png`
- `app-icon.ico`

If your branch uses an auto-generated resource list, run the branch's resource update step.
Some QGC branches use scripts like `updateqrc.py`; follow your branch's custom-build README.

## 7. Toolbar items

For a stable first version, this package does not fully replace `MainToolBar.qml`
because that file changes across QGC versions. Instead, it provides:

```text
src/ProtthapanMapToolbarOverlay.qml
```

Use it as a reference or overlay if you later override the toolbar.
Recommended toolbar items:

- Protthapan logo
- Connect/Disconnect
- Map/Fly view
- Mode
- Arm status
- GPS
- Battery
- Telemetry link
- RTL/Land

## 8. Build order

1. Build normal QGC once successfully.
2. Copy these files into `qgroundcontrol/custom`.
3. Merge snippets into `CustomPlugin.cc`.
4. Change app display name.
5. Build again.
