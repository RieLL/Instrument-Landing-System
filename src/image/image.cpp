#include "image.h"
#include <QPainter>

Image::Image(QString pathToImage, QWidget* parent, int readFlag)
    : QWidget(parent)
    , img(pathToImage)
    , copyImg(img)
    , oldPos(0, 0)
    , x(0)
    , y(0)
    , readFlag(readFlag)
{
    setMouseTracking(false);
    setFixedSize(img.width(), img.height());

    drawCrossHair(0, 0);
}

Image::~Image()
{
    //
}

void Image::drawCrossHair(int bank, int pitch)
{
    qreal k_bank  = { -3.2 * bank + 222 };
    qreal k_pitch = { 6.0 * pitch + 422 };

    bankLine  = { QLine(k_bank, 0, k_bank, img.height() - 1) };
    pitchLine = { QLine(0, k_pitch, img.width() - 1, k_pitch) };

    repaint();
}

void Image::consider()
{
    if (x + width() > img.width())
    {
        x = { img.width() - width() };
    }

    if (y + height() > img.height())
    {
        y = { img.height() - height() };
    }

    update();
}

void Image::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(0, 0, copyImg);

    if (readFlag == 1)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor(0, 0, 0, 255), 2, Qt::SolidLine));

        QRegion region(168, 367, 110, 110, QRegion::Ellipse);
        painter.setClipRegion(region);

        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setPen(QPen(QColor(0, 0, 0, 255), 3, Qt::SolidLine));

        painter.drawLine(bankLine);
        painter.drawLine(pitchLine);
    }

    painter.end();
}

void Image::resizeEvent(QResizeEvent*)
{
    consider();
}

void Image::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        oldPos = { event->pos() };
    }
}

void Image::mouseMoveEvent(QMouseEvent* event)
{
    int dx = { static_cast<int>( oldPos.x() ) - event->x() };
    int dy = { static_cast<int>( oldPos.y() ) - event->y() };

    oldPos = { event->pos() };

    x += dx;
    y += dy;

    if (x < 0) { x = { 0 }; }
    if (y < 0) { y = { 0 }; }

    consider();
}
