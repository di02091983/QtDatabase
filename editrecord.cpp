#include "editrecord.h"
#include "ui_editrecord.h"

bool showEditForm(EditData* data)
{
    EditRecord editRecord;

    editRecord.ui->edId->setValue(data->id);
    editRecord.ui->edName->setText(data->name);
    editRecord.ui->edDone->setChecked(data->done);

    if(editRecord.exec() == QDialog::Accepted)
    {
        data->id = editRecord.ui->edId->value();
        data->name = editRecord.ui->edName->text();
        data->done = editRecord.ui->edDone->isChecked();

        return true;
    }
    return false;
}

EditRecord::EditRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditRecord)
{
    ui->setupUi(this);
}

EditRecord::~EditRecord()
{
    delete ui;
}
