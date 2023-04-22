#ifndef EDITRECORD_H
#define EDITRECORD_H

#include <QDialog>

struct EditData
{
    qint32 id;
    QString name;
    bool done;
};

namespace Ui {
class EditRecord;
}

class EditRecord : public QDialog
{
    Q_OBJECT

public:    
    explicit EditRecord(QWidget *parent = nullptr);
    ~EditRecord();
private:    
    Ui::EditRecord *ui;
friend bool showEditForm(EditData* data);
};

bool showEditForm(EditData* data);
#endif // EDITRECORD_H
