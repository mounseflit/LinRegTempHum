#include <dht.h>

dht DHT;


long int gap = 3600000;                     // Time Period Between Samples taking              : 3600000 = 1h
const int SAMPLE_SIZE = 600;                // Number of Samples used to calculate a and b     : 1000 time
float hum_samples[SAMPLE_SIZE]={60, 53, 48, 44, 39, 39, 40, 40, 42, 44, 46, 48, 49, 51, 55, 58, 62, 64, 65, 67, 65, 64, 62, 58, 53, 49, 47, 45, 43, 44, 45, 47, 48, 49, 51, 51, 51, 51, 53, 55, 57, 56, 55, 54, 50, 47, 43, 39, 34, 30, 29, 27, 26, 27, 28, 29, 30, 32, 33, 34, 34, 34, 34, 34, 33, 35, 37, 39, 38, 38, 38, 35, 33, 30, 28, 25, 23, 24, 25, 26, 29, 31, 34, 36, 38, 40, 40, 40, 40, 42, 45, 47, 48, 49, 51, 48, 46, 43, 40, 37, 34, 35, 36, 37, 40, 44, 47, 49, 51, 53, 54, 54, 55, 58, 60, 63, 63, 63, 63, 58, 53, 48, 44, 39, 34, 34, 33, 33, 36, 39, 43, 45, 47, 49, 50, 51, 53, 55, 58, 60, 62, 63, 64, 59, 55, 50, 45, 39, 34, 34, 34, 34, 37, 41, 44, 46, 47, 49, 49, 50, 50, 52, 54, 56, 56, 56, 55, 52, 49, 46, 44, 42, 40, 42, 43, 45, 45, 46, 46, 47, 47, 48, 49, 50, 51, 52, 53, 55, 54, 54, 53, 49, 44, 40, 36, 32, 28, 29, 29, 29, 32, 34, 37, 38, 39, 39, 42, 44, 46, 47, 47, 48, 46, 45, 44, 40, 37, 34, 31, 29, 26, 27, 27, 27, 30, 32, 35, 36, 38, 40, 40, 40, 41, 41, 42, 43, 42, 42, 42, 38, 35, 32, 29, 26, 24, 24, 24, 24, 26, 28, 30, 30, 31, 32, 33, 35, 36, 38, 40, 42, 42, 42, 43, 39, 36, 33, 30, 28, 25, 25, 25, 26, 28, 30, 32, 33, 34, 34, 36, 37, 38, 39, 40, 41, 41, 42, 42, 39, 37, 34, 32, 29, 27, 26, 26, 26, 28, 30, 32, 32, 33, 34, 35, 37, 38, 39, 41, 42, 41, 41, 41, 37, 34, 31, 29, 27, 25, 25, 26, 26, 29, 31, 34, 35, 37, 39, 39, 40, 40, 41, 43, 44, 44, 43, 43, 39, 35, 32, 29, 27, 24, 24, 24, 24, 26, 28, 30, 31, 33, 34, 38, 42, 46, 46, 47, 48, 47, 46, 45, 41, 37, 33, 30, 28, 25, 25, 24, 24, 26, 28, 30, 32, 34, 36, 43, 51, 58, 60, 62, 64, 64, 64, 63, 57, 51, 44, 38, 32, 26, 25, 24, 23, 25, 27, 29, 31, 33, 35, 40, 45, 50, 52, 54, 55, 53, 51, 48, 43, 37, 32, 29, 26, 23, 23, 23, 24, 26, 29, 31, 33, 35, 36, 39, 41, 43, 45, 47, 49, 49, 50, 50, 46, 42, 38, 34, 30, 26, 26, 26, 26, 29, 31, 33, 36, 38, 40, 42, 43, 45, 47, 49, 52, 51, 51, 51, 47, 43, 39, 35, 32, 28, 28, 28, 28, 31, 33, 36, 38, 39, 41, 45, 48, 52, 53, 55, 57, 56, 55, 54, 49, 44, 40, 36, 32, 28, 28, 27, 27, 29, 31, 33, 34, 35, 36, 40, 43, 47, 48, 49, 51, 49, 48, 47, 42, 38, 33, 30, 27, 24, 24, 24, 24, 26, 28, 30, 31, 32, 34, 36, 39, 41, 42, 44, 45, 44, 43, 43, 39, 36, 33, 30, 27, 25, 25, 24, 24, 26, 28, 30, 31, 32, 33, 35, 37, 40, 41, 42, 43, 42, 42, 41, 38, 36, 33, 31, 29, 28, 29, 30, 31, 33, 36, 38, 40, 41, 43, 45, 47, 49, 50, 51, 52, 51, 50, 49, 46, 43, 39, 36, 34, 31, 31, 31, 31, 32, 33, 34, 34, 34, 35, 35, 36, 36, 37, 37, 38, 37, 37, 37, 35};
float temp_samples[SAMPLE_SIZE]={27, 28, 30, 31, 31, 32, 32, 31, 31, 30, 30, 29, 28, 28, 27, 27, 27, 26, 26, 26, 25, 26, 26, 26, 27, 28, 30, 30, 31, 31, 31, 30, 29, 29, 28, 28, 27, 27, 26, 25, 25, 24, 23, 23, 22, 23, 23, 23, 24, 25, 26, 27, 28, 29, 29, 29, 29, 28, 28, 27, 26, 26, 25, 24, 23, 22, 21, 21, 20, 20, 20, 20, 22, 23, 24, 26, 27, 28, 28, 28, 27, 27, 26, 25, 24, 24, 23, 23, 22, 22, 21, 21, 20, 21, 21, 21, 22, 24, 25, 26, 27, 28, 28, 28, 28, 27, 27, 26, 26, 25, 25, 24, 24, 23, 23, 22, 22, 22, 21, 21, 23, 24, 26, 27, 28, 30, 30, 30, 30, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 20, 20, 20, 20, 22, 23, 25, 26, 27, 29, 29, 28, 28, 27, 26, 25, 25, 24, 24, 24, 23, 23, 23, 22, 22, 22, 22, 22, 23, 24, 25, 26, 26, 27, 26, 26, 25, 25, 25, 25, 24, 24, 23, 23, 23, 22, 22, 21, 21, 21, 22, 22, 23, 25, 26, 27, 29, 30, 30, 30, 29, 28, 28, 27, 27, 26, 26, 25, 24, 23, 23, 23, 23, 23, 23, 23, 24, 25, 27, 28, 29, 30, 30, 30, 30, 29, 28, 27, 27, 26, 25, 25, 24, 24, 23, 23, 22, 22, 22, 23, 24, 25, 27, 28, 29, 30, 30, 30, 30, 29, 28, 27, 27, 27, 26, 26, 25, 24, 24, 23, 23, 23, 23, 23, 24, 26, 27, 28, 29, 30, 30, 30, 30, 29, 29, 28, 28, 27, 27, 27, 26, 25, 24, 24, 23, 23, 23, 24, 25, 26, 28, 29, 30, 31, 31, 31, 31, 30, 29, 29, 28, 28, 28, 27, 27, 26, 26, 25, 25, 25, 25, 25, 26, 28, 29, 30, 31, 32, 32, 32, 32, 31, 30, 30, 29, 29, 28, 27, 26, 26, 25, 25, 24, 24, 24, 25, 26, 27, 29, 30, 30, 31, 31, 31, 30, 29, 28, 27, 25, 23, 22, 23, 24, 25, 25, 24, 24, 24, 24, 24, 26, 27, 29, 30, 31, 32, 31, 31, 30, 29, 29, 28, 27, 25, 24, 24, 24, 24, 24, 24, 23, 23, 24, 24, 26, 27, 29, 30, 31, 32, 32, 32, 32, 31, 30, 29, 29, 28, 28, 27, 26, 25, 24, 24, 24, 24, 24, 25, 26, 27, 29, 30, 31, 32, 31, 31, 30, 30, 29, 28, 27, 27, 26, 25, 24, 23, 23, 23, 23, 23, 23, 23, 25, 27, 29, 30, 31, 32, 32, 31, 31, 30, 28, 27, 27, 26, 25, 25, 25, 25, 25, 25, 25, 25, 25,1, 31, 30, 28, 27, 26, 25, 23, 23, 23, 23, 23, 23, 23, 23, 24, 25, 26, 27, 28, 29, 30, 31, 31, 32, 32, 31, 30, 30, 29, 28, 28, 27, 26, 25, 24, 22, 21, 21, 22, 22, 23, 25, 26, 27, 29, 30, 30, 30, 30, 29, 28, 27, 26, 26, 25, 25, 24, 24, 23, 23, 22, 22, 23, 23, 24, 26, 27, 28, 29, 30, 30, 30, 30, 29, 28, 28, 27, 26, 26, 25, 24, 24, 23, 23, 23, 23, 23, 23, 25, 26, 27, 28, 29, 30, 30, 29, 29, 28, 27, 26, 26, 25, 25, 24, 24, 23, 23, 22, 22, 22, 22, 22, 24, 25, 26, 27, 28, 29, 29, 29, 29, 28, 27, 27, 26, 25, 25, 24, 24, 23, 23, 22, 22, 22, 22, 23, 24, 25, 27, 28, 29, 30, 30, 30};

void setup() {

  //My sensor trick 3:VCC/4:GND
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);

  Serial.begin(9600);      // Initialize serial communication

  // ;) to look Pro
  Serial.print(">>> Welcome!");
  delay(1000);
  Serial.print("\n\n   > Initializing...");
  delay(3000);
  Serial.print("\n\n   > Checking...");
  delay(2000);
  Serial.print("\n\n   > Starting...");
  delay(1000);
  Serial.print("\n\n>>> Collecting Data :\n\n");
  delay(500);

}

int index = 0;
float a = 0, b = 0;
float humidity = 0, temperature = 0;
float predicted_temp;


void loop() {

  

    // Calculate a and b values based on the current samples lists

    // Calculate sum of lists
    float sum_hum = 0, sum_temp = 0, sum_humtemp = 0, sum_cubetemp = 0, sum_cubehum = 0;
    for (int i = 0; i < SAMPLE_SIZE; i++) {
      sum_hum += hum_samples[i];                            //sum of exesting listed data humidity        //sum of x
      sum_temp += temp_samples[i];                          //sum of exesting listed data temperature     //sum of y
      sum_humtemp += hum_samples[i] * temp_samples[i];      //sum of exesting listed data humtemp         //sum of xy
      sum_cubetemp += temp_samples[i] * temp_samples[i];    //sum of exesting listed data cubetemp        //sum of yy
      sum_cubehum += hum_samples[i] * hum_samples[i];       //sum of exesting listed data cubehum         //sum of xx
    }

    // Calculate avg of lists
    float avg_hum = sum_hum / SAMPLE_SIZE;                                              //avg of x
    float avg_temp = sum_temp / SAMPLE_SIZE;                                            //avg of y
    float avg_humtemp = sum_humtemp / SAMPLE_SIZE;                                      //avg of xy
    float avg_cubehum = sum_cubehum / SAMPLE_SIZE;                                      //avg of xx
    float avg_cubetemp = sum_cubetemp / SAMPLE_SIZE;                                    //avg of yy

    // Calculate a and b
    float num = avg_humtemp - avg_hum * avg_temp;
    float den = avg_cubehum - avg_cubetemp;

    a = num / den;                                                                      //a
    b = avg_temp - a * avg_hum;                                                         //b

    Serial.print("\n>>> End of Collecting data And Start of Prediction");
    delay(1000);
    Serial.print("\n\n   > Initializing...");
    delay(3000);
    Serial.print("\n\n   > Checking...");
    delay(2000);
    Serial.print("\n\n   > Starting...");
    delay(1000);
    Serial.print("\n\n>>> Real-Time Prediction :\n\n");
    delay(500);
 
  

  //Print old a and b to serial monitor
  /*Serial.print("\nOLD a&b : \n");
    Serial.print("a : ");
    Serial.print(a);
    Serial.print("  b : ");
    Serial.print(b);
    Serial.print("\n"); */

  // Use the current humidity value to predict the temperature using old a and b
  float prv_pred_temp = a * humidity + b;


  int chk = DHT.read11(2);  // Read humidity and temperature from DHT11 sensor

  //check availblity of the sensor
 if (chk == -1) {

    humidity = DHT.humidity;        // Get the humidity value
    temperature = DHT.temperature;  // Get the temperature value

    //filling the table

    // Update by adding new humidity and temperature readings to the samples lists (erease from top)
    hum_samples[index] = humidity;                        //x
    temp_samples[index] = temperature;                    //y

    index = (index + 1) % SAMPLE_SIZE;                    // start over from 0 after surpassing SAMPLE SIZE

    // Calculate new a and b values based on the current samples lists

    // Calculate sum of lists
    float sum_hum = 0, sum_temp = 0, sum_humtemp = 0, sum_cubetemp = 0, sum_cubehum = 0;
    for (int i = 0; i < SAMPLE_SIZE; i++) {
      sum_hum += hum_samples[i];                            //sum of exesting listed data humidity        //sum of x
      sum_temp += temp_samples[i];                          //sum of exesting listed data temperature     //sum of y
      sum_humtemp += hum_samples[i] * temp_samples[i];      //sum of exesting listed data humtemp         //sum of xy
      sum_cubetemp += temp_samples[i] * temp_samples[i];    //sum of exesting listed data cubetemp        //sum of yy
      sum_cubehum += hum_samples[i] * hum_samples[i];       //sum of exesting listed data cubehum         //sum of xx
    }
    // Calculate avg of lists
    float avg_hum = sum_hum / SAMPLE_SIZE;                                              //avg of x
    float avg_temp = sum_temp / SAMPLE_SIZE;                                            //avg of y
    float avg_humtemp = sum_humtemp / SAMPLE_SIZE;                                      //avg of xy
    float avg_cubehum = sum_cubehum / SAMPLE_SIZE;                                      //avg of xx
    float avg_cubetemp = sum_cubetemp / SAMPLE_SIZE;                                    //avg of yy

    // Calculate a and b
    float num = avg_humtemp - avg_hum * avg_temp;
    float den = avg_cubehum - avg_cubetemp;

    a = num / den;                                                                      //a
    b = avg_temp - a * avg_hum;                                                         //b

    //Print new a and b to serial monitor
    /*Serial.print("\nNEW a&b : \n");
      Serial.print("a : ");
      Serial.print(a);
      Serial.print("  b : ");
      Serial.print(b);
      Serial.print("\n");*/

    // Use the current humidity value to predict the temperature
    predicted_temp = a * humidity + b;

    // Print humidity, temperature, predicted temperature, prv predicted temperature and error to serial monitor
    //Serial.print("\nDATA : \n");
    Serial.print("\n ");
    Serial.print(index);
    Serial.print(" | Humidity: ");
    Serial.print(humidity);
    Serial.print("% |");
    Serial.print(" Temperature: ");
    Serial.print(temperature);
    Serial.print("C |");
    Serial.print(" Predicted temperature: ");
    Serial.print(predicted_temp);
    Serial.print("C |");
    Serial.print(" Prv Predicted temperature: ");
    Serial.print(prv_pred_temp);
    Serial.print("C |");
    Serial.print(" Error: "); 
    Serial.print((predicted_temp - temperature) * (predicted_temp - temperature));
    Serial.print("\n");
  }

  delay(gap);  // Wait before taking another reading
} 
