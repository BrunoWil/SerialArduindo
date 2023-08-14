
#include <stdio.h>
#include <stdlib.h>
#define tamanho 10 //Tamanho maximo
#define flista 255

/*
Licença MIT

Direitos Autorais (C) 2022, Bruno Wilson Moura Do Nascimento e Kildary Jucá Cajazeiras

Permissão é concedida, gratuitamente, a qualquer pessoa que obtenha uma cópia deste software e arquivos de documentação associados (o "Software") , para lidar no Software sem restrições, incluindo, sem limitação; os direitos usar, copiar, modificar, mesclar, publicar, distribuir, sublicenciar e / ou vender cópias do Software e para permitir que pessoas a quem c Software seja fornecido para tal, sujeito às seguintes condições :

— O aviso de "direitos autorais" acima e este aviso de permissão devem ser incluídos em todas as cópias ou partes substanciais do Software.

O SOFTRARE É FORNECIDO "COMO ESTÁ", SEM GARANTIA DE QUALQUER TIPO, EXPRESSA OU IMPLÍCITA, INCLUINDO, MAS NÃO SE LIMITANDO Às GARANTIAS DE COMERCIALIZAÇÃO, ADEQUAÇÃO À UM DETERMINADO FIM E NÃO VIOLAÇÃO. EM NENHUMA CIRCUNSTÂNCIA AUTORES OU DETENTORES DOS DIREITOS AUTORAIS SERÃO RESPONSABILIZADOS POR QUAISQUER REIVINDICAÇÕES, DANOS OU OUTRAS RESPONSABILIDADE, SEJA DE CONTRATO, DELITO OU OUTRO, DECORRENTE DE, FORA OU RELACIONADA COM O SOFTWARE OU O USO OU OUTRAS CONCESSÕES O SOFTWARE.
*/

/*
A Entrada é de dois pontos de que são duas array de dois elementos e um matriz de bits.
A saida é uma lista de pontos e uma matriz de btis.

*/

// Variaveis utilizadas
int deltaX, deltaY, deltaXM, deltaYM, aux;
float x0, x1, y0, y1;
float m, b;
//int ponto[2];
int ponto0[2];
int ponto1[2];


// lista de pontos
uint8_t listaPonto[tamanho + 2][2] = {};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  raster();



}

void loop() {

}

/*
int main (void){
  Serial.println("Digite o tamanho matriz quadada");

 
  Serial.println("Digite o x0");
  while (Serial.availableForWrite() == 0) {}
  delay(5000);

  ponto0[0] = Serial.parseFloat();
  Serial.println(ponto0[0]);

 
 
  Serial.println("Digite o y0");

  while (Serial.availableForWrite() == 0) {}  
  delay(5000);

  ponto0[1] = Serial.parseFloat();
  Serial.println(ponto0[1]);




  Serial.println("Digite o x1");
  while (Serial.availableForWrite() == 0) {}  
  delay(5000);
  

  ponto1[0] = Serial.parseFloat();
  Serial.println(ponto1[0]);
  



  Serial.println("Digite o y1");

  while (Serial.availableForWrite() == 0) {}  
  delay(5000);

  ponto1[1] = Serial.parseFloat();
  Serial.println(ponto1[1]);


  while (Serial.available() == 0) {}  

  raster(); 
  return 1; 
}
*/

void raster() {


  // uint8_t matrizDeBits[tamanho+2][tamanho+2]={};//indicado int 8 bits

  // Testes de pontos
  int ponto0[2] = {0,0};
  int ponto1[2] = {0,tamanho};


  // int ponto0[2] = {0,0};
  // int ponto1[2] = {tamanho,0};

  // int ponto0[2] = { 0, 0 };
  // int ponto1[2] = { tamanho, tamanho };

  // int ponto0[2] = {0,tamanho};
  // int ponto1[2] = {tamanho,0};

  // int ponto0[2] = {tamanho,0};
  // int ponto1[2] = {0,tamanho};

  deltaX = ponto1[0] - ponto0[0];
  deltaY = ponto1[1] - ponto0[1];

  // tesde de delta se ambos for negativos troca os pontos
  if (deltaX < 0 & deltaY < 0) {
    aux = ponto0[0];
    ponto0[0] = ponto1[0];
    ponto1[0] = aux;

    aux = ponto0[1];
    ponto0[1] = ponto1[1];
    ponto1[1] = aux;

    deltaX = abs(deltaX);
    deltaY = abs(deltaY);
  }

  // Coeficientes e delta modulo
  m = 0;
  b = 0;
  deltaXM = abs(deltaX);
  deltaYM = abs(deltaY);

  if (deltaXM != 0) {
    m = deltaY / deltaX;
    b = ponto0[1] - m * ponto0[0];
  }

  x0 = ponto0[0];
  y0 = ponto0[1];
  x1 = ponto1[0];
  y1 = ponto1[1];

  // reta anda em igual velocidade em x e y

  if (deltaYM == deltaXM) {
    int i = 0;

    if (y0 < y1) {
      if (x0 <= x1) {
        while (x0 <= x1) {
          listaPonto[i][0] = x0;
          listaPonto[i][1] = y0;

          i++;
          y0++;
          x0++;
        }
      } else {
        while (x0 >= x1) {
          listaPonto[i][0] = x0;
          listaPonto[i][1] = y0;

          i++;
          y0++;
          x0--;
        }
      }
    } else {
      if (y0 > y1) {
        if (x0 <= x1) {
          while (x0 <= x1) {
            listaPonto[i][0] = x0;
            listaPonto[i][1] = y0;

            i++;
            x0++;
            y0--;
          }
        } else {
          while (x0 >= x1) {
            listaPonto[i][0] = x0;
            listaPonto[i][1] = y0;

            i++;
            x0++;
            y0--;
          }
        }
      }
    }
    listaPonto[i][0] = flista;
    listaPonto[i][1] = flista;
  }

  else {

    // reta anda em maior velocidade no eixo x
    if (deltaXM > deltaYM) {
      int i = 0;
      if (x0 <= x1) {
        while (x0 <= x1) {
          // printf("%f",x0);
          listaPonto[i][0] = x0;
          listaPonto[i][1] = y0;

          i++;
          x0++;
          if (deltaY != 0) {
            y0 = m * x0 + b;
          }
        }
      } else {
        aux = x0;
        int i = 0;
        while (x1 <= aux) {
          listaPonto[i][0] = x0;
          listaPonto[i][1] = y0;

          i++;
          x1++;
          x0--;
          if (deltaY != 0) {
            y0 = m * x0 + b;
          }
        }
      }
      listaPonto[i][0] = flista;
      listaPonto[i][1] = flista;
    }

    // reta anda em maior velocidade no eixo y
    if (deltaXM < deltaYM) {
      int i = 0;
      if (y0 < y1) {

        while (y0 <= y1) {
          listaPonto[i][0] = x0;
          listaPonto[i][1] = y0;

          i++;
          y0++;
          if (deltaX != 0) {
            x0 = (y0 - b) / m;
          }
        }
      } else {
        aux = y0;
        int i = 0;
        while (y1 <= aux) {
          listaPonto[i][0] = x0;
          listaPonto[i][1] = y0;

          i++;
          y1++;
          y0--;
          if (deltaX != 0) {
            x0 = (y0 - b) / m;
          }
        }
      }
      listaPonto[i][0] = flista;
      listaPonto[i][1] = flista;
    }
  }
  printListaPontos();

  Serial.print("Lista de pontos ");
  Serial.print(sizeof(listaPonto), DEC);
  Serial.println(" byte");
}


void printListaPontos() {
    Serial.print("Tamanho:");
    Serial.println(tamanho,DEC);

  // Mostra lista de pontos do ponto inicial ate o final
  for (int i = 0; i < tamanho + 2; i++) {
    Serial.print(listaPonto[i][0], DEC);
    Serial.print(",");
    Serial.print(listaPonto[i][1], DEC);
    Serial.println("");
  }
  printMatrizImagem();
}

void printMatrizImagem() {
  Serial.println("Inicio");

  for (int i = tamanho-1; i >= 0; i--) {
    for (int j = 0; j < tamanho ; j++) {
      int flag = 0;
      int k = 0;
      while (k < tamanho) {
        if (i == listaPonto[k][0] & j == listaPonto[k][1]) {
          Serial.print(1, DEC);

          flag = 1;
          break;
        }
        k++;
      }
      if (flag == 0) {
        Serial.print(0, DEC);

        
      }
    }
    Serial.println();

  }
  
  Serial.println("Fim");

}


