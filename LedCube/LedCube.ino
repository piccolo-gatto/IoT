int ledpins[] = {4,5,6,7}; // 1 2 3 4 колонки
int groundpins[] = {2,3}; // 0 и 1 слои

int BRIGHTNESS = 128;
int DELAY = 500;

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

  //01 / 02 / 03 / 04 / 11 / 12 / 13 / 14
  for (int i=0; i<=1; i++){ // layer   
    for (int j=0; j<=3; j++){ // col
      light_one(i, j);
      delay(DELAY);
      change_all(0);
    }
  }

  //01 11 / 02 12 / 03 13 / 04 14
  for (int i=0; i<=3; i++){ //column
      light_two_in_column(i);
      delay(DELAY);
      change_all(0);
  }

  //01 12 / 01 13 / 01 14 / 02 11 / 02 13 / 02 14 / 03 11 / 03 12 / 03 14 / 04 11 / 04 12 / 04 13
  for (int i=0; i<=3; i++){ //column for zero
    for (int j=0; j<=3; j++){ //column for first
      if (i != j){
        light_two_in_diff_layers(i, j);
      }
    }
  }

  //01 02 / 01 03 / 01 04 / 02 03 / 02 04 / 03 04 / 11 12 / 11 13 / 11 14 / 12 13 / 12 14 / 13 14
  for (int i=0; i<=1; i++){ // layer
    for (int j=0; j<3; j++){ // column
      for (int k=j+1; k<=3;k++){
        light_two_in_layer(i, j, k);
        delay(DELAY);
        change_all(0);
      }
    }
  }

 // 01 02 03 / 01 02 04 / 01 03 04 / 02 03 04 / 11 12 13 / 11 12 14 / 11 13 14 / 12 13 14
  for (int i=1; i>=0; i--){ // layer   
    for (int j=0; j<=3; j++){ // col
      light_three_in_layer_without(i, j);
      delay(DELAY);
      change_all(0);
    }
  }


  //всякие разные тройки (где 2 в одном столбце и один в стороне)
  for (int i=0; i<=3; i++){
    for(int j=0;j<=1;j++){
      for(int k=0;k<=3;k++){
        if(i!=k){
          for(int q=0; q<=DELAY/10; q++){
            light_two_in_column(i);
            delay(5);
            change_all(0);
            light_one(j, k);
            delay(5);
            change_all(0);
          }
          change_all(0);
        }
      }
    }
  }


  // пример всяких разных троек (где все ваще разное)
  for (int i=1; i<=3; i++){
    for (int j=1; j<=3; j++){
      
        if (i!=j){
          for(int q=0; q<=DELAY/10; q++){
            light_one(0, 0);
            delay(5);
            change_all(0);
            light_two_in_layer(1, i, j);
            delay(5);
            change_all(0);
          }
        }  
    }
  }


  //01 02 11 12 / 02 03 12 13 / 03 04 13 14 / 01 04 11 14 (по два столбика)
  for (int i=0; i<=3; i++){ // layer
   if(i==3){
    light_two_in_column(i);
    light_two_in_column(0);
    delay(DELAY);
    change_all(0);
   } else{
    light_two_in_column(i);
    light_two_in_column(i+1);
    delay(DELAY);
    change_all(0);
   }
  }


  // по целому слою
  for (int i = 0; i <= 1; i++){
    light_two_in_layer(i, 0, 1);
    light_two_in_layer(i, 2, 3);
    delay(DELAY);
    change_all(0);
  }

  // диагональные плоскости через куб
  for (int i=0; i<=1; i++){
    for (int j=0;j<=DELAY/10;j++){
    if (i==1){
      light_two_in_layer(i, 0, 1);
      delay(5);
      change_all(0);
      light_two_in_layer(i-1, 2, 3);
      delay(5);
      change_all(0);
    } else{
      light_two_in_layer(i, 0, 1);
      delay(5);
      change_all(0);
      light_two_in_layer(i+1, 2, 3);
      delay(5);
      change_all(0);
    }
  }
  }
  
  
  // перекрестные диагонали в плоскостях слоев перекрестные
  for (int i=0; i<=1; i++){
    for (int j=0;j<=DELAY/10;j++){
    if (i==1){
      light_two_in_layer(i, 0, 3);
      delay(5);
      change_all(0);
      light_two_in_layer(i-1, 1, 2);
      delay(5);
      change_all(0);
    } else{
      light_two_in_layer(i, 0, 3);
      delay(5);
      change_all(0);
      light_two_in_layer(i+1, 1, 2);
      delay(5);
      change_all(0);
    }
  }
  }

  // пятерка
  for (int j=0;j<=DELAY/10;j++){
    light_two_in_column(0);
    light_two_in_column(3);
    delay(5);
    change_all(0);
    light_one(1, 1);
    delay(5);
    change_all(0);
  }

  // шестерка
  light_two_in_column(0);
  light_two_in_column(1);
  light_two_in_column(2);


  // семерка
  for (int j=0;j<=DELAY/10;j++){
  light_two_in_column(0);
  light_two_in_column(1);
  light_two_in_column(2);
    delay(5);
    change_all(0);
    light_one(1, 3);
    delay(5);
    change_all(0);
  }

  //все сразу
  on_all();
  delay(DELAY+100);
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


void light_one(int layer, int col){
  digitalWrite(groundpins[layer], HIGH);
  digitalWrite(ledpins[col], HIGH);
}

void light_two_in_column(int col){
  digitalWrite(ledpins[col], HIGH);
}

void light_two_in_diff_layers(int fcol, int scol){
 for (int i=0; i<=DELAY/10; i++){
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
