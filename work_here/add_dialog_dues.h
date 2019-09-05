#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE


class add_dialog : public QDialog
{
    Q_OBJECT

public:
    add_dialog(QWidget *parent = 0);

    //THESE ARE FOR THE DUE TAB
    QLineEdit *apText;
    QLineEdit *edText;
    QLineEdit *erText;
    QLineEdit *joText;

private:

    //THESE ARE FOR THE DUE TAB
    QLabel *apLabel;
    QLabel *edLabel;
    QLabel *erLabel;
    QLabel *joLabel;

    QPushButton *okButton;
    QPushButton *cancelButton;

};

#endif // ADD_DIALOG_H
