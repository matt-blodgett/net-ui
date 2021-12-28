#include "panelresponse.h"

#include <QGridLayout>
#include <QTextEdit>


PanelResponse::PanelResponse(QWidget *parent) : QWidget(parent)
{
    m_boxDisplay = new QTextEdit(this);
    m_boxDisplay->setReadOnly(true);

    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_boxDisplay, 0, 0, 1, 1);
    gridMain->setContentsMargins(0, 0, 0, 0);
    gridMain->setHorizontalSpacing(0);
    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);
}

void PanelResponse::setDisplayText(const QString &text)
{
    m_boxDisplay->setText(text);
}
