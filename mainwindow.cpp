#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jlevels.h"
#include "jimager.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerID = startTimer( 1000 );
    //this->setStyleSheet("#centralWidget { background: url(../probering-simple/icons/bg_stars.png); }");
}

MainWindow::~MainWindow()
{
    killTimer( timerID );
    delete ui;
}

void MainWindow::on_pbTweede_clicked()
{
    int col = 0;

    ui->tlOutput->setText("TEST runtime rows");
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(210,202,226));
    ui->tlOutput->setPalette(palette);
    //ui->tlOutput->setAutoFillBackground(false);

    JHeaderRow * headerRow = new JHeaderRow();
    headerRow->setupUI(ui->gridResults, 0, 0);
    headerRow->groupName->setText( QString::fromUtf8("Test Group") );

    for ( unsigned int i = 0; i < 16; ++i)
    {
        JItemRow *item = new JItemRow();
        //item = new JItemRow(this);
        item->itemNo = i;
        if ( i%2  ) {
            item->myLevel = 1;
        } else if ( !(i%5) ) {
            item->myLevel = 0;
        } else {
            item->myLevel = 2;
        }
        item->setupUI(ui->gridResults, i+1, col);
        item->itemName->setText( QString::fromUtf8("Item %1").arg(i+1) );
        item->showLevel();
    }

    col = 1;
    JHeaderRow * headerRow2 = new JHeaderRow();
    headerRow2->setupUI(ui->gridResults, 2, col);

    ui->sxAreaResults->setFixedHeight( 2 + (17 * 29));
}

void MainWindow::on_actionProbeersel_triggered()
{
    ui->tlOutput->setText( "Imager" );
    jimager *imager = new jimager( ui->saImager2 );
    imager->createActions( menuBar() );
    imager->loadFile( QString::fromUtf8("../probering-simple/icons/bg_stars.png") );
}


void MainWindow::on_pbFillShem_clicked()
{
    if (sharedMemory.isAttached()) {
        return;
        //detach();
    }

    sharedMemory.setKey( QString("7439ABB2-5378-3351-6588-") );

    /*QImage image;
    QString fileName = QFileDialog::getOpenFileName(0, QString(), QString(),
                                        tr("Images (*.png *.xpm *.jpg)"));

    if ( !image.load( fileName ) ) {
    //if ( !image.load( QString::fromUtf8("../probering-simple/icons/bg_stars.png") ) ) {
        ui->lbStatus->setText(tr("Selected file is not an image, please select another."));
        return;
    }
    ui->lbStatus->setPixmap(QPixmap::fromImage(image));

    // load into shared memory
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << mySData;
    int size = buffer.size();

    if (!sharedMemory.create(size)) {
        ui->tlOutput->setText(tr("Unable to create shared memory segment."));
        return;
    }
    sharedMemory.lock();
    char *to = (char*)sharedMemory.data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(sharedMemory.size(), size));
    sharedMemory.unlock();

     ui->tlOutput->setText( QString::fromUtf8("Size %1").arg(size) );
     */

    if ( !sharedMemory.create(sizeof(SData)) ) {
        ui->tlOutput->setText(tr("Unable to create shared memory segment."));
        return;
    }
    shData = static_cast<SData *>( sharedMemory.data() );


    shData->a = 2;
    shData->b = 85;
    shData->c = 9298;
    for ( int i = 0; i < 24; ++i) {
        shData->d[i] = 40 + i;
    }
    ui->lbStatus->setText( QString::fromUtf8("b:%1").arg(shData->b) );

}

void MainWindow::detach()
{
    if (!sharedMemory.detach())
        ui->lbStatus->setText(tr("Unable to detach from shared memory."));
}

void MainWindow::timerEvent( QTimerEvent *)
{
    if ( shData != nullptr ) {
        shData->b = rand();
        ui->lbStatus->setText( QString::fromUtf8("b:%1").arg(shData->b) );
    }
}
