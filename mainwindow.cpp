/*
Auteur : Julien Van Loo
Date de création : Mon Apr 1 2013

Rôle :
*/
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Fractalisor");
    setWindowIcon(QIcon("icon.png"));

    fractalType = new QComboBox();
    fractalType->addItem(tr("Fractal Type"));
    fractalType->addItem(tr("Mandelbot's fractal"));
    fractalType->addItem(tr("Julia's fractal"));
    connect(fractalType, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshOptions(int)));

    QHBoxLayout *layoutCst = new QHBoxLayout;
    cstGroupBox = new QGroupBox(tr("Constant"));
    cstReal = new QDoubleSpinBox();
    cstPlusLabel = new QLabel("+");
    cstImag = new QDoubleSpinBox();
    cstImagLabel = new QLabel("i");
    layoutCst->addWidget(cstReal);
    layoutCst->addWidget(cstPlusLabel);
    layoutCst->addWidget(cstImag);
    layoutCst->addWidget(cstImagLabel);
    cstGroupBox->setLayout(layoutCst);
    cstGroupBox->setEnabled(false);

    QHBoxLayout *layoutX = new QHBoxLayout;
    groupBoxX = new QGroupBox(tr("Limits on X axis"));
    minimalX = new QDoubleSpinBox();
    minimalX->setDecimals(5);
    minimalX->setSingleStep(0.01);
    maximalX = new QDoubleSpinBox();
    maximalX->setDecimals(5);
    maximalX->setSingleStep(0.01);
    layoutX->addWidget(minimalX);
    layoutX->addWidget(maximalX);
    groupBoxX->setLayout(layoutX);
    groupBoxX->setEnabled(false);
    connect(minimalX, SIGNAL(valueChanged(double)), this, SLOT(setMinOfMaxX(double)));
    connect(maximalX, SIGNAL(valueChanged(double)), this, SLOT(setMaxOfMinX(double)));

    QHBoxLayout *layoutY = new QHBoxLayout;
    groupBoxY = new QGroupBox(tr("Limits on Y axis"));
    minimalY = new QDoubleSpinBox();
    minimalY->setDecimals(5);
    minimalY->setSingleStep(0.01);
    maximalY = new QDoubleSpinBox();
    maximalY->setDecimals(5);
    maximalY->setSingleStep(0.01);
    layoutY->addWidget(minimalY);
    layoutY->addWidget(maximalY);
    groupBoxY->setLayout(layoutY);
    groupBoxY->setEnabled(false);
    connect(minimalY, SIGNAL(valueChanged(double)), this, SLOT(setMinOfMaxY(double)));
    connect(maximalY, SIGNAL(valueChanged(double)), this, SLOT(setMaxOfMinY(double)));

    QHBoxLayout *layoutZoomIter = new QHBoxLayout;
    groupBoxZoomIter = new QGroupBox(tr("Zoom et number of iterations"));
    zoomValue = new QSpinBox();
    zoomValue->setRange(1, 1000000);
    zoomValue->setValue(100);
    iterationNbr = new QSpinBox();
    iterationNbr->setRange(1, 10000);
    iterationNbr->setValue(50);
    layoutZoomIter->addWidget(zoomValue);
    layoutZoomIter->addWidget(iterationNbr);
    groupBoxZoomIter->setLayout(layoutZoomIter);
    groupBoxZoomIter->setEnabled(false);

    QHBoxLayout *layoutSavePath = new QHBoxLayout;
    groupBoxSavePath = new QGroupBox(tr("Save as..."));
    savePath = new QLineEdit(QDir().homePath()+"/fractal.png");
    savePath->setEnabled(false);
    savePathButton = new QPushButton(tr("Browse..."));
    layoutSavePath->addWidget(savePath);
    layoutSavePath->addWidget(savePathButton);
    groupBoxSavePath->setLayout(layoutSavePath);
    groupBoxSavePath->setEnabled(false);
    connect(savePathButton, SIGNAL(clicked()), this, SLOT(savePathChoice()));

    QVBoxLayout *layoutOptions = new QVBoxLayout;
    optionsGroupBox = new QGroupBox(tr("Options"));
    layoutOptions->addWidget(fractalType);
    layoutOptions->addWidget(cstGroupBox);
    layoutOptions->addWidget(groupBoxX);
    layoutOptions->addWidget(groupBoxY);
    layoutOptions->addWidget(groupBoxZoomIter);
    layoutOptions->addWidget(groupBoxSavePath);
    optionsGroupBox->setLayout(layoutOptions);

    generationBar = new QProgressBar();
    generationBar->setValue(0);

    generationInfos = new QLabel();

    generateButton = new QPushButton(tr("Generate!"));
    generateButton->setEnabled(false);
    connect(generateButton, SIGNAL(clicked()), this, SLOT(calculate()));

    QVBoxLayout *principalLayout = new QVBoxLayout;
    principalLayout->addWidget(optionsGroupBox);
    principalLayout->addWidget(generationBar);
    principalLayout->addWidget(generationInfos);
    principalLayout->addWidget(generateButton);

    setLayout(principalLayout);
}

void MainWindow::refreshOptions(int type)
{
    switch (type)
    {
        case -1: case 0:
            cstGroupBox->setEnabled(false);
            groupBoxX->setEnabled(false);
            groupBoxY->setEnabled(false);
            groupBoxZoomIter->setEnabled(false);
            groupBoxSavePath->setEnabled(false);
            generateButton->setEnabled(false);
            break;
        case 1:
            cstGroupBox->setEnabled(false);
            groupBoxX->setEnabled(true);
            groupBoxY->setEnabled(true);
            groupBoxZoomIter->setEnabled(true);
            groupBoxSavePath->setEnabled(true);
            generateButton->setEnabled(true);
            minimalX->setRange(-2.1, 0.6);
            minimalX->setValue(-2.1);
            maximalX->setRange(-2.1, 0.6);
            maximalX->setValue(0.6);
            minimalY->setRange(-1.2, 1.2);
            minimalY->setValue(-1.2);
            maximalY->setRange(-1.2, 1.2);
            maximalY->setValue(1.2);
            break;
        case 2:
            cstGroupBox->setEnabled(true);
            groupBoxX->setEnabled(true);
            groupBoxY->setEnabled(true);
            groupBoxZoomIter->setEnabled(true);
            groupBoxSavePath->setEnabled(true);
            generateButton->setEnabled(true);
            minimalX->setRange(-2.0, 2.0);
            minimalX->setValue(-2.0);
            maximalX->setRange(-2.0, 2.0);
            maximalX->setValue(2.0);
            minimalY->setRange(-2.0, 2.0);
            minimalY->setValue(-2.0);
            maximalY->setRange(-2.0, 2.0);
            maximalY->setValue(2.0);
            break;
        default:
            break;


    }
}

void MainWindow::setMinOfMaxX(double value)
{
    maximalX->setMinimum(value);
}

void MainWindow::setMaxOfMinX(double value)
{
    minimalX->setMaximum(value);
}

void MainWindow::setMinOfMaxY(double value)
{
    maximalY->setMinimum(value);
}

void MainWindow::setMaxOfMinY(double value)
{
    minimalY->setMaximum(value);
}

void MainWindow::savePathChoice()
{
    QString filter;
    QString path = QFileDialog::getSaveFileName(this, tr("save fractal as..."), savePath->text(), tr("PNG (*.png | *.PNG);;JPEG (*.jpg | *.jpeg | *.JPG | *.JPEG);;BMP (*.bmp | *.BMP);;TIFF (*.tiff | *.TIFF);;XBM (*.xbm | *.XBM);;XPM (*.xpm | *.XPM);;PPM (*.ppm | *.PPM)"), &filter);
    if (!path.isEmpty())
    {
        savePath->setText(path);
    }
}

void MainWindow::calculate()
{
    switch (fractalType->currentIndex())
    {
        case -1: case 0:
            generationInfos->setText(tr("No fractal type selected"));
            break;
        case 1:
            calculateMandelbrot();
            break;
        case 2:
            calculateJulia();
            break;
        default :
            generationInfos->setText(tr("Fractal type selected doesn't exist"));
            break;
    }
}

void MainWindow::calculateMandelbrot()
{
    optionsGroupBox->setEnabled(false);
    generateButton->setEnabled(false);
    generationInfos->setText(tr("Génération en cours..."));
    generationBar->setValue(0);
    clock_t tempsI, tempsF;

    tempsI=clock();

    double xMin=minimalX->value(), xMax=maximalX->value(), yMin=minimalY->value(), yMax=maximalY->value(), zoom=(double)(zoomValue->value());
    int iterationMax=iterationNbr->value(), i;
    double cReel, cImag, zReel, zImag, tmp;

    int imageX=fabs(xMax-xMin)*zoom;
    int imageY=fabs(yMax-yMin)*zoom;

    QImage image = QImage(imageX, imageY, QImage::Format_RGB32);

    for(int x=0; x<imageX; x++)
    {
        for(int y=0; y<imageY;y++)
        {
            cReel=(x/zoom)+xMin;
            cImag=(y/zoom)+yMin;
            zReel=0;
            zImag=0;
            i=0;
            while (pow(zReel, 2)+pow(zImag, 2)<4 && i<iterationMax)
            {
                tmp=zReel;
                zReel=pow(zReel, 2)-pow(zImag, 2)+cReel;
                zImag=(2*zImag*tmp)+cImag;
                i++;
            }
            if (i==iterationMax)
            {
                image.setPixel(x, y, qRgb(0,0,0));
            }
            else
            {
                image.setPixel(x, y, QColor::fromHsv((255*(i%iterationMax))/iterationMax, 250, 250).rgb());
            }
            generationBar->setValue((x*100)/(imageX-1));
        }
    }
    tempsF=clock();
    generationInfos->setText(tr("Saving the picture..."));
    image.save(savePath->text());
    generationInfos->setText(tr("Generated in ")+QString().setNum((double)(tempsF-tempsI)/CLOCKS_PER_SEC)+tr(" seconds."));
    optionsGroupBox->setEnabled(true);
    generateButton->setEnabled(true);

    return;
}

void MainWindow::calculateJulia()
{
    optionsGroupBox->setEnabled(false);
    generateButton->setEnabled(false);
    generationInfos->setText(tr("Génération en cours..."));
    generationBar->setValue(0);
    clock_t tempsI, tempsF;

    tempsI=clock();

    double xMin=minimalX->value(), xMax=maximalX->value(), yMin=minimalY->value(), yMax=maximalY->value(), zoom=(double)(zoomValue->value()), cReel=cstReal->value(), cImag=cstImag->value();
    int iterationMax=iterationNbr->value(), i;
    double zReel, zImag, tmp;

    int imageX=fabs(xMax-xMin)*zoom;
    int imageY=fabs(yMax-yMin)*zoom;

    QImage image = QImage(imageX, imageY, QImage::Format_RGB32);

    for(int x=0; x<imageX; x++)
    {
        for(int y=0; y<imageY;y++)
        {
            zReel=0;
            zImag=0;
            i=0;
            while (pow(zReel, 2)+pow(zImag, 2)<4 && i<iterationMax)
            {
                tmp=zReel;
                zReel=pow(zReel, 2)-pow(zImag, 2)+cReel;
                zImag=(2*zImag*tmp)+cImag;
                i++;
            }
            if (i==iterationMax)
            {
                image.setPixel(x, y, qRgb(0,0,0));
            }
            else
            {
                image.setPixel(x, y, QColor::fromHsv((255*(i%iterationMax))/iterationMax, 250, 250).rgb());
            }
            generationBar->setValue((x*100)/(imageX-1));
        }
    }
    tempsF=clock();
    generationInfos->setText(tr("Saving the picture..."));
    image.save(savePath->text());
    generationInfos->setText(tr("Generated in ")+QString().setNum((double)(tempsF-tempsI)/CLOCKS_PER_SEC)+tr(" seconds."));
    optionsGroupBox->setEnabled(true);
    generateButton->setEnabled(true);

    return;
}

MainWindow::~MainWindow()
{

}
