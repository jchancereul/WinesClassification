//This window is the one which opens to give the result (eg wine quality)

#ifndef HEADER_FENGENERE
#define HEADER_FENGENERE

#include <QWidget>
#include <QDialog>
#include <QTextEdit>
#include <QString>
#include <QPushButton>
#include <QtGui>

class FenGenere : public QDialog
{
    public:
        FenGenere(QString &code, QWidget *parent);

    private:
        QTextEdit *codeGenere;
        QPushButton *fermer;
};

#endif
