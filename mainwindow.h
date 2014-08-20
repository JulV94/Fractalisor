#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void refreshOptions(int type);
    void setMinOfMaxX(double value);
    void setMaxOfMinX(double value);
    void setMinOfMaxY(double value);
    void setMaxOfMinY(double value);
    void savePathChoice();
    void calculate();
    void calculateMandelbrot();
    void calculateJulia();

private:
    QComboBox *fractalType;
    QGroupBox *cstGroupBox;
    QLabel *cstPlusLabel;
    QDoubleSpinBox *cstReal;
    QLabel *cstImagLabel;
    QDoubleSpinBox *cstImag;
    QGroupBox *groupBoxX;
    QDoubleSpinBox *minimalX;
    QDoubleSpinBox *maximalX;
    QGroupBox *groupBoxY;
    QDoubleSpinBox *minimalY;
    QDoubleSpinBox *maximalY;
    QGroupBox *groupBoxZoomIter;
    QSpinBox *zoomValue;
    QSpinBox *iterationNbr;
    QGroupBox *groupBoxSavePath;
    QPushButton *savePathButton;
    QLineEdit *savePath;
    QGroupBox *optionsGroupBox;
    QProgressBar *generationBar;
    QLabel *generationInfos;
    QPushButton *generateButton;
};

#endif // MAINWINDOW_H
