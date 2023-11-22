// Библиотека цифровых фильтров значений

#ifndef DFILTERS_H
#define DFILTERS_H

// Класс фильтра "Экспоненциальное бегущее среднее"
class EMA_filter{
    public:
        EMA_filter(double coef){
            _coef = coef;
        }

        double filtered (double value){
            _value = value;
            _output += (_value - _output) * _coef;
            return _output;
        }

    private:
        double _coef;
        double _value;
        double _output;    
};

// Класс фильтра "Бегущее среднее арифметическое"
template < int SIZE, typename VAR_TYPES >
class RMA_filter{
    public: 
        VAR_TYPES filtered(VAR_TYPES _input){
            if(++_counter >= SIZE) _counter = 0;
            _avarage -= _values[_counter];
            _avarage += _input;
            _values[_counter] = _input;
            return _avarage / SIZE;
        }

    private:
        VAR_TYPES _values[SIZE];
        int _counter = 0;
        VAR_TYPES _avarage = 0;
};

//Класс фильтра "Медиана заданного порядка"
template < int SIZE, typename VAR_TYPES >
class Median_filter{
public:
    VAR_TYPES filtered(VAR_TYPES value) {
        buffer[_count] = value;
        if((_count < _order - 1) && (buffer[_count] > buffer[_count + 1])){
            for(int i = _count; i < _order - 1; i++){
                if(buffer[i] > buffer[i + 1]){
                    VAR_TYPES buff = buffer[i];
                    buffer[i] = buffer[i + 1];
                    buffer[i + 1] = buff;
                }
            }
        } 
        else{
            if((_count > 0) and (buffer[_count - 1] > buffer[_count])){
                for(int i = _count; i > 0; i--){
                    if(buffer[i] < buffer[i - 1]){
                        VAR_TYPES buff = buffer[i];
                        buffer[i] = buffer[i - 1];
                        buffer[i - 1] = buff;
                    }
                }
            }
        }
        if (++_count >= _order) _count = 0;
        return buffer[(int)_order / 2];
    }
private:
    VAR_TYPES buffer[SIZE];
    byte _count = 0;
    byte _order = SIZE;
};

#endif