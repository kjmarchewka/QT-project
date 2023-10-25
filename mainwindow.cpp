#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QDebug>
#include <QThread>
#include <QString>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
        setWindowTitle("Program okienkowy");
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::isBlf(const QVector<char> &data) {
        if (data.size() >= 4 && data[0] == 'L' && data[1] == 'O' && data[2] == 'G' && data[3] == 'G') {
            ui->checkboxik->setChecked(true);
        } else {
            ui->checkboxik->setChecked(false);
        }
        return ui->checkboxik->isChecked();
}
QString fileName;
QVector<char> MainWindow::readFile() {
        fileName = QFileDialog::getOpenFileName(this, "Wybierz plik", "", "Wszystkie pliki (*.*);;Pliki binarne (*.bin);;Pliki tekstowe (*.txt);;Pliki BLF (*.blf)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly)) {
                QByteArray data = file.readAll();
                file.close();
                container.clear();
                for (int e = 0; e < data.count(); e++) {
                    container.append(data[e]);
                }
            }
        }
    return container;
}

QString MainWindow::binchange() {
        for (char byte : container) {
            for (int i = 7; i >= 0; i--) {
                binaryByte.append((byte & (1 << i)) ? '1' : '0');
            }
            binaryByte.append(" ");
        }
        return binaryByte;
}

void MainWindow::on_clear_clicked() {
        ui->edytorek->clear();
        ui->checkboxik->setChecked(false);
        ui->viewer->setChecked(false);
        qInfo() << "WYCZYSZCZONO!";
}

void MainWindow::on_add_clicked() {
        QVector<char> vectOfData = readFile();
        if (isBlf(vectOfData) || ui->viewer->isChecked()){
            if (ui->checkboxik->isChecked()) {
                ui->edytorek->setPlainText(binchange());
            } else {
                ui->edytorek->setPlainText("Plik nie jest BLFem");
                ui->edytorek->append(binchange());
            }
        } else {
            ui->edytorek->append("--------------------------------------------------------------------------------");
            ui->edytorek->append("File Name: ");
            ui->edytorek->append("File Path: " + fileName);
            ui->edytorek->append("File Size: ");
            ui->edytorek->append("Header: ");
            ui->edytorek->append("Is BLF?: ");
            ui->edytorek->append("--------------------------------------------------------------------------------");
        }
}

//    QVector<char> vectOfData = readFile();
//    if (isBlf(vectOfData ))
//    {

//    }

