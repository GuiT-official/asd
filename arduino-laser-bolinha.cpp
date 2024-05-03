const int ldrPin = A0; // Define o pino analógico conectado ao LDR.
int ldrValue; // Variável para armazenar o valor lido do LDR.
const int ligado = 850; // Valor mínimo do LDR para a ativação.
int t = 0; // Tempo.
int a = 0; // Estado. O inicial (0) é o laser sem interrupção.

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial.
}

void loop() {
  ldrValue = analogRead(ldrPin); // Lê o valor do LDR.
  if (ldrValue > ligado) {
    if (a == 1) {
      a++; // Quando o objeto ultrapassar completamente o laser - ativando o tal novamente -, passa pro estágio 2, que é esperar a próxima interrupção.
    } else if (a == 3) {
      a = 0; // Volta pro estágio 0
      t = 0;
      delay(1000);
    }
  } else if {
    if (a == 0) {
      a++; // Passa pro estágio 1, que é o objeto atravessando o laser.
      Serial.println("Comecou!");
    } else if (a == 2) {
      a++; // A interrupção do laser ocorre, iniciando o estágio 3 (final), que é printar o resultado.
      Serial.println(t);
    }
  }
  if (a > 0) {
    t++; // Se o estágio for maior que 0, inicia a contagem.
  }
  delay(1); // Tempo de 1 milisegundo entre cada loop.
}
