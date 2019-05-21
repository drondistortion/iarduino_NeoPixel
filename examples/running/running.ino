/*  Скетч демонстрирует перелив всех цветов радуги
 *  Подходит для любого количества светодиодов
 *  Номер вывода Arduino и количество используемых светодиодов указывается при объявлении объекта led(вывод,количество)
 *  Значение константы z определяет задержку в мс, чем выше значение, тем медленнее перелив
 */

#include <iarduino_NeoPixel.h>                       //  Подключаем библиотеку iarduino_NeoPixel для работы со светодиодами NeoPixel
iarduino_NeoPixel led(6,25);                         //  Объявляем объект LED указывая (№ вывода Arduino к которому подключены светодиоды NeoPixel, количество используемых светодиодов)

      uint8_t j;                                     //  Объявляем переменную для хранения значения сдвига спектра цветов для всех светодиодов (от 0 до 255)
      uint8_t k;                                     //  Объявляем переменную для хранения положения сдвига спектра цвета для каждого светодиода на спектре j (зависит от количества светодиодов)
      uint8_t r, g, b;                               //  Объявляем переменную для хранения цветов RGB для каждого светодиода
const uint8_t z=5;                                   //  Определяем константу указывающую задержку в мс (чем выше значение, тем медленнее перелив цветов) 

void setup(){
    Serial.begin(9600);                              //  Инициируем передачу данных в монитор последовательного порта
    if(led.begin()) {Serial.println("Ok");}          //  Инициируем работу со светодиодами и выводим сообщение об успешной инициализации
    else            {Serial.println("Err");}         //  Если инициализация невозможна (не хватает памяти для хранения цветов всех светодиодов), то выводим сообщение об ошибке
}

void loop(){
    j++;                                             //  Смещаем спектр цветов для всех светодиодов
    for(uint16_t i=0; i<led.count(); i++){           //  Проходим по всем светодиодам
        k=((uint16_t)(i*256/led.count())+j);         //  Определяем положение очередного светодиода на смещённом спектре цветов
        if(k<85) {        b=0; r=k*3; g=255-r;}else  //  Перелив от зелёного к красному, через жёлтый
        if(k<170){k-=85;  g=0; b=k*3; r=255-b;}else  //  Перелив от красного к синему  , через фиолетовый
                 {k-=170; r=0; g=k*3; b=255-g;}      //  Перелив от синего   к зелёному, через голубой
        led.setColor(i, r,g,b);                      //  Устанавливаем выбранный цвет для очередного светодиода
    }   led.write();                                 //  Записываем цвета всех светодиодов
    delay(z);                                        //  Устанавливаем задержку
}
