
/*

Copyright 2011 Claus Ilginnis <Claus@Ilginnis.de>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.


*/

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

//#include "qgitrepository.h"
#include "qgitrevwalk.h"
#include "qgitcommit.h"
#include "qgitsignature.h"
#include "qgitrefs.h"

using namespace LibQGit2;


#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString repoPath = QFileDialog::getExistingDirectory(0,"Open a Repository", QDir::homePath());

    int err = 0;

    // add .git when not on a bare repository (yes, it's dirty but quick)
    if ( QFileInfo(repoPath).suffix().toLower() != "git" )
        repoPath += "/.git";

    // open the repo
    QGitRepository  repo;
    err = repo.open(QString("%1").arg(repoPath));
    if (err != 0)
    {
        QMessageBox::critical(0, "Error", "Unable to open Repository!");
        return;
    }

    // lookup commit in test repo by hash of HEAD commit
    QGitCommit commit;
    err = commit.lookup(repo,
                         QGitOId::fromString("cfb3b62519898e869be120ebc70800f1f2eb810b"));

    QGitRevWalk revWalker(repo);
    revWalker.sorting(GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE);
    err = revWalker.push(commit);

    ui->textCommitLogTest->appendPlainText(QString("Repository history:\n"));
    while ((revWalker.next(commit)) == GIT_SUCCESS)
    {
        QString message = commit.message();
        const git_signature * auth = commit.author().data();
        ui->textCommitLogTest->appendPlainText(QString("* %1 (%2 - %3)")
                                               .arg(message).arg(auth->name).arg(auth->email));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
