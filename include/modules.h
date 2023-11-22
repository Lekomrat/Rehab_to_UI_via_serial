#include "HX711.h"
#include <DFilters.h>
#include "pinmap.h"

const int LEFT_STOPA_1_SCALE = 1;
const int LEFT_STOPA_2_SCALE = 2;
const int LEFT_STOPA_3_SCALE = 3;

HX711 left_stopa_1;
HX711 left_stopa_2;
HX711 left_stopa_3;

double all_units[3] {}; 

void setupScales(){
    left_stopa_1.begin(PIN_LEFT_STOPA_1_DT, PIN_LEFT_STOPA_1_SCK);
    left_stopa_1.set_gain(128);  
    left_stopa_1.set_scale(LEFT_STOPA_1_SCALE); // установка калибровочного коэфф.
    left_stopa_1.tare(); // сбросить значения тензодатчика в 0

    left_stopa_2.begin(PIN_LEFT_STOPA_2_DT, PIN_LEFT_STOPA_2_SCK);
    left_stopa_2.set_gain(128);  
    left_stopa_2.set_scale(LEFT_STOPA_2_SCALE);
    left_stopa_2.tare();

    left_stopa_3.begin(PIN_LEFT_STOPA_3_DT, PIN_LEFT_STOPA_3_SCK);
    left_stopa_3.set_gain(128);  
    left_stopa_3.set_scale(LEFT_STOPA_3_SCALE);
    left_stopa_3.tare();
}

double getLeftStopa1Raw(){ // фильтрация полученных значений
    static Median_filter<7, double> _med_f;
    static EMA_filter _ema_f(0.1);

    static double _stopa_1_raw;

    if(left_stopa_1.is_ready()) _stopa_1_raw = _ema_f.filtered(_med_f.filtered(left_stopa_1.get_units(1)));
    return _stopa_1_raw;
}

double getLeftStopa1(){  //перевод в единицы СИ 
    return (getLeftStopa1Raw() / 1000.0) * 9.8;
}

double getLeftStopa2Raw(){
    static Median_filter<7, double> _med_f;
    static EMA_filter _ema_f(0.1);

    static double _stopa_2_raw;

    if(left_stopa_2.is_ready()) _stopa_2_raw = _ema_f.filtered(_med_f.filtered(left_stopa_2.get_units(1)));
    return _stopa_2_raw;
}

double getLeftStopa2(){
    return (getLeftStopa2Raw() / 1000.0) * 9.8;
}

double getLeftStopa3Raw(){
    static Median_filter<7, double> _med_f;
    static EMA_filter _ema_f(0.1);

    static double _stopa_3_raw;

    if(left_stopa_3.is_ready()) _stopa_3_raw = _ema_f.filtered(_med_f.filtered(left_stopa_3.get_units(1)));
    return _stopa_3_raw;
}

double getLeftStopa3(){
    return (getLeftStopa3Raw() / 1000.0) * 9.8;  
}

double getMassive(){
    all_units[0] = getLeftStopa1();
    all_units[1] = getLeftStopa2();
    all_units[3] = getLeftStopa3();
}



