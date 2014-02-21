//The Main Window

#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QProgressBar>
#include <QMessageBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QMainWindow>
#include <QtGui>
#include "QCheckBox"
#include <QDoubleSpinBox>

class MaFenetre : public QWidget
{
    Q_OBJECT

    public:
    MaFenetre();

    public slots:
      void genererCode();
      void genererCodee();
      void ouvrirprog();

    private:
      QLineEdit *fichier;
      QDoubleSpinBox *comp1;
      QDoubleSpinBox *comp2;
      QDoubleSpinBox *comp3;
      QDoubleSpinBox *comp4;
      QDoubleSpinBox *comp5;
      QDoubleSpinBox *comp6;
      QDoubleSpinBox *comp7;
      QDoubleSpinBox *comp8;
      QDoubleSpinBox *comp9;
      QDoubleSpinBox *comp10;
      QDoubleSpinBox *comp11;
      QPushButton *generer;
      QPushButton *aider;
      QPushButton *quitter;
      QPushButton *train;
      QCheckBox *protections;

};

#endif

