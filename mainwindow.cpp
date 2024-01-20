#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->input, &QLineEdit::returnPressed, this, &MainWindow::on_input_returnPressed);
    // Cargar las tareas guardadas
    loadTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadTasks()
{
    QSettings settings("TuEmpresa", "TuAplicacion");
    QStringList tasks = settings.value("tasks").toStringList();

    // Cargar las tareas en el QListWidget
    ui->listWidget->addItems(tasks);
}

void MainWindow::saveTasks()
{
    QSettings settings("TuEmpresa", "TuAplicacion");
    QStringList tasks;

    // Obtener las tareas del QListWidget y agregarlas a la lista
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        tasks << ui->listWidget->item(i)->text();
    }

    // Guardar las tareas en el archivo
    settings.setValue("tasks", tasks);
}

void MainWindow::on_addTask_clicked()
{
    QString input = ui->input->text();
    if (!input.isEmpty()) {
        ui->listWidget->addItem(input);
        ui->input->clear();
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

