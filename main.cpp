#include <QApplication>
#include "voter_login_window.h"
#include "candidate_login_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //VoterLoginWindow w;
    CandidateLoginWindow w;
    w.show();
    return a.exec();
}