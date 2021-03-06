#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include "plot/axis.h"
#include "plot/grid.h"
#include "plot/signature.h"

#include "plot/plot.h"
#include "plot/plotTypes/dots.h"
#include "plot/plotTypes/spectrum.h"

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QColor>

class PlotManager : public QWidget
{
    Q_OBJECT

public:
    explicit PlotManager(QWidget* parent = 0);
    virtual ~PlotManager();

    void setId(int id);
    int  getId() const;
    void setIdFreq(int idFreq);
    int  getIdFreq() const;
    void setInvelopeFlag(int invelopeFlag);
    int  getInvelopeFlag() const;

    void addAxis(Axis::PlotAxis axis);
    int  getIdAxis() const;
    void setSignatureAxis(const QVector<qreal>& point, const QVector<QString>& str);
    void addGrid(const int countHLine, const int countVLine);
    void addSignature(const QString str);
    void addPlot();
    void setPlot(const QVector<QPointF>& plotPoints);
    void addInvelope();
    void setInvelope(const QVector<QPointF>& invelopePoints);
    void addSpectrum();
    void setSpectrum(const QVector<QPointF>& spectrumPoints, const QVector<QString>& str);

    void setMargin(const int left, const int right, const int top, const int buttom);
    void setCountLines(const int countHLine, const int countVLine);

protected:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void resizeEvent(QResizeEvent*) override;

private:
    int countHLines;
    int countVLines;

    int idPlot;
    int idFreq;
    int invelopeFlag;
    int idAxis;

    int marginTop;
    int marginButtom;
    int marginLeft;
    int marginRight;

    Axis* axisX;
    Axis* axisY;
    Grid* grid;
    Signature* signature;

    QColor colorFunction;
    QColor colorInvelope;

    QVector<Plot*> plots;

    void consider();
};

#endif // PLOTMANAGER_H
