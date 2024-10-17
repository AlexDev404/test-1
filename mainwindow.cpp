#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

QString product = "";
int price = 0;
int qty = 0;
double total = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Calculate the total
void calcTotal(Ui::MainWindow *ui){
    // Calculate the total
    total = price * qty;
    // Reflect this on the UI (frontend)
    ui->total->setValue(total);
}

// Save File
void saveFile(QString fileName){
    // Logic for saving files
    // Check if a valid filename was chosen
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            // Create a new JSONObject
            QJsonObject data;
            data["item"] = product;
            data["price"] = price;
            data["qty"] = qty;
            data["total"] = total;

            // Write the file as-is (cast+write)
            file.write(QJsonDocument(data).toJson(QJsonDocument::Compact));
            file.close(); // Close the file handle (hoping it wrote)
        } else {
            qDebug() << "[saveFile] Unable to open file for writing.";
        }
    }
}


// Our hero `openFile` has returned to save the day once more!
void openFile(Ui::MainWindow *ui, QString fileName){
    // Open up a file picker to read some JSON
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "[openFile]: Could not open file!";
        return;
    }
    QTextStream in(&file);
    QString raw = in.readAll(); // Read in the raw data and save it
    file.close(); // Dispose of the file

    QJsonDocument json = QJsonDocument::fromJson(raw.toUtf8());
    QJsonObject data = json.object();

    // Restore our data
    // Set values
    product = data["item"].toString();
    price = data["price"].toInt();
    qty = data["qty"].toInt();

    // Reflect this on the frontend
    ui->item->setText(product);
    ui->price->setValue(price);
    ui->qty->setValue(qty);
    calcTotal(ui); // We don't want to shame ourselves by giving
                   // a wrong total
}


// Random stuff
// Mostly single-statements
void MainWindow::on_item_editingFinished()
{
    product = ui->item->text();
}


void MainWindow::on_price_editingFinished()
{
    price = ui->price->value();
    calcTotal(ui); // Run some quick maths
}


void MainWindow::on_qty_editingFinished()
{
    qty = ui->qty->value();
    calcTotal(ui); // Run some quick maths
}


void MainWindow::on_total_editingFinished()
{
    total = ui->total->value();
    // We don't do quick maths here
}


// Opening the file
void MainWindow::on_actionOpen_From_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "",
        "JSON/Text Files (*.json; *.txt)");
    openFile(ui, fileName);
}


void MainWindow::on_actionSave_To_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save File",
        "",
        "JSON/Text Files (*.json; *.txt)");
    saveFile(fileName);
}


void MainWindow::on_actionExit_triggered()
{
    int result = QMessageBox::question(
        this,
        "Confirmation",
        "Are you sure you want to exit?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No // Default button
        );

    if (result == QMessageBox::Yes) {
        QApplication::quit(); // Exit out
    }

}


void MainWindow::on_submit_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save File",
        "",
        "JSON/Text Files (*.json; *.txt)");
    saveFile(fileName);
}


void MainWindow::on_cancel_clicked()
{
    int result = QMessageBox::question(
        this,
        "Confirmation",
        "Are you sure you want to exit?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No // Default button
        );

    if (result == QMessageBox::Yes) {
        QApplication::quit(); // Exit out
    }

}


void MainWindow::on_actionExit_No_confirmation_triggered()
{
    QApplication::quit(); // Exit out
}


void MainWindow::on_actionClear_Form_triggered()
{
    // Reset to initial values
    product = "";
    price = 0;
    qty = 0;
    total = 0;
    // Clear the form
    ui->item->setText("");
    ui->price->setValue(0);
    ui->qty->setValue(0);
    ui->total->setValue(0);
}

