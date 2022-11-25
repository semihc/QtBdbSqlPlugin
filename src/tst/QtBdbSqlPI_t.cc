#include <iostream>
#include <gtest/gtest.h>

#include <QObject>
#include <QDir>
#include <QtPlugin>
#include <QPluginLoader>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlDriverPlugin>


using namespace std;



static QPluginLoader PluginLoader{};


bool QtBdbSqlPI_LoadPlugin(const string& piName = "qtbdbsql")
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    //-pluginsDir.cd("plugins");
    const QStringList entries = pluginsDir.entryList(QDir::Files);
    for (const QString &fileName : entries) {
        PluginLoader.setFileName(pluginsDir.absoluteFilePath(fileName));
        // Get the root object in the plugin
        QObject *plugin = PluginLoader.instance();
        if (plugin) {
            cout << "Plugin identified: " << fileName.toLatin1().data() << endl;
            // Is the root object is castable to the designated interface?
            QSqlDriverPlugin* qsdp = qobject_cast<QSqlDriverPlugin *>(plugin);
            if (qsdp) {
                cout << "Plugin with QSqlDriverPlugin: " << fileName.toLatin1().data() << endl;
                return true;
            }

            PluginLoader.unload();
        }
    }

    return false;
}


bool QtBdbSqlPI_UnloadPlugin()
{
    bool rv = PluginLoader.unload();
    return rv;
}


TEST(QtBdbSql_test, Connect)
{
    for(auto& p : QCoreApplication::libraryPaths())
        cout << p.toLatin1().data() << endl;

    //-ASSERT_TRUE(QtBdbSqlPI_LoadPlugin());
    for(auto& d : QSqlDatabase::drivers())
        cout << d.toLatin1().data() << endl;
    ASSERT_TRUE(QSqlDatabase::isDriverAvailable("QBDBSQL"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QBDBSQL");
    ASSERT_TRUE(1);
}


