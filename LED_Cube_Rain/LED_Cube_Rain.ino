/*
  Lập trình LED lập phương 3x3x3 theo hiệu ứng: Mưa.
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

void animationRain(){           //Tạo ra hiệu ứng mưa.
  static int x = random(3) , y = random(3) , z  = 2;
  model[z][y][x] = LOW;
  z--;
  if (z < 0){
    z = 2;
    x = random(3);
    y = random(3);
  }
  model[z][y][x] = HIGH;
}


void refresh(){                //Cập nhật hiệu ứng mưa từ hàm animationRain().
  for (int layer = 0 ; layer < 3 ; layer++){      //Xét từng layer.
    digitalWrite(layerPins[layer] , LOW);
    for(int x = 0 ; x < 3 ; x++){                 //Led của layer được chỉ định ở animationRain().
      for(int y = 0 ; y < 3 ; y++){
        digitalWrite(ledPins[y][x] , model[layer][y][x]);
      }
    }
    delay(refreshPeriod);
    digitalWrite(layerPins[layer] , HIGH);
  }
}

void loop() {
  static long lastUpdate = 0;
  long now = millis();              //Sử dụng millis() để tránh không bị ngưng chương trình.
  if (now > lastUpdate + period){   //Câu lệnh này tương đương delay(period).
    animationRain();
    lastUpdate = now;
  }
  refresh();
}


