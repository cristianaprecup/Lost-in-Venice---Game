#include <C:\Users\gabri\OneDrive\Desktop\Lost-in-Venice---Game\dependencies\glfw\glfw3.h> // path to glfw, if have to put your own path to it 
// ex if you clone the projec to Desktop: C:\Users\"name"\Desktop\Lost-in-Venice--Game\dependencies\glfw\glfw3.h 

//main, you write only inside of it
int main(void)
{
	// initialize a variable window of type GLFWwindow 
    GLFWwindow* window;

	// initialize the library 
    if (!glfwInit())
		return -1; // if the library is not initialized, return -1 and close the program

	// create the window with the size and the title Lost in Venice
    window = glfwCreateWindow(1000, 632, "Lost in Venice", NULL, NULL);
    if (!window)
    {
		glfwTerminate(); // if the window cannot be created close the program
        return -1;
    }

	// DO NOT DELETE THIS LINE, this is the line that makes the game to work
    glfwMakeContextCurrent(window);

	// the main loop of the program where the window is created and the program runs
	// any code that you want to run in the game, you have to put it inside of this loop
    while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT); // this have to be the first line of the loop, it clears the window

		// anything that you want to do in the game, put here
		
		// ... code here


		// these lines have to be the last lines of the loop
		glfwSwapBuffers(window); 
        glfwPollEvents(); 
    }

	glfwTerminate(); // close the program
    return 0;
}