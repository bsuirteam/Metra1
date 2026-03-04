#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QtMath>
#include <QTextStream>
#include <QTableWidget>
#include <QMap>
#include <QFont>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString _fileName;
    int _n_1 = 0;
    int _n_2 = 0;
    int _N_1 = 0;
    int _N_2 = 0;

    void SetText();
    void SetHolsted();
    void SetTableOperators(const QMap<QString, int>& operators);
    void SetTableOperands(const QMap<QString, int>& operands);
    void SaveTable(QTableWidget *table, const QString &filePath);

public slots:
    void OpenFileSlot();
    void RefreshSlot();
    void SaveTablesSlot();
};
#endif // MAINWINDOW_H
