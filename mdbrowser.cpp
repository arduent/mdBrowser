#include "mdbrowser.h"
#include "ui_mdbrowser.h"

#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QModelIndex>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QUuid>
#include <QProcess>

mdBrowser::mdBrowser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mdBrowser)
{
    ui->setupUi(this);

    /* Setup filesystem model */
    model.setIconProvider(&iconProvider);
    model.setFilter( QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot)  ;

    /* Add filter for MD files */
    QStringList filters;
    filters << "*.md";
    model.setNameFilters(filters);
    model.setNameFilterDisables(false);

    /* set the path to the current path,
     * so you can launch from console and it will load the pwd
     */
    QString path = QDir::currentPath();
    model.setRootPath(path);
    ui->tree->setModel(&model);
    QModelIndex index=model.index(path);
    ui->tree->expand(index);
    ui->tree->scrollTo(index);

    ui->tree->setColumnWidth(0, 300);

    /* add some HTML to webview */
    ui->webEngineView->setHtml("<h1>mdBrowser</h1>");


}

mdBrowser::~mdBrowser()
{
    delete ui;
}


void mdBrowser::on_tree_clicked(const QModelIndex &index)
{
    /* get the currently selected file and convert if it's an MD file */
    QString selPath = model.filePath(index);
    QFileInfo ff = QFileInfo(selPath);
    if (ff.isFile() && (ff.completeSuffix().toLower()=="md"))
    {
        /* use uuid to generate a temporary file */
        QUuid uuid = QUuid::createUuid();
        QString tmpFile = QDir::toNativeSeparators(QDir::tempPath() + "/" + qApp->applicationName().replace(" ", "") + "_" + uuid.toString(QUuid::WithoutBraces) + ".html");

        /* set up the pandoc command and run it
         * pandoc demands a TITLE so we make a bogus one then remove it later
        */
        QProcess process;
        QString cmd = "pandoc";
        QStringList arguments;
        arguments << selPath;
        arguments << "--metadata" << "title='REMOVETITLE'";
        arguments << "-f" << "markdown";
        arguments << "-t" << "html";
        arguments << "-s";
        arguments << "-o" << tmpFile;
        process.start(cmd, arguments);
        process.waitForFinished();
        process.close();


        QFile f(tmpFile);
        if (f.open(QFile::ReadOnly | QFile::Text))
        {
            /* read the html file into a string */
            QTextStream in(&f);
            QString md = in.readAll();

            /* remove the bogus title */
            md.replace("<header id=\"title-block-header\">","");
            md.replace("<h1 class=\"title\">'REMOVETITLE'</h1>","");
            md.replace("</header>","");
            md.replace("'REPLACETITLE'","");

            /* show it in the webview */
            ui->webEngineView->setHtml(md);
        }
        /* delete the temporary file
         * if the f.open don't work for some reason then this might make bad things happen
        */
        //f.remove();
    }
}
