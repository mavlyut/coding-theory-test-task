# Метод порядковых статистик

Реализовано декодирование методом порядковых статистик.

## Запуск
```c++
std::vector<bool> decode(std::vector<bool> const& encoded, double stn_ratio, std::size_t t);
```
В качестве `encoded` подается закодированное слово, `stn_ratio` -- отношение сигнал/шум на бит
в дБ, `t` -- точность (максимально допустимое количество ошибок в кодовом слове). Возвращается
предполагаемое кодовое слово.

## Исследование
Метод был исследован на линейных (16,11)- и (32,21)-кодах с параметрами `stn_ratio in [-0.25; 6.25]` и
точностью от 0 до 3 _для канала с аддитивным белым гауссовым шумом_.

Графики зависимости вероятности ошибки от отношения сигнал/шум на бит.

![img1](files/Линейный%20(16,%2011)-код.png)
![img2](files/Линейный%20(32,%2021)-код.png)

Статистические данные можно найти по [ссылке](https://docs.google.com/spreadsheets/d/1PS6VEk52_fhZ3wfI7l45s5bajXU3JejWTIMJk9NVYyA/edit?usp=sharing)

По графикам можно заметить, что вероятность ошибки убывает по ОСШ. Также при больших `t` наблюдается
тенденция к росту вероятности ошибки.

Также хочется отметить, что при `stn_ration > 6` вероятность ошибки была околонулевой. Это может
быть связано с выбором слишком малых `t`. При `stn_ratio < 0` эта вероятность довольно велика, т.к. пропускная
способность канала с АБГШ = `-ln2` (при ОСШ меньше этого параметра добиться надежной передачи невозможно, так что
вероятность ошибок близится к 1).
