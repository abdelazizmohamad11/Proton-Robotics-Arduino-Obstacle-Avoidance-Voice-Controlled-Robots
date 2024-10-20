/*
    Copyright 2021-2023 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#include <Picovoice_EN.h>
#include <Arduino_HTS221.h>
#include <Arduino_APDS9960.h>
#include <Arduino_LPS22HB.h>
#include "params.h"
#include "ScreenImages.h"
#include "timer.h"
#define MEMORY_BUFFER_SIZE (70 * 1024)

#define LED_PWR 25

static const char *ACCESS_KEY = "lVXOn6hWshtqhoePLXNehuwIZkBSCso85Kv48QrF2DMskcoxNY6Q3g=="; // AccessKey string obtained from Picovoice Console (https://picovoice.ai/console/)

static pv_picovoice_t *handle = NULL;

static int8_t memory_buffer[MEMORY_BUFFER_SIZE] __attribute__((aligned(16)));

static const float PORCUPINE_SENSITIVITY = 0.75f;
static const float RHINO_SENSITIVITY = 0.5f;
static const float RHINO_ENDPOINT_DURATION_SEC = 1.0f;
static const bool RHINO_REQUIRE_ENDPOINT = true;

bool isMoving = false;
static const int obstacleThreshhold = 210;
bool isAwake = false;



static void wake_word_callback(void) {
  Serial.println("Wake word detected!");
    displayImageWithText("?");

}
//
//static void inference_callback(pv_inference_t *inference) {
//    Serial.println("{");
//    Serial.print("    is_understood : ");
//    Serial.println(inference->is_understood ? "true" : "false");
//    if (inference->is_understood) {
//        Serial.print("    intent : ");
//        Serial.println(inference->intent);
//        if (inference->num_slots > 0) {
//            Serial.println("    slots : {");
//            for (int32_t i = 0; i < inference->num_slots; i++) {
//                Serial.print("        ");
//                Serial.print(inference->slots[i]);
//                Serial.print(" : ");
//                Serial.println(inference->values[i]);
//            }
//            Serial.println("    }");
//        }
//    }
//    Serial.println("}\n");
//    pv_inference_delete(inference);
//}
static void inference_callback(pv_inference_t *inference) {
  if (inference->is_understood) {
    RemoveTextFromImage();    
    if (strcmp(inference->intent, "showMeEmotions") == 0) {
      // Extract slot values
      const char *emotionState = NULL;
      for (int32_t i = 0; i < inference->num_slots; i++) {
        if (strcmp(inference->slots[i], "state") == 0) {
          emotionState = inference->values[i];
          break;
        }
      }

      // Perform action based on the detected intent and slot values
      if (emotionState != NULL) {
        if (strcmp(emotionState, "happy") == 0) {
          Serial.println("I am happy");
          Happy();
        } else if (strcmp(emotionState, "bored") == 0) {
          Serial.println("I am bored");
        } else if (strcmp(emotionState, "sad") == 0) {
          Serial.println("I am sad");
          Sad();
        } else if (strcmp(emotionState, "angry") == 0) {
          Serial.println("I am angry");
          Angry();
        }
        else if (strcmp(emotionState, "mad") == 0) {
          Serial.println("I am mad");
          Angry();
        }
      }
      else {
        Serial.println("Error: Missing required slot value.");
      }
    } else if (strcmp(inference->intent, "Movement") == 0) {
      const char *moveState = NULL;
      const char *directionState = NULL;
      for (int32_t i = 0; i < inference->num_slots; i++) {
        if (strcmp(inference->slots[i], "state1") == 0) {
          moveState = inference->values[i];
        }
        if (strcmp(inference->slots[i], "state2") == 0) {
          directionState = inference->values[i];
        }
      }

      if (moveState != NULL) {
        if (strcmp(moveState, "move") == 0) {
          isMoving = true;
          Serial1.write('0');
          if (strcmp(directionState, "forward") == 0) {
            Serial1.write('f');
            Serial.println("forward");
          }
          else if(strcmp(directionState, "backwards") == 0){
            Serial1.write('b');
            Serial.println("backwards");
          }
        } else if (strcmp(moveState, "turn") == 0) {
        } else if (strcmp(moveState, "rotate") == 0) {
          Serial.println("rotate");
          Serial.println(directionState);
        } else if (strcmp(moveState, "stop") == 0) {
          Serial1.write('s');
          Serial.println("Stop");
        }
      } else {
        Serial.println("Error: Missing required slot value.");
      }
    }
    else if (strcmp(inference->intent, "Attention") == 0) {
      const char *attentionState = NULL;
      for (int32_t i = 0; i < inference->num_slots; i++) {
        if (strcmp(inference->slots[i], "state") == 0) {
          attentionState = inference->values[i];
        }
      }

      if (attentionState != NULL) {
        if (strcmp(attentionState, "wake up") == 0) {
          isAwake = true;
          Serial.println("wake up");
          WakeUp();
        }
        else if (strcmp(attentionState, "sleep") == 0) {
          Serial.println("sleep");
          isAwake = false;
          Sleep();
        }
        else {
          Serial.println("Error: Missing required slot value.");
        }
      }
    }
    else if (strcmp(inference->intent, "Speed") == 0) {
      const char *speedState = NULL;
      const char *speedIntensityState = NULL;
      for (int32_t i = 0; i < inference->num_slots; i++) {
        if (strcmp(inference->slots[i], "state1") == 0) {
          speedState = inference->values[i];
        }
        if (strcmp(inference->slots[i], "state2") == 0) {
          speedIntensityState = inference->values[i];
        }
      }

      if (speedState != NULL) {
        if (strcmp(speedState, "increase") == 0) {
          Serial.println("increase");
        } else if (strcmp(speedState, "decrease") == 0) {
          Serial.println("decrease");
        }
        else {
          if (speedIntensityState != NULL) {
            Serial.println("set speed to");
            Serial.println(speedIntensityState);
          } else {
            Serial.println("to what!!");
          }
        }
      }
    }
    else if (strcmp(inference->intent, "Interaction") == 0) {
      const char *interactionState = NULL;
      for (int32_t i = 0; i < inference->num_slots; i++) {
        if (strcmp(inference->slots[i], "state") == 0) {
          interactionState = inference->values[i];
          break;
        }
      }

      if (interactionState != NULL) {
        if ((strcmp(interactionState, "hi") == 0) || (strcmp(interactionState, "hello") == 0)) {
          displayText("Hello!");
          Serial.println("hii");
        }
        else if (strcmp(interactionState, "a joke") == 0) {
          displayText("A Joke!");
        }
        else if (strcmp(interactionState, "yourself") == 0) {
          tellMeAboutYourself();
          Serial.println("i'm proton");
        }
      } else {
        Serial.println("Error: Missing required slot value.");
      }
    }
    else if (strcmp(inference->intent, "Environmental") == 0) {
      const char *environmentalState = NULL;
      for (int32_t i = 0; i < inference->num_slots; i++) {
        if (strcmp(inference->slots[i], "state") == 0) {
          environmentalState = inference->values[i];
        }
      }

      if (environmentalState != NULL) {
        if (strcmp(environmentalState, "information") == 0) {
          float temperature = HTS.readTemperature();
          float humidity  = HTS.readHumidity();
          float pressure = BARO.readPressure();
          // Convert float values to strings
          String tempString = String(temperature, 1); // Temperature with 1 decimal place
          String humidityString = String(humidity, 1); // Humidity with 1 decimal place
          String pressureString = String(pressure, 1); // Pressure with 1 decimal place

          // Construct the text to display
          String sensorData = tempString + " C\n" + humidityString + " %\n" + pressureString + " Pa";
          displayText(sensorData);
          Serial.println(sensorData);
        }
        else if (strcmp(environmentalState, "temperature") == 0) {
          float temperature = HTS.readTemperature();
          String tempString = String(temperature, 1);
          displayText(tempString + " C");
        }
        else if (strcmp(environmentalState, "humidity") == 0) {
          float humidity  = HTS.readHumidity();
          String humidityString = String(humidity, 1);
          displayText(humidityString + " %");
          Serial.println(humidityString + " %");
        }
      }
      else {
        //send data anyway because it detects environmental intent
        Serial.println("Error: Missing required slot value.");
      }
    }
    else if (strcmp(inference->intent, "Achnowledgment") == 0) {
      const char *acknowledgmentState = NULL;
      for (int32_t i = 0; i < inference->num_slots; i++) {
        if (strcmp(inference->slots[i], "state") == 0) {
          acknowledgmentState = inference->values[i];
        }
      }

      if (acknowledgmentState != NULL) {
        if ((strcmp(acknowledgmentState, "dumb") == 0) || (strcmp(acknowledgmentState, "rude") == 0) ||
            (strcmp(acknowledgmentState, "bad") == 0) || (strcmp(acknowledgmentState, "stupid") == 0)) {
          Serial.println("Mean Reactions");
          TooSad();
        }
        else if ((strcmp(acknowledgmentState, "intelligent") == 0) || (strcmp(acknowledgmentState, "smart") == 0) ||
                 (strcmp(acknowledgmentState, "fabulous") == 0) || (strcmp(acknowledgmentState, "amazing") == 0) || ((strcmp(acknowledgmentState, "great") == 0))) {
          Serial.println("nice Reactions");
          TooHappy();
        }
      } else {
        Serial.println("Error: Missing required slot value.");
      }
    }
    else {
      Serial.println("Unknown intent.");
      displayImageWithText("|");
    }

  }
  else {
    Serial.println("Unable to understand the command.");
    displayImageWithText("-");
  }

  pv_inference_delete(inference);
}
static void print_error_message(char **message_stack, int32_t message_stack_depth) {
  for (int32_t i = 0; i < message_stack_depth; i++) {
    Serial.println(message_stack[i]);
  }
}

void setup() {
  Serial.begin(9600);
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
  Sleep();



  // initialize the digital Pin as an output
  pinMode(LED_PWR, OUTPUT);

  pv_status_t status = pv_audio_rec_init();
  if (status != PV_STATUS_SUCCESS) {
    Serial.print("Audio init failed with ");
    Serial.println(pv_status_to_string(status));
    while (1);
  }

  char **message_stack = NULL;
  int32_t message_stack_depth = 0;
  pv_status_t error_status;

  status = pv_picovoice_init(
             ACCESS_KEY,
             MEMORY_BUFFER_SIZE,
             memory_buffer,
             sizeof(KEYWORD_ARRAY),
             KEYWORD_ARRAY,
             PORCUPINE_SENSITIVITY,
             wake_word_callback,
             sizeof(CONTEXT_ARRAY),
             CONTEXT_ARRAY,
             RHINO_SENSITIVITY,
             RHINO_ENDPOINT_DURATION_SEC,
             RHINO_REQUIRE_ENDPOINT,
             inference_callback,
             &handle);
  if (status != PV_STATUS_SUCCESS) {
    Serial.print("Picovoice init failed with ");
    Serial.println(pv_status_to_string(status));

    error_status = pv_get_error_stack(&message_stack, &message_stack_depth);
    if (error_status != PV_STATUS_SUCCESS) {
      Serial.println("Unable to get Porcupine error state");
      while (1);
    }
    print_error_message(message_stack, message_stack_depth);
    pv_free_error_stack(message_stack);

    while (1);
  }

  const char *rhino_context = NULL;
  status = pv_picovoice_context_info(handle, &rhino_context);
  if (status != PV_STATUS_SUCCESS) {
    Serial.print("retrieving context info failed with");
    Serial.println(pv_status_to_string(status));
    while (1);
  }
  Serial.println("Wake word: 'proton'");
  Serial.println(rhino_context);
  randomSeed(analogRead(0));
  Serial1.begin(9600);
}

void loop() {
  const int16_t *buffer = pv_audio_rec_get_new_buffer();
  if (buffer) {
    const pv_status_t status = pv_picovoice_process(handle, buffer);
    if (status != PV_STATUS_SUCCESS) {
      Serial.print("Picovoice process failed with ");
      Serial.println(pv_status_to_string(status));
      char **message_stack = NULL;
      int32_t message_stack_depth = 0;
      pv_get_error_stack(
        &message_stack,
        &message_stack_depth);
      for (int32_t i = 0; i < message_stack_depth; i++) {
        Serial.println(message_stack[i]);
      }
      pv_free_error_stack(message_stack);
      while (1);
    }
  }

  if (isMoving) {
    if (APDS.proximityAvailable()) {
      // read the proximity
      // - 0   => close
      // - 255 => far
      // - -1  => error
      int proximity = APDS.readProximity();
      if (proximity <= obstacleThreshhold) {
        Serial.println("obstacle detected");
        //send data to the other arduino to avoide obstacle
      }
    }
  }
  if (timerRunning) {
    unsigned long currentTime = millis();
    elapsedTime = currentTime - startTime;

    if (elapsedTime >= duration) {
      timerRunning = false;
      Serial.println("Timer expired!");
    }
  }
//  if(Serial.available()){
//    char c=Serial.read();
//    if(c=='0'){
//      startTimer(2,'m');
//    }
//    else if(c=='1'){
//      showTimerInfo(timerRunning,startTime,duration);
//    }
//    else if(c=='2'){
//      resetTimer();
//    }
//  }
}
