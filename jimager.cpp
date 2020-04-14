#include "jimager.h"

#include <QtWidgets>

jimager::jimager(QGridLayout *gridImager)
    : imageLabel(new QLabel)
    , scaleFactor(1)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    gridImager->addWidget(imageLabel);
}

jimager::jimager(QScrollArea *saArea)
    : scrollArea(saArea)
    , imageLabel(new QLabel)
    , scaleFactor(1)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    saArea->setWidget( imageLabel );
}

bool jimager::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        return false;
    }

    setImage(newImage);

    //setWindowFilePath(fileName);

//    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
//        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
//    statusBar()->showMessage(message);
    return true;
}

void jimager::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;
    scaleImage(1.0);
}

void jimager::zoomIn()
{
    scaleImage(1.25);
}

void jimager::zoomOut()
{
    scaleImage(0.8);
}

void jimager::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void jimager::scaleImage(double factor)
{
      Q_ASSERT(imageLabel->pixmap());
      scaleFactor *= factor;
      imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

      adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
      adjustScrollBar(scrollArea->verticalScrollBar(), factor);
}

void jimager::createActions(QMenuBar * mbar)
{
    QMenu *viewMenu = mbar->addMenu(tr("&View"));

    zoomInAct = viewMenu->addAction(tr("Zoom &In (25%)"), this, &jimager::zoomIn);
    zoomInAct->setShortcut(QKeySequence::ZoomIn);

    zoomOutAct = viewMenu->addAction(tr("Zoom &Out (25%)"), this, &jimager::zoomOut);
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
 }
