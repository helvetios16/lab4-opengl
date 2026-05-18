#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>

struct ColorRGB {
  float red;
  float green;
  float blue;
};

void exercise1_1() {
  static float angle = 0.0f;
  angle += 0.02f;
  glRotatef(angle * 180.0f / 3.14159f, 0.0f, 0.0f, 1.0f);

  float size = 0.5f;

  glColor3f(0.6f, 0.8f, 1.0f);
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i <= 360; i += 10) {
    float rad = i * 3.14159f / 180.0f;
    glVertex2f(cos(rad) * size, sin(rad) * size);
  }
  glEnd();

  glPushMatrix();
  glTranslatef(4.0f, 0.0f, 0.0f);
  glColor3f(0.8f, 0.5f, 0.2f);
  glutSolidTeapot(0.5f);
  glPopMatrix();
}

void exercise2() {
  static float angle = 0.0f;
  angle += 1.0f;

  glPushMatrix();
  glColor3f(0.6f, 0.8f, 1.0f);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(0.0f, 0.0f);
  for (int i = 0; i <= 360; i += 10) {
    float rad = i * 3.14159f / 180.0f;
    glVertex2f(cos(rad) * 2.0f, sin(rad) * 2.0f);
  }
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Movimiento orbital
  glTranslatef(8.0f, 0.0f, 0.0f);      // Radio de la orbita
  glRotatef(-angle, 0.0f, 0.0f, 1.0f); // Anular rotacion propia

  glColor3f(0.8f, 0.5f, 0.2f);
  glutSolidTeapot(1.5f);
  glPopMatrix();
}

void drawCube(float size) {
  float s = size / 2.0f;

  glBegin(GL_QUADS);
  glColor3f(0.2f, 0.4f, 0.8f);
  glVertex3f(-s, -s, s);
  glVertex3f(s, -s, s);
  glVertex3f(s, s, s);
  glVertex3f(-s, s, s);

  glColor3f(0.3f, 0.5f, 0.9f);
  glVertex3f(-s, -s, -s);
  glVertex3f(-s, s, -s);
  glVertex3f(s, s, -s);
  glVertex3f(s, -s, -s);

  glColor3f(0.1f, 0.3f, 0.7f);
  glVertex3f(-s, s, -s);
  glVertex3f(-s, s, s);
  glVertex3f(s, s, s);
  glVertex3f(s, s, -s);

  glColor3f(0.4f, 0.6f, 1.0f);
  glVertex3f(-s, -s, -s);
  glVertex3f(s, -s, -s);
  glVertex3f(s, -s, s);
  glVertex3f(-s, -s, s);

  glColor3f(0.25f, 0.45f, 0.85f);
  glVertex3f(s, -s, -s);
  glVertex3f(s, s, -s);
  glVertex3f(s, s, s);
  glVertex3f(s, -s, s);

  glColor3f(0.35f, 0.55f, 0.95f);
  glVertex3f(-s, -s, -s);
  glVertex3f(-s, -s, s);
  glVertex3f(-s, s, s);
  glVertex3f(-s, s, -s);
  glEnd();
}

void exercise3() {
  static float timer = 0.0f;
  static float armAngle = 0.0f;
  static float forearmAngle = 0.0f;
  static float cableLength = 0.0f;

  timer += 0.02f;
  armAngle = 20.0f * sin(timer * 0.5f);
  forearmAngle = 30.0f * sin(timer * 0.8f);
  cableLength = 1.0f + 0.5f * sin(timer * 0.3f);

  // base
  glPushMatrix();
  glColor3f(0.3f, 0.3f, 0.3f);
  glRectf(-2.0f, -0.25f, 2.0f, 0.25f);

  // brazo superior
  glTranslatef(0.0f, 0.25f, 0.0f);
  glRotatef(armAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, 2.0f, 0.0f);
  glColor3f(0.5f, 0.5f, 0.5f);
  glRectf(-0.4f, -2.0f, 0.4f, 2.0f);

  // antebrazo
  glTranslatef(0.0f, 2.0f, 0.0f);
  glRotatef(forearmAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, 1.5f, 0.0f);
  glColor3f(0.7f, 0.7f, 0.7f);
  glRectf(-0.3f, -1.5f, 0.3f, 1.5f);

  // polea
  glTranslatef(0.0f, 1.5f, 0.0f);
  glRotatef(-(armAngle + forearmAngle), 0.0f, 0.0f, 1.0f);

  // hilo
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(0.0f, -cableLength);
  glEnd();

  // cuadrado
  glTranslatef(0.0f, -cableLength, 0.0f);
  glColor3f(0.2f, 0.2f, 0.8f);
  glRectf(-0.5f, -1.0f, 0.5f, 0.0f);

  glPopMatrix();
}

void exercise4() {
  static float timer = 0.0f;
  static float posX = 0.0f;
  static int direction = 1;

  timer += 0.05f;
  posX += 0.05f * direction;

  // movimiento de caminata
  if (posX > 10.0f || posX < -10.0f)
    direction *= -1;

  float limbAngle = 25.0f * sin(timer);

  glPushMatrix();
  glTranslatef(posX, 0.0f, 0.0f);
  glColor3f(0.5f, 0.5f, 0.5f);

  // torso
  glRectf(-0.75f, -1.5f, 0.75f, 1.5f);

  // cabeza
  glPushMatrix();
  glTranslatef(0.0f, 2.0f, 0.0f);
  glRectf(-0.4f, -0.4f, 0.4f, 0.4f);
  glPopMatrix();

  // brazo derecho
  glPushMatrix();
  glTranslatef(0.75f, 1.25f, 0.0f);
  glRotatef(limbAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -0.75f, 0.0f);
  glRectf(-0.25f, -0.75f, 0.25f, 0.75f);
  glPopMatrix();

  // brazo izquierdo
  glPushMatrix();
  glTranslatef(-0.75f, 1.25f, 0.0f);
  glRotatef(-limbAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -0.75f, 0.0f);
  glRectf(-0.25f, -0.75f, 0.25f, 0.75f);
  glPopMatrix();

  // pierna derecha
  glPushMatrix();
  glTranslatef(0.4f, -1.5f, 0.0f);
  glRotatef(-limbAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -1.0f, 0.0f);
  glRectf(-0.35f, -1.0f, 0.35f, 1.0f);
  glPopMatrix();

  // pierna izquierda
  glPushMatrix();
  glTranslatef(-0.4f, -1.5f, 0.0f);
  glRotatef(limbAngle, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -1.0f, 0.0f);
  glRectf(-0.35f, -1.0f, 0.35f, 1.0f);
  glPopMatrix();

  glPopMatrix();
}

void exercise1() {
  static float angle = 0.0f;
  angle += 1.0f;

  glPushMatrix();
  glTranslatef(-5.0f, 0.0f, 0.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glColor3f(1.0f, 0.0f, 0.0f); // Rojo
  glutSolidCube(2.0f);
  glPopMatrix(); // Restauramos la matriz original

  // El cubo verde se traslada a la derecha.
  // Gracias al glPopMatrix() anterior, su posición es relativa al origen
  // (0,0,0) y no hereda la traslación ni rotación del cubo rojo.
  glPushMatrix();
  glTranslatef(5.0f, 0.0f, 0.0f);
  glRotatef(angle, 1.0f, 0.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f); // Verde
  glutSolidCube(2.0f);
  glPopMatrix();

  /*
     Si elimináramos glPopMatrix() después del cubo rojo, el cubo verde:
     1. Se trasladaría 5 unidades DESDE la posición del rojo (-5 + 5 = 0).
     2. Estaría rotando sobre el eje Y (heredado del rojo) Y sobre el eje X.
  */
}

void exercise5() {
  static float timer = 0.0f;
  timer += 0.02f;

  // Parametros de traslacion (movimiento horizontal y vertical)
  float Tx = 6.0f * sin(timer * 0.4f);
  float Ty = 3.0f * cos(timer * 0.25f);

  // Rotacion constante
  float theta = timer;
  float cosT = cos(theta);
  float sinT = sin(theta);

  // Escala pulsante
  float Sx = 1.0f + 0.4f * sin(timer * 0.6f);
  float Sy = 1.0f + 0.4f * sin(timer * 0.6f);

  // Matriz homogenea combinada M = T * R * S
  // T*R*S resulta en:
  // | cos(t)*Sx  -sin(t)*Sy  Tx |
  // | sin(t)*Sx   cos(t)*Sy  Ty |
  // |     0           0       1 |
  float M[2][3] = {
      {cosT * Sx, -sinT * Sy, Tx},
      {sinT * Sx, cosT * Sy, Ty},
  };

  // Vertigos del pentagono definidos manualmente en espacio local
  const int N = 5;
  float verts[N][2];
  for (int i = 0; i < N; i++) {
    float rad = i * 2.0f * 3.14159f / N - 3.14159f / 2.0f;
    verts[i][0] = cos(rad) * 3.0f;
    verts[i][1] = sin(rad) * 3.0f;
  }

  // Dibujar forma transformada aplicando M manualmente a cada vertice
  glColor3f(0.9f, 0.6f, 0.1f);
  glBegin(GL_POLYGON);
  for (int i = 0; i < N; i++) {
    float x = verts[i][0];
    float y = verts[i][1];
    float nx = M[0][0] * x + M[0][1] * y + M[0][2];
    float ny = M[1][0] * x + M[1][1] * y + M[1][2];
    glVertex2f(nx, ny);
  }
  glEnd();

  // Dibujar borde del pentagono para mejor visibilidad
  glColor3f(1.0f, 0.85f, 0.4f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < N; i++) {
    float x = verts[i][0];
    float y = verts[i][1];
    float nx = M[0][0] * x + M[0][1] * y + M[0][2];
    float ny = M[1][0] * x + M[1][1] * y + M[1][2];
    glVertex2f(nx, ny);
  }
  glEnd();
}

static void mat4_mul(float C[16], const float A[16], const float B[16]) {
  float tmp[16] = {};
  for (int col = 0; col < 4; col++)
    for (int row = 0; row < 4; row++)
      for (int k = 0; k < 4; k++)
        tmp[col * 4 + row] += A[k * 4 + row] * B[col * 4 + k];
  for (int i = 0; i < 16; i++)
    C[i] = tmp[i];
}

// Matrices en column-major (convencion de OpenGL):
// M[col*4 + row]

static void mat4_translation(float M[16], float tx, float ty, float tz) {
  float t[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1};
  for (int i = 0; i < 16; i++)
    M[i] = t[i];
}

static void mat4_rotZ(float M[16], float theta) {
  float c = cosf(theta), s = sinf(theta);
  float t[16] = {c, s, 0, 0, -s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  for (int i = 0; i < 16; i++)
    M[i] = t[i];
}

static void mat4_rotX(float M[16], float theta) {
  float c = cosf(theta), s = sinf(theta);
  float t[16] = {1, 0, 0, 0, 0, c, s, 0, 0, -s, c, 0, 0, 0, 0, 1};
  for (int i = 0; i < 16; i++)
    M[i] = t[i];
}

static void mat4_rotAxis(float M[16], float ax, float ay, float az,
                         float theta) {
  float len = sqrtf(ax * ax + ay * ay + az * az);
  float ux = ax / len, uy = ay / len, uz = az / len;
  float c = cosf(theta), s = sinf(theta), t = 1.0f - c;
  float tmp[16] = {ux * ux * t + c,
                   uy * ux * t + uz * s,
                   uz * ux * t - uy * s,
                   0,
                   ux * uy * t - uz * s,
                   uy * uy * t + c,
                   uz * uy * t + ux * s,
                   0,
                   ux * uz * t + uy * s,
                   uy * uz * t - ux * s,
                   uz * uz * t + c,
                   0,
                   0,
                   0,
                   0,
                   1};
  for (int i = 0; i < 16; i++)
    M[i] = tmp[i];
}

void exercise6() {
  static float x = -10.0f;
  static int dir = 1;
  static float selfAngle = 0.0f;
  static float timer = 0.0f;

  x += 0.06f * dir;
  if (x > 10.0f || x < -10.0f)
    dir *= -1;
  selfAngle += 0.05f;
  timer += 0.02f;

  // Traslacion horizontal sobre y=0
  float T[16];
  mat4_translation(T, x, 0.0f, 0.0f);

  // Rotacion sobre el propio eje Y
  float Ry[16];
  mat4_rotAxis(Ry, 0.0f, 1.0f, 0.0f, selfAngle);

  // Escala pulsante
  float s = 1.0f + 0.35f * sinf(timer * 0.7f);
  float S[16] = {
      s,    0.0f, 0.0f, 0.0f, 0.0f, s,    0.0f, 0.0f,
      0.0f, 0.0f, s,    0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
  };

  // M = T * Ry * S
  float TRy[16], TRS[16];
  mat4_mul(TRy, T, Ry);
  mat4_mul(TRS, TRy, S);

  glPushMatrix();
  glMultMatrixf(TRS);
  glColor3f(0.8f, 0.5f, 0.2f);
  glutSolidTeapot(1.5f);
  glPopMatrix();
}

// Ejercicio 1 rehecho con matrices homogeneas:
// tetera a 4 unidades del origen girando alrededor del eje Z
void exercise7() {
  static float angle = 0.0f;
  angle += 0.02f;

  float Rz[16];
  mat4_rotZ(Rz, angle);

  // Circulo en el origen (con la rotacion de escena aplicada)
  glPushMatrix();
  glMultMatrixf(Rz);
  glColor3f(0.6f, 0.8f, 1.0f);
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i <= 360; i += 10) {
    float rad = i * 3.14159f / 180.0f;
    glVertex2f(cosf(rad) * 0.5f, sinf(rad) * 0.5f);
  }
  glEnd();
  glPopMatrix();

  // Tetera: M = R_Z(angle) * T(4,0,0)
  // Primero se mueve a 4 unidades, luego rota alrededor del origen
  float T4[16];
  mat4_translation(T4, 4.0f, 0.0f, 0.0f);
  float M[16];
  mat4_mul(M, Rz, T4);

  glPushMatrix();
  glMultMatrixf(M);
  glColor3f(0.8f, 0.5f, 0.2f);
  glutSolidTeapot(0.5f);
  glPopMatrix();
}

// Ejercicio 2 rehecho con matrices homogeneas:
// circulo se mueve en X de -8 a 8 y la tetera orbita ese punto
void exercise8() {
  static float x = -8.0f;
  static int dir = 1;
  static float orbit = 0.0f;

  x += 0.05f * dir;
  if (x > 8.0f || x < -8.0f)
    dir *= -1;
  orbit += 0.02f;

  // Circulo: T(x, 0, 0)
  float Tx[16];
  mat4_translation(Tx, x, 0.0f, 0.0f);

  glPushMatrix();
  glMultMatrixf(Tx);
  glColor3f(0.6f, 0.8f, 1.0f);
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i <= 360; i += 10) {
    float rad = i * 3.14159f / 180.0f;
    glVertex2f(cosf(rad) * 0.5f, sinf(rad) * 0.5f);
  }
  glEnd();
  glPopMatrix();

  // Tetera: M = T(x,0,0) * R_Z(orbit) * T(4,0,0)
  // Primero se coloca a 4 unidades, luego orbita, luego se traslada con x
  float Rz[16], T4[16], tmp[16], M[16];
  mat4_rotZ(Rz, orbit);
  mat4_translation(T4, 4.0f, 0.0f, 0.0f);
  mat4_mul(tmp, Rz, T4); // R_Z * T(4,0,0)
  mat4_mul(M, Tx, tmp);  // T(x) * R_Z * T(4,0,0)

  glPushMatrix();
  glMultMatrixf(M);
  glColor3f(0.8f, 0.5f, 0.2f);
  glutSolidTeapot(0.5f);
  glPopMatrix();
}

// Ejercicio 3 rehecho con matrices homogeneas:
// tetera + toro que orbita la tetera + cubo independiente
void exercise9() {
  static float x = -8.0f;
  static int dir = 1;
  static float orbit = 0.0f;
  static float cubeOrbit = 0.0f;

  x += 0.05f * dir;
  if (x > 8.0f || x < -8.0f)
    dir *= -1;
  orbit += 0.02f;
  cubeOrbit += 0.02f;

  float Tx[16], Rz[16], T4[16];
  mat4_translation(Tx, x, 0.0f, 0.0f);
  mat4_rotZ(Rz, orbit);
  mat4_translation(T4, 4.0f, 0.0f, 0.0f);

  // Circulo: T(x, 0, 0)
  glPushMatrix();
  glMultMatrixf(Tx);
  glColor3f(0.6f, 0.8f, 1.0f);
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i <= 360; i += 10) {
    float rad = i * 3.14159f / 180.0f;
    glVertex2f(cosf(rad) * 0.5f, sinf(rad) * 0.5f);
  }
  glEnd();
  glPopMatrix();

  // Tetera: M = T(x) * R_Z(orbit) * T(4,0,0)
  float teapotBase[16], Mteapot[16];
  mat4_mul(teapotBase, Rz, T4);      // R_Z * T(4)
  mat4_mul(Mteapot, Tx, teapotBase); // T(x) * R_Z * T(4)

  glPushMatrix();
  glMultMatrixf(Mteapot);
  glColor3f(0.8f, 0.5f, 0.2f);
  glutSolidTeapot(0.5f);
  glPopMatrix();

  // Toro: M = T(x) * R_Z(orbit) * T(4) * R_Y(3*orbit) * T(3,0,0)
  // Orbita la tetera a 3 unidades, 3 veces mas rapido, sobre eje Y
  float RyFast[16], T3[16], tmp1[16], tmp2[16], Mtorus[16];
  // orbit ya esta en radianes, multiplicamos por 3
  mat4_rotAxis(RyFast, 0.0f, 1.0f, 0.0f, orbit * 3.0f);
  mat4_translation(T3, 3.0f, 0.0f, 0.0f);
  mat4_mul(tmp1, RyFast, T3);
  mat4_mul(tmp2, teapotBase, tmp1);
  mat4_mul(Mtorus, Tx, tmp2);

  glPushMatrix();
  glMultMatrixf(Mtorus);
  glColor3f(0.5f, 0.5f, 0.5f);
  glutSolidTorus(0.1f, 0.3f, 20, 20);
  glPopMatrix();

  // Cubo: M = T(x) * R_X(cubeOrbit) * T(0,3,0) * R_YZ(cubeOrbit*50 grados)
  float RxCube[16], Tup[16], RyzCube[16], cTmp1[16], cTmp2[16], Mcube[16];
  mat4_rotX(RxCube, cubeOrbit);
  mat4_translation(Tup, 0.0f, 3.0f, 0.0f);
  mat4_rotAxis(RyzCube, 0.0f, 1.0f, 1.0f,
               cubeOrbit * 50.0f * 3.14159f / 180.0f);
  mat4_mul(cTmp1, RxCube, Tup);
  mat4_mul(cTmp2, cTmp1, RyzCube);
  mat4_mul(Mcube, Tx, cTmp2);

  glPushMatrix();
  glMultMatrixf(Mcube);
  drawCube(2.0f);
  glPopMatrix();
}

static int currentExercise = 9;

static void key_callback(GLFWwindow *win, int key, int scancode, int action,
                         int mods) {
  if (action != GLFW_PRESS)
    return;
  if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9) {
    currentExercise = key - GLFW_KEY_0;
    printf("Ejercicio %d\n", currentExercise);
  }
  if (key == GLFW_KEY_ESCAPE)
    glfwSetWindowShouldClose(win, GLFW_TRUE);
}

int main(int argc, char **argv) {
  if (!glfwInit()) {
    return -1;
  }

  glutInit(&argc, argv);

  GLFWwindow *window = glfwCreateWindow(800, 800, "OpenGL Teapot", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    float size = 15.0f;
    if (width >= height)
      glOrtho(-size * aspect, size * aspect, -size, size, -100.0f, 100.0f);
    else
      glOrtho(-size, size, -size / aspect, size / aspect, -100.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0f); // Centrar la figura
    // Vista frontal 2D (sin rotaciones en X)

    switch (currentExercise) {
    case 1:
      exercise1();
      break;
    case 2:
      exercise2();
      break;
    case 3:
      exercise3();
      break;
    case 4:
      exercise4();
      break;
    case 5:
      exercise5();
      break;
    case 6:
      exercise6();
      break;
    case 7:
      exercise7();
      break;
    case 8:
      exercise8();
      break;
    case 9:
      exercise9();
      break;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
