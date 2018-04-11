#include <QCoreApplication>
#include <QDebug>
#include <QArchive>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    /*
     * 1.Construct
    */
    QArchive::Reader e("test.7z");


    /*
     * 2.Connect Callbacks
    */

    QObject::connect(&e, &QArchive::Reader::archiveFiles, [&](QString archive, QStringList files) {
        qDebug() << archive << " :: ";
        qDebug() << files;
        app.quit();
    });

    // emitted when something goes wrong
    QObject::connect(&e, &QArchive::Reader::error, [&](short code, QString file) {
        switch(code) {
        case QArchive::ARCHIVE_READ_ERROR:
            qDebug() << "unable to find archive :: " << file;
            app.quit();
            break;
        case QArchive::ARCHIVE_QUALITY_ERROR:
            qDebug() << "bad archive! :: " << file;
            app.quit();
            break;
        case QArchive::ARCHIVE_UNCAUGHT_ERROR:
            qDebug() << "fatal error. :: " << file;
            app.quit();
            break;
        default:
            qDebug() << "unknown error. :: " << file;
            app.quit();
            break;
        }
    });

    /*
     * 3.Start extraction!
    */
    e.start();
    return app.exec();
}
