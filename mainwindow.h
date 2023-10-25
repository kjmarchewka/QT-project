#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<char> container;
    QString binaryByte;

private slots:
    void on_clear_clicked();

    void on_add_clicked();

    bool isBlf(const QVector<char> &data);

    QVector<char> readFile();

    QString binchange();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
