#include <Arduino.h>
#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

// Firebase configuration
#define FIREBASE_HOST "arduinotrafficcontrol-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "AIzaSyDTwLmVpOGNTc71mDnN14mgE6GMwTrqQuw"

// WiFi credentials
#define WIFI_SSID "..."
#define WIFI_PASSWORD "hello12345"

// LED pins
const int RED_LED_PIN = 5;
const int YELLOW_LED_PIN = 6;
const int GREEN_LED_PIN = 7;

// Firebase data path for LED status
const String firebasePath = "/light/led";

// Firebase object
FirebaseData firebaseData;

void setup()
{
    // Initialize serial communication
    Serial.begin(9600);
    
    // Initialize LED pins as output
    setupLEDs();
    
    // Connect to Wi-Fi
    connectToWiFi();
    
    // Initialize Firebase connection
    initializeFirebase();
    
    // Set initial LED status in Firebase to "OFF"
    updateFirebaseLEDStatus("OFF");
}

void loop()
{
    // Get current LED status from Firebase
    String ledStatus = fetchFirebaseLEDStatus();
    
    // Control LEDs based on the status retrieved
    handleLEDStatus(ledStatus);
    
    delay(1000); // Pause for a second between updates
}

// Function to set up the LED pins
void setupLEDs()
{
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    controlLEDs(LOW, LOW, LOW); // Ensure all LEDs are off at the start
}

// Function to connect to Wi-Fi
void connectToWiFi()
{
    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID);
    
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Function to initialize Firebase connection
void initializeFirebase()
{
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
    Firebase.reconnectWiFi(true); // Enable Wi-Fi reconnection
}

// Function to update LED status in Firebase
void updateFirebaseLEDStatus(const String &status)
{
    if (Firebase.setString(firebaseData, firebasePath, status))
    {
        Serial.print("Updated Firebase status to: ");
        Serial.println(status);
    }
    else
    {
        Serial.print("Failed to update Firebase. Error: ");
        Serial.println(firebaseData.errorReason());
    }
}

// Function to fetch LED status from Firebase
String fetchFirebaseLEDStatus()
{
    if (Firebase.getString(firebaseData, firebasePath))
    {
        return firebaseData.stringData();
    }
    else
    {
        Serial.print("Error fetching Firebase status: ");
        Serial.println(firebaseData.errorReason());
        return "ERROR"; // Return error if unable to fetch
    }
}

// Function to control the LEDs based on received statuses
void handleLEDStatus(const String &status)
{
    if (status == "RED")
    {
        controlLEDs(HIGH, LOW, LOW); // Red LED on
        Serial.println("Red LED ON");
    }
    else if (status == "YELLOW")
    {
        controlLEDs(LOW, HIGH, LOW); // Yellow LED on
        Serial.println("Yellow LED ON");
    }
    else if (status == "GREEN")
    {
        controlLEDs(LOW, LOW, HIGH); // Green LED on
        Serial.println("Green LED ON");
    }
    else if (status == "OFF")
    {
        controlLEDs(LOW, LOW, LOW); // All LEDs off
        Serial.println("All LEDs OFF");
    }
    else
    {
        Serial.print("Unknown status from Firebase: ");
        Serial.println(status);
    }
}

// Function to control individual LED states
void controlLEDs(int red, int yellow, int green)
{
    digitalWrite(RED_LED_PIN, red);
    digitalWrite(YELLOW_LED_PIN, yellow);
    digitalWrite(GREEN_LED_PIN, green);
}