#include <gl/glut.h>
#include <cstdlib>

GLfloat blue_rec[4][3] = { {-10,22,0}, {10,22,0}, {10,-22,0}, {-10,-22,0} }; //size: 10*22
GLfloat left_rec[4][3] = { {-14,26,0}, {0,26,0}, {0,-26,0}, {-14,-26,0} }; //size: 14*26
GLfloat right_rec[4][3] = { {0,26,0}, {14,26,0}, {14,-26,0}, {0,-26,0} };
GLfloat color[3][3] = { {0,0,1}, {1,1,1}, {0,0,0} }; //[0] = blue, [1] = white, [2] = black

void reshape(int width, int height) {
	float w_aspect = 16.0 / 9.0, aspect = ((float)width) / height;
	if (aspect <= w_aspect)
		glViewport(0, (height - width / w_aspect) / 2, width, width / w_aspect);
	else
		glViewport((width - height * w_aspect) / 2, 0, height*w_aspect, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1024.0, 0.0, 576.0);
}
void draw_rec(int left_color, int right_color) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {	//left border
		glColor3fv(color[left_color]);
		glVertex3fv(left_rec[i]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {	//right border
		glColor3fv(color[right_color]);
		glVertex3fv(right_rec[i]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {	//center blue
		glColor3fv(color[0]);
		glVertex3fv(blue_rec[i]);
	}
	glEnd();
}

void draw_ring(int left_color, int right_color) {	//darw rings
	for (int r = 0; r < 360; r += 45) {
		glPushMatrix();
		glRotated(r, 0, 0, 1);		//rotate 45 degree
		glTranslated(0, 74, 0);		//translate top 45 px
		draw_rec(left_color, right_color);
		glPopMatrix();
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	int x_position = 128;	//top left position
	int y_position = 432;	//top row
	int z_position = 0;
	int left_color = 0;
	int right_color = 0;

	for (int r = 0; r < 2; r++) {		//2 row of ring
		for (int c = 0; c < 4; c++) {	//every row has 4 rings
			left_color = ((r + c) % 2 == 0) ? 1 : 2;	//in row 1 left border is black if it's in odd position
			right_color = ((r + c) % 2 == 0) ? 2 : 1;	//in row 2 left border is black if it's in even position
			glPushMatrix();
			glTranslated(x_position, y_position, z_position);
			draw_ring(left_color, right_color);
			glPopMatrix();
			x_position += 256;	//every ring evenly distributed horizontally
		}
		x_position = 128;
		y_position = 144;	//bottom row
	}
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1024, 576);
	glutInitWindowPosition(220, 220);
	glutCreateWindow("Project 2");
	glClearColor(0.97, 0.97, 0.0, 0.0);	//yellowish background
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1024.0, 0.0, 576.0);	//1024*576 resolution
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
