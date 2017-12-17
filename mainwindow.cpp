#include "mainwindow.h"
#include "qtextstream"
#include "patterns/adapter.h"

QString* MainWindow::_console_text = new QString;

QDebug MainWindow::qout = QDebug(_console_text);

const QString MainWindow::NOT_SELECTED("NOT_SELECTED");
const QString MainWindow::ADAPTER("Adapter");
const QString MainWindow::BRIDGE("Bridge");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FullMainWindow)
{
    ui->setupUi(this);
    //writing code
    initializeMapFromHiddenTextBrowsers();

    MainWindow::qout.setAutoInsertSpaces(true);
    ui->tBrowser_Console->clear();
    ui->tBrowser_Problem->clear();
    //Hiding the texte database
    ui->tBrowser_AdapterProblem->hide();
    ui->tBrowser_AdapterSolution->hide();
    ui->tBrowser_BridgeData->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeMapFromHiddenTextBrowsers()
{
    _pattern_name_to_text[MainWindow::NOT_SELECTED] = TextData(QString("No design pattern selected"), QString("No design pattern selected"));
    _pattern_name_to_text[MainWindow::ADAPTER] = TextData(ui->tBrowser_AdapterProblem->toHtml(),ui->tBrowser_AdapterSolution->toHtml());
    _pattern_name_to_text[MainWindow::BRIDGE] = TextData(ui->tBrowser_BridgeData->toHtml(),QString("Solution comming soon"));
}
void MainWindow::on_pushButton_clicked()
{
    if (_current_combobox_elt == MainWindow::ADAPTER)
    {
        MainWindow::qout<<"Adapter example output :"<<endl;
        MainWindow::qout<<"******************************"<<endl;
        Patterns::Adapter::ThingToAdaptTo api_unchangable_interface_to_adapt_to_client;
        Patterns::Adapter::ConcreteAdapter the_adapter(&api_unchangable_interface_to_adapt_to_client);
        Patterns::Adapter::Client the_client(&the_adapter);

        the_client.IAlwaysCallThisMethodButWantItToBeAdaptedExternally();
        MainWindow::qout<<"******************************"<<endl;
        update_console_text();
    }
    else if (_current_combobox_elt == MainWindow::BRIDGE)
    {
        MainWindow::qout<<"Bridge Pattern comming soon !"<<endl;
        update_console_text();
    }
    else
    {
        MainWindow::qout<<"Please choose a pattern in the patterns list!"<<endl;
        update_console_text();
    }
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    _current_combobox_elt = arg1;
    select_problem_text(_current_combobox_elt);
}

void MainWindow::select_problem_text(const QString &arg1)
{
    if (arg1 == MainWindow::ADAPTER)
    {
        update_problem_text(MainWindow::ADAPTER);
        update_solution_text(MainWindow::ADAPTER);
    }
    else if (arg1 == MainWindow::BRIDGE)
    {
        update_problem_text(MainWindow::BRIDGE);
        update_solution_text(MainWindow::BRIDGE);
    }
    else
    {
        MainWindow::qout<<"no valid pattern selected "<<endl;
        update_problem_text(MainWindow::NOT_SELECTED);
        update_solution_text(MainWindow::NOT_SELECTED);
    }

}

void MainWindow::update_console_text()
{
    ui->tBrowser_Console->clear();
    ui->tBrowser_Console->setText(*MainWindow::_console_text);
    MainWindow::_console_text->clear();
}

void MainWindow::update_problem_text(const QString& key)
{
    ui->tBrowser_Problem->clear();
    ui->tBrowser_Problem->setHtml(_pattern_name_to_text[key]._problem);
}

void MainWindow::update_solution_text(const QString& key)
{
    ui->tBrowser_Solution->clear();
    ui->tBrowser_Solution->setHtml(_pattern_name_to_text[key]._solution);
}
