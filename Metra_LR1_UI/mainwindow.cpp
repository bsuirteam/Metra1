#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFont fontText("Verdana", 14);
    QFont fontHeaders("Verdana", 12, QFont::Bold);
    QFont fontTable("Verdana", 12);
    QFont fontCode("Courier New", 10);

    this->setWindowTitle("Holsted Measures");
    this->setWindowIcon(QIcon("..\\..\\..\\images\\icon.ico"));
    this->setFixedSize(1540, 750);

    ui->labelDict->setFont(fontText);
    ui->labelLength->setFont(fontText);
    ui->labelVolume->setFont(fontText);

    ui->buttonOpenFile->setFont(fontText);
    ui->buttonRefresh->setFont(fontText);
    ui->buttonSave->setFont(fontText);

    ui->textFile->setReadOnly(true);
    ui->textFile->setFont(fontCode);

    ui->textDict->setReadOnly(true);
    ui->textDict->setText("\nn = " + QString::number(_n_1 + _n_2));
    ui->textDict->setFont(fontText);
    ui->textDict->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ui->textLength->setReadOnly(true);
    ui->textLength->setText("\nN = " + QString::number(_N_1 + _N_2));
    ui->textLength->setFont(fontText);
    ui->textLength->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ui->textVolume->setReadOnly(true);
    ui->textVolume->setText("\nV = " + ((_n_1 + _n_2 != 0) ? QString::number((int) ( (_N_1 + _N_2) * log2(_n_1 + _n_2) ) ) : "0"));
    ui->textVolume->setFont(fontText);
    ui->textVolume->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ui->tableOperators->setColumnCount(3);
    ui->tableOperators->setHorizontalHeaderLabels({"j", "Operator", "f_1j"});
    ui->tableOperators->horizontalHeader()->setStretchLastSection(false);
    ui->tableOperators->verticalHeader()->setVisible(false);
    ui->tableOperators->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableOperators->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableOperators->setFont(fontTable);
    ui->tableOperators->horizontalHeader()->setFont(fontHeaders);

    ui->tableOperands->setColumnCount(3);
    ui->tableOperands->setHorizontalHeaderLabels( {"i", "Operand", "f_2i"});
    ui->tableOperands->horizontalHeader()->setStretchLastSection(false);
    ui->tableOperands->verticalHeader()->setVisible(false);
    ui->tableOperands->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableOperands->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableOperands->setFont(fontTable);
    ui->tableOperands->horizontalHeader()->setFont(fontHeaders);

    connect(ui->buttonOpenFile, &QPushButton::clicked, this, &MainWindow::OpenFileSlot);
    connect(ui->buttonRefresh, &QPushButton::clicked, this, &MainWindow::RefreshSlot);
    connect(ui->buttonSave, &QPushButton::clicked, this, &MainWindow::SaveTablesSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetText()
{
    if(_fileName.isEmpty()){
        QMessageBox::warning(this, "File Problem", "No opened File!");
        return;
    }

    QFile file(_fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        ui->textFile->setPlainText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(this, "File Problem", "Can't Open File!");
    }
}

void MainWindow::SetHolsted()
{
    QMap<QString, int> operatorsCount;

    operatorsCount.insert("+", 10);
    operatorsCount.insert("-", 7);
    operatorsCount.insert("*", 5);
    operatorsCount.insert("/", 3);

    QMap<QString, int> operandsCount;

    operandsCount.insert("a", 4);
    operandsCount.insert("b", 3);
    operandsCount.insert("3", 2);

    this->SetTableOperators(operatorsCount);
    this->SetTableOperands(operandsCount);


    ui->textDict->setText("\nn = " + QString::number(_n_1 + _n_2));
    ui->textLength->setText("\nN = " + QString::number(_N_1 + _N_2));
    ui->textVolume->setText("\nV = " + ((_n_1 + _n_2 != 0) ? QString::number((int) ( (_N_1 + _N_2) * log2(_n_1 + _n_2) ) ) : "0"));
}

void MainWindow::SetTableOperators(const QMap<QString, int> &operators)
{
    ui->tableOperators->clear();
    ui->tableOperators->setRowCount(operators.size() + 1);
    ui->tableOperators->setColumnCount(3);

    QStringList headers = {"j", "Operator", "f_1j"};
    ui->tableOperators->setHorizontalHeaderLabels(headers);
    ui->tableOperators->horizontalHeader()->setStretchLastSection(true);

    QTableWidgetItem *temp;
    int row = 0;
    int count = 0;
    foreach (const QString &op, operators.keys()) {
        temp =  new QTableWidgetItem(QString::number(row + 1));
        temp->setTextAlignment(Qt::AlignCenter);
        ui->tableOperators->setItem(row, 0, temp);

        temp =  new QTableWidgetItem(op);
        temp->setTextAlignment(Qt::AlignCenter);
        ui->tableOperators->setItem(row, 1, temp);

        temp = new QTableWidgetItem(QString::number(operators.value(op)));
        temp->setTextAlignment(Qt::AlignCenter);
        ui->tableOperators->setItem(row, 2, temp);

        count += operators.value(op);
        ++row;
    }

    ui->tableOperators->setItem(row, 0, new QTableWidgetItem("n_1 = " + (QString::number(row))));
    _n_1 = row;
    ui->tableOperators->setItem(row, 2, new QTableWidgetItem("N_1 = " + QString::number(count)));
    _N_1 = count;

    ui->tableOperators->resizeColumnsToContents();
    ui->tableOperators->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::SetTableOperands(const QMap<QString, int> &operands)
{
    ui->tableOperands->clear();
    ui->tableOperands->setRowCount(operands.size() + 1);
    ui->tableOperands->setColumnCount(3);

    QStringList headers = {"i", "Operand", "f_2i"};
    ui->tableOperands->setHorizontalHeaderLabels(headers);
    ui->tableOperands->horizontalHeader()->setStretchLastSection(true);

    QTableWidgetItem *temp;
    int row = 0;
    int count = 0;
    foreach (const QString &op, operands.keys()) {
        temp =  new QTableWidgetItem(QString::number(row + 1));
        temp->setTextAlignment(Qt::AlignCenter);
        ui->tableOperands->setItem(row, 0, temp);

        temp =   new QTableWidgetItem(op);
        temp->setTextAlignment(Qt::AlignCenter);
        ui->tableOperands->setItem(row, 1, temp);

        temp = new QTableWidgetItem(QString::number(operands.value(op)));
        temp->setTextAlignment(Qt::AlignCenter);
        ui->tableOperands->setItem(row, 2, temp);

        count += operands.value(op);
        ++row;
    }

    ui->tableOperands->setItem(row, 0, new QTableWidgetItem("n_2 = " + (QString::number(row))));
    _n_2 = row;
    ui->tableOperands->setItem(row, 2, new QTableWidgetItem("N_2 = " + QString::number(count)));
    _N_2 = count;

    ui->tableOperands->resizeColumnsToContents();
    ui->tableOperands->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::SaveTable(QTableWidget *table, const QString &filePath)
{
    if (!table) {
        QMessageBox::warning(this, "Save Error", "Table is Empty!");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Save Error", "Can't open file!");
        return;
    }

    QTextStream out(&file);

    QVector<int> colWidths(table->columnCount(), 0);
    for (int col = 0; col < table->columnCount(); ++col) {
        int maxLen = table->horizontalHeaderItem(col)->text().length();
        for (int row = 0; row < table->rowCount(); ++row) {
            QTableWidgetItem *item = table->item(row, col);
            if (item)
                maxLen = qMax(maxLen, item->text().length());
        }
        colWidths[col] = maxLen + 2;
    }

    auto writeLine = [&]() {
        out << "+";
        for (int w : colWidths) {
            out << QString(w, '-') << "+";
        }
        out << "\n";
    };

    auto writeRow = [&](const QStringList &rowData) {
        out << "|";
        for (int i = 0; i < rowData.size(); ++i) {
            QString s = " " + rowData[i].left(colWidths[i]-2).leftJustified(colWidths[i]-2) + " ";
            out << s << "|";
        }
        out << "\n";
    };

    writeLine();

    QStringList headers;
    for (int col = 0; col < table->columnCount(); ++col)
        headers << table->horizontalHeaderItem(col)->text();
    writeRow(headers);

    writeLine();

    for (int row = 0; row < table->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *item = table->item(row, col);
            rowData << (item ? item->text() : "");
        }
        writeRow(rowData);
    }

    writeLine();

    file.close();

    QMessageBox::information(this, "Saved", "Table Saved To File:");
}

void MainWindow::OpenFileSlot()
{
    QString initDir = "..\\..\\..\\analyz";
    QStringList filters;
    filters << "Scala (*.scala *.sc)"
            << "All files (*.*)";

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Choose File",
        initDir,
        filters.join(";;")
        );

    if(fileName.isEmpty()){
        QMessageBox::warning(this, "File Problem", "No such file!");
        return;
    }

    _fileName = fileName;

    this->RefreshSlot();
}

void MainWindow::RefreshSlot()
{
    this->SetText();
    this->SetHolsted();
}

void MainWindow::SaveTablesSlot()
{
    this->SaveTable(ui->tableOperators, "..\\..\\..\\res\\operators.txt");
    this->SaveTable(ui->tableOperands, "..\\..\\..\\res\\operands.txt");
}


