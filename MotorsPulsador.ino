/*
  class <NombreDeClase>{
  //Atributos
  //MetodoConstructor (Es el nombre de la clase)
  //El metodo constructo lo usamos para inicializar atributos.
  //Este solo se ejcuta una sola vez.
  //Metodos o acciones
  }
*/

class Led {
  private:
    int pin;

  public:
    Led(int p) {
      pin = p;
      pinMode(pin, OUTPUT);
    }
    void setPrenderLed() {
      digitalWrite(pin, HIGH);
    }
    void setApagarLed() {
      digitalWrite(pin, LOW);
    }

};

class Pulsador {
  private:
    int pin;
    bool flanco = HIGH;
    bool estado_anterior = !flanco;

    //metodo
  public:
    Pulsador(int p) {
      pin = p;

      pinMode(pin, INPUT);
    }

    void setFlanco(bool f) {
      flanco = f;
      estado_anterior = !flanco;
    }

    //metodos o acciones
    bool getIsPress() {
      bool estado_actual = digitalRead(pin);
      bool estado = (estado_anterior != estado_actual) && estado_actual == flanco;
      estado_anterior = estado_actual;
      return estado;
    }

    String getIsPressText() {
      if (getIsPress()) return "PRESS";
      else return "IS NOT PRESS";
    }

};

#define PIN_PULSADOR_1 3
#define PIN_PULSADOR_2 6
#define PIN_LED 13

Pulsador *p1 = new Pulsador(PIN_PULSADOR_1);
Pulsador *p2 = new Pulsador(PIN_PULSADOR_2);
Led *l1 = new Led(PIN_LED);

int contador = 0;
void setup() {
  Serial.begin(9600);
  p1->setFlanco(LOW);
  p2->setFlanco(HIGH);
}

void loop() {

  if (p1->getIsPress()) {
    Serial.println("p1 is press");
    l1->setPrenderLed();
  }

  if (p2->getIsPress()) {
    Serial.println("p2 is press");
    l1->setApagarLed();
  }


}


//Clase//
Motor
//Atributos
default_speed : int
pin_dir: int
pin_pwm: int 
speed: int
invert: bool
//Metodos o acciones
*  + stop() : void
*  + backward() : void 
*  + forward() : void 
*  + invertDirection() : void 
*  + setSpeed(int speed) : void

class Motor
{
private:
    int default_speed = 100;
    int pin_dir, pin_pwm, speed;
    bool invert;
public:
    Motor(int pdir, int ppwm)
    {
        pin_dir = pdir;
        pin_pwm = ppwm;
        pinMode(pin_dir, OUTPUT);
        pinMode(pin_pwm, OUTPUT);
        speed = default_speed;
    }
    void setSpeed(int s)
    {
        if (s >= 100)
        {
            s = 100;
        }
        else if (s <= 0)
        {
            s = 0;
        }
        int value = (int)s * 255 / 100;
        speed = value;
    }

    void forward()
    {
        digitalWrite(pin_dir, invert);
        analogWrite(pin_pwm, speed);
    }

    void backward() 
    {
        digitalWrite(pin_dir, !invert);
        //seteo la velocidad.
        analogWrite(pin_pwm, speed);
    }

    void invertDirection()
    {
        invert = !invert;
    }

    void stop() 
    {
        digitalWrite(pin_dir, LOW);
        analogWrite(pin_pwm, 0);
    }
};

#define PIN_MOTOR_DERECHO_DIR 4
#define PIN_MOTOR_DERECHO_PWM 5
#define PIN_MOTOR_IZQUIERDO_DIR 6
#define PIN_MOTOR_IZQUIERDO_PWM 7

Motor m1 = Motor(PIN_MOTOR_DERECHO_DIR, PIN_MOTOR_DERECHO_PWM);
Motor m2 = Motor(PIN_MOTOR_IZQUIERDO_DIR, PIN_MOTOR_IZQUIERDO_PWM);

void forward() //voy hacia adelante
{
    m1.forward();
    m2.forward();
}

void backward() //voy hacia atras
{
    m1.backward();
    m2.backward();
}

void left() //giro a la izquierda
{
    m1.forward();
    m2.backward();
}


void right() //giro a la derecha
{
    m1.backward();
    m2.forward();
}

void stopMotor() //freno
{
  m1.stop();
  m2.stop();
}

void setup()
{
    m1.invertDirection();
}

void loop()
{
    forward();
    delay(1000);
    backward();
    delay(1000);
    left();
    delay(1000);
    right();
    delay(1000);
    stopMotor();
    delay(1000);
}
