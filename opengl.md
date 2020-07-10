## OpenGL

### Clock

```c
# gcc -o clock clock.c -framework GLUT -framework OpenGL

#include <stdio.h>
#include <GLUT/glut.h>
#include <time.h>
#include <math.h>

float angle = 0.0;
void
handleDisplay(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLineWidth(2.5);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(sin(angle), cos(angle), 0);
  glEnd();

  glutSwapBuffers();
}

void
handleKeyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
  }
}

char buffer[80];
time_t rawtime;
struct tm * timeinfo;

void
handleRender(void)
{
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );

  angle = timeinfo->tm_sec * 6 * M_PI / 180.0;

  sprintf(buffer, "%f", sin(angle));
  glutSetWindowTitle(buffer);
  handleDisplay();
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutCreateWindow("red 3D lighted cube");
  glutDisplayFunc(handleDisplay);
  glutKeyboardFunc(handleKeyboard);
  glutIdleFunc(handleRender);
  glutMainLoop();

  return 0;
}
```

