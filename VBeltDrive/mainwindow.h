#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QList>
#include <QMessageBox>
#include <QRegExpValidator>
#include <stdexcept>
#include <math.h>

namespace Ui {
class VBeltWnd;
}

class VBeltWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit VBeltWnd(QWidget *parent = 0);
    ~VBeltWnd();

    // Расчет данных
    void Calculate();

    // Вывод результатов
    void ShowResut();

    // Выбор параметров шкива
    void ShkivParam();

    // Вывод параметров шкива
    void ShowShkivParam();

    // Выбор угла канавки шкива
    int ShkivAngle(const float dp);

    // Подбор стандартного диаметра шкива
    // или стандартной длинны ремня
    float ChoiceStandartValue(const float value, const QList<int> list);

private slots:
    void on_calcBtn_clicked();

    void on_beltSection_currentIndexChanged(const QString &arg1);

    void on_clearBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::VBeltWnd *ui;

    QList<int> constDiam;               // Стандартные диаметры
    QList<int> constBeltLength;         // Стандартные длины ремня

    enum BeltType {Z=0, A, B, C, D, E, EO};    // Стандартные типы сечения ремня

    float d1, d2, u,                    // Номинальные диаметры шкивов (dp)
                                        // и предаточное отношение (мм)
        P1, P2,                         // Мощьность на валах (кВт)
        T1, T2,                         // Момент на валах (Нм)
        n1, n2,                         // Частота вращения валов (об/мин)
        a, beltLength, beltSpeed,       // Межосевое расстояние, длина ремня (мм),
                                        // скорость ремня (м/с)
        Wd, f, e, b, h, M, r;           // Параметры канавки швива (мм)
    qint64 z;                           // Количество ремней, угол канавки шкива
    BeltType beltType;                  // Тип сечения ремня (A, B, C, D, E)
    int Angle1, Angle2;                 // Угол охвата меньшего шкива (град)
};

#endif // MAINWINDOW_H
