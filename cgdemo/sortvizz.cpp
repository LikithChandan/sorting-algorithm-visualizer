#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL\glut.h>
#include <string>

#define SORT_NO 3
#define MAX 50			// Max Array size
#define SPEED 800		// Speed of sorting

int a[MAX];				// Array to sort
int swapflag = 0;		// Flag to check if swapping has occurred
int i = 0, j = 0;		// To iterate through the array
int k = 0;				// To Switch from Welcome screen to Main Screen
int flag = 0;			// For insertion sort
int sorting = 0;		// 1 if Sorted else 0
int sort_count = 0;		// To cycle through the string

std::string sort_string[] = { "Bubble Sort", "Selection Sort", "Insertion Sort" };

// Function to display text on screen char by char
void bitmap_output(int x, int y, std::string str, void* font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = str.length();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

void display_text()
{
	glColor3f(0, 1, 0);
	bitmap_output(300, 695, "SORT VIZZ", GLUT_BITMAP_TIMES_ROMAN_24);
	glEnd();



	if (sorting == 0)	// if not sorting display menu
	{
		bitmap_output(10, 595, "MENU", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 575, "Press s to SORT", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 555, "Press r to RANDOMISE", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 535, "Press c to CHANGE ALGORITHM", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 515, "Esc to QUIT", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 495, "Sort Algorithm: ", GLUT_BITMAP_9_BY_15);
		bitmap_output(150, 495, sort_string[sort_count], GLUT_BITMAP_9_BY_15);
	}
	else if (sorting == 1)	// while sorting
	{
		glColor3f(0.6, 0.6, 0.6);
		bitmap_output(10, 555, "Sorting in progress...", GLUT_BITMAP_9_BY_15);
		bitmap_output(10, 535, "Press p to PAUSE", GLUT_BITMAP_9_BY_15);
		glColor3f(0.0, 0.0, 0.0);
	}
}

void front()
{
	glColor3f(0.0, 1.0, 0.0);
	bitmap_output(300, 565, "WELCOME", GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(330, 525, "TO", GLUT_BITMAP_TIMES_ROMAN_24);
	glVertex2f(325, 521);
	glVertex2f(360, 521);
	
	bitmap_output(200, 485, "SORT VIZZ - A SORTING VISUALIZER", GLUT_BITMAP_TIMES_ROMAN_24);
	bitmap_output(30, 125, "Created By : ", GLUT_BITMAP_HELVETICA_18);
	bitmap_output(30, 95, "Anirudh G - 1RN17CS013", GLUT_BITMAP_HELVETICA_18);
	bitmap_output(30, 65, "Likith Chandan - 1RN17CS047", GLUT_BITMAP_HELVETICA_18);
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(520, 120.0); glVertex2f(520, 150); glVertex2f(796, 150); glVertex2f(796, 120.0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	bitmap_output(530, 125, "Press enter to continue", GLUT_BITMAP_HELVETICA_18);
}

void Initialize() {
	int temp1;

	// Randomize the array
	for (temp1 = 0; temp1 < MAX; temp1++)
	{
		a[temp1] = rand() % 100 + 1;
		printf("%d ", a[temp1]);
	}

	// Reset indexes
	i = j = 0;

	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 699, 0, 799);
}

// Return 1 if not sorted
int notsorted() {
	int q;
	for (q = 0; q < MAX - 1; q++)
	{
		if (a[q] > a[q + 1])
			return 1;
	}
	return 0;
}

// Main function for display
void display()
{
	int ix, temp;
	glClear(GL_COLOR_BUFFER_BIT);

	if (k == 0)
		front();
	else
	{
		display_text();
		std::string text;

		for (ix = 0; ix < MAX; ix++)
		{
			glColor3f(1, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(10 + (700 / (MAX + 1)) * ix, 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (ix + 1), 50 + a[ix] * 4);
			glVertex2f(10 + (700 / (MAX + 1)) * ix, 50 + a[ix] * 4);
			glEnd();

			text = std::to_string(a[ix]);
			glColor3f(1, 1, 1);
			bitmap_output(12 + (700 / (MAX + 1)) * ix, 35, text, GLUT_BITMAP_TIMES_ROMAN_10);
		}

		if (swapflag || sorting == 0)
		{
			glColor3f(0, 1, 1);
			glBegin(GL_POLYGON);
			glVertex2f(10 + (700 / (MAX + 1)) * j, 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (j + 1), 50);
			glVertex2f(10 + (700 / (MAX + 1)) * (j + 1), 50 + a[j] * 4);
			glVertex2f(10 + (700 / (MAX + 1)) * j, 50 + a[j] * 4);
			glEnd();
			swapflag = 0;
		}
	}
	glFlush();
}

void bubble_sort()
{
	int temp;
	while (notsorted())
	{
		while (j < MAX - 1)
		{
			if (a[j] > a[j + 1])
			{
				swapflag = 1;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;

				return;
			}
			j++;
			if (j == MAX - 1) j = 0;
			std::cout<<"swap "<<a[j]<<" and "<< a[j + 1]<<std::endl;
		}
	}
	sorting = 0;
}
void insertion_sort()
{
	int temp;

	while (i < MAX)
	{
		if (flag == 0) { j = i; flag = 1; }
		while (j < MAX - 1)
		{
			if (a[j] > a[j + 1])
			{
				swapflag = 1;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				i = j = 0;
				return;
			}
			j++;
			if (j == MAX - 1)
			{
				flag = 0;
			}
			std::cout << "swap " << a[j] << " and " << a[j + 1] << std::endl;
		}
		i++;
	}
	sorting = 0;
}

void selection_sort()
{
	int temp, j, min, pos;

	while (notsorted())
	{

		while (i < MAX - 1)
		{
			min = a[i + 1];
			pos = i + 1;
			if (i != MAX - 1)
			{
				for (j = i + 2; j < MAX; j++)
				{
					if (min > a[j])
					{
						min = a[j];
						pos = j;
					}
				}
			}
			printf("\ni=%d min=%d at %d", i, min, pos);
			printf("\nchecking %d and %d", min, a[i]);
			if (min < a[i])
			{
				printf("\nswapping %d and %d", min, a[i]);
				temp = a[pos];
				a[pos] = a[i];
				a[i] = temp;
				return;
			}
			i++;
		}
	}
	sorting = 0;
	i = j = 0;
}
int exp1 = 1;
int getMax()
{
	int mx = a[0];
	for (int i = 1; i < MAX; i++)
		if (a[i] > mx)
			mx = a[i];
	return mx;
}
//Timer function to choose sort
void makedelay(int)
{
	if (sorting)
	{
		switch (sort_count)
		{
			case 0:	bubble_sort();		break;
			case 1:	selection_sort();	break;
			case 2: insertion_sort();	break;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(SPEED / MAX, makedelay, 1);
}
// Keyboard Function
void keyboard(unsigned char key, int x, int y)
{
	if (key == 13)	//ENTER
		k = 1;
	if (k == 1 && sorting != 1)
	{
		switch (key)
		{
			case 27:	exit(0); //ESC
			case 's':	sorting = 1; break;
			case 'r':	Initialize(); break;
			case 'c':	sort_count = (sort_count + 1) % SORT_NO;	break; //cycle between 0 to 2
		}
	}
	if (k == 1 && sorting == 1)
		if (key == 'p')	sorting = 0;
}

// Main Function
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sorting Visualizer");
	Initialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000, makedelay, 1);
	glutMainLoop();
}
