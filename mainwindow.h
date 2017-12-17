#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdebug>
#include "treecombobox.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>

namespace Ui {

class FullMainWindow :public MainWindow
{
public:
    FullMainWindow()
    {}
    void setupUi(QMainWindow *MainWindow)
    {
        MainWindow::setupUi(MainWindow);
        combo_treeview = new TreeComboBox(centralWidget);
        combo_treeview->setObjectName(QStringLiteral("comboBox_treeview"));
        combo_treeview->setGeometry(QRect(1000, 30, 221, 22));
        QFileSystemModel *model = new QFileSystemModel;
        model->setRootPath(QDir::currentPath());
        combo_treeview->setModel(model);
    }
    TreeComboBox * combo_treeview;
};

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static QDebug qout; // output to console textbox //pure text

    void update_console_text();
    void update_problem_text(const QString &key);
    void update_solution_text(const QString& key);
    void select_problem_text(const QString &arg1);
    void initializeMapFromHiddenTextBrowsers();
private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::FullMainWindow *ui;
    QString _current_combobox_elt;
    static QString* _console_text;
    TreeComboBox* combo;
    class TextData
    {
    public:
        TextData()
        {}
        TextData(QString p, QString s):
            _problem(p),
            _solution(s)
        {}
        QString _problem;
        QString _solution;
    };

    typedef QMap<QString, TextData> PatternNameToText;
    PatternNameToText _pattern_name_to_text;

    static const QString NOT_SELECTED;
    static const QString ADAPTER;
    static const QString BRIDGE;
};

#endif // MAINWINDOW_H
