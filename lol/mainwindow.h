#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QIcon>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    QStringList find_champions(QString &role);

    void on_pushButton_search_clicked();

    void on_pushButton_add_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_remove_doubleClicked(const QModelIndex &index);

    void on_pushButton_refresh_clicked();

    void on_comboBox_top_activated(const QString &arg1);

    void on_comboBox_jungle_activated(const QString &arg1);

    void on_comboBox_mid_activated(const QString &arg1);

    void on_comboBox_bot_activated(const QString &arg1);

    void on_comboBox_support_activated(const QString &arg1);


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
