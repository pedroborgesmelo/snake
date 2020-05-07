/*
* Snake Game - SNiX
* Written by: Pedro Henrique Borges de Melo
* E-mail: pedro.borges.melo@gmail.com
*/

#include "field.h"
#include "graphics.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <stdio.h>

#define INITIAL_SNAKE_SPEED 40

int foodbuffer;
int keybuffer, score;
int width, height, offset;
struct field f;
pthread_mutex_t mutex;

void onDisplay() {
	// setting 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	// printing
	printBackground();
	printBorder(width, height);
	offset = DISPLACEMENT + BORDER_SIDE + BORDER_SPACE;
	printSnake(offset, &(f.s));
	printFood(offset, &(f.food));
	// print food list
	glFlush();
}

void snakeWalking(int value) {
	pthread_mutex_lock(&mutex);
	if(keybuffer == -1) keybuffer = f.s.list.first->s.direction;
	// walk with snake
	int tmp;
	if(keybuffer == EAST) tmp = snakeLeft(&f);
	else if(keybuffer == SOUTH) tmp = snakeDown(&f);
	else if(keybuffer == WEST) tmp = snakeRight(&f);
	else tmp = snakeUp(&f);
	// verify if snake touch in border or in her self
	if(tmp != 0 && crash(&f) == 0) {
		glutTimerFunc(INITIAL_SNAKE_SPEED, snakeWalking, 1);
	}
	// verify food
	if(equals(&(f.s.ref), &(f.food.p)) == 1) {
		foodbuffer += 5;
		score += f.food.energy;
		putFood(&f);
	}
	// increment snake size
	if(foodbuffer > 0) {
		incrementLastSegment(&(f.s));
		--foodbuffer;
	}
	// clean buffer
	keybuffer = -1;
	// schedule task
	glutPostRedisplay();
	pthread_mutex_unlock(&mutex);
}

void keyBoard(unsigned char key, int x, int y) {
	pthread_mutex_lock(&mutex);
	int k = (int) key;
	if((k == 65 || k == 97) && f.s.list.first->s.direction != EAST) {
		// A or a is left command
		keybuffer = WEST;
	} else if((k == 83 || k == 115) && f.s.list.first->s.direction != NORTH) {
		// S or s is down command
		keybuffer = SOUTH;
	} else if((k == 100 || k == 68) && f.s.list.first->s.direction != WEST) {
		// D or d is right command
		keybuffer = EAST;
	} else if((k == 87 || k == 119) && f.s.list.first->s.direction != SOUTH) {
		// W or w is up command
		keybuffer = NORTH;
	}
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char** argv) {
	foodbuffer = 0;
	score = 0;
	keybuffer = -1;
	char* appName = "SNiX - Snake Game";
	width = 900; height = 500;
	int initX = 0, initY = 0;
	pthread_mutex_init(&mutex, NULL);
	// init variables
	int offset = 2*DISPLACEMENT + 2*BORDER_SIDE + 2*BORDER_SPACE;
	initField(&f, width, height, offset, SQUARE_SIDE + SNAKE_SPACE);
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initX, initY);
	glutCreateWindow(appName);
	// callback handlers
	glutDisplayFunc(onDisplay);
	glutKeyboardFunc(keyBoard);
	glutTimerFunc(INITIAL_SNAKE_SPEED, snakeWalking, 1);
	// main loop
	glutMainLoop();
	// exit and cleanup
	pthread_mutex_destroy(&mutex);
	return EXIT_SUCCESS;
}
