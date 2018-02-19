#include "mainwindow.h"
#include "ui_mainwindow.h"

VBeltWnd::VBeltWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VBeltWnd)
{
    ui->setupUi(this);

    // Стандартные номинальные диаметры шкивов
    constDiam << 50 << 53 << 56 << 60 << 63 << 67 << 71 << 75 << 80
              << 85 << 90 << 95 << 100 << 106 << 112 << 118 << 125
              << 135 << 140 << 150 << 160 << 170 << 180 << 190 << 200
              << 224 << 236 << 250 << 265 << 280 << 300 << 315 << 335
              << 355 << 375 << 400 << 425 << 450 << 475 << 500 << 530
              << 560 << 600 << 620 << 630 << 670 << 710 << 750 << 800
              << 850 << 900 << 950 << 1000 << 1060 << 1120 << 1180
              << 1250 << 1320 << 1400 << 1500 << 1600 << 1700 << 1800
              << 1900 << 2000 << 2120 << 2240 << 2360 << 2500 << 2650
              << 2800 << 3000 << 3150 << 3550 << 3750 << 4000;

    foreach (int str, constDiam)
    {
        ui->dVed->addItem(QString::number(str));
    }

    // Стандартные длины ремня
    constBeltLength << 400 << 425 << 450 << 475 << 500 << 530 << 560
                    << 600  << 630 << 670 << 710 << 750 << 800 << 850
                    << 900 << 950 << 1000 << 1060 << 1120 << 1180
                    << 1320 << 1400 << 1500 << 1600 << 1700 << 1800
                    << 1900 << 2000 << 2120 << 2240 << 2360 << 2500
                    << 2650 << 2800 << 3000 << 3150 << 3350 << 3550
                    << 3750 << 4000 << 4250 << 4500 << 4750 << 5000
                    << 5300 << 5600 << 6000 << 6300 << 6700 << 7100
                    << 7500 << 8000 << 8500 << 9000 << 9500 << 10000
                    << 10600 << 11200 << 11800 << 13200 << 14000
                    << 15000 << 16000 << 17000 << 18000;

    // Фильтрация ввода
    // От 1 до 5 чисел до точки и 1 после
    QRegExp rx("^[0-9]{1,5}[.][0-9]{1}");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->nVed->setValidator(validator);
    ui->pVed->setValidator(validator);
    ui->aPred->setValidator(validator);
    // От 1 до 5 чисел до точки и 3 после
    QRegExp r("^[0-9]{1,5}[.][0-9]{3}");
    QRegExpValidator *validat = new QRegExpValidator(r, this);
    ui->uPered->setValidator(validat);
}

VBeltWnd::~VBeltWnd()
{
    delete ui;
}

void VBeltWnd::on_calcBtn_clicked()
{
    // Считать начальные данные
    d1 = ui->dVed->currentText().toFloat();
    n1 = ui->nVed->text().toFloat();
    u = ui->uPered->text().toFloat();
    P1 = ui->pVed->text().toFloat();
    a = ui->aPred->text().toFloat();
    beltType = (BeltType)ui->beltSection->currentIndex();

    // Выполнить расчет
    try
    {
        Calculate();
    }
    // Перехват исключительной ситуации
    catch (std::exception &e)
    {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

    // Выбрать параметры шкива
    ShkivParam();

    // Вывод результата
    ShowResut();    

    // Вывод параметров шкива
    ShowShkivParam();
}

void VBeltWnd::Calculate()
{
    // Расчет данных

    // Приближенный номинальный диаметр ведомого шкива
    d2 = d1 * u;
    // Выбор из стандартного ряда
    d2 = ChoiceStandartValue(d2, constDiam);

    // Фактическое передаточное отношение:
    float Ufact = d2/(0.99 * d1);

    // Проверка на расхождение (допускается не более 2%)
    float delta = abs(Ufact - u)/u;

    // Если превышает, то необходимо
    // скорректировать диаметры шкивов
    if (delta > 2)
    {
        // Уменьшить диаметр ведомого шкива до предыдущего
        // стандартного значения
        int i = constDiam.indexOf(d2);
        d2 = constDiam.at(i-1);
    }

    // Длина ремня
    beltLength = (2*a) + ((M_PI/2)*(d1+d2)) + (pow(abs(d2-d1), 2)/(4*a));
    // Выбор из стандартного ряда
    beltLength = ChoiceStandartValue(beltLength, constBeltLength);

    // Вычислить вспомогательные велечины
    float w = (M_PI * (d1+d2))/2;
    float q = pow((abs(d2-d1)/2), 2);
    // Уточнить межосевое
    a = 0.25*((beltLength - w) + sqrt(pow((beltLength-w), 2) - (8*q)));
    // Мощность на ведомом валу
    P2 = P1/u;
    // Частота вращения ведомого вала
    n2 = n1/u;
    // Момент на ведущем и ведомом валу
    T1 = (30*P1)/(M_PI*n1);
    T2 = (30*P2)/(M_PI*n2);
    // Число ремней
    z = (1.2 * P1)/(4.5*0.95*0.96*0.96);
    // Скорость ремня
    beltSpeed = (M_PI*d1*n1)/60000;
    if (beltSpeed > 30) QMessageBox::warning(this, "Предупрждение",
                "Скрость ремня выше 30 м/с./nСкорректируйте начальные данные.",
                QMessageBox::Ok);
}

void VBeltWnd::ShowResut()
{
    // Вывод результата
    ui->d1_Lbl->setText(QString("%1  мм").arg(d1, 0, 'f', 0));
    ui->d2_Lbl->setText(QString("%1  мм").arg(d2, 0, 'f', 0));
    ui->T1_Lbl->setText(QString("%1  Нм").arg(T1, 0, 'f', 2));
    ui->T2_Lbl->setText(QString("%1  Нм").arg(T2, 0, 'f', 2));
    ui->n1_Lbl->setText(QString("%1  кВт").arg(n1, 0, 'f', 1));
    ui->n2_Lbl->setText(QString("%1  кВт").arg(n2, 0, 'f', 1));
    ui->a_Lbl->setText(QString("%1  мм").arg(a, 0, 'f', 0));
    ui->lBelt_Lbl->setText(QString("%1  мм").arg(beltLength, 0, 'f', 0));
    ui->sBelt_Lbl->setText(QString("%1  м/с").arg(beltSpeed, 0, 'f', 1));
    ui->zBelt_Lbl->setText(QString::number(z));
}

void VBeltWnd::ShkivParam()
{
    // Выбор параметров шкива
    switch (beltType) {
    case BeltType::Z:
        Wd = 8.5;   f = 8;      e = 12;     b = 2.5;
        h = 7;      r = 0.5;
        break;
    case BeltType::A:
        Wd = 11.0;  f = 10;     e = 15;     b = 3.3;
        h = 8.7;    r = 1.0;
        break;
    case BeltType::B:
        Wd = 14;    f = 12.5;   e = 19;     b = 4.2;
        h = 10.8;   r = 1.0;
        break;
    case BeltType::C:
        Wd = 19;    f = 17;     e = 25.5;   b = 5.7;
        h = 14.3;   r = 1.5;
        break;
    case BeltType::D:
        Wd = 27;    f = 24;     e = 37;     b = 8.1;
        h = 19.9;   r = 2.0;
        break;
    case BeltType::E:
        Wd = 32;    f = 29;     e = 44.5;   b = 9.6;
        h = 23.4;   r = 2.0;
        break;
    case BeltType::EO:
        Wd = 42;    f = 38;     e = 58;     b = 12.5;
        h = 30.5;   r = 2.5;
        break;
    }
    M = (z-1)*e +(2*f);

    // Выбор угла канавки шкива
    Angle1 = ShkivAngle(d1);
    Angle2 = ShkivAngle(d2);
}

void VBeltWnd::ShowShkivParam()
{
    // Вывод параметров шкива
    ui->Wd_Lbl->setText(QString("%1  мм").arg(Wd, 0, 'f', 1));
    ui->f_Lbl->setText(QString("%1  мм").arg(f, 0, 'f', 1));
    ui->e_Lbl->setText(QString("%1  мм").arg(e, 0, 'f', 1));
    ui->b_Lbl->setText(QString("%1  мм").arg(b, 0, 'f', 1));
    ui->h_Lbl->setText(QString("%1  мм").arg(h, 0, 'f', 1));
    ui->Angle1_Lbl->setText(QString("%1  град").arg(Angle1));
    ui->Angle2_Lbl->setText(QString("%1  град").arg(Angle2));
    ui->M_Lbl->setText(QString("%1  мм").arg(M, 0, 'f', 0));
    ui->r_Lbl->setText(QString("%1  мм").arg(r, 0, 'f', 1));
}

int VBeltWnd::ShkivAngle(const float dp)
{
    // Выбор угла канавки шкива
    switch (beltType) {
    case BeltType::Z:
        if ((50 <= dp) && (dp <= 71)) return 34;
        else if ((71 < dp) && (dp <= 100)) return 36;
        else if ((100 < dp) && (dp <= 160)) return 38;
        else return 40;
        break;
    case BeltType::A:
        if ((75 <= dp) && (dp <= 112)) return 34;
        else if ((112 < dp) && (dp <= 160)) return 36;
        else if ((160 < dp) && (dp <= 401)) return 38;
        else return 40;
        break;
    case BeltType::B:
        if ((125 <= dp) && (dp <= 160)) return 34;
        else if ((160 < dp) && (dp <= 224)) return 36;
        else if ((224 < dp) && (dp <= 501)) return 38;
        else return 40;
        break;
    case BeltType::C:
        if ((200 <= dp) && (dp <= 315)) return 36;
        else if ((315 < dp) && (dp <= 630)) return 38;
        else return 40;
        break;
    case BeltType::D:
        if ((315 <= dp) && (dp <= 450)) return 36;
        else if ((450 < dp) && (dp <= 900)) return 38;
        else return 40;
        break;
    case BeltType::E:
        if ((500 <= dp) && (dp <= 560)) return 36;
        else if ((560 < dp) && (dp <= 11200)) return 38;
        else return 40;
        break;
    case BeltType::EO:
        if ((800 <= dp) && (dp <= 1400)) return 38;
        else return 40;
        break;
    default:
        return 0;
        break;
    }
}

float VBeltWnd::ChoiceStandartValue(const float value, const QList<int> list)
{
    // Подбор стандартного диаметра шкива
    // или стандартной длинны ремня
    int start = 0;
    int end = list.length();
    int middle = start + ((end - start)/2);

    while (end - start > 1)
    {
        if (value > list.at(middle))
        {
            start = middle;
            middle = start + ((end - start)/2);
        }
        else if (list.at(middle) > value)
        {
            end = middle;
            middle = start + ((end - start)/2);
        }
        else return value;
    }

    int delta1 = abs(value - list.at(start));
    int delta2 = abs(list.at(end) - value);

    if (delta2 > delta1) return list.at(start);
    else return list.at(end);
}

void VBeltWnd::on_beltSection_currentIndexChanged(const QString &arg1)
{
    // Изменен тип сечения ремня
    beltType = (BeltType)ui->beltSection->currentIndex();

    switch (beltType) {
    case BeltType::A:
        if (ui->dVed->currentIndex() < 7)
        {
            ui->dVed->setCurrentIndex(7);   // 75 мм
        }
        break;
    case BeltType::B:
        if (ui->dVed->currentIndex() < 16)
        {
            ui->dVed->setCurrentIndex(16);  // 125 мм
        }
        break;
    case BeltType::C:
        if (ui->dVed->currentIndex() < 24)
        {
            ui->dVed->setCurrentIndex(24);  // 200 мм
        }
        break;
    case BeltType::D:
        if (ui->dVed->currentIndex() < 31)
        {
            ui->dVed->setCurrentIndex(31);  // 315 мм
        }
        break;
    case BeltType::E:
        if (ui->dVed->currentIndex() < 39)
        {
            ui->dVed->setCurrentIndex(39);  // 500 мм
        }
        break;
    case BeltType::EO:
        if (ui->dVed->currentIndex() < 48)
        {
            ui->dVed->setCurrentIndex(48);  // 800 мм
        }
        break;
    default:
        break;
    }

    Q_UNUSED(arg1);
}

void VBeltWnd::on_clearBtn_clicked()
{
    // Очистить все данные (новый расчет)
    ui->Angle1_Lbl->setText("0");
    ui->Angle2_Lbl->setText("0");
    ui->aPred->setText("0");
    ui->a_Lbl->setText("0");
    ui->b_Lbl->setText("0");
    ui->d1_Lbl->setText("0");
    ui->d2_Lbl->setText("0");
    ui->e_Lbl->setText("0");
    ui->f_Lbl->setText("0");
    ui->h_Lbl->setText("0");
    ui->lBelt_Lbl->setText("0");
    ui->M_Lbl->setText("0");
    ui->n1_Lbl->setText("0");
    ui->n2_Lbl->setText("0");
    ui->nVed->setText("0");
    ui->pVed->setText("0");
    ui->r_Lbl->setText("0");
    ui->sBelt_Lbl->setText("0");
    ui->T1_Lbl->setText("0");
    ui->T2_Lbl->setText("0");
    ui->uPered->setText("0");
    ui->Wd_Lbl->setText("0");
    ui->zBelt_Lbl->setText("0");
}

void VBeltWnd::on_pushButton_clicked()
{
    // Информация о программе

    QString aboutText;
    aboutText = "         V-Belt Drive  v 1.0.0  \n\n";
    aboutText += "Автор  : \tmasterarrow\n\n";
    aboutText += "email  : \tmasterarrow@mail.ru\n\n";
    aboutText += "          Copyright © 2017\n";

    QMessageBox::about(this, "О программе", aboutText);
}
