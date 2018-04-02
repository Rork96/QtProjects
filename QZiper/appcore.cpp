#include "appcore.h"

#include "quazip-Qt5/quazip/JlCompress.h"

AppCore::AppCore(QObject *parent) :
        BaseClass(parent)
{
}

void AppCore::compress(QString File, QString Dir)
{
    /* * * Receive data from qml * * */
    /* * * Compress dir * * */

    if (!Dir.isEmpty()) {
        //JlCompress::compressDir(File, Dir);
    }
}
