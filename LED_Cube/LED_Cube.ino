/*
  Lập trình LED lập phương 3x3x3 theo hiệu ứng: Sáng theo dọc từ trái qua phải.
*/

//Khai báo 9 chân dương của LED, chân âm chung của cả 3 tầng nối GND
const int ledPins[3][3] = {{3 , 4 , 5} , {6 , 7 , 8} , {9 , 10 , 11}};
const int period = 200;
const int layerPins[3] = {2, 12, 13};      //Chân A chung của tầng 1,2,3.
int model[3][3][3];                        //Lưu trữ trạng thái của Led tầng z hàng x cột y.
const int refreshPeriod = 5;

void setup() {
  // Khai báo các chân Arduino
  for (int x = 0 ; x < 3 ; x++){
    for(int y = 0 ; y < 3 ; y++){
      pinMode(ledPins[x][y] , OUTPUT);
    }
  }
  pinMode(layerPins[0] , OUTPUT);
  pinMode(layerPins[1] , OUTPUT);
  pinMode(layerPins[2] , OUTPUT);
}

void animationLayer(){
  static int x = 2, y = 0, z = 0;
  for (int z = 0 ; z <= 2 ; z++){
    for (int y = 0 ; y <= 2 ; y++){
      model[z][x][y] = LOW;           //Led ở cột trước đó tắt.
    }
  }
  x++;
  if (x > 2) x = 0;                   //Nếu x = 2 thì reset lại x = 0.
  for (int z = 0 ; z <= 2 ; z++){
    for (int y = 0 ; y <= 2 ; y++){
      model[z][x][y] = HIGH;          //Led ở tầng z hàng x cột y sáng.
    }
  }
}

void refresh(){
  for (int layer = 0 ; layer < 3 ; layer++){      //Xét từng layer.
    digitalWrite(layerPins[layer] , LOW);
    for(int x = 0 ; x < 3 ; x++){                 //Led của layer được chỉ định ở animationLayer().
      for(int y = 0 ; y < 3 ; y++){
        digitalWrite(ledPins[x][y] , model[layer][x][y]);
      }
    }
    delay(refreshPeriod);
  }
}

void loop(){
  static long lastUpdate = 0;
  long now = millis();                  
  if (now > lastUpdate + period){              //Câu lệnh tương đương delay(period);
    animationLayer();
    lastUpdate = now;
  }
  refresh();
}
