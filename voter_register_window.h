#pragma once

#include <QWidget>
#include <QFont>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>
#include "admin.h"
#include <QFileDialog>
#include <QPixmap>

class VoterRegisterWindow : public QWidget
{
    Q_OBJECT

public:
    VoterRegisterWindow(QWidget *parent = nullptr);

private slots:
    void register_user();
    void close_register();
    void clear_fields();
    void upload_photo();

private:
    QLabel *title, *f_name_label, *l_name_label, *nid_label, *pass_label, *msg, *f_name_warn, *l_name_warn, *pass_warn, *nid_warn;
    QLineEdit *f_name_input, *l_name_input, *nid_input, *pass_input;
    QLabel    *dob_label;
    QDateEdit *dob_input;
    QLabel    *dob_warn;
    QLabel    *gender_label;
    QComboBox *gender_input;
    QLabel    *gender_warn;
    QLabel      *photo_label;
    QPushButton *photo_btn;
    QLabel      *photo_warn;
    QLabel      *photo_preview;
    QString      photo_path;
    QPushButton *reg_btn, *back_btn;
    QGridLayout *grid;
    Admin admin;
};