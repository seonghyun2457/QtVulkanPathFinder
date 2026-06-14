#include "GroupSolver.h"

#include "ui_GroupSolver.h"

GroupSolver::GroupSolver(QWidget* parent)
    : QGroupBox(parent),
      ui(new Ui::GroupSolver) {
    ui->setupUi(this);

    // CONNECT
    connect(ui->rbDijkstra, &QRadioButton::clicked, this, &GroupSolver::setDijkstra);
    connect(ui->rbAStar, &QRadioButton::clicked, this, &GroupSolver::setAstar);

    ui->rbDijkstra->click();
}

GroupSolver::~GroupSolver() {
    delete ui;
}

void GroupSolver::setDijkstra() {
    emit solverChanged(eSolver::Dijkstra);
}

void GroupSolver::setAstar() {
    emit solverChanged(eSolver::AStar);
}