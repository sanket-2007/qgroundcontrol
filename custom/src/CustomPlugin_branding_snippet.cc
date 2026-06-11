// Paste/merge these functions into custom/src/CustomPlugin.cc.
// If functions with the same names already exist, replace their bodies only.
// QGC versions differ, so keep the function signatures already present in your CustomPlugin.cc.

QString CustomPlugin::brandImageIndoor(void) const
{
    return QStringLiteral("/custom/res/Images/protthapan-logo-catalog-transparent.png");
}

QString CustomPlugin::brandImageOutdoor(void) const
{
    return QStringLiteral("/custom/res/Images/protthapan-logo-catalog-transparent.png");
}

QString CustomPlugin::appName(void) const
{
    return QStringLiteral("Protthapan Technologies");
}

QString CustomPlugin::companyName(void) const
{
    return QStringLiteral("Protthapan Technologies Pvt. Ltd.");
}

// If your branch does not have appName/companyName methods, do not add them blindly.
// Instead, change the application display name in CMake/App metadata and keep only brandImageIndoor/Outdoor here.
