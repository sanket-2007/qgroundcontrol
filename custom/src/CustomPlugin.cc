#include "CustomPlugin.h"
#include "PerimeterScanComplexItem.h"
#include "PerimeterScanPlanCreator.h"
#include "QmlComponentInfo.h"
#include "QGCLoggingCategory.h"
#include "QGCPalette.h"
#include "QGCMAVLink.h"
#include "AppSettings.h"

#include <QtCore/QApplicationStatic>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlFile>
#include <QtGui/QColor>

QGC_LOGGING_CATEGORY(CustomLog, "Custom.CustomPlugin")

Q_APPLICATION_STATIC(CustomPlugin, _customPluginInstance);

CustomFlyViewOptions::CustomFlyViewOptions(CustomOptions* options, QObject* parent)
    : QGCFlyViewOptions(options, parent)
{
    qCDebug(CustomLog) << this;
}

CustomOptions::CustomOptions(CustomPlugin *plugin, QObject *parent)
    : QGCOptions(parent)
    , _plugin(plugin)
    , _flyViewOptions(new CustomFlyViewOptions(this, this))
{
    Q_CHECK_PTR(_plugin);
}

/*===========================================================================*/

CustomPlugin::CustomPlugin(QObject *parent)
    : QGCCorePlugin(parent)
    , _options(new CustomOptions(this, this))
{
    qCDebug(CustomLog) << this;

    _showAdvancedUI = false;
    (void) connect(this, &QGCCorePlugin::showAdvancedUIChanged, this, &CustomPlugin::_advancedChanged);
}

QGCCorePlugin *CustomPlugin::instance()
{
    return _customPluginInstance();
}

void CustomPlugin::cleanup()
{
    if (_qmlEngine) {
        _qmlEngine->removeUrlInterceptor(_selector);
    }

    delete _selector;
}

void CustomPlugin::_advancedChanged(bool changed)
{
    // Firmware Upgrade page is only show in Advanced mode
    emit _options->showFirmwareUpgradeChanged(changed);
}

void CustomPlugin::_addSettingsEntry(const QString &title, const char *qmlFile, const char *iconFile)
{
    Q_CHECK_PTR(qmlFile);
    // 'this' instance will take ownership on the QmlComponentInfo instance
    _customSettingsList.append(QVariant::fromValue(
        new QmlComponentInfo(
            title,
            QUrl::fromUserInput(qmlFile),
            !iconFile ? QUrl() : QUrl::fromUserInput(iconFile),
            this)
        )
    );
}

void CustomPlugin::adjustSettingMetaData(const QString& settingsGroup, FactMetaData& metaData, bool &userVisible)
{
    QGCCorePlugin::adjustSettingMetaData(settingsGroup, metaData, userVisible);

    if (settingsGroup == AppSettings::settingsGroup) {
        // This tells QGC than when you are creating Plans while not connected to a vehicle
        // the specific firmware/vehicle the plan is for.
        if (metaData.name() == AppSettings::offlineEditingFirmwareClassName) {
            metaData.setRawDefaultValue(QGCMAVLink::FirmwareClassPX4);
            userVisible = false;
            return;
        } else if (metaData.name() == AppSettings::offlineEditingVehicleClassName) {
            metaData.setRawDefaultValue(QGCMAVLink::VehicleClassMultiRotor);
            userVisible = false;
            return;
        }
    }
}

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


QQmlApplicationEngine* CustomPlugin::createQmlApplicationEngine(QObject* parent)
{
    _qmlEngine = QGCCorePlugin::createQmlApplicationEngine(parent);
    _qmlEngine->addImportPath("qrc:/qml/Custom/Widgets");
    _qmlEngine->addImportPath("qrc:/qml/Custom/Plan");
    // TODO: Investigate _qmlEngine->setExtraSelectors({"custom"})

    _selector = new CustomOverrideInterceptor();
    _qmlEngine->addUrlInterceptor(_selector);

    return _qmlEngine;
}

/*===========================================================================*/

CustomOverrideInterceptor::CustomOverrideInterceptor()
    : QQmlAbstractUrlInterceptor()
{

}

QUrl CustomOverrideInterceptor::intercept(const QUrl &url, QQmlAbstractUrlInterceptor::DataType type)
{
    switch (type) {
    case QQmlAbstractUrlInterceptor::QmlFile:
    case QQmlAbstractUrlInterceptor::UrlString:
        if (url.scheme() == QStringLiteral("qrc")) {
            const QString origPath = url.path();
            const QString overrideRes = QStringLiteral(":/Custom%1").arg(origPath);
            if (QFile::exists(overrideRes)) {
                const QString relPath = overrideRes.mid(2);
                QUrl result;
                result.setScheme(QStringLiteral("qrc"));
                result.setPath('/' + relPath);
                return result;
            }
        }
        break;
    default:
        break;
    }

    return url;
}

/*===========================================================================*/

QVariantList CustomPlugin::complexMissionItemNames(Vehicle *vehicle)
{
    // Start with the standard set, then append our custom item.
    QVariantList items = QGCCorePlugin::complexMissionItemNames(vehicle);

    QVariantMap entry;
    entry[QStringLiteral("canonicalName")]  = QString(PerimeterScanComplexItem::canonicalName);
    entry[QStringLiteral("translatedName")] = PerimeterScanComplexItem::tr(PerimeterScanComplexItem::canonicalName);
    items.append(entry);

    return items;
}

ComplexMissionItem *CustomPlugin::createComplexMissionItem(const QString &complexItemType,
                                                            PlanMasterController *masterController,
                                                            bool flyView,
                                                            const QString &kmlOrShpFile)
{
    if (complexItemType == PerimeterScanComplexItem::canonicalName
            || complexItemType == PerimeterScanComplexItem::jsonComplexItemTypeValue) {
        return new PerimeterScanComplexItem(masterController, flyView, kmlOrShpFile);
    }
    // Fall back to the built-in factory for all standard item types.
    return QGCCorePlugin::createComplexMissionItem(complexItemType, masterController, flyView, kmlOrShpFile);
}

QList<PlanCreator *> CustomPlugin::planCreators(PlanMasterController *planMasterController)
{
    // Start with the standard creators, then add ours.
    QList<PlanCreator *> creators = QGCCorePlugin::planCreators(planMasterController);
    creators.append(new PerimeterScanPlanCreator(planMasterController));
    return creators;
}

QString CustomPlugin::brandImageIndoor(void) const
{
    return QStringLiteral("/custom/res/Images/protthapan-logo-catalog.png");
}

QString CustomPlugin::brandImageOutdoor(void) const
{
    return QStringLiteral("/custom/res/Images/protthapan-logo-catalog-transparent.png");
}

