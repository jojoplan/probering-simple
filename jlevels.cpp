#include "jlevels.h"
#include <QMessageBox>
//#include <QApplication>

//---------------------------------------------------------------------
void JHeaderRow::setupUI( QGridLayout *gridLayout, int row, int col )
{
    rowFrame = new QFrame();
    rowFrame->setObjectName( QString::fromUtf8("RowFrame_%1").arg(row) );

    QPalette palette;
    palette.setColor( QPalette::Window, QColor(210,202,226) );
    rowFrame->setAutoFillBackground( true );
    rowFrame->setPalette( palette );
    rowFrame->setMinimumHeight( 28 );
    rowFrame->setMaximumHeight( 28 );

    rowLayout = new QHBoxLayout();
    rowLayout->setObjectName( QString::fromUtf8("rowHeader_%1").arg(row) );
    rowLayout->setSpacing( 9 );
    rowLayout->setContentsMargins( 6, 1, 6, 1 );
    // group
    groupName = new QLabel();
    QSizePolicy sizePol( QSizePolicy:: Preferred, QSizePolicy::Preferred );
    sizePol.setHorizontalStretch( 0 );
    sizePol.setVerticalStretch( 0 );
    groupName->setSizePolicy( sizePol );
    groupName->setMinimumWidth( 182 );
    groupName->setMaximumWidth( 182 );
    rowLayout->addWidget( groupName );
    rowFrame->setLayout( rowLayout );

    gridLayout->addWidget( rowFrame, row, col, 0 );
}
//---------------------------------------------------------------------

//---------------------------------------------------------------------
JItemRow::JItemRow()
{
    myLevel = 0;
}


void JItemRow::setupUI( QGridLayout *gridLayout, int row, int col )
{
    rowFrame = new QFrame();
    rowFrame->setObjectName( QString::fromUtf8("RowFrame_%1").arg(row) );

    QPalette palette;
    if ( row % 2) {
        palette.setColor( QPalette::Window, QColor(232,240,242) );
    } else {
        palette.setColor( QPalette::Window, QColor(226,232,238) );
    }
    rowFrame->setAutoFillBackground( true );
    rowFrame->setPalette( palette );
    rowFrame->setMinimumHeight( 28 );
    rowFrame->setMaximumHeight( 28 );

    rowLayout = new QHBoxLayout();
    rowLayout->setObjectName( QString::fromUtf8("rowItem_%1").arg(row) );
    rowLayout->setSpacing( 9 );
    rowLayout->setContentsMargins( 2, 1, 2, 1 );
    // leveling
    leveling = new QToolButton();
    leveling->setObjectName( QString::fromUtf8("levelItem_%1").arg(row) );
    leveling->setMinimumWidth(  26 );
    leveling->setMaximumWidth(  26 );
    leveling->setMinimumHeight( 26 );
    leveling->setMaximumHeight( 26 );
    QIcon iconL;
    iconL.addPixmap( QPixmap(QString::fromUtf8("../probering-simple/icons/green_round.png")), QIcon::Normal, QIcon::On  );
    iconL.addPixmap( QPixmap(QString::fromUtf8("../probering-simple/icons/red_cross.png")),   QIcon::Normal, QIcon::Off );
    leveling->setIcon( iconL );
    leveling->setIconSize( QSize(20, 20) );
    leveling->setCheckable( true );
    leveling->setFocusPolicy( Qt::StrongFocus );
     //-- Connect signal.
    connect(leveling, &QToolButton::pressed,
            this,     &JItemRow::on_leveling_pressed );
    rowLayout->addWidget( leveling );
    // item
    itemName = new QLabel();
    QSizePolicy sizePol( QSizePolicy:: Preferred, QSizePolicy::Fixed );
    sizePol.setHorizontalStretch( 0 );
    sizePol.setVerticalStretch( 0 );
    itemName->setSizePolicy( sizePol );
    itemName->setMinimumWidth( 162 );
    itemName->setMaximumWidth( 162 );
    rowLayout->addWidget( itemName );

    rowFrame->setLayout( rowLayout );

    gridLayout->addWidget( rowFrame, row, col, 0 );
}

void JItemRow::showLevel() {
    switch ( myLevel ) {
    case 0:
        leveling->setChecked( false );
        leveling->setIconSize( QSize(12, 12));
        itemName->setEnabled( false );
        break;
    case 1:
        leveling->setChecked( true );
        itemName->setEnabled( true );
        break;
    default:
        leveling->setChecked( false );
        itemName->setEnabled( false );
        break;
    }
}

void JItemRow::on_leveling_pressed()
{
//    QMessageBox msgBox;
//    msgBox.setText( QString::fromUtf8("Pressed %1: level is %2").arg(itemNo+1).arg(myLevel) );
//    msgBox.exec();
    switch ( myLevel ) {
    case 1:
        myLevel = 0;
        leveling->setIconSize( QSize(12, 12));
        itemName->setEnabled( false );
        break;
    case 2:
        myLevel = 1;
        leveling->setChecked( false );
        itemName->setEnabled( true );
        break;
    default:
        myLevel = 2;
        leveling->setChecked( true );
        leveling->setIconSize( QSize(20, 20));
        itemName->setEnabled( false );
        break;
    }
}
//---------------------------------------------------------------------

