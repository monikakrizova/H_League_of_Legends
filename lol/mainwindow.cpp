#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("../LOLdb.db");

    if (!mydb.open())
    {
        qDebug()<<"Databazi se nepodařilo otevřít"<< "\n";
    }
    else
    {
        qDebug()<<"Databáze byla otevřena"<< "\n";
    }

    QPixmap image(":/img/logolol");
    ui->label_pic->setPixmap(image);
    ui->pic_top->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
    ui->pic_jungle->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
    ui->pic_mid->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
    ui->pic_support->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
    ui->pic_bot->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));

    //

    ui->comboBox_top->clear();
    ui->comboBox_top->addItem("---");
    QString top = "top";
    ui->comboBox_top->addItems(find_champions(top));

    ui->comboBox_jungle->clear();
    ui->comboBox_jungle->addItem("---");
    QString jungle = "jungle";
    ui->comboBox_jungle->addItems(find_champions(jungle));

    ui->comboBox_mid->clear();
    ui->comboBox_mid->addItem("---");
    QString mid = "mid";
    ui->comboBox_mid->addItems(find_champions(mid));

    ui->comboBox_support->clear();
    ui->comboBox_support->addItem("---");
    QString support = "support";
    ui->comboBox_support->addItems(find_champions(support));

    ui->comboBox_bot->clear();
    ui->comboBox_bot->addItem("---");
    QString bot = "bot";
    ui->comboBox_bot->addItems(find_champions(bot));

}


MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::find_champions(QString &role)
{
    QSqlQuery *qry = new QSqlQuery;
    qry->prepare("SELECT champion FROM Champions JOIN Roles ON Champions.role_id = Roles.role_id JOIN Classes ON Classes.class_id = Champions.class_id WHERE role = '"+role+"'");
    qry->exec();
    QStringList list;
    while (qry->next()) {
        QString abc=qry->value(0).toString();
        list.append(abc);
    }
    return list;
}

//vyhledavani
void MainWindow::on_pushButton_search_clicked()
{
    //zobrazi vsechny postavy
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery();
    qry->prepare("SELECT champion FROM Champions");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);

    //vyhledavani
    QString champselect = "SELECT champion FROM Champions JOIN Roles ON Champions.role_id = Roles.role_id JOIN Classes ON Classes.class_id = Champions.class_id ";
    QSqlQueryModel* mdl = new QSqlQueryModel();

    //role
    if (ui->CB_top->isChecked()) {
        champselect += "WHERE role = 'top'";
    }

    if (ui->CB_jungle->isChecked()) {
        champselect += "WHERE role = 'jungle'";
    }

    if (ui->CB_mid->isChecked()) {
        champselect += "WHERE role = 'mid'";
    }

    if (ui->CB_bot->isChecked()) {
        champselect += "WHERE role = 'bot'";
    }

    if (ui->CB_support->isChecked()) {
        champselect += "WHERE role = 'support'";
    }

    //class
    if (ui->CB_mage->isChecked()) {
        champselect += "AND class = 'mage'";
    }

    if (ui->CB_tank->isChecked()) {
        champselect += "AND class = 'tank'";
    }

    if (ui->CB_slayer->isChecked()) {
        champselect += "AND class = 'slayer'";
    }

    if (ui->CB_fighter->isChecked()) {
        champselect += "AND class = 'fighter'";
    }

    if (ui->CB_marksman->isChecked()) {
        champselect += "AND class = 'marksman'";
    }

    if (ui->CB_controller->isChecked()) {
        champselect += "AND class = 'controller'";
    }

    if (ui->CB_specialist->isChecked()) {
        champselect += "AND class = 'speciallist'";
    }

    //attribute
    if (ui->CB_melee->isChecked()) {
        champselect += "AND adv_attributes = 'melee'";
    }

    if (ui->CB_ranged->isChecked()) {
        champselect += "AND adv_attributes = 'ranged'";
    }


    if (ui->CB_min_winrate->isChecked()) {
        QString wr = ui->min_winrate->text();
        champselect += "AND win_rate > '"+wr+"'";
    }

    QSqlQuery* query = new QSqlQuery();
    query->prepare(champselect);
    query->exec();
    mdl->setQuery(*query);
    ui->tableView->setModel(mdl);

}


//po kliknuti na nazev postavy zobrazim jeji jmeno a obrazek
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT champion FROM Champions WHERE champion ='"+val+"'");
    qry.exec();

    QPixmap image(":/img/"+val+"");
    ui->label_pic->setPixmap(image);
    ui->label_pic->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));

    while(qry.next()) {
        ui->label_champname->setText(qry.value(0).toString());
    }

}


//pridavani postav
void MainWindow::on_pushButton_add_clicked()
{
    QString newName = ui->lineEdit_addname->text();
    QString newRole;
    QString newClass;
    QString newWR=ui->lineEdit_winrate->text();
    QString newAtr;

    //role
    if (ui->RB_top->isChecked()) {
        newRole = "1";
    }

    if (ui->RB_jungle->isChecked()) {
        newRole = "2";
    }

    if (ui->RB_mid->isChecked()) {
        newRole = "3";
    }

    if (ui->RB_bot->isChecked()) {
        newRole = "4";
    }

    if (ui->RB_support->isChecked()) {
        newRole = "5";
    }

    //class
    if (ui->RB_controller->isChecked()) {
        newClass = "1";
    }

    if (ui->RB_fighter->isChecked()) {
        newClass = "2";
    }

    if (ui->RB_mage->isChecked()) {
        newClass = "3";
    }

    if (ui->RB_marksman->isChecked()) {
        newClass = "4";
    }

    if (ui->RB_slayer->isChecked()) {
        newClass = "5";
    }

    if (ui->RB_tank->isChecked()) {
        newClass = "6";
    }

    if (ui->RB_specialist->isChecked()) {
        newClass = "7";
    }

    // Atributes
    if (ui->RB_melee ->isChecked()) {
        newAtr = "melee";
    }
    if (ui->RB_ranged ->isChecked()) {
        newAtr = "ranged";
    }

    QSqlQuery *pr = new QSqlQuery;
    QString max_id_select="SELECT max(champ_id)+1 FROM Champions";
    pr->prepare(max_id_select);
    pr->exec();
    pr->first();
    QString max_id=pr->value(0).toString();

    QSqlQuery q;
    q.exec("INSERT INTO Champions VALUES ('"+newName+"', '"+max_id+"', '"+newAtr+"', '"+newRole+"', '"+newClass+"', '"+newWR+"')");

    ui->lineEdit_addname->clear();
    ui->lineEdit_winrate->clear();

}


//odststranovani postav s nutnosti potvrzeni akce
void MainWindow::on_tableView_remove_doubleClicked(const QModelIndex &index)
{
    QMessageBox msgBox;
    msgBox.setText(tr("Are you sure you want to remove this champion from database?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Ok"), QMessageBox::YesRole);
    msgBox.addButton(tr("Cancel"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {

        QString val = ui->tableView_remove->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("DELETE FROM Champions WHERE champion ='"+val+"'");
        qry.exec();
    }
    else {
        msgBox.close();
    }
}


void MainWindow::on_pushButton_refresh_clicked()
{
    QSqlQueryModel* modelrefresh= new QSqlQueryModel();
    QSqlQuery* qry2 = new QSqlQuery();
    qry2->prepare("SELECT champion FROM Champions");
    qry2->exec();
    modelrefresh->setQuery(*qry2);
    ui->tableView_remove->setModel(modelrefresh);
}


//grafika tvorba tymu
void MainWindow::on_comboBox_top_activated(const QString &arg1)
{
    QSqlQuery qry;
    qry.prepare("SELECT champion FROM Champions WHERE champion ='"+arg1+"'");
    qry.exec();

    QPixmap image(":/img/"+arg1+"");
    ui->pic_top->setPixmap(image);
    ui->pic_top->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
}

void MainWindow::on_comboBox_jungle_activated(const QString &arg1)
{
    QSqlQuery qry;
    qry.prepare("SELECT champion FROM Champions WHERE champion ='"+arg1+"'");
    qry.exec();

    QPixmap image(":/img/"+arg1+"");
    ui->pic_jungle->setPixmap(image);
    ui->pic_jungle->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
}

void MainWindow::on_comboBox_mid_activated(const QString &arg1)
{
    QSqlQuery qry;
    qry.prepare("SELECT champion FROM Champions WHERE champion ='"+arg1+"'");
    qry.exec();

    QPixmap image(":/img/"+arg1+"");
    ui->pic_mid->setPixmap(image);
    ui->pic_mid->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
}

void MainWindow::on_comboBox_bot_activated(const QString &arg1)
{
    QSqlQuery qry;
    qry.prepare("SELECT champion FROM Champions WHERE champion ='"+arg1+"'");
    qry.exec();

    QPixmap image(":/img/"+arg1+"");
    ui->pic_bot->setPixmap(image);
    ui->pic_bot->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
}

void MainWindow::on_comboBox_support_activated(const QString &arg1)
{
    QSqlQuery qry;
    qry.prepare("SELECT champion FROM Champions WHERE champion ='"+arg1+"'");
    qry.exec();

    QPixmap image(":/img/"+arg1+"");
    ui->pic_support->setPixmap(image);
    ui->pic_support->setPixmap(image.scaled(80,80,Qt::KeepAspectRatio));
}



void MainWindow::on_pushButton_clicked()
{
    QString top = ui->comboBox_top->currentText();
    QSqlQuery qry;
    qry.prepare("SELECT Champions.win_rate FROM Champions WHERE champion = '"+top+"'");
    qry.exec();
    qry.next();
    double a = qry.value(0).toDouble();

    QString jungle = ui->comboBox_jungle->currentText();
    QSqlQuery qry_jungle;
    qry_jungle.prepare("SELECT Champions.win_rate FROM Champions WHERE champion = '"+jungle+"'");
    qry_jungle.exec();
    qry_jungle.next();
    double b = qry_jungle.value(0).toDouble();

    QString mid = ui->comboBox_mid->currentText();
    QSqlQuery qry_mid;
    qry_mid.prepare("SELECT Champions.win_rate FROM Champions WHERE champion = '"+mid+"'");
    qry_mid.exec();
    qry_mid.next();
    double c = qry_mid.value(0).toDouble();

    QString support = ui->comboBox_support->currentText();
    QSqlQuery qry_support;
    qry_support.prepare("SELECT Champions.win_rate FROM Champions WHERE champion = '"+support+"'");
    qry_support.exec();
    qry_support.next();
    double d = qry_support.value(0).toDouble();

    QString bot = ui->comboBox_bot->currentText();
    QSqlQuery qry_bot;
    qry_bot.prepare("SELECT Champions.win_rate FROM Champions WHERE champion = '"+bot+"'");
    qry_bot.exec();
    qry_bot.next();
    double e = qry_bot.value(0).toDouble();

    double mean = (a+b+c+d+e)/5;
    QString mean_str = QString::number(mean);
    ui->lineEdit_winrate_2->setText(mean_str);
}
