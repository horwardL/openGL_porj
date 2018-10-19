/*
	bad
*/

#include <gl/glut.h>
#include <cstdlib>
#include<time.h>
#include <Math.h>

bool overlapping(int cx, int cy, int x[], int y[], int size) {		//check if other circles inside the 45x45 quare
	for (int d = 0; d < size; d++) {						
		if (sqrt(((cx-x[d])* (cx - x[d])) + ((cy-y[d])*(cy-y[d]))) < 90)
			return true;
	}
	return false;
}

void checkRotation(int r[], int size) {		//make sure there is atleast one rising or cave-in disk
	int rising = 0;
	int caveIn = 0;
	for (int d = 0; d < size; d++) {
		if (r[d] == 0)
			rising++;
		else
			caveIn++;
	}
	if (rising == 0)
		r[rand() % size]--;
	if (caveIn == 0)
		r[rand() % size]++;
}


void reshape(int width, int height) {
	float w_aspect = 4.0 / 3.0, aspect = ((float)width) / height;
	if (aspect <= w_aspect)
		glViewport(0, (height - width / w_aspect) / 2, width, width / w_aspect);
	else
		glViewport((width - height * w_aspect) / 2, 0, height*w_aspect, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 450.0);
}

void display(void) {
	int num_disk = rand() % 6 + 5;		//random number of disk between 5-10
	int *positionX = NULL;		//store all positions
	int *positionY = NULL;
	int *rotation = NULL;	//store all the disk color rotation
	int randX;		//random potision x and y
	int randY;
	positionX = new int[num_disk];
	positionY = new int[num_disk];
	rotation = new int[num_disk];
	for (int d = 0; d < num_disk; d++) {		//find all disk postitions and color rotation
		do {
			randX = rand() % (500) + 51;
			randY = rand() % (350) + 51;
		} while (overlapping(randX, randY, positionX, positionY, d));	//if the new position is overlaped find other position until no overlapping
		positionX[d] = randX;
		positionY[d] = randY;
		rotation[d] = rand() % 2;
	}
	checkRotation(rotation, num_disk);		//makesure there is atleast one of each color rotation
	double t, p = 3.1415926535897932384626433832795 / 180;
	float c;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	for (int d = 0; d < num_disk; d++) {
		int count = 0;
		c = 255;
		if (rotation[d] == 1) {			//draw disk with black on top
			for (int i = -90; i <= 90; i++) {
				glColor3ub(c, c, c);
				count++;
				if (count == 2) {
					if (c >= 1)
						c -= 3.5;
					count = 0;
				}
				t = i * p;
				float x = cos(t) * 45;
				glVertex2f(x + positionX[d], sin(t) * 45 + positionY[d]);
				glVertex2f(-x + positionX[d], sin(t) * 45 + positionY[d]);
			}
		}
		else {		//draw disk with white on top
			for (int i = 90; i >= -90; i--) {
				glColor3ub(c, c, c);
				count++;
				if (count == 2) {
					if (c >= 1)
						c -= 3.5;
					count = 0;
				}
				t = i * p;
				float x = cos(t) * 45;
				glVertex2f(x + positionX[d], sin(t) * 45 + positionY[d]);
				glVertex2f(-x + positionX[d], sin(t) * 45 + positionY[d]);
			}
		}
	}
	delete[] positionX;
	delete[] positionY;
	delete[] rotation;
	positionX = NULL;
	positionY = NULL;
	rotation = NULL;
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 450);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("project 1");
	glClearColor(0.4, 0.4, 0.4, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600.0, 0.0, 450.0);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
