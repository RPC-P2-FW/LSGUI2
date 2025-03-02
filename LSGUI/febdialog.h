#ifndef FEBDIALOG_H
#define FEBDIALOG_H

#include <QDialog>

namespace Ui {
class febDialog;
}

class febDialog : public QDialog
{
    Q_OBJECT

public:
    explicit febDialog(QWidget *parent = nullptr);
    ~febDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::febDialog *ui;
};

#endif // FEBDIALOG_H
