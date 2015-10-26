////////////////////////////////////////////////////////////////////////////////
#include "editwindow.hpp"
#include "eventmodel.hpp"

#include <QMessageBox>

////////////////////////////////////////////////////////////////////////////////
EditWindow::EditWindow(QWidget* parent) : QWidget(parent),
    dialog(new QFileDialog(this))
{
    setupUi(this);

    sections->setModel(model);

    connect(name, &QLineEdit::textChanged, model, &EventModel::set_name);
    connect(model, &EventModel::name_changed, name, &QLineEdit::setText);

    connect(model, &EventModel::filename_changed, this, &EditWindow::set_button);
    connect(model, &EventModel::name_changed, this, &EditWindow::set_button);
    connect(model, &EventModel::dataChanged, this, &EditWindow::set_button);

    connect(clear, &QToolButton::clicked, this, &EditWindow::clear_clicked);
    connect(open, &QToolButton::clicked, this, &EditWindow::open_clicked);
    connect(save, &QToolButton::clicked, this, &EditWindow::save_clicked);
    connect(save_as, &QToolButton::clicked, this, &EditWindow::save_as_clicked);

    QHeaderView* header = sections->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    dialog->setConfirmOverwrite(true);
    dialog->setDefaultSuffix("xml");
    dialog->setNameFilters(QStringList() << "Event files (*.xml)" << "All files (*)");
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::clear_clicked()
{
    model->clear();
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::open_clicked()
try
{
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setAcceptMode(QFileDialog::AcceptOpen);

    if(dialog->exec() == QDialog::Accepted)
        model->open(dialog->selectedFiles().at(0));
}
catch(const QString& e)
{
    QMessageBox::critical(this, "Error", e);
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::save_clicked()
try
{
    model->save();
}
catch(const QString& e)
{
    QMessageBox::critical(this, "Error", e);
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::save_as_clicked()
try
{
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setAcceptMode(QFileDialog::AcceptSave);

    if(dialog->exec() == QDialog::Accepted)
        model->save_as(dialog->selectedFiles().at(0));
}
catch(const QString& e)
{
    QMessageBox::critical(this, "Error", e);
}

////////////////////////////////////////////////////////////////////////////////
void EditWindow::set_button()
{
    save->setEnabled(model->filename().size());
    save_as->setEnabled(model->name().size());
}
