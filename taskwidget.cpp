#include "taskwidget.h"
#include <QHBoxLayout>

TaskWidget::TaskWidget(const QString &text, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    checkBox = new QCheckBox;
    label = new QLabel();
    layout->addWidget(label);
    layout->addStretch();  // Esto agregará un espacio flexible que empujará el QCheckBox al final
    layout->addWidget(checkBox);
    layout->setAlignment(Qt::AlignTop);
    connect(checkBox, &QCheckBox::stateChanged, this, &TaskWidget::onStateChanged);

}
void TaskWidget::setChecked(bool checked)
{
    checkBox->setChecked(checked);
}

bool TaskWidget::isChecked() const
{
    return checkBox->isChecked();
}
QString TaskWidget::getText() const {
    return label->text();
}

void TaskWidget::onStateChanged(int state)
{
    emit stateChanged(state == Qt::Checked);
}
