#include <dht.h>
#include <EEPROM.h>

dht DHT;

//150 Hours of Collecting Data and 150 Hour of Prediction to Re-Write the Table
//6.25 Day of Collecting Data and 6.25 Day of Prediction to Re-Write the Table

long int gap = 10;                          // Time Period Between Samples taking              : 15 min900000
const int SAMPLE_SIZE = 2040;                // Number of Samples used to calculate a and b     : 600 time : max 2040
float hum_samples[SAMPLE_SIZE];
float temp_samples[SAMPLE_SIZE];

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
int prd = 0;
float predicted_temp;


void loop() {

  //Collecting data 680 2040

  if (prd == 0) {
    for (int i = 0, j = SAMPLE_SIZE ; i < SAMPLE_SIZE ; i++, j++) {

      int chk = DHT.read11(2);  // Read humidity and temperature from DHT11 sensor

      //check availblity of the sensor
      if (chk == -1) {

        humidity = DHT.humidity;   // Get the humidity value
        temperature = DHT.temperature;  // Get the temperature value

        //filling the table

        // Add new humidity and temperature readings to the samples lists
        EEPROM.write(i, humidity);                       //x
        EEPROM.write(j, temperature);                    //y

        // Print humidity, temperature to serial monitor
        Serial.print("\n ");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(j);
        Serial.print(" | Humidity: ");
        Serial.print(humidity);
        Serial.print("% |");
        Serial.print(" Temperature: ");
        Serial.print(temperature);
        Serial.print("C \n");

        delay(gap);     // Wait before taking another reading
      }
    }

    // Calculate a and b values based on the current samples lists

    // Calculate sum of lists
    float sum_hum = 0, sum_temp = 0, sum_humtemp = 0, sum_cubetemp = 0, sum_cubehum = 0;

    for (int ii = 0, jj = SAMPLE_SIZE ; ii < SAMPLE_SIZE ; ii++, jj++) {

      sum_hum += EEPROM[ii];                            //sum of exesting listed data humidity        //sum of x
      sum_temp += EEPROM[jj];                           //sum of exesting listed data temperature     //sum of y
      sum_humtemp += EEPROM[ ii ] * EEPROM[ jj ];       //sum of exesting listed data humtemp         //sum of xy
      sum_cubehum += EEPROM[ ii ] * EEPROM[ ii ];       //sum of exesting listed data cubehum         //sum of xx
      sum_cubetemp += EEPROM[ jj ] * EEPROM[ jj ];      //sum of exesting listed data cubetemp        //sum of yy

    }

    // Calculate avg of lists
    float avg_hum = sum_hum / SAMPLE_SIZE;                                          //avg of x
    float avg_temp = sum_temp / SAMPLE_SIZE;                                        //avg of y
    float avg_humtemp = sum_humtemp / SAMPLE_SIZE;                                  //avg of xy
    float avg_cubehum = sum_cubehum / SAMPLE_SIZE;                                      //avg of xx
    float avg_cubetemp = sum_cubetemp / SAMPLE_SIZE;                                    //avg of yy

    // Calculate a and b
    float num = avg_humtemp - avg_hum * avg_temp;
    float den = avg_cubehum - avg_cubetemp;

    a = num / den;                                                                  //a
    b = avg_temp - a * avg_hum;                                                     //b

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
  }
  prd = 1;   //to never enter the collecting again

  
    //Print old a and b to serial monitor
      Serial.print("\nOLD a&b : \n");
      Serial.print("a : ");
      Serial.print(a);
      Serial.print("  b : ");
      Serial.print(b);
      Serial.print("\n"); 
  //
  //  // Use the current humidity value to predict the temperature using old a and b
  //  float prv_pred_temp = a * humidity + b;
  //
  //
  //  int chk = DHT.read11(2);  // Read humidity and temperature from DHT11 sensor
  //
  //  //check availblity of the sensor
  //  if (chk == -1) {
  //
  //    humidity = DHT.humidity;        // Get the humidity value
  //    temperature = DHT.temperature;  // Get the temperature value
  //
  //    //filling the table
  //
  //    // Update by adding new humidity and temperature readings to the samples lists (erease from top)
  //    hum_samples[index] = humidity;                        //x
  //    temp_samples[index] = temperature;                    //y
  //    humtemp_samples[index] = humidity * temperature;      //xy
  //    cubehum_samples[index] = humidity * humidity;         //xx
  //    cubetemp_samples[index] = temperature * temperature;  //yy
  //
  //    index = (index + 1) % SAMPLE_SIZE;                    // start over from 0 after surpassing SAMPLE SIZE
  //
  //    // Calculate new a and b values based on the current samples lists
  //
  //    // Calculate sum of lists
  //    float sum_hum = 0, sum_temp = 0, sum_humtemp = 0, sum_cubetemp = 0, sum_cubehum = 0;
  //    for (int i = 0; i < SAMPLE_SIZE; i++) {
  //      sum_hum += hum_samples[i];                            //sum of exesting listed data humidity        //sum of x
  //      sum_temp += temp_samples[i];                          //sum of exesting listed data temperature     //sum of y
  //      sum_humtemp += hum_samples[i] * temp_samples[i];      //sum of exesting listed data humtemp         //sum of xy
  //      sum_cubetemp += temp_samples[i] * temp_samples[i];    //sum of exesting listed data cubetemp        //sum of yy
  //      sum_cubehum += hum_samples[i] * hum_samples[i];       //sum of exesting listed data cubehum         //sum of xx
  //    }
  //    // Calculate avg of lists
  //    float avg_hum = sum_hum / SAMPLE_SIZE;                                              //avg of x
  //    float avg_temp = sum_temp / SAMPLE_SIZE;                                            //avg of y
  //    float avg_humtemp = sum_humtemp / SAMPLE_SIZE;                                      //avg of xy
  //    float avg_cubehum = sum_cubehum / SAMPLE_SIZE;                                      //avg of xx
  //    float avg_cubetemp = sum_cubetemp / SAMPLE_SIZE;                                    //avg of yy
  //
  //    // Calculate a and b
  //    float num = avg_humtemp - avg_hum * avg_temp;
  //    float den = avg_cubehum - avg_cubetemp;
  //
  //    a = num / den;                                                                  //a
  //    b = avg_temp - a * avg_hum;                                                     //b
  //
  //    //Print new a and b to serial monitor
  //    /*Serial.print("\nNEW a&b : \n");
  //      Serial.print("a : ");
  //      Serial.print(a);
  //      Serial.print("  b : ");
  //      Serial.print(b);
  //      Serial.print("\n");*/
  //
  //    // Use the current humidity value to predict the temperature
  //    predicted_temp = a * humidity + b;
  //
  //    // Print humidity, temperature, predicted temperature, prv predicted temperature and error to serial monitor
  //    //Serial.print("\nDATA : \n");
  //    Serial.print("\n ");
  //    Serial.print(index);
  //    Serial.print(" | Humidity: ");
  //    Serial.print(humidity);
  //    Serial.print("% |");
  //    Serial.print(" Temperature: ");
  //    Serial.print(temperature);
  //    Serial.print("C |");
  //    Serial.print(" Predicted temperature: ");
  //    Serial.print(predicted_temp);
  //    Serial.print("C |");
  //    Serial.print(" Prv Predicted temperature: ");
  //    Serial.print(prv_pred_temp);
  //    Serial.print("C |");
  //    Serial.print(" Error: ");
  //    Serial.print((predicted_temp - temperature) * (predicted_temp - temperature));
  //    Serial.print("\n");
  //  }
  //
  //  delay(gap);  // Wait before taking another reading
}
