#include <gl/glut.h>
#include <math.h>

GLfloat r(double angle) {
	return 1 - cos(angle);
}

void display(void) {
	double t, p = 3.14159265359 / 180;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 360; i+=4) {
		t = i * p;
		glVertex2f(r(t)*cos(t), r(t)*sin(t));
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("sample");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -1.5, 1.5);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}