#ifndef MDBROWSER_H
#define MDBROWSER_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileIconProvider>

QT_BEGIN_NAMESPACE
namespace Ui { class mdBrowser; }
QT_END_NAMESPACE

class mdBrowser : public QMainWindow
{
    Q_OBJECT

public:
    mdBrowser(QWidget *parent = nullptr);
    ~mdBrowser();

private slots:
    void on_tree_clicked(const QModelIndex &index);

private:
    Ui::mdBrowser *ui;
    QFileSystemModel model;
    QFileIconProvider iconProvider;

};
#endif // MDBROWSER_H
