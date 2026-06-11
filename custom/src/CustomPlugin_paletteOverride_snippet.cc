// Paste/merge this inside custom/src/CustomPlugin.cc.
// If CustomPlugin::paletteOverride already exists, replace only its body.
// Do not create a duplicate paletteOverride function.

void CustomPlugin::paletteOverride(const QString& colorName, QGCPalette::PaletteColorInfo_t& colorInfo)
{
    const QColor bgDark("#050A07");
    const QColor panelDark("#0E1A12");
    const QColor panelShade("#13261B");
    const QColor accentGreen("#00FF88");
    const QColor accentCyan("#00D4FF");
    const QColor textMain("#D8FFE6");
    const QColor textDisabled("#6F7F72");
    const QColor amber("#FFB000");
    const QColor dangerRed("#FF2E2E");

    if (colorName == QStringLiteral("window")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = bgDark;
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled] = panelDark;
    } else if (colorName == QStringLiteral("windowShade")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = panelDark;
        colorInfo[QGCPalette::Light][QGCPalette::ColorGroupEnabled] = panelShade;
    } else if (colorName == QStringLiteral("text")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = textMain;
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupDisabled] = textDisabled;
    } else if (colorName == QStringLiteral("button")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = panelShade;
    } else if (colorName == QStringLiteral("buttonText")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = textMain;
    } else if (colorName == QStringLiteral("buttonHighlight")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = accentGreen;
    } else if (colorName == QStringLiteral("primaryButton")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = accentGreen;
    } else if (colorName == QStringLiteral("primaryButtonText")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = QColor("#041008");
    } else if (colorName == QStringLiteral("warningText")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = amber;
    } else if (colorName == QStringLiteral("colorRed")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = dangerRed;
    } else if (colorName == QStringLiteral("colorGreen")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = accentGreen;
    } else if (colorName == QStringLiteral("colorBlue")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = accentCyan;
    } else if (colorName == QStringLiteral("mapIndicator")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = QColor("#1FFF9A");
    } else if (colorName == QStringLiteral("mapButton")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = QColor("#07130C");
    } else if (colorName == QStringLiteral("mapButtonHighlight")) {
        colorInfo[QGCPalette::Dark][QGCPalette::ColorGroupEnabled] = accentGreen;
    }
}
