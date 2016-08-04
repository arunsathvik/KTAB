// --------------------------------------------
// Copyright KAPSARC. Open source MIT License.
// --------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015 King Abdullah Petroleum Studies and Research Center
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
// and associated documentation files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// -------------------------------------------------

#include "mainwindow.h"

//lineGraph - Graph 1 / Dock 1

void MainWindow::initializeLineGraphDock()
{
    graphTypeStackedWidget = new QStackedWidget(lineGraphDock);

    lineCustomGraph = new QCustomPlot;
    graphTypeStackedWidget->addWidget(lineCustomGraph);

    lineGraphGridLayout->addWidget(graphTypeStackedWidget,1,0);

    initializeLineGraphPlot();

    lineGraphControlsFrame = new QFrame;
    lineGraphControlsFrame->setFrameShape(QFrame::StyledPanel);

    QVBoxLayout *lineControlsVerticalLayout = new QVBoxLayout(lineGraphControlsFrame);

    QFont  labelFont;
    labelFont.setBold(true);

    QLabel * actorsLabel = new QLabel("Actors");
    actorsLabel->setAlignment(Qt::AlignHCenter);
    actorsLabel->setFont(labelFont);
    actorsLabel->setFrameStyle(QFrame::Panel | QFrame::StyledPanel);
    lineControlsVerticalLayout->addWidget(actorsLabel);

    lineGraphActorsScrollArea = new QScrollArea(lineGraphControlsFrame);

    lineControlsVerticalLayout->addWidget(lineGraphActorsScrollArea);

    lineGraphSelectAllCheckBox = new QCheckBox("Select All Actors");
    lineGraphSelectAllCheckBox->setChecked(true);
    lineControlsVerticalLayout->addWidget(lineGraphSelectAllCheckBox);

    connect(lineGraphSelectAllCheckBox,SIGNAL(clicked(bool)),this,SLOT(lineGraphSelectAllActorsCheckBoxClicked(bool)));

    QLabel * lineGraphTypeLabel = new QLabel("Graph Type");
    lineGraphTypeLabel->setAlignment(Qt::AlignHCenter);
    lineGraphTypeLabel->setFont(labelFont);
    lineGraphTypeLabel->setFrameStyle(QFrame::Panel | QFrame::StyledPanel);

    lineControlsVerticalLayout->addWidget(lineGraphTypeLabel);

    lineGraphRadioButton = new QRadioButton("Line Graph");
    sankeyGraphRadioButton = new QRadioButton("Sankey Diagram");
    lineGraphRadioButton->setChecked(true);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(lineGraphRadioButton);
    layout->addWidget(sankeyGraphRadioButton);
    lineControlsVerticalLayout->addLayout(layout);

    QLabel * lineGraphDimensionsLabel = new QLabel("Dimensions");
    lineGraphDimensionsLabel->setAlignment(Qt::AlignHCenter);
    lineGraphDimensionsLabel->setFont(labelFont);
    lineGraphDimensionsLabel->setFrameStyle(QFrame::Panel | QFrame::StyledPanel);
    lineControlsVerticalLayout->addWidget(lineGraphDimensionsLabel);

    lineGraphDimensionComboBox= new QComboBox;
    lineControlsVerticalLayout->addWidget(lineGraphDimensionComboBox);
    connect(lineGraphDimensionComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(lineGraphDimensionChanged(int)));

    lineGraphTurnSlider = new QSlider(Qt::Horizontal);
    lineGraphTurnSlider->setTickInterval(1);
    lineGraphTurnSlider->setTickPosition(QSlider::TicksBothSides);
    lineGraphTurnSlider->setPageStep(1);
    lineGraphTurnSlider->setSingleStep(1);
    lineGraphTurnSlider->setRange(0,1);
    lineGraphTurnSlider->setVisible(false);
    connect(lineGraphTurnSlider,SIGNAL(valueChanged(int)),this,SLOT(lineGraphTurnSliderChanged(int)));

    //positioning widgets in the grid
    lineGraphGridLayout->addWidget(lineGraphTurnSlider,0,0,1,1,Qt::AlignTop);
    lineGraphGridLayout->addWidget(lineGraphControlsFrame,1,1,Qt::AlignRight);

}


void MainWindow::initializeLineGraphPlot()
{
    lineCustomGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                     QCP::iSelectLegend | QCP::iSelectPlottables);
    lineCustomGraph->xAxis->setRange(0, 10);
    lineCustomGraph->yAxis->setRange(0,100);
    lineCustomGraph->axisRect()->setupFullAxesBox();

    lineCustomGraph->plotLayout()->insertRow(0);
    lineCustomGraph->plotLayout()->addElement(0, 0, new QCPPlotTitle(lineCustomGraph, "Competitive vs Time "));

    lineCustomGraph->xAxis->setLabel("Turn");
    lineCustomGraph->yAxis->setLabel("Competitive");
    lineCustomGraph->legend->setVisible(false);

//    QFont legendFont = font();
//    legendFont.setPointSize(10);
//    lineCustomGraph->legend->setFont(legendFont);
//    lineCustomGraph->legend->setSelectedFont(legendFont);
//    lineCustomGraph->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

//    connect(lineCustomGraph, SIGNAL(legendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(selectionChanged()));
    // connect slot that ties some axis selections together (especially opposite axes):
    connect(lineCustomGraph, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(lineCustomGraph, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(lineCustomGraph, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(lineCustomGraph->xAxis, SIGNAL(rangeChanged(QCPRange)), lineCustomGraph->xAxis2, SLOT(setRange(QCPRange)));
    connect(lineCustomGraph->yAxis, SIGNAL(rangeChanged(QCPRange)), lineCustomGraph->yAxis2, SLOT(setRange(QCPRange)));

    //    // connect some interaction slots:
    //    connect(lineCustomGraph, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
    //    connect(lineCustomGraph, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    //    connect(lineCustomGraph, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(lineCustomGraph, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    lineCustomGraph->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(lineCustomGraph, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
}

void MainWindow::lineGraphSelectAllActorsCheckBoxClicked(bool)
{

}

void MainWindow::lineGraphDimensionChanged(int indx)
{

}

void MainWindow::lineGraphTurnSliderChanged(int)
{

}
void MainWindow::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
{
    Q_UNUSED(event)
    // Set the plot title by double clicking on it
    bool ok;
    QString newTitle = QInputDialog::getText(this, "Title", "New plot title:", QLineEdit::Normal, title->text(), &ok);
    if (ok)
    {
        title->setText(newTitle);
        lineCustomGraph->replot();
    }
}


void MainWindow::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (lineCustomGraph->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        lineCustomGraph->axisRect()->setRangeDrag(lineCustomGraph->xAxis->orientation());
    else if (lineCustomGraph->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        lineCustomGraph->axisRect()->setRangeDrag(lineCustomGraph->yAxis->orientation());
    else
        lineCustomGraph->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (lineCustomGraph->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        lineCustomGraph->axisRect()->setRangeZoom(lineCustomGraph->xAxis->orientation());
    else if (lineCustomGraph->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        lineCustomGraph->axisRect()->setRangeZoom(lineCustomGraph->yAxis->orientation());
    else
        lineCustomGraph->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::addGraphOnModule1(const QVector<double> &x, const QVector<double> &y,QString Actor)
{
    lineCustomGraph->addGraph();
//    lineCustomGraph->graph()->setName(Actor);
    lineCustomGraph->graph()->setData(x, y);
    lineCustomGraph->graph()->setLineStyle(((QCPGraph::LineStyle)(1)));//upto 5

    //  if (rand()%100 > 50)
    lineCustomGraph->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(0)));

    QPen graphPen;
    graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);

    lineCustomGraph->graph()->setPen(graphPen);
    lineCustomGraph->replot();

}

void MainWindow::removeAllGraphs()
{
    lineCustomGraph->clearGraphs();
    lineCustomGraph->replot();
}

void MainWindow::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    if (lineCustomGraph->legend->selectTest(pos, false) >= 0) // context menu on legend requested
    {
        menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
        menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
        menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
        menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
        menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
    }
    else  // general context menu on graphs requested
    {
        menu->addAction("Add random graph", this, SLOT(addGraphOnModule1()));
        if (lineCustomGraph->selectedGraphs().size() > 0)
            menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
        if (lineCustomGraph->graphCount() > 0)
            menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
    }

    menu->popup(lineCustomGraph->mapToGlobal(pos));
}

void MainWindow::moveLegend()
{
    if (QAction * contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            lineCustomGraph->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            lineCustomGraph->replot();
        }
    }
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable)
{
    //statusBar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
}



// --------------------------------------------
// Copyright KAPSARC. Open source MIT License.
// --------------------------------------------
