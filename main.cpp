#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Sta³e do ustawiania ró¿nych opcji widoku i skali
enum {
    FULL_WINDOW,
    ASPECT_1_1,
    ORTO,
    FRUST
};

// Zmienne globalne do przechowywania stanu aplikacji
GLint skala = FULL_WINDOW;
GLint rzut = ORTO;
GLfloat zakres = 5.0f;
GLfloat blisko = 1.0f;
GLfloat daleko = 50.0f;
GLdouble qq1 = 3;
GLdouble qq2 = 3;
GLdouble qq3 = 3;
GLdouble x2 = 0;
GLdouble y2 = 0;
GLdouble z2 = 0;
GLfloat cameraX = 0.0f, cameraY = 0.0f, cameraZ = 20.0f;

GLuint texture1, texture2;

// Parametry œwiat³a

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat light1_position[] = { -2.0f, -5.0f, -5.0f, 0.0f };
const GLfloat light1_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };

// Parametry materia³u
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

//dom
void drawHouse() {
    // Œciany boczne
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    // Przód
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-2.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(2.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(2.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-2.0, 1.0, 1.0);

    // Ty³
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-2.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(2.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(2.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-2.0, 1.0, -1.0);

    // Lewa œciana
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-2.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-2.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-2.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-2.0, 1.0, -1.0);

    // Prawa œciana
    glTexCoord2f(0.0, 0.0);
    glVertex3f(2.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(2.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(2.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(2.0, 1.0, -1.0);
    glEnd();

    // Dach
    glColor3f(0.5, 0.2, 0.0);
    glBegin(GL_TRIANGLES);
    // Dach przód
    glVertex3f(-2.0, 1.0, 1.0);
    glVertex3f(2.0, 1.0, 1.0);
    glVertex3f(0.0, 2.0, 0.0);

    // Dach ty³
    glVertex3f(-2.0, 1.0, -1.0);
    glVertex3f(2.0, 1.0, -1.0);
    glVertex3f(0.0, 2.0, 0.0);

    // Dach lewo
    glVertex3f(-2.0, 1.0, -1.0);
    glVertex3f(-2.0, 1.0, 1.0);
    glVertex3f(0.0, 2.0, 0.0);

    // Dach prawo
    glVertex3f(2.0, 1.0, -1.0);
    glVertex3f(2.0, 1.0, 1.0);
    glVertex3f(0.0, 2.0, 0.0);
    glEnd();

    // Drzwi
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -1.0, 1.01);
    glVertex3f(0.5, -1.0, 1.01);
    glVertex3f(0.5, 0.0, 1.01);
    glVertex3f(-0.5, 0.0, 1.01);
    glEnd();

    // Okna
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    // Okna przód
    glVertex3f(-1.5, 0.5, 1.01);
    glVertex3f(-0.5, 0.5, 1.01);
    glVertex3f(-0.5, 1.0, 1.01);
    glVertex3f(-1.5, 1.0, 1.01);

    glVertex3f(0.5, 0.5, 1.01);
    glVertex3f(1.5, 0.5, 1.01);
    glVertex3f(1.5, 1.0, 1.01);
    glVertex3f(0.5, 1.0, 1.01);

    // Okna ty³
    glVertex3f(-1.5, 0.5, -1.01);
    glVertex3f(-0.5, 0.5, -1.01);
    glVertex3f(-0.5, 1.0, -1.01);
    glVertex3f(-1.5, 1.0, -1.01);

    glVertex3f(0.5, 0.5, -1.01);
    glVertex3f(1.5, 0.5, -1.01);
    glVertex3f(1.5, 1.0, -1.01);
    glVertex3f(0.5, 1.0, -1.01);
    glEnd();
}

//podloga
void drawFloor() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-10.0f, -2.0f, -10.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-10.0f, -2.0f, 10.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(10.0f, -2.0f, 10.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(10.0f, -2.0f, -10.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void display(float size) {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(x2, y2, z2);
    glRotatef(qq1, 1.0f, 0.0f, 0.0f);
    glRotatef(qq2, 0.0f, 1.0f, 0.0f);
    glRotatef(qq3, 0.0f, 0.0f, 1.0f);
    drawHouse();
    glPopMatrix();

    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    drawFloor();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -cameraZ);
    glPopMatrix();
}



// Funkcja do ³adowania plików BMP
GLuint LoadTextureBMP(const char* filename) {
    GLuint texture;
    int width, height;
    unsigned char* data;
    FILE* file;

    if (fopen_s(&file, filename, "rb") != 0) return 0;
    if (file == NULL) return 0;
    width = 1024;
    height = 512;
    data = (unsigned char*)malloc(width * height * 3);
    if (data == NULL) {
        fclose(file);
        return 0;
    }
    if (fread(data, width * height * 3, 1, file) != 1) {
        free(data);
        fclose(file);
        return 0;
    }
    fclose(file);

    for (int i = 0; i < width * height; ++i) {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];
        data[index] = R;
        data[index + 2] = B;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}

void initTextures() {
    texture1 = LoadTextureBMP("texture1.bmp");
    texture2 = LoadTextureBMP("texture2.bmp");
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_0:
            rzut = ORTO;
            break;
        case GLFW_KEY_1:
            rzut = FRUST;
            break;
        case GLFW_KEY_2:
            skala = ASPECT_1_1;
            break;
        case GLFW_KEY_3:
            skala = FULL_WINDOW;
            break;
        case GLFW_KEY_A:
            qq1 += 6;
            break;
        case GLFW_KEY_D:
            qq1 -= 6;
            break;
        case GLFW_KEY_W:
            qq2 += 6;
            break;
        case GLFW_KEY_S:
            qq2 -= 6;
            break;
        case GLFW_KEY_Q:
            qq3 += 10;
            break;
        case GLFW_KEY_E:
            qq3 -= 10;
            break;
        case GLFW_KEY_Z:
            z2 += 2;
            break;
        case GLFW_KEY_X:
            z2 -= 2;
            break;
        case GLFW_KEY_O:
            x2 += 2;
            break;
        case GLFW_KEY_P:
            x2 -= 2;
            break;
        case GLFW_KEY_I:
            y2 += 2;
            break;
        case GLFW_KEY_U:
            y2 -= 2;
            break;
        case GLFW_KEY_K:
            cameraZ += 1;
            break;
        case GLFW_KEY_L:
            cameraZ -= 1;
            break;
        case GLFW_KEY_F:
            light_diffuse[0] = min(light_diffuse[0] + 0.1f, 1.0f);
            light_diffuse[1] = min(light_diffuse[1] + 0.1f, 1.0f);
            light_diffuse[2] = min(light_diffuse[2] + 0.1f, 1.0f);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
            break;
        case GLFW_KEY_G:
            light_diffuse[0] = max(light_diffuse[0] - 0.1f, 0.0f);
            light_diffuse[1] = max(light_diffuse[1] - 0.1f, 0.0f);
            light_diffuse[2] = max(light_diffuse[2] - 0.1f, 0.0f);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
            break;
        case GLFW_KEY_H:
            glDisable(GL_LIGHT0);
            break;
        case GLFW_KEY_J:
            glEnable(GL_LIGHT0);
            break;
        }
    }
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1200, 800, "Przykladowe Okno GLFW", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    initTextures();

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if (rzut == ORTO) {
            if (skala == ASPECT_1_1) {
                if (width < height && width > 0)
                    glOrtho(-zakres, zakres, -zakres * height / width, zakres * height / width, -zakres, zakres);
                else if (width >= height && height > 0)
                    glOrtho(-zakres * width / height, zakres * width / height, -zakres, zakres, -zakres, zakres);
            }
            else {
                glOrtho(-zakres, zakres, -zakres, zakres, -zakres, zakres);
            }
        }
        else if (rzut == FRUST) {
            if (skala == ASPECT_1_1) {
                if (width < height && width > 0)
                    glFrustum(-zakres, zakres, -zakres * height / width, zakres * height / width, blisko, daleko);
                else if (width >= height && height > 0)
                    glFrustum(-zakres * width / height, zakres * width / height, -zakres, zakres, blisko, daleko);
            }
            else {
                glFrustum(-zakres, zakres, -zakres, zakres, blisko, daleko);
            }
        }
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float squareSize = static_cast<float>(std::min(width, height)) * 0.2f;
        display(squareSize);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
