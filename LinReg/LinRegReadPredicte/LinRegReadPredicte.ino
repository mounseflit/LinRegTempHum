#include <dht.h>

dht DHT;                     

const int SAMPLE_SIZE = 700;         // Number of samples used to calculate a and b
float hum_samples[SAMPLE_SIZE];
float temp_samples[SAMPLE_SIZE];
int index = 0;
float a, b = 0;


void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  Serial.begin(9600);      // Initialize serial communication
  delay(1000);             // Wait for serial monitor to initialize
}

void loop() {

  int chk = DHT.read11(2);  // Read humidity and temperature from DHT11 sensor
  
  //check availblity of the sensor
  if (chk == -1) {

    float humidity = DHT.humidity;   // Get the humidity value
    float temperature = DHT.temperature;  // Get the temperature value

    //filling the table

    // Add new humidity and temperature readings to the samples lists
    hum_samples[index] = humidity;                        //x
    temp_samples[index] = temperature;                    //y

    index = (index + 1) % SAMPLE_SIZE;                    // start over from 0 after surpassing 600

    // Calculate a and b values based on the current samples lists

    // Calculate sum of lists
    float sum_hum = 0, sum_temp = 0, sum_humtemp = 0, sum_cubetemp = 0, sum_cubehum = 0;
    for (int i = 0; i < SAMPLE_SIZE; i++) {
      sum_hum += hum_samples[i];                         //sum of exesting listed data humidity    //sum of x
      sum_temp += temp_samples[i];                       //sum of exesting listed data temperature //sum of y
      sum_humtemp += temp_samples[i]*hum_samples[i];     //sum of exesting listed data humtemp     //sum of xy
      sum_cubetemp += temp_samples[i]*temp_samples[i];   //sum of exesting listed data cubetemp    //sum of yy
      sum_cubehum += hum_samples[i]*hum_samples[i];      //sum of exesting listed data cubehum     //sum of xx
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

    a = num / den;                                                                  //a
    b = avg_temp - a * avg_hum;                                                     //b


    // Use the current humidity value to predict the temperature
    float predicted_temp = a * humidity + b;

    // Print humidity, temperature, predicted temperature, and error to serial monitor
    Serial.print(index);
    Serial.print(" Humidity: ");
    Serial.print(humidity);
    Serial.print("%");
    Serial.print(" Temperature: ");
    Serial.print(temperature);
    Serial.print("C");
    Serial.print(" Predicted temperature: ");
    Serial.print(predicted_temp);
    Serial.print("C");
    Serial.print(" Error: ");
    Serial.print((predicted_temp - temperature));
    Serial.print("\n");
  }
  delay(3600000);  // Wait for 1h before taking another reading
}
