#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QDoubleSpinBox;
QT_END_NAMESPACE


class add_dialog : public QDialog
{
    Q_OBJECT

public:
    //only add shit you are going to input
    add_dialog(QWidget *parent = 0);
    // THESE ARE FOR THE RENT TAB
    QLineEdit *billIdText;
    QDoubleSpinBox *rentText;
    QDoubleSpinBox *electricityText;
    QDoubleSpinBox *waterText;
    QDoubleSpinBox *gasText;
    QDoubleSpinBox *internetText;
    QLineEdit *totalText;
    QLineEdit *dateAddedText;
    QLineEdit *dateDueText;




private:
    // THESE ARE FOR THE RENT TAB
    QLabel *billIdLabel;
    QLabel *rentLabel;
    QLabel *electricityLabel;
    QLabel *waterLabel;
    QLabel *gasLabel;
    QLabel *internetLabel;
    QLabel *dateDueLabel;
    QLabel *totalLabel;
    QLabel *dateAddedLabel;

    QPushButton *okButton;
    QPushButton *cancelButton;

};

#endif // ADD_DIALOG_H
