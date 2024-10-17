#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_item_editingFinished();

    void on_price_editingFinished();

    void on_qty_editingFinished();

    void on_total_editingFinished();

    void on_actionOpen_From_triggered();

    void on_actionSave_To_triggered();

    void on_actionExit_triggered();

    void on_submit_clicked();

    void on_cancel_clicked();

    void on_actionExit_No_confirmation_triggered();

    void on_actionClear_Form_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
