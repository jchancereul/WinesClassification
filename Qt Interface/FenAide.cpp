// This window, as its name shows, is the windows which opens to give some help and details about the way to use the program.

#include "FenAide.h"
#include "QVBoxLayout"
#include "QTextEdit"


FenAide::FenAide(QString &codee, QWidget *parent = 0) : QDialog(parent)
{
    //The part of the code containing the text with the help.
    codeGeneree = new QTextEdit();
    codeGeneree->setPlainText(codee);
    codeGeneree->setReadOnly(true);
    codeGeneree->setFont(QFont("Courier"));
    codeGeneree->setLineWrapMode(QTextEdit::NoWrap);

    //The Button to leave the window and come back to the main window.
    fermer = new QPushButton("Ok, I git it, I'm ready to use this program !");
    fermer->setToolTip("Let's check that.");

    //The text and the Button are included in a vertival Layout.
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(codeGeneree);
    layoutPrincipal->addWidget(fermer);

    //Window Properties
    resize(800, 450);
    setLayout(layoutPrincipal);
    setWindowTitle("SOS");

    //Connection of the Button
    connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
}

