#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>

class TaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskWidget(const QString &text, QWidget *parent = nullptr);

    bool isChecked() const;
    QString getText() const;
    void setChecked(bool checked);
signals:
    void stateChanged(bool checked);

private:
    QCheckBox *checkBox;
    QLabel *label;

private slots:
    void onStateChanged(int state);

};

#endif // TASKWIDGET_H
