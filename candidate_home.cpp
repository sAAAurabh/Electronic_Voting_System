#include "candidate_home.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QFrame>

CandidateHomeWindow::CandidateHomeWindow(const QString& nid, QWidget* parent) : QWidget(parent){
    setWindowTitle("Candidate Dashboard");
    setFixedSize(550, 420);


    //title
    title = new QLabel("Candidate Dashboard", this);


    //title design
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color:#3498db; margin-bottom:10px;");

    QString info_style = "color:white; font-size:14px;";

    //profilebox
    QFrame *profile_box = new QFrame(this);

    //profile box design
    profile_box->setStyleSheet(
        "QFrame {"
        "border:1px solid #e0e0e0;"
        "border-radius:6px;"
        "padding:10px;"
        "}"
        );

    QGridLayout *profile_layout = new QGridLayout(profile_box);

    Candidate c;
    Admin a;
    a.find_candidate(nid.toStdString(), c);


    name_label = new QLabel(QString::fromStdString("Name : " + c.first + " " + c.last) );
    nid_label   = new QLabel(QString::fromStdString("NID: " + c.nid));
    party_label = new QLabel(QString::fromStdString("Part: " + c.party));
    vote_label  = new QLabel("Votes: 152");

    name_label->setStyleSheet(info_style);
    nid_label->setStyleSheet(info_style);
    party_label->setStyleSheet(info_style);
    vote_label->setStyleSheet(info_style);

    profile_layout->addWidget(name_label, 0, 0);
    profile_layout->addWidget(nid_label, 1, 0);
    profile_layout->addWidget(party_label, 0, 1);
    profile_layout->addWidget(vote_label, 1, 1);


    QFrame *manifesto_box = new QFrame(this);
    manifesto_box->setStyleSheet(
        "QFrame {"
        "border:1px solid #e0e0e0;"
        "border-radius:6px;"
        "padding:10px;"
        "}"
        );

    manifesto_label = new QLabel(this);
    manifesto_label->setText(QString::fromStdString(a.get_manifesto(c.nid)));

    manifesto_label->setWordWrap(true);
    manifesto_label->setStyleSheet(info_style);

    QVBoxLayout *manifesto_layout = new QVBoxLayout(manifesto_box);
    manifesto_layout->addWidget(manifesto_label);


    msg = new QLabel(this);
    msg->setAlignment(Qt::AlignCenter);
    msg->setStyleSheet("color:#27ae60; font-weight:bold;");

    logout_btn = new QPushButton("Logout", this);

    logout_btn->setStyleSheet(
        "background-color:#e74c3c;"
        "color:white;"
        "padding:8px;"
        "border-radius:6px;"
        );


    //adding to the grids layout
    grid = new QGridLayout(this);
    grid->setContentsMargins(40, 20, 40, 20);
    grid->setVerticalSpacing(12);

    grid->addWidget(title, 0, 0, 1, 2);

    grid->addWidget(profile_box, 1, 0, 1, 2);
    grid->addWidget(manifesto_box, 2, 0, 1, 2);

    grid->addWidget(logout_btn, 3, 0, 1, 2);

    grid->addWidget(msg, 4, 0, 1, 2);


    //signals and slots
    connect(logout_btn, &QPushButton::clicked,
            this, &CandidateHomeWindow::logout);
}



void CandidateHomeWindow::edit_profile()
{
    msg->setStyleSheet("color:#2563EB;");
    msg->setText("Edit profile clicked");
}

void CandidateHomeWindow::logout()
{
    this->close();
}