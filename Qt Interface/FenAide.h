// This window, as its name shows, is the windows which opens to give some help and details about the way to use the program.

#ifndef HEADER_FENAIDE
#define HEADER_FENAIDE

#include <QWidget>
#include <QDialog>
#include <QTextEdit>
#include <QString>
#include <QPushButton>
#include <QtGui>

class FenAide : public QDialog
{
    public:
        FenAide(QString &codee, QWidget *parent);

    private:
        QTextEdit *codeGeneree;
        QPushButton *fermer;
};

#endif

