#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>

struct ColorRGB {
  float red;
  float green;
  float blue;
};

void exerce2_1() {
  // decidir el angulo de giro
  static float angle = 0.0f;
  angle += 0.02f;
  glRotatef(angle * 180.0f / 3.14159f, 0.0f, 0.0f, 1.0f);

  float size = 0.5f;

  // dibujar circulo
  glColor3f(0.6f, 0.8f, 1.0f);
  glBegin(GL_TRIANGLE_FAN);
  for (int i = 0; i <= 360; i += 10) {
    float rad = i * 3.14159f / 180.0f;
    glVertex2f(cos(rad) * size, sin(rad) * size);
  }
  glEnd();

  // dibujar tetera
  glPushMatrix();
  glTranslatef(4.0f, 0.0f, 0.0f);
  glColor3f(0.8f, 0.5f, 0.2f);
  glutSolidTeapot(0.5f);
  glPopMatrix();
}

void exerce2() {
  static float angle = 0.0f;
  angle += 1.0f;

  // Dibujar circulo central como referencia
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

  // Orbita de la tetera sin rotacion propia
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

void exerce3() {
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

void exerce4() {
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

void exerce1() {
  static float angle = 0.0f;
  angle += 1.0f;

  // --- DEMOSTRACIÓN DE USO CORRECTO ---
  // El cubo rojo se traslada y rota independientemente.
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

    // exerce1();
    // exerce2();
    // exerce3();
    exerce4();
    // exerce5();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Limpiar al salir
  glfwTerminate();
  return 0;
}
