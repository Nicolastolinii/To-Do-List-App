#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QSettings>
#include <QCheckBox>
#include "taskwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->input, &QLineEdit::returnPressed, this, &MainWindow::on_input_returnPressed);
    QListWidget *listWidget = ui->listWidget;
    // Cargar las tareas guardadas
    loadTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
    saveTasks();
}
void MainWindow::applyCheckBoxStyles(QCheckBox *checkBox)
{
    // Implementa aquí la lógica para aplicar los estilos al QCheckBox
    // Puedes utilizar setStyleSheet u otras propiedades según tus necesidades
}
void MainWindow::onTaskWidgetStateChanged(bool checked)
{
    // Obtener el widget que emitió la señal
    TaskWidget *senderWidget = qobject_cast<TaskWidget*>(sender());

    // Buscar el elemento correspondiente en el QListWidget
    int index = ui->listWidget->row(ui->listWidget->itemAt(senderWidget->pos()));

    if (index != -1) {
        // Obtener el elemento y tachar o destachar el texto según el estado del checkbox
        QListWidgetItem *item = ui->listWidget->item(index);
        QFont font = item->font();
        font.setStrikeOut(checked);  // Tacha el texto si el checkbox está marcado
        item->setFont(font);

    }

    // Agrega aquí cualquier otra lógica que desees ejecutar al cambiar el estado del widget
}
void MainWindow::loadTasks()
{
    QSettings settings("TuEmpresa", "TuAplicacion");
    QList<QVariant> taskList = settings.value("tasks").toList();

    // Borrar las tareas existentes en el QListWidget
    ui->listWidget->clear();

    // Cargar las tareas en el QListWidget
    for (const QVariant &taskVariant : taskList) {
        QVariantMap taskMap = taskVariant.toMap();

        QString taskText = taskMap["text"].toString();
        bool completed = taskMap["completed"].toBool();

        // Crear un nuevo elemento para el QListWidget
        QListWidgetItem *taskItem = new QListWidgetItem(ui->listWidget);
        taskItem->setText(taskText);

        // Crear un nuevo TaskWidget
        TaskWidget *taskWidget = new TaskWidget(taskText);

        // Establecer el estado del TaskWidget
        taskWidget->setChecked(completed);

        // Asignar el TaskWidget al elemento del QListWidget
        ui->listWidget->setItemWidget(taskItem, taskWidget);
        // Conectar la señal stateChanged del TaskWidget a la ranura onTaskWidgetStateChanged
        connect(taskWidget, &TaskWidget::stateChanged, this, &MainWindow::onTaskWidgetStateChanged);
        QFont font = taskItem->font();
        font.setStrikeOut(completed);
        taskItem->setFont(font);

    }
}

void MainWindow::saveTasks()
{
    QSettings settings("TuEmpresa", "TuAplicacion");
    QList<QVariant> taskList;

    // Obtener las tareas del QListWidget y agregarlas a la lista
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *taskItem = ui->listWidget->item(i);
        TaskWidget *taskWidget = qobject_cast<TaskWidget*>(ui->listWidget->itemWidget(taskItem));

        if (taskWidget) {
            QString taskText = taskItem->text();
            bool completed = taskWidget->isChecked(); // Obtener el estado del checkbox desde TaskWidget
            // Guardar la tarea y su estado de completado en la lista
            QVariantMap taskMap;
            taskMap.insert("text", taskText);
            taskMap.insert("completed", completed);
            taskList.append(taskMap);
        }
    }

    // Guardar las tareas en el archivo
    settings.setValue("tasks", taskList);
}

void MainWindow::on_addTask_clicked()
{
    QString input = ui->input->text();
    if (!input.isEmpty()) {
        // Crear un nuevo elemento para el QListWidget
        QListWidgetItem *taskItem = new QListWidgetItem(ui->listWidget);
        taskItem->setText(input);

        // Crear un nuevo TaskWidget
        TaskWidget *taskWidget = new TaskWidget(input);
        taskWidget->findChild<QCheckBox*>()->setMinimumSize(14, 14);

        // Asignar el TaskWidget al elemento del QListWidget
        ui->listWidget->setItemWidget(taskItem, taskWidget);
        connect(taskWidget, &TaskWidget::stateChanged, this, &MainWindow::onTaskWidgetStateChanged);

        // Limpiar el QLineEdit
        ui->input->clear();

        // Guardar las tareas
        saveTasks();
    }
}


void MainWindow::on_Delete_clicked()
{
    // Obtener el ítem seleccionado actualmente
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();

    // Verificar si hay un ítem seleccionado antes de intentar eliminarlo
    if (selectedItem) {
        // Eliminar el ítem seleccionado de la lista
        delete selectedItem;
        saveTasks();
    }
}

void MainWindow::on_input_returnPressed()
{
    // Llamar a la ranura existente para agregar tarea cuando se presiona Enter
    on_addTask_clicked();
}

void MainWindow::on_modify_clicked()
{
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
        // Obtener el texto actual del elemento seleccionado
        QString currentText = selectedItem->text();

        // Mostrar un cuadro de diálogo modal para editar el texto
        bool ok;
        QString modifiedText = QInputDialog::getText(this, tr("Modificar Tarea"), tr("Nuevo texto:"), QLineEdit::Normal, currentText, &ok);

        // Verificar si el usuario hizo clic en "Aceptar" en el cuadro de diálogo
        if (ok) {
            // Establecer el nuevo texto en el elemento seleccionado
            selectedItem->setText(modifiedText);
            saveTasks();
        }
    }
}


