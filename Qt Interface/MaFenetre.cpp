//The Main Window

#include "FenGenere.h"
#include "MaFenetre.h"
#include "FenAide.h"
#include "QFormLayout"
#include "QGroupBox"
#include "QFormLayout"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QWidget"
#include "QString"
#include "QMessageBox"
#include "QPixmap"
#include "QLabel"
#include "QIcon"
#include "QCheckBox"
#include "QProcess"
#include "qDebug"
#include "QFileDialog"
#include <QDoubleSpinBox>


MaFenetre::MaFenetre() : QWidget()
{
    //We create all the Text Widgets of the window
    QLabel *label = new QLabel(this);
    label->setText("Welcome to Wine Quality Simulator !");
    label->setFont(QFont("Times New Roman", 13));
    label->setAlignment(Qt::AlignCenter);
    QLabel *label2 = new QLabel(this);
    label2->setPixmap(QPixmap("vinn.jpg"));
    label2->setAlignment(Qt::AlignCenter);
    QLabel *label3 = new QLabel(this);
    label3->setPixmap(QPixmap("top.jpg"));
    label3->setAlignment(Qt::AlignCenter);

    //The first Layout : the one for the "train" function
    train = new QPushButton("&Train the Neural Network");
    train->setToolTip("Be sure to write C:/aa/aa and not C:\\aa\\aa");
    fichier = new QLineEdit("C:/");
    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow("&Copy/paste the database path :", fichier);
    layout1->addWidget(train);
    QGroupBox *layoutt = new QGroupBox("First, please indicate the location of the training database :");
    layoutt->setLayout(layout1);

    //The second Layout : the one for the "predict my wine quality" function
    comp1 = new QDoubleSpinBox;
    comp2 = new QDoubleSpinBox;
    comp3 = new QDoubleSpinBox;
    comp4 = new QDoubleSpinBox;
    comp5 = new QDoubleSpinBox;
    comp6 = new QDoubleSpinBox;
    comp7 = new QDoubleSpinBox;
    comp8 = new QDoubleSpinBox;
    comp9 = new QDoubleSpinBox;
    comp10 = new QDoubleSpinBox;
    comp11 = new QDoubleSpinBox;
    protections = new QCheckBox("Warn me if my values seem strange.");
    generer = new QPushButton("&Predict my Wine Quality");
    generer->setToolTip("SuperNeuralNetwork : report!");

    QFormLayout *definitionLayout = new QFormLayout;
    definitionLayout->addWidget(protections);
    definitionLayout->addRow("&Fixed Acidity :", comp1);
    definitionLayout->addRow("&Volatile Acidity :", comp2);
    definitionLayout->addRow("&Citric Acid :", comp3);
    definitionLayout->addRow("&Residual Sugar :", comp4);
    definitionLayout->addRow("&Chlorides :", comp5);
    definitionLayout->addRow("&Free Sulfur Dioxide :", comp6);
    definitionLayout->addRow("&Total Sulfure Dioxide :", comp7);
    definitionLayout->addRow("&Density :", comp8);
    definitionLayout->addRow("&pH :", comp9);
    definitionLayout->addRow("&Sulphates :", comp10);
    definitionLayout->addRow("&Alcohol :", comp11);
    definitionLayout->addWidget(generer);

    QGroupBox *groupDefinition = new QGroupBox("Cheap wine or masterpiece? Give us the required informations :");
    groupDefinition->setLayout(definitionLayout);


    //Third Layout : Help and Leave
    quitter = new QPushButton("&Leave");
    quitter->setToolTip("Goodbye !");
    aider = new QPushButton("&Need some help ?");
    aider->setToolTip("Looking for more info? Come here young padawan");
    QHBoxLayout *boutonsLayout = new QHBoxLayout;
    boutonsLayout->setAlignment(Qt::AlignRight);
    boutonsLayout->addWidget(aider);
    boutonsLayout->addWidget(quitter);

    //The Main Layout : contains all three previous Layouts
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;

    layoutPrincipal->addWidget(label);
    layoutPrincipal->addWidget(label3);
    layoutPrincipal->addWidget(layoutt);
    layoutPrincipal->addWidget(groupDefinition);
    layoutPrincipal->addWidget(label2);
    layoutPrincipal->addLayout(boutonsLayout);

    //Properties of the Window
    setLayout(layoutPrincipal);
    setWindowTitle("Wine Quality Simulator");
    setWindowIcon(QIcon("icone.jpg"));
    resize(400, 450);

    // Connection of the buttons
    connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(generer, SIGNAL(clicked()), this, SLOT(genererCode()));
    connect(aider, SIGNAL(clicked()), this, SLOT(genererCodee()));
    connect(train, SIGNAL(clicked()), this, SLOT(ouvrirprog()));
}



void MaFenetre::genererCode()
{
    //First, we transform the information given by the user to double variables.
    double com1;
    com1 = comp1->value();
    double com2;
    com2 = comp2->value();
    double com3;
    com3 = comp3->value();
    double com4;
    com4 = comp4->value();
    double com5;
    com5 = comp5->value();
    double com6;
    com6 = comp6->value();
    double com8;
    com8 = comp8->value();
    double com7;
    com7 = comp7->value();
    double com9;
    com9 = comp9->value();
    double com10;
    com10 = comp10->value();
    double com11;
    com11 = comp11->value();


    // Then, we advertise the user that its values seem strange (if he has checked "protection")
    if ((com1<5) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Fixed Acity value seems pretty low. Are you sure ?");
    }
    if ((com1>10) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Fixed Acity value seems pretty high. Are you sure ?");
    }

    if ((com2<0.08) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Volatile Acidity value seems pretty low. Are you sure ?");
    }
    if ((com2>1.1) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Volatile Acidity value seems pretty high. Are you sure ?");
    }

    if ((com3<0) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Citric Acid value seems pretty low. Are you sure ??");
    }
    if ((com3>1.66) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Citric Acid  value seems pretty high. Are you sure ?");
    }

    if ((com4<1) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Residual Sugar value seems pretty low. Are you sure ?");
    }
    if ((com4>9.9) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Residual Sugar  value seems pretty high. Are you sure ?");
    }

    if ((com5<0.009) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Chlorides value seems pretty low. Are you sure ?");
    }
    if ((com5>0.346) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Chlorides  value seems pretty high. Are you sure ?");
    }

    if ((com6<2) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Free Sulfur Dioxide value seems pretty low. Are you sure ?");
    }
    if ((com6>82.5) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Free Sulfur Dioxide value seems pretty high. Are you sure ?");
    }

    if ((com7<9) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Total Sulfure Dioxide value seems pretty low. Are you sure ?");
    }
    if ((com7>366.5) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Total Sulfure Dioxide  value seems pretty high. Are you sure ?");
    }

    if ((com8<0.98711) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Density value seems pretty low. Are you sure ?");
    }
    if ((com8>1.03898) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Density  value seems pretty high. Are you sure ?");
    }

    if ((com9<3) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the pH value seems pretty low. Are you sure ?");
    }
    if ((com9>3.82) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the pH  value seems pretty high. Are you sure ?");
    }

    if ((com10<0.22) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Sulphates value seems pretty low. Are you sure ?");
    }
    if ((com10>1.08) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Sulphates  value seems pretty high. Are you sure ?");
    }

    if ((com11<8) & (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Alcohol value seems pretty low. Are you sure ?");
    }
    if ((com11>9.9)& (protections->isChecked()))
    {
        QMessageBox::warning(this, "T'es mauvais Jack!", "Hey you, the Alcohol  value seems pretty high. Are you sure ?");
    }

    //We create the code for the FenGenere, and we transfer the code from MaFenetre to FenGenere
    QString code;
        code += "\n Premier composant : " + comp1->text() + "\n";
        code += "\n Deuxième composant : " + comp2->text() + "\n";
        code += "\n Troisième composant : " + comp3->text() + "\n";
        code += "\n Quatrième composant : " + comp4->text() + "\n";
        code += "\n Cinqième composant : " + comp5->text() + "\n";
        code += "\n Sixième composant : " + comp6->text() + "\n";
        code += "\n Septième composant : " + comp7->text() + "\n";
        code += "\n Huitième composant : " + comp8->text() + "\n";
        code += "\n Neuvième composant : " + comp9->text() + "\n";
        code += "\n Dixième composant : " + comp10->text() + "\n";
        code += "\n Onzième composant : " + comp11->text() + "\n\n";
        FenGenere *fenetreCode = new FenGenere(code, this);
        fenetreCode->exec();
    }


void MaFenetre::genererCodee()
{
   // Code for the Help
   QString codee;
   codee.append("\n This is a white wine quality simulator. \n  Beer or red wine amator, this is not for you! \n ");
   codee.append( "\n First, train the neural network. \n In order to do so, copy-paste the training database path. \n >>>WARNING : writing the path, please ensure you write \\ and not / ! <<< \n Example : C:/user/app.exe \n Then, enter the required values. \n");
   codee.append("\n And because we are your friend, we help you : \n  If your values seems strange, you will be advised.  \n ");
   FenAide *fenetreCodee = new FenAide(codee, this);
   fenetreCodee->exec();
}

void MaFenetre::ouvrirprog()
{

    QProcess process;
    bool ok = process.startDetached("C:/Qt/Qt5.2.1/Tools/QtCreator/bin/qtcreator.exe");
      if (ok) { qDebug() << "ok";
      } else {qDebug()<<"error";
      }

}


