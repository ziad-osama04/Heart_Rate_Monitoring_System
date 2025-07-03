#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Wire.h>

// LCD setup
LiquidCrystal lcd(3, 5, 7, 9, 11, 13);

// Pulse Sensor setup
const int PulseWire = A0;
const int LED_3 = 1;
int Threshold = 550;
int Instructions_view = 500;

// Pulse Sensor object
PulseSensorPlayground pulseSensor;

// Signal filtering and scaling variables
int filteredSignal = 0;
const int rawMin = 500;
const int rawMax = 900;
const int bpmMin = 0;
const int bpmMax = 170;

// BPM averaging variables
const int numReadings = 10;
int bpmReadings[numReadings];
int readIndex = 0;
int total = 0;
int averageBPM = 0;

// Timer variables
unsigned long previousMillis = 0;
const long interval = 2000;

// ECG-like signal variables
unsigned long lastBeatTime = 0;
const int ecgCycleDuration = 1000;

// Gaussian function parameters for ECG simulation
const float pWaveAmplitude = 0.1;
const float qrsAmplitude = 1.0;
const float tWaveAmplitude = 0.2;
const float pWaveWidth = 0.03;
const float qrsWidth = 0.02;
const float tWaveWidth = 0.05;

// Signal smoothing variables
const int smoothingWindowSize = 10;
float smoothedECGSignal = 0;

// Function to generate synthetic ECG signal
float generate_ecg_signal(int raw_value) {
    float normalized_value;
    if (raw_value > 550) {
        normalized_value = (raw_value - 550) / 450.0;
    } else {
        normalized_value = 0;
    }

    static float t = 0;

    float p_wave = pWaveAmplitude * exp(-pow(t - 0.2, 2) / (2 * pow(pWaveWidth, 2)));
    float q_wave = 0.15 * exp(-pow(t - 0.45, 2) / (2 * pow(0.01, 2)));
    float r_wave = qrsAmplitude * exp(-pow(t - 0.5, 2) / (2 * pow(qrsWidth, 2)));
    float s_wave = -0.2 * exp(-pow(t - 0.55, 2) / (2 * pow(0.01, 2)));
    float qrs_complex = q_wave + r_wave + s_wave;
    float t_wave = tWaveAmplitude * exp(-pow(t - 0.75, 2) / (2 * pow(tWaveWidth, 2)));

    float ecg_signal = (p_wave + qrs_complex + t_wave);
    float scaled_ecg_signal = ecg_signal * normalized_value;

    t += 0.01;
    if (t > 1.0) {
        t = 0;
    }

    return scaled_ecg_signal;
}

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);

    // Initialize LCD
    lcd.begin(16, 2);
    lcd.print("HeartBeat Rate");
    lcd.setCursor(0, 1);
    lcd.print("  Monitoring  ");

    // Configure Pulse Sensor
    pulseSensor.analogInput(PulseWire);
    pulseSensor.blinkOnPulse(LED_3);
    pulseSensor.setThreshold(Threshold);

    // Check if Pulse Sensor started correctly
    if (pulseSensor.begin()) {
        Serial.println("Pulse Sensor started!");
    } else {
        Serial.println("Pulse Sensor failed to start.");
    }

    // Initialize BPM readings array
    for (int i = 0; i < numReadings; i++) {
        bpmReadings[i] = 0;
    }

    delay(200);
    lcd.clear();
}

void loop() {
    // Read and filter the signal
    int rawSignal = analogRead(PulseWire);
    filteredSignal = 0.9 * filteredSignal + 0.1 * rawSignal;

    // Scale the filtered signal to BPM range
    int scaledBPM = map(filteredSignal, rawMin, rawMax, bpmMin, bpmMax);
    scaledBPM = constrain(scaledBPM, bpmMin, bpmMax);

    // Detect heartbeat and calculate BPM
    if (pulseSensor.sawStartOfBeat()) {
        int myBPM = pulseSensor.getBeatsPerMinute();
        myBPM = scaledBPM;

        // Update BPM readings array
        total = total - bpmReadings[readIndex];
        bpmReadings[readIndex] = myBPM;
        total = total + bpmReadings[readIndex];
        readIndex = (readIndex + 1) % numReadings;

        // Print current BPM to Serial Monitor
        Serial.print("Current BPM: ");
        Serial.println(myBPM);

        // Update last heartbeat time
        lastBeatTime = millis();
    }

    // Generate ECG signal
    float ecg_value = generate_ecg_signal(rawSignal);

    // Smooth ECG signal using moving average filter
    static float ecgSignalBuffer[smoothingWindowSize];
    static int ecgSignalIndex = 0;
    ecgSignalBuffer[ecgSignalIndex] = ecg_value;
    ecgSignalIndex = (ecgSignalIndex + 1) % smoothingWindowSize;

    float sum = 0;
    for (int i = 0; i < smoothingWindowSize; i++) {
        sum += ecgSignalBuffer[i];
    }
    smoothedECGSignal = sum / smoothingWindowSize;

    // Send ECG signal to Serial Plotter
    Serial.print("ECG Signal:");
    Serial.println(smoothedECGSignal * 100);

    // Update LCD every 2 seconds
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        averageBPM = total / numReadings;

        // Print average BPM to Serial Monitor
        Serial.print("Average BPM over the last seconds: ");
        Serial.println(averageBPM);

        // Clear LCD and display updated BPM
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("H. R. :");
        lcd.print(averageBPM);
        lcd.print(" BPM");

        // Display heart rate status
        lcd.setCursor(0, 1);
        if (averageBPM >= 60 && averageBPM <= 100) {
            lcd.print("Status: Normal ");
        } else {
            lcd.print("Status:Abnormal ");
        }

        // Reset timer
        previousMillis = currentMillis;
    }

    delay(50); // Small delay for stability
}
