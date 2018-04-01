#include "appcore.h"

#include <quazip5/JlCompress.h>

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
