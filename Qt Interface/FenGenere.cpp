//This window is the one which opens to give the result (eg wine quality)

#include "FenGenere.h"
#include "QVBoxLayout"
#include "QTextEdit"


FenGenere::FenGenere(QString &code, QWidget *parent = 0) : QDialog(parent)
{
    //The part of the code containing the text with the help.
    codeGenere = new QTextEdit();
    codeGenere->setPlainText(code);
    codeGenere->setReadOnly(true);
    codeGenere->setFont(QFont("Courier"));
    codeGenere->setLineWrapMode(QTextEdit::NoWrap);

    //The Button to leave the window and come back to the main window.
    fermer = new QPushButton("Return");
    fermer->setToolTip("I want to try with an other wine!");

    //The text and the Button are included in a vertival Layout.
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(codeGenere);
    layoutPrincipal->addWidget(fermer);

    //Window Properties
    resize(350, 450);
    setLayout(layoutPrincipal);
    setWindowTitle("Results");

    //Connection of the Button
    connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
}

