// ESTUDIANTE: ALBA MARÍA RODAS VELÁSQUEZ}
// LABORATORIO NO.5 - ELECTRÓNICA DIGITAL 2.
//////////////////////////////////////////// 
// DEFINICION DEL PINES A UTILIZAR:
// LEDS:

//////////////////////////////////////////////////////////////////

#define LED_01 23 // LED NO. 1 --> CELESTE.
#define LED_02 22 // LED NO. 2 --> VERDE.
#define LED_03 21 // LED NO. 3 --> ROSADITO.
#define LED_04 19
#define LED_05 18

// DEFINIR FRECUENCIA PARA FUNCIONAMIENTO DEL PWM:
const int frecuencia = 5000; // IGUAL QUE VIDEO
const int resolucion = 12;

// MILLIS:
unsigned long tiempo = 0;

// EJEMPLO VISTO EN INTERNET, SIMILAR MÁS NO IGUAL.
// EL PLAN ES IR JUGANDO CON LOS ESTADOS DE LA LED, PARA DESACTIVAR LA LED AL APACHAR DE NUEVO.
int ESTADO_L01;
int ESTADO_L02;
int ESTADO_L03;
int ESTADO_L04;
int ESTADO_L05;

AdafruitIO_Group *L05 = io.group("l05");

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  // wait for serial monitor to open
  while(! Serial);
  
  Serial.print("Connecting to Adafruit IO");
  // connect to io.adafruit.com
  io.connect();
  
  // ASIGNAMOS FUNCIONES PARA LLAMAR A LOS FEEDS:
  L0->onMessage("l05.l4", d); // LEDS DE POTS
  L0->onMessage("l05.l5", e); // LEDS DE POTS
  //LED NORMAL:
  L0->onMessage("l05.l1", a);
  L0->onMessage("l05.l2", b);
  L0->onMessage("l05.l3", c);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
}

  // visto en ejemplo proporcionado:
  // we are connected
  Serial.println();
  Serial.println(io.statusText());  
  // OUTPUTS:
  pinMode(LED_01, OUTPUT);
  pinMode(LED_02, OUTPUT);
  pinMode(LED_03, OUTPUT);

  // CONFIGURACION PWM:
  ledcSetup(0, frecuencia, resolucion);
  // ledcWrite(channel, dutycycle):
  // to control the LED brightness using PWM, you use the following function.
  // --> attach the channel to the GPIO to be controlled
  ledcAttachPin(LED_04, 0);
  delay(20);
    // to control the LED brightness using PWM, you use the following function.
  // --> attach the channel to the GPIO to be controlled
  ledcSetup(1, frecuencia, resolucion);
  ledcAttachPin(LED_05, 1);

  Serial.println("Input de: '1' para solicitar datos de Adafruit IO.");
}
void loop() 
{
  // put your main code here, to run repeatedly:
  io.run();

  // ACTIVACIÓN DE LEDS:
  digitalWrite(LED_01, ESTADO_L01);
  digitalWrite(LED_02, ESTADO_L02);
  digitalWrite(LED_03, ESTADO_L03);

  // MODIFICACION DE LEDS SEGUN LECTURA DE POTS:
  // Channel 0, Channel 1.
  ledcWrite(0, ESTADO_L04);
  delay(20);
  // Channel 0, Channel 1.
  ledcWrite(1, ESTADO_L05);
  delay(20);
  
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    if (command == "1") 
    {
      L05->get();
    }
  }
}
void a(AdafruitIO_Data *data)
{
  Serial.print("Led_01 --->");
  Serial.println(data->toPinLevel());
  ESTADO_L01 = data->toPinLevel();
}

void b(AdafruitIO_Data *data)
{
  Serial.print("Led_02 --->");
  Serial.println(data->toPinLevel());
  ESTADO_L02 = data->toPinLevel();
}

void c(AdafruitIO_Data *data)
{
  Serial.print("Led_03 --->");
  Serial.println(data->toPinLevel());
  ESTADO_L03 = data->toPinLevel();
}
void d(AdafruitIO_Data *data)
{
  Serial.print("Led_04 --->");
  Serial.println(data->toPinLevel());
  ESTADO_L04 = data->toPinLevel();
}
void e(AdafruitIO_Data *data)
{
  Serial.print("Led_05 --->");
  Serial.println(data->toPinLevel());
  ESTADO_L05 = data->toPinLevel();
}
