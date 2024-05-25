// // Пины для подключения куба
// const int layerPins[] = {2, 3};   // Пины для управления слоями
// const int columnPins[] = {4, 5, 6, 7};   // Пины для управления столбцами

// // Массив для хранения состояния светодиодов
// bool ledState[2][2][2] = {{{false, false}, {false, false}},
//                            {{false, false}, {false, false}}};

// // Функция для инициализации пинов
// void setup() {
//   // Устанавливаем пины как OUTPUT
//   for (int i = 0; i < 2; i++) {
//     pinMode(layerPins[i], OUTPUT);
//   }
//   for (int i = 0; i < 4; i++) {
//     pinMode(columnPins[i], OUTPUT);
//   }
// }

// // Функция для включения светодиода в кубе
// void turnOnLED(int layer, int row, int column) {
//   // Выключаем все светодиоды
//   turnOffAllLEDs();
//   // Включаем нужный светодиод
//   digitalWrite(layerPins[layer], HIGH);
//   digitalWrite(columnPins[row], HIGH);
//   digitalWrite(columnPins[column + 2], HIGH);
//   // Обновляем состояние светодиода
//   ledState[layer][row][column] = true;
// }

// // Функция для выключения всех светодиодов
// void turnOffAllLEDs() {
//   // Выключаем все слои и столбцы
//   for (int i = 0; i < 2; i++) {
//     digitalWrite(layerPins[i], LOW);
//   }
//   for (int i = 0; i < 4; i++) {
//     digitalWrite(columnPins[i], LOW);
//   }
//   // Обновляем состояние всех светодиодов
//   for (int layer = 0; layer < 2; layer++) {
//     for (int row = 0; row < 2; row++) {
//       for (int column = 0; column < 2; column++) {
//         ledState[layer][row][column] = false;
//       }
//     }
//   }
// }

// // Функция для переключения состояния светодиода в кубе
// void toggleLED(int layer, int row, int column) {
//   if (ledState[layer][row][column]) {
//     // Если светодиод включен, выключаем его
//     digitalWrite(layerPins[layer], LOW);
//     digitalWrite(columnPins[row], LOW);
//     digitalWrite(columnPins[column + 2], LOW);
//     ledState[layer][row][column] = false;
//   } else {
//     // Если светодиод выключен, включаем его
//     turnOnLED(layer, row, column);
//   }
// }

// void loop() {
//   // Показываем свечение каждого отдельного светодиода поочередно
//   for (int layer = 0; layer < 2; layer++) {
//     for (int row = 0; row < 2; row++) {
//       for (int column = 0; column < 2; column++) {
//         delay(500); // Задержка в полсекунды
//         turnOnLED(layer, row, column); // Включаем светодиод
//         delay(500); // Задержка в полсекунды
//         turnOffAllLEDs(); // Выключаем все светодиоды
//       }
//     }
//   }

//   // Показываем свечение двух светодиодов одновременно
//   for (int layer = 0; layer < 2; layer++) {
//     for (int row = 0; row < 2; row++) {
//       for (int column = 0; column < 2; column++) {
//         for (int layer2 = 0; layer2 < 2; layer2++) {
//           for (int row2 = 0; row2 < 2; row2++) {
//             for (int column2 = 0; column2 < 2; column2++) {
//               if (!(layer == layer2 && row == row2 && column == column2)) {
//                 delay(500); // Задержка в полсекунды
//                 turnOnLED(layer, row, column); // Включаем первый светодиод
//                 turnOnLED(layer2, row2, column2); // Включаем второй светодиод
//                 delay(500); // Задержка в полсекунды
//                 turnOffAllLEDs(); // Выключаем все светодиоды
//               }
//             }
//           }
//         }
//       }
//     }
//   }

//   // Показываем свечение трех светодиодов одновременно
//   for (int layer = 0; layer < 2; layer++) {
//     for (int row = 0; row < 2; row++) {
//       for (int column = 0; column < 2; column++) {
//         for (int layer2 = 0; layer2 < 2; layer2++) {
//           for (int row2 = 0; row2 < 2; row2++) {
//             for (int column2 = 0; column2 < 2; column2++) {
//               for (int layer3 = 0; layer3 < 2; layer3++) {
//                 for (int row3 = 0; row3 < 2; row3++) {
//                   for (int column3 = 0; column3 < 2; column3++) {
//                     if (!((layer == layer2 && row == row2 && column == column2) ||
//                           (layer == layer3 && row == row3 && column == column3) ||
//                           (layer2 == layer3 && row2 == row3 && column2 == column3))) {
//                       delay(500); // Задержка в полсекунды
//                       turnOnLED(layer, row, column); // Включаем первый светодиод
//                       turnOnLED(layer2, row2, column2); // Включаем второй светодиод
//                       turnOnLED(layer3, row3, column3); // Включаем третий светодиод
//                       delay(500); // Задержка в полсекунды
//                       turnOffAllLEDs(); // Выключаем все светодиоды
//                     }
//                   }
//                 }
//               }
//             }
//           }
//         }
//       }
//     }
//   }

//   // Показываем свечение всех четырех светодиодов одновременно
//   for (int layer = 0; layer < 2; layer++) {
//     for (int row = 0; row < 2; row++) {
//       for (int column = 0; column < 2; column++) {
//         for (int layer2 = 0; layer2 < 2; layer2++) {
//           for (int row2 = 0; row2 < 2; row2++) {
//             for (int column2 = 0; column2 < 2; column2++) {
//               for (int layer3 = 0; layer3 < 2; layer3++) {
//                 for (int row3 = 0; row3 < 2; row3++) {
//                   for (int column3 = 0; column3 < 2; column3++) {
//                     if (!((layer == layer2 && row == row2 && column == column2) ||
//                           (layer == layer3 && row == row3 && column == column3) ||
//                           (layer2 == layer3 && row2 == row3 && column2 == column3))) {
//                       delay(500); // Задержка в полсекунды
//                       turnOnLED(layer, row, column); // Включаем первый светодиод
//                       turnOnLED(layer2, row2, column2); // Включаем второй светодиод
//                       turnOnLED(layer3, row3, column3); // Включаем третий светодиод
//                       turnOnLED(1 - (layer + layer2 + layer3), 1 - (row + row2 + row3), 1 - (column + column2 + column3)); // Включаем четвертый светодиод
//                       delay(500); // Задержка в полсекунды
//                       turnOffAllLEDs(); // Выключаем все светодиоды
//                     }
//                   }
//                 }
//               }
//             }
//           }
//         }
//       }
//     }
//   }
// }







int ledpins[] = {4,5,6,7}; // 1 2 3 4 колонки
int groundpins[] = {2,3}; // 0 и 1 слои
void setup ()
{
  for(int i = 0; i < 4; i++)
  {       
      pinMode(ledpins[i],OUTPUT);
  }                         
  for (int i= 0; i<2; i++)
  {pinMode(groundpins[i],OUTPUT);}

}

void loop()
{
  change_all(0);

  // 01 / 02 / 03 / 04 / 11 / 12 / 13 / 14
  // for (int i=0; i<=1; i++){ // layer   
  //   for (int j=0; j<=3; j++){ // col
  //     light_one(i, j);
  //     delay(500);
  //     change_all(0);
  //   }
  // }

  // 01 11 / 02 12 / 03 13 / 04 14
  // for (int i=0; i<=3; i++){ //column
  //     light_two_in_column(i);
  //     delay(500);
  //     change_all(0);
  // }

  // 01 12 / 01 13 / 01 14 / 02 11 / 02 13 / 02 14 / 03 11 / 03 12 / 03 14 / 04 11 / 04 12 / 04 13
  // for (int i=0; i<=3; i++){ //column for zero
  //   for (int j=0; j<=3; j++){ //column for first
  //     if (i != j){
  //       light_two_in_diff_layer(i, j);
  //       delay(100);
  //     }
  //   }
  // }

  // 01 02 / 01 03 / 01 04 / 02 03 / 02 04 / 03 04 / 11 12 / 11 13 / 11 14 / 12 13 / 12 14 / 13 14
  // for (int i=0; i<=1; i++){ // layer
  //   for (int j=0; j<3; j++){ // column
  //     for (int k=j+1; k<=3;k++){
  //       light_two_in_layer(i, j, k);
  //       delay(2000);
  //       change_all(0);
  //     }
      
  //   }
  // }

  //01 02 03 / 01 02 04 / 01 03 04 / 02 03 04 / 11 12 13 / 11 12 14 / 11 13 14 / 12 13 14
  // for (int i=1; i>=0; i--){ // layer   
  //   for (int j=0; j<=3; j++){ // col
  //     light_three_in_layer_without(i, j);
  //     delay(500);
  //     change_all(0);
  //   }
  // }


  // всякие разные тройки (где 2 в одном столбце и один в стороне)
  // for (int i=0; i<=3; i++){
  //   for(int j=0;j<=1;j++){
  //     for(int k=0;k<=3;k++){
  //       if(i!=k){
  //         for(int q=0; q<=50; q++){
  //           light_two_in_column(i);
  //           delay(5);
  //           change_all(0);
  //           light_one(j, k);
  //           delay(5);
  //           change_all(0);
  //         }
  //         change_all(0);
  //       }
  //     }
  //   }
  // }


  // доделать!
  // всякие разные тройки (где все ваще разное)
  for (int i=0; i<=1; i++){
    for(int j=0;j<=3;j++){
      for(int k=0;k<=3;k++){
        if(j!=k){
          for(int q=0; q<=100; q++){
            light_two_in_layer(i, j, k);
            delay(5);
            change_all(0);
            light_one(i, k);
            delay(5);
            change_all(0);
          }
          change_all(0);
        }
      }
    }
  }


  // все сразу
  // on_all();
  // delay(200);
}

void change_all(int state){
  digitalWrite(groundpins[0], state);
  digitalWrite(groundpins[1], state);
  digitalWrite(ledpins[0], state);
  digitalWrite(ledpins[1], state);
  digitalWrite(ledpins[2], state);
  digitalWrite(ledpins[3], state);
}

void on_all(){
  change_all(0);
  digitalWrite(ledpins[0], HIGH);
  digitalWrite(ledpins[1], HIGH);
  digitalWrite(ledpins[2], HIGH);
  digitalWrite(ledpins[3], HIGH);
}


// void light_zero_layer(){
//   digitalWrite(groundpins[0], HIGH);
//   for (int i = 0; i <= 3; i++){
//     digitalWrite(ledpins[i], HIGH);
//     delay(200);
//     digitalWrite(ledpins[i], LOW);
//     delay(200);
//   }
//   digitalWrite(groundpins[0], LOW);
//   delay(200);
// }

// void light_first_layer(){
//   digitalWrite(groundpins[1], HIGH);
//   for (int i = 0; i <= 3; i++){
//     digitalWrite(ledpins[i], HIGH);
//     delay(200);
//     digitalWrite(ledpins[i], LOW);
//     delay(200);
//   }
//   digitalWrite(groundpins[1], LOW);
//   delay(200);
// }

// void light_columns(){
//   for (int i = 0; i <= 3; i++){
//     digitalWrite(ledpins[i], HIGH);
//     delay(200);
//     digitalWrite(ledpins[i], LOW);
//     delay(200);
//   }
// }

void light_one(int layer, int col){
  digitalWrite(groundpins[layer], HIGH);
  digitalWrite(ledpins[col], HIGH);
}

void light_two_in_column(int col){
  digitalWrite(ledpins[col], HIGH);
}

void light_two_in_diff_layers(int fcol, int scol){
 for (int i=0; i<=100; i++){
  light_one(0, fcol);
    delay(5);
    change_all(0);

    light_one(1, scol);
    delay(5);
    change_all(0);
 }
}

void light_two_in_layer(int layer, int col1, int col2){
  light_one(layer, col1);
  light_one(layer, col2);
  
}

void light_three_in_layer_without(int layer, int col){
  change_all(1);
  digitalWrite(groundpins[layer], LOW);
  digitalWrite(ledpins[col], LOW);
}

void light_three_in_diff_layers(){

}


void test_twos_in_one(){
  // // 01 11
  // digitalWrite(groundpins[0], LOW);
  // digitalWrite(groundpins[1], LOW);
  // digitalWrite(ledpins[0], HIGH);

  // // 02 12
  // digitalWrite(groundpins[0], LOW);
  // digitalWrite(groundpins[1], LOW);
  // digitalWrite(ledpins[1], HIGH);

  // 01 13 !!!!!!!!!!!!!
  // digitalWrite(groundpins[1], HIGH);
  // digitalWrite(ledpins[0], HIGH);
  // delay(5);
  // digitalWrite(groundpins[1], LOW);
  // digitalWrite(ledpins[0], LOW);

  // digitalWrite(groundpins[0], HIGH);
  // digitalWrite(ledpins[2], HIGH);
  // delay(5);
  // digitalWrite(groundpins[0], LOW);
  // digitalWrite(ledpins[2], LOW);

   // 01 12
  // digitalWrite(groundpins[1], HIGH);
  // digitalWrite(ledpins[0], HIGH);
  // delay(5);
  // digitalWrite(groundpins[1], LOW);
  // digitalWrite(ledpins[0], LOW);

  // digitalWrite(groundpins[0], HIGH);
  // digitalWrite(ledpins[1], HIGH);
  // delay(5);
  // digitalWrite(groundpins[0], LOW);
  // digitalWrite(ledpins[1], LOW);

  // 01 03
  // digitalWrite(groundpins[1], HIGH);
  // digitalWrite(ledpins[1], HIGH);
  // digitalWrite(ledpins[2], HIGH);
}

void test_ones_top(){
  // top 1
  digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[0], HIGH);
  // итд
}

void test_ones_bottom(){
  // bottom 1
  digitalWrite(groundpins[1], HIGH);
  digitalWrite(ledpins[0], HIGH);
  // итд
}

void test1in0and2in1(){
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[0], LOW);
  digitalWrite(ledpins[1], LOW);
  digitalWrite(ledpins[2], LOW);
  digitalWrite(ledpins[3], LOW);

  // 01 11 12
  digitalWrite(ledpins[0], HIGH);
  delay(5);
  digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[1], HIGH);
  delay(5);
}

void test2in0and2in1(){
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[0], LOW);
  digitalWrite(ledpins[1], LOW);
  digitalWrite(ledpins[2], LOW);
  digitalWrite(ledpins[3], LOW);

  // 01 02 11 12
  // digitalWrite(ledpins[0], HIGH);
  // digitalWrite(ledpins[1], HIGH);

  // 02 03 12 13
  // digitalWrite(ledpins[1], HIGH);
  // digitalWrite(ledpins[2], HIGH);

    // 03 04 13 14
  // digitalWrite(ledpins[2], HIGH);
  // digitalWrite(ledpins[3], HIGH);

  // 01 04 11 14
  // digitalWrite(ledpins[0], HIGH);
  // digitalWrite(ledpins[3], HIGH);


  // 01 03 11 12
  digitalWrite(ledpins[0], HIGH); // 01 и 11

  digitalWrite(groundpins[1], HIGH); //03
  digitalWrite(ledpins[2], HIGH);

  delay(5);
  digitalWrite(groundpins[1], LOW); // 03 гасим
  digitalWrite(ledpins[2], LOW);

  digitalWrite(groundpins[0], HIGH); // 12
  digitalWrite(ledpins[1], HIGH);
  delay(5);
}




void test_all(){
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[0], HIGH);
  digitalWrite(ledpins[1], HIGH);
  digitalWrite(ledpins[2], HIGH);
  digitalWrite(ledpins[3], HIGH);
}

void twist()
{
  int delaytime=1000;
   digitalWrite(groundpins[0], HIGH);
    delay(100);   
  digitalWrite(ledpins[0], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[1], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[2], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[3], HIGH);
  delay(delaytime);
 
   digitalWrite(ledpins[0], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[1], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[2], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[3], LOW); 
delay(delaytime);
digitalWrite(groundpins[0], LOW);




digitalWrite(groundpins[1], HIGH);
    delay(100);   
  digitalWrite(ledpins[1], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[2], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[3], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[0], HIGH);
  delay(delaytime);
 
   digitalWrite(ledpins[1], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[2], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[3], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[0], LOW); 
  delay(delaytime);
  digitalWrite(groundpins[1], LOW);
 
 
  digitalWrite(groundpins[0], HIGH);
    delay(100);   
  digitalWrite(ledpins[2], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[3], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[0], HIGH);
  delay(delaytime);               
  digitalWrite(ledpins[1], HIGH);
  delay(delaytime);
 
  digitalWrite(ledpins[2], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[3], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[0], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[1], LOW); 
  delay(delaytime);
  digitalWrite(groundpins[0], LOW);
 
  digitalWrite(groundpins[1], HIGH);
    delay(100);   
  digitalWrite(ledpins[3], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[0], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[1], HIGH); 
  delay(delaytime);               
  digitalWrite(ledpins[2], HIGH);
  delay(delaytime);
 
  digitalWrite(ledpins[3], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[0], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[1], LOW); 
  delay(delaytime);               
  digitalWrite(ledpins[2], LOW); 
  delay(delaytime);
  digitalWrite(groundpins[1], LOW);
}

void drop()
{
  int dtime = 75;
  digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[0], HIGH);
  delay(dtime);
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1],HIGH);
  delay(dtime);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[0], LOW);
 
  digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[1], HIGH);
  delay(dtime);
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], HIGH);
  delay(dtime);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[1], LOW);
 
  digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[2], HIGH);
  delay(dtime);
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], HIGH);
  delay(dtime);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[2], LOW);
 
   digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[3], HIGH);
  delay(dtime);
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], HIGH);
  delay(dtime);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[3], LOW);
 
 
  //second time down
  digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[0], HIGH);
  delay(dtime);
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1],HIGH);
  delay(dtime);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[0], LOW);
 
  digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[1], HIGH);
  delay(dtime);
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], HIGH);
  delay(dtime);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[1], LOW);
 
  digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[2], HIGH);
  delay(dtime);
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], HIGH);
  delay(dtime);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[2], LOW);
 
   digitalWrite(groundpins[0], HIGH);
  digitalWrite(ledpins[3], HIGH);
  delay(dtime);
  digitalWrite(groundpins[0], LOW);
  digitalWrite(groundpins[1], HIGH);
  delay(dtime);
  digitalWrite(groundpins[1], LOW);
  digitalWrite(ledpins[3], LOW);
 
}





void my(){
    int dtime= 1000;
    //bottom pin 0 on
    digitalWrite(groundpins[1], HIGH);
    digitalWrite(ledpins[0], HIGH);
    delay(dtime);
    //bottom pin 1 on
    digitalWrite(groundpins[1], HIGH);
    digitalWrite(ledpins[1], HIGH);
    delay(dtime);
    //bottom pin 2 on
    digitalWrite(groundpins[1], HIGH);
    digitalWrite(ledpins[2], HIGH);
    delay(dtime);
      //bottom pin 3 on
    digitalWrite(groundpins[1], HIGH);
    digitalWrite(ledpins[3], HIGH);
    delay(dtime);
    //top pin 0 on
    digitalWrite(groundpins[0], HIGH);
    digitalWrite(ledpins[0], HIGH);
    delay(dtime);
    //top pin 1 on
    digitalWrite(groundpins[0], HIGH);
    digitalWrite(ledpins[1], HIGH);
    delay(dtime);
    //top pin 2 on
    digitalWrite(groundpins[0], HIGH);
    digitalWrite(ledpins[2], HIGH);
    delay(dtime);
    //top pin 3 on
    digitalWrite(groundpins[0], HIGH);
    digitalWrite(ledpins[3], HIGH);

    delay(dtime);

    //bottom pin 0 off
    digitalWrite(groundpins[1], LOW);
    digitalWrite(ledpins[0], LOW);
    //bottom pin 1 off
    digitalWrite(groundpins[1], LOW);
    digitalWrite(ledpins[1], LOW);
    //bottom pin 2 off
    digitalWrite(groundpins[1], LOW);
    digitalWrite(ledpins[2], LOW);
    //bottom pin 3 off
    digitalWrite(groundpins[1], LOW);
    digitalWrite(ledpins[3], LOW);
    //top pin 0 off
    digitalWrite(groundpins[0], LOW);
    digitalWrite(ledpins[0], LOW);
    //top pin 1 off
    digitalWrite(groundpins[0], LOW);
    digitalWrite(ledpins[1], LOW);
    //top pin 2 off
    digitalWrite(groundpins[0], LOW);
    digitalWrite(ledpins[2], LOW);
    //top pin 3 off
    digitalWrite(groundpins[0], LOW);
    digitalWrite(ledpins[3], LOW);


    delay(dtime);
}

void diagonal()
{
int dtime= 500;
//bottom pin 0 on
digitalWrite(groundpins[1], HIGH);
digitalWrite(ledpins[0], HIGH);
delay(dtime);
//bottom pin 0 off
digitalWrite(groundpins[1], LOW);
digitalWrite(ledpins[0], LOW);
delay(dtime);
//top pin 1 on
digitalWrite(groundpins[0], HIGH);
digitalWrite(ledpins[1], HIGH);
delay(dtime);
//top pin 1 off
digitalWrite(groundpins[0], LOW);
digitalWrite(ledpins[1], LOW);
//bottom pin 2 on
digitalWrite(groundpins[1], HIGH);
digitalWrite(ledpins[2], HIGH);
delay(dtime);
//bottom pin 2 off
digitalWrite(groundpins[1], LOW);
digitalWrite(ledpins[2], LOW);
  //top pin 3 on
digitalWrite(groundpins[0], HIGH);
digitalWrite(ledpins[3], HIGH);
delay(dtime);
//top pin 3 off
digitalWrite(groundpins[0], LOW);
digitalWrite(ledpins[3], LOW);






//bottom pin 1 on
digitalWrite(groundpins[1], HIGH);
digitalWrite(ledpins[1], HIGH);
delay(dtime);
//bottom pin 1 off
digitalWrite(groundpins[1], LOW);
digitalWrite(ledpins[1], LOW);
//top pin 2 on
digitalWrite(groundpins[0], HIGH);
digitalWrite(ledpins[2], HIGH);
delay(dtime);
//top pin 2 off
digitalWrite(groundpins[0], LOW);
digitalWrite(ledpins[2], LOW);


}



// // Пины для подключения куба
// const int layerPins[] = {2, 3};   // Пины для управления слоями
// const int columnPins[] = {4, 5, 6, 7};   // Пины для управления столбцами

// // Массив для хранения состояния светодиодов
// bool ledState[2][2][2] = {{{false, false}, {false, false}},
//                            {{false, false}, {false, false}}};

// // Функция для инициализации пинов
// void setup() {
//   // Устанавливаем пины как OUTPUT
//   for (int i = 0; i < 2; i++) {
//     pinMode(layerPins[i], OUTPUT);
//   }
//   for (int i = 0; i < 4; i++) {
//     pinMode(columnPins[i], OUTPUT);
//   }
// }

// // Функция для включения светодиода в кубе
// void turnOnLED(int layer, int row, int column) {
//   // Выключаем все светодиоды
//   turnOffAllLEDs();
//   // Включаем нужный светодиод
//   digitalWrite(layerPins[layer], HIGH);
//   digitalWrite(columnPins[row], HIGH);
//   digitalWrite(columnPins[column + 2], HIGH);
//   // Обновляем состояние светодиода
//   ledState[layer][row][column] = true;
// }

// // Функция для выключения всех светодиодов
// void turnOffAllLEDs() {
//   // Выключаем все слои и столбцы
//   for (int i = 0; i < 2; i++) {
//     digitalWrite(layerPins[i], LOW);
//   }
//   for (int i = 0; i < 4; i++) {
//     digitalWrite(columnPins[i], LOW);
//   }
//   // Обновляем состояние всех светодиодов
//   for (int layer = 0; layer < 2; layer++) {
//     for (int row = 0; row < 2; row++) {
//       for (int column = 0; column < 2; column++) {
//         ledState[layer][row][column] = false;
//       }
//     }
//   }
// }

// // Функция для переключения состояния светодиода в кубе
// void toggleLED(int layer, int row, int column) {
//   if (ledState[layer][row][column]) {
//     // Если светодиод включен, выключаем его
//     digitalWrite(layerPins[layer], LOW);
//     digitalWrite(columnPins[row], LOW);
//     digitalWrite(columnPins[column + 2], LOW);
//     ledState[layer][row][column] = false;
//   } else {
//     // Если светодиод выключен, включаем его
//     turnOnLED(layer, row, column);
//   }
// }

// void loop() {
//   // Пример использования: включаем и выключаем светодиоды поочередно
//   for (int layer = 0; layer < 2; layer++) {
//     for (int row = 0; row < 2; row++) {
//       for (int column = 0; column < 2; column++) {
//         delay(500); // Задержка в полсекунды
//         toggleLED(layer, row, column); // Переключаем состояние светодиода
//       }
//     }
//   }
// }

