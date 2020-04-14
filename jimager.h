#ifndef JIMAGER_H
#define JIMAGER_H

//#include <QObject>
#include <QImage>

QT_BEGIN_NAMESPACE
class QObject;
class QMenuBar;
class QAction;
class QLabel;
class QMenu;
class QGridLayout;
class QWidget;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class jimager: public QObject
{
    Q_OBJECT
public:
    jimager(QGridLayout *gridImager);
    jimager(QScrollArea *saArea);
    //virtual ~jimager() {};
    void createActions( QMenuBar * mbar);
    bool loadFile(const QString &);

private slots:
    void zoomIn();
    void zoomOut();

private:
    //void createMenus();
    void setImage(const QImage &newImage);
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    QAction *zoomInAct;
    QAction *zoomOutAct;

};

#endif // JIMAGER_H
